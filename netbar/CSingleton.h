#pragma once
class CSingleton
{
private:
	CSingleton() //构造函数是私有的
	{
	}
public:
	static CSingleton * GetInstance()
	{
		static CSingleton *m_pInstance;
		if (m_pInstance == nullptr)  //判断是否第一次调用
			m_pInstance = new CSingleton();
		return m_pInstance;
	}
};