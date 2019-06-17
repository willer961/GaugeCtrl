////////////////////////////////////////////////////////////////////////////////
//
// 文件名称：ColorStatic.cpp
// 功    能：静态文本框
//
// 作    者：邓智宏
// 完成日期：2017-1-13
//
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ColorStatic.h"


// CColorStatic

IMPLEMENT_DYNAMIC(CColorStatic, CStatic)

CColorStatic::CColorStatic()
{

}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CColorStatic 消息处理程序



void CColorStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	CRect rc;
	GetClientRect(&rc);
	dc.Rectangle(&rc);
	dc.FillSolidRect(&rc, m_clr);
}


void CColorStatic::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CStatic::PreSubclassWindow();
	DWORD dwStyle = GetStyle();  
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle | SS_OWNERDRAW);
}

