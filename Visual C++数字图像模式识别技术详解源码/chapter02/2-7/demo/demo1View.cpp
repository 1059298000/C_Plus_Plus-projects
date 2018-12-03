// demo1View.cpp : implementation of the CDemo1View class
//

#include "stdafx.h"
#include "demo1.h"

#include "demo1Doc.h"
#include "demo1View.h"
#include "MainFrm.h"

#include "GeometryTrans.h"//���α任��
#include "GeometryMoveDlg.h"//ƽ�Ʋ�������
#include "ZoomDlg.h"   //���Ų�������
#include "RotateDlg.h"//��ת�Ƕ�����
#include "GrayTrans.h" //�Ҷȱ任��
#include "HistogramDrawDlg.h"//ֱ��ͼ��ʾ
#include "ThreshStrechDlg.h"//��ֵ����
#include "StrechWindowDlg.h"//���ڱ任��������
#include "LinearStepParamDlg.h"//�ֶ����������������
#include "ImageEnhance.h"//ͼ�������ǿ��
#include "NeiAverSmoothDlg.h"//ͼ������ƽ��ģ������
#include "MedianSmoothDlg.h"//ͼ����ֵƽ��ģ������
#include "FourierTrans.h"//����Ҷ�任��
#include "ImageFreqEnhance.h"//ͼ��Ƶ����ǿ��
#include "WaveletTrans.h"//С���任��
#include "Morphology.h"//ͼ����̬ѧ��

//ȫ�ֱ���
FourierTrans fftTrans;
WaveletTrans wavltTrans;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#include "ImageDib.h"
/////////////////////////////////////////////////////////////////////////////
// CDemo1View

IMPLEMENT_DYNCREATE(CDemo1View, CView)

BEGIN_MESSAGE_MAP(CDemo1View, CView)
	//{{AFX_MSG_MAP(CDemo1View)
	ON_COMMAND(id_Move, OnMove)
	ON_COMMAND(id_HorizontalMirror, OnHorizontalMirror)
	ON_COMMAND(id_VerticalMirror, OnVerticalMirror)
	ON_COMMAND(id_Zoom, OnZoom)
	ON_COMMAND(id_Clockwise90, OnClockwise90)
	ON_COMMAND(id_Anticlockwise90, OnAnticlockwise90)
	ON_COMMAND(id_Rotate180, OnRotate180)
	ON_COMMAND(id_FreeRotate, OnFreeRotate)
	ON_COMMAND(id_Binary, OnBinary)
	ON_COMMAND(id_HistogramDraw, OnHistogramDraw)
	ON_COMMAND(id_HistgramAver, OnHistgramAver)
	ON_COMMAND(id_ImageReverse, OnImageReverse)
	ON_COMMAND(id_ImgThresh, OnImgThresh)
	ON_COMMAND(id_ThresholdWindow, OnThresholdWindow)
	ON_COMMAND(id_LinearStrecth, OnLinearStrecth)
	ON_COMMAND(id_PepperSaltNoise, OnPepperSaltNoise)
	ON_COMMAND(id_GaussNoise, OnGaussNoise)
	ON_COMMAND(id_ChooseMaskSmooth, OnChooseMaskSmooth)
	ON_COMMAND(id_GradeSharp, OnGradeSharp)
	ON_COMMAND(id_NeiAveSmooth, OnNeiAveSmooth)
	ON_COMMAND(id_MedianSmooth, OnMedianSmooth)
	ON_COMMAND(id_LaplaceSharp, OnLaplaceSharp)
	ON_COMMAND(id_QuickFFt, OnQuickFFt)
	ON_COMMAND(id_QuickFFt_Reverse, OnQuickFFtReverse)
	ON_COMMAND(id_IdealLowPass, OnIdealLowPass)
	ON_COMMAND(id_ButterLowPass, OnButterLowPass)
	ON_COMMAND(id_IdealHighPass, OnIdealHighPass)
	ON_COMMAND(id_ButterHighPass, OnButterHighPass)
	ON_COMMAND(id_HarrWaveletTrans, OnHarrWaveletTrans)
	ON_COMMAND(id_HarrWavRevTrans, OnHarrWavRevTrans)
	ON_COMMAND(id_Erosion, OnErosion)
	ON_COMMAND(id_Dilation, OnDilation)
	ON_COMMAND(id_Open, OnOpen)
	ON_COMMAND(id_Close, OnClose)
	ON_COMMAND(id_Thinning, OnThinning)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo1View construction/destruction

