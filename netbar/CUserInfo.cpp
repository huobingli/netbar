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
	MD5Update(&md5, encrypt, (int)strlen((char *)encrypt));//ֻ�Ǹ��м䲽��
	MD5Final(&md5, decrypt);//32λ

							// �õ������MD5����
	CString strTmp;
	for (i = 0; i < 16; i++) {
		strTmp.Format(_T("%02x"), decrypt[i]);
		m_strPasswordMd5 += strTmp;
	}

	// �õ��м���ʱ"�û���+md5����"���
	strTmp = m_strUsername + _T("+") + m_strPasswordMd5;

	// תbase64
	str = strTmp.GetBuffer(0);
	unsigned char *encrypt2 = (unsigned char *)str.c_str();

	std::string normal, encoded;
	int len = strTmp.GetLength();
	Base64 base;
	encoded = base.Encode(encrypt2, len);

	// �õ�base64("�û���+md5����")
	m_strUrlParam = encoded.c_str();
}