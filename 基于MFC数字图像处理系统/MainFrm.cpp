// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//
// MainFrm.cpp : implementation of the CMainFrame class
//
#pragma once

#include "stdafx.h"
#include "MSMoneyDemo.h"
#include "MSMoneyDemoDoc.h"

#include "MainFrm.h"
#include "MSMVisualManager.h"
#include "MSMLinksBarButton.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(AFX_WM_TOOLBARMENU, OnToolbarContextMenu)
	ON_UPDATE_COMMAND_UI(ID_GO_ADDRESS_EDIT, OnUpdateGoAddressEdit)
	ON_UPDATE_COMMAND_UI(ID_BACKWARD_1, OnUpdateBackward1)
	ON_UPDATE_COMMAND_UI(ID_BACKWARD_2, OnUpdateBackward2)
	ON_UPDATE_COMMAND_UI(ID_FORWARD_1, OnUpdateForward1)
	ON_UPDATE_COMMAND_UI(ID_FORWARD_2, OnUpdateForward2)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_CUSTOMIZE, OnUpdateCustomize)

	ON_COMMAND_RANGE(ID_CATEGORIE_1, ID_CATEGORIE_14, OnCategorie)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CATEGORIE_1, ID_CATEGORIE_14, OnUpdateCategorie)
	ON_COMMAND_RANGE(ID_File_OPEN, id_ObjectTrace, OnLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_File_OPEN, id_ObjectTrace, OnUpdateLinks)

	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_APP_HELP_MICROSOFT, OnHelpMicrosoft)
	ON_COMMAND(ID_HELP_MICROSOFT, OnHelpMicrosoft)
	ON_WM_SETTINGCHANGE()
//	ON_WM_MOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bMainToolbarMenu = FALSE;
	m_nCategorie       = (UINT)-1;
	m_SoleProcView = NULL;
	m_OriginView = NULL;
	m_OutputView = NULL;
}

CMainFrame::~CMainFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::SetupMemoryBitmapSize(const CSize& sz)
{
	CMSMVisualManager* pManager = DYNAMIC_DOWNCAST(CMSMVisualManager,
		CMFCVisualManager::GetInstance());

	if (pManager != NULL)
	{
		CRect rtRes(0, 0, sz.cx, 0);

		CRect rt;

		CPane* bars[4] =
		{ &m_wndCaptionBar, &m_wndMenuBar, &m_wndToolBar, &m_wndCategoryBar };

		for (long i = 0; i < 4; i++)
		{
			CPane* pBar = bars[i];

			if (pBar != NULL && pBar->GetSafeHwnd() != NULL)
			{
				pBar->GetWindowRect(rt);
				rtRes.bottom += rt.Height();
			}
		}

		CDC* pDC = GetDC();

		pManager->SetupMemoryBitmapSize(pDC, rtRes.Size());

		ReleaseDC(pDC);
	}
}

// ��������ͼ�ָ��
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	CRect rect;
	GetClientRect(&rect);  //��ȡ�ͻ�������(���� ����)  
	int nRcWidth = rect.Width();
	int nRcHeight = rect.Height();
	if (!m_wndSplitter1.CreateStatic(this, 1, 2))
		return FALSE;      //������̬�ָ������� 1��*2��	 

	 //�ָ�ĵ�һ�е�һ��ָ����̬��������OriginView  
	//ָ�����ڿ����1/4������,�߶�Ϊ��������߶� 
	if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(OriginView), CSize(nRcWidth / 3, nRcHeight), pContext))
		return FALSE;      //����λ��(0,0)  
	m_OriginView = (OriginView*)m_wndSplitter1.GetPane(0, 0);

	//��m_wndSplitter1�ָ�ĵڶ���������ʹ��m_wndSplitter2���зָ�ָ��2*1������  
	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter1, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter1.IdFromRowCol(0, 1))) 
		return FALSE;

	if (!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CMSMoneyDemoView), CSize(nRcWidth / 3*2, nRcHeight / 2), pContext))
		return FALSE;      //����λ��(0,1)  
	m_SoleProcView = (CMSMoneyDemoView*)m_wndSplitter2.GetPane(0, 0);

	if (!m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(OutputView), CSize(nRcWidth / 3*2, nRcHeight / 2), pContext))
		return FALSE;      //����λ��(1,1)  
	m_OutputView = (OutputView*)m_wndSplitter2.GetPane(1, 0);

	SetActiveView((CMSMoneyDemoView*)m_wndSplitter2.GetPane(0, 0));
	return TRUE;

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

