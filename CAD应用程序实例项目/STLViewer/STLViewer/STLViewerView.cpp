// STLViewerView.cpp : implementation of the CSTLViewerView class
//

#include "stdafx.h"
#include "STLViewer.h"

#include "MainFrm.h"

#include "STLViewerDoc.h"
#include "STLViewerView.h"
#include <iostream>

#include "tetgen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerView

IMPLEMENT_DYNCREATE(CSTLViewerView, CGLView)

BEGIN_MESSAGE_MAP(CSTLViewerView, CGLView)
	//{{AFX_MSG_MAP(CSTLViewerView)
	ON_COMMAND(ID_VIEW_BACK, OnViewBack)
	ON_COMMAND(ID_VIEW_BOTTOM, OnViewBottom)
	ON_COMMAND(ID_VIEW_FRONT, OnViewFront)
	ON_COMMAND(ID_VIEW_LEFT, OnViewLeft)
	ON_COMMAND(ID_VIEW_RIGHT, OnViewRight)
	ON_COMMAND(ID_VIEW_TOP, OnViewTop)
	ON_COMMAND(ID_VIEW_SW_ISOMETRIC, OnViewSWIsometric)
	ON_COMMAND(ID_VIEW_SE_ISOMETRIC, OnViewSEIsometric)
	ON_COMMAND(ID_VIEW_NE_ISOMETRIC, OnViewNEIsometric)
	ON_COMMAND(ID_VIEW_NW_ISOMETRIC, OnViewNWIsometric)
	ON_COMMAND(ID_VIEW_ZOOMALL, OnViewZoomall)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_VIEW_SHADE, OnViewShade)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerView construction/destruction

CSTLViewerView::CSTLViewerView()
{
	// TODO: add construction code here
	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_Scale = 1.0f;
}

CSTLViewerView::~CSTLViewerView()
{
}

BOOL CSTLViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerView drawing
/////////////////////////////////////////////////////////////////////////////
// CSTLViewerView diagnostics

#ifdef _DEBUG
void CSTLViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CSTLViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSTLViewerDoc* CSTLViewerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSTLViewerDoc)));
	return (CSTLViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerView message handlers
void CSTLViewerView::RenderScene(COpenGLDC* pDC)
{
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);

	// ����һ������ϵ���
	pDC->DrawCoord();

	// ����pSTLModelģ�Ͷ������ת�ǶȺ������������ű���
	if (!pDoc->m_Part.IsEmpty()) {// ���ģ��m_Part��Ϊ��

		for (int i = 0;i< pDoc->m_Part.GetEntitySize();i++)
		{// ѭ��ģ��ʵ�֣�ʵ�ֶ�ģ��ͬ�����Ŵ�С����תģ��
			CSTLModel* s = (CSTLModel*)(pDoc->m_Part.GetEntity(i));
			s->SetScale(m_Scale);
			s->SetMouseRo(m_xAngle, m_yAngle);
			s->SetMode(CMainFrame::m_Model); // ���û���ģʽ
		}

		pDoc->m_Part.Draw(pDC); // ��OpenGL����ģ��m_Part
	}

	//glLoadIdentity();
	//glTranslatef(m_xPos, m_yPos, -5.0f);
	//glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	//glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	//glScalef(m_Scale, m_Scale, m_Scale);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	////Front Face
	//glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//glColor3f(1.0f, 1.0f, 0.0f);
	//glVertex3f(1.0f, -1.0f, 0.0f);
	//glColor3f(1.0f, 0.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glVertex3f(-1.0f, 1.0f, 0.0f);
	//glEnd();
	//glColor3f(1.0f, 1.0f, 0.0f);
	////Back Face
	//glBegin(GL_POLYGON);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);
	//glVertex3f(1.0f, 1.0f, -1.0f);
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glEnd();
	//glColor3f(1.0f, 0.0f, 1.0f);
	////Left Face
	//glBegin(GL_POLYGON);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//glVertex3f(-1.0f, 1.0f, 0.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glEnd();
	//glColor3f(0.0f, 1.0f, 0.0f);
	////Right Face
	//glBegin(GL_POLYGON);
	//glVertex3f(1.0f, -1.0f, 0.0f);
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glVertex3f(1.0f, 1.0f, -1.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glEnd();
	//glColor3f(0.0f, 1.0f, 1.0f);
	////Top Face
	//glBegin(GL_POLYGON);
	//glVertex3f(-1.0f, 1.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, -1.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);
	//glEnd();
	//glColor3f(0.0f, 0.0f, 1.0f);
	////Botton Face
	//glBegin(GL_POLYGON);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glVertex3f(1.0f, -1.0f, 0.0f);
	//glEnd();

}

BOOL CSTLViewerView::GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1)
{
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);

	if(!pDoc->m_Part.IsEmpty()){//���ģ�Ͳ�Ϊ�գ���ȡ���ݺ���Ϣ
		CBox3D box;
		if(pDoc->m_Part.GetBox(box)){
			x0 = box.x0; y0 = box.y0;	z0 = box.z0;
			x1 = box.x1; y1 = box.y1;   z1 = box.z1;
			return TRUE;
		}
	}

	return FALSE; // ģ��Ϊ��
}

