////////////////////////////////////////////////////////////////////////////////
//
// 文件名称：GaugeCtrl.cpp
// 功    能：仪表盘控件
//
// 作    者：邓智宏
// 完成日期：2017-1-13
//
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GaugeCtrl.h"
#pragma comment(lib, "gdiplus.lib")
#include <math.h>
// CGaugeCtrl
using namespace Gdiplus;
IMPLEMENT_DYNAMIC(CGaugeCtrl, CWnd)

GdiplusStartupInput CGaugeCtrl::s_gdiplusStartupInput;
ULONG_PTR CGaugeCtrl::s_gdiplusToken = NULL;
//int CGaugeCtrl::s_nGauges = 0;

//////////////////////////////////////////////////////////////////////////
CGaugeCtrl::CGaugeCtrl()
{
	//if (s_gdiplusToken == NULL)
	//{
	//	Gdiplus::GdiplusStartup(&s_gdiplusToken, &s_gdiplusStartupInput, NULL);
	//}
	//s_nGauges++;
	RegisterWindowClass();
	m_alpha = 200;
	m_bHighlight = FALSE;
	m_fVal = 50.0f;
	m_pImgBk = NULL;
	m_fNumSize = 20.0f;
	m_ptLed = PointF(100.f, 160.f);

}

CGaugeCtrl::~CGaugeCtrl()
{
	if (m_pImgBk)
	{
		delete m_pImgBk;
		m_pImgBk = NULL;
	}
	//if ((--s_nGauges) == 0)
	//{
	//	Gdiplus::GdiplusShutdown(s_gdiplusToken);
	//}
}


BEGIN_MESSAGE_MAP(CGaugeCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CGaugeCtrl 消息处理程序


//----------------------------------------------------------------------//
// 注册窗体类
//----------------------------------------------------------------------//
BOOL CGaugeCtrl::RegisterWindowClass(void)
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetResourceHandle();

	if (!(::GetClassInfo(hInst, _T("GaugeCtrl"), &wndcls)))
	{
		wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
#ifndef _WIN32_WCE_NO_CURSOR
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
#else
		wndcls.hCursor          = 0;
#endif
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    =  _T("GaugeCtrl");

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}



void CGaugeCtrl::OnPaint()
{
	// 获取控件大小	
	CRect rc;
	GetDialRect(rc);
	// 使用双缓存绘制仪表
	Image * pImg = new Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB);
	Graphics* pGr = Graphics::FromImage(pImg);// 创建双缓存图
	pGr->SetSmoothingMode(SmoothingModeHighQuality);//平滑效果开启
	// 表盘、刻度已绘制成图片
	if (m_pImgBk)
		pGr->DrawImage(m_pImgBk, 0, 0, rc.Width(), rc.Height());
	// 计算当前数值下指针指向的角度并绘制仪表指针
	float fAg = m_scale.GetValueAngle(m_fVal);
	m_pointer.Draw(*pGr, fAg, PointF(rc.Width() / 2.0f, rc.Height() / 2.0f));
	// 判断是否需要绘制透明玻璃效果
	if (m_bHighlight)
		DrawHighlight(*pGr);
	// 绘制数显
	//m_led.Draw(*pGr, m_fVal, RectF(0.0f, rc.Height() * 4.0f / 5, (float)rc.Width(), m_fNumSize));
	m_led.Draw(*pGr, m_fVal, m_ptLed);
	// 将缓存图片会知道图形对象上
	CPaintDC dc(this); 
	Graphics gr(dc.GetSafeHdc());
	gr.SetSmoothingMode(SmoothingModeHighQuality);
	gr.DrawImage(pImg, 0, 0, rc.Width(), rc.Height());

	// 生成图片文件调试用
	
	delete pImg;// 释放缓存图片
}

/******************************************************************************/
// 控件子类化前，设置好仪表的大小
/******************************************************************************/
void CGaugeCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CWnd::PreSubclassWindow();
	CRect rc;
	GetDialRect(rc);
	m_scale.SetCenter(Rect(0, 0, rc.Width(), rc.Height()));
	m_scale.SetRgBarOffset(rc.Width() / 2.0f - 12);
	m_ptLed = PointF(rc.left + rc.Width() / 2.0f, rc.top + rc.Height() * 4 / 5.0f);
	CreateBkImage();// 将表盘、刻度绘制成图片

}

