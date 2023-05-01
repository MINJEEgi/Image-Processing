
// NEWONEView.h: CNEWONEView 클래스의 인터페이스
//

#pragma once


class CNEWONEView : public CView
{
protected: // serialization에서만 만들어집니다.
	CNEWONEView() noexcept;
	DECLARE_DYNCREATE(CNEWONEView)

// 특성입니다.
public:
	CNEWONEDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CNEWONEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBasicbinary();
	afx_msg void OnRanging();
	afx_msg void OnInversion();
	afx_msg void OnDialog();
	afx_msg void OnDialog2();
	afx_msg void OnHistostrech();
	afx_msg void OnHistogram();
	afx_msg void OnHistoequal();
	afx_msg void OnHistohisto();
	afx_msg void OnHistospec();
	afx_msg void OnHistohisto2();
};

#ifndef _DEBUG  // NEWONEView.cpp의 디버그 버전
inline CNEWONEDoc* CNEWONEView::GetDocument() const
   { return reinterpret_cast<CNEWONEDoc*>(m_pDocument); }
#endif

