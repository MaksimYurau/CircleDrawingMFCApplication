
// CircleDrawingMFCApplicationView.h: интерфейс класса CCircleDrawingMFCApplicationView
//

#pragma once


class CCircleDrawingMFCApplicationView : public CView
{
protected: // создать только из сериализации
	CCircleDrawingMFCApplicationView() noexcept;
	DECLARE_DYNCREATE(CCircleDrawingMFCApplicationView)

// Атрибуты
public:
	CCircleDrawingMFCApplicationDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CCircleDrawingMFCApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// afx_msg void OnDraw(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в CircleDrawingMFCApplicationView.cpp
inline CCircleDrawingMFCApplicationDoc* CCircleDrawingMFCApplicationView::GetDocument() const
   { return reinterpret_cast<CCircleDrawingMFCApplicationDoc*>(m_pDocument); }
#endif

