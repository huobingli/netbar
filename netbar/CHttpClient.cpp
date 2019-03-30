// HttpClient.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "CHttpClient.h"  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CHttpClient::CHttpClient(LPCTSTR strAgent)
{
	m_pSession = new CInternetSession(strAgent);
	m_pConnection = NULL;
	m_pFile = NULL;
}


CHttpClient::~CHttpClient(void)
{
	Clear();

	if (m_pSession != NULL)
	{
		m_pSession->Close();
		delete m_pSession;
		m_pSession = NULL;
	}
}


//���������
//������
//����ֵ��
void CHttpClient::Clear()
{
	if (m_pFile != NULL)
	{
		m_pFile->Close();
		delete m_pFile;
		m_pFile = NULL;
	}

	if (m_pConnection != NULL)
	{
		m_pConnection->Close();
		delete m_pConnection;
		m_pConnection = NULL;
	}
}

//������Httpִ������
//������
//����ֵ��
int CHttpClient::ExecuteRequest(int strMethod, LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse)
{
	int             nResult;
	CString         strServer;
	CString         strObject;
	DWORD           dwServiceType;
	INTERNET_PORT		nPort;
	DWORD           dwRet;
	CString         strUtf8;
	DWORD           dwErrorCode;

	nResult = HTTP_FAILURE;

	AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort);

	if (AFX_INET_SERVICE_HTTP != dwServiceType && AFX_INET_SERVICE_HTTPS != dwServiceType)
	{
		return HTTP_FAILURE;
	}

	try
	{
		m_pConnection = m_pSession->GetHttpConnection(strServer, dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_CONNECT : SECURE_CONNECT, nPort);
		m_pFile = m_pConnection->OpenRequest(strMethod, strObject, NULL, 1, NULL, NULL, (dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_REQUEST : SECURE_REQUEST));

		m_pFile->AddRequestHeaders(_T("Accept: */*,application/json"));
		m_pFile->AddRequestHeaders(_T("Accept-Charset:UTF8"));
		m_pFile->AddRequestHeaders(_T("Accept-Language: zh-cn;q=0.8,en;q=0.6,ja;q=0.4"));
		m_pFile->AddRequestHeaders(_T("Content-Type:application/json"));

		m_pFile->SendRequest(NULL, 0, (LPVOID)(LPCTSTR)strPostData, strPostData == NULL ? 0 : CString(strPostData).GetLength());

		m_pFile->QueryInfoStatusCode(dwRet);

		if (dwRet == HTTP_STATUS_OK)
		{
			nResult = HTTP_SUCCESS;
		}

		m_pFile->ReadString(strUtf8);
		strResponse = UTF8AndUnicode_Convert(strUtf8, CP_UTF8, CP_ACP);

		Clear();
	}
	catch (CInternetException *e)
	{
		Clear();

		dwErrorCode = e->m_dwError;
		e->Delete();

		strResponse.Format(_T("CInternetException error, error code = %d!"), dwErrorCode);

		if (dwErrorCode == ERROR_INTERNET_TIMEOUT)
		{
			return HTTP_TIMEOUT;
		}
		else
		{
			return HTTP_FAILURE;
		}
	}

	return nResult;
}

//������Http��ȡ
//������
//����ֵ��
int CHttpClient::HttpGet(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse)
{
	return ExecuteRequest(CHttpConnection::HTTP_VERB_GET, strUrl, NULL, strResponse);
}

//������Http�ʼ�
//������
//����ֵ��
int CHttpClient::HttpPost(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse)
{
	return ExecuteRequest(CHttpConnection::HTTP_VERB_POST, strUrl, strPostData, strResponse);
}

//������Http�ύ
//������
//����ֵ��
int CHttpClient::HttpPut(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse)
{
	return ExecuteRequest(CHttpConnection::HTTP_VERB_PUT, strUrl, strPostData, strResponse);
}

//������Unicode��UTF-8ת��
//������
//����ֵ��
CString CHttpClient::UTF8AndUnicode_Convert(CString &strSource, UINT nSourceCodePage, UINT nTargetCodePage)
{
	CString        strTarget;

	wchar_t        *pWideBuf;
	int            nWideBufLen;

	char           *pMultiBuf;
	int            nMiltiBufLen;

	int            nSourceLen;

	nSourceLen = strSource.GetLength();
	nWideBufLen = MultiByteToWideChar(nSourceCodePage, 0, (LPCCH)(LPCTSTR)strSource, -1, NULL, 0);

	pWideBuf = new wchar_t[nWideBufLen + 1];
	memset(pWideBuf, 0, (nWideBufLen + 1) * sizeof(wchar_t));

	MultiByteToWideChar(nSourceCodePage, 0, (LPCCH)(LPCTSTR)strSource, -1, (LPWSTR)pWideBuf, nWideBufLen);

	pMultiBuf = NULL;
	nMiltiBufLen = WideCharToMultiByte(nTargetCodePage, 0, (LPWSTR)pWideBuf, -1, (char *)pMultiBuf, 0, NULL, NULL);

	pMultiBuf = new char[nMiltiBufLen + 1];
	memset(pMultiBuf, 0, nMiltiBufLen + 1);

	WideCharToMultiByte(nTargetCodePage, 0, (LPWSTR)pWideBuf, -1, (char *)pMultiBuf, nMiltiBufLen, NULL, NULL);

	strTarget.Format(_T("%s"), pMultiBuf);

	delete pWideBuf;
	delete pMultiBuf;

	return strTarget;
}