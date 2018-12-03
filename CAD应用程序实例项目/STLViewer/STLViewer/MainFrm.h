// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__6D83EE55_397D_4E92_818E_86D7465F9521__INCLUDED_)
#define AFX_MAINFRM_H__6D83EE55_397D_4E92_818E_86D7465F9521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	static int m_Model; // ����ģʽ����

// Operations
public:
	CMFCButton * NewMyRadio(int nID, CString titile, CRect rect, int nStyle);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	m_wndDisplayBar; // ������ʾ������

	CMFCButton *p_MyRadio[3]; // �Զ��嵥ѡ��ť

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG

	afx_msg void OnMyRadio1(); //��ѡ��ť1
	afx_msg void OnMyRadio2(); //��ѡ��ť2
	afx_msg void OnMyRadio3(); //��ѡ��ť3

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6D83EE55_397D_4E92_818E_86D7465F9521__INCLUDED_)
