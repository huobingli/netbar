#pragma once
#include "CSingleton.h"
#include "stdafx.h"

class CUserInfo
{
public:
	CUserInfo(const CString& strName, const CString& strPassword);
	~CUserInfo();

	CString GetUrlParam() { return m_strUrlParam; }
private:
	CString m_strName;
	CString m_strPassword;
	CString m_strUrlParam;
};

//typedef CSingleton<CUserInfo> CUserInfo

typedef TSingletonHolder<CUserInfo> CUserInfoHolder;