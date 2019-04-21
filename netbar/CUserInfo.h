#pragma once
#include "CSingleton.h"
#include "stdafx.h"

class CUserInfo
{
public:
	CUserInfo();
	~CUserInfo();

	void SetUrlParam(const CString& strName, const CString& strPassword);
	CString GetUrlParam() { return m_strUrlParam; }

	void SetNetBarInfo(const CString& strName) { m_strNetInfo = strName; }
	CString GetNetBarInfo() { return m_strNetInfo; }
private:
	CString m_strUsername;
	CString m_strPassword;
	CString m_strUrlParam;

	CString m_strPasswordMd5;

	CString m_strNetInfo;
};

//typedef CSingleton<CUserInfo> CUserInfo

typedef TSingletonHolder<CUserInfo> CUserInfoHolder;