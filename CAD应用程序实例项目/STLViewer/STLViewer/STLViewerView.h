// STLViewerView.h : interface of the CSTLViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STLVIEWERVIEW_H__D5F8FC2E_373C_442E_AAF5_D321322B1658__INCLUDED_)
#define AFX_STLVIEWERVIEW_H__D5F8FC2E_373C_442E_AAF5_D321322B1658__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define TETLIBRARY

#include "..\inc\glContext\openGLDC.h" // ˵������CGLView
#include "..\inc\glContext\Camera.H"

//#include "..\inc\tetgen\tetgen.h"
#pragma comment(lib,"TetGen.lib")

class CSTLViewerView : public CGLView // �ڻ���CGLView������
{
protected: // create from serialization only
	CSTLViewerView();
	DECLARE_DYNCREATE(CSTLViewerView)

// Attributes
public:
	CSTLViewerDoc* GetDocument();

	GLfloat m_xAngle;
	GLfloat m_yAngle; // ������ת�Ƕ�
	GLfloat m_xPos;
	GLfloat m_yPos;
	CPoint m_MouseDownPoint;
	float m_Scale;

	// ���¶������⺯����ʵ�ֶ�̬��
	virtual void RenderScene(COpenGLDC* pDC);

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSTLViewerView)
	public:
		// ע�͵��˺�����ʹ�û����OnDraw()����
		//virtual void OnDraw(CDC*pDC);  
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSTLViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSTLViewerView)
	// ��ͼѡ����������
	afx_msg void OnViewBack();
	afx_msg void OnViewBottom();
	afx_msg void OnViewFront();
	afx_msg void OnViewLeft();
	afx_msg void OnViewRight();
	afx_msg void OnViewTop();
	afx_msg void OnViewSWIsometric();
	afx_msg void OnViewSEIsometric();
	afx_msg void OnViewNEIsometric();
	afx_msg void OnViewNWIsometric();

	// ȫ�����ź���
	afx_msg void OnViewZoomall();

	// ģ����ʾ�Ŵ���
	afx_msg void OnViewZoomin();

	// ģ����ʾ��С����
	afx_msg void OnViewZoomout();

	// ��Ⱦ/����Ⱦ�л�
	afx_msg void OnViewShade();

	// ��Ӧ������Ϣ
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	// ʵ�����Լ������⺯��GetBox()
	virtual BOOL	GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in STLViewerView.cpp
inline CSTLViewerDoc* CSTLViewerView::GetDocument()
   { return (CSTLViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STLVIEWERVIEW_H__D5F8FC2E_373C_442E_AAF5_D321322B1658__INCLUDED_)
