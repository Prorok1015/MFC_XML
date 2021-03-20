
// MFC_XML_ProjDoc.h: интерфейс класса CMFCXMLProjDoc 
//


#pragma once

class CMFCXMLProjDoc : public CDocument
{
private:
	IXMLDOMDocument* pXMLDom = NULL;
	IXMLDOMParseError* pXMLErr = NULL;
	

protected: // создать только из сериализации
	CMFCXMLProjDoc() noexcept;
	DECLARE_DYNCREATE(CMFCXMLProjDoc)

// Атрибуты
public:
	BSTR bstrXML = NULL;
// Операции
public:
	BOOL LoadXMLFILE(CString xmlName1);
	BOOL NewXMLFILE(CString varFileName);
	BOOL SaveXMLFILE();
// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CMFCXMLProjDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
