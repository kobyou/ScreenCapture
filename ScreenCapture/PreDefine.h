#ifndef  PREDEFINE_H
#define  PREDEFINE_H

//pos&size
const int    SCREEN_X = GetSystemMetrics(SM_CXSCREEN);
const int    SCREEN_Y = GetSystemMetrics(SM_CYSCREEN);
const POINT  ZERO_PT = {0, 0};

const RectX SCREEN_RC(0, 0, SCREEN_X, SCREEN_Y);
const RectX ZERO_RC(ZERO_PT, ZERO_PT);

const RectX TOOLWND_RC(0, 0, 341, 28);  //工具栏窗口大小
const RectX TOOLBAR_RC(1, 1, 340, 27);  //工具栏大小
const RectX COLORWND_RC(0, 0, 240, 34); //颜色选择框
const RectX EDITWND_RC(0, 0, 140, 28);  //工具栏窗口大小
//RGB
const DWORD COLOR_SCRAWL = RGB(50, 150, 255);
const DWORD COLOR_RCSEL  = RGB(51, 153, 255);


const double PI = 3.1415926;


//filter name
const TCHAR* const  FILTERNAME_ARR[] = {_T(".bmp"), _T(".jpg"), _T(".png")};
const TCHAR* const  ENCODERFORMART_ARR[] = {_T("image/bmp"), _T("image/jpeg"), _T("image/png")};

//color
const COLORREF PEN_COLOR[] = {RGB(0, 0, 0), RGB(127, 129, 130), RGB(128, 0, 0),
                              RGB(127, 128, 0), RGB(0, 128, 1), RGB(1, 0, 128),
                              RGB(255, 255, 255), RGB(192, 192, 192), RGB(255, 1, 1),
                              RGB(255, 255, 0), RGB(0, 255, 0), RGB(0, 0, 254)
                             };

//user msg
#define  SCMSG_RECAP        WM_USER + 1
#define  SCMSG_SAVEIMAGE    WM_USER + 2
#define  SCMSG_TEXT			WM_USER + 3
#define  SCMSG_RECTANGLE    WM_USER + 4
#define  SCMSG_ELLIPSE      WM_USER + 5
#define  SCMSG_ARROWLINE    WM_USER + 6
#define  SCMSG_SCRAWL       WM_USER + 7
#define  SCMSG_HIGHLIGHT    WM_USER + 8
#define  SCMSG_UNDO         WM_USER + 9
#define  SCMSG_REDO         WM_USER + 10
#define  SCMSG_CANCEL       WM_USER + 11
#define  SCMSG_FINISH       WM_USER + 12

#define  SCMSG_PENSIZE_CHANGE      WM_USER + 13
#define  SCMSG_PENCOLOR_CHANGE     WM_USER + 14

//工具栏命令
#define  IDM_RECAP       0
#define  IDM_SAVE        1
#define  IDM_TEXT        2
#define  IDM_RECT        3
#define  IDM_ELLIPSE     4
#define  IDM_ARROW       5
#define  IDM_SCRAWL      6
#define  IDM_HIGHLIGHT   7
#define  IDM_UNDO        8
#define  IDM_REDO        9
#define  IDM_CANCEL      10
#define  IDM_FINISH      11

#endif