// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <windows.h>
#include <iostream>

HHOOK g_hHook = nullptr;
HINSTANCE g_hInstance = nullptr;
LRESULT CALLBACK MsgHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (HC_ACTION == nCode) // ˵������Ϣ����
	{
		PMSG pMsg = (PMSG)lParam;
		if (WM_CHAR == pMsg->message)
		{
			// ȷ����ʱ�Ѿ�������һ����
			char szKey = (char)pMsg->wParam;

			// ��Ч�ַ���Ϣ ��32��126֮��
			if (szKey >= 32 && szKey <= 126)
			{
				char szWindowName[MAXBYTE] = { 0 };
				char szDebug[MAXBYTE] = { 0 };
				GetWindowTextA(pMsg->hwnd, szWindowName, MAXBYTE);
				sprintf_s(szDebug, MAXBYTE, "�������� %s���յ���һ����Ϣ��%c", szWindowName, szKey);
				OutputDebugStringA(szDebug);
			}
			
		}
	}

	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}


extern "C"
_declspec(dllexport) BOOL StartHook()
{
	// ��Ҫ��DLL��̬���ӿ���ʵ���������
	// ��Ϊֻ�ж�̬���ӿ����ȫ�ֹ����
	// �ص����� Hook �Ѿ�Hook���� ֻ�����Ϲ��ˣ�����
	g_hHook = SetWindowsHookEx(WH_GETMESSAGE, MsgHookProc, g_hInstance, NULL);
	if (nullptr == g_hHook)
	{
		// ���ص�������
		SetLastError(GetLastError());
		return FALSE;
	}
	return TRUE;
}

BOOL UnHook()
{
	if (g_hHook)
	{
		return UnhookWindowsHookEx(g_hHook);
	}
	return FALSE;
}

// main ����
// dll��ʵҲ��main�����ģ� �����
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: // ��DLL�����������ʱ����
		g_hInstance = hModule;
		break;
	case DLL_THREAD_ATTACH: // ��DLL���߳������Ǵ���
	case DLL_THREAD_DETACH: // ��DLL���߳����������ʱ����
	case DLL_PROCESS_DETACH: // ��DLL���ӽ����а����ʱ�򴥷�
		UnHook();
		break;
	}
	return TRUE;
}

