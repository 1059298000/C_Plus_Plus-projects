
// FeatureReuse.h : FeatureReuse Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef _DEBUG // �ڴ�й©���֧�֡�
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <malloc.h>    // ��� malloc.h �� crtdbg.h ˳���µ� Debug Assertion Failed, "Corrupted pointer passed to _freea" ��
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "resource.h"       // ������


// CFeatureReuseApp:
// �йش����ʵ�֣������ FeatureReuse.cpp
//

class CFeatureReuseApp : public CWinAppEx
{
public:
	CFeatureReuseApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFeatureReuseApp theApp;
