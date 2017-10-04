
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "MultiThread.h"

using namespace std;

pthread_mutex_t CMultiThread::mutex;

CMultiThread::CMultiThread()
{
    pthread_mutex_init(&mutex, NULL);
}

CMultiThread::~CMultiThread()
{
    pthread_mutex_destroy(&mutex);
}

void CMultiThread::Run()
{  
    int number = 0;
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);

        cout << "Current number is " << number++;
        cout << " PID is " << getpid() << " TID is " << GetThreadID() << endl;
        sleep(1);

        pthread_mutex_unlock(&mutex);
    }
}

//------------------------------//
//   River flows in summer
//------------------------------//
