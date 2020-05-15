#include "DrawGraph.hpp"
#include "GlobalAPI.h"

using namespace GlobalAPI;

void GraphText::DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn /* = SCREEN_RC */)
{

	//CString str(_T("Hello world..."));
	CString str(_T("Hello world..."));
	HFONT  hFont = CreateFont(        //创建一个自定义字体
	                   20,             //字体的高度（字体大小）
	                   0,              //由系统根据高宽比选取字体最佳宽度值
	                   0,              //文本的倾斜度为0，表示水平
	                   0,              //字体的倾斜度为0
	                   FW_NORMAL,      //字体的粗度，FW_NORMAL为正常  FW_HEAVY为最粗
	                   0,              //非斜体字
	                   0,              //无下划线
	                   0,              //无删除线
	                   GB2312_CHARSET, //表示所用的字符集为ANSI_CHARSET
	                   OUT_DEFAULT_PRECIS, //输出精度为缺省精度
	                   CLIP_DEFAULT_PRECIS,    //剪裁精度为缺省精度
	                   DEFAULT_QUALITY,        //输出质量为缺省值
	                   DEFAULT_PITCH | FF_DONTCARE,//字间距和字体系列使用缺省值
	                   L"宋体"             //字体名称
	               );
	SetTextColor(hDC, dwPenColor);  //设置文本颜色为蓝色
	//SetBkColor(hDC, TRANSPARENT);  //设置背景颜色
	SelectObject(hDC, hFont);      //将自定义字体选入设备环境

	TextOutW(hDC, ptStart.x, ptStart.y, m_strText, wcslen(m_strText));//使用当前字体输出文本

	TextOutW(hDC, ptStart.x, ptStart.y, str, wcslen(str));//使用当前字体输出文本

	DeleteObject(hFont);

	//HPEN hPen = CreatePen(PS_SOLID, nPenWidth, dwPenColor);
	//HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);

	//LOGBRUSH  LogBrush;
	//LogBrush.lbStyle = BS_NULL;
	//HBRUSH hBrush = CreateBrushIndirect(&LogBrush);
	//HBRUSH hOldbrush = (HBRUSH)::SelectObject(hDC, hBrush);

	//RectX rcGraph(ptStart, ptEnd);
	//rcGraph.ResetStartEnd();
	//if(rcGraph.OutOfBoundary(rcRgn)) {
	//	rcGraph.ResetBoundary(rcRgn);
	//}

	//RectangleX(hDC, rcGraph);

	//SelectObject(hDC, hOldPen);
	//SelectObject(hDC, hOldbrush);
	//DeleteObject(hPen);
	//DeleteObject(hBrush);
}

void GraphRectangle::DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn /* = SCREEN_RC */)
{
	HPEN hPen = CreatePen(PS_SOLID, nPenWidth, dwPenColor);
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);

	LOGBRUSH  LogBrush;
	LogBrush.lbStyle = BS_NULL;
	HBRUSH hBrush = CreateBrushIndirect(&LogBrush);
	HBRUSH hOldbrush = (HBRUSH)::SelectObject(hDC, hBrush);

	RectX rcGraph(ptStart, ptEnd);
	rcGraph.ResetStartEnd();
	if(rcGraph.OutOfBoundary(rcRgn)) {
		rcGraph.ResetBoundary(rcRgn);
	}

	RectangleX(hDC, rcGraph);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldbrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void GraphEllipse::DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn /* = SCREEN_RC */)
{
	HPEN hPen = CreatePen(PS_SOLID, nPenWidth, dwPenColor);
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);

	LOGBRUSH  LogBrush;
	LogBrush.lbStyle = BS_NULL;
	HBRUSH hBrush = CreateBrushIndirect(&LogBrush);
	HBRUSH hOldbrush = (HBRUSH)::SelectObject(hDC, hBrush);

	RectX rcGraph(ptStart, ptEnd);
	rcGraph.ResetStartEnd();
	if(rcGraph.OutOfBoundary(rcRgn)) {
		rcGraph.ResetBoundary(rcRgn);
	}

	EllipseX(hDC, rcGraph);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldbrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void GraphArrowLine::DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn /* = SCREEN_RC */)
{
	ptEnd.x = ptEnd.x < rcRgn.leftX ? rcRgn.leftX : ptEnd.x;
	ptEnd.x = ptEnd.x > rcRgn.rightX ? rcRgn.rightX : ptEnd.x;
	ptEnd.y = ptEnd.y < rcRgn.topX ? rcRgn.topX : ptEnd.y;
	ptEnd.y = ptEnd.y > rcRgn.bottomX ? rcRgn.bottomX : ptEnd.y;

	double xAngleLine = 0;
	if(ptStart.x == ptEnd.x)
		xAngleLine = PI / 2;
	else {
		xAngleLine = atan((double(ptEnd.y) - double(ptStart.y)) / (double(ptEnd.x) - double(ptStart.x)));
	}
	POINT ptLineLeft;
	if(ptStart.x > ptEnd.x) {
		ptLineLeft.x = long(ptEnd.x + cos(xAngleLine + PI / 8) * 11.0);
		ptLineLeft.y = long(ptEnd.y + sin(xAngleLine + PI / 8) * 11.0);
	}
	else if(ptStart.x == ptEnd.x) {
		if(ptStart.y > ptEnd.y) {
			ptLineLeft.x = long(ptEnd.x + cos(xAngleLine + PI / 8) * 11.0);
			ptLineLeft.y = long(ptEnd.y + sin(xAngleLine + PI / 8) * 11.0);
		}
		else if(ptStart.y == ptEnd.y) {
			return ;
		}
		else {
			ptLineLeft.x = long(ptEnd.x - cos(xAngleLine + PI / 8) * 11.0);
			ptLineLeft.y = long(ptEnd.y - sin(xAngleLine + PI / 8) * 11.0);
		}
	}
	else {
		ptLineLeft.x = long(ptEnd.x - cos(xAngleLine + PI / 8) * 11.0);
		ptLineLeft.y = long(ptEnd.y - sin(xAngleLine + PI / 8) * 11.0);
	}
	POINT ptLineRight;
	if(ptStart.x > ptEnd.x) {
		ptLineRight.x = long(ptEnd.x + cos(xAngleLine - PI / 8) * 11.0);
		ptLineRight.y = long(ptEnd.y + sin(xAngleLine - PI / 8) * 11.0);
	}
	else if(ptStart.x == ptEnd.x) {
		if(ptStart.y > ptEnd.y) {
			ptLineRight.x = long(ptEnd.x + cos(xAngleLine - PI / 8) * 11.0);
			ptLineRight.y = long(ptEnd.y + sin(xAngleLine - PI / 8) * 11.0);
		}
		else if(ptStart.y > ptEnd.y) {
			return ;
		}
		else {
			ptLineRight.x = long(ptEnd.x - cos(xAngleLine - PI / 8) * 11.0);
			ptLineRight.y = long(ptEnd.y - sin(xAngleLine - PI / 8) * 11.0);
		}
	}
	else {
		ptLineRight.x = long(ptEnd.x - cos(xAngleLine - PI / 8) * 11.0);
		ptLineRight.y = long(ptEnd.y - sin(xAngleLine - PI / 8) * 11.0);
	}
	HPEN hPen = ::CreatePen(PS_SOLID, nPenWidth, dwPenColor);
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = dwPenColor;
	HBRUSH hBrush = ::CreateBrushIndirect(&logBrush);
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);
	// Draw line
	::MoveToEx(hDC, ptStart.x, ptStart.y, NULL);
	::LineTo(hDC, ptEnd.x, ptEnd.y);
	// Draw arrow
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, hBrush);
	POINT ptPolygon[3] = {ptEnd.x, ptEnd.y, ptLineLeft.x, ptLineLeft.y, ptLineRight.x, ptLineRight.y};
	::Polygon(hDC, ptPolygon, 3);
	::SelectObject(hDC, hOldBrush);
	::SelectObject(hDC, hOldPen);
	::DeleteObject(hBrush);
	::DeleteObject(hPen);

}

void GraphScrawl::DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn /* = SCREEN_RC */)
{
	HPEN hPen = CreatePen(PS_SOLID, nPenWidth, dwPenColor);
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);

	MoveToEx(hDC, ptStart.x, ptStart.y, NULL);
	LineTo(hDC, ptEnd.x, ptEnd.y);

	::SelectObject(hDC, hOldPen);
	::DeleteObject(hPen);
}

void GraphHighlight::DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn /* = SCREEN_RC */)
{
	HPEN hPen = CreatePen(PS_SOLID, nPenWidth, dwPenColor);
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);

	int hOldROP = SetROP2(hDC, R2_MASKPEN); //荧光笔

	MoveToEx(hDC, ptStart.x, ptStart.y, NULL);
	LineTo(hDC, ptEnd.x, ptEnd.y);

	::SetROP2(hDC, hOldROP);

	::SelectObject(hDC, hOldPen);
	::DeleteObject(hPen);
}

IGraph* GraphFactory::CreateGraph(int graphID, CString str)
{
	IGraph* pGraph = NULL;
	switch(graphID) {
		default:
			break;
		case 2:
			pGraph = new GraphText(str);
			break;
		case 3:
			pGraph = new GraphRectangle();
			break;
		case 4:
			pGraph = new GraphEllipse();
			break;
		case 5:
			pGraph = new GraphArrowLine();
			break;
		case 6:
			pGraph = new GraphScrawl();
			break;
		case 7:
			pGraph = new GraphHighlight();
			break;
	}

	return pGraph;
}

