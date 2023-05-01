
// NEWONEDoc.cpp: CNEWONEDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "NEWONE.h"
#endif

#include "NEWONEDoc.h"

#include <propkey.h>
#include "CDialogrange.h"
#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CNEWONEDoc

IMPLEMENT_DYNCREATE(CNEWONEDoc, CDocument)

BEGIN_MESSAGE_MAP(CNEWONEDoc, CDocument)
END_MESSAGE_MAP()


// CNEWONEDoc 생성/소멸

CNEWONEDoc::CNEWONEDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CNEWONEDoc::~CNEWONEDoc()
{
}

BOOL CNEWONEDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CNEWONEDoc serialization

void CNEWONEDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CNEWONEDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CNEWONEDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CNEWONEDoc::SetSearchContent(const CString& value)
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

// CNEWONEDoc 진단

#ifdef _DEBUG
void CNEWONEDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNEWONEDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNEWONEDoc 명령


BOOL CNEWONEDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary); // 파일을 오픈할건데 어디에있어? mode : 읽기만하고나서 열어줘 


	if (File.GetLength() == 32 * 32) { //width, height에 대한 정보를 미리준다. 
		m_height = 32;
		m_width = 32;
	}
	else if (File.GetLength() == 64 * 64) {
		m_height = 64;
		m_width = 64;
	}
	else if (File.GetLength() == 128 * 128) {
		m_height = 128;
		m_width = 128;
	}
	else if (File.GetLength() == 256 * 256) {
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) {
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) {
		m_height = 480;
		m_width = 640;
	}
	else if (File.GetLength() == 176 * 144) {
		m_height = 144;
		m_width = 176;
	}
	else if (File.GetLength() == 176 * 216) {
		m_height = 216;
		m_width = 176;
	}
	//if 문중에 하나를 가져와 : 중복되는데이터는없어 하나의 데이터에 할당이될거야 --> input이미지 버프의 크기를 할당할 수 있어 어떤거를 
	//로딩하겠다고 결정햇고 사이즈도 할당이 되었기 때문에 가능하다 
	else {
		AfxMessageBox(L"Not Support Image Size", MB_OK | MB_ICONEXCLAMATION);
		//다른형식의 파일은 사용할 수 ㅇ없다 . (예외처리)
		return 0;
	}
	//m_width m_hight 결정
	m_size = m_width * m_height; // 전체 바이트 수가 나온다. 실제 할당해야할 메모리사이즈 
	m_InputImage = new unsigned char[m_size]; // 영상의 크기만큼 버퍼를 주고 inpute

	for (int i = 0; i < m_size; i++) // 배열에 대한 초기화 초기화 세팅 : 꼭 안해도돼 --> 정확한 사이즈를 불러올거기때문에 
		m_InputImage[i] = 255;
	File.Read(m_InputImage, m_size); // 읽으면돼 READ 여기의 버프에러가 m_size만큼 읽어들어라 실제 영상데이터가 들어가는 곳
	File.Close(); //항상 다 읽어들이고 나면 close를 해야한다.


	return TRUE;
}


void CNEWONEDoc::OnBinarization()
{
	//기본이진화 코드 , m_OutputImage에 저장했어. 
	int i, value;
	m_size = m_height * m_width;
	m_Re_size = m_size;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_OutputImage = new unsigned char[m_size];
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		if (value > 128)
			m_OutputImage[i] = (char)128;
		else
			m_OutputImage[i] = (char)50;
	}
}


void CNEWONEDoc::OnRanging()
{
	int i, value;
	m_size = m_height * m_width;
	m_Re_size = m_size;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_OutputImage = new unsigned char[m_size];
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		if (value >= 0 && value <= 20) { // 0 과 p1사이 구간에서의 영상처리 
			m_OutputImage[i] = m_InputImage[i] / 2; // 더 밝아짐. contrast는 낮음
		}
		else if (value >= 20 && value <= 250) { // p1과 p2사이 구간에서의 영상처리 
			m_OutputImage[i] = 2 * m_InputImage[i] - 150; // 더 밝아지면서 선명해짐 . contrast 높음
		}
		else { //p2이상 구간에서의 영상처리
			m_OutputImage[i] = m_InputImage[i];
		}
	}
}


void CNEWONEDoc::OnInversion()
{
	int i, value;
	m_size = m_height * m_width;
	m_Re_size = m_size;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_OutputImage = new unsigned char[m_size];



	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];

		m_OutputImage[i] = (unsigned)(-value + 255); //y=-x+255 , 실제 output은 실제 잘라주는 역할 (unsigned가 좋음)

	}

}


void CNEWONEDoc::OnBinarization2()
{
	CDialogrange dlg; //클래스 객체를 받아옴

	int i, value;
	m_size = m_height * m_width;
	m_Re_size = m_size;
	m_Re_height = m_Re_height;
	m_Re_width = m_width;
	m_OutputImage = new unsigned char[m_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++) {
			value = (int)m_InputImage[i];
			if (value > dlg.m_Input1) {
				m_OutputImage[i] = (char)255;
			}
			else
				m_OutputImage[i] = (char)50;
		}

	}
}


void CNEWONEDoc::OnBinarization3()
{
	CDialogrange dlg;
	 
	int i, value;
	m_size = m_height * m_width;
	m_Re_size = m_size;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_OutputImage = new unsigned char[m_size];

	if (dlg.DoModal() == IDOK)
	{

		for (i = 0; i < m_size; i++) {
			value = (int)m_InputImage[i];
			if (value >= dlg.m_Input1 && value <= dlg.m_Input2) {
				m_OutputImage[i] = (char)255;
			}
			else
				m_OutputImage[i] = m_InputImage[i];
		}
	}
}

//히스토그램 스트래칭 구현하는 코드
void CNEWONEDoc::OnHistoStretch()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	LOW= 0;
	HIGH = 255;
	//최소값, 최대값을 찾기 위한 초기값
	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	//입력 영상의 최소값 찾기
	for (i = 0; i < m_size; i++) { //m_size만큼 전체 배열을 순회하면서 
		if (m_InputImage[i] < MIN) //각 원소의 값과 현재까지의 최소값 (MIN)을 비교하면서
			MIN = m_InputImage[i]; // 더 작은 값을 MIN변수에 대입
	}
	//입력 영상의 최대값 찾기 
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	//출력 영상 버퍼 할당 
	m_OutputImage = new unsigned char[m_Re_size];

	//히스토그램 스트레칭
	for (i = 0; i < m_size; i++) 
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * HIGH / (MAX - MIN));
	
}


void CNEWONEDoc::OnHistogram()
{
	//히스토그램의 값은 0~255
	//히스토그램의 크기 값을 MAX=255로 정규화하여 출력
	//히스토그램의 크기 : 256*256 지정
	int i, j, value;
	unsigned char LOW, HIGH;
	double MAX, MIN, DIF;

	m_Re_height = 256;
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	
	//초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;
	
	//빈도수 조사 : 히스토그램 생성
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	//정규화 max min 값을 찾기
	MAX = m_HIST[0];
	MIN = m_HIST[0];
	for (i = 0; i < 256; i++) {
		if (m_HIST[i] > MAX)
			MAX = m_HIST[i];
	}
	for (i = 0; i < 256; i++) {
		if (m_HIST[i] <MIN)
			MIN = m_HIST[i];
	}
	DIF = MAX - MIN;
	
	//정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);
	//정규화된 히스토그램 출력
	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];//색 밴드를 넣기 위해서 아래에 여백을 넣어줌
	for (i = 0; i < 256; i++)
		m_OutputImage[i] = 255; //배경화면은 하얀색

	//정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현 x축은 밝기값, y축은 빈도수
	for (i = 0; i < 256; i++) {//모든 밝기값에 대해 반복
		for (j = 0; j < m_Scale_HIST[i]; j++) {
			m_OutputImage[m_Re_width * (m_Re_height - j - 1) + i] = 0;
		}
	}//y축 위치를 (m_Re_height - j - 1) x축 위치를 i로저장하고 검은 점을 그리는 것이다. 
	
	 //히스토그램을 출력하고 그 아래부분에 히스토그램의 색을 표시
	for (i = m_Re_height; i < m_Re_width + 5; i++) {
		for (j = 0; j < 256; j++)
		{
			m_OutputImage[m_Re_height * i + j] = 255;
		} 
	}
	for (i = m_Re_height + 5; i < m_Re_height + 20; i++) {
		for (j = 0; j < 256; j++)
		{
			m_OutputImage[m_Re_height * i + j] = j;
		}
	}
	//ondraw에서 다시 맞추어 주기 위해
	m_Re_height = m_Re_height + 20;
	m_Re_size=m_Re_height*m_Re_width;
}



void CNEWONEDoc::OnHistoequal()
{
	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;
	// 빈도 수 조사: 히스토그램 생성 //
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	// 누적 히스토그램 생성
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}
	m_OutputImage = new unsigned char[m_Re_size];
	// 입력 영상을 평활화된 영상으로 출력
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	// TODO: 여기에 구현 코드 추가.
}


void CNEWONEDoc::OnHistohisto()
{
//첫번째 영상처리//히스토그램 스트레칭하는 코드//

	int i, value2;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;
	// 빈도 수 조사: 히스토그램 생성 //
	for (i = 0; i < m_size; i++) {
		value2 = (int)m_InputImage[i];
		m_HIST[value2]++;
	}
	// 누적 히스토그램 생성
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}
	m_OutputImage = new unsigned char[m_Re_size];
	// 입력 영상을 평활화된 영상으로 출력
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}

//두번째 이미지 - 원본이미지의 히스토그램 출력
	//히스토그램의 값은 0~255
	//히스토그램의 크기 값을 MAX=255로 정규화하여 출력
	//히스토그램의 크기 : 256*256 지정

	int k, j, value;
	double MAX1, MIN1, DIF;

	m_Re_height1 = 256;
	m_Re_width1 = 256;
	m_Re_size1 = m_Re_height1 * m_Re_width1;
	
	//초기화
	for (k = 0; k < 256; k++)
		m_HIST[k] = LOW;

	//빈도수 조사 : 히스토그램 생성
	for (k = 0; k < m_size; k++) {
		value = (int)m_InputImage[k];
		m_HIST[value]++;
	}
	//정규화 max min 값을 찾기
	MAX1 = m_HIST[0];
	MIN1 = m_HIST[0];
	for (k = 0; k < 256; k++) {
		if (m_HIST[k] > MAX1)
			MAX1 = m_HIST[k];
	}
	for (k = 0; k < 256; k++) {
		if (m_HIST[k] < MIN1)
			MIN1 = m_HIST[k];
	}
	DIF = MAX1 - MIN1;

	//정규화된 히스토그램
	for (k = 0; k < 256; k++)
		m_Scale_HIST[k] = (unsigned char)((m_HIST[k] - MIN1) * HIGH / DIF);
	//정규화된 히스토그램 출력
	m_OutputImage1 = new unsigned char[m_Re_size1 + (256 * 20)];//색 밴드를 넣기 위해서 아래에 여백을 넣어줌
	for (k = 0; k < 256; k++)
		m_OutputImage1[k] = 255; //배경화면은 하얀색

	//정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현 x축은 밝기값, y축은 빈도수
	for (k = 0; k < 256; k++) {//모든 밝기값에 대해 반복
		for (j = 0; j < m_Scale_HIST[k]; j++) {
			m_OutputImage1[m_Re_width1 * (m_Re_height1 - j - 1) + k] = 0;
		}
	}//y축 위치를 (m_Re_height - j - 1) x축 위치를 i로저장하고 검은 점을 그리는 것이다. 

	 //히스토그램을 출력하고 그 아래부분에 히스토그램의 색을 표시
	for (k = m_Re_height1; k < m_Re_width1 + 5; k++) {
		for (j = 0; j < 256; j++)
		{
			m_OutputImage1[m_Re_height1 * k + j] = 255;
		}
	}
	for (k = m_Re_height1 + 5; k < m_Re_height1 + 20; k++) {
		for (j = 0; j < 256; j++)
		{
			m_OutputImage1[m_Re_height1 * k + j] = j;
		}
	}
	//ondraw에서 다시 맞추어 주기 위해
	m_Re_height1 = m_Re_height1 + 20;
	m_Re_size1 = m_Re_height1 * m_Re_width1;

//영상처리 후 히스토그램 가져오기 
	int a, b, value1;
	double MAX2, MIN2, DIF1;

	m_Re_height2 = 256;
	m_Re_width2 = 256;
	m_Re_size2 = m_Re_height2 * m_Re_width2;

	//초기화
	for (a = 0; a < 256; a++)
		m_HIST1[a] = LOW;

	//빈도수 조사 : 히스토그램 생성
	for (a = 0; a < m_size; a++) {
		value1 = (int)m_OutputImage[a];
		m_HIST1[value1]++;
	}
	//정규화 max min 값을 찾기
	MAX2 = m_HIST1[0];
	MIN2 = m_HIST1[0];
	for (a = 0; a < 256; a++) {
		if (m_HIST1[a] > MAX2)
			MAX2 = m_HIST1[a];
	}
	for (a = 0; a < 256; a++) {
		if (m_HIST1[a] < MIN2)
			MIN2 = m_HIST1[a];
	}
	DIF1 = MAX2 - MIN2;

	//정규화된 히스토그램
	for (a = 0; a < 256; a++)
		m_Scale_HIST1[a] = (unsigned char)((m_HIST1[a] - MIN2) * HIGH / DIF1);
	//정규화된 히스토그램 출력
	m_OutputImage2 = new unsigned char[m_Re_size2 + (256 * 20)];//색 밴드를 넣기 위해서 아래에 여백을 넣어줌
	for (a = 0; a < 256; a++)
		m_OutputImage2[a] = 255; //배경화면은 하얀색

	//정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현 x축은 밝기값, y축은 빈도수
	for (a = 0; a < 256; a++) {//모든 밝기값에 대해 반복
		for (b = 0; b < m_Scale_HIST1[a]; b++) {
			m_OutputImage2[m_Re_width2 * (m_Re_height2 - b - 1) + a] = 0;
		}
	}//y축 위치를 (m_Re_height - j - 1) x축 위치를 i로저장하고 검은 점을 그리는 것이다. 

	 //히스토그램을 출력하고 그 아래부분에 히스토그램의 색을 표시
	for (a = m_Re_height2; a < m_Re_width2 + 5; a++) {
		for (b = 0; b < 256; b++)
		{
			m_OutputImage2[m_Re_height2 * a + b] = 255;
		}
	}
	for (a = m_Re_height2 + 5; a < m_Re_height2 + 20; a++) {
		for (b = 0; b < 256; b++)
		{
			m_OutputImage2[m_Re_height2 * a + b] = b;
		}
	}
	//ondraw에서 다시 맞추어 주기 위해
	m_Re_height2 = m_Re_height2 + 20;
	m_Re_size2 = m_Re_height2 * m_Re_width2;


}



