#pragma once
#include <GdiPlus.h>
using namespace Gdiplus;
class CDigitalDisplay
{
public:
	CDigitalDisplay(void);
public:
	~CDigitalDisplay(void);
public:
	void Draw(Graphics& gr, float fV, RectF rc);
	void Draw(Graphics& gr, float fV, PointF ptCenter);	

	void DrawDigital( float &fRatio, RectF &rc, float &fSingleW, float &fGap, Graphics &gr, CString &str );

	void SetLen(int iLen);
	void SetPrecision(int iPrecision);
	void SetColor(Color clr){m_clr = clr;}
	Color GetColor(){return m_clr;}
protected:
	int m_iLen;
	int m_iPre;
	Color m_clr;
	float m_fCharSize;
	void DrawChar(Graphics &gr, TCHAR ch, PointF *pts);
public:
	// 字体大小，指单字的高度
	void SetCharSize(float fSize){m_fCharSize = fSize;}
	float GetCharSize(){return m_fCharSize;}
	
};
