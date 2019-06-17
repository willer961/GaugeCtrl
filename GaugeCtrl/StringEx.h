#pragma once



	class CStringEx :
		public CString
	{
	public:
		CStringEx(CString str);
		CStringEx();
		~CStringEx(void);
		static CString FormatString( __in __format_string PCXSTR pszFormat,  ... );
		void Split(CString strSplit, CStringArray &arr);
		long ToInteger();
		void operator=(CString&str)
		{
			*this = CStringEx(str);
		}
		void operator=(const TCHAR str[])
		{
			*this = CStringEx(str);
		}
		void FromWStr(LPWSTR pStr);
		void FromMStr(LPSTR pStr);
		void ToWStr(LPWSTR &pWStr);
		void ToMStr(LPSTR &pStr);
		static int W2MBC(LPWSTR lpIn, LPSTR& lpOut);
		static int MBC2W(LPSTR lpIn, LPWSTR& lpOut);
	};

