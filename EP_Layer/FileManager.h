
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include "./../OP_Layer/FileOPer.h"
#include "./LineEPer.h"

using namespace std;


class CFileManager
{
public:
    CFileManager();
    CFileManager(const char *cha_FileName);
    ~CFileManager();

    void VecLineInit();

    int GetLineNum();
    string GetFullLine(const int int_LineIndex);

private:
    string m_str_FileName;              // .md文件名称
    CFileOPer m_cls_FileOPer;           // .md文件
    int m_int_LineNum;                  // 行数
    vector<CLineEPer> m_vec_cls_Line;   // 行
};

//------------------------------//
//   river flows in summer
//------------------------------//
