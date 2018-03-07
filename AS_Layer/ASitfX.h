
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <map>
#include "./../X_Frame/X_Tool.h"
#include "./../X_Frame/Singleton.h"
#include "./../X_Frame/X_CFGLoader.h"
#include "./../FA_Layer/FAitfX.h"

using namespace std;


class CASitfX
{
public:
    friend class Singleton<CASitfX>;
    
    CASitfX();
    ~CASitfX();

    /****************************************/
    //   分析月度趋势 操作区
    /****************************************/
    void AnalysisMonthTrend_CSM();
    void AnalysisMonthTrend_ROOM();

private:
    //~;
};

//------------------------------//
//   River flows in summer
//------------------------------//
