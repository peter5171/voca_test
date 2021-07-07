
// VocaTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "VocaTest.h"
#include "VocaTestDlg.h"
#include "afxdialogex.h"
#include<cstring>
#include<locale> //파일에서 한글 문자열 깨짐 해결
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "StudyDlg.h"
#include "TestDlg.h"
#include "MGameDlg.h"



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVocaTestDlg 대화 상자



CVocaTestDlg::CVocaTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VOCATEST_DIALOG, pParent)
	, m_hDay1(NULL)
	, m_hDay2(NULL)
	, m_hRoot(NULL)
	, m_hSelectedNode(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVocaTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DAY, m_treeControl);
}

BEGIN_MESSAGE_MAP(CVocaTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_STUDY, &CVocaTestDlg::OnClickedButtonStudy)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CVocaTestDlg::OnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_MINI, &CVocaTestDlg::OnClickedButtonMini)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DAY, &CVocaTestDlg::OnSelchangedTreeDay)
END_MESSAGE_MAP()


// CVocaTestDlg 메시지 처리기

BOOL CVocaTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	std::locale::global(std::locale("Korean")); //파일에서 한글 문자열 깨짐 해결
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다. 
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_hRoot = m_treeControl.InsertItem(TEXT("Voca"), 0, 0, TVI_ROOT, TVI_LAST);
	m_hDay1 = m_treeControl.InsertItem(TEXT("Day1"), 0, 0, m_hRoot, TVI_LAST);
	m_hDay2 = m_treeControl.InsertItem(TEXT("Day2"), 0, 0, m_hRoot, TVI_LAST);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CVocaTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CVocaTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CVocaTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVocaTestDlg::OnClickedButtonStudy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//단어 학습 버튼을 누르면 단어 학습 대화상자를 띄운다
	StudyDlg* pDlg = new StudyDlg;
	pDlg->Create(IDD_DIALOG_STUDY);
	pDlg->ShowWindow(SW_SHOW);

	//pDlg->DestroyWindow();
	//pDlg = NULL;
}


void CVocaTestDlg::OnClickedButtonTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//테스트  버튼을 누르면 단어 테스트 대화상자를 띄운다
	TestDlg* pDlg = new TestDlg;
	pDlg->Create(IDD_DIALOG_TEST);
	pDlg->ShowWindow(SW_SHOW);

	//pDlg->DestroyWindow();
	//pDlg = NULL;
}


void CVocaTestDlg::OnClickedButtonMini()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MGameDlg* pDlg = new MGameDlg;
	pDlg->Create(IDD_DIALOG_MGAME);
	pDlg->ShowWindow(SW_SHOW);

	//pDlg->DestroyWindow();
	//pDlg = NULL;
}


void CVocaTestDlg::OnSelchangedTreeDay(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_hSelectedNode = pNMTreeView->itemNew.hItem;

	CStdioFile file; //CStdioFile 선언
	CFileException e; //파일 오류
	CString str; // 파일의 내용을 저장할 문자열
	int i = 0; //파일의 크기
	if (m_hSelectedNode == m_hDay1) { //Day1이 선택됐을 때

		//파일을 연다 (읽어올 파일의 이름) 읽어올 모드(읽기, 쓰기) 파일의 형식(text)
		if (file.Open(_T("Day1.txt"), CFile::modeReadWrite | CFile::typeText)) { //파일을 열었으면.
			//파일의 끝까지
			while (file.ReadString(str)) {
				//구분자를 기준으로 문자열을 분리해서 각각 배열에 저장
				AfxExtractSubString(m_strA[i], str, 0, '|');
				AfxExtractSubString(m_strQ[i], str, 1, '|');
				i++;
			}
		
		}
		else {
			e.ReportError();

		}

	}

	if (m_hSelectedNode == m_hDay2) { //Day1이 선택됐을 때

		//파일을 연다 (읽어올 파일의 이름) 읽어올 모드(읽기, 쓰기) 파일의 형식(text)
		if (file.Open(_T("Day2.txt"), CFile::modeReadWrite | CFile::typeText)) { //파일을 열었으면.
			//파일의 끝까지
			while (file.ReadString(str)) {
				//구분자를 기준으로 문자열을 분리해서 각각 배열에 저장
				AfxExtractSubString(m_strA[i], str, 0, '|');
				AfxExtractSubString(m_strQ[i], str, 1, '|');
				i++;
			}

		}
		else {
			e.ReportError();

		}

	}
	*pResult = 0;
}
