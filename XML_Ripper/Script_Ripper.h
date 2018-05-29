
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

    void VersionRipper();
    void MonthRipper();

    void MonthRangeGenerator();
    void MonthRangeDuplicator(vector<string> &vec_str_DestMonth);
    bool IsIncludeMonthRange(const string str_SelMonth);

    string GetVersion();
    string GetOriginMonth();
    string GetCurrentMonth();

private:
    CXMLRipper m_cls_XMLRipper;
    string m_str_ScriptFilePath;

    string m_str_Version;
    string m_str_OriginMonth;
    string m_str_CurrentMonth;
    unsigned int m_uni_OriginMonth;
    unsigned int m_uni_CurrentMonth;

    vector<string> m_vec_str_Title;
    vector<string> m_vec_str_SubMonth;
    vector<string> m_vec_str_Tail;
    vector<string> m_vec_str_DPS;

    vector<string> m_vec_str_Month;   // Month需要计算生成
};


//------------------------------//
//   River flows in summer
//------------------------------//
