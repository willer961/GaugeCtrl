////////////////////////////////////////////////////////////////////////////////
//
// 文件名称：Pointer.cpp
// 功    能：仪表盘指针的绘制
//
// 作    者：邓智宏
// 完成日期：2017-1-13
//
////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Pointer.h"

CPointer::CPointer(void)
{
	m_clrNeedle = Color::OrangeRed;
	m_clrCap = Color::Gray;
	m_fLen = 80.0f;
	SetCapSize(10.0f);
	SetAxisSize(20.0f);
}

CPointer::~CPointer(void)
{
}

void CPointer::Draw(Graphics &gr, float fAg, PointF ptCenter)
{
	Matrix mx;
	gr.GetTransform(&mx);
	gr.TranslateTransform(ptCenter.X, ptCenter.Y);
	gr.RotateTransform(fAg);
	float fCapBorder = m_fCapSize + 2.0f;
	
	PointF pts[] ={
		PointF(m_fLen, 0),
		PointF(-m_fLen / 3, fCapBorder / 2),
		PointF(-m_fLen / 3, -fCapBorder / 2),
		PointF(m_fLen, 0)
	};
	// 指针画刷
	
	//LinearGradientBrush brNeedle(
	//	PointF(m_fLen, fCapBorder / 2),
	//	PointF(-m_fLen / 3, -fCapBorder / 2), 
	//	Color::Transparent, m_clrNeedle);

	//gr.FillPolygon(&brNeedle, pts, 4);
	gr.FillPolygon(&SolidBrush(m_clrNeedle), pts, 4);
	gr.DrawPolygon(&Pen(Color::DimGray), pts, 4);
	gr.FillEllipse(&SolidBrush(m_clrNeedle), m_rcAxis);
	GraphicsPath path;
	
	path.AddEllipse(m_rcCap);
	PathGradientBrush br(&path);
	br.SetCenterPoint(Point(0, 0));
	br.SetCenterColor(Color::White);
	int iCnt = 1;
	br.SetSurroundColors(&m_clrCap, &iCnt);
	gr.FillEllipse(&br, m_rcCap);
	gr.SetTransform(&mx);
}

void CPointer::SetCapSize(float fSize)
{
	m_fCapSize = fSize;
	m_rcCap = RectF(-m_fCapSize / 2, -m_fCapSize / 2, m_fCapSize, m_fCapSize);
}

void CPointer::SetAxisSize(float fSize)
{
	m_fAxisSize = fSize;
	m_rcAxis = RectF(-m_fAxisSize / 2, -m_fAxisSize / 2, m_fAxisSize, m_fAxisSize);
}