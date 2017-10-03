
//------------------------------//
//   Coded by 番茄_summer
//   @20171003
//   @summer studio
//
//   River flows in summer
//------------------------------//

#include "MultiThread.h"

using namespace std;

//pthread_mutex_t CMultiThread::mutex;

void CMultiThread::Run()
{  
    int number = 0;
    for (int i = 0; i < 10; i++)
    {
        //pthread_mutex_lock(&mutex);

        cout << "Current number is " << number++;
        cout << " PID is " << getpid() << " TID is " << GetThreadID() << endl;
        sleep(1);

        //pthread_mutex_unlock(&mutex);
    }
}
