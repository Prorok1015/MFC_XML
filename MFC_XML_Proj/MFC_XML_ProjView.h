
// MFC_XML_ProjView.h: интерфейс класса CMFCXMLProjView
//

#pragma once


class CMFCXMLProjView : public CEditView
{
protected:
	// создать только из сериализации
	CMFCXMLProjView() noexcept;
	DECLARE_DYNCREATE(CMFCXMLProjView)

// Атрибуты
public:
	CMFCXMLProjDoc* GetDocument() const;
	void OpenDocuemnt();
// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора

// Реализация
public:
	virtual ~CMFCXMLProjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFileSave();
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в MFC_XML_ProjView.cpp
inline CMFCXMLProjDoc* CMFCXMLProjView::GetDocument() const
   { return reinterpret_cast<CMFCXMLProjDoc*>(m_pDocument); }
#endif

