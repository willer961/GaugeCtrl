// TestGaugeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestGauge.h"
#include "TestGaugeDlg.h"

#ifdef _DEBUG
#pragma comment(lib,"../debug/gaugectrl_d.lib")
#define new DEBUG_NEW
#else
#pragma comment(lib,"../release/gaugectrl.lib")
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
Color GetCtrlColor(CColorStatic& ctrl)
{
	COLORREF clr = ctrl.GetColor();
	ARGB c = 0XFF000000 | ((clr & 0XFF) << 16 )| ((clr & 0XFF00))| ((clr & 0XFF0000) >> 16);
	return Color(c);

}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestGaugeDlg 对话框




CTestGaugeDlg::CTestGaugeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGaugeDlg::IDD, pParent)
	, m_fMin(0)
	, m_fMax(0)
	, m_iMS(0)
	, m_iMinS(0)
	, m_bHighLight(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGaugeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_gauge);
	DDX_Control(pDX, IDC_BACK1, m_clrBkCtrl);
	DDX_Control(pDX, IDC_BACK2, m_clrBk2Ctrl);
	DDX_Control(pDX, IDC_RG1, m_clrRg1);
	DDX_Control(pDX, IDC_RG2, m_clrRg2);
	DDX_Control(pDX, IDC_RG3, m_clrRg3);
	DDX_Control(pDX, IDC_PTCOLOR, m_clrPt);
	DDX_Control(pDX, IDC_BORDER_CLR, m_clrBorder);
	DDX_Control(pDX, IDC_FRM_CLR1, m_clrFrm1);
	DDX_Control(pDX, IDC_FRM_CLR2, m_clrFrm2);
	DDX_Control(pDX, IDC_LABLE_CLR, m_clrLabel);
	DDX_Control(pDX, IDC_SLIDER_FRM, m_sldFrmW);
	DDX_Control(pDX, IDC_SLIDER_RG1, m_sldRg1Clr);
	DDX_Control(pDX, IDC_SLIDER_RG2, m_sldRg2Clr);
	DDX_Control(pDX, IDC_SLIDER_PT, m_sldPt);
	DDX_Text(pDX, IDC_EDIT_MIN, m_fMin);
	DDX_Text(pDX, IDC_EDIT_MAX, m_fMax);
	DDX_Text(pDX, IDC_EDIT_MAJOR, m_iMS);
	DDV_MinMaxInt(pDX, m_iMS, 2, 10);
	DDX_Text(pDX, IDC_EDIT_MINOR, m_iMinS);
	DDV_MinMaxInt(pDX, m_iMinS, 2, 10);
	DDX_Control(pDX, IDC_MINOR_CLR, m_clrMinor);
	DDX_Control(pDX, IDC_SLIDER_RGW, m_sldRgW);
	DDX_Control(pDX, IDC_SLIDER_TICK_OFFSET, m_sldTickOffset);
	DDX_Control(pDX, IDC_SLIDER_LABEL_OFFSET, m_sldLabelOffset);
	DDX_Control(pDX, IDC_SLIDER_TICKLEN, m_sldTickLen);
	DDX_Control(pDX, IDC_SLIDER_RG_OFFSET, m_sldRgOffset);
	DDX_Control(pDX, IDC_SLIDER_VALUE, m_sldValue);
	DDX_Control(pDX, IDC_SLIDER_DIGI, m_sldDigital);
	DDX_Control(pDX, IDC_DIGICLR, m_clrDigital);
	DDX_Check(pDX, IDC_CHECK1, m_bHighLight);
}

