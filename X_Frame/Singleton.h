
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

/**************************************************/
//   经典懒汉实现
//   线程安全(加锁)
//   template不支持分离式编译
/**************************************************/

template<class T>
class Singleton
{
public:
    Singleton();
    ~Singleton();

    static T* GetInstance();
    static T* GetInstance(const char *cha_FilePath);
    static pthread_mutex_t m_mutex;

private:
    static T* m_pInstance;
};

template<class T>
pthread_mutex_t Singleton<T>::m_mutex;

template<class T>
T* Singleton<T>::m_pInstance = NULL;


/**************************************************/
//   Singleton 构造函数
/**************************************************/
template<class T>
Singleton<T>::Singleton()
{
    pthread_mutex_init(&m_mutex, NULL);
}


/**************************************************/
//   Singleton 析构函数
/**************************************************/
template<class T>
Singleton<T>::~Singleton()
{
    pthread_mutex_destroy(&m_mutex);
}


/**************************************************/
//   GetInstance() 不带参数实现
/**************************************************/
template<class T>
T* Singleton<T>::GetInstance()
{
    if( m_pInstance == NULL )
    {
        pthread_mutex_lock(&m_mutex);
        if( m_pInstance == NULL )
            m_pInstance = new T;
        pthread_mutex_unlock(&m_mutex);
    }

    return m_pInstance;
}


/**************************************************/
//   GetInstance() 带参数实现
/**************************************************/
template<class T>
T* Singleton<T>::GetInstance(const char *cha_FilePath)
{
    if( m_pInstance == NULL )
    {
        pthread_mutex_lock(&m_mutex);
        if( m_pInstance == NULL )
            m_pInstance = new T(cha_FilePath);
        pthread_mutex_unlock(&m_mutex);
    }

    return m_pInstance;
}

#endif

//------------------------------//
//   River flows in summer
//------------------------------//
