
// MFC_XML_ProjDoc.cpp: реализация класса CMFCXMLProjDoc 
//


#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFC_XML_Proj.h"
#endif

#include "MFC_XML_ProjDoc.h"

#include <propkey.h>

#include <objbase.h>
#include <MsXml6.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCXMLProjDoc

IMPLEMENT_DYNCREATE(CMFCXMLProjDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCXMLProjDoc, CDocument)
END_MESSAGE_MAP()


// Macro that calls a COM method returning HRESULT value.
#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0)

// Macro to verify memory allcation.
#define CHK_ALLOC(p)        do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0)

// Macro that releases a COM object if not NULL.
#define SAFE_RELEASE(p)     do { if ((p)) { (p)->Release(); (p) = NULL; } } while(0)

// Helper function to create a VT_BSTR variant from a null terminated string. 
HRESULT VariantFromString(PCWSTR wszValue, VARIANT& Variant)
{
	HRESULT hr = S_OK;
	BSTR bstr = SysAllocString(wszValue);
	CHK_ALLOC(bstr);

	V_VT(&Variant) = VT_BSTR;
	V_BSTR(&Variant) = bstr;

CleanUp:
	return hr;
}

// Helper function to create a DOM instance. 
HRESULT CreateAndInitDOM(IXMLDOMDocument** ppDoc)
{
	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc));
	if (SUCCEEDED(hr))
	{
		// these methods should not fail so don't inspect result
		(*ppDoc)->put_async(VARIANT_FALSE);
		(*ppDoc)->put_validateOnParse(VARIANT_FALSE);
		(*ppDoc)->put_resolveExternals(VARIANT_FALSE);
	}
	return hr;
}

// Создание или уничтожение CMFCXMLProjDoc

CMFCXMLProjDoc::CMFCXMLProjDoc() noexcept
{
	HRESULT hr = S_OK;

	BSTR bstrXML = NULL;
	BSTR bstrErr = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;
	VariantInit(&varFileName);

	CreateAndInitDOM(&pXMLDom);
}

CMFCXMLProjDoc::~CMFCXMLProjDoc()
{
}

BOOL CMFCXMLProjDoc::LoadXMLFILE(CString xmlName)
{
	HRESULT hr = S_OK;

	BSTR bstrErr = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;
	VariantInit(&varFileName);
	VariantFromString(xmlName, varFileName);
	pXMLDom->load(varFileName, &varStatus);
	if (varStatus == VARIANT_TRUE)
	{
		pXMLDom->get_xml(&bstrXML);
		return TRUE;
	}
	else
	{
		bstrXML = L"";
	}

	return FALSE;
}

BOOL CMFCXMLProjDoc::NewXMLFILE(CString FileName)
{
	VARIANT varFileName;
	VariantInit(&varFileName);
	VariantFromString(FileName, varFileName);
	HRESULT hr = pXMLDom->save(varFileName);
	return SUCCEEDED(hr);
}

BOOL CMFCXMLProjDoc::SaveXMLFILE()
{
	CFileDialog FileDlg(FALSE, L"xml", NULL, NULL, CString(".xml"));
	if (FileDlg.DoModal() == IDOK)
	{
		CFile f;
		f.Open(FileDlg.GetPathName(), CFile::modeCreate |
			CFile::modeReadWrite);
		f.Write(CString(bstrXML), sizeof(CString(bstrXML)));
	}
	return 0;
}

BOOL CMFCXMLProjDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	
	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CMFCXMLProjDoc

void CMFCXMLProjDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CMFCXMLProjDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CMFCXMLProjDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CMFCXMLProjDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CMFCXMLProjDoc

#ifdef _DEBUG
void CMFCXMLProjDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCXMLProjDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CMFCXMLProjDoc