BEGIN_MESSAGE_MAP(CTestGaugeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_BACK2, &CTestGaugeDlg::OnStnClickedBack2)
	ON_STN_CLICKED(IDC_BACK1, &CTestGaugeDlg::OnStnClickedBack1)
	ON_STN_CLICKED(IDC_RG1, &CTestGaugeDlg::OnStnClickedRg1)
	ON_STN_CLICKED(IDC_RG2, &CTestGaugeDlg::OnStnClickedRg2)
	ON_STN_CLICKED(IDC_RG3, &CTestGaugeDlg::OnStnClickedRg3)
	ON_STN_CLICKED(IDC_PTCOLOR, &CTestGaugeDlg::OnStnClickedPtcolor)
	ON_STN_CLICKED(IDC_BORDER_CLR, &CTestGaugeDlg::OnStnClickedBorderClr)
	ON_STN_CLICKED(IDC_FRM_CLR1, &CTestGaugeDlg::OnStnClickedFrmClr1)
	ON_STN_CLICKED(IDC_FRM_CLR2, &CTestGaugeDlg::OnStnClickedFrmClr2)
	ON_STN_CLICKED(IDC_LABLE_CLR, &CTestGaugeDlg::OnStnClickedLableClr)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_FRM, &CTestGaugeDlg::OnNMReleasedcaptureSliderFrm)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RG1, &CTestGaugeDlg::OnNMReleasedcaptureSliderRg1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RG2, &CTestGaugeDlg::OnNMReleasedcaptureSliderRg2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_PT, &CTestGaugeDlg::OnNMReleasedcaptureSliderPt)
	ON_WM_HSCROLL()
	ON_STN_CLICKED(IDC_MINOR_CLR, &CTestGaugeDlg::OnStnClickedMinorClr)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RGW, &CTestGaugeDlg::OnNMReleasedcaptureSliderRgw)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TICK_OFFSET, &CTestGaugeDlg::OnNMReleasedcaptureSliderTickOffset)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_LABEL_OFFSET, &CTestGaugeDlg::OnNMReleasedcaptureSliderLabelOffset)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TICKLEN, &CTestGaugeDlg::OnNMReleasedcaptureSliderTicklen)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RG_OFFSET, &CTestGaugeDlg::OnNMReleasedcaptureSliderRgOffset)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VALUE, &CTestGaugeDlg::OnNMReleasedcaptureSliderValue)
	ON_STN_CLICKED(IDC_DIGICLR, &CTestGaugeDlg::OnStnClickedDigiclr)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIGI, &CTestGaugeDlg::OnNMReleasedcaptureSliderDigi)
	ON_BN_CLICKED(IDC_CHECK1, &CTestGaugeDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CTestGaugeDlg 消息处理程序

BOOL CTestGaugeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CRect rc;
	m_gauge.GetWindowRect(&rc);
	m_gauge.AutoLayout();
	CScalePane *pScale = m_gauge.GetScalePane();
	pScale->SetRange1Color(Color::Gray);
	m_gauge.GetPointer()->SetNeedleColor(Color(60, 60, 60));
	CDial *pDial = m_gauge.GetDial();
	pDial->SetBackColor(Color(120, 140 ,230), Color(120, 140, 230));
	//m_gauge.SetValue(30.2f);
	//pScale->SetRange1End(50.f);
	//pScale->SetRange2Color(Color::Orange);
	//pScale->SetRange2End(80.f);
	//pScale->SetRange3Color(Color(215, 40, 40));
	//pScale->SetWidth(20.0f);
	//m_gauge.SeHighlight(TRUE);
	CDigitalDisplay *pLed = m_gauge.GetLed();
	m_gauge.Redraw();
	// 边界
	m_clrBorder.SetColor(pDial->GetBorderColor());
	// 表框
	Color clrFrm1, clrFrm2;
	pDial->GetFrameColor(clrFrm1, clrFrm2);
	m_clrFrm1.SetColor(clrFrm1);
	m_clrFrm2.SetColor(clrFrm2);
	// 背景色
	Color clrbk1, clrbk2;
	pDial->GetBackColor(clrbk1, clrbk2);
	m_clrBkCtrl.SetColor(clrbk1);
	m_clrBk2Ctrl.SetColor(clrbk2);
	// 分段色
	m_clrRg1.SetColor(pScale->GetRange1Color());
	m_clrRg2.SetColor(pScale->GetRange2Color());
	m_clrRg3.SetColor(pScale->GetRange3Color());
	// 字体
	m_clrLabel.SetColor(pScale->GetMajorColor());
	m_clrMinor.SetColor(pScale->GetMinorColor());
	//SetTimer(1, 100, 0);
	// 表盘
	// 刻度范围
	m_fMax = pScale->GetMaxValue();
	m_fMin = pScale->GetMinValue();
	m_iMinS = pScale->GetMinorSteps();
	m_iMS = pScale->GetMajorSteps();
	// 刻度分段
	m_sldRg1Clr.SetRange((int)pScale->GetMinValue(), (int)pScale->GetMaxValue());
	m_sldRg1Clr.SetPos((int)pScale->GetRange1End());
	m_sldRg2Clr.SetRange((int)pScale->GetMinValue(), (int)pScale->GetMaxValue());
	m_sldRg2Clr.SetPos((int)pScale->GetRange2End());
	// 分段条宽
	m_sldRgW.SetRange(1, 40);
	m_sldRgW.SetPos((int)pScale->GetWidth());
	// 分段偏移
	m_sldRgOffset.SetRange(1, rc.Width() / 2);
	m_sldRgOffset.SetPos((int)pScale->GetRgBarOffset());
	// 刻度偏移
	m_sldLabelOffset.SetRange(1, rc.Width() / 2 );
	m_sldLabelOffset.SetPos((int)pScale->GetLabelOffset());
	// 刻度偏移
	m_sldTickOffset.SetRange(1, rc.Width() / 2 );
	m_sldTickOffset.SetPos((int)pScale->GetTickOffset());
	// 刻度长度
	m_sldTickLen.SetRange(1, 40);
	m_sldTickLen.SetPos((int)pScale->GetMajorSize().Height);

	// 表指针
	CPointer *pPt = m_gauge.GetPointer();
	m_clrPt.SetColor(pPt->GetNeedleColor());
	m_sldPt.SetRange(30, rc.Width() / 2);
	m_sldPt.SetPos((int)pPt->GetNeedleLen());
	//
	m_sldValue.SetRange((int)m_fMin, (int)m_fMax);
	m_sldValue.SetPos((int)m_gauge.GetValue());
	// 数显
	m_sldDigital.SetRange(5, 64);
	m_sldDigital.SetPos((int)pLed->GetCharSize());
	m_clrDigital.SetColor(pLed->GetColor());
	// 高亮
	m_bHighLight = m_gauge.GetHighlight();
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestGaugeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestGaugeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestGaugeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestGaugeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		static float fv = 0.0f;
		m_gauge.SetValue(fv);
		//m_gauge.Invalidate(FALSE);
		fv += 10;
	}
	CDialog::OnTimer(nIDEvent);
}


