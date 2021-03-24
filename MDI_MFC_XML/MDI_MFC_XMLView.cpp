
// MDI_MFC_XMLView.cpp: реализация класса CMDIMFCXMLView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MDI_MFC_XML.h"
#endif

#include "MDI_MFC_XMLDoc.h"
#include "MDI_MFC_XMLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

// CMDIMFCXMLView

IMPLEMENT_DYNCREATE(CMDIMFCXMLView, CTreeView)

BEGIN_MESSAGE_MAP(CMDIMFCXMLView, CTreeView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CMDIMFCXMLView

CMDIMFCXMLView::CMDIMFCXMLView() noexcept
{
	// TODO: добавьте код создания

}

CMDIMFCXMLView::~CMDIMFCXMLView()
{
}

HTREEITEM CMDIMFCXMLView::AddOnTree(CComBSTR sName, HTREEITEM parent = NULL)
{
	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = parent;
	tvInsert.hInsertAfter = parent;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = sName;
	HTREEITEM itm = GetTreeCtrl().InsertItem(&tvInsert);
	return itm;
}

void CMDIMFCXMLView::AddChildNode(CComPtr<IXMLDOMNode> pNode, HTREEITEM parent = NULL)
{
	if (pNode == NULL)
		return;
	CComPtr<IXMLDOMNodeList> fooNodeList = NULL;
	HRESULT hr = pNode->get_childNodes(&fooNodeList);
	if (SUCCEEDED(hr))
	{
		long nLen;
		fooNodeList->get_length(&nLen);
		for (long i = 0; i != nLen; ++i)
		{
			CComPtr<IXMLDOMNode> Node = NULL;
			hr = fooNodeList->nextNode(&Node);

			CComPtr<IXMLDOMNode> Node2 = NULL;
			Node->cloneNode(VARIANT_FALSE, &Node2);

			CComPtr<IXMLDOMNodeList> fooNodeList2 = NULL;
			Node2->get_childNodes(&fooNodeList2);

			long nLen2;
			fooNodeList2->get_length(&nLen2);
			for (long i2 = 0; i2 != nLen; ++i2)
			{
				CComPtr<IXMLDOMNode> varNode = NULL;
				fooNodeList2->get_item(i2, &varNode);
				Node2->removeChild(varNode, &varNode);
			}
			hr = Node2->get_xml(&ssName);
			if (SUCCEEDED(hr))
			{
				auto par = AddOnTree(ssName, parent);
				AddChildNode(Node, par);
			}

		}
	}

}

void CMDIMFCXMLView::LoadFile(CString pathName)
{
	GetDocument()->LoadXMLFILE(pathName);

	CComPtr<IXMLDOMElement> pRootElement;
	CComPtr<IXMLDOMDocument> pDoc = GetDocument()->pXMLDom;

	if (SUCCEEDED( pDoc->get_documentElement(&pRootElement) ))
	{

		CComPtr<IXMLDOMNodeList> pNodeList;

		pRootElement->get_childNodes(&pNodeList); // Child node list
		long nLen;
		pNodeList->get_length(&nLen);    // Child node list
		for (long i = 0; i != nLen; ++i)
		{
			CComPtr<IXMLDOMNode> pNode;
			HRESULT hr = pNodeList->nextNode(&pNode);
			CComBSTR ssName;
			hr = pNode->get_nodeName(&ssName);
			if (SUCCEEDED(hr))
			{
				auto par = AddOnTree(ssName);
				AddChildNode(pNode, par);
			}
		}
	}

}

void CMDIMFCXMLView::Clear()
{
	GetTreeCtrl().DeleteAllItems();
}



BOOL CMDIMFCXMLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void CMDIMFCXMLView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	ModifyStyle(LVS_TYPEMASK, TVS_LINESATROOT | TVS_HASLINES |
		TVS_HASBUTTONS | TVS_EDITLABELS);

}

void CMDIMFCXMLView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMDIMFCXMLView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CMDIMFCXMLView

#ifdef _DEBUG
void CMDIMFCXMLView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMDIMFCXMLView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMDIMFCXMLDoc* CMDIMFCXMLView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIMFCXMLDoc)));
	return (CMDIMFCXMLDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMDIMFCXMLView
