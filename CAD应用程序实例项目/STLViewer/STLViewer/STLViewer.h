
// STLViewer.h : STLViewer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSTLViewerApp:
// �йش����ʵ�֣������ STLViewer.cpp
//

class CSTLViewerApp : public CWinApp
{
public:
	CSTLViewerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSTLViewerApp theApp;
