// TestGauge.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestGaugeApp:
// �йش����ʵ�֣������ TestGauge.cpp
//

class CTestGaugeApp : public CWinApp
{
public:
	CTestGaugeApp();

// ��д
	public:
	virtual BOOL InitInstance();
protected:

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CTestGaugeApp theApp;