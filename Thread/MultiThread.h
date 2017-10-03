
//------------------------------//
//   Coded by 番茄_summer
//   @20171002
//   @summer studio
//
//   River flows in summer
//------------------------------//

#include "Thread.h"
#include <unistd.h>

using namespace std;

class CMultiThread: public CThread
{  
public:  
    void Run();
    //static pthread_mutex_t mutex;   // 互斥量同步
};