/******************************************************************************/
// 
/******************************************************************************/
void CGaugeCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
	m_scale.SetCenter(Rect(0, 0, cx, cy));
	//m_ticks.SetRadius((cx >> 1) - 12);
	CreateBkImage();// 将表盘、刻度绘制成图片
	CRect rc;
	GetDialRect(rc);
	m_ptLed = PointF(rc.left + rc.Width() / 2.0f, rc.top + rc.Height() * 4 / 5.0f);

}

/******************************************************************************/
// 绘制镜面效果
// gr:用于绘制的图形对象
/******************************************************************************/
void CGaugeCtrl::DrawHighlight(Graphics& gr)
{
	CRect rc;
	GetDialRect(rc);

	// 模糊区间
	float fOffset = m_dial.GetBorderWidth() + m_dial.GetFrameWidth() + rc.Height() * 0.02f;
	RectF hlRect(rc.Width() * 0.15f, fOffset, rc.Width() * 0.7f, rc.Height() * 0.4f);
	LinearGradientBrush br(hlRect, Color(m_alpha, 255, 255, 255), 
		Color::Transparent, LinearGradientModeVertical);
	hlRect.Inflate(0.0f, -1.0f);// 不进行扩展会显示边界线。画笔设置透明可否解决？
	gr.FillEllipse(&br, hlRect);
}

void CGaugeCtrl::SetValue(float fV, BOOL bUpdate)
{
	if (fV >= m_scale.GetMinValue() && fV <= m_scale.GetMaxValue())
	{
		m_fVal = fV;
		if (bUpdate)
			Invalidate(FALSE);
	}
}

/******************************************************************************/
// 创建表盘及刻度图片
/******************************************************************************/
void CGaugeCtrl::CreateBkImage(void)
{
	CRect rc;
	GetDialRect(rc);
	// 如果以经创建背景图片，需要先进行释放
	if (m_pImgBk)
	{
		delete m_pImgBk;
		m_pImgBk = NULL;
	}
	// 创建背景图，并绘制图片内容
	m_pImgBk = new Bitmap(rc.Width(), rc.Height());
	Graphics* pGr = Graphics::FromImage(m_pImgBk);
	pGr->SetSmoothingMode(SmoothingModeHighQuality);
	// 绘制表盘和指针
	m_dial.Draw(*pGr, Rect(0, 0, rc.Width() - 1, rc.Height() - 1));
	m_scale.Draw(*pGr, Rect(0, 0, rc.Width() - 1, rc.Height() - 1));
}

void CGaugeCtrl::Redraw(void)
{
	CreateBkImage();
	CWnd *pParent = GetParent();
	if (pParent)
		pParent->Invalidate(FALSE);
	else
		Invalidate(TRUE);
}


BOOL CGaugeCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
}
/******************************************************************************/
// 控件长宽不等时，计算绘图区间
/******************************************************************************/
void CGaugeCtrl::GetDialRect( CRect &rc )
{
	GetWindowRect(&rc);
	// 宽度大于高度
	if (rc.Width() > rc.Height())
	{
		rc.left += (rc.Width() - rc.Height()) / 2;
		rc.right = rc.left + rc.Height();
	}
	// 高度大于宽度
	else if (rc.Height() > rc.Width())
	{
		rc.top += (rc.Height() - rc.Width()) / 2;
		rc.bottom = rc.top + rc.Width();
	}
	// 从屏幕坐标转成控件坐标
	rc.OffsetRect(-rc.left, -rc.top);
}

/******************************************************************************/
// 自动进行控件元素布局，使用该方法后，所有用户定义的内容都会被覆盖
/******************************************************************************/
void CGaugeCtrl::AutoLayout(void)
{
	// 获取控件绘图区位置及大小
	CRect rc;
	GetDialRect(rc);
	float fW = float(rc.Width());
	// 设置刻度盘
	m_scale.SetRgBarOffset(fW * 0.45f);
	m_scale.SetTickOffset(fW * 0.45f);
	m_scale.SetWidth(2.0f);
	m_scale.SetLabelOffset(fW * 0.42f);
	m_scale.SetFont(Font(L"Times New Roma",fW * 0.05f, FontStyleRegular));
	m_scale.SetAngleRange(-210.f, 30.f);
	m_scale.SetMajorSize(SizeF(fW *0.01f, fW * 0.03f));
	
	// 设置表盘
	m_dial.SetFrameWidth(3.0f);

	m_pointer.SetNeedleLen(fW * 0.4f );
	m_pointer.SetCapSize(fW * 0.05f);
	m_pointer.SetAxisSize(fW *0.1f);
	// 设置led数显
	m_ptLed = PointF(rc.left + fW / 2.0f, rc.top + fW * 5 / 6.0f);
	m_led.SetCharSize(fW * 0.1f);
}
