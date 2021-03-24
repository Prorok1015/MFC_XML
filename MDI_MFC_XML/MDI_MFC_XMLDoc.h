
// MDI_MFC_XMLDoc.h: интерфейс класса CMDIMFCXMLDoc 
//


#pragma once


class CMDIMFCXMLDoc : public CDocument
{
protected: // создать только из сериализации
	CMDIMFCXMLDoc() noexcept;
	DECLARE_DYNCREATE(CMDIMFCXMLDoc)

// Атрибуты
public:
	IXMLDOMDocument* pXMLDom = NULL;
	IXMLDOMParseError* pXMLErr = NULL;
	BSTR bstrXML = NULL;
// Операции
public:
	BOOL LoadXMLFILE(CString xmlName1);
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
	virtual ~CMDIMFCXMLDoc();
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
