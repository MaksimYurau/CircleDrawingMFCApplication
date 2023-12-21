
// CircleDrawingMFCApplicationDoc.h: интерфейс класса CCircleDrawingMFCApplicationDoc 
//


#pragma once

#include <vector>
#include <afxwin.h> 
#include <random> 

class CCircleDrawingMFCApplicationDoc : public CDocument
{
protected: // создать только из сериализации
	CCircleDrawingMFCApplicationDoc() noexcept;
	DECLARE_DYNCREATE(CCircleDrawingMFCApplicationDoc)

// Атрибуты
public:
	struct Circle
	{
		int x;
		int y;
		int radius;
		COLORREF color; // Поле для хранения цвета окружности
	};

	void AddCircle(int x, int y, int radius);
	void RemoveLastCircle();
	void RemoveAllCircles();
	const std::vector<Circle>& GetCircles() const;

private:
	CPoint m_startPoint; // Начальная точка рисования окружности
	bool m_isDrawing;    // Флаг рисования окружности
	std::vector<Circle> m_circles;
// Операции
public:
	void SetDrawingData(const CPoint& startPoint, bool isDrawing)
	{
		m_startPoint = startPoint;
		m_isDrawing = isDrawing;
	}

	void GetDrawingData(CPoint& startPoint, bool& isDrawing)
	{
		startPoint = m_startPoint;
		isDrawing = m_isDrawing;
}

	void UpdateCircleRadius(int radius)
	{
		std::vector<Circle>& circles = m_circles;
		if (!circles.empty())
		{
			Circle& lastCircle = circles.back();
			lastCircle.radius = radius;
		}
	}
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
	virtual ~CCircleDrawingMFCApplicationDoc();
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
