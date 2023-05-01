
// NEWONEView.cpp: CNEWONEView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "NEWONE.h"
#endif

#include "NEWONEDoc.h"
#include "NEWONEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNEWONEView

IMPLEMENT_DYNCREATE(CNEWONEView, CView)

BEGIN_MESSAGE_MAP(CNEWONEView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNEWONEView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BASICBINARY, &CNEWONEView::OnBasicbinary)
	ON_COMMAND(ID_RANGING, &CNEWONEView::OnRanging)
	ON_COMMAND(ID_INVERSION, &CNEWONEView::OnInversion)
	ON_COMMAND(ID_DIALOG, &CNEWONEView::OnDialog)
	ON_COMMAND(ID_DIALOG2, &CNEWONEView::OnDialog2)
	ON_COMMAND(ID_HISTOSTRECH, &CNEWONEView::OnHistostrech)
	ON_COMMAND(ID_HISTOGRAM, &CNEWONEView::OnHistogram)
	ON_COMMAND(ID_HISTOEQUAL, &CNEWONEView::OnHistoequal)
	ON_COMMAND(ID_HISTOHISTO, &CNEWONEView::OnHistohisto)
	ON_COMMAND(ID_HISTOSPEC, &CNEWONEView::OnHistospec)
	ON_COMMAND(ID_HISTOHISTO2, &CNEWONEView::OnHistohisto2)
END_MESSAGE_MAP()

// CNEWONEView 생성/소멸

CNEWONEView::CNEWONEView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CNEWONEView::~CNEWONEView()
{
}

BOOL CNEWONEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CNEWONEView 그리기

void CNEWONEView::OnDraw(CDC* pDC)
{
	CNEWONEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int i, j;
	unsigned char R, G, B;
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = G = B = pDoc->m_InputImage[i * pDoc->m_width + j];
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}
	//m_OutputImage 출력 --> 원본이미지 아래에 영상처리된 이미지 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + pDoc->m_height + 30, RGB(R, G, B));
		}
	}
	//m_OutputImage1 출력 --> 원본이미지 히스토그램 출력 -원본이미지 옆에
	for (i = 0; i < pDoc->m_Re_height1; i++) {
		for (j = 0; j < pDoc->m_Re_width1; j++) {
			R = pDoc->m_OutputImage1[i * pDoc->m_Re_width1 + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_Re_width + 10, i + 5, RGB(R, G, B));
		}
	}
	//m_OutputImage2 출력 --> 원본이미지 히스토그램 출력  -영상처리된 이미지 옆에
	for (i = 0; i < pDoc->m_Re_height2; i++) {
		for (j = 0; j < pDoc->m_Re_width2; j++) {
			R = pDoc->m_OutputImage2[i * pDoc->m_Re_width2 + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_Re_width + 10, i + pDoc->m_Re_height2 + 10, RGB(R, G, B));
		}
	}
	
}


// CNEWONEView 인쇄


void CNEWONEView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNEWONEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CNEWONEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CNEWONEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CNEWONEView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNEWONEView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNEWONEView 진단

#ifdef _DEBUG
void CNEWONEView::AssertValid() const
{
	CView::AssertValid();
}

void CNEWONEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNEWONEDoc* CNEWONEView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNEWONEDoc)));
	return (CNEWONEDoc*)m_pDocument;
}
#endif //_DEBUG


// CNEWONEView 메시지 처리기


void CNEWONEView::OnBasicbinary()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnBinarization();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);// 화면 갱신
}



void CNEWONEView::OnRanging()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnRanging();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);// 화면 갱신
}


void CNEWONEView::OnInversion()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnInversion();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);// 화면 갱신
}


void CNEWONEView::OnDialog()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnBinarization2();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);// 화면 갱신
}


void CNEWONEView::OnDialog2()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnBinarization3();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);// 화면 갱신
}


void CNEWONEView::OnHistostrech()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnHistoStretch();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);// 화면 갱신
}


void CNEWONEView::OnHistogram()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnHistogram();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);// 화면 갱신
}


void CNEWONEView::OnHistoequal()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnHistoequal();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);// 화면 갱신
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CNEWONEView::OnHistohisto()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnHistohisto();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);
}


void CNEWONEView::OnHistospec()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnHistospec();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);
}


void CNEWONEView::OnHistohisto2()
{
	CNEWONEDoc* pDoc = GetDocument();// Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnHistohisto2();// 함수 호출, 즉 Doc 클래스에 구현되어 있어야 한다.
	Invalidate(TRUE);
}
