
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
    CLineEPer(const char *cha_FileName, const int int_LineIndex, const char *cha_LineBuffer);
    CLineEPer(const char *cha_FileName, const int int_LineIndex, const unsigned int uni_LineType,\
              const int int_LineValue, const string str_LineContent);
    ~CLineEPer();

    int LineParser();
    void ValuePMParser(string str_ValuePM);

    string GetParentFileName();
    unsigned int GetLineIndex();
    unsigned int GetLineType();
    string GetLineContent();
    string GetFullLine();
    bool GetLineValuePM();
    unsigned int GeLineValueABS();
    int GeLineValue();
    bool GetLineModFlag();

    void SetLineValuePM(const bool bol_LineValuePM);
    void SetLineValueABS(const unsigned int uni_LineValueABS);
    void SetLineValue(const int int_LineValue);

    void SetLineModFlag(const bool bol_LineModFlag);

    void UpdateValue(bool bol_UpdateDirection);
    void UpdateFullLine();

    bool IsContainKey(const char *cha_Key);

private:
    string m_str_ParentFileName;        // 所属.md文件名称
    unsigned int m_uni_LineIndex;       // 行号
    unsigned int m_uni_LineType;        // 行类型
    string m_str_LineContent;           // 行内容
    string m_str_FullLine;              // 整行内容
    bool m_bol_LineValuePM;             // 行金额_正负
    unsigned int m_uni_LineValueABS;    // 行金额_绝对值
    int m_int_LineValue;                // 行金额
    bool m_bol_LineModFlag;             // 行修改标识
};

//------------------------------//
//   river flows in summer
//------------------------------//
