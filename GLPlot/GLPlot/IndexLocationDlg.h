#pragma once
#include "resource.h"

// CIndexLocationDlg �Ի���

class CIndexLocationDlg : public CDialog
{
	DECLARE_DYNAMIC(CIndexLocationDlg)

public:
	CIndexLocationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIndexLocationDlg();

// �Ի�������
	enum { IDD = IDD_INDEX_LOCATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    UINT m_EditIndex;
public:
    afx_msg void OnBnClickedOk();
};
