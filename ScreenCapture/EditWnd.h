#ifndef  EDITWND_H
#define  EDITWND_H
#include "WndImpl.hpp"
#include "RectEx.hpp"

class CEditWnd : public CWndImpl {
public:
	CEditWnd();
	~CEditWnd();

public:
	LPCTSTR  GetWindowClassName() const;
	void Initialize(void);
	void CreateEditWnd(HWND hWnd,  CRectEx rect);
	HDC GetHDC() const;
	HWND GetSafeHwnd() const;
private:
	//HBRUSH m_hBrushBk;
	HWND m_hEditWnd;
	HMODULE  m_hRichEditDll;
};

#endif