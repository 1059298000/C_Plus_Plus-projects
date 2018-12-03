// STLViewerDoc.cpp : implementation of the CSTLViewerDoc class
//

#include "stdafx.h"
#include "STLViewer.h"

#include "STLViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerDoc

IMPLEMENT_DYNCREATE(CSTLViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CSTLViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CSTLViewerDoc)
	ON_COMMAND(ID_STL_FILEIN, OnStlFilein)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerDoc construction/destruction

CSTLViewerDoc::CSTLViewerDoc()
{
	// TODO: add one-time construction code here
	pSTLModel = NULL; // ��ʼ��
	m_Mode = 0; // ��ʼ������ģʽΪ0������ԭ�ͻ���
}

CSTLViewerDoc::~CSTLViewerDoc()
{
}

BOOL CSTLViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_Part.RemoveAllEntity();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSTLViewerDoc serialization

void CSTLViewerDoc::Serialize(CArchive& ar)
{
	m_Part.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerDoc diagnostics

#ifdef _DEBUG
void CSTLViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSTLViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSTLViewerDoc commands

void CSTLViewerDoc::OnStlFilein() 
{
	CFileDialog dlg(TRUE,_T("stl"),NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Stereo Lithograpic File(*.stl)|*.stl"), NULL );

	if(dlg.DoModal()==IDOK){
		// ����һ���յ�CSTLModel�Ķ���
		pSTLModel = new CSTLModel();

		// �ڶ���pSTLModel�������ļ��ڵ�STLģ��
		CString strName = dlg.GetPathName();

		// ��ȡSTL�ļ�
		pSTLModel->LoadSTLFile(strName, m_Mode);

		if (pSTLModel->IsEmpty()) // ���STLģ��Ϊ�գ��ͷ�pSTLModel����
			delete pSTLModel;
		else			// ���STLģ�Ͳ�Ϊ�գ�����pSTLModel����m_Part��
			m_Part.AddEntity(pSTLModel);

		UpdateAllViews(NULL); // �����������ĵ���������ͼ������ʾ�������ģ��
	}
}


void CSTLViewerDoc::OnCloseDocument() 
{

	CDocument::OnCloseDocument();
}
