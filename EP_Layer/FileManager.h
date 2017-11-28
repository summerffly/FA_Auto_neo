
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

    /****************************************/
    //   .md文件直接操作区
    /****************************************/
    int FileWriter();
    int FileWriter(const char *cha_FullFileName);

    /****************************************/
    //   行直接操作区
    /****************************************/
    string GetFullLine(const int int_LineIndex);

    void SetLineValue(const int int_LineIndex, const int int_LineValue);

    /****************************************/
    //   综合操作区
    /****************************************/
    int SearchLineKey(const char *cha_Key);
    string GetSearchLine(const int int_VecIndex);

private:
    string m_str_FileName;                      // .md文件名称
    CFileOPer m_cls_FileOPer;                   // .md文件
    int m_int_LineNum;                          // 行数
    vector<CLineEPer> m_vec_cls_Line;           // 行
    vector<unsigned int> m_vec_uni_LineIndex;   // 匹配行
};

//------------------------------//
//   river flows in summer
//------------------------------//
