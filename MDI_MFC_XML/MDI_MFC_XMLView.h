
// MDI_MFC_XMLView.h: интерфейс класса CMDIMFCXMLView
//

#pragma once


class CMDIMFCXMLView : public CTreeView
{
	CComBSTR ssName = NULL;
protected: // создать только из сериализации
	CMDIMFCXMLView() noexcept;
	DECLARE_DYNCREATE(CMDIMFCXMLView)

// Атрибуты
public:
	CMDIMFCXMLDoc* GetDocument() const;

// Операции
public:
	HTREEITEM AddOnTree(CComBSTR sName, HTREEITEM parent);
	void AddChildNode(CComPtr<IXMLDOMNode> pNode, HTREEITEM parent);
	void LoadFile(CString pathName);
	void Clear();
// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора

// Реализация
public:
	virtual ~CMDIMFCXMLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в MDI_MFC_XMLView.cpp
inline CMDIMFCXMLDoc* CMDIMFCXMLView::GetDocument() const
   { return reinterpret_cast<CMDIMFCXMLDoc*>(m_pDocument); }
#endif