// ��������������Ϊÿ����������ť��ID
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle (WS_CAPTION | FWS_ADDTOTITLE, 0);
	ModifyStyleEx (WS_EX_CLIENTEDGE, 0);
	CMFCVisualManager::SetDefaultManager (RUNTIME_CLASS (CMSMVisualManager));

	//---------------------------------
	// Set toolbar and menu image size:
	//---------------------------------
	CMFCToolBarButton::m_bWrapText = FALSE;
	CMFCToolBar::SetMenuSizes (CSize (42, 42), CSize (16, 16));
	CMFCToolBarComboBoxButton::SetFlatMode ();
	CMFCToolBarComboBoxButton::SetCenterVert ();

	if (!m_wndCaptionBar.Create(this, IDR_MAINFRAME))
	{
		TRACE0("Failed to create captionbar\n");
		return -1;
	}

	if (afxGlobalData.fontRegular.GetSafeHandle () != NULL)
	{
		LOGFONT lf;
		ZeroMemory (&lf, sizeof (LOGFONT));
		afxGlobalData.fontRegular.GetLogFont (&lf);
		m_wndCaptionBar.SetCaptionFont (lf);
	}

	if (!m_wndMenuBar.Create (this, AFX_DEFAULT_TOOLBAR_STYLE))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}


	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	CClientDC dc (this);
	m_bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 16;

	UINT uiToolbarHotID  = m_bIsHighColor ? IDB_HOTTOOLBAR : 0;
	UINT uiToolbarColdID = m_bIsHighColor ? IDB_COLDTOOLBAR : 0;
	UINT uiToolbarDisID  = m_bIsHighColor ? IDB_DISABLEDTOOLBAR : 0;
	UINT uiToolbarPresID = m_bIsHighColor ? IDB_PRESSEDTOOLBAR : 0;
	UINT uiMenuID        = m_bIsHighColor ? IDB_MENU_IMAGES : IDB_MENU_IMAGES_16;

	if (!m_wndToolBar.CreateEx (this, TBSTYLE_FLAT,
		                        CBRS_SIZE_FIXED | AFX_DEFAULT_TOOLBAR_STYLE) ||
		!m_wndToolBar.LoadToolBar (IDR_MAINFRAME, uiToolbarColdID, uiMenuID, 
			FALSE /* Not locked */, uiToolbarDisID, 0, uiToolbarHotID, uiToolbarPresID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.InsertButton 
		(CMFCToolBarComboBoxButton (ID_GO_ADDRESS_EDIT, 0), 3);
	DockPane (&m_wndToolBar);


	if (!m_wndCategoryBar.CreateEx (this, TBSTYLE_FLAT, 
		                      CBRS_SIZE_FIXED | AFX_DEFAULT_TOOLBAR_STYLE, 
							  CRect (1, 1, 1, 1), AFX_IDW_TOOLBAR + 3))
	{
		TRACE0("Failed to create categoriebar\n");
		return -1;      // fail to create
	}

	DockPane (&m_wndCategoryBar);
	//m_wndCategoryBar.SetSizes(CSize(24, 24), CSize(16, 16));
	
	for (long i = 0; i < 14; i++)
	{
		if (!m_wndLinksBars[i].CreateEx (this, TBSTYLE_FLAT, 
								  CBRS_SIZE_FIXED | AFX_DEFAULT_TOOLBAR_STYLE, 
								  CRect (1, 1, 1, 1), AFX_IDW_TOOLBAR + 4 + i))
		{
			TRACE0("Failed to create linksbar\n");
			return -1;      // fail to create
		}

		DockPane (&m_wndLinksBars[i]);
		ShowPane (&m_wndLinksBars[i], FALSE, FALSE, FALSE);
		//m_wndLinksBars[i].SetSizes(CSize(24, 24), CSize(16, 16));
	}

	// �ļ�
	m_wndLinksBars[0].InsertButton (CMSMLinksBarButton (_T("��"), ID_File_OPEN));
	m_wndLinksBars[0].InsertButton (CMSMLinksBarButton (_T("����"), ID_LINKS_SAVE));
	m_wndLinksBars[0].InsertButton(CMSMLinksBarButton(_T("��ӡ"), ID_LINKS_PRINT));
	m_wndLinksBars[0].InsertButton(CMSMLinksBarButton(_T("�ر�"), ID_LINKS_EXIT));
	m_wndLinksBars[0].SetCurrentCommand (ID_File_OPEN);
	// ���α任
	m_wndLinksBars[1].InsertButton (CMSMLinksBarButton (_T("ƽ��"), ID_LINKS_Move));
	m_wndLinksBars[1].InsertButton (CMSMLinksBarButton (_T("ˮƽ����"), ID_LINKS_HorizontalMirror));
	m_wndLinksBars[1].InsertButton (CMSMLinksBarButton (_T("��ֱ����"), ID_LINKS_verticalMirror));
	m_wndLinksBars[1].InsertButton (CMSMLinksBarButton (_T("����"), ID_LINKS_Zoom));
	m_wndLinksBars[1].InsertButton (CMSMLinksBarButton (_T("˳ʱ����ת90��"), ID_LINKS_Clockwise90));
	m_wndLinksBars[1].InsertButton(CMSMLinksBarButton(_T("��ʱ����ת90��"), ID_LINKS_Anticlockwise90));
	m_wndLinksBars[1].InsertButton(CMSMLinksBarButton(_T("��ת180��"), ID_LINKS_Rotate180));
	m_wndLinksBars[1].InsertButton(CMSMLinksBarButton(_T("����Ƕ���ת"), ID_LINKS_FreeRotate));
	m_wndLinksBars[1].SetCurrentCommand (ID_LINKS_Move);
	// �Ҷȱ任
	m_wndLinksBars[2].InsertButton (CMSMLinksBarButton (_T("��ֵ��"), ID_Binary));
	m_wndLinksBars[2].InsertButton(CMSMLinksBarButton(_T("��ֵ��"), id_ColorToGray));
	m_wndLinksBars[2].InsertButton (CMSMLinksBarButton (_T("ֱ��ͼ"), ID_HistogramDraw));
	m_wndLinksBars[2].InsertButton (CMSMLinksBarButton (_T("ֱ��ͼ����"), ID_HistgramAver));
	m_wndLinksBars[2].InsertButton (CMSMLinksBarButton (_T("��ת"), ID_ImageReverse));
	m_wndLinksBars[2].InsertButton (CMSMLinksBarButton (_T("��ֵ�任"), ID_ImgThresh));
	m_wndLinksBars[2].InsertButton(CMSMLinksBarButton(_T("���ڱ任"), ID_ThresholdWindow));
	m_wndLinksBars[2].InsertButton(CMSMLinksBarButton(_T("�ֶ���������"), ID_LinearStrecth));
	m_wndLinksBars[2].SetCurrentCommand (ID_Binary);
	// ͼ�������ǿ
	m_wndLinksBars[3].InsertButton (CMSMLinksBarButton (_T("��˹����"), ID_LINKS_GaussNoise));
	m_wndLinksBars[3].InsertButton (CMSMLinksBarButton (_T("��������"), ID_LINKS_PeppersaltNoise));
	m_wndLinksBars[3].InsertButton (CMSMLinksBarButton (_T("����ƽ��"), ID_LINKS_NeiAveSmooth));
	m_wndLinksBars[3].InsertButton(CMSMLinksBarButton(_T("��ֵƽ��"), ID_LINKS_MedianSmooth));
	m_wndLinksBars[3].InsertButton(CMSMLinksBarButton(_T("��ģƽ��"), ID_LINKS_ChooseMaskSmooth));
	m_wndLinksBars[3].InsertButton(CMSMLinksBarButton(_T("�ݶ���"), ID_LINKS_GradeSharp));
	m_wndLinksBars[3].InsertButton(CMSMLinksBarButton(_T("������˹��"), ID_LINKS_LaplaceSharp));
	m_wndLinksBars[3].SetCurrentCommand (ID_LINKS_GaussNoise);
	// ͼ��Ƶ����ǿ
	m_wndLinksBars[4].InsertButton (CMSMLinksBarButton (_T("���ٸ���Ҷ�任"), ID_LINKS_QuickFFT));
	m_wndLinksBars[4].InsertButton (CMSMLinksBarButton (_T("���ٸ���Ҷ���任"), ID_LINKS_QuickFFT_Reverse));
	m_wndLinksBars[4].InsertButton(CMSMLinksBarButton(_T("�����ͨ�˲�"), ID_LINKS_IdealLowPass));
	m_wndLinksBars[4].InsertButton(CMSMLinksBarButton(_T("�����ͨ�˲�"), ID_LINKS_IdealHighPass));
	m_wndLinksBars[4].InsertButton(CMSMLinksBarButton(_T("������˹��ͨ�˲�"), ID_LINKS_ButterLowPass));
	m_wndLinksBars[4].InsertButton(CMSMLinksBarButton(_T("������˹��ͨ�˲�"), ID_LINKS_ButterHighPass));
	m_wndLinksBars[4].InsertButton(CMSMLinksBarButton(_T("С���任"), ID_LINKS_HarrWaveletTrans));
	m_wndLinksBars[4].InsertButton(CMSMLinksBarButton(_T("С�����任"), ID_LINKS_HarrWaveletTrans_Reverse));
	m_wndLinksBars[4].SetCurrentCommand (ID_LINKS_QuickFFT);
	// ͼ����̬ѧ
	m_wndLinksBars[5].InsertButton (CMSMLinksBarButton (_T("��ֵ��ʴ"), ID_LINKS_Erosion));
	m_wndLinksBars[5].InsertButton (CMSMLinksBarButton (_T("��ֵ����"), ID_LINKS_Dilation));
	m_wndLinksBars[5].InsertButton (CMSMLinksBarButton (_T("��ֵ��"), ID_LINKS_Open));
	m_wndLinksBars[5].InsertButton (CMSMLinksBarButton (_T("��ֵ��"), ID_LINKS_Close));
	//m_wndLinksBars[5].InsertButton (CMSMLinksBarButton (_T("��ֵ�ڱ߽�"), ID_LINKS_INVESTING_5));
	//m_wndLinksBars[5].InsertButton (CMSMLinksBarButton (_T("��ֵ��߽�"), ID_LINKS_INVESTING_6)); 
	//m_wndLinksBars[5].InsertButton(CMSMLinksBarButton(_T("��ֵ��̬ѧ�߽�"), ID_LINKS_INVESTING_1));
	m_wndLinksBars[5].InsertButton(CMSMLinksBarButton(_T("���л�����ϸ��"), ID_LINKS_Thinning));
	m_wndLinksBars[5].InsertButton(CMSMLinksBarButton(_T("������ϸ��"), ID_LINKS_HitMissThinning));
	m_wndLinksBars[5].InsertButton(CMSMLinksBarButton(_T("��ֵ��ʴ"), ID_LINKS_GrayErosion));
	m_wndLinksBars[5].InsertButton(CMSMLinksBarButton(_T("��ֵ����"), ID_LINKS_GrayDilation));
	m_wndLinksBars[5].InsertButton(CMSMLinksBarButton(_T("��ֵ��"), ID_LINKS_GrayOpen));
	m_wndLinksBars[5].InsertButton(CMSMLinksBarButton(_T("��ֵ��"), ID_LINKS_GrayClose));
	m_wndLinksBars[5].SetCurrentCommand (ID_LINKS_Erosion);
	// ͼ��ָ�
	m_wndLinksBars[6].InsertButton (CMSMLinksBarButton (_T("ֱ��ͼ��ֵ�ָ�"), ID_LINKS_HistThreshSeg));
	m_wndLinksBars[6].InsertButton (CMSMLinksBarButton (_T("����Ӧ��ֵ�ָ�"), ID_LINKS_AdaptiveThreshold));
	m_wndLinksBars[6].InsertButton (CMSMLinksBarButton (_T("Robert����"), ID_LINKS_Robert));
	m_wndLinksBars[6].InsertButton (CMSMLinksBarButton (_T("Sobel����"), ID_LINKS_Sobel));
	m_wndLinksBars[6].InsertButton (CMSMLinksBarButton (_T("Prewitt����"), ID_LINKS_Prewitt));
	m_wndLinksBars[6].InsertButton (CMSMLinksBarButton (_T("Laplacian����"), ID_LINKS_Laplacian));
	m_wndLinksBars[6].InsertButton(CMSMLinksBarButton(_T("�߽����"), ID_LINKS_EdgeTrace));
	m_wndLinksBars[6].InsertButton(CMSMLinksBarButton(_T("��������"), ID_LINKS_RegionGrow));
	m_wndLinksBars[6].SetCurrentCommand (ID_LINKS_HistThreshSeg);
	// �������
	m_wndLinksBars[7].InsertButton (CMSMLinksBarButton (_T("���ƶȼ���"), id_similardegree));
	m_wndLinksBars[7].InsertButton (CMSMLinksBarButton (_T("������ȡ"), id_boundary));
	m_wndLinksBars[7].InsertButton (CMSMLinksBarButton (_T("������λ"), id_facelocate));
	m_wndLinksBars[7].InsertButton (CMSMLinksBarButton (_T("����������ȡ"), id_innerboundary));
	m_wndLinksBars[7].InsertButton (CMSMLinksBarButton (_T("�۾���λ"), id_eyelocate));
	m_wndLinksBars[7].InsertButton(CMSMLinksBarButton(_T("���Ӷ�λ"), id_noselocate));
	m_wndLinksBars[7].InsertButton(CMSMLinksBarButton(_T("�춨λ"), id_mouthlocate));
	m_wndLinksBars[7].SetCurrentCommand (id_similardegree);
	// ����ʶ��
	m_wndLinksBars[8].InsertButton(CMSMLinksBarButton(_T("�Ҷ�ת��"), id_ColorToGray));
	m_wndLinksBars[8].InsertButton(CMSMLinksBarButton(_T("Prewitt����"), ID_LINKS_Prewitt));
	m_wndLinksBars[8].InsertButton(CMSMLinksBarButton(_T("��ֵ������"), ID_Binary2));
	m_wndLinksBars[8].InsertButton(CMSMLinksBarButton(_T("��ɫ�������"), id_ColorPair));
	m_wndLinksBars[8].InsertButton(CMSMLinksBarButton(_T("���ƶ�λ"), id_platelocate));
	m_wndLinksBars[8].InsertButton(CMSMLinksBarButton(_T("�����ٶ�λ"), id_platerelocate));
	m_wndLinksBars[8].InsertButton(CMSMLinksBarButton(_T("�ַ��ָ�"), id_charseparate));
	m_wndLinksBars[8].InsertButton(CMSMLinksBarButton(_T("�ַ�ʶ��"), id_charrecognition));
	m_wndLinksBars[8].SetCurrentCommand(id_ColorToGray);

	// ӡˢ�庺��ʶ��
	m_wndLinksBars[9].InsertButton(CMSMLinksBarButton(_T("����Ԥ����"), id_PaperBinary));
	m_wndLinksBars[9].InsertButton(CMSMLinksBarButton(_T("���ֶ�λ"), id_location));
	m_wndLinksBars[9].InsertButton(CMSMLinksBarButton(_T("����ʶ��"), id_recognition));
	m_wndLinksBars[9].SetCurrentCommand(id_PaperBinary);

	// �˶�ͼ�����
	m_wndLinksBars[10].InsertButton(CMSMLinksBarButton(_T("����Ƶ�ļ�"), id_AVIOpen));
	m_wndLinksBars[10].InsertButton(CMSMLinksBarButton(_T("Ŀ����"), id_ObjectDetect));
	m_wndLinksBars[10].InsertButton(CMSMLinksBarButton(_T("Ŀ�����"), id_ObjectTrace));
	m_wndLinksBars[10].SetCurrentCommand(id_AVIOpen);

	//-----------------------
	// Set up Favorites menu:
	//-----------------------
	int nCategorie = theApp.GetProfileInt (_T(""), _T("Categorie"), 0);
	OnCategorie (ID_CATEGORIE_1 + nCategorie);

	m_wndTaskPane.Create (_T(""), this, CRect (0, 0, 140, 200), 
		FALSE, IDR_MAINFRAME + 1, 
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT, 0, 0);

	DockPane(&m_wndTaskPane);

	return 0;
}


CMSMLinksBar* CMainFrame::GetLinksBar(UINT nID)
{
	CMSMLinksBar* pBar = NULL;

	if (ID_File_OPEN <= nID && nID <= ID_LINKS_EXIT)
	{
		pBar = &m_wndLinksBars[0];
	}
	else if (ID_LINKS_Move <= nID && nID <= ID_LINKS_FreeRotate)
	{
		pBar = &m_wndLinksBars[1];
	}
	else if (ID_Binary <= nID && nID <= ID_LinearStrecth)
	{
		pBar = &m_wndLinksBars[2];
	}
	else if (ID_LINKS_GaussNoise <= nID && nID <= ID_LINKS_LaplaceSharp)
	{
		pBar = &m_wndLinksBars[3];
	}
	else if (ID_LINKS_QuickFFT <= nID && nID <= ID_LINKS_HarrWaveletTrans_Reverse)
	{
		pBar = &m_wndLinksBars[4];
	}
	else if (ID_LINKS_Erosion <= nID && nID <= ID_LINKS_GrayClose)
	{
		pBar = &m_wndLinksBars[5];
	}
	else if (ID_LINKS_HistThreshSeg <= nID && nID <= ID_LINKS_RegionGrow)
	{
		pBar = &m_wndLinksBars[6];
	}
	else if (id_similardegree <= nID && nID <= id_mouthlocate)
	{
		pBar = &m_wndLinksBars[7];
	}
	else if (id_ColorToGray <= nID && nID <= id_charrecognition)
	{
		pBar = &m_wndLinksBars[8];
	}

	else if (id_PaperBinary <= nID && nID <= id_recognition)
	{
		pBar = &m_wndLinksBars[9];
	}

	else if (id_AVIOpen <= nID && nID <= id_ObjectTrace)
	{
		pBar = &m_wndLinksBars[10];
	}
	else
	{
		ASSERT(FALSE);
	}

	return pBar;
}


void CMainFrame::OnClose() 
{
	theApp.WriteProfileInt (_T(""), _T("Categorie"), m_nCategorie);
	
	CFrameWnd::OnClose();
}


void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	if (m_wndCaptionBar.GetSafeHwnd () != NULL)
	{
		m_wndCaptionBar.SetParentActive (nState != WA_INACTIVE);
	}
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	SetupMemoryBitmapSize (CSize (cx, cy));

	if (m_wndCaptionBar.GetSafeHwnd () != NULL)
	{
		m_wndCaptionBar.SetParentMaximize (nType == SIZE_MAXIMIZED);
	}

	CFrameWnd::OnSize(nType, cx, cy);
}

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM /*wp*/,LPARAM /*lp*/)
{
	return 0;
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wp, LPARAM)
{
	UINT uiToolBarId = (UINT) wp;
	if (uiToolBarId == IDR_MAINFRAME)
	{
		// Replace "Back" and "Forward" buttons by the menu buttons
		// with the history lists:

		CMenu menuBackward;
		menuBackward.LoadMenu (IDR_BACKWARD_MENU);

		m_wndToolBar.ReplaceButton (ID_GO_BACK, 
			CMFCToolBarMenuButton (ID_GO_BACK, menuBackward, 
						GetCmdMgr ()->GetCmdImage (ID_GO_BACK), NULL));

		CMenu menuForward;
		menuForward.LoadMenu (IDR_FORWARD_MENU);

		m_wndToolBar.ReplaceButton (ID_GO_FORWARD,
			CMFCToolBarMenuButton (ID_GO_FORWARD, menuForward, 
						GetCmdMgr ()->GetCmdImage (ID_GO_FORWARD), NULL));
	}

	return 0;
}

BOOL CMainFrame::OnShowPopupMenu (CMFCPopupMenu* pMenuPopup)
{
	CFrameWndEx::OnShowPopupMenu (pMenuPopup);

	if (pMenuPopup == NULL)
	{
		return TRUE;
	}

	CMFCToolBarMenuButton* pParentButton = pMenuPopup->GetParentButton ();
	if (pParentButton == NULL)
	{
		return TRUE;
	}

	switch (pParentButton->m_nID)
	{
	case ID_GO_BACK:
	case ID_GO_FORWARD:
		{
			if (CMFCToolBar::IsCustomizeMode ())
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CMainFrame::OnUpdateGoAddressEdit(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnCategorie(UINT nID)
{
	if (m_nCategorie != -1)
	{
		ShowPane (&m_wndLinksBars[m_nCategorie], FALSE, TRUE, FALSE);
	}

	m_nCategorie = nID - ID_CATEGORIE_1;

	ShowPane (&m_wndLinksBars[m_nCategorie], TRUE, FALSE, FALSE);
}

void CMainFrame::OnUpdateCategorie(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (pCmdUI->m_nID == (m_nCategorie + ID_CATEGORIE_1));
}

void CMainFrame::OnLinks(UINT nID)
{
	CMSMLinksBar* pBar = GetLinksBar (nID);

	if (pBar != NULL)
	{
		pBar->SetCurrentCommand (nID);
	}
}

void CMainFrame::OnUpdateLinks(CCmdUI* pCmdUI) 
{
	CMSMLinksBar* pBar = GetLinksBar (pCmdUI->m_nID);

	if (pBar != NULL)
	{
		pCmdUI->SetCheck (pCmdUI->m_nID == pBar->GetCurrentCommand ());
	}

	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateBackward1(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
	
}

void CMainFrame::OnUpdateBackward2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateForward1(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateForward2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateCustomize(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CFrameWnd::OnGetMinMaxInfo(lpMMI);

	if(m_wndCategoryBar.GetSafeHwnd () != NULL)
	{
		CRect rtRect (CPoint (0, 0), m_wndCategoryBar.CalcSize (FALSE));

		rtRect.bottom = 200;

		CalcWindowRect (rtRect, CWnd::adjustBorder);

		lpMMI->ptMinTrackSize.x = rtRect.Width ();
		lpMMI->ptMinTrackSize.y = rtRect.Height ();
	}
}

void CMainFrame::OnHelpMicrosoft() 
{
	::ShellExecute (NULL, NULL, _T("http://msdn2.microsoft.com/en-us/visualc/default.aspx"), NULL, NULL, NULL);
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CFrameWnd::OnSettingChange(uFlags, lpszSection);

	if (m_wndCaptionBar.GetSafeHwnd () != NULL && 
		afxGlobalData.fontRegular.GetSafeHandle () != NULL)
	{
		LOGFONT lf;
		ZeroMemory (&lf, sizeof (LOGFONT));
		afxGlobalData.fontRegular.GetLogFont (&lf);

		m_wndCaptionBar.SetCaptionFont (lf);
	}

	CRect rt;
	GetClientRect (rt);

	SetupMemoryBitmapSize (rt.Size ());
}

