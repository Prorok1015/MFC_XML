
// LeftView.cpp: реализация класса CLeftView
//

#include "pch.h"
#include "framework.h"
#include "MFC_XML_Proj.h"

#include "MFC_XML_ProjDoc.h"
#include "LeftView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_COMMAND(ID_FILE_NEW, &CLeftView::ToolBarNew)
	ON_COMMAND(ID_FILE_OPEN, &CLeftView::ToolBarOpen)
	ON_COMMAND(ID_FILE_DELETE, &CLeftView::ToolBarDelete)
	ON_COMMAND(ID_FILE_EDIT, &CLeftView::ToolBarEdit)
	ON_COMMAND(ID_FILE_SAVE, &CLeftView::OnFileSave)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CLeftView::OnFileSave()
{
	GetDocument()->SaveXMLFILE();
}

void CLeftView::ToolBarEdit()
{

}

void CLeftView::ToolBarDelete()
{
	HTREEITEM item = GetTreeCtrl().GetSelectedItem();
	GetTreeCtrl().DeleteItem(item);
}

void CLeftView::ToolBarOpen()
{
	CFileDialog fileDlg(TRUE);

	bool bOk = fileDlg.DoModal() == IDOK;

	if (bOk) {
		CString pathName = fileDlg.GetPathName();
		TVINSERTSTRUCT tvInsert;
		tvInsert.hParent = lastSelect;
		tvInsert.hInsertAfter = lastSelect;
		tvInsert.item.mask = TVIF_TEXT;
		tvInsert.item.pszText = pathName.GetBuffer(FILE_LIST_BUFFER_SIZE);
		GetTreeCtrl().InsertItem(&tvInsert);

		
	}
}

void CLeftView::ToolBarNew()
{
	CString nameFile;
	nameFile.Format(TEXT("res/New%d.xml"), countNew++);
	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = lastSelect;
	tvInsert.hInsertAfter = lastSelect;
	tvInsert.item.mask = TVIF_TEXT;
	//tvInsert.item.lParam =
	tvInsert.item.pszText = nameFile.GetBuffer(FILE_LIST_BUFFER_SIZE);

	if (GetDocument()->NewXMLFILE(nameFile) == TRUE)
	{
		GetTreeCtrl().InsertItem(&tvInsert);
		GetTreeCtrl().SetFocus();
	}

}

// Создание или уничтожение CLeftView

CLeftView::CLeftView()
{
	// TODO: добавьте код создания

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: измените класс Window или стили посредством изменения CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	ModifyStyle(LVS_TYPEMASK, TVS_LINESATROOT | TVS_HASLINES |
		TVS_HASBUTTONS | TVS_EDITLABELS);
	
	/*TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("Insert");

	for(int i = 0; i < 10; ++i)
	GetTreeCtrl().InsertItem(&tvInsert);*/
	// TODO: заполните TreeView элементами посредством непосредственного обращения
	//  к элементам управления этого дерева через вызов GetTreeCtrl().
}


// Диагностика CLeftView

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

void CLeftView::OnLButtonDown(UINT nFlags, CPoint point)
{
	HTREEITEM select = GetTreeCtrl().HitTest(point);
	if (select == NULL)
	{
		GetTreeCtrl().SelectItem(select);
		lastSelect = select;
		return;
	}
	GetTreeCtrl().SelectItem(select);
	CString st = GetTreeCtrl().GetItemText(select);
	lastSelect = select;
	
	GetDocument()->LoadXMLFILE(st);
	GetParentFrame()->SendMessage(WM_USER_MY_OWN_MESSAGE);
}

CMFCXMLProjDoc* CLeftView::GetDocument() // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCXMLProjDoc)));
	return (CMFCXMLProjDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CLeftView