void CNEWONEDoc::OnHistospec()
{
	int i, value, Dvalue, top, bottom, DADD;
	unsigned char* m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];
	unsigned char LOW, HIGH, Temp, * m_Org_Temp;
	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
	double DMAX, DMIN;
	top = 255;
	bottom = top - 1;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_Org_Temp = new unsigned char[m_size];
	CFile File;
	CFileDialog OpenDlg(TRUE);

	// 원하는 히스토그램이 있는 영상을 입력받음
    m_DTEMP = new unsigned char[m_size]; 
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_size) {
			
			File.Read(m_DTEMP, m_size);
			File.Close();
		}
		else {
			AfxMessageBox(L"Image size not matched");
			// 같은 크기의 영상을 대상으로 함
			return;
		}
	}

	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
		m_DHIST[i] = LOW;
		m_TABLE[i] = LOW;
	}
	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];
		m_DHIST[Dvalue]++;
	}
	// 누적 히스토그램 조사
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
		DSUM += m_DHIST[i];
		m_Sum_Of_DHIST[i] = DSUM;
	}
	// 원본 영상의 평활화
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	// 누적 히스토그램에서 최소값과 최대값 지정
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];
	// 원하는 영상을 평활화 //
	for (i = 0; i < 256; i++) {
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i]
			- DMIN) * HIGH / (DMAX - DMIN));
	}
	// 룩업테이블을 이용한 명세화 //
	for (; ; ) {
		for (i = m_Sum_Of_ScHIST[bottom];
			i <= m_Sum_Of_ScHIST[top]; i++) {
			m_TABLE[i] = top;
		}
		top = bottom;
		bottom = bottom - 1;
		if (bottom < -1)
			break;
	}
	for (i = 0; i < m_size; i++) {
		DADD = (int)m_Org_Temp[i];
		m_OutputImage[i] = m_TABLE[DADD];
	}

}


void CNEWONEDoc::OnHistohisto2()
{
/// 히스토그램 명세화 -> m_OutputImage
	int i, value, Dvalue, top, bottom, DADD;
	unsigned char* m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];
	unsigned char LOW, HIGH, Temp, * m_Org_Temp;
	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
	double DMAX, DMIN;
	top = 255;
	bottom = top - 1;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_Org_Temp = new unsigned char[m_size];
	CFile File;
	CFileDialog OpenDlg(TRUE);

	// 원하는 히스토그램이 있는 영상을 입력받음
	m_DTEMP = new unsigned char[m_size];
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_size) {

			File.Read(m_DTEMP, m_size);
			File.Close();
		}
		else {
			AfxMessageBox(L"Image size not matched");
			// 같은 크기의 영상을 대상으로 함
			return;
		}
	}

	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
		m_DHIST[i] = LOW;
		m_TABLE[i] = LOW;
	}
	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];
		m_DHIST[Dvalue]++;
	}
	// 누적 히스토그램 조사
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
		DSUM += m_DHIST[i];
		m_Sum_Of_DHIST[i] = DSUM;
	}
	// 원본 영상의 평활화
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	// 누적 히스토그램에서 최소값과 최대값 지정
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];
	// 원하는 영상을 평활화 //
	for (i = 0; i < 256; i++) {
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i]- DMIN) * HIGH / (DMAX - DMIN));
	}
	// 룩업테이블을 이용한 명세화 //
	for (; ; ) {
		for (i = m_Sum_Of_ScHIST[bottom];
			i <= m_Sum_Of_ScHIST[top]; i++) {
			m_TABLE[i] = top;
		}
		top = bottom;
		bottom = bottom - 1;
		if (bottom < -1)
			break;
	}
	for (i = 0; i < m_size; i++) {
		DADD = (int)m_Org_Temp[i];
		m_OutputImage[i] = m_TABLE[DADD];
	}

