
// FeatureReuseView.cpp : CFeatureReuseView ���ʵ��
//

#include "stdafx.h"
#include "FeatureReuse.h"
#include "FeatureReuseDoc.h"
#include "FeatureReuseView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CFeatureReuseView
IMPLEMENT_DYNCREATE(CFeatureReuseView, CGLView)

BEGIN_MESSAGE_MAP(CFeatureReuseView, CGLView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFeatureReuseView::OnFilePrintPreview)

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
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_VIEW_ZOOMALL, OnViewZoomall)
	ON_COMMAND(ID_VIEW_SHADE, OnViewShade)

	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CFeatureReuseView ����/����

CFeatureReuseView::CFeatureReuseView()
{
	// TODO: �ڴ˴���ӹ������
	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_Scale = 1.0f;

}

CFeatureReuseView::~CFeatureReuseView()
{
}

BOOL CFeatureReuseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

int CFeatureReuseView::time = 200;

void CFeatureReuseView::myIdle(void)
{
	++time;
	if (time >= 360)
		time = 0;
	//Redraw the view
	InvalidateRect(NULL, FALSE);
}


// ������Ļˢ��֡�ʵ���ʾFPS
double CFeatureReuseView::CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if (count <= 50)
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current - last) / (double)CLK_TCK;
	save = 50.0 / timegap;
	return save;
}

void CFeatureReuseView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (CMainFrame::m_Mode == 4) // ����ģʽ�Ƕ�̬��ʾ
	{
	
		CMainFrame::m_delta = CMainFrame::m_delta + (CFeatureReuseDoc::steps)/6;

		if (CMainFrame::m_delta > CFeatureReuseDoc::steps - 1)
		{
			CMainFrame::m_delta = CFeatureReuseDoc::steps - 1;
		}
		else
			CMainFrame::m_Counts = CMainFrame::m_Counts + 1;

		InvalidateRect(NULL, FALSE);  // ǿ��ˢ�³���
	}

	CGLView::OnTimer(nIDEvent);
}

int CFeatureReuseView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGLView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
		SetTimer(0, 1000, NULL); // ���ü�ʱ�����Ҽ��ʱ��Ϊ1sˢ��һ��

	return 0;
}

// CFeatureReuseView ����
void CFeatureReuseView::RenderScene(COpenGLDC* pDC)
{
	CFeatureReuseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// ��̬�������ű���
	pDoc->SetScale(m_Scale);
	// ��̬������ת�Ƕ�
	pDoc->SetMouseRotate(m_xAngle, m_yAngle);
	// ���û���ģ�͵Ĳ�����ɫ����
	pDC->SetMaterialColor(CMainFrame::m_Color); 

	// ���û���ģʽ
	pDoc->SetMode(CMainFrame::m_Mode);

	// ���û���ʸ����ͷģʽ
	pDoc->SetArrows(CMainFrame::is_PrintArrows);

	// ���û��Ʋ�ɫ��ͼģʽ
	pDoc->Set_cloudPicture(CMainFrame::is_Draw_cloudPicture);	

	// ����ģ����ʾ�׶�
	pDoc->SetStage(CMainFrame::m_stage);

	// ����ģ�Ͷ�̬��ʾѭ������
	pDoc->SetDelta(CMainFrame::m_delta);
	pDoc->SetCounter(CMainFrame::m_Counts); // ������

	// ����������
	pDC->DrawCoord();

	// ����ģ��
	pDoc->DrawModel(pDC);

}

void CFeatureReuseView::OnInitialUpdate()
{
	CGLView::OnInitialUpdate();
	OnViewType(VIEW_SW_ISOMETRIC);
	ZoomAll();
}
// CFeatureReuseView ��ӡ

void CFeatureReuseView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CFeatureReuseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFeatureReuseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFeatureReuseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CFeatureReuseView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFeatureReuseView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

// CFeatureReuseView ���

#ifdef _DEBUG
void CFeatureReuseView::AssertValid() const
{
	CView::AssertValid();
}

void CFeatureReuseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFeatureReuseDoc* CFeatureReuseView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFeatureReuseDoc)));
	return (CFeatureReuseDoc*)m_pDocument;
}
#endif //_DEBUG

