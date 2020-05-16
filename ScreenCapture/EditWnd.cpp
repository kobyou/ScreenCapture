#include "stdafx.h"
#include "EditWnd.h"

CEditWnd::CEditWnd()
{
	m_hEditWnd = NULL;
	m_hRichEditDll = NULL;
}

CEditWnd::~CEditWnd()
{
	if(NULL != m_hEditWnd) {
		::DestroyWindow(m_hEditWnd);
		m_hEditWnd = NULL;
	}
	if(NULL != m_hRichEditDll) {
		FreeLibrary(m_hRichEditDll);
		m_hRichEditDll = NULL;
	}
}

LPCTSTR CEditWnd::GetWindowClassName() const
{
	return _T("CEditWnd");
}

void CEditWnd::Initialize()
{
	InitCommonControls();
}

void CEditWnd::CreateEditWnd(HWND hWnd, CRectEx rect)
{
	if(m_hEditWnd == NULL) {
		DWORD dStyleEx = WS_CHILD | ES_MULTILINE | ES_WANTRETURN | WS_VISIBLE;
		//DWORD dStyleEx = WS_CHILD | WS_VISIBLE | WS_BORDER;
#if 1
		m_hEditWnd = CreateWindow(_T("edit"), NULL, dStyleEx,
		                          rect.leftX, rect.topX, rect.GetW(), rect.GetH(), hWnd, NULL, NULL, NULL);
#else
		m_hRichEditDll = LoadLibrary(_T("RICHED20.dll"));
		m_hEditWnd = Create(hWnd, TEXT("RichEdit20A"), NULL,
		                    WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_NOHIDESEL, rect);
#endif
		//SetTextColor((HDC)m_hEditWnd, RGB(255, 0, 0));
		Initialize();
	}
	SetFocus(m_hEditWnd);
}

HWND CEditWnd::GetSafeHwnd() const
{
	return this == NULL ? NULL : m_hEditWnd;
}