
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>
#include <regex>

using namespace std;


class CLineEPer
{
public:
    CLineEPer();
    CLineEPer(const char *cha_LineBuffer);
    CLineEPer(const unsigned int uni_LineType, const int int_LineValue, const string str_LineContent);
    ~CLineEPer();

    int LineParser();
    void ValuePMParser(string str_ValuePM);

    /****************************************/
    //   属性获取
    /****************************************/
    unsigned int GetLineType();
    string GetLineContent();
    string GetFullLine();
    bool GetLineValuePM();
    unsigned int GeLineValueABS();
    int GetLineValue();
    bool GetLineModFlag();

    /****************************************/
    //   设置方法
    /****************************************/
    void SetLineValuePM(const bool bol_LineValuePM);
    void SetLineValueABS(const unsigned int uni_LineValueABS);
    void SetLineValue(const int int_LineValue);
    void SetLineContent(const char *cha_LineContent);
    void SetLineModFlag(const bool bol_LineModFlag);

    /****************************************/
    //   同步功能
    /****************************************/
    void UpdateValue(bool bol_UpdateDirection);
    void UpdateFullLine();

    /****************************************/
    //   综合功能
    /****************************************/
    bool IsContainKey(const char *cha_Key);

private:
    unsigned int m_uni_LineType;        // 行类型
    string m_str_LineContent;           // 行内容
    string m_str_FullLine;              // 整行内容
    bool m_bol_LineValuePM;             // 行金额_正负
    unsigned int m_uni_LineValueABS;    // 行金额_绝对值
    int m_int_LineValue;                // 行金额
    bool m_bol_LineModFlag;             // 行修改标识
};

//------------------------------//
//   River flows in summer
//------------------------------//
