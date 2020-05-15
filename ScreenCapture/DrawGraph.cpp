#include "DrawGraph.hpp"
#include "GlobalAPI.h"

using namespace GlobalAPI;

void GraphText::DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn /* = SCREEN_RC */)
{

	//CString str(_T("Hello world..."));
	CString str(_T("Hello world..."));
	HFONT  hFont = CreateFont(        //����һ���Զ�������
	                   20,             //����ĸ߶ȣ������С��
	                   0,              //��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ
	                   0,              //�ı�����б��Ϊ0����ʾˮƽ
	                   0,              //�������б��Ϊ0
	                   FW_NORMAL,      //����Ĵֶȣ�FW_NORMALΪ����  FW_HEAVYΪ���
	                   0,              //��б����
	                   0,              //���»���
	                   0,              //��ɾ����
	                   GB2312_CHARSET, //��ʾ���õ��ַ���ΪANSI_CHARSET
	                   OUT_DEFAULT_PRECIS, //�������Ϊȱʡ����
	                   CLIP_DEFAULT_PRECIS,    //���þ���Ϊȱʡ����
	                   DEFAULT_QUALITY,        //�������Ϊȱʡֵ
	                   DEFAULT_PITCH | FF_DONTCARE,//�ּ�������ϵ��ʹ��ȱʡֵ
	                   L"����"             //��������
	               );
	SetTextColor(hDC, dwPenColor);  //�����ı���ɫΪ��ɫ
	//SetBkColor(hDC, TRANSPARENT);  //���ñ�����ɫ
	SelectObject(hDC, hFont);      //���Զ�������ѡ���豸����

	TextOutW(hDC, ptStart.x, ptStart.y, m_strText, wcslen(m_strText));//ʹ�õ�ǰ��������ı�

	TextOutW(hDC, ptStart.x, ptStart.y, str, wcslen(str));//ʹ�õ�ǰ��������ı�

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

	int hOldROP = SetROP2(hDC, R2_MASKPEN); //ӫ���

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