void CTestGaugeDlg::OnStnClickedBack2()
{
	CColorDialog dlg(m_clrBk2Ctrl.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrBk2Ctrl.SetColor(dlg.GetColor());
		CDial *pDial = m_gauge.GetDial();

		pDial->SetBackColor(GetCtrlColor(m_clrBkCtrl), 
			GetCtrlColor(m_clrBk2Ctrl) );
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnStnClickedBack1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrBkCtrl.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrBkCtrl.SetColor(dlg.GetColor());
		CDial *pDial = m_gauge.GetDial();
		pDial->SetBackColor(GetCtrlColor(m_clrBkCtrl), 
			GetCtrlColor(m_clrBk2Ctrl));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnStnClickedRg1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrRg1.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrRg1.SetColor(dlg.GetColor());
		CScalePane* pScale = m_gauge.GetScalePane();
		pScale->SetRange1Color(GetCtrlColor(m_clrRg1));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnStnClickedRg2()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrRg2.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrRg2.SetColor(dlg.GetColor());
		CScalePane* pScale = m_gauge.GetScalePane();
		pScale->SetRange1Color(GetCtrlColor(m_clrRg2));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnStnClickedRg3()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrRg3.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrRg3.SetColor(dlg.GetColor());
		CScalePane* pScale = m_gauge.GetScalePane();
		pScale->SetRange3Color(GetCtrlColor(m_clrRg3));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}

}

void CTestGaugeDlg::OnStnClickedPtcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrPt.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		
		m_clrPt.SetColor(dlg.GetColor());
		CPointer* pPt = m_gauge.GetPointer();
		pPt->SetNeedleColor(GetCtrlColor(m_clrPt));
		//m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnStnClickedBorderClr()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrBorder.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrBorder.SetColor(dlg.GetColor());
		CDial* pDial = m_gauge.GetDial();
		pDial->SetBorderColor(GetCtrlColor(m_clrBorder));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnStnClickedFrmClr1()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrFrm1.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrFrm1.SetColor(dlg.GetColor());
		CDial* pDial = m_gauge.GetDial();
		pDial->SetFrameColor(GetCtrlColor(m_clrFrm1),
			GetCtrlColor(m_clrFrm2));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnStnClickedFrmClr2()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrFrm2.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrFrm2.SetColor(dlg.GetColor());
		CDial* pDial = m_gauge.GetDial();
		pDial->SetFrameColor(GetCtrlColor(m_clrFrm1),
			GetCtrlColor(m_clrFrm2));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnStnClickedLableClr()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrLabel.GetColor());
	if (dlg.DoModal() == IDOK)
	{
		m_clrLabel.SetColor(dlg.GetColor());
		CScalePane* pScale = m_gauge.GetScalePane();
		pScale->SetMajorColor(GetCtrlColor(m_clrLabel));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}



void CTestGaugeDlg::OnNMReleasedcaptureSliderFrm(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CDial *pDial = m_gauge.GetDial();
	pDial->SetFrameWidth((float)m_sldFrmW.GetPos());
	m_gauge.Redraw();
	*pResult = 0;
}


void CTestGaugeDlg::OnNMReleasedcaptureSliderRg1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CScalePane *pScale = m_gauge.GetScalePane();
	pScale->SetRange1End((float)m_sldRg1Clr.GetPos());
	m_sldRg2Clr.SetPos((int)pScale->GetRange2End());
	m_gauge.Redraw();
	*pResult = 0;
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderRg2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CScalePane *pScale = m_gauge.GetScalePane();
	pScale->SetRange2End((float)m_sldRg2Clr.GetPos());
	m_sldRg1Clr.SetPos((int)pScale->GetRange1End());
	m_gauge.Redraw();
	*pResult = 0;
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderPt(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CPointer *pPt = m_gauge.GetPointer();
	pPt->SetNeedleLen((float)m_sldPt.GetPos());
	m_gauge.Invalidate();
	*pResult = 0;
}

void CTestGaugeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (pScrollBar)
	{
		int iID = pScrollBar->GetDlgCtrlID();
		if (iID == IDC_SLIDER_VALUE)
		{
			
			m_gauge.SetValue((float)m_sldValue.GetPos());
			m_gauge.Invalidate();
		}
	
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}




BOOL CTestGaugeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		int iID = ::GetDlgCtrlID(pMsg->hwnd);
		CScalePane *pScale = m_gauge.GetScalePane();
		if ((iID == IDC_EDIT_MAX || iID == IDC_EDIT_MIN) && UpdateData())
		{
			if (m_fMin > m_fMax)
			{
				float fTmp = m_fMax;
				m_fMax = m_fMin;
				m_fMin = fTmp;
				UpdateData(FALSE);
			}
			pScale->SetScaleRagne(m_fMin, m_fMax);
			m_sldRg1Clr.SetRange((int)m_fMin, (int)m_fMax);
			m_sldRg1Clr.SetPos((int)pScale->GetRange1End());
			m_sldRg2Clr.SetRange((int)m_fMin, (int)m_fMax);
			m_sldRg2Clr.SetPos((int)pScale->GetRange2End());
			float fV = m_gauge.GetValue();
			if (fV > m_fMax)
				fV = m_fMax;
			else if (fV < m_fMin)
				fV = m_fMin;
			m_gauge.SetValue(fV);
			m_sldValue.SetRange((int)m_fMin, (int)m_fMax, TRUE);
			m_sldValue.SetPos((int)fV);
			m_gauge.Redraw();
		}
		else if (iID == IDC_EDIT_MAJOR && UpdateData())
		{
			pScale->SetMajorSteps(m_iMS);
			m_gauge.Redraw();

		}
		else if (iID == IDC_EDIT_MINOR && UpdateData())
		{
			pScale->SetMinorSteps(m_iMinS);
			m_gauge.Redraw();

		}
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTestGaugeDlg::OnStnClickedMinorClr()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrMinor.GetColor());
	if (dlg.DoModal() == IDOK)
	{

		m_clrMinor.SetColor(dlg.GetColor());
		CScalePane* pScale = m_gauge.GetScalePane();
		pScale->SetMinorColor(GetCtrlColor(m_clrMinor));
		m_gauge.Redraw();
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderRgw(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CScalePane *pScale = m_gauge.GetScalePane();
	pScale->SetWidth((float)m_sldRgW.GetPos());
	m_gauge.Redraw();
	*pResult = 0;
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderTickOffset(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CScalePane *pScale = m_gauge.GetScalePane();
	pScale->SetTickOffset((float)m_sldTickOffset.GetPos());
	m_gauge.Redraw();
	*pResult = 0;
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderLabelOffset(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CScalePane *pScale = m_gauge.GetScalePane();
	pScale->SetLabelOffset((float)m_sldLabelOffset.GetPos());
	m_gauge.Redraw();
	*pResult = 0;
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderTicklen(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CScalePane *pScale = m_gauge.GetScalePane();
	float fL = (float)m_sldTickLen.GetPos();
	
	pScale->SetMajorSize(SizeF(3.0, fL));
	pScale->SetMinorSize(SizeF(1.0f, fL));
	m_gauge.Redraw();

	*pResult = 0;
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderRgOffset(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CScalePane *pScale = m_gauge.GetScalePane();
	float fL = (float)m_sldRgOffset.GetPos();
	pScale->SetRgBarOffset(fL);
	m_gauge.Redraw();
	*pResult = 0;
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderValue(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTestGaugeDlg::OnStnClickedDigiclr()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg(m_clrDigital.GetColor());
	if (dlg.DoModal() == IDOK)
	{

		m_clrDigital.SetColor(dlg.GetColor());
		CDigitalDisplay *pLED = m_gauge.GetLed();
		pLED->SetColor(GetCtrlColor(m_clrDigital));
		m_gauge.Invalidate(FALSE);
	}
}

void CTestGaugeDlg::OnNMReleasedcaptureSliderDigi(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CDigitalDisplay *pLed = m_gauge.GetLed();
	pLed->SetCharSize((float)m_sldDigital.GetPos());
	m_gauge.Invalidate(FALSE);
	*pResult = 0;
}

void CTestGaugeDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bHighLight = !m_bHighLight;
	m_gauge.SetHighlight(m_bHighLight);
	UpdateData(FALSE);
	m_gauge.Invalidate();
}
