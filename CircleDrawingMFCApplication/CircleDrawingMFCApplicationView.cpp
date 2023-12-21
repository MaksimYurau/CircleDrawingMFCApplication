
// CircleDrawingMFCApplicationView.cpp: реализация класса CCircleDrawingMFCApplicationView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "CircleDrawingMFCApplication.h"
#endif

#include "CircleDrawingMFCApplicationDoc.h"
#include "CircleDrawingMFCApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCircleDrawingMFCApplicationView

IMPLEMENT_DYNCREATE(CCircleDrawingMFCApplicationView, CView)

BEGIN_MESSAGE_MAP(CCircleDrawingMFCApplicationView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCircleDrawingMFCApplicationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CCircleDrawingMFCApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Добавьте код обработчика сообщений или вызов стандартного обработчика
	CCircleDrawingMFCApplicationDoc* pDoc = GetDocument();
	pDoc->AddCircle(point.x, point.y, 50); // Добавление окружности с начальным радиусом 50 в документ
	SetCapture(); // Захватываем мышь для отслеживания движения мыши

	CPoint startPoint = point; // Запоминаем начальную точку
	bool isDrawing = true; // Устанавливаем флаг рисования окружности

	// Регистрируем начальную точку и флаг рисования в хранилище окружностей
	pDoc->SetDrawingData(startPoint, isDrawing);

	CView::OnLButtonDown(nFlags, point);
}

void CCircleDrawingMFCApplicationView::OnMouseMove(UINT nFlags, CPoint point)
{
	CCircleDrawingMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Получаем данные о рисовании окружности из хранилища
	CPoint startPoint;
	bool isDrawing;
	pDoc->GetDrawingData(startPoint, isDrawing);

	if (isDrawing)
	{
		// Рассчитываем расстояние между начальной точкой и текущей позицией курсора
		int dx = point.x - startPoint.x;
		int dy = point.y - startPoint.y;
		int radius = static_cast<int>(sqrt(dx * dx + dy * dy)); // Вычисляем расстояние

		// Обновляем радиус окружности
		pDoc->UpdateCircleRadius(radius);

		// Перерисовываем представление
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}

void CCircleDrawingMFCApplicationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// Освобождаем захваченную мышь
	ReleaseCapture();

	CCircleDrawingMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Устанавливаем флаг рисования окружности в false
	pDoc->SetDrawingData(CPoint(0, 0), false);

	CView::OnLButtonUp(nFlags, point);
}

void CCircleDrawingMFCApplicationView::OnDraw(CDC* pDC)
{
	CCircleDrawingMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте код отрисовки для своего документа
	// Пример кода для рисования окружности
	for (const auto& circle : pDoc->GetCircles()) {
		int centerX = circle.x; // координата X центра окружности
		int centerY = circle.y; // координата Y центра окружности
		int radius = circle.radius;   // радиус окружности

		// Создание кисти с заданным цветом окружности
		CBrush brush(circle.color);
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		pDC->Ellipse(centerX - radius, centerY - radius, centerX + radius, centerY + radius);

		// Восстановление предыдущей кисти
		pDC->SelectObject(pOldBrush);
	}
}

void CCircleDrawingMFCApplicationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CCircleDrawingMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (nChar == VK_BACK)
	{
		// Удаляем последнюю нарисованную окружность
		pDoc->RemoveLastCircle();

		// Перерисовываем вид
		Invalidate();
	}
	else if (nChar == VK_DELETE)
	{
		// Удаляем все окружности
		pDoc->RemoveAllCircles();

		// Перерисовываем вид
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Создание или уничтожение CCircleDrawingMFCApplicationView

CCircleDrawingMFCApplicationView::CCircleDrawingMFCApplicationView() noexcept
{
	// TODO: добавьте код создания

}

CCircleDrawingMFCApplicationView::~CCircleDrawingMFCApplicationView()
{
}

BOOL CCircleDrawingMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CCircleDrawingMFCApplicationView

// Печать CCircleDrawingMFCApplicationView


void CCircleDrawingMFCApplicationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCircleDrawingMFCApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CCircleDrawingMFCApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CCircleDrawingMFCApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CCircleDrawingMFCApplicationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCircleDrawingMFCApplicationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CCircleDrawingMFCApplicationView

#ifdef _DEBUG
void CCircleDrawingMFCApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CCircleDrawingMFCApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCircleDrawingMFCApplicationDoc* CCircleDrawingMFCApplicationView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCircleDrawingMFCApplicationDoc)));
	return (CCircleDrawingMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CCircleDrawingMFCApplicationView
