
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <iostream>
#include <pthread.h>

using namespace std;

class CThread
{
public:
    /********************
         线程状态参数
    ********************/
    static const int THREAD_STATUS_NEW = 0;       // 新建
    static const int THREAD_STATUS_RUNNING = 1;   // 正在运行
    static const int THREAD_STATUS_EXIT = -1;     // 结束

    CThread();    // 构造函数
    ~CThread();   // 析构函数

    bool Start();                          // 开始执行线程
    virtual void Run()=0;                  // 纯虚函数 & 现成的运行实体
    void Join();                           // 等待线程直至退出    
    //void Join(unsigned long millisTime);   // 等待线程退出或者超时
    
    pthread_t GetThreadID();   // 获取线程ID
    int GetThreadState();      // 获取线程状态 

private:  
    pthread_t m_ptt_ThreadID;   // 线程ID  
    int m_int_ThreadStatus;   // 线程状态
    static void *thread_proxy_func(void *args);   // 获取执行方法的指针
    void* run();   // 内部执行方法
};

//------------------------------//
//   River flows in summer
//------------------------------//
