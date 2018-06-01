
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <map>
#include "./../X_Frame/CmdLib.h"
#include "./../X_Frame/X_Tool.h"
#include "./../X_Frame/Singleton.h"
#include "./../X_Frame/X_CFGLoader.h"
#include "./../XML_Ripper/Script_Ripper.h"
#include "./../FA_Layer/FAitfX.h"

using namespace std;


class CASitfX
{
public:
    friend class Singleton<CASitfX>;
    
    CASitfX();
    ~CASitfX();

    void CheckFA();
    void UpdateFA();

    /****************************************/
    //   统计化 操作区
    /****************************************/
    void AnalysisMonthTrend_CSM();
    void AnalysisMonthTrend_ROOM();

    /****************************************/
    //   展示化 操作区
    /****************************************/
    void ShowMDRawSubMonthTraversal(const string str_SelMonth, bool bol_NumFlag);

    /****************************************/
    //   帮助提示
    /****************************************/
    void HelpAll();
};

//------------------------------//
//   River flows in summer
//------------------------------//
