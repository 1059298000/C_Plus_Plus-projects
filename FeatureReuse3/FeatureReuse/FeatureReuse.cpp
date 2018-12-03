﻿
// FeatureReuse.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "FeatureReuse.h"
#include "MainFrm.h"

#include "FeatureReuseDoc.h"
#include "FeatureReuseView.h"
#include "G:\develop\c++Projects\FeatureReuse3\FeatureReuse\CButtonST\BtnST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFeatureReuseApp

BEGIN_MESSAGE_MAP(CFeatureReuseApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CFeatureReuseApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CFeatureReuseApp 构造

CFeatureReuseApp::CFeatureReuseApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CFeatureReuseApp 对象

CFeatureReuseApp theApp;


// CFeatureReuseApp 初始化

BOOL CFeatureReuseApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);



	CWinAppEx::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名


	
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CleanState(_T("应用程序向导生成的本地应用程序")); // 用于清除注册表信息，及时显示工具栏更改

	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); //这一句 


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFeatureReuseDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CFeatureReuseView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);

	//CString title = "金属塑性成形过程的无网格方法仿真可视化系统";
	//m_pMainWnd->SetWindowText(title);

	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生

	
	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CButtonST bn1;
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, bn1);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CFeatureReuseApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CFeatureReuseApp 自定义加载/保存方法

void CFeatureReuseApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CFeatureReuseApp::LoadCustomState()
{
}

void CFeatureReuseApp::SaveCustomState()
{
}

// CFeatureReuseApp 消息处理程序


void CAboutDlg::OnBnClickedButton1()
{
	bn1.SetIcon(IDI_ICON2, IDI_ICON1);
	bn1.SetFlat(FALSE);
	// TODO: 在此添加控件通知处理程序代码
}
