
// LeftView.h: интерфейс класса CLeftView
//


#pragma once

class CMFCXMLProjDoc;

class CLeftView : public CTreeView
{
	HTREEITEM lastSelect = NULL;
	INT countNew = 0;
protected: // создать только из сериализации
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Атрибуты
public:
	CMFCXMLProjDoc* GetDocument();

// Операции
public:

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
	afx_msg void OnFileSave();
	afx_msg void ToolBarEdit();
	afx_msg void ToolBarDelete();
	afx_msg void ToolBarOpen();
	afx_msg void ToolBarNew();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в LeftView.cpp
inline CMFCXMLProjDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CMFCXMLProjDoc*>(m_pDocument); }
#endif

