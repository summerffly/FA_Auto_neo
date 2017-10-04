
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "Thread.h"

using namespace std;

CThread::CThread()  
{  
    m_ptt_ThreadID = 0;
    m_int_ThreadStatus = THREAD_STATUS_NEW;
}

CThread::~CThread()  
{  
    // Do Nothing
}

bool CThread::Start()
{
    //int iRet = 0;
    return pthread_create(&m_ptt_ThreadID, NULL, thread_proxy_func, this);
}

pthread_t CThread::GetThreadID()
{
    return m_ptt_ThreadID;
}

int CThread::GetThreadState()
{
    return m_int_ThreadStatus;
}
  
void CThread::Join()  
{  
    if (m_ptt_ThreadID > 0)
    {
        pthread_join(m_ptt_ThreadID, NULL);
    }
}

/*
void CThread::Join(unsigned long millisTime)  
{  
    if( m_ptt_ThreadID == 0 )
    {
        return;
    }

    if( millisTime == 0 )  
    {  
        Join();
    }
    else
    {  
        unsigned long k = 0;  
        while( (m_int_ThreadStatus != THREAD_STATUS_EXIT) && (k <= millisTime) )
        {
            usleep(100);
            k++;
        }
    }
}
*/

void *CThread::thread_proxy_func(void *args)
{
    CThread *pThread = static_cast<CThread *>(args);
    pThread->Run();
    return NULL;
}

void *CThread::run()
{
    m_int_ThreadStatus = THREAD_STATUS_RUNNING;
    m_ptt_ThreadID = pthread_self();
    Run();
    m_int_ThreadStatus = THREAD_STATUS_EXIT;
    m_ptt_ThreadID = 0;
    pthread_exit(NULL);
}

//------------------------------//
//   River flows in summer
//------------------------------//
