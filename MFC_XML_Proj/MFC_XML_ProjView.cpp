
// MFC_XML_ProjView.cpp: реализация класса CMFCXMLProjView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFC_XML_Proj.h"
#endif

#include "MFC_XML_ProjDoc.h"
#include "MFC_XML_ProjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCXMLProjView

IMPLEMENT_DYNCREATE(CMFCXMLProjView, CEditView)

BEGIN_MESSAGE_MAP(CMFCXMLProjView, CEditView)
	//ON_COMMAND(ID_FILE_OPEN, CMFCXMLProjView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVE, &CMFCXMLProjView::OnFileSave)
	ON_WM_STYLECHANGED()
	
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CMFCXMLProjView

CMFCXMLProjView::CMFCXMLProjView() noexcept
{
	// TODO: добавьте код создания
}

void CMFCXMLProjView::OpenDocuemnt()
{
	OnFilePrintPreview();
}

CMFCXMLProjView::~CMFCXMLProjView()
{
}

BOOL CMFCXMLProjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CEditView::PreCreateWindow(cs);
}

void CMFCXMLProjView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	//CString strText;

	// Insert 10 items in the list view control.
	/*for (int i = 0; i < 10; i++)
	{
		strText.Format(TEXT("item %d"), i);

		// Insert the item, select every other item.
		GetListCtrl().InsertItem(LVIF_TEXT | LVIF_STATE, i, strText,
			(i % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);

	}*/
	// TODO: ListView можно заполнить элементами посредством непосредственного обращения
	//  к элементам управления этого списка через вызов GetListCtr().
}

void CMFCXMLProjView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//GetEditCtrl().accHitTest()
}

void CMFCXMLProjView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCXMLProjView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CMFCXMLProjView

#ifdef _DEBUG
void CMFCXMLProjView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMFCXMLProjView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMFCXMLProjDoc* CMFCXMLProjView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCXMLProjDoc)));
	return (CMFCXMLProjDoc*)m_pDocument;
}
#endif //_DEBUG


void CMFCXMLProjView::OnFileSave()
{
	GetDocument()->SaveXMLFILE();
}

// Обработчики сообщений CMFCXMLProjView
void CMFCXMLProjView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: добавьте код для выполнения, если пользователь изменит стиль представления окна
	CEditView::OnStyleChanged(nStyleType,lpStyleStruct);
}

void CMFCXMLProjView::OnFilePrintPreview()
{


	if(GetDocument()->bstrXML == NULL)
		GetEditCtrl().SetWindowTextW(L"");
	CString strText = GetDocument()->bstrXML;
	GetEditCtrl().SetWindowTextW(strText);
}