/// 원본 이미지 히스토그램 출력-> ㅡm_OutputImage1

	int  j, value1;
	double MAX1, MIN1, DIF;

	m_Re_height1 = 256;
	m_Re_width1 = 256;
	m_Re_size1 = m_Re_height1 * m_Re_width1;

	//초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	//빈도수 조사 : 히스토그램 생성
	for (i = 0; i < m_size; i++) {
		value1 = (int)m_InputImage[i];
		m_HIST[value1]++;
	}
	//정규화 max min 값을 찾기
	MAX1 = m_HIST[0];
	MIN1 = m_HIST[0];
	for (i = 0; i < 256; i++) {
		if (m_HIST[i] > MAX1)
			MAX1 = m_HIST[i];
	}
	for (i = 0; i < 256; i++) {
		if (m_HIST[i] < MIN1)
			MIN1 = m_HIST[i];
	}
	DIF = MAX1 - MIN1;

	//정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN1) * HIGH / DIF);
	//정규화된 히스토그램 출력
	m_OutputImage1 = new unsigned char[m_Re_size1 + (256 * 20)];//색 밴드를 넣기 위해서 아래에 여백을 넣어줌
	for (i = 0; i < 256; i++)
		m_OutputImage1[i] = 255; //배경화면은 하얀색

	//정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현 x축은 밝기값, y축은 빈도수
	for (i = 0; i < 256; i++) {//모든 밝기값에 대해 반복
		for (j = 0; j < m_Scale_HIST[i]; j++) {
			m_OutputImage1[m_Re_width1 * (m_Re_height1 - j - 1) + i] = 0;
		}
	}//y축 위치를 (m_Re_height - j - 1) x축 위치를 i로저장하고 검은 점을 그리는 것이다. 

	 //히스토그램을 출력하고 그 아래부분에 히스토그램의 색을 표시
	for (i = m_Re_height1; i < m_Re_width1 + 5; i++) {
		for (j = 0; j < 256; j++)
		{
			m_OutputImage1[m_Re_height1 * i + j] = 255;
		}
	}
	for (i = m_Re_height1 + 5; i < m_Re_height1 + 20; i++) {
		for (j = 0; j < 256; j++)
		{
			m_OutputImage1[m_Re_height1 * i + j] = j;
		}
	}
	//ondraw에서 다시 맞추어 주기 위해
	m_Re_height1 = m_Re_height1 + 20;
	m_Re_size1 = m_Re_height1 * m_Re_width1;

///명세화된 영상의 히스토그램 출력 --> m_OutputImage2
	int value2;
	double MAX2, MIN2, DIF1;

	m_Re_height2 = 256;
	m_Re_width2 = 256;
	m_Re_size2 = m_Re_height2 * m_Re_width2;

	//초기화
	for (i = 0; i < 256; i++)
		m_HIST1[i] = LOW;

	//빈도수 조사 : 히스토그램 생성
	for (i = 0; i < m_size; i++) {
		value2 = (int)m_OutputImage[i];
		m_HIST1[value2]++;
	}
	//정규화 max min 값을 찾기
	MAX2 = m_HIST1[0];
	MIN2 = m_HIST1[0];
	for (i = 0; i < 256; i++) {
		if (m_HIST1[i] > MAX2)
			MAX2 = m_HIST1[i];
	}
	for (i = 0; i< 256; i++) {
		if (m_HIST1[i] < MIN2)
			MIN2 = m_HIST1[i];
	}
	DIF1 = MAX2 - MIN2;

	//정규화된 히스토그램
	for (i= 0; i < 256; i++)
		m_Scale_HIST1[i] = (unsigned char)((m_HIST1[i] - MIN2) * HIGH / DIF1);
	//정규화된 히스토그램 출력
	m_OutputImage2 = new unsigned char[m_Re_size2 + (256 * 20)];//색 밴드를 넣기 위해서 아래에 여백을 넣어줌
	for (i = 0; i < 256; i++)
		m_OutputImage2[i] = 255; //배경화면은 하얀색

	//정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현 x축은 밝기값, y축은 빈도수
	for (i = 0; i < 256; i++) {//모든 밝기값에 대해 반복
		for (j = 0; j < m_Scale_HIST1[i]; j++) {
			m_OutputImage2[m_Re_width2 * (m_Re_height2 - j - 1) + i] = 0;
		}
	}//y축 위치를 (m_Re_height - j - 1) x축 위치를 i로저장하고 검은 점을 그리는 것이다. 

	 //히스토그램을 출력하고 그 아래부분에 히스토그램의 색을 표시
	for (i = m_Re_height2; i < m_Re_width2 + 5; i++) {
		for (j = 0; j < 256; j++)
		{
			m_OutputImage2[m_Re_height2 * i + j] = 255;
		}
	}
	for (i = m_Re_height2 + 5; i < m_Re_height2 + 20; i++) {
		for (j = 0; j < 256; j++)
		{
			m_OutputImage2[m_Re_height2 * i + j] = j;
		}
	}
	//ondraw에서 다시 맞추어 주기 위해
	m_Re_height2 = m_Re_height2 + 20;
	m_Re_size2 = m_Re_height2 * m_Re_width2;

}