CDemo1View::CDemo1View()
{
	// TODO: add construction code here

}

CDemo1View::~CDemo1View()
{
}

BOOL CDemo1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo1View drawing
/**/
void CDemo1View::OnDraw(CDC* pDC)
{
	CDemo1Doc* pDoc = GetDocument();			//��ȡ�ĵ���ָ��
	ASSERT(pDoc != NULL);
	ImageDib* pDib = pDoc->m_dib;					//����m_dib��ָ��
	
	pDib->Draw(pDC, CPoint(0, 0), pDib->GetDimensions()); 	//��ʾDIB
}


/////////////////////////////////////////////////////////////////////////////
// CDemo1View printing

BOOL CDemo1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemo1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemo1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemo1View diagnostics

#ifdef _DEBUG
void CDemo1View::AssertValid() const
{
	CView::AssertValid();
}

void CDemo1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemo1Doc* CDemo1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemo1Doc)));
	return (CDemo1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo1View message handlers

void CDemo1View::OnMove() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8 && pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//ƽ�Ʋ������öԻ���
	GeometryMoveDlg dlgPara;
	if(dlgPara.DoModal()==IDOK)
	{
		//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
		GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
			pDib->m_lpColorTable, pDib->m_pImgData);
		
		//��dlgPara.m_Xmove, dlgPara.m_Ymove��Ϊƽ��������ͼ��ƽ��
		geoTrans.Move(dlgPara.m_Xmove, dlgPara.m_Ymove);

		
/*	*/	//�½���ͼ���ڣ����ĵ���ʾ�任���
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo1Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->m_dib;
		dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
		pView->OnInitialUpdate();		
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);

//      ���ĵ���ʾ�任���
/*
		CClientDC dc(this);
		ImageDib *dibNew = new ImageDib;
		dibNew->ReplaceDib(geoTrans.GetDimensions(),
			geoTrans.m_nBitCountOut,geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
		dibNew->Draw(&dc,CPoint(0,0),dibNew->GetDimensions());
		pDib->Draw(&dc,CPoint(dibNew->GetDimensions().cx,0),pDib->GetDimensions());
 */
/*
		pDib->ReplaceDib(geoTrans.GetDimensions(),
			geoTrans.m_nBitCountOut,geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
		Invalidate();
*/
	}	
}

void CDemo1View::OnHorizontalMirror() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//ˮƽ����
	geoTrans.MirrorHorTrans();
   //��ʾ�任���
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo1Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->m_dib;
		dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
		pView->OnInitialUpdate();		
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);

}

void CDemo1View::OnVerticalMirror() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ֱ����
	geoTrans.MirrorVerTrans();
   //��ʾ�任���
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo1Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->m_dib;
		dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
		pView->OnInitialUpdate();		
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
}

void CDemo1View::OnZoom() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//ԭͼ��ߴ�
	CSize oldImgSize=pDib->GetDimensions();
	
	//���Ų������öԻ���
	ZoomDlg dlgPara;
	
	if(dlgPara.DoModal()==IDOK){
		//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
		GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
			pDib->m_lpColorTable, pDib->m_pImgData);
		
		//����ָ�������ű����Զ�ԭͼ�������������
		geoTrans.Zoom(dlgPara.m_XstrechRatio,dlgPara.m_YstrechRatio);	
		
		//�½���ͼ���ڣ���ʾ������
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo1Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->m_dib;
		dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
			geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
		Invalidate();
	}
}

