
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
END_MESSAGE_MAP()

void CCircleDrawingMFCApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Добавьте код обработчика сообщений или вызовстандартного обработчика
	CCircleDrawingMFCApplicationDoc* pDoc = GetDocument();
	pDoc->AddCircle(point.x, point.y); // Добавление окружности в документ
	Invalidate(); // Перерисовка представления
	CView::OnLButtonDown(nFlags, point);
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
