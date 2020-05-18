#include "stdafx.h"
#include "ScrnCapWnd.h"
#include <shellapi.h>

extern char * wchar2char(const wchar_t* wchar);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, _T("ScreenCapture"));
	if(GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hMutex);
		return -1;
	}

	LPWSTR *argv;
	int argc;
	BOOL bScrShot = FALSE;
	argv = CommandLineToArgvW(GetCommandLine(), &argc);
	if(argv == NULL) {
		return 10;
	}
	else {
		for(int i = 0; i < argc; i++) {
			if(strcmp(wchar2char(argv[i]), wchar2char(_T("--fullscrshot"))) == 0) {
				bScrShot = TRUE;
				break;
			}
		}
	}

	CWndImpl::SetInstance(hInstance);
	CScrnCapWnd* pScrnCap = new CScrnCapWnd(bScrShot);
	pScrnCap->Create(NULL, _T("ScrnCap"), WS_POPUP | WS_VISIBLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW, SCREEN_RC);
	UpdateWindow(pScrnCap->GetSafeHwnd());

	if(bScrShot) {
		pScrnCap->SetFullScrShot(bScrShot);
		pScrnCap->FullScreen();
		pScrnCap->Finish();
	}
	LocalFree(argv);

	CWndImpl::MsgLoop();

	CloseHandle(hMutex);

	return 0;
}
