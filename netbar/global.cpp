#include "global.h"

CString UTF8ToGBK(const char* pUTF8Str)
{
	CString strResult;

	if (NULL == pUTF8Str || 0 == pUTF8Str[0])
	{
		return strResult;
	}

	wchar_t * pUnicodeStr = NULL;
	do
	{
		int nRetLen = 0;
		nRetLen = ::MultiByteToWideChar(CP_UTF8, 0, pUTF8Str, -1, NULL, NULL); //Unicode 编码所需空间

		if (0 == nRetLen)
		{
			break;
		}

		pUnicodeStr = new WCHAR[nRetLen + 1];
		nRetLen = ::MultiByteToWideChar(CP_UTF8, 0, pUTF8Str, -1, pUnicodeStr, nRetLen); //转换到Unicode

		if (0 == nRetLen) // fail
		{
			break;
		}

		nRetLen = ::WideCharToMultiByte(CP_ACP, 0, pUnicodeStr, -1, NULL, NULL, NULL, NULL); //获取转换到GBK编码长度
		if (0 == nRetLen)
		{
			break;
		}

		nRetLen = ::WideCharToMultiByte(CP_ACP, 0, pUnicodeStr, -1, strResult.GetBuffer(nRetLen), nRetLen, NULL, NULL); //获取转换到GBK编码长度

		strResult.ReleaseBuffer();
	} while (FALSE);

	if (pUnicodeStr != NULL)
	{
		delete pUnicodeStr;
		pUnicodeStr = NULL;
	}

	return strResult;
}