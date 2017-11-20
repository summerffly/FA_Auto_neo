
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>

using namespace std;


class CLineEPer
{
public:
    CLineEPer();
    CLineEPer(const char *cha_FileName, const int int_LineIndex, const char *cha_LineBuffer);
    ~CLineEPer();

    int LineParser();
    void ValuePMParser(string str_ValuePM);

    int GetLineType();
    string GetLineContent();
    string GetFullLine();
    bool GetLineValuePM();

private:
    string m_str_ParentFileName;     // 所属.md文件名称
    int m_int_LineIndex;             // 行号
    unsigned int m_uni_LineType;     // 行类型
    bool m_bol_LineValuePM;          // 行金额正负
    unsigned int m_uni_LineValue;    // 行金额
    string m_str_LineContent;        // 行内容
    string m_str_FullLine;           // 整行内容
    bool m_bol_LineModFlag;          // 行修改标识
};

//------------------------------//
//   River flows in summer
//------------------------------//
