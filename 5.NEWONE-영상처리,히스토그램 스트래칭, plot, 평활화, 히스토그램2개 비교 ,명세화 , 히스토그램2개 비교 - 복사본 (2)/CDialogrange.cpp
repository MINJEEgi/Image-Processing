// CDialogrange.cpp: 구현 파일
//

#include "pch.h"
#include "NEWONE.h"
#include "afxdialogex.h"
#include "CDialogrange.h"


// CDialogrange 대화 상자

IMPLEMENT_DYNAMIC(CDialogrange, CDialogEx)

CDialogrange::CDialogrange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_Input1(0)
	, m_Input2(0)
{

}

CDialogrange::~CDialogrange()
{
}

void CDialogrange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Input1);
	DDX_Text(pDX, IDC_EDIT2, m_Input2);
}


BEGIN_MESSAGE_MAP(CDialogrange, CDialogEx)
END_MESSAGE_MAP()


// CDialogrange 메시지 처리기
