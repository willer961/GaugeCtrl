#pragma once
#include <gdiplus.h>
using namespace Gdiplus;
class CScalePane
{
	friend class CGaugeCtrl;
	enum TickVisile
	{
		bothInvisible = 0,
		firstVisible,
		lastVisible,
		bothVisible
	};// 
public:
	CScalePane(void);
public:
	~CScalePane(void);
protected:
	
	float m_fAngleMin, m_fAngleMax;
	float m_fRange[4];
	Color m_clrRange[4];
	Color m_clrMajor;
	Color m_clrMinor;
	SizeF m_szMajor;
	SizeF m_szMinor;
	float m_fWidth;
	int m_iMajorTickSteps;
	int m_iMinorTickSteps;
	float m_fRgBarOffset;
	PointF m_ptCenter;
	Font* m_pFt;
	int m_iDigital;
	CString m_strFmt;
	TickVisile m_byVisible;
	float m_fDLabel;
	float m_fTickOffset;
protected:
	// 绘制
	void Draw(Graphics&gr, Rect rc);
	void DrawStyleAround(Graphics& gr);
	void DrawStyleHorizontal(Graphics& gr);
public:
	// 刻度范围
	void SetScaleRagne(float fMin, float fMax);
	float GetMinValue(){return m_fRange[0];}
	float GetMaxValue(){return m_fRange[3];}
	// 刻度分段区间的范围
	void SetRange1End(float fRng);
	float GetRange1End(){return m_fRange[1];}
	void SetRange2End(float fRng);
	float GetRange2End(){return m_fRange[2];}
	// 刻度分段区间的颜色
	void SetRange1Color(Color clr){m_clrRange[0] = clr;}
	Color GetRange1Color(){return m_clrRange[0];}
	void SetRange2Color(Color clr){m_clrRange[1] = clr;}
	Color GetRange2Color(){return m_clrRange[1];}
	void SetRange3Color(Color clr){m_clrRange[2] = clr;}
	Color GetRange3Color(){return m_clrRange[2];}
	// 刻度起始角度范围
	void SetMaxAngle(float fAng){m_fAngleMax = fAng;}
	float GetMaxAngle(){return m_fAngleMax;}
	void SetAngleRange(float fMin, float fMax);
	float GetMinAngle(){return m_fAngleMin;}
	// 
	void SetRgBarOffset(float iVal);
	float GetRgBarOffset(){return m_fRgBarOffset;}

	void SetCenter(Rect rc);
	void SetCenter(Point pt);
	// 刻度文字字体
	void SetFont(Font &ft);
	// 刻度颜色
	void SetMajorColor(Color clr){m_clrMajor = clr;}
	Color GetMajorColor(){return m_clrMajor;}
	void SetMinorColor(Color clr){m_clrMinor = clr;}
	Color GetMinorColor(){return m_clrMinor;}
	// 刻度点宽度
	void SetMajorSize(SizeF fSz){m_szMajor = fSz;}
	void SetMinorSize(SizeF fSz){m_szMinor = fSz;}
	SizeF GetMajorSize(){return m_szMajor;}
	SizeF GetMinorSize(){return m_szMinor;}
	// 
	void SetWidth(float fWidth){m_fWidth = fWidth;}
	float GetWidth(){return m_fWidth;}

	// 获取显示值对应的角度
	float GetValueAngle(float fVal);
	// 刻度可见
	void SetTickVisible(TickVisile flag){m_byVisible = flag;}
	TickVisile GetTickVisible(){return m_byVisible;}
	// 刻度文本中心偏离表中心的距离
	void SetLabelOffset(float fOffset);
	float GetLabelOffset(){return m_fDLabel;}
	void SetTickOffset(float fOffset){m_fTickOffset = fOffset;}
	float GetTickOffset(){return m_fTickOffset;}
	// 
	void SetMajorSteps(int iS){m_iMajorTickSteps = iS;}
	int GetMajorSteps(){return m_iMajorTickSteps;}
	void SetMinorSteps(int iS){m_iMinorTickSteps = iS;}
	int GetMinorSteps(){return m_iMinorTickSteps;}

protected:
};
