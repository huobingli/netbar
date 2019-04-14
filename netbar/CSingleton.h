#pragma once
class CSingleton
{
private:
	CSingleton() //���캯����˽�е�
	{
	}
public:
	static CSingleton * GetInstance()
	{
		static CSingleton *m_pInstance;
		if (m_pInstance == nullptr)  //�ж��Ƿ��һ�ε���
			m_pInstance = new CSingleton();
		return m_pInstance;
	}
};