
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

// 线程安全(加锁)的经典懒汉实现

template<class T>
class Singleton
{
public:
    Singleton();
    ~Singleton();

    static T* GetInstance();
    static pthread_mutex_t m_mutex;

private:
    static T* m_pInstance;
};

template<class T>
pthread_mutex_t Singleton<T>::m_mutex;

template<class T>
T* Singleton<T>::m_pInstance = NULL;

template<class T>
Singleton<T>::Singleton()
{
    pthread_mutex_init(&m_mutex, NULL);
}

template<class T>
Singleton<T>::~Singleton()
{
    pthread_mutex_destroy(&m_mutex);
}

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

#endif

//------------------------------//
//   River flows in summer
//------------------------------//
