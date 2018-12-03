// STLViewerView.cpp : implementation of the CSTLViewerView class
//

#include "stdafx.h"
#include "STLViewer.h"

#include "STLViewerDoc.h"
#include "STLViewerView.h"

#include "MainFrm.h"
//#include "..\inc\cadbase\cadbase.h"

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
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
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

	return CGLView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerView drawing
/*
void CSTLViewerView::OnDraw(CDC* pDC)
{
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}
*/
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

	pDC->DrawCoord();	

	if (!pDoc->m_Part.IsEmpty()) {// ���ģ��m_Part��Ϊ��

		for (int i = 0;i < pDoc->m_Part.GetEntitySize();i++)//ѭ������ģ��
		{
			
			CSTLModel* s = (CSTLModel*)(pDoc->m_Part.GetEntity(i));

			if (pDoc->m_Part.GetEntity(i)->IsHighlight())//�жϸ�ģ���Ƿ��������ʾ������ѡ��
			{

				s->SetScale(m_Scale);
				s->SetMouseRo(m_xAngle, m_yAngle);
				s->SetMode(CMainFrame::m_Model); // ���û���ģʽ
			}
		}

		pDoc->m_Part.Draw(pDC); // ��OpenGL����ģ��m_Part
	}
}


BOOL CSTLViewerView::GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1)
{
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);

	if(!pDoc->m_Part.IsEmpty()){
		CBox3D box;
		if(pDoc->m_Part.GetBox(box)){
			x0 = box.x0; y0 = box.y0;	z0 = box.z0;
			x1 = box.x1; y1 = box.y1;   z1 = box.z1;
			return TRUE;
		}
	}

	return FALSE;
}

void CSTLViewerView::OnViewBack() 
{
	OnViewType(VIEW_BACK);
}

void CSTLViewerView::OnViewBottom() 
{
	OnViewType(VIEW_BOTTOM);
}

void CSTLViewerView::OnViewFront() 
{
	OnViewType(VIEW_FRONT);
}

void CSTLViewerView::OnViewLeft() 
{
	OnViewType(VIEW_LEFT);
}

void CSTLViewerView::OnViewRight() 
{
	OnViewType(VIEW_RIGHT);
}

void CSTLViewerView::OnViewTop() 
{
	OnViewType(VIEW_TOP);
}

void CSTLViewerView::OnViewSWIsometric()
{
	OnViewType(VIEW_SW_ISOMETRIC);
}

void CSTLViewerView::OnViewSEIsometric()
{
	OnViewType(VIEW_SE_ISOMETRIC);
}

void CSTLViewerView::OnViewNEIsometric()
{
	OnViewType(VIEW_NE_ISOMETRIC);
}

void CSTLViewerView::OnViewNWIsometric()
{
	OnViewType(VIEW_NW_ISOMETRIC);
}

void CSTLViewerView::OnViewZoomall() 
{
	ZoomAll();
}

void CSTLViewerView::OnViewZoomin() 
{
	Zoom(0.9);
}

void CSTLViewerView::OnViewZoomout() 
{
	Zoom(1.1);
}

void CSTLViewerView::OnViewShade() 
{
	m_pGLDC->Shading(!m_pGLDC->IsShading());
	Invalidate();
}

void CSTLViewerView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);

	m_MouseDownPoint = point; // �����������Ϣ
	SetCapture();

	// �ж�ģ���Ƿ�Ϊ�գ���Ϊ�գ��򲻽���ʰȡ����
	if(!pDoc->m_Part.IsEmpty()){
		int hits;
		UINT items[64];

		// ʰȡ����ʼ
		m_pGLDC->BeginSelection(point.x,point.y);

		// ���ø�������ʾ����ɫ(��ɫ)
		m_pGLDC->SetHighlightColor(RGB(0,0,255));	//red highlight color	

		// ��ʰȡģʽ�»���ģ��
		RenderScene(m_pGLDC);

		// ʰȡ����������ʰȡ��¼��������
		hits = m_pGLDC->EndSelection(items);
		CEntity* ent;

		// �������У����������ʾ����������ö����Ѿ��Ǹ�������ʾ����ر�
		if(hits){
			for(int i=0;i<hits;i++){
				ent = (CEntity*) items[i];
				ent->SetHighlight(!ent->IsHighlight());

			}

			Invalidate(FALSE); // ˢ����ͼ
		}

		// ����Ļ�ײ�����Ϣ�����������й�ʰȡ����ʾ��Ϣ
		CString str;
		str.Format(_T("%d entities selected"),hits);
		CMainFrame* frm = (CMainFrame*) AfxGetMainWnd();
		ASSERT(frm);
		frm->m_OutputDockBar.AddMessageLine(str);
	}

	CGLView::OnLButtonDown(nFlags, point);
}

void CSTLViewerView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;

	// �����ݲ˵���Դ
	VERIFY(menu.LoadMenu(IDR_CONTEXT_MENU));
	
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);

	// ������ݲ˵�
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,
		point.y,this);
	
}

void CSTLViewerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar){
	case VK_UP:
		MoveView(0.0,0.02);
		break;
	case VK_DOWN:
		MoveView(0.0,-0.02);
		break;
	case VK_RIGHT:
		MoveView(0.02,0);
		break;
	case VK_LEFT:
		MoveView(-0.02,0);
		break;
	}

	CGLView::OnKeyDown(nChar, nRepCnt, nFlags);
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

	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);


	if (GetCapture() == this)
	{
		for (int i = 0;i < pDoc->m_Part.GetEntitySize();i++)//ѭ������ģ��
		{
			if (pDoc->m_Part.GetEntity(i)->IsHighlight())//�ж�ģ���Ƿ��������ʾ������ѡ��
			{
				//Increment the object rotation angles
				m_xAngle += (point.y - m_MouseDownPoint.y) / 3.6;
				m_yAngle += (point.x - m_MouseDownPoint.x) / 3.6;

				//Redraw the view
				InvalidateRect(NULL, FALSE);

				//Set the mouse point
				m_MouseDownPoint = point;

				break; // ֻҪ�б�ѡ�е�ģ����ֱ������ѭ��
			}
		}
	};


	CGLView::OnMouseMove(nFlags, point);
}


BOOL CSTLViewerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);

	for (int i = 0;i < pDoc->m_Part.GetEntitySize();i++)//ѭ������ģ��
	{
		if (pDoc->m_Part.GetEntity(i)->IsHighlight())//�ж�ģ���Ƿ��������ʾ������ѡ��
		{
			
			m_Scale += 0.1 *zDelta / 120; // ��������ת��ʱ���ı����ֵ��ģ�ʹ�С���˱�����������
			break; // ֻҪ�б�ѡ�е�ģ����ֱ������ѭ��
		}
	}

	InvalidateRect(NULL, FALSE);

	return CGLView::OnMouseWheel(nFlags, zDelta, pt);
}
