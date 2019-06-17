// TestGaugeDlg.h : 头文件
//

#pragma once
#include "../gaugectrl/GaugeCtrl.h"
#include "../gaugectrl/colorstatic.h"
#include "afxcmn.h"

// CTestGaugeDlg 对话框
class CTestGaugeDlg : public CDialog
{
// 构造
public:
	CTestGaugeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTGAUGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CGaugeCtrl m_gauge;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	CColorStatic m_clrBkCtrl;
public:
	CColorStatic m_clrBk2Ctrl;
public:
	afx_msg void OnStnClickedBack2();
public:
	afx_msg void OnStnClickedBack1();
public:
	afx_msg void OnStnClickedRg1();
public:
	afx_msg void OnStnClickedRg2();
public:
	afx_msg void OnStnClickedRg3();
public:
	CColorStatic m_clrRg1;
public:
	CColorStatic m_clrRg2;
public:
	CColorStatic m_clrRg3;
public:
	afx_msg void OnStnClickedPtcolor();
public:
	CColorStatic m_clrPt;
public:
	CColorStatic m_clrBorder;
public:
	CColorStatic m_clrFrm1;
public:
	CColorStatic m_clrFrm2;
public:
	CColorStatic m_clrLabel;
public:
	afx_msg void OnStnClickedBorderClr();
public:
	afx_msg void OnStnClickedFrmClr1();
public:
	afx_msg void OnStnClickedFrmClr2();
public:
	afx_msg void OnStnClickedLableClr();
public:
	afx_msg void OnNMReleasedcaptureSliderFrm(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMReleasedcaptureSliderCtrl(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMReleasedcaptureSliderRg1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMReleasedcaptureSliderRg2(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMReleasedcaptureSliderPt(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	CSliderCtrl m_sldFrmW;
public:
	CSliderCtrl m_sldRg1Clr;
public:
	CSliderCtrl m_sldRg2Clr;
public:
	CSliderCtrl m_sldPt;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	float m_fMin;
public:
	float m_fMax;
public:
	int m_iMS;
public:
	int m_iMinS;
public:
	CColorStatic m_clrMinor;
public:
	afx_msg void OnStnClickedMinorClr();
public:
	CSliderCtrl m_sldRgW;
public:
	CSliderCtrl m_sldTickOffset;
public:
	afx_msg void OnNMReleasedcaptureSliderRgw(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMReleasedcaptureSliderTickOffset(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CSliderCtrl m_sldLabelOffset;
public:
	CSliderCtrl m_sldTickLen;
public:
	afx_msg void OnNMReleasedcaptureSliderLabelOffset(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMReleasedcaptureSliderTicklen(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CSliderCtrl m_sldRgOffset;
public:
	afx_msg void OnNMReleasedcaptureSliderRgOffset(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CSliderCtrl m_sldValue;
public:
	afx_msg void OnNMReleasedcaptureSliderValue(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CSliderCtrl m_sldDigital;
public:
	CColorStatic m_clrDigital;
public:
	afx_msg void OnStnClickedDigiclr();
public:
	afx_msg void OnNMReleasedcaptureSliderDigi(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedCheck1();
public:
	BOOL m_bHighLight;
};
