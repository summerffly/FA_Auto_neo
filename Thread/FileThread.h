
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

#include "Thread.h"

#define MAX_LINE_CHAR   128     // 每行最大字符数

using namespace std;

class CFileThread: public CThread
{
public:
    CFileThread();
    CFileThread(const char *cha_FileName);
    ~CFileThread();

    int GetLineNum();
    bool GetModFlag();

    string GetLine(const int int_LineIndex);
    int InsertLine(const int int_LineIndex, const string str_LineContent);
    int ModifyLine(const int int_LineIndex, const string str_LineContent);
    int DeleteLine(const int int_LineIndex);

    int FileWriter(const char *cha_FileName);

    void Run();

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
