
// ChildFrm.cpp: реализация класса CChildFrame
//

#include "pch.h"
#include "framework.h"
#include "MDI_MFC_XML.h"

#include "ChildFrm.h"
#include "LeftView.h"
#include "MDI_MFC_XMLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame



IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_OPEN, &CChildFrame::OnOpenFile)
END_MESSAGE_MAP()

// Создание или уничтожение CChildFrame

CChildFrame::CChildFrame() noexcept
{
	// TODO: добавьте код инициализации члена
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	// создать окно разделения
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(400, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMDIMFCXMLView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: измените класс Window или стили посредством изменения CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

void CChildFrame::OnOpenFile()
{
	CFileDialog fileDlg(TRUE);

	bool bOk = fileDlg.DoModal() == IDOK;

	if (bOk) {
		GetRightPane()->Clear();
		GetLeftView()->Clear();
		GetRightPane()->LoadFile(fileDlg.GetPathName());
		GetLeftView()->LoadFile(fileDlg.GetPathName());
	}
}


CMDIMFCXMLView* CChildFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CMDIMFCXMLView* pView = DYNAMIC_DOWNCAST(CMDIMFCXMLView, pWnd);
	return pView;
}

CLeftView* CChildFrame::GetLeftView()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	return pView;
}
// Диагностика CChildFrame

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// Обработчики сообщений CChildFrame
