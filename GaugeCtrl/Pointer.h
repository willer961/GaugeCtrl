#pragma once
#include <GdiPlus.h>
using namespace Gdiplus;
class CPointer
{
public:
	CPointer(void);
public:
	~CPointer(void);
protected:
	Color m_clrNeedle;
	Color m_clrCap;
	float m_fLen;
	float m_fWidth;
	float m_fCapSize;
	RectF m_rcCap;
	float m_fAxisSize;
	RectF m_rcAxis;
public:
	void Draw(Graphics &gr, float fAg, PointF ptCenter);
	void SetCapSize(float fSize);
	void SetAxisSize(float fSize);
	void SetNeedleLen(float fLen){m_fLen = fLen;}
	void SetNeedleColor(Color clr){m_clrNeedle = clr;}
	float GetNeedleLen(){return m_fLen;}
	Color GetNeedleColor(){return m_clrNeedle;}
protected:

};