void CDemo1View::OnClockwise90() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//˳ʱ��90��
	geoTrans.Clockwise90();
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
		geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

void CDemo1View::OnAnticlockwise90() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ʱ��90��
	geoTrans.Anticlockwise90();
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
		geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

void CDemo1View::OnRotate180() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ת180��
	geoTrans.Rotate180();
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
		geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

void CDemo1View::OnFreeRotate() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	//��ת�������öԻ���
	RotateDlg dlgPara;
	if(dlgPara.DoModal()==IDOK){
		//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
		GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
			pDib->m_lpColorTable, pDib->m_pImgData);
		
		//����Rotate��������ͼ����ת�����ǶȺͲ�ֵ��ʽ������������
		geoTrans.Rotate(dlgPara.m_RotateAngle);
		
		//�½���ͼ���ڣ���ʾ������
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo1Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->m_dib;
		dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
			geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}


void CDemo1View::OnBinary() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//�쳣�ж�
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
		return ;
	}
	
	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	//����GrayTrans��Ķ���graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//����Binary()��ͼ����ж�ֵ����ȱʡ״̬����ֵΪ
	graytrans.BinaryImage();
	
	//����һ������ͼ����ʾ�ָ���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	pView->OnInitialUpdate();	
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

void CDemo1View::OnHistogramDraw() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//�쳣�ж�
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//ֱ��ͼ���ƶԻ���
	HistogramDrawDlg dlgHist;
	dlgHist.m_himageDib.ReplaceDib(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ʾֱ��ͼ
   dlgHist.DoModal();
}


void CDemo1View::OnHistgramAver() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	HistogramDrawDlg histodrawdlg1; 
	histodrawdlg1.m_himageDib.ReplaceDib(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);

	//ֱ��ͼ����
	histodrawdlg1.histogramAve();
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(histodrawdlg1.GetDimensions(),histodrawdlg1.m_nBitCountOut,histodrawdlg1.m_lpColorTableOut, histodrawdlg1.m_pImgDataOut);
	pView->OnInitialUpdate();	
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

void CDemo1View::OnImageReverse() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ���ָ��
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//DIB�����ж�
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
		return ;
	}
	
	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	//����GrayTrans��Ķ���graytrans
	GrayTrans graytrans(pDib->GetDimensions(),
		pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);
	
	//����ReverseImg()��ͼ����
	graytrans.RevImage();
	
	//����һ������ͼ����ʾ�ָ���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

void CDemo1View::OnImgThresh() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//��ֵ�ָ�Ի��������threshsetdlg
	ThreshStrechDlg threshsetdlg;
	if(threshsetdlg.DoModal()==IDOK)
	{
		//����Ҷȱ任��Ķ���graytrans��������ǰDIB������Ϊ�������ݴ���graytrans��
		GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
			pDib->m_lpColorTable, pDib->m_pImgData);
		
		//�����û�ѡ�����ֵ�����ö�ֵ�������ָ�ͼ��
		if ((threshsetdlg.m_Thresh>=0)&&(threshsetdlg.m_Thresh<=255)) 	
			graytrans.BinaryImage(threshsetdlg.m_Thresh);
		
        else
		{
			AfxMessageBox("������һ��0-255֮�����ֵ��");
		    return;
		}
			//�½���ͼ����ʾ�ָ���
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo1Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->m_dib;
		dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}

void CDemo1View::OnThresholdWindow() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//��ֵ�ָ�Ի��������threshsetdlg
	StrechWindowDlg  strechwinsetdlg;
	if(strechwinsetdlg.DoModal()==IDOK)
	{
		//����Ҷȱ任��Ķ���graytrans��������ǰDIB������Ϊ�������ݴ���graytrans��
		GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
			pDib->m_lpColorTable, pDib->m_pImgData);
		graytrans.ThresholdWindow(strechwinsetdlg.m_nBottom,strechwinsetdlg.m_nTop);
	  
	   	//�½���ͼ����ʾ�ָ���
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo1Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->m_dib;
		dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}

void CDemo1View::OnLinearStrecth() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//�쳣�ж�
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
		return ;
	}
	
	//��������������öԻ���
	LinearStepParamDlg linesdlgPara;
	if(linesdlgPara.DoModal()==IDOK){
		//��ȡ�û����õ���������ת�۵�
		CPoint point1,point2;
		point1.x=linesdlgPara.m_nX1;
		point1.y=linesdlgPara.m_nY1;
		point2.x =linesdlgPara.m_nX2;
		point2.y=linesdlgPara.m_nY2;
		
		//�жϲ����ĺ�����
		if(point1.x<0||point1.x>255||point2.x<0||point2.x>255
			||point1.y<0||point1.y>255||point2.y<0||point2.y>255
			||point1.x>point2.x){
			::MessageBox(0,"����������",MB_OK,0);
			return;
		}
		
		//����Ҷȱ任�������
		GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
			pDib->m_lpColorTable, pDib->m_pImgData);
		
		//��������
		graytrans.LinearStrech(point1,point2);
		
		//�½�������ʾ
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);		
		CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo1Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->m_dib;	
		dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
		pView->OnInitialUpdate();	
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}

void CDemo1View::OnPepperSaltNoise() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	ImageEnhance imgnoise(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	imgnoise.AddPepperSaltNoise();
	
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgnoise.GetDimensions(),imgnoise.m_nBitCountOut,imgnoise.m_lpColorTable, imgnoise.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}


void CDemo1View::OnGaussNoise() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	ImageEnhance imgnoise(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	imgnoise.AddGaussNoise();
	
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	
	dibNew->ReplaceDib(imgnoise.GetDimensions(),imgnoise.m_nBitCountOut,imgnoise.m_lpColorTable, imgnoise.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}

void CDemo1View::OnChooseMaskSmooth() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	ImageEnhance imgSmooth(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	imgSmooth.ChooseMaskSmooth();
	
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgSmooth.GetDimensions(),imgSmooth.m_nBitCountOut,imgSmooth.m_lpColorTable, imgSmooth.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);

}


void CDemo1View::OnGradeSharp() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	ImageEnhance imgsharp(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	int nThresh=30;
	imgsharp.GradeSharp(nThresh);
	
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	
	dibNew->ReplaceDib(imgsharp.GetDimensions(),imgsharp.m_nBitCountOut,imgsharp.m_lpColorTable, imgsharp.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
	Invalidate();
}

void CDemo1View::OnNeiAveSmooth() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	ImageEnhance imgsmooth(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	NeiAverSmoothDlg dlgparam;
	
	if (dlgparam.DoModal()==IDOK) {
        
		if (dlgparam.m_radiovalue==0||dlgparam.m_radiovalue==1||dlgparam.m_radiovalue==2) {
	
        float Temp1[81];
		int i;
		for (i = 0; i < 81; i++)
		{
			Temp1[i]=1.0;
		}

           imgsmooth.NeiAveTemplate(dlgparam.TempH,dlgparam.TempW,dlgparam.TempCX,
	       dlgparam.TempCY,Temp1,dlgparam.fCoef);
		}
		else if (dlgparam.m_radiovalue=3) {
		   	float Temp[25];
			//��ģ��Ϊƽ��ģ��
			Temp[0]=0.0;
			Temp[1]=1.0;
			Temp[2]=2.0;
			Temp[3]=1.0;
			Temp[4]=0.0;
			
			Temp[5]=1.0;
			Temp[6]=2.0;
			Temp[7]=4.0;
			Temp[8]=2.0;
			Temp[9]=1.0;
			
			Temp[10]=2.0;
			Temp[11]=4.0;
			Temp[12]=8.0;
			Temp[13]=4.0;
			Temp[14]=2.0;
			
			Temp[15]=1.0;
			Temp[16]=2.0;
			Temp[17]=4.0;
			Temp[18]=2.0;
			Temp[19]=1.0;
			
			Temp[20]=0.0;
			Temp[21]=1.0;
			Temp[22]=2.0;
			Temp[23]=1.0;
	        Temp[24]=0.0;
			imgsmooth.NeiAveTemplate(dlgparam.TempH,dlgparam.TempW,dlgparam.TempCX,
	       dlgparam.TempCY,Temp,dlgparam.fCoef); 

		} 
		else
			return;
		
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgsmooth.GetDimensions(),imgsmooth.m_nBitCountOut,imgsmooth.m_lpColorTable, imgsmooth.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
	}
}


void CDemo1View::OnMedianSmooth() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	MedianSmoothDlg dlgparam;
    if (dlgparam.DoModal()==TRUE) {
	
	ImageEnhance imgsmooth(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);

	imgsmooth.MedianSmooth(dlgparam.TempH,dlgparam.TempW,dlgparam.TempCX,dlgparam.TempCY);
	
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgsmooth.GetDimensions(),imgsmooth.m_nBitCountOut,imgsmooth.m_lpColorTable, imgsmooth.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
	Invalidate();
	}
}

void CDemo1View::OnLaplaceSharp() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	ImageEnhance imgsharp(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	int TempH, TempW, TempCX, TempCY;
	float fCoef;
	float Temp[9];
	//��ģ��Ϊƽ��ģ��
	Temp[0]=-1.0;
	Temp[1]=-1.0;
	Temp[2]=-1.0;
	Temp[3]=-1.0;
	Temp[4]=9.0;
	Temp[5]=-1.0;
	Temp[6]=-1.0;
	Temp[7]=-1.0;
	Temp[8]=-1.0;
    //��ʼ���Ի������
	TempH=3;
	TempW=3;
	TempCX=1;
	TempCY=1;
	fCoef=1.0;
    imgsharp.LapTemplate(TempH,TempW,TempCX,TempCY,Temp,fCoef);
	
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgsharp.GetDimensions(),imgsharp.m_nBitCountOut,imgsharp.m_lpColorTable, imgsharp.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}

void CDemo1View::OnQuickFFt() 
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж�ͼ���С�Ƿ�Ϊ2���ݴεķ���
	int isValidateFlag=1;
	int width=pDib->GetDimensions().cx;
	int height=pDib->GetDimensions().cy;
	int i=1;
	while(i<width)
		i=i*2;
	if(i!=width)//ͼ�����2���ݴη�
		isValidateFlag=0;
	
	i=1;
	while(i<height)
		i=i*2;
	if(i!=height)//ͼ��߲���2���ݴη�
		isValidateFlag=0;
	
	if(isValidateFlag==0){
		::MessageBox(0,"����ͼ��Ŀ�͸�ӦΪ2���ݴη�",MB_OK,0);
		return ;
	}
	
	//����ͼ�����ݸ�transform_FFT�����FFTTrans
	fftTrans.InputImgData(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	//���ٸ���Ҷ�任
	fftTrans.Fourier();
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(fftTrans.GetDimensions(),fftTrans.m_nBitCountOut,
		fftTrans.m_lpColorTable, fftTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}


void CDemo1View::OnQuickFFtReverse() 
{
	// TODO: Add your command handler code here
	fftTrans.RevFourier();
    //�½���ͼ���ڣ���ʾͼ��ָ��Ľ��
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(fftTrans.GetDimensions(),fftTrans.m_nBitCountOut,
		fftTrans.m_lpColorTable, fftTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}



void CDemo1View::OnIdealLowPass() 
{
	// TODO: Add your command handler code here
    CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж�ͼ���С�Ƿ�Ϊ2���ݴεķ���
	int isValidateFlag=1;
	int width=pDib->GetDimensions().cx;
	int height=pDib->GetDimensions().cy;
	int i=1;
	while(i<width)
		i=i*2;
	if(i!=width)//ͼ�����2���ݴη�
		isValidateFlag=0;
	
	i=1;
	while(i<height)
		i=i*2;
	if(i!=height)//ͼ��߲���2���ݴη�
		isValidateFlag=0;
	
	if(isValidateFlag==0){
		::MessageBox(0,"����ͼ��Ŀ�͸�ӦΪ2���ݴη�",MB_OK,0);
		return ;
	}
	
	//����ͼ�����ݸ�ImageFreqEnhance�����imgfreq;
	ImageFreqEnhance imgfreq;
	imgfreq.InputImageData(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	//ͼ�������ͨ�˲�
	imgfreq.IdealLowPassFilter(pDib->m_imgWidth,pDib->m_imgHeight,pDib->m_imgHeight/16);
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgfreq.GetDimensions(),imgfreq.m_nBitCountOut,
		imgfreq.m_lpColorTable, imgfreq.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
	
}

void CDemo1View::OnButterLowPass() 
{
	// TODO: Add your command handler code here
    CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж�ͼ���С�Ƿ�Ϊ2���ݴεķ���
	int isValidateFlag=1;
	int width=pDib->GetDimensions().cx;
	int height=pDib->GetDimensions().cy;
	int i=1;
	while(i<width)
		i=i*2;
	if(i!=width)//ͼ�����2���ݴη�
		isValidateFlag=0;
	
	i=1;
	while(i<height)
		i=i*2;
	if(i!=height)//ͼ��߲���2���ݴη�
		isValidateFlag=0;
	
	if(isValidateFlag==0){
		::MessageBox(0,"����ͼ��Ŀ�͸�ӦΪ2���ݴη�",MB_OK,0);
		return ;
	}
	
	//����ͼ�����ݸ�ImageFreqEnhance�����imgfreq;
	ImageFreqEnhance imgfreq;
	imgfreq.InputImageData(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	//ͼ�������ͨ�˲�
	imgfreq.ButterLowPassFilter(pDib->m_imgWidth,pDib->m_imgHeight,pDib->m_imgHeight/16);
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgfreq.GetDimensions(),imgfreq.m_nBitCountOut,
		imgfreq.m_lpColorTable, imgfreq.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();	
}

void CDemo1View::OnIdealHighPass() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж�ͼ���С�Ƿ�Ϊ2���ݴεķ���
	int isValidateFlag=1;
	int width=pDib->GetDimensions().cx;
	int height=pDib->GetDimensions().cy;
	int i=1;
	while(i<width)
		i=i*2;
	if(i!=width)//ͼ�����2���ݴη�
		isValidateFlag=0;
	
	i=1;
	while(i<height)
		i=i*2;
	if(i!=height)//ͼ��߲���2���ݴη�
		isValidateFlag=0;
	
	if(isValidateFlag==0){
		::MessageBox(0,"����ͼ��Ŀ�͸�ӦΪ2���ݴη�",MB_OK,0);
		return ;
	}
	
	//����ͼ�����ݸ�ImageFreqEnhance�����imgfreq;
	ImageFreqEnhance imgfreq;
	imgfreq.InputImageData(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	//ͼ�������ͨ�˲�
	imgfreq.IdealHighPassFilter(pDib->m_imgWidth,pDib->m_imgHeight,pDib->m_imgHeight/16);
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgfreq.GetDimensions(),imgfreq.m_nBitCountOut,
		imgfreq.m_lpColorTable, imgfreq.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();	
}

void CDemo1View::OnButterHighPass() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж�ͼ���С�Ƿ�Ϊ2���ݴεķ���
	int isValidateFlag=1;
	int width=pDib->GetDimensions().cx;
	int height=pDib->GetDimensions().cy;
	int i=1;
	while(i<width)
		i=i*2;
	if(i!=width)//ͼ�����2���ݴη�
		isValidateFlag=0;
	
	i=1;
	while(i<height)
		i=i*2;
	if(i!=height)//ͼ��߲���2���ݴη�
		isValidateFlag=0;
	
	if(isValidateFlag==0){
		::MessageBox(0,"����ͼ��Ŀ�͸�ӦΪ2���ݴη�",MB_OK,0);
		return ;
	}
	
	//����ͼ�����ݸ�ImageFreqEnhance�����imgfreq;
	ImageFreqEnhance imgfreq;
	imgfreq.InputImageData(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	//ͼ�������ͨ�˲�
	imgfreq.ButterHighPassFilter(pDib->m_imgWidth,pDib->m_imgHeight,pDib->m_imgHeight/16);
	
	//�½���ͼ���ڣ���ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(imgfreq.GetDimensions(),imgfreq.m_nBitCountOut,
		imgfreq.m_lpColorTable, imgfreq.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();	
}

void CDemo1View::OnHarrWaveletTrans() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	wavltTrans.InputImageData(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
    wavltTrans.BasicWaveletTrans(2);
	
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(wavltTrans.GetDimensions(),wavltTrans.m_nBitCountOut,wavltTrans.m_pColorTableOut,wavltTrans.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();	
}

void CDemo1View::OnHarrWavRevTrans() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
    wavltTrans.BasicWaveletReverse();
	
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(wavltTrans.GetDimensions(),wavltTrans.m_nBitCountOut,wavltTrans.m_pColorTableOut,wavltTrans.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}

void CDemo1View::OnErosion() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;

	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}

	//����Morphology��Ķ���mortrans���õ�ǰDIB�����ʼ��
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
   
	//����ṹԪ��ģ�壬Ĭ��Ϊ3*3ģ��
/*
    int i;
	for (i=0;i<TempH*TempW;i++) {
		m_InitTemp[i]=0;
	}	
*/
	//ģ��1
	morTrans.m_InitTemp[1]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[5]=1;
	morTrans.m_InitTemp[7]=1;
	
/*	//ģ��2
	morTrans.m_InitTemp[0]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[6]=1;
	morTrans.m_InitTemp[7]=1;
	morTrans.m_InitTemp[8]=1;
	*/

	if(morTrans.m_TempBuf){
		delete []morTrans.m_TempBuf;
		morTrans.m_TempBuf=NULL;
	}

	//������ĽṹԪ�ؿ�����m_TempBuf��������
	morTrans.m_TempBuf=new int[morTrans.TempW*morTrans.TempH];
	int i0, j0;
	for(i0=0;i0<morTrans.TempH;i0++){
		for(j0=0;j0<morTrans.TempW;j0++){
			morTrans.m_TempBuf[i0*morTrans.TempW+j0]=morTrans.m_InitTemp[i0*morTrans.TempW+j0];
		}
	}
	
	morTrans.ImgErosion(morTrans.m_pImgData,morTrans.m_pImgDataOut,morTrans.m_imgWidth,morTrans.m_imgHeight,
		morTrans.m_TempBuf, morTrans.TempW, morTrans.TempH);
/*	*/
	//��ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}

void CDemo1View::OnDilation() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;

	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}

	//����Morphology��Ķ���mortrans���õ�ǰDIB�����ʼ��
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
   
	//����ṹԪ��ģ�壬Ĭ��Ϊ3*3ģ��
/*
    int i;
	for (i=0;i<TempH*TempW;i++) {
		m_InitTemp[i]=0;
	}	
*/
	//ģ��1
	morTrans.m_InitTemp[1]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[5]=1;
	morTrans.m_InitTemp[7]=1;
	
/*	//ģ��2
	morTrans.m_InitTemp[0]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[6]=1;
	morTrans.m_InitTemp[7]=1;
	morTrans.m_InitTemp[8]=1;
	*/

	if(morTrans.m_TempBuf){
		delete []morTrans.m_TempBuf;
		morTrans.m_TempBuf=NULL;
	}

	//������ĽṹԪ�ؿ�����m_TempBuf��������
	morTrans.m_TempBuf=new int[morTrans.TempW*morTrans.TempH];
	int i0, j0;
	for(i0=0;i0<morTrans.TempH;i0++){
		for(j0=0;j0<morTrans.TempW;j0++){
			morTrans.m_TempBuf[i0*morTrans.TempW+j0]=morTrans.m_InitTemp[i0*morTrans.TempW+j0];
		}
	}
	
	morTrans.ImgDilation(morTrans.m_pImgData,morTrans.m_pImgDataOut,morTrans.m_imgWidth,morTrans.m_imgHeight,
		morTrans.m_TempBuf, morTrans.TempW, morTrans.TempH);
/*	*/
	//��ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();	
}

void CDemo1View::OnOpen() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;

	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}

	//����Morphology��Ķ���mortrans���õ�ǰDIB�����ʼ��
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
   
	//����ṹԪ��ģ�壬Ĭ��Ϊ3*3ģ��
/*
    int i;
	for (i=0;i<TempH*TempW;i++) {
		m_InitTemp[i]=0;
	}	
*/
	//ģ��1
	morTrans.m_InitTemp[1]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[5]=1;
	morTrans.m_InitTemp[7]=1;
	
/*	//ģ��2
	morTrans.m_InitTemp[0]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[6]=1;
	morTrans.m_InitTemp[7]=1;
	morTrans.m_InitTemp[8]=1;
	*/

	if(morTrans.m_TempBuf){
		delete []morTrans.m_TempBuf;
		morTrans.m_TempBuf=NULL;
	}

	//������ĽṹԪ�ؿ�����m_TempBuf��������
	morTrans.m_TempBuf=new int[morTrans.TempW*morTrans.TempH];
	int i0, j0;
	for(i0=0;i0<morTrans.TempH;i0++){
		for(j0=0;j0<morTrans.TempW;j0++){
			morTrans.m_TempBuf[i0*morTrans.TempW+j0]=morTrans.m_InitTemp[i0*morTrans.TempW+j0];
		}
	}
	
	morTrans.Open();
	
	/*	*/
	//��ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}

void CDemo1View::OnClose() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;

	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}

	//����Morphology��Ķ���mortrans���õ�ǰDIB�����ʼ��
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
   
	//����ṹԪ��ģ�壬Ĭ��Ϊ3*3ģ��
