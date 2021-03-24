
// MDI_MFC_XML.h: основной файл заголовка для приложения MDI_MFC_XML
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMDIMFCXMLApp:
// Сведения о реализации этого класса: MDI_MFC_XML.cpp
//

class CMDIMFCXMLApp : public CWinAppEx
{
public:
	CMDIMFCXMLApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMDIMFCXMLApp theApp;
