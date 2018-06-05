
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <map>
#include "./../X_Frame/CmdLib.h"
#include "./../X_Frame/X_Tool.h"
#include "./../X_Frame/Singleton.h"
#include "./../XML_Ripper/Script_Ripper.h"
#include "./../FA_Layer/FAitfX.h"

using namespace std;


class CASitfX
{
public:
    friend class Singleton<CASitfX>;
    
    CASitfX();
    ~CASitfX();

    /****************************************/
    //   FA全系统 计算区
    /****************************************/
    void CheckFA();
    void UpdateFA();

    /****************************************/
    //   SUM 计算区
    /****************************************/
    int CheckSum(int int_OFlag);
    void UpdateSum(int int_OFlag);

    /****************************************/
    //   统计区
    /****************************************/
    void AnalysisMonthTrend_CSM();
    void AnalysisMonthTrend_ROOM();

    /****************************************/
    //   展示区
    /****************************************/
    void ShowMDRawSubMonthTraversal(const string str_SelMonth, bool bol_NumFlag);

    /****************************************/
    //   其他
    /****************************************/
    void AppendNextMonth(const string str_SelMonth);
    void HelpAll();
};

//------------------------------//
//   River flows in summer
//------------------------------//
