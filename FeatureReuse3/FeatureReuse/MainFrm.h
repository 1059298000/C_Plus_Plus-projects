
// MainFrm.h : CMainFrame ��Ľӿ�
//

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

#include "DockingBar/ViewBar.h"
#include "CButtonST/BCMenu.h"
#include "CButtonST/BtnST.h"

#pragma once

class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

	static int m_Mode; // ��ѡģʽѡ�����
	static bool is_PrintArrows; // �Ƿ����ʸ����ͷ
	static bool is_Draw_cloudPicture; // �Ƿ���Ʋ�ɫ��ͼ
	
	static int m_stage; // ��һ����ť��ѭ������������ÿһ��ģ�͵��ػ�

	static int m_delta; // ���ڶ�̬��ʾ�Ľ׶�ѭ������
	static int m_Counts; // ��ѡģʽѡ�����

	static COLORREF m_Color; //��̬��Ա ������ɫ����


	bool isChecked;
	bool isChecked2;

// ����
public:
	
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = 
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL,
		CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
	CMFCButton * NewMyRadio(int nID, CString titile, CRect rect, int nStyle);
	CMFCButton * NewMyButton(int nID, CString titile, CRect rect, int nStyle);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;

	CMFCToolBarImages m_UserImages;

	CMFCToolBar		m_wndDisplayBar; // �Զ���ͼ�β���������

	CMFCToolBar		ButtonBar; // �Զ���ͼ�β���������

	CMFCButton *p_MyBut[4]; // �Զ��尴ť
	CMFCButton *p_MyRadio[4]; // �Զ��嵥ѡ��ť

	CMFCColorButton* m_ColorPicker;  // ��ɫѡ��ť


	void	DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf);

// ���ɵ���Ϣӳ�亯��
protected:
	// ��ť��Ϣ��Ӧ����

	CButtonST m_btn;


	afx_msg void OnMybut1();
	afx_msg void OnMybut2();
	afx_msg void OnMybut3();

	afx_msg void OnMybut4();
	afx_msg void OnMybut5();
	afx_msg void OnMybut6();
	afx_msg void OnMybut7(); 

	afx_msg void OnMyColorbut();

	afx_msg void OnMyRadio1(); //��ѡ��ť1
	afx_msg void OnMyRadio2(); //��ѡ��ť2
	afx_msg void OnMyRadio3(); //��ѡ��ť3
	afx_msg void OnMyRadio4();// ��ѡ��ť4

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
};

