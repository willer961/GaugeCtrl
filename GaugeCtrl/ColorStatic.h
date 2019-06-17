#pragma once

#include <GdiPlus.h>
// CColorStatic

class CColorStatic : public CStatic
{
	DECLARE_DYNAMIC(CColorStatic)

public:
	CColorStatic();
	virtual ~CColorStatic();
	void SetColor(COLORREF clr){m_clr = clr; Invalidate();}
	void SetColor(Gdiplus::Color clr)
	{
		Gdiplus::ARGB c = clr.GetValue() & 0XFFFFFF;
		m_clr = ((c & 0XFF) << 16 )| ((c & 0XFF00))| ((c & 0XFF0000) >> 16);
		Invalidate();
	}
	COLORREF GetColor(){return m_clr;}
protected:
	COLORREF m_clr;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
protected:
	virtual void PreSubclassWindow();
};


