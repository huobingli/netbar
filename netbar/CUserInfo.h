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
private:
	CString m_strUsername;
	CString m_strPassword;
	CString m_strUrlParam;

	CString m_strPasswordMd5;
};

//typedef CSingleton<CUserInfo> CUserInfo

typedef TSingletonHolder<CUserInfo> CUserInfoHolder;