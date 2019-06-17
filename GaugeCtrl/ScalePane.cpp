////////////////////////////////////////////////////////////////////////////////
//
// 文件名称：ScalePane.cpp
// 功    能：仪表盘刻度区间的绘制
//
// 作    者：邓智宏
// 完成日期：2017-1-13
//
////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "scalepane.h"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
CScalePane::CScalePane(void)
{
	m_fAngleMax = 30.0f;
	m_fAngleMin = -210.0f;
	// m_fRange用于存放刻度的刻度区间，m_fRange[0]对应刻度最小值，m_fRange[3]
	m_fRange[0] = 0.0f;
	m_fRange[1] = m_fRange[2]= m_fRange[3]= 100.0f;
	m_fRgBarOffset = 100;
	m_ptCenter = PointF();
	m_fWidth = 10.0f;
	m_clrRange[0] = Color(10, 225, 10);
	m_clrRange[1] = Color::Orange;
	m_clrRange[2] = Color(205, 20, 20);
	m_iMajorTickSteps = 10;
	m_iMinorTickSteps = 5;
	m_clrMajor = Color(0XFF404040);
	m_clrMinor = Color(0XFF404040);
	m_szMajor = SizeF(4.0f, 8.0f);
	m_szMinor = SizeF(1.0f, 6.0f);
	m_pFt = new Font(L"宋体", 10.0f, FontStyleRegular);
	m_iDigital = 0;
	m_strFmt.Format(_T("%%.%df"), m_iDigital);
	m_byVisible = bothVisible;
	m_fDLabel = float(m_fRgBarOffset);
	m_fTickOffset = m_fDLabel;
}

CScalePane::~CScalePane(void)
{
	delete m_pFt;
	m_pFt = NULL;
}

/******************************************************************************/
// 绘制刻度盘
// gr：绘制图形对象
// rc：绘制的区域
/******************************************************************************/
void CScalePane::Draw(Graphics&gr, Rect rc)
{
	Matrix mx;
	gr.GetTransform(&mx);
	gr.TranslateTransform(m_ptCenter.X, m_ptCenter.Y);
	// 绘制分段刻度的背景
	for (int i = 0; i < 3; i++)
	{
		if (m_fRange[i + 1] == m_fRange[i])
			continue;
		Pen penRng1(m_clrRange[i], m_fWidth);
		float fStart = GetValueAngle(m_fRange[i]);// 起始角度
		float fEnd = GetValueAngle(m_fRange[i + 1]) ;// 结束角度
		RectF rcArc(-m_fRgBarOffset, -m_fRgBarOffset, m_fRgBarOffset * 2, m_fRgBarOffset * 2);
		//RectF rcArc(-m_fRadius + m_fWidth / 2,
		//	-m_fRadius + m_fWidth / 2,
		//	m_fRadius* 2 - m_fWidth ,
		//	m_fRadius* 2 - m_fWidth);

		gr.DrawArc(&penRng1, rcArc, fStart, fEnd - fStart);
	}
	//DrawStyleHorizontal(gr);
	
	DrawStyleAround(gr);

	gr.SetTransform(&mx);
}

/******************************************************************************/
// 设置刻度范围,最大刻度必须大于最小刻度,需要刻度按逆时针方向增长可以通过
// 设置角度范围来实现。
// fMin：最小刻度
// fMax：最大刻度
/******************************************************************************/
void CScalePane::SetScaleRagne(float fMin, float fMax)
{
	if (fMin >= fMax)
		throw _T("刻度范围超出规定");
	m_fRange[0] = fMin;
	m_fRange[3] = fMax;
	//------------------------------------------------
	// 需要确保中间的分段区间包含在最大最小刻度之间
	if (m_fRange[1] >= fMax || m_fRange[2] < fMin)
	{
		m_fRange[1] = fMax;
		m_fRange[2] = fMax;
	}
	else if (m_fRange[2] == fMin || m_fRange[1] < fMin)
		m_fRange[1] = fMin;
	else if (m_fRange[2] > fMax)
		m_fRange[2] = fMax;
	//------------------------------------------------
}


/******************************************************************************/
// 设置分段条1的终止位置
/******************************************************************************/
void CScalePane::SetRange1End(float fRng)
{
	if (fRng < m_fRange[0] || fRng > m_fRange[3])
		throw _T("分段条1设置错误");
	// 如果设置值小于当前最小值，则重新设置最小值
	m_fRange[1] = fRng;
	if (m_fRange[0] > fRng)
		m_fRange[0] = fRng;
	if (fRng > m_fRange[2])
		m_fRange[2] = fRng;
	if (fRng > m_fRange[3])
		m_fRange[3] = fRng;
}

/******************************************************************************/
// 设置分段条2的终止位置
/******************************************************************************/
void CScalePane::SetRange2End(float fRng)
{
	m_fRange[2] = fRng;
	if (m_fRange[1] > fRng)
		m_fRange[1] = fRng;
	if (m_fRange[0] > fRng)
		m_fRange[0] = fRng;
	if (m_fRange[3] < fRng)
		m_fRange[3] = fRng;

}
/******************************************************************************/
// 设置半径分段条中心到表盘圆形距离
/******************************************************************************/
void CScalePane::SetRgBarOffset(float fVal)
{
		m_fRgBarOffset = abs(fVal);
}

/******************************************************************************/
// 设置刻度分布的角度范围，0角度在X正轴方向，顺时针增大，逆时针减小。设置角度
// 范围时，两个角度相差必须在360度以内。fMax大于fMin时，刻度顺时针方向增加；
// fMin大于fMin时，刻度顺时针方向减小。
// fMin：最小角度，单位度数
// fMax：最大角度，单位度数
/******************************************************************************/
void CScalePane::SetAngleRange(float fMin, float fMax)
{
	if (abs(fMax - fMin) > 360)
		throw _T("角度超范围");
	m_fAngleMin = fMin;
	m_fAngleMax = fMax;
}

/******************************************************************************/
// 获取指定刻度值对应的角度，指针指向的角度也可以使用该函数计算
// 返回值：设定数值对应的角度
/******************************************************************************/
float CScalePane::GetValueAngle(float fVal)
{
	return (m_fAngleMax - m_fAngleMin) / (m_fRange[3] - m_fRange[0]) * (fVal - m_fRange[0]) + m_fAngleMin;
}

void CScalePane::SetCenter(Rect rc)
{
	m_ptCenter = PointF(rc.GetLeft() + rc.Width / 2.0f, 
		rc.GetTop() + rc.Height / 2.0f);
}

void CScalePane::SetCenter(Point pt)
{
	m_ptCenter = PointF((float)pt.X, (float)pt.Y);
}

/******************************************************************************/
// 设置刻度标签字体
/******************************************************************************/
void CScalePane::SetFont(Font &ft)
{
	if (ft.GetLastStatus() == Ok && m_pFt)
	{
		delete m_pFt;
		m_pFt = ft.Clone();
	}
}

/******************************************************************************/
// 使用围绕方式进行绘制
/******************************************************************************/
void CScalePane::DrawStyleAround(Graphics& gr)
{
	Pen penMajor(m_clrMajor, m_szMajor.Width);// 主刻度画笔
	Pen penMinor(m_clrMinor, m_szMinor.Width);// 子刻度画笔
	SolidBrush br(m_clrMajor);// 主刻度画刷
	float fMajorStep = (m_fRange[3] - m_fRange[0]) / m_iMajorTickSteps;// 主刻度步长
	float fMinorStep = fMajorStep / m_iMinorTickSteps;// 子刻度步长
	float fOuter = m_fTickOffset + m_szMajor.Height / 2;// 主刻度外延到表盘中心距
	float fInner = m_fTickOffset - m_szMajor.Height / 2;// 主刻度内沿到表盘中心距
	//float fFontSize = m_pFt->GetSize();// 字体大小
	float fAgOffset = (m_fAngleMax - m_fAngleMin) / (m_iMajorTickSteps * m_iMinorTickSteps);
	// 
	gr.SetTextRenderingHint(TextRenderingHintAntiAlias);
	gr.RotateTransform(m_fAngleMin + 90);
	for (int i = 0; i <= m_iMajorTickSteps; i++)
	{
		float fV = fMajorStep * i + m_fRange[0];
		gr.DrawLine(&penMajor, 0.0f, -fOuter, 0.0f, -fInner);

		//// 绘制主刻度数字
		StringFormat strFmt(StringFormatFlagsNoClip);
		strFmt.SetAlignment(StringAlignmentCenter);
		
		CStringW str;
		str.Format(m_strFmt, fV);

		int iStrLen = str.GetLength();
		// 刻度文本位置
		PointF ptTxt(0.0f, -m_fDLabel);
		gr.DrawString(str, iStrLen, m_pFt, ptTxt, &strFmt, &br);
		gr.RotateTransform(fAgOffset);

		//// 子刻度
		if (fV + fMinorStep >= m_fRange[3])// 超出绘制范围，退出循环
			break;
		for (int j = 1; j < m_iMinorTickSteps; j++)
		{
			gr.DrawLine(&penMinor, 0.0f, -fOuter, 0.0f, -fInner - 2);
			gr.RotateTransform(fAgOffset);
		}
	}

}

/******************************************************************************/
// 使用水平方式进行绘制
/******************************************************************************/
void CScalePane::DrawStyleHorizontal(Graphics& gr)
{
	// 主刻度
	Pen penMajor(m_clrMajor, m_szMajor.Width);// 主刻度画笔
	Pen penMinor(m_clrMinor, m_szMinor.Width);// 子刻度画笔
	SolidBrush br(m_clrMajor);// 主刻度画刷
	float fMajorStep = (m_fRange[3] - m_fRange[0]) / m_iMajorTickSteps;// 主刻度步长
	float fMinorStep = fMajorStep / m_iMinorTickSteps;// 子刻度步长
	float fOuter = m_fRgBarOffset + m_szMajor.Width;// 主刻度外延到表盘中心距
	float fInner = m_fRgBarOffset - m_szMajor.Width;// 主刻度内沿到表盘中心距
	float fFontSize = m_pFt->GetSize();// 字体大小
	// 依次绘制各刻度点
	for (int i = 0; i <= m_iMajorTickSteps; i++)
	{
		float fV = fMajorStep * i;
		float fAg = float(GetValueAngle(fV) * M_PI / 180);
		PointF pt1(cos(fAg) * fOuter, sin(fAg) * fOuter);
		PointF pt2(cos(fAg) * fInner, sin(fAg) * fInner);
		gr.DrawLine(&penMajor, pt1, pt2);
		// 绘制主刻度数字
		StringFormat strFmt(StringFormatFlagsNoClip);
		strFmt.SetAlignment(StringAlignmentCenter);
		CStringW str;
		str.Format(m_strFmt, fV);
		int iStrLen = str.GetLength();
		// 刻度文本位置
		PointF ptTxt(cos(fAg) * m_fDLabel, sin(fAg) * m_fDLabel - fFontSize);
		gr.DrawString(str, iStrLen, m_pFt, ptTxt, &strFmt, &br);


		// 子刻度
		if (fV + fMinorStep >= m_fRange[3])// 超出绘制范围，退出循环
			break;
		for (int j = 1; j < m_iMinorTickSteps; j++)
		{
			float fV = (i * (m_iMinorTickSteps) + j) * fMinorStep;
			fAg = float(GetValueAngle(fV) * M_PI / 180);
			PointF pt1(cos(fAg) * fOuter, sin(fAg) * fOuter);
			PointF pt2(cos(fAg) * (fInner + 2), sin(fAg) * (fInner + 2));
			gr.DrawLine(&penMinor, pt1, pt2);
		}
	}
}

/******************************************************************************/
// 设置刻度文本中心偏离表中心的距离
// fOffset：文本中心到仪表中心的距离
/******************************************************************************/
void CScalePane::SetLabelOffset(float fOffset)
{
	m_fDLabel = abs(fOffset);
}
