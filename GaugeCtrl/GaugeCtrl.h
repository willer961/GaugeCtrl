#pragma once

#include <GdiPlus.h>
#include "Dial.h"
#include "ScalePane.h"
#include "Pointer.h"
#include "DigitalDisplay.h"

// CGaugeCtrl

class CGaugeCtrl : public CWnd
{
	DECLARE_DYNAMIC(CGaugeCtrl)

public:
	CGaugeCtrl();
	virtual ~CGaugeCtrl();
protected:
	BOOL RegisterWindowClass();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
protected:
	Gdiplus::Image* m_pImgBk;
	CDial m_dial;
	CScalePane m_scale;
	CPointer m_pointer;
	int m_alpha;
	BOOL m_bHighlight;
	float m_fVal;
	CString m_strTxt;
	float m_fNumSize;
	CDigitalDisplay m_led;
	PointF m_ptLed;
	virtual void PreSubclassWindow();
	static Gdiplus::GdiplusStartupInput s_gdiplusStartupInput;
	static ULONG_PTR s_gdiplusToken;
	static int s_nGauges;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	void DrawHighlight(Graphics& gr);

	void GetDialRect( CRect &rc );

	CDial *GetDial(){return &m_dial;}
	CScalePane *GetScalePane(){return &m_scale;}
	CPointer* GetPointer(){return &m_pointer;}
	CDigitalDisplay* GetLed(){return &m_led;}
	void SetAlphaValue(int val){m_alpha = val;}
	void SetHighlight(BOOL bV){m_bHighlight = bV;}
	BOOL GetHighlight(){return m_bHighlight;}
	void SetValue(float fV, BOOL bUpdate = TRUE);
	float GetValue(){return m_fVal;}
	void SetText(CString strTxt){m_strTxt = strTxt;}
	CString GetText(){return m_strTxt;}
	void SetNumSize(float fSize){m_led.SetCharSize(fSize);}
	void SetLEDPos(PointF pt){m_ptLed = pt;}

public:
	void CreateBkImage(void);
public:
	void Redraw(void);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
public:
	void AutoLayout(void);
	static void Init()
	{		
		Gdiplus::GdiplusStartup(&s_gdiplusToken, &s_gdiplusStartupInput, NULL);
	}
	static void Uninit()
	{		
		Gdiplus::GdiplusShutdown(s_gdiplusToken);
	}
};


