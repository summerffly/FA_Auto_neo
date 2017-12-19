
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


class CFileOPer
{
public:
    CFileOPer();
    CFileOPer(const char *cha_FullFileName);
    ~CFileOPer();

    void FullFileNameParser(const char *cha_FullFileName);

    string GetLine(const int int_LineIndex);
    int InsertLine(const int int_LineIndex, const string str_LineContent);
    int ModifyLine(const int int_LineIndex, const string str_LineContent);
    int DeleteLine(const int int_LineIndex);

    string GetFilePath();
    string GetFileName();
    int GetLineNum();
    bool GetModFlag();

    int FileReader();
    int FileReader(const char *cha_FullFileName);
    int FileWriter();
    int FileWriter(const char *cha_FullFileName);

private:
    string m_str_FilePath;       // .md文件路径
    string m_str_FileName;       // .md文件名称
    int m_int_LineNum;           // 行数
    vector<string> m_vec_Line;   // 行内容
    bool m_bol_ModFlag;          // .md文件修改标识
};

//------------------------------//
//   River flows in summer
//------------------------------//
