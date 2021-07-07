// TestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "VocaTest.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "VocaTestDlg.h"
#include<algorithm>

// TestDlg 대화 상자

IMPLEMENT_DYNAMIC(TestDlg, CDialogEx)

TestDlg::TestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEST, pParent)
	, m_TQuestion(_T(""))
	, m_Qstridx(0)
	, m_tInsert(_T(""))
	, m_TPoint(_T(""))
	, m_Qpoint(0)
{

}

TestDlg::~TestDlg()
{
}

void TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TQUESTION, m_TQuestion);
	DDX_Control(pDX, IDC_EDIT_TINSERT, m_TInsert);
	DDX_Control(pDX, IDC_LIST_TANWER, m_TListcontrol);
	DDX_Text(pDX, IDC_EDIT_TINSERT, m_tInsert);
	DDX_Text(pDX, IDC_EDIT_QPOINT, m_TPoint);
}


BEGIN_MESSAGE_MAP(TestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TINSERT, &TestDlg::OnClickedButtonTinsert)
END_MESSAGE_MAP()


// TestDlg 메시지 처리기


BOOL TestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	LPWSTR list[3] = { _T("문제"), _T("정답"), _T("채점") };
	int    nWidth[3] = { 66, 65 ,50 };

	//list Control의 칼럼을 설정
	for (int i = 0; i < 3; i++) {
		m_TListcontrol.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);
	}
	m_Qstridx = 0;
	CString strQ[100];
	std::copy(((CVocaTestDlg*)GetParent())->m_strQ, ((CVocaTestDlg*)GetParent())->m_strQ + 100, strQ);
	m_TQuestion.SetString(strQ[0].GetString());
	SetDlgItemInt(IDC_EDIT_QPOINT, m_Qpoint); //점수를 점수 에디트 박스에 출력

	UpdateData(FALSE); // 대화상자의 컨트롤에 데이터를 출력
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TestDlg::OnClickedButtonTinsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strQ[100]; //VocaTest 다일로그의 m_strQ배열을 저장하기 위한 배열
	CString strA[100]; //VocaTest 다일로그의 m_strA배열을 저장하기 위한 배열
	CString insert = _T("");

	m_TInsert.GetWindowText(insert); //에디트 박스에 입력한 문자열을 가져온다.
	//Vocatest의 CString 배열을 StudyDlg의 CString 배열에 복사하여 저장
	std::copy(((CVocaTestDlg*)GetParent())->m_strQ, ((CVocaTestDlg*)GetParent())->m_strQ + 100, strQ);
	std::copy(((CVocaTestDlg*)GetParent())->m_strA, ((CVocaTestDlg*)GetParent())->m_strA + 100, strA);

	//strA에 있는 정답과 입력한 문자열을 비교한다.
	if (strA[m_Qstridx].CollateNoCase(insert) == 0) {
		//리스트 컨트롤에 정답과 문자 체점이 출력된다.
		m_TListcontrol.InsertItem(m_Qstridx, strQ[m_Qstridx]);
		m_TListcontrol.SetItem(m_Qstridx, 1, LVIF_TEXT, strA[m_Qstridx], 0, 0, 0, 0);
		m_TListcontrol.SetItem(m_Qstridx, 2, LVIF_TEXT, _T("o"), 0, 0, 0, 0);
		//다음 문제와 정답으로 갱신
		m_Qstridx++; // strQ,strA의 인덱스 값을 증가 시켜준다.
		m_TQuestion.SetString(strQ[m_Qstridx]); //다음 문제를 출력해준다.
		m_tInsert.Empty(); //입력 에디트 박스를 빈칸으로 만들어줌
		m_Qpoint += 5;		
		SetDlgItemInt(IDC_EDIT_QPOINT, m_Qpoint); //점수를 점수 에디트 박스에 출력
		//학습이 종료돼면 점수가 나오고 메세지박스의 OK를 누르면 점수가 사라짐
		
	}
	else {
		//리스트 컨트롤에 정답과 문자 체점이 출력된다.
		m_TListcontrol.InsertItem(m_Qstridx, strQ[m_Qstridx]);
		m_TListcontrol.SetItem(m_Qstridx, 1, LVIF_TEXT, strA[m_Qstridx], 0, 0, 0, 0);
		m_TListcontrol.SetItem(m_Qstridx, 2, LVIF_TEXT, _T("x"), 0, 0, 0, 0);
		//다음 문제와 정답으로 갱신
		m_Qstridx++; // strQ,strA의 인덱스 값을 증가 시켜준다.
		m_TQuestion.SetString(strQ[m_Qstridx]); //다음 문제를 출력해준다.
		m_tInsert.Empty(); //입력 에디트 박스를 빈칸으로 만들어줌
	}
	
	if (strA[m_Qstridx].CollateNoCase(_T("@")) == 0) {
		MessageBox(_T("모든 학습이 끝나셨습니다."), _T("잠깐"), MB_OK);
	}
	Invalidate();
	UpdateData(FALSE);
}
