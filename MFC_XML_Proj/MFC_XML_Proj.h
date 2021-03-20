
// MFC_XML_Proj.h: основной файл заголовка для приложения MFC_XML_Proj
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMFCXMLProjApp:
// Сведения о реализации этого класса: MFC_XML_Proj.cpp
//

class CMFCXMLProjApp : public CWinAppEx
{
public:
	CMFCXMLProjApp() noexcept;
	

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnNewFile();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCXMLProjApp theApp;
