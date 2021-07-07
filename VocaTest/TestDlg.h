#pragma once


// TestDlg 대화 상자

class TestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TestDlg)

public:
	TestDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TestDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_TQuestion;
	afx_msg void OnClickedButtonTinsert();
	int m_Qstridx;
	CEdit m_TInsert;
	CListCtrl m_TListcontrol;
	CString m_tInsert;
	int m_Qpoint;
	CString m_TPoint;
};
