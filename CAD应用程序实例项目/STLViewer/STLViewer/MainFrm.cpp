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

	// ���ı�����ɫ 
	p_Radio->SetFaceColor(RGB(153, 217, 234));

	// ��꾭��ʱ������� 
	p_Radio->SetMouseCursorHand();
	// ���ĸ�����ɫ 
	p_Radio->SetTextHotColor(RGB(63, 72, 204));

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
		p_MyRadio[m_Model]->SetCheck(1); //���õ�һ����ѡΪѡ��״̬
		// ������ʾ 
		p_MyRadio[0]->SetTooltip(_T("��ԭ��ģʽ��ʾ"));
		p_MyRadio[1]->SetTooltip(_T("������������ģʽ��ʾ"));
		p_MyRadio[2]->SetTooltip(_T("������������ģʽ��ʾ"));
	}


	// ������ʾ������m_wndDisplayBar
	if (!m_wndDisplayBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndDisplayBar.LoadToolBar(IDR_TOOLBAR_DISPLAY))
	{
		TRACE0("Failed to create display toolbar\n");
		return -1;      // fail to create
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


	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	// ����m_wndDisplayBar��ͣ������
	m_wndDisplayBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar); // ���������ƺ���

	// ��m_wndDisplayBarͣ���ڿ�ܴ��ڵ����
	DockControlBar(&m_wndDisplayBar,AFX_IDW_DOCKBAR_LEFT);
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

