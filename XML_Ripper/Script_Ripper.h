
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "./../X_Frame/X_Tool.h"
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
    void SalaryRipper();
    void SumRipper();
    void TitleRipper();
    void TitleDeepRipper();
    void TailRipper();
    void CAFRipper();
    void RoomRipper();
    void SubMonthRipper();
    void FileRipper();
    void BakupPathRipper();

    /****************************************/
    //   Month 操作区
    /****************************************/
    void ExMonthGenerator();
    void MonthRangeGenerator();
    bool IsIncludeMonthRange(const string str_SelMonth);

    /****************************************/
    //   读取 Script
    /****************************************/
    string GetVersion();
    string GetOriginMonth();
    string GetCurrentMonth();
    string GetPreviousMonth();
    string GetOriginSum();
    string GetCurrentSum();
    string GetCAFSum();
    int GetCAFIndex();
    int GetSubMonthNum();
    unsigned int GetMonthSalary();

    void MonthRangeDuplicator(vector<string> &vec_str_DestMonth);
    void TitleDuplicator(vector<string> &vec_str_Dest);
    void TitleDeepDuplicator(vector<string> &vec_str_Dest);
    void TailDuplicator(vector<string> &vec_str_Dest);
    void CAFDuplicator(vector<string> &vec_str_Dest);
    void RoomDuplicator(vector<string> &vec_str_Dest);
    void SubMonthDuplicator(vector<string> &vec_str_Dest);
    void FileDuplicator(vector<string> &vec_str_Dest);
    void BakupPathDuplicator(vector<string> &vec_str_Dest);

    /****************************************/
    //   CMD Translater
    /****************************************/
    string TitleTranslater(const string str_TitleCMD);
    string SubMonthTranslater(const string str_SubMonthCMD);

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
    string m_str_PreviousMonth;
    unsigned int m_uni_OriginMonth;
    unsigned int m_uni_CurrentMonth;
    unsigned int m_uni_PreviousMonth;
    vector<string> m_vec_str_Month;   // Month需要计算生成

    unsigned int m_uni_MonthSalary;

    string m_str_OriginSum;
    string m_str_CurrentSum;
    string m_str_CAFSum;

    unsigned int m_uni_TitleNum;
    unsigned int m_uni_TitleDeepNum;
    unsigned int m_uni_TailNum;
    unsigned int m_uni_CAFNum;
    unsigned int m_uni_CAFIndex;
    unsigned int m_uni_RoomNum;
    unsigned int m_uni_SubMonthNum;
    unsigned int m_uni_FileNum;
    unsigned int m_uni_BakupPathNum;
    vector<string> m_vec_str_Title;
    vector<string> m_vec_str_TitleDeep;
    map<string, string> m_map_TitleDeep;
    vector<string> m_vec_str_Tail;
    vector<string> m_vec_str_CAF;
    vector<string> m_vec_str_Room;
    vector<string> m_vec_str_SubMonth;
    map<string, string> m_map_SubMonth;
    vector<string> m_vec_str_File;
    vector<string> m_vec_str_BakupPath;
};


//------------------------------//
//   River flows in summer
//------------------------------//
