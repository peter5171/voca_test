
// VocaTestDlg.h: 헤더 파일
//

#pragma once


// CVocaTestDlg 대화 상자
class CVocaTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CVocaTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VOCATEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeControl;
	HTREEITEM m_hRoot;
	HTREEITEM m_hDay1;
	HTREEITEM m_hDay2;
	HTREEITEM m_hSelectedNode;
	afx_msg void OnClickedButtonStudy();
	afx_msg void OnClickedButtonTest();
	afx_msg void OnClickedButtonMini();
	afx_msg void OnSelchangedTreeDay(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_strQ[100];
	CString m_strA[100];
	CString m_VocaList[200];
};
