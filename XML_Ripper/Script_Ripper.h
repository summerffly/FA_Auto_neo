
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "./../X_Frame/Singleton.h"
#include "XML_Ripper.h"

using namespace std;


class CScriptRipper
{
public:
    // 单例访问
    friend class Singleton<CScriptRipper>;

    CScriptRipper(const char *cha_xmlPath);
    ~CScriptRipper();

    /****************************************/
    //   解析 Script
    /****************************************/
    void VersionRipper();
    void MonthRipper();
    void SumRipper();
    void TitleRipper();
    void TitleDeepRipper();
    void SubMonthRipper();
    void TailRipper();
    void CAFRipper();

    void MonthRangeGenerator();
    bool IsIncludeMonthRange(const string str_SelMonth);

    /****************************************/
    //   读取 Script
    /****************************************/
    string GetVersion();
    string GetOriginMonth();
    string GetCurrentMonth();
    string GetOriginSum();
    string GetCurrentSum();

    void MonthRangeDuplicator(vector<string> &vec_str_DestMonth);
    void TitleDuplicator(vector<string> &vec_str_Dest);
    void TitleDeepDuplicator(vector<string> &vec_str_Dest);
    void SubMonthDuplicator(vector<string> &vec_str_Dest);
    void TailDuplicator(vector<string> &vec_str_Dest);
    void CAFDuplicator(vector<string> &vec_str_Dest);

    /****************************************/
    //   修改 Script
    /****************************************/
    void ModifyCurrentMonth(const string str_SelMonth);

private:
    CXMLRipper m_cls_XMLRipper;
    string m_str_ScriptFilePath;

    string m_str_Version;

    string m_str_OriginMonth;
    string m_str_CurrentMonth;
    unsigned int m_uni_OriginMonth;
    unsigned int m_uni_CurrentMonth;
    vector<string> m_vec_str_Month;   // Month需要计算生成

    string m_str_OriginSum;
    string m_str_CurrentSum;

    unsigned int m_uni_TitleNum;
    unsigned int m_uni_TitleDeepNum;
    unsigned int m_uni_SubMonthNum;
    unsigned int m_uni_TailNum;
    unsigned int m_uni_CAFNum;
    vector<string> m_vec_str_Title;
    vector<string> m_vec_str_TitleDeep;
    vector<string> m_vec_str_SubMonth;
    vector<string> m_vec_str_Tail;
    vector<string> m_vec_str_CAF;

    
};


//------------------------------//
//   River flows in summer
//------------------------------//
