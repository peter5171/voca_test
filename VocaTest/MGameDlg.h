#pragma once


// MGameDlg 대화 상자

class MGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MGameDlg)

public:
	MGameDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MGameDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MGAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_MInsert;
	CString m_mInsert;
	CString m_MQuestion;
	CListCtrl m_MListcontrol;
	afx_msg void OnClickedButtonMinsert();
	int m_Qpoint;
	int m_Qstridx;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedButtonMstrat();
};
