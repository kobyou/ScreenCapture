
// AutoScrShotDlg.h : header file
//

#pragma once


// CAutoScrShotDlg dialog
class CAutoScrShotDlg : public CDialogEx {
	// Construction
public:
	CAutoScrShotDlg(CWnd* pParent = nullptr);	// standard constructor

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOSCRSHOT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAutoShot();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void AutoStart();
	void CancelAutoStart();
public:
	BOOL m_bAutoSreShot;
	//BOOL m_bManuSreShot;
	BOOL m_bEnAutoSreShot;
	DWORD  m_dIntervalTime;
	afx_msg void OnSettingEnableAutoShot();
	afx_msg void OnIntervaltime5s();
	afx_msg void OnIntervalTime10s();
	afx_msg void OnIntervalTime20s();
	afx_msg void OnIntervalTime30s();
	afx_msg void OnIntervalTime60s();
	afx_msg void OnIntervalTime5m();
	afx_msg void OnIntervalTime10m();
	afx_msg void OnIntervalTime20m();
	afx_msg void OnIntervalTime30m();
	afx_msg void OnIntervalTime1H();
	afx_msg void OnIntervalTime2H();
	afx_msg void OnSettingMinWindow();
	afx_msg void OnSettingExit();
};
