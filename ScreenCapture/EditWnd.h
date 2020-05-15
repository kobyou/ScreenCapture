#ifndef  EDITWND_H
#define  EDITWND_H
#include "WndImpl.hpp"
#include "RectEx.hpp"
#define IDC_EDIT 1000
class CEditWnd : public CWndImpl {
public:
	CEditWnd();
	~CEditWnd();

public:
	LPCTSTR  GetWindowClassName() const;
	void Initialize(void);
	void CreateEditWnd(HWND hWnd,  CRectEx rect);
	HWND GetSafeHwnd() const;
private:
	//HBRUSH m_hBrushBk;
	HWND m_hEditWnd;
	HMODULE  m_hRichEditDll;
};

#endif