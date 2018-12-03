
// FeatureReuseView.h : CFeatureReuseView ��Ľӿ�
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

#include "opengl\OpenGLDC.h"
#pragma once

class CFeatureReuseView : public CGLView
{
protected: // �������л�����
	CFeatureReuseView();
	DECLARE_DYNCREATE(CFeatureReuseView)

// ����
public:
	CFeatureReuseDoc* GetDocument() const;


	double CalFrequency(); // ������Ļˢ��֡�ʵ���ʾFPS

// ����
public:
	GLfloat m_xAngle;
	GLfloat m_yAngle; // ������ת�Ƕ�
	GLfloat m_xPos;
	GLfloat m_yPos;
	CPoint m_MouseDownPoint;
	float m_Scale;


	void myIdle(void); // ���ڶ�����ʾ���
	static int time; // �������ʱ��

// ��д
public:
	virtual void			RenderScene(COpenGLDC* pDC);
	virtual BOOL		PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL		OnPreparePrinting(CPrintInfo* pInfo);
	virtual void			OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void			OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void			OnSize(UINT nType, int cx, int cy);
	virtual void				OnInitialUpdate();
	virtual BOOL			GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1);


// ʵ��
public:
	virtual ~CFeatureReuseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:

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

	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // FeatureReuseView.cpp �еĵ��԰汾
inline CFeatureReuseDoc* CFeatureReuseView::GetDocument() const
   { return reinterpret_cast<CFeatureReuseDoc*>(m_pDocument); }
#endif

