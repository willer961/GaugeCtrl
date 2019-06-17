
#include "StdAfx.h"
#include "StringEx.h"

CStringEx::CStringEx(CString str):CString(str)
{
		
}
CStringEx::CStringEx():CString()
{

}


CStringEx::~CStringEx(void)
{
	
}

/******************************************************************************/
// 格式化字符串，CString::Format的静态函数形式
/******************************************************************************/
CString CStringEx::FormatString( __in __format_string PCXSTR pszFormat,  ... )
{
	ATLASSERT( AtlIsValidString( pszFormat ) );
	CString str;
	va_list argList;
	va_start( argList, pszFormat );
	str.FormatV( pszFormat, argList );
	va_end( argList );
	return str;
}


/******************************************************************************/
// 返回一个字符串拆分为若干子字符串时所产生的字符串数组
// strRes：需要拆分的字符串
// strSplit：拆分标志
/******************************************************************************/
void CStringEx::Split(CString strSplit, CStringArray &arr)
{
	int curPos= 0;
	arr.RemoveAll();
	CString strTmp = Tokenize(strSplit,curPos);

	while (strTmp != _T(""))
	{
		arr.Add(strTmp);
		strTmp = Tokenize(strSplit,curPos);
	};
}

/******************************************************************************/
// 将一个字符串转换成整型数
// 返回值：转换成的整型数
/******************************************************************************/
long CStringEx::ToInteger()
{
	return _ttol(*this);
}

void CStringEx::FromWStr(LPWSTR pWStr)
{
#ifdef _UNICODE
	*this = pWStr;
#else
	LPSTR pStr;
	W2MBC(pWStr, pStr);
	*this = pStr;
	delete []pStr;
#endif

}
void CStringEx::FromMStr(LPSTR pStr)
{
#ifdef _UNICODE
	LPWSTR pWStr;
	MBC2W(pStr, pWStr);
	*this = pWStr;
	delete []pWStr;
#else
	*this = pStr;
#endif
}
void CStringEx::ToWStr(LPWSTR &pWStr)
{
	int nLen = GetLength();
#ifdef _UNICODE
	pWStr = new WCHAR[nLen + 1];
	pWStr[nLen] = 0;
	memcpy(pWStr, GetBuffer(), nLen << 1);
#else
	MBC2W(GetBuffer(), pWStr);
#endif
	ReleaseBuffer();

}
void CStringEx::ToMStr(LPSTR &pStr)
{
	int nLen = GetLength();
	pStr = new CHAR[nLen + 1];
	pStr[nLen] = 0;
#ifdef _UNICODE
	W2MBC(GetBuffer(), pStr);
#else
	memcpy(pStr, GetBuffer(), nLen);
#endif
	ReleaseBuffer();
}

int CStringEx::W2MBC(LPWSTR lpIn, LPSTR& lpOut)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, lpIn, -1, 0, 0,NULL,NULL);

	lpOut = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, lpIn, -1, lpOut, nLen,NULL,NULL);
	return nLen;
}

int CStringEx::MBC2W(LPSTR lpIn, LPWSTR& lpOut)
{
	int nLen = MultiByteToWideChar(CP_ACP, 0,lpIn, -1, NULL, NULL);
	lpOut = new WCHAR[nLen];
	MultiByteToWideChar(CP_ACP, 0, lpIn, -1, lpOut, nLen);
	return nLen;
}