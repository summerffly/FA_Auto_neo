
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "Thread.h"
#include <unistd.h>

using namespace std;

class CMultiThread: public CThread
{
public:
    CMultiThread();    // 构造函数
    ~CMultiThread();    // 析构函数

    void Run();

    static pthread_mutex_t mutex;   // 互斥量同步
};

//------------------------------//
//   River flows in summer
//------------------------------//
