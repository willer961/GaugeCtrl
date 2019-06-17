#pragma once
#include <GdiPlus.h>

class CGDIPlusImage
{
public:
	CGDIPlusImage(void);
	CGDIPlusImage(CString strFile);
	CGDIPlusImage(CString strType, int nID);
	void FromResource(CString strType, int nID);
	void FormFile( CString strFile );
	inline void Release()
	{	if (m_pImg){delete m_pImg;m_pImg = 0;}}
	virtual ~CGDIPlusImage(void);
	Gdiplus::Bitmap *GetImage(){return m_pImg;}
protected:
	static BOOL SaveImage(Gdiplus::Image *pImg, const WCHAR* format, CStringW fileName);
	static int GetImageCLSID(const WCHAR* format,CLSID* pCLSID);  
	Gdiplus::Bitmap *m_pImg;

};
