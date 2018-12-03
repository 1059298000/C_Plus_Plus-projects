// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "STLViewer.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_MYRADIO1, OnMyRadio1) //��ѡ��ť1
	ON_BN_CLICKED(IDC_MYRADIO2, OnMyRadio2) //��ѡ��ť2
	ON_BN_CLICKED(IDC_MYRADIO3, OnMyRadio3) //��ѡ��ť3

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int CMainFrame::m_Model = 0; // Ĭ��Ϊ����ģʽ0��������ԭ��


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
	for (int i = 0; i < 3; i++)
	{
		if (p_MyRadio[i])
			delete p_MyRadio[i];
	}
}

CMFCButton* CMainFrame::NewMyRadio(int nID, CString titile, CRect rect, int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString(nID); //ȡ��ť����
	CMFCButton *p_Radio = new CMFCButton();
	ASSERT_VALID(p_Radio);
	p_Radio->Create(m_Caption, WS_CHILD | WS_VISIBLE | nStyle | WS_TABSTOP | BS_AUTORADIOBUTTON, rect, this, nID); //������ť
																												   // �������� 
	p_Radio->SetWindowText(titile);
	//p_Radio->m_bTransparent = TRUE;

	p_Radio->m_nFlatStyle = CMFCButton::BUTTONSTYLE_3D;

	p_Radio->SetCheck(TRUE);
	//p_Radio->SizeToContent();
	return p_Radio;
}

//������ѡ��ť1
void CMainFrame::OnMyRadio1()
{
	m_Model = 0;
	//Redraw the view
	InvalidateRect(NULL, FALSE);
}
//������ѡ��ť2
void CMainFrame::OnMyRadio2()
{
	m_Model = 1;
	//Redraw the view
	InvalidateRect(NULL, FALSE);
}
//������ѡ��ť3 
void CMainFrame::OnMyRadio3()
{
	m_Model = 2;

	//Redraw the view
	InvalidateRect(NULL, FALSE);
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	// ����ģʽѡ��ť
	{
		// ����ģʽѡ��ť
		p_MyRadio[0] = NewMyRadio(IDC_MYRADIO1, _T("ԭ��"), CRect(500, 10, 600, 40), WS_GROUP);
		p_MyRadio[1] = NewMyRadio(IDC_MYRADIO2, _T("����������"), CRect(600, 10, 700, 40), 0);
		p_MyRadio[2] = NewMyRadio(IDC_MYRADIO3, _T("����������"), CRect(700, 10, 800, 40), 0);
		//p_MyRadio[m_Model]->SetCheck(1); //���õ�һ����ѡΪѡ��״̬
		// ������ʾ 
		p_MyRadio[0]->SetTooltip(_T("��ԭ��ģʽ��ʾ"));
		p_MyRadio[1]->SetTooltip(_T("������������ģʽ��ʾ"));
		p_MyRadio[2]->SetTooltip(_T("������������ģʽ��ʾ"));
	}


	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if(!m_wndDisplayBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndDisplayBar.LoadToolBar(IDR_TOOLBAR_DISPLAY))
	{
		TRACE0("Failed to create display toolbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	// ���� m_wndToolBar����ͣ���ڴ����ڵ�����λ����
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	// ����m_wndDisplayBar����ͣ���ڴ����ڵ�����λ����
	m_wndDisplayBar.EnableDocking(CBRS_ALIGN_ANY);

	// ����������������
	m_wndToolBar.SetWindowText(_T("Standard Tool"));
	m_wndDisplayBar.SetWindowText(_T("Display Tool"));

	// ���������ڴ����ڵ�����λ��ͣ��
	EnableDocking(CBRS_ALIGN_ANY);

	// ͣ��������m_wndToolBar��Ĭ��λ��
	DockControlBar(&m_wndToolBar);

	// ��������m_wndDisplayBar��m_wndToolBarͣ����һ�У���λ������
	DockControlBarLeftOf(&m_wndDisplayBar,&m_wndToolBar);

	//------------------------------------------------------------
	//create LeftDockBar ������ߵĸ�������
	if (!m_LeftDockBar.Create(this,_T("Work Bar")))
	{
		TRACE0("Failed to create LeftDockBar\n");
		return -1;		// fail to create
	}

	m_OutputDockBar.SetDockSize(CSize(200,100));
	if(!m_OutputDockBar.Create(this,_T("Output Bar")))
	{
		TRACE0("Failed to create m_OutputDockBar\n");
		return -1;
	}

	// ֻ���������m_LeftDockBarʹ����������ͣ����
	m_LeftDockBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);

	// ʹ����ߵ�ͣ������ͣ��m_LeftDockBar
	DockControlBar(&m_LeftDockBar,AFX_IDW_DOCKBAR_LEFT);

	// ֻ����������m_OutputDockBarͣ������������ͣ����
	m_OutputDockBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);

	// ʹ�������ͣ������ͣ��m_OutputDockBar
	DockControlBar(&m_OutputDockBar,AFX_IDW_DOCKBAR_BOTTOM);

	//---------------------------------------------------------------

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
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
void CMainFrame::DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf)
{
	CRect rect; // �����������
	DWORD dw;
	UINT n;

	// ʹ��MFC�����¼������й������ĳߴ磬ȷ��GetWindowRect()׼ȷ
	RecalcLayout();
	LeftOf->GetWindowRect(&rect);

	// ����ƫ��ֵ��ͣ����ͬһ������
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// ��������ͣ����rect�涨�ľ���������
	DockControlBar(Bar,n,&rect);
}
