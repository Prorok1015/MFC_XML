
// ChildFrm.h: интерфейс класса CChildFrame
//

#pragma once
class CMDIMFCXMLView;
class CLeftView;

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame() noexcept;

// Атрибуты
protected:
	CSplitterWndEx m_wndSplitter;
public:

// Операции
public:

// Переопределение
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMDIMFCXMLView* GetRightPane();
	CLeftView* GetLeftView();
// Созданные функции схемы сообщений
protected:
	afx_msg void OnOpenFile();
	DECLARE_MESSAGE_MAP()
};
