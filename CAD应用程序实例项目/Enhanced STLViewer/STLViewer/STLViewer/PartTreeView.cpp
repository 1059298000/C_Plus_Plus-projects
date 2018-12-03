// PartTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "STLViewer.h"
#include "PartTreeView.h"

#include "STLViewerDoc.h"
#include "DlgEntityName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ITEM_OF_NAME	0
#define ITEM_OF_COLOR	1
#define ITEM_OF_VISIBLE	2

/////////////////////////////////////////////////////////////////////////////
// CPartTreeView

IMPLEMENT_DYNCREATE(CPartTreeView, CTreeView)

CPartTreeView::CPartTreeView()
{
}

CPartTreeView::~CPartTreeView()
{
}


BEGIN_MESSAGE_MAP(CPartTreeView, CTreeView)
	//{{AFX_MSG_MAP(CPartTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPartTreeView drawing

void CPartTreeView::OnDraw(CDC* pDC)
{
	CSTLViewerDoc* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPartTreeView diagnostics

#ifdef _DEBUG
void CPartTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CPartTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPartTreeView message handlers
CSTLViewerDoc* CPartTreeView::GetDocument()
{
	// ������ͼ��δ���ĵ�����
	if(m_pDocument==NULL){

		// ��ȡӦ�ó�����ĵ�ָ��
		CFrameWnd* frm = (CFrameWnd*) ::AfxGetMainWnd();
		ASSERT(frm);
		CDocument* pDoc = frm->GetActiveDocument();
		ASSERT(pDoc);

		// ȷ�ϻ�ȡ���ĵ�������Ҫ������
		ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CSTLViewerDoc)));

		// ���ĵ��м������ͼ��ָ��
		pDoc->AddView(this);
	}

	// ���Ѿ����ĵ��������򷵻��ĵ�ָ��
	return (CSTLViewerDoc*)m_pDocument;
}

void CPartTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	// ��ȡ���������ĵ������ָ��
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	// ������Ϳؼ���������Ŀ
	treeCtrl.DeleteAllItems();

	HTREEITEM hti,hti0,hti1;

	CString str;
	// �������Ŀ
	str.Format(_T("PART:%s"),pDoc->m_Part.GetName());
	hti = treeCtrl.InsertItem(str,0,0,NULL,TVI_LAST);
	
	CEntity* ent;

	// �����ĵ���m_Part�����ݴ������Ϳؼ�����Ŀ
	for(int i=0; i<pDoc->m_Part.GetEntitySize();i++){
		ent = pDoc->m_Part.GetEntity(i);
		ASSERT(ent);

		// �ڸ���Ŀ�²���STLģ�͵���Ŀ
		str.Format(_T("Model:%s"),ent->GetName());
		hti0 = treeCtrl.InsertItem(str,1,1,hti,TVI_LAST);

		// STLģ�Ͷ����ָ��ֵ��Ϊ�����Ŀ������
		// ͨ���������ʹ����Ŀ��ģ�Ͷ������
		treeCtrl.SetItemData(hti0,(DWORD)ent);
		
		//attrib of name

		str.Format(_T("Name:%s"),ent->GetName());
		hti1 = treeCtrl.InsertItem(str,2,2,hti0,TVI_LAST);

		// Ϊ����������Ŀ��������ITEM_OF_NAME
		treeCtrl.SetItemData(hti1,ITEM_OF_NAME);

		//attrib of color 
		// ��STLģ����Ŀ�²�����ɫ������Ŀ
		COLORREF clr = ent->GetColor();
		BYTE r = GetRValue(clr);
		BYTE g = GetGValue(clr);
		BYTE b = GetBValue(clr);
		str.Format(_T("Color: R%d G%d B%d"),r,g,b);
		hti1 = treeCtrl.InsertItem(str,2,2,hti0,TVI_LAST);

		// Ϊ��ɫ������Ŀ��������ITEM_OF_COLOR
		treeCtrl.SetItemData(hti1,ITEM_OF_COLOR);
		
		//attrib of visible
		// ��STLģ����Ŀ�²�����ʾ������Ŀ
		if(ent->IsVisible())
			str = "Visible";
		else
			str = "Unvisible";
		hti1 = treeCtrl.InsertItem(str,2,2,hti0,TVI_LAST);

		// Ϊ��ʾ������Ŀ��������ITEM_OF_VISIBLE
		treeCtrl.SetItemData(hti1,ITEM_OF_VISIBLE);
	}

	// ����Ŀ¼�µ���Ŀչ��
	GetTreeCtrl().Expand(hti,TVE_EXPAND);
}

