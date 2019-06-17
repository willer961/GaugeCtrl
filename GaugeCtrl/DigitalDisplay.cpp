////////////////////////////////////////////////////////////////////////////////
//
// 文件名称：DigitalDisplay.cpp
// 功    能：LED显示
//
// 作    者：邓智宏
// 完成日期：2017-1-13
//
////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "DigitalDisplay.h"

// 7段LED
PointF g_ptNum[8][6] = {{
	PointF(4.0f, 2.0f),		PointF(6.0f, 0.0f),		PointF(25.0f, 0.0f),
	PointF(27.0f, 2.0f),	PointF(23.0f, 6.0f),	PointF(8.0f, 6.0f)
},{
	PointF(29.0f, 4.0f),	PointF(31.0f, 6.0f),	PointF(31.0f, 25.0f),
	PointF(29.0f, 27.0f),	PointF(25.0f, 23.0f),	PointF(25.0f, 8.0f)
},{
	PointF(29.0f, 29.0f),	PointF(31.0f, 31.0f),	PointF(31.0f, 51.0f),
	PointF(29.0f, 53.0f),	PointF(25.0f, 49.0f),	PointF(25.0f, 33.0f)
},{
	PointF(8.0f, 51.0f),	PointF(23.0f, 51.0f),	PointF(27.0f, 55.0f),
	PointF(25.0f, 57.0f),	PointF(6.0f, 57.0f),	PointF(4.0f, 55.0f)
},{
	PointF(2.0f, 29.0f),	PointF(6.0f, 33.0f),	PointF(6.0f, 49.0f),
	PointF(2.0f, 53.0f),	PointF(0.0f, 51.0f),	PointF(0.0f, 31.0f)
},{
	PointF(2.0f, 4.0f),		PointF(6.0f, 8.0f),		PointF(6.0f, 23.0f),
	PointF(2.0f, 27.0f),	PointF(0.0f, 25.0f),	PointF(0.0f, 6.0f)
},{
	PointF(8.0f, 25.0f),	PointF(23.0f, 25.0f),	PointF(26.0f, 28.0f),
	PointF(23.0f, 31.0f),	PointF(8.0f, 31.0f),	PointF(5.0f, 28.0f)
},{
	PointF(6.0f, 36.0f),	PointF(9.0f, 36.0f),	PointF(14.0f, 41.0f),
	PointF(9.0f, 46.0f),	PointF(6.0f, 46.0f),	PointF(1.0f, 41.0f)}};
					
	BYTE g_byNum[12] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F, 0X80, 0X40};
					//  0	  1	    2	  3	    4	  5     6     7     8     9     .     -
	SizeF g_SigleSize(32.0f, 57.0f);// 单字符占据大小
CDigitalDisplay::CDigitalDisplay(void)
{
	m_iPre = 1;// 小数位0
	m_iLen = 5;
	m_clr = Color(60, 60, 60);
	m_fCharSize = g_SigleSize.Height;
}

CDigitalDisplay::~CDigitalDisplay(void)
{
}

/******************************************************************************/
// 以7段LED形式绘制指定数值
// fV：需要绘制的数值
// rc：数值绘制的位置，使用该方法时，不使用设定的字体大小
/******************************************************************************/
void CDigitalDisplay::Draw(Graphics& gr, float fV, RectF rc)
{
	// 单字符可占据宽度
	float fSingleW = rc.Width / (m_iLen + (m_iPre > 0 ? 0.5f : 0));
	float fSingleH = g_SigleSize.Height;
	float fGap = 2.0f;
	CString strFmt, str;
	int iLen = m_iLen + (m_iPre > 0 ? 1 : 0);// 字符长度
	strFmt.Format(_T("%%0%d.%df"), iLen, m_iPre);
	str.Format(strFmt, fV);
	str = str.Right(iLen);// 只显示指定长度数据
	// 按照没字符间留2Pix空隙
	if (fSingleW > g_SigleSize.Width + 2)
		fGap = fSingleW / (g_SigleSize.Width * 2);
	// 去除间隙
	fSingleW -= fGap;
	// 计算缩放比例
	float fRatio = fSingleW / g_SigleSize.Width;
	// 如果按照该比例得出的单字符高度大于绘图区域高度，
	// 需要重新计算缩放比例
	if (fRatio * g_SigleSize.Height > rc.Height)
	{
		fRatio = rc.Height / g_SigleSize.Height;
		fSingleW = fRatio * g_SigleSize.Width;
		if (fRatio > 1.0f)
			fGap = fSingleW /(g_SigleSize.Width * 2);
		else
			fGap = 2.0f;
		fSingleW += fGap;
		float fW = fSingleW * (m_iLen + (m_iPre > 0 ? 0.5f : 0));
		rc.X += (rc.Width - fW) / 2;
		rc.Width = fW;
	}

	DrawDigital(fRatio, rc, fSingleW, fGap, gr, str);

}