/*
    int i;
	for (i=0;i<TempH*TempW;i++) {
		m_InitTemp[i]=0;
	}	
*/
	//ģ��1
	morTrans.m_InitTemp[1]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[5]=1;
	morTrans.m_InitTemp[7]=1;
	
/*	//ģ��2
	morTrans.m_InitTemp[0]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[6]=1;
	morTrans.m_InitTemp[7]=1;
	morTrans.m_InitTemp[8]=1;
	*/

	if(morTrans.m_TempBuf){
		delete []morTrans.m_TempBuf;
		morTrans.m_TempBuf=NULL;
	}

	//������ĽṹԪ�ؿ�����m_TempBuf��������
	morTrans.m_TempBuf=new int[morTrans.TempW*morTrans.TempH];
	int i0, j0;
	for(i0=0;i0<morTrans.TempH;i0++){
		for(j0=0;j0<morTrans.TempW;j0++){
			morTrans.m_TempBuf[i0*morTrans.TempW+j0]=morTrans.m_InitTemp[i0*morTrans.TempW+j0];
		}
	}
	
	morTrans.Close();
	
	/*	*/
	//��ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();	
}


void CDemo1View::OnThinning() 
{
	// TODO: Add your command handler code here
	CDemo1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}
	
	//����Morphology��Ķ���mortrans���õ�ǰDIB�����ʼ��
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
    morTrans.ImgThinning();

	/*	*/
	//��ʾ�任���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo1View* pView=(CDemo1View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}







