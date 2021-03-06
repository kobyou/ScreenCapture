
// AutoScrShotDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoScrShot.h"
#include "AutoScrShotDlg.h"
#include "afxdialogex.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx {
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
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


// CAutoScrShotDlg dialog



CAutoScrShotDlg::CAutoScrShotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTOSCRSHOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bAutoSreShot = FALSE;
	//m_bManuSreShot = FALSE;
	m_bEnAutoSreShot = FALSE;
	m_dIntervalTime = 20; //10s
}

void CAutoScrShotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAutoScrShotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_AUTO_SHOT, &CAutoScrShotDlg::OnBnClickedButtonAutoShot)
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_SETTING_ENABLEAUTOSHOT, &CAutoScrShotDlg::OnSettingEnableAutoShot)
	ON_COMMAND(ID_INTERVALTIME_5SECOND, &CAutoScrShotDlg::OnIntervaltime5s)
	ON_COMMAND(ID_INTERVALTIME_10SECOND, &CAutoScrShotDlg::OnIntervalTime10s)
	ON_COMMAND(ID_INTERVALTIME_20SECOND, &CAutoScrShotDlg::OnIntervalTime20s)
	ON_COMMAND(ID_INTERVALTIME_30SECOND, &CAutoScrShotDlg::OnIntervalTime30s)
	ON_COMMAND(ID_INTERVALTIME_60SECOND, &CAutoScrShotDlg::OnIntervalTime60s)
	ON_COMMAND(ID_INTERVALTIME_5MINUTE, &CAutoScrShotDlg::OnIntervalTime5m)
	ON_COMMAND(ID_INTERVALTIME_10MINUTE, &CAutoScrShotDlg::OnIntervalTime10m)
	ON_COMMAND(ID_INTERVALTIME_20MINUTE, &CAutoScrShotDlg::OnIntervalTime20m)
	ON_COMMAND(ID_INTERVALTIME_30MINUTE, &CAutoScrShotDlg::OnIntervalTime30m)
	ON_COMMAND(ID_INTERVALTIME_1HOUR, &CAutoScrShotDlg::OnIntervalTime1H)
	ON_COMMAND(ID_INTERVALTIME_2HOUR, &CAutoScrShotDlg::OnIntervalTime2H)
	ON_COMMAND(ID_SETTING_MINWINDOW, &CAutoScrShotDlg::OnSettingMinWindow)
	ON_COMMAND(ID_SETTING_EXIT, &CAutoScrShotDlg::OnSettingExit)
END_MESSAGE_MAP()


// CAutoScrShotDlg message handlers

BOOL CAutoScrShotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if(pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if(!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetWindowText(L"ScrShots");
	//CancelAutoStart();
	//AutoStart();
	if(m_bEnAutoSreShot) {
		ShowWindow(SW_MINIMIZE);
		SetTimer(0, m_dIntervalTime * 1000, NULL);
		GetDlgItem(IDC_BUTTON_AUTO_SHOT)->SetWindowTextW(_T("停止自动截屏"));
	}
	else {
		ShowWindow(SW_SHOWNORMAL);
		//SetTimer(0, 10000, NULL);
		GetDlgItem(IDC_BUTTON_AUTO_SHOT)->SetWindowTextW(_T("开始手动截屏"));

		CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
		menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAutoScrShotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAutoScrShotDlg::OnPaint()
{
	if(IsIconic()) {
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAutoScrShotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAutoScrShotDlg::OnBnClickedButtonAutoShot()
{
	// TODO: Add your control notification handler code here
	if(m_bEnAutoSreShot) {
		m_bAutoSreShot = !m_bAutoSreShot;
		if(m_bAutoSreShot) {
			SetTimer(0, m_dIntervalTime * 1000, NULL);
			ShowWindow(SW_MINIMIZE);
			GetDlgItem(IDC_BUTTON_AUTO_SHOT)->SetWindowTextW(_T("停止自动截屏"));
		}
		else {
			KillTimer(0);
			GetDlgItem(IDC_BUTTON_AUTO_SHOT)->SetWindowTextW(_T("开始自动截屏"));
		}
	}
	else {

		ShowWindow(SW_MINIMIZE);
		Sleep(200);
		ShellExecuteW(NULL, L"open", L"ScreenCapture.exe", NULL, NULL, SW_HIDE);
	}
}


void CAutoScrShotDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent) {
		case 0:
			ShellExecuteW(NULL, L"open", L"ScreenCapture.exe", _T("--fullscrshot"), NULL, SW_HIDE);
			break;
		case 1:
			break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CAutoScrShotDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//ShowWindow(SW_MINIMIZE);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}

// 程序开机自动启动
void CAutoScrShotDlg ::AutoStart()
{
	HKEY hKey;
	CString strRegPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//1、找到系统的启动项
	if(RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) { ///打开启动项
		//2、得到本程序自身的全路径
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);

		//3、判断注册表项是否已经存在
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, nullptr, L"AutoSrcShot", RRF_RT_REG_SZ, 0, strDir, &nLength);

		//4、已经存在
		if(result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0) {
			//5、添加一个子Key,并设置值，"GISRestart"是应用程序名字（不加后缀.exe）
			RegSetValueEx(hKey, L"AutoSrcShot", 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1) * sizeof(TCHAR));

			//6、关闭注册表
			RegCloseKey(hKey);
		}
	}
	else {
		//QMessageBox::warning(0, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("\n系统参数错误,不能随系统启动n"));
	}
}

// 取消开机自动启动
void CAutoScrShotDlg::CancelAutoStart()
{
	HKEY hKey;
	CString strRegPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//1、找到系统的启动项
	if(RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		//2、删除值
		RegDeleteValue(hKey, L"AutoSrcShot");

		//3、关闭注册表
		RegCloseKey(hKey);
	}
}


void CAutoScrShotDlg::OnSettingEnableAutoShot()
{
	// TODO: Add your command handler code here
	m_bEnAutoSreShot = !m_bEnAutoSreShot;
	//GetDlgItem(ID_SETTING_ENABLEAUTOSHOT)->SetCheck(TRUE);
	CMenu* menu = GetMenu()->GetSubMenu(0);
	if(m_bEnAutoSreShot) {
		menu->CheckMenuItem(ID_SETTING_ENABLEAUTOSHOT, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
		GetDlgItem(IDC_BUTTON_AUTO_SHOT)->SetWindowTextW(_T("开始自动截屏"));
	}
	else {
		menu->CheckMenuItem(ID_SETTING_ENABLEAUTOSHOT, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
		GetDlgItem(IDC_BUTTON_AUTO_SHOT)->SetWindowTextW(_T("开始手动截屏"));
	}
}


void CAutoScrShotDlg::OnIntervaltime5s()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 5;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}

void CAutoScrShotDlg::OnIntervalTime10s()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 10;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime20s()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 20;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime30s()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 30;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime60s()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 60;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime5m()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 300;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime10m()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 600;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime20m()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 1200;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime30m()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 1800;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime1H()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 3600;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnIntervalTime2H()
{
	// TODO: Add your command handler code here
	m_dIntervalTime = 7200;
	SetTimer(0, m_dIntervalTime * 1000, NULL);
	CMenu* menu = GetMenu()->GetSubMenu(0)->GetSubMenu(1);
	menu->CheckMenuItem(ID_INTERVALTIME_5SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_60SECOND, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_5MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_10MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_20MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_30MINUTE, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_1HOUR, MF_BYCOMMAND | MF_UNCHECKED);//通过命令ID
	menu->CheckMenuItem(ID_INTERVALTIME_2HOUR, MF_BYCOMMAND | MF_CHECKED);//通过命令ID
}


void CAutoScrShotDlg::OnSettingMinWindow()
{
	// TODO: Add your command handler code here
	ShowWindow(SW_MINIMIZE);
}


void CAutoScrShotDlg::OnSettingExit()
{
	// TODO: Add your command handler code here
	OnCancel();
}
