#pragma once
// class CSingleton
// {
// private:
// 	CSingleton() //构造函数是私有的
// 	{
// 	}
// public:
// 	static CSingleton * GetInstance()
// 	{
// 		static CSingleton *m_pInstance;
// 		if (m_pInstance == nullptr)  //判断是否第一次调用
// 			m_pInstance = new CSingleton();
// 		return m_pInstance;
// 	}
// };

template <class TObject>
class TSingletonHolder
{
public:
	static TObject* Instance(bool bCreate = TRUE)
	{
		if (m_pInstance == NULL)
		{
			if (bCreate)
			{
				m_pInstance = new TObject;
				ASSERT(m_pInstance);
			}
		}
		return m_pInstance;
	}

	static void Release()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
protected:
	TSingletonHolder() {}
	virtual ~TSingletonHolder() {}
private:
	TSingletonHolder(const TSingletonHolder& src) {}
	static TObject* m_pInstance;
};

template <class TObject> TObject* TSingletonHolder<TObject>::m_pInstance = NULL;