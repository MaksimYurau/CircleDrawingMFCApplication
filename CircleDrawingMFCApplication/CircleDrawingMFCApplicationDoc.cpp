
// CircleDrawingMFCApplicationDoc.cpp: реализация класса CCircleDrawingMFCApplicationDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "CircleDrawingMFCApplication.h"
#endif

#include "CircleDrawingMFCApplicationDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCircleDrawingMFCApplicationDoc

IMPLEMENT_DYNCREATE(CCircleDrawingMFCApplicationDoc, CDocument)

BEGIN_MESSAGE_MAP(CCircleDrawingMFCApplicationDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CCircleDrawingMFCApplicationDoc

CCircleDrawingMFCApplicationDoc::CCircleDrawingMFCApplicationDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CCircleDrawingMFCApplicationDoc::~CCircleDrawingMFCApplicationDoc()
{
}

BOOL CCircleDrawingMFCApplicationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}

// Сериализация CCircleDrawingMFCApplicationDoc

void CCircleDrawingMFCApplicationDoc::Serialize(CArchive& ar)
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

BOOL CCircleDrawingMFCApplicationDoc::OpenDocument(const CString& filePath)
{
	CFile file(filePath, CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	Serialize(ar);
	SetModifiedFlag(FALSE);
	return TRUE;
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CCircleDrawingMFCApplicationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CCircleDrawingMFCApplicationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CCircleDrawingMFCApplicationDoc::SetSearchContent(const CString& value)
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

// Диагностика CCircleDrawingMFCApplicationDoc

#ifdef _DEBUG
void CCircleDrawingMFCApplicationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCircleDrawingMFCApplicationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CCircleDrawingMFCApplicationDoc

void CCircleDrawingMFCApplicationDoc::AddCircle(int x, int y, int radius)
{
	Circle circle;
	circle.x = x;
	circle.y = y;
	circle.radius = radius;

	// Генерация случайного цвета окружности
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);
	circle.color = RGB(dis(gen), dis(gen), dis(gen)); // Задайте случайный цвет окружности

	m_circles.push_back(circle);
}

void CCircleDrawingMFCApplicationDoc::RemoveLastCircle()
{
	if (!m_circles.empty())
		m_circles.pop_back();
}

void CCircleDrawingMFCApplicationDoc::RemoveAllCircles()
{
	m_circles.clear();
}

const std::vector<CCircleDrawingMFCApplicationDoc::Circle>& CCircleDrawingMFCApplicationDoc::GetCircles() const
{
	return m_circles;
}
