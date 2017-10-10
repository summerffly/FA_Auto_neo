
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
    CLineEPer(const char *cha_FileName, const char *cha_LineBuffer);
    ~CLineEPer();

    int LineParser(const char *cha_LineBuffer);

private:
    string m_str_ParentFileName;   // 所属.md文件名称
    bool m_bol_LineModFlag;   // 行修改标识
    int m_int_LineIndex;   // 行号
    unsigned int m_uni_LineType;   // 行类型
    bool m_uni_LineValuePM;   // 行金额正负
    unsigned int m_uni_LineValue;   // 行金额
    string m_str_LineContent;   // 行内容
    string m_str_FullLine;   // 整行内容
};

//------------------------------//
//   River flows in summer
//------------------------------//
