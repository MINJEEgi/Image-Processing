
// NEWONEDoc.h: CNEWONEDoc 클래스의 인터페이스
//


#pragma once


class CNEWONEDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CNEWONEDoc() noexcept;
	DECLARE_DYNCREATE(CNEWONEDoc)

// 특성입니다.
public:
	int m_width;//영상의 가로 크기
	int m_height;//영상의 세로 크기
	int m_size;//영상 데이터 전체 바이트 수
	int m_Re_width;
	int m_Re_height;
	int m_Re_size;
	int m_Re_width1; //히스토그램그릴때 
	int m_Re_height1;
	int m_Re_size1;
	int m_Re_width2; //히스토그램그릴때 
	int m_Re_height2;
	int m_Re_size2;
	unsigned char* m_InputImage;//입력 영상 버퍼
	unsigned char* m_OutputImage;//출력 영상 버퍼
	unsigned char* m_OutputImage1;//영상처리 전 히스토그램
	unsigned char* m_OutputImage2;//영상처리 후 히스토그램 

	double m_HIST[256]; //0~255 픽셀값에 대한 빈도수를 저장
	double m_Sum_Of_HIST[256]; //각 픽셀값에 대한 누적 빈도수를 저장
	unsigned char m_Scale_HIST[256]; //0~255 픽셀값에 대한 그래프 상의 높이를 저장
	//m_Scale_HIST 값은 m_HIST을 일정 비율로 스케일링한 값
	//이렇게 계산된 m_Scale_HIST배열에 저장된 값을 그래프의 높이로 해서 i에 해당하는 픽셀값을
	//그래프 가로축에 대응시킨다. 
	double m_HIST1[256]; //0~255 픽셀값에 대한 빈도수를 저장
	double m_Sum_Of_HIST1[256]; //각 픽셀값에 대한 누적 빈도수를 저장
	unsigned char m_Scale_HIST1[256];
	unsigned char* m_DTEMP;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CNEWONEDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	void OnBinarization();
	void OnRanging();
	void OnInversion();
	void OnBinarization2();
	void OnBinarization3();
	void OnHistoStretch();
	void OnHistogram();
	void OnHistoequal();
	void OnHistohisto();
	void OnHistospec();
	void OnHistohisto2();
};
