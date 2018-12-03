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
	Invalidate();
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
	Invalidate();
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
	Invalidate();
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
		Invalidate();
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
	Invalidate();
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
	Invalidate();
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
	Invalidate();
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
		Invalidate();
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
		Invalidate();
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
		Invalidate();
	}
}
