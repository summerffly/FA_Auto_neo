
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include "Thread.h"
#include <unistd.h>

using namespace std;

class CMultiThread: public CThread
{
public:
    CMultiThread();    // 构造函数
    ~CMultiThread();    // 析构函数

    void Run();
};

//------------------------------//
//   River flows in summer
//------------------------------//
