// MGameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "VocaTest.h"
#include "MGameDlg.h"
#include "afxdialogex.h"
#include "VocaTestDlg.h"
#include<algorithm> 

// MGameDlg 대화 상자

IMPLEMENT_DYNAMIC(MGameDlg, CDialogEx)

MGameDlg::MGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MGAME, pParent)
	, m_mInsert(_T(""))
	, m_MQuestion(_T(""))
	, m_Qstridx(0)
	, m_Qpoint(0)
{

}

MGameDlg::~MGameDlg()
{
}

void MGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MINSERT, m_MInsert);
	DDX_Text(pDX, IDC_EDIT_MINSERT, m_mInsert);
	DDX_Text(pDX, IDC_EDIT_MQUESTION, m_MQuestion);
	DDX_Control(pDX, IDC_LIST_MANWER, m_MListcontrol);
}


BEGIN_MESSAGE_MAP(MGameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MINSERT, &MGameDlg::OnClickedButtonMinsert)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MSTRAT, &MGameDlg::OnClickedButtonMstrat)
END_MESSAGE_MAP()


// MGameDlg 메시지 처리기


BOOL MGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	LPWSTR list[3] = { _T("문제"), _T("정답"), _T("채점") };
	int    nWidth[3] = { 66, 65 ,50 };

	//list Control의 칼럼을 설정
	for (int i = 0; i < 3; i++) {
		m_MListcontrol.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);
	}
	m_Qstridx = 0;
	CString strQ[100];
	std::copy(((CVocaTestDlg*)GetParent())->m_strQ, ((CVocaTestDlg*)GetParent())->m_strQ + 100, strQ);
	m_MQuestion.SetString(strQ[0].GetString());
	
	UpdateData(FALSE); // 대화상자의 컨트롤에 데이터를 출력
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MGameDlg::OnClickedButtonMinsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	CString strQ[100]; //VocaTest 다일로그의 m_strQ배열을 저장하기 위한 배열
	CString strA[100]; //VocaTest 다일로그의 m_strA배열을 저장하기 위한 배열
	CString insert = _T(""); //에디트 박스의 문자열을 저장하기 위한 변수

	m_MInsert.GetWindowText(insert); //에디트 박스에 입력한 문자열을 가져온다.
	//Vocatest의 CString 배열을 StudyDlg의 CString 배열에 복사하여 저장
	std::copy(((CVocaTestDlg*)GetParent())->m_strQ, ((CVocaTestDlg*)GetParent())->m_strQ + 100, strQ);
	std::copy(((CVocaTestDlg*)GetParent())->m_strA, ((CVocaTestDlg*)GetParent())->m_strA + 100, strA);

	//strA에 있는 정답과 입력한 문자열을 비교한다.
	if (strA[m_Qstridx].CollateNoCase(insert) == 0) {
		//리스트 컨트롤에 정답과 문자 체점이 출력된다.
		m_MListcontrol.InsertItem(m_Qstridx, strQ[m_Qstridx]);
		m_MListcontrol.SetItem(m_Qstridx, 1, LVIF_TEXT, strA[m_Qstridx], 0, 0, 0, 0);
		m_MListcontrol.SetItem(m_Qstridx, 2, LVIF_TEXT, _T("o"), 0, 0, 0, 0);
		//다음 문제와 정답으로 갱신
		m_Qstridx++; // strQ,strA의 인덱스 값을 증가 시켜준다.
		m_MQuestion.SetString(strQ[m_Qstridx]); //다음 문제를 출력해준다.
		m_mInsert.Empty(); //입력 에디트 박스를 빈칸으로 만들어줌
		m_Qpoint += 5; //맞으면 점수를 증가시킨다.
		SetDlgItemInt(IDC_EDIT_MPOINT, m_Qpoint); //점수를 점수 에디트 박스에 출력
		//학습이 종료돼면 점수가 나오고 메세지박스의 OK를 누르면 점수가 사라짐
		KillTimer(0); //미니게임이 끝나면 타이머 종료
	}
	else {
		//리스트 컨트롤에 정답과 문자 체점이 출력된다.
		m_MListcontrol.InsertItem(m_Qstridx, strQ[m_Qstridx]);
		m_MListcontrol.SetItem(m_Qstridx, 1, LVIF_TEXT, strA[m_Qstridx], 0, 0, 0, 0);
		m_MListcontrol.SetItem(m_Qstridx, 2, LVIF_TEXT, _T("x"), 0, 0, 0, 0);
		//다음 문제와 정답으로 갱신
		m_Qstridx++; // strQ,strA의 인덱스 값을 증가 시켜준다.
		m_MQuestion.SetString(strQ[m_Qstridx]); //다음 문제를 출력해준다.
		m_mInsert.Empty(); //입력 에디트 박스를 빈칸으로 만들어줌
	}
	//메모장에 단어가 끝나면 @으로 표시해서 strA가 @이면 종료
	if (strA[m_Qstridx].CollateNoCase(_T("@")) == 0) {
		if (AfxMessageBox(_T("미니 게임이 끝났습니다."),
			MB_YESNO | MB_ICONINFORMATION) == IDYES) {
			KillTimer(0); //미니게임이 끝나면 타이머 종료
		}
		
	}
	SetTimer(0, 10000, NULL); // 이벤트 아이디 0, 10000ms(10초)
	Invalidate();
	UpdateData(FALSE);
}


void MGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//UpdateData(TRUE);
	CString strQ[100];
	CString strA[100];
	std::copy(((CVocaTestDlg*)GetParent())->m_strQ, ((CVocaTestDlg*)GetParent())->m_strQ + 100, strQ);
	std::copy(((CVocaTestDlg*)GetParent())->m_strA, ((CVocaTestDlg*)GetParent())->m_strA + 100, strA);
	
	m_Qstridx++;
	//시간초가 지나면 틀린것으로 간주해서 리스트 박스에 틀렸다고 출력
	m_MListcontrol.InsertItem(m_Qstridx, strQ[m_Qstridx-1]);
	SetDlgItemText(IDC_EDIT_MQUESTION, strQ[m_Qstridx]); //10초가 지나면 문제가 바뀐다.
	m_mInsert.Empty(); //입력 에디트 박스를 빈칸으로 만들어줌
	Invalidate();
	//UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void MGameDlg::OnClickedButtonMstrat()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//시작 버튼을 누르면 타이머가 시작된다.
	m_Qpoint = 0;
	m_Qstridx = 0;
	if (AfxMessageBox(_T("미니게임을 시작하시겠습니까?"),
		MB_YESNO | MB_ICONQUESTION) == IDYES) {
		SetTimer(0, 10000, NULL); // 이벤트 아이디 0, 10000ms(10초)
	}

}
