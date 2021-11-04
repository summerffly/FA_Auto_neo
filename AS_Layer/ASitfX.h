
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <map>
#include "./../CMD_Handler/DefCMD.h"
#include "./../X_Frame/X_Tool.h"
#include "./../X_Frame/Singleton.h"
#include "./../FA_Layer/FAitfX.h"

using namespace std;


class CASitfX
{
public:
    friend class Singleton<CASitfX>;
    
    CASitfX();
    ~CASitfX();

    /****************************************/
    //   FA全系统
    /****************************************/
    void CheckFA();
    void UpdateFA();
    void ShowFA();

    /****************************************/
    //   SUM
    /****************************************/
    int CheckSum(int int_OFlag);
    void UpdateSum(int int_OFlag);
    void ShowSum();

    /****************************************/
    //   Month
    /****************************************/
    int CheckMonth(const string str_SelMonth, int int_OFlag);
    void CheckMonthTraversal();
    void UpdateMonth(const string str_SelMonth, int int_OFlag);
    void UpdateMonthTraversal();
    void ShowMonth(const string str_SelMonth);

    /****************************************/
    //   统计区
    /****************************************/
    void AnalysisMonthTrend_EXP();
    void AnalysisMonthTrend_LIFE();
    void AnalysisMonthTrend_ROOM();
    void AnalysisMonthTrend_CSM();
    void AnalysisMonthTrend(const string str_MonthKey);

    /****************************************/
    //   展示区
    /****************************************/
    void ShowAllSubMonth(const string str_SelMonth);

    /****************************************/
    //   操作区
    /****************************************/
    void PrintAllSubMonth(const string str_SelMonth, bool bol_NumFlag);
    void PrintSubMonthTraversal(const string str_SubMonthKey, bool bol_NumFlag);

    /****************************************/
    //   其他
    /****************************************/
    void AppendNextMonth(const string str_SelMonth);
};

//------------------------------//
//   River flows in summer
//------------------------------//