// CFeatureReuseView ��Ϣ�������
void CFeatureReuseView::OnSize(UINT nType, int cx, int cy)
{
	CGLView::OnSize(nType, cx, cy);
	ZoomAll();
}
//
BOOL CFeatureReuseView::GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1)
{
	CFeatureReuseDoc* pDoc = GetDocument();
	ASSERT(pDoc);

	if(pDoc->meshes.size()>0)
	{
		x0 = (pDoc->getbox()).min[0]; 
		y0 = (pDoc->getbox()).min[1]; 
		z0 = (pDoc->getbox()).min[2]; 
		x1 = (pDoc->getbox()).max[0]; 
		y1 = (pDoc->getbox()).max[1];   
		z1 = (pDoc->getbox()).max[2]; 
		return TRUE;
	}

	return FALSE;
}
//


void CFeatureReuseView::OnViewBack()
{
	OnViewType(VIEW_BACK); // ģ�͵ĺ���ͼ
}

void CFeatureReuseView::OnViewBottom()
{
	OnViewType(VIEW_BOTTOM); // ģ�͵ĵ���ͼ
}

void CFeatureReuseView::OnViewFront()
{
	OnViewType(VIEW_FRONT); // ģ�͵�ǰ��ͼ
}

void CFeatureReuseView::OnViewLeft()
{
	OnViewType(VIEW_LEFT); // ģ�͵�����ͼ
}

void CFeatureReuseView::OnViewRight()
{
	OnViewType(VIEW_RIGHT); // ģ�͵�����ͼ
}

void CFeatureReuseView::OnViewTop()
{
	OnViewType(VIEW_TOP); // ģ�͵Ķ���ͼ
}

void CFeatureReuseView::OnViewSWIsometric()
{
	OnViewType(VIEW_SW_ISOMETRIC); // ģ�͵�SW����ͼ
}

void CFeatureReuseView::OnViewSEIsometric()
{
	OnViewType(VIEW_SE_ISOMETRIC); // ģ�͵�SE����ͼ
}

void CFeatureReuseView::OnViewNEIsometric()
{
	OnViewType(VIEW_NE_ISOMETRIC); // ģ�͵�NE����ͼ
}

void CFeatureReuseView::OnViewNWIsometric()
{
	OnViewType(VIEW_NW_ISOMETRIC); // ģ�͵�NW����ͼ
}

void CFeatureReuseView::OnViewZoomall()
{
	ZoomAll(); // ��ģ����ʾ������������
}

void CFeatureReuseView::OnViewZoomin()
{
	Zoom(0.9); // ���Ӿ�������СΪԭ����0.9��ģ������Ļ�ϵ�ʵ����ʾ�ߴ�Ŵ�
}

void CFeatureReuseView::OnViewZoomout()
{
	Zoom(1.1); // ���Ӿ�����Ŵ���1.1����ģ������Ļ�ϵ�ʵ����ʾ�ߴ���С
}

void CFeatureReuseView::OnViewShade()
{
	m_pGLDC->Shading(!m_pGLDC->IsShading()); // �򿪻�ر�OpenGL����ɫ����
	Invalidate();
}

void CFeatureReuseView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_UP:
		MoveView(0.0, 0.04); // �����ƶ�����4%
		break;
	case VK_DOWN:
		MoveView(0.0, -0.04); // �����ƶ�����4%
		break;
	case VK_RIGHT:
		MoveView(0.04, 0); // �����ƶ�����4%
		break;
	case VK_LEFT:
		MoveView(-0.04, 0); // �����ƶ�����4%
		break;
	}

	CGLView::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CFeatureReuseView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_MouseDownPoint = point;
	SetCapture();

	CGLView::OnLButtonDown(nFlags, point);
}

void CFeatureReuseView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_MouseDownPoint = CPoint(0, 0);
	ReleaseCapture();

	CGLView::OnLButtonUp(nFlags, point);
}

void CFeatureReuseView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CGLView::OnMButtonDown(nFlags, point);
}

void CFeatureReuseView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_CONTROL)
	{
		CGLView::OnMouseMove(nFlags, point);
		return;
	}

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

BOOL CFeatureReuseView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_Scale += 0.8 *zDelta / 120; // ��������ת��ʱ���ı����ֵ��ģ�ʹ�С���˱�����������


	InvalidateRect(NULL, FALSE);
	return CGLView::OnMouseWheel(nFlags, zDelta, pt);
}