void CSTLViewerView::OnViewBack() 
{
	OnViewType(VIEW_BACK); // ģ�͵ĺ���ͼ
}

void CSTLViewerView::OnViewBottom() 
{
	OnViewType(VIEW_BOTTOM); // ģ�͵ĵ���ͼ
}

void CSTLViewerView::OnViewFront() 
{
	OnViewType(VIEW_FRONT); // ģ�͵�ǰ��ͼ
}

void CSTLViewerView::OnViewLeft() 
{
	OnViewType(VIEW_LEFT); // ģ�͵�����ͼ
}

void CSTLViewerView::OnViewRight() 
{
	OnViewType(VIEW_RIGHT); // ģ�͵�����ͼ
}

void CSTLViewerView::OnViewTop() 
{
	OnViewType(VIEW_TOP); // ģ�͵Ķ���ͼ
}

void CSTLViewerView::OnViewSWIsometric()
{
	OnViewType(VIEW_SW_ISOMETRIC); // ģ�͵�SW����ͼ
}

void CSTLViewerView::OnViewSEIsometric()
{
	OnViewType(VIEW_SE_ISOMETRIC); // ģ�͵�SE����ͼ
}

void CSTLViewerView::OnViewNEIsometric()
{
	OnViewType(VIEW_NE_ISOMETRIC); // ģ�͵�NE����ͼ
}

void CSTLViewerView::OnViewNWIsometric()
{
	OnViewType(VIEW_NW_ISOMETRIC); // ģ�͵�NW����ͼ
}

void CSTLViewerView::OnViewZoomall() 
{
	ZoomAll(); // ��ģ����ʾ������������
}

void CSTLViewerView::OnViewZoomin() 
{
	Zoom(0.9); // ���Ӿ�������СΪԭ����0.9��ģ������Ļ�ϵ�ʵ����ʾ�ߴ�Ŵ�
}

void CSTLViewerView::OnViewZoomout() 
{
	Zoom(1.1); // ���Ӿ�����Ŵ���1.1����ģ������Ļ�ϵ�ʵ����ʾ�ߴ���С
}

void CSTLViewerView::OnViewShade() 
{
	m_pGLDC->Shading(!m_pGLDC->IsShading()); // �򿪻�ر�OpenGL����ɫ����
	Invalidate();
}

void CSTLViewerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar){
	case VK_UP:
		MoveView(0.0,0.02); // �����ƶ�����2%
		break;
	case VK_DOWN:
		MoveView(0.0,-0.02); // �����ƶ�����2%
		break;
	case VK_RIGHT:
		MoveView(0.02,0); // �����ƶ�����2%
		break;
	case VK_LEFT:
		MoveView(-0.02,0); // �����ƶ�����2%
		break;
	}
	
	CGLView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSTLViewerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_MouseDownPoint = point;
	SetCapture();

	CGLView::OnLButtonDown(nFlags, point);
}


void CSTLViewerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_MouseDownPoint = CPoint(0, 0);
	ReleaseCapture();

	CGLView::OnLButtonUp(nFlags, point);
}


void CSTLViewerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (GetCapture() == this)
	{
		//Increment the object rotation angles
		m_xAngle += (point.y - m_MouseDownPoint.y) / 3.6;
		m_yAngle += (point.x - m_MouseDownPoint.x) / 3.6;

		//Redraw the view
		InvalidateRect(NULL, FALSE);

		//Set the mouse point
		m_MouseDownPoint = point;
	};

	CGLView::OnMouseMove(nFlags, point);
}


BOOL CSTLViewerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_Scale += 0.1 *zDelta / 120; // ��������ת��ʱ���ı����ֵ��ģ�ʹ�С���˱�����������

	InvalidateRect(NULL, FALSE);
	return CGLView::OnMouseWheel(nFlags, zDelta, pt);
}
