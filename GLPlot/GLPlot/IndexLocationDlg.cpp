// IndexLocationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IndexLocationDlg.h"


// CIndexLocationDlg �Ի���

IMPLEMENT_DYNAMIC(CIndexLocationDlg, CDialog)

CIndexLocationDlg::CIndexLocationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIndexLocationDlg::IDD, pParent)
    , m_EditIndex(0)
{

}

CIndexLocationDlg::~CIndexLocationDlg()
{
}

void CIndexLocationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_INDEX, m_EditIndex);
}


BEGIN_MESSAGE_MAP(CIndexLocationDlg, CDialog)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CIndexLocationDlg ��Ϣ�������

void CIndexLocationDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (!UpdateData())
    {
        return;
    }
    OnOK();
}
