
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class CFileOper
{
public:
    CFileOper();
    CFileOper(const char *cha_FileName);
    ~CFileOper();

    int GetLineNum();
    bool GetModFlag();

    string GetLine(const int int_LineIndex);
    int InsertLine(const int int_LineIndex, const string str_LineContent);
    int ModifyLine(const int int_LineIndex, const string str_LineContent);
    int DeleteLine(const int int_LineIndex);

    int FileWriter(const char *cha_FileName);

private:
    string m_str_FilePath;   // .md文件路径
    string m_str_FileName;   // .md文件名称
    bool m_bol_ModFlag;   // 文件修改标识
    int m_int_LineNum;   // 行数
    vector<string> m_vec_Line;   // 行内容
};

//------------------------------//
//   River flows in summer
//------------------------------//
