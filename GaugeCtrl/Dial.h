#pragma once
#include <GdiPlus.h>
#include "GDIPlusImage.h"
using namespace Gdiplus;

class CDial
{
	friend class CGaugeCtrl;
public:
	CDial(void);
public:
	~CDial(void);
protected:
	float m_fBorderWidth;
	float m_fFrameWidth;
	Color m_clrBorder;
	Color m_clrFrame[2];
	Color m_clrBk[2];
	CGDIPlusImage m_image;
	BOOL m_bUseImage;
protected:
	virtual void Draw(Graphics& gr, Rect rc);
	void DrawBackPane( Graphics &gr, RectF rc );
public:
	BOOL LoadFromFile(CString strFile);
	BOOL LoadFromResource(CString sType, int iId);
	// 边界色
	void SetBorderColor(Color clr){m_clrBorder = clr;}
	Color GetBorderColor(){return m_clrBorder;}
	// 边界宽度
	void SetBorderWidth(float fW){m_fBorderWidth = fW;}
	float GetBorderWidth(){return m_fBorderWidth;}
	// 边框宽度
	void SetFrameWidth(float fW){m_fFrameWidth = fW;}
	float GetFrameWidth(){return m_fFrameWidth;}
	// 表框色
	void SetFrameColor(Color clrLeft, Color clrRight)
	{m_clrFrame[0] = clrLeft; m_clrFrame[1] = clrRight;}
	void GetFrameColor(Color &clrLeft, Color &clrRight)
	{clrLeft = m_clrFrame[0]; clrRight = m_clrFrame[1];}
	// 背景色
	void SetBackColor(Color clrCenter, Color clrRound)
	{m_clrBk[0] = clrCenter; m_clrBk[1] = clrRound;}
	void GetBackColor(Color &clrCenter, Color &clrRound)
	{clrCenter = m_clrBk[0]; clrRound = m_clrBk[1];}
	// 是否使用外部图片
	void SetUseImage(BOOL bUse){m_bUseImage = bUse;}
	BOOL IsUseImage(){return m_bUseImage;}
};
