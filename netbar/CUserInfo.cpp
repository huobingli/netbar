#include "CUserInfo.h"
#include "global.h"


CUserInfo::CUserInfo()
{
	

	
}


CUserInfo::~CUserInfo()
{
}


void CUserInfo::SetUrlParam(const CString& strName, const CString& strPassword)
{
	m_strUsername = strName;
	m_strPassword = strPassword;

	int i;
	//unsigned char encrypt[] = "admin";//"admin";//21232f297a57a5a743894a0e4a801fc3
	unsigned char decrypt[16];

	std::string str = m_strPassword.GetBuffer(0);
	unsigned char *encrypt = (unsigned char *)str.c_str();

	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, encrypt, (int)strlen((char *)encrypt));//只是个中间步骤
	MD5Final(&md5, decrypt);//32位

							// 得到密码的MD5加密
	CString strTmp;
	for (i = 0; i < 16; i++) {
		strTmp.Format(_T("%02x"), decrypt[i]);
		m_strPasswordMd5 += strTmp;
	}

	// 得到中间临时"用户名+md5密码"组合
	strTmp = m_strUsername + _T("+") + m_strPasswordMd5;

	// 转base64
	str = strTmp.GetBuffer(0);
	unsigned char *encrypt2 = (unsigned char *)str.c_str();

	std::string normal, encoded;
	int len = strTmp.GetLength();
	Base64 base;
	encoded = base.Encode(encrypt2, len);

	// 得到base64("用户名+md5密码")
	m_strUrlParam = encoded.c_str();
}