#if !defined(AFX_PARTTREEVIEW_H__2DA1D8A5_360F_4EF9_9E1C_439F2F48B769__INCLUDED_)
#define AFX_PARTTREEVIEW_H__2DA1D8A5_360F_4EF9_9E1C_439F2F48B769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PartTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPartTreeView view
#include <afxcview.h>

class CSTLViewerDoc;
class CEntity;
class CPartTreeView : public CTreeView
{
protected:
	CPartTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPartTreeView)

// Attributes
public:

// Operations
public:
	CSTLViewerDoc* GetDocument(); // ʵ����CSTLViewerDoc�ĵ��Ĺ���

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPartTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

	// ��Ӧ���ĵ���ĺ���UpdateAllViews()
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPartTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �����ĵ�ģ������
	void	ChangeEntityName(CEntity* ent); // �ı�ģ�͵�����
	void	ChangeEntityColor(CEntity* ent); // �ı�ģ����ɫ
	void	ChangeEntityVisible(CEntity* ent); // �ı�ģ����ʾ����

	// Generated message map functions
protected:
	//{{AFX_MSG(CPartTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CImageList	m_ImageList; // �������Կؼ�����Ŀ��ͼ��
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARTTREEVIEW_H__2DA1D8A5_360F_4EF9_9E1C_439F2F48B769__INCLUDED_)
