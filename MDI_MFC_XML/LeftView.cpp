
// LeftView.cpp: реализация класса CLeftView
//

#include "pch.h"
#include "framework.h"
#include "MDI_MFC_XML.h"

#include "MDI_MFC_XMLDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
END_MESSAGE_MAP()


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
	// TODO: заполните TreeView элементами посредством непосредственного обращения
	//  к элементам управления этого дерева через вызов GetTreeCtrl().
}

HTREEITEM CLeftView::AddOnTree(CComBSTR sName, HTREEITEM parent)
{
	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = parent;
	tvInsert.hInsertAfter = parent;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = sName;
	HTREEITEM itm = GetTreeCtrl().InsertItem(&tvInsert);
	return itm;
}

void CLeftView::AddChildNode(CComPtr<IXMLDOMNode> pNode, HTREEITEM parent)
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
			hr = Node->get_nodeName(&ssName);
			if (SUCCEEDED(hr))
			{
				auto par = AddOnTree(ssName, parent);
				AddChildNode(Node, par);
			}

		}
	}

}

void CLeftView::LoadFile(CString pathName)
{
	GetDocument()->LoadXMLFILE(pathName);

	CComPtr<IXMLDOMElement> pRootElement;
	CComPtr<IXMLDOMDocument> pDoc = GetDocument()->pXMLDom;

	if (SUCCEEDED(pDoc->get_documentElement(&pRootElement)))
	{

		CComPtr<IXMLDOMNodeList> pNodeList;

		pRootElement->get_childNodes(&pNodeList); // Child node list
		pRootElement->get_nodeName(&ssName);
		HTREEITEM parent = AddOnTree(ssName, NULL);
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
				auto par = AddOnTree(ssName, parent);
				AddChildNode(pNode, par);
			}
		}
	}

}
void CLeftView::Clear()
{
	GetTreeCtrl().DeleteAllItems();
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

CMDIMFCXMLDoc* CLeftView::GetDocument() // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIMFCXMLDoc)));
	return (CMDIMFCXMLDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CLeftView