void CPartTreeView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
}

int CPartTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_ImageList.Create(IDB_PART_TREE, 16, 1, RGB(0,255,0));
	GetTreeCtrl().SetImageList(&m_ImageList, TVSIL_NORMAL);

	GetTreeCtrl().CancelToolTips(TRUE);
	CancelToolTips(TRUE);
	return 0;
}

void CPartTreeView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	UINT uFlags = 0;
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	// �õ���굱ǰλ�ô�����Ŀ���
	HTREEITEM hItem = treeCtrl.HitTest(point,&uFlags);
	
	// ȷ�ϸ���Ŀ��������Ŀ
	if(	hItem &&							// ��������Ŀ����
		hItem != treeCtrl.GetRootItem() &&	// ���ص���Ŀ��Ϊ����Ŀ
		!treeCtrl.ItemHasChildren(hItem)){	// ���ص���Ŀû������Ŀ
		
		// ��ȡ����Ŀ�����ݣ����������
		DWORD itemData = treeCtrl.GetItemData(hItem);
		
		// ��ȡ����Ŀ�ĸ���Ŀ�ľ��
		HTREEITEM hParentItem = treeCtrl.GetParentItem(hItem);
		ASSERT(hParentItem);

		// ��ȡ����Ŀ�����ݣ���ָ��CSTLModel��ģ�͵�ָ��
		DWORD parentData = treeCtrl.GetItemData(hParentItem);
		ASSERT(parentData);

		// ������Ŀ������ת��Ϊָ������ָ�룬����Ҫ���޸����ԵĶ����ָ��
		CEntity* ent = (CEntity*) parentData;

		// ������ѡ��Ŀ���������ж��޸�ʲô����
		switch(itemData){
		case ITEM_OF_NAME:
			ChangeEntityName(ent); // �޸���������
			break;
		case ITEM_OF_COLOR:
			ChangeEntityColor(ent); // �޸���ɫ����
			break;
		case ITEM_OF_VISIBLE:
			ChangeEntityVisible(ent); // �޸���ʾ����
			break;
		}
	}
	CTreeView::OnLButtonDblClk(nFlags, point);
}

void CPartTreeView::ChangeEntityName(CEntity* ent)
{
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	CDlgEntityName dlg;
	dlg.m_EntityName = ent->GetName();
	if(dlg.DoModal() == IDOK){				// �����޸����ƶԻ���
		ent->SetName(dlg.m_EntityName);		// ��������
		pDoc->UpdateAllViews(NULL);			// ������ͼ��ʾ
	}
}

// �޸���ɫ����
void CPartTreeView::ChangeEntityColor(CEntity* ent)
{
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	CColorDialog dlg; // ������ɫ�༭�Ի���
	if(dlg.DoModal() == IDOK){ // �����޸���ɫ�Ի���
		COLORREF color = dlg.GetColor();
		ent->SetColor(color); // ��������
		pDoc->UpdateAllViews(NULL); // ������ͼ
	}
}

void CPartTreeView::ChangeEntityVisible(CEntity* ent)
{
	CSTLViewerDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	ent->SetVisible(!ent->IsVisible()); // �޸���ʾ����
	pDoc->UpdateAllViews(NULL); // ������ͼ
}
