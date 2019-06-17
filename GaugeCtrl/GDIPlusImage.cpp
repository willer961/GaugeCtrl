
#include "stdafx.h"
#include "GDIPlusImage.h"
#include "StringEx.h"
using namespace  Gdiplus;


CGDIPlusImage::CGDIPlusImage(void)
{
	m_pImg = 0;
}

CGDIPlusImage::CGDIPlusImage(CString strFile)
{
	FormFile(strFile);

}

CGDIPlusImage::CGDIPlusImage(CString strType, int nID)
{
	FromResource(strType, nID);

}

CGDIPlusImage::~CGDIPlusImage(void)
{
	Release();
}

/******************************************************************************/
// 从文件导入图片
/******************************************************************************/
void CGDIPlusImage::FormFile( CString strFile )
{
	Release();
	LPWSTR pBuf;
	CStringEx(strFile).ToWStr(pBuf);
	m_pImg = new Gdiplus::Bitmap(pBuf);
	if (m_pImg->GetLastStatus() != Ok)
	{
		delete m_pImg;
		m_pImg = NULL;
	}
	delete []pBuf;
}

/******************************************************************************/
// 从资源导入图片
// strType：资源类型
// nID：资源编号
/******************************************************************************/
void CGDIPlusImage::FromResource(CString strType, int nID)
{
	Release();
	HMODULE hIns = (HMODULE)AfxGetApp()->m_hInstance;
	HRSRC hRes = FindResource(hIns, CStringEx::FormatString(_T("#%d"), nID), strType);
	HGLOBAL hGblRes = LoadResource(hIns, hRes);

	DWORD nSize = SizeofResource(hIns, hRes);
	LPVOID lpBuffer = LockResource(hGblRes);

	HGLOBAL hGbl = GlobalAlloc(GMEM_MOVEABLE , nSize);
	LPVOID lpRs = GlobalLock(hGbl);
	memcpy(lpRs, lpBuffer, nSize);
	IStream* st = 0;
	CreateStreamOnHGlobal(hGbl, FALSE, &st);
	if (m_pImg)
	{
		delete m_pImg;
		m_pImg = 0;
	}
	m_pImg = new Bitmap(st);

	GlobalFree(hGbl);
	FreeResource(hGblRes);
	st->Release();
}

int CGDIPlusImage::GetImageCLSID(const WCHAR* format, CLSID* pCLSID)  
{   
	//得到格式为format的图像文件的编码值，访问该格式图像的COM组件的GUID值保存在pCLSID中  
	UINT num  = 0;  
	UINT size = 0; 

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;  
	GetImageEncodersSize(&num,   &size); 

	// 编码信息不可用 
	if(size == 0)  
		return FALSE;   

	//分配内存  
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));  
	if(pImageCodecInfo == NULL)  
		return FALSE;   //   分配失败 

	//获得系统中可用的编码方式的所有信息  
	GetImageEncoders(num, size, pImageCodecInfo); 

	//在可用编码信息中查找format格式是否被支持  
	for(UINT i = 0; i < num; ++i)  
	{
		//MimeType：编码方式的具体描述  
		if(wcscmp(pImageCodecInfo[i].MimeType, format) == 0)  
		{  
			*pCLSID = pImageCodecInfo[i].Clsid;  
			free(pImageCodecInfo);  
			return TRUE;  
		}  
	} 
	
	// 必须在退出前释放资源
	free(pImageCodecInfo);  
	return FALSE;  
}

BOOL CGDIPlusImage::SaveImage(Image *pImg, const WCHAR* format, CStringW fileName)
{
	CLSID clImageClsid;

	GetImageCLSID(format, &clImageClsid);
	return Ok == pImg->Save(fileName, &clImageClsid);
}