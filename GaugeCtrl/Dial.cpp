////////////////////////////////////////////////////////////////////////////////
//
// 文件名称：Dial.cpp
// 功    能：表盘的绘制显示
//
// 作    者：邓智宏
// 完成日期：2017-1-13
//
////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Dial.h"

CDial::CDial(void)
{
	m_clrBorder = Color::DimGray;
	m_clrFrame[0] = Color::LightGray;
	m_clrFrame[1] = Color::LightGray;
	m_clrBk[0] = Color::White;
	m_clrBk[1] = Color::LightSlateGray;
	m_fBorderWidth = 1.0f;
	m_fFrameWidth = 3;
	m_bUseImage = FALSE;
}

CDial::~CDial(void)
{
}

/******************************************************************************/
// 绘制表盘，依次绘制边界，表框和背板
// 返回值：
/******************************************************************************/
void CDial::Draw(Graphics& gr, Rect rcIn)
{

	RectF rcDraw(rcIn.GetLeft() + 0.f, rcIn.GetTop()+0.f, 
		rcIn.Width + 0.f, rcIn.Height + 0.f);

	//gr.FillRectangle(&SolidBrush(Color::White), rcDraw);
	Image *pImg = m_image.GetImage();
	if (m_bUseImage && pImg)// 使用表盘图片
	{
		int iW = pImg->GetWidth();
		int iH = pImg->GetWidth();
		gr.DrawImage(pImg, rcIn, 0, 0, iW, iH, UnitPixel);
	}
	else// 自绘表盘
	{
		// 绘制边界
		Pen penBorder(m_clrBorder, m_fBorderWidth);
		gr.DrawEllipse(&penBorder, rcDraw);
		// 绘制表框
		// 绘制区域缩小到表框大小
		float fShrink = (-m_fFrameWidth - m_fBorderWidth) / 2;
		rcDraw.Inflate(fShrink, fShrink);
		if (m_clrFrame[0].GetValue() == m_clrFrame[1].GetValue())// 单色绘制
		{
			Pen pen(m_clrFrame[0], m_fFrameWidth);
			gr.DrawArc(&pen, rcDraw, 0, 360);
		}
		else
		{
			// 中心向四周渐变
			//GraphicsPath path;
			//path.AddArc(rcIn, 0, 360);
			//PathGradientBrush br(&path);
			//br.SetCenterColor(m_clrFrame[0]);			
			//int iCnt = 1;
			//br.SetSurroundColors(m_clrFrame + 1, &iCnt);
			// 线性渐变，中心色对应左上角，
			PointF pt1(rcDraw.GetLeft(), rcDraw.GetTop());
			PointF pt2(rcDraw.GetRight(), rcDraw.GetTop() + rcDraw.Height);
			LinearGradientBrush br(pt1, pt2, m_clrFrame[0], m_clrFrame[1]);
			Pen pen(&br, m_fFrameWidth);
			gr.DrawArc(&pen, rcDraw, 0, 360);
			
		}
		rcDraw.Inflate(fShrink, fShrink);
		// 绘制背板
		DrawBackPane(gr, rcDraw);
	}
}

BOOL CDial::LoadFromFile(CString strFile)
{
	m_image.FormFile(strFile);
	return m_image.GetImage() != NULL;
}

BOOL CDial::LoadFromResource(CString sType, int iId)
{
	m_image.FromResource(sType, iId);
	return m_image.GetImage() != NULL;
}

/******************************************************************************/
// 绘制背板,如果背板颜色相同，使用单色画刷，否则使用渐变画刷
// 返回值：
/******************************************************************************/
void CDial::DrawBackPane( Graphics &gr, RectF rc )
{
	if (m_clrBk[0].GetValue() == m_clrBk[1].GetValue())// 单色绘制
	{
		SolidBrush brBk(m_clrBk[0]);
		gr.FillEllipse(&brBk, rc);
	}
	else// 使用路径渐变画刷绘制
	{
		GraphicsPath path;
		path.AddEllipse(rc);
		PathGradientBrush br(&path);
		int iCnt = 1;
		br.SetSurroundColors(&m_clrBk[1], &iCnt);
		br.SetCenterColor(m_clrBk[0]);
		br.SetCenterPoint(PointF(rc.GetLeft() + rc.Width / 2, 
			rc.GetTop() + rc.Height / 2));
		gr.FillEllipse(&br, rc);
		gr.DrawEllipse(&Pen(m_clrBk[1], 1.0f), rc);
	}
}
