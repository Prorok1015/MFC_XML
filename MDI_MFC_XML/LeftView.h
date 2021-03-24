
// LeftView.h: интерфейс класса CLeftView
//


#pragma once

class CMDIMFCXMLDoc;

class CLeftView : public CTreeView
{
	CComBSTR ssName = NULL;
protected: // создать только из сериализации
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Атрибуты
public:
	CMDIMFCXMLDoc* GetDocument();

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
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в LeftView.cpp
inline CMDIMFCXMLDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CMDIMFCXMLDoc*>(m_pDocument); }
#endif