/******************************************************************************/
// 以7段LED形式绘制指定数值
// fV：需要绘制的数值
// ptCenter：绘制的中心点位置
/******************************************************************************/
void CDigitalDisplay::Draw(Graphics& gr, float fV, PointF ptCenter)
{
	// 单字符可占据宽度
	float fSingleH = m_fCharSize;
	float fRatio = fSingleH / g_SigleSize.Height;
	float fSingleW = fRatio * g_SigleSize.Width;
	float fGap = fRatio > 1.0f ? fSingleW /(g_SigleSize.Width * 2) : 2.0f;
	CString strFmt, str;
	int iLen = m_iLen + (m_iPre > 0 ? 1 : 0);// 字符长度
	strFmt.Format(_T("%%0%d.%df"), iLen, m_iPre);
	str.Format(strFmt, fV);
	str = str.Right(iLen);// 只显示指定长度数据
	
	float fW = (m_iLen + (m_iPre > 0 ? 0.5f : 0)) * (fRatio * g_SigleSize.Width + fGap);
	RectF rc(ptCenter.X - fW / 2, ptCenter.Y - fSingleH / 2, fW, fSingleH);

	DrawDigital(fRatio, rc, fSingleW, fGap, gr, str);

}

/******************************************************************************/
// 设置显示长度
/******************************************************************************/
void CDigitalDisplay::SetLen(int iLen)
{
	if (iLen > 0  && iLen <= 6)
	{
		m_iLen = iLen;
	}
	if (m_iPre >= m_iLen)
	{
		m_iPre = m_iLen - 1;
	}
}

/******************************************************************************/
// 设置显示的小数位
/******************************************************************************/
void CDigitalDisplay::SetPrecision(int iPrecision)
{
	if (iPrecision >= 0 && iPrecision < m_iLen)
	{
		m_iPre = iPrecision;
	}
}

/******************************************************************************/
// 绘制单个字符
/******************************************************************************/
void CDigitalDisplay::DrawChar(Graphics &gr, TCHAR ch, PointF *pts)
{
	BYTE byNum = 0;
	// 获取需要绘制的字符对应的LED灯
	if (ch >= 0x30 && ch <= 0X39)// 数字
		byNum = g_byNum[ch - 0X30];
	else if (ch == _T('.'))
		byNum = g_byNum[10];
	else if (ch == _T('-'))
		byNum = g_byNum[11];
	
	// 输入字符不正确
	if (byNum == 0)
		return;
	// 进行绘制
	for (int i = 0; i < 8; i++)
	{
		// 对应的LED灯可见
		if (byNum  & (1 << i))
		{
			gr.FillPolygon(&SolidBrush(m_clr), pts + i * 6, 6);
		}
	}
}

void CDigitalDisplay::DrawDigital( float &fRatio, RectF &rc, float &fSingleW, float &fGap, Graphics &gr, CString &str )
{
	
	PointF pts[48];
	for (int i = 0; i < 48; i++)
	{
		pts[i] = PointF(g_ptNum[i / 6][i % 6].X * fRatio, 
			g_ptNum[i / 6][i % 6].Y *fRatio);
	}
	// 保存当前矩阵
	Matrix mx;
	gr.GetTransform(&mx);
	// 移动绘图区域
	gr.TranslateTransform(rc.GetLeft(), rc.GetTop());
	fGap = fGap / 2;// 单边间距
	int iCnt = str.GetLength();
	for (int i = 0; i < iCnt; i++)
	{
		gr.TranslateTransform(fGap, 0);
		DrawChar(gr, str.GetAt(i), pts);
		if (str.GetAt(i) == _T('.'))// 半个宽度
			gr.TranslateTransform(fGap + fSingleW / 2, 0);
		else
			gr.TranslateTransform(fGap + fSingleW, 0);
	}
	// 恢复矩阵
	gr.SetTransform(&mx);
}


