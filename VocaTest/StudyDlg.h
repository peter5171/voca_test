#pragma once


// StudyDlg 대화 상자

class StudyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StudyDlg)

public:
	StudyDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~StudyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STUDY};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_sInsert;
	CString m_sQuestion;
	HTREEITEM selectNode;
	HTREEITEM day1;
	HTREEITEM day2;
	
	afx_msg void OnClickedButtonSinsert();
	virtual BOOL OnInitDialog();
	int m_Qstridx;
	CEdit m_SInsert;
	afx_msg void OnLvnItemchangedListSanwer(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_SListcontrol;
};
