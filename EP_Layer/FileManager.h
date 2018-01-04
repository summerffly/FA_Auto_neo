
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

    void SyncVecLine();
    void SyncFile();
    int GetLineNum();

    /****************************************/
    //   .md文件直接操作区
    /****************************************/
    int FileWriter();
    int FileWriter(const char *cha_FullFileName);
    int BackUpFile(const string str_BackUpPath);

    /****************************************/
    //   行直接操作区
    /****************************************/
    unsigned int GetLineType(const int int_LineIndex);
    int GetLineValue(const int int_LineIndex);
    unsigned int GetLineValueABS(const int int_LineIndex);
    string GetLineContent(const int int_LineIndex);
    string GetFullLine(const int int_LineIndex);

    /****************************************/
    //   搜索操作区
    /****************************************/
    int SearchLineKey(const char *cha_Key);
    int SearchRangeLineKey(const char *cha_Key, const unsigned int uni_RangeBeginIndex,\
                           const unsigned int uni_RangeEndIndex);
    unsigned int GetSearchLineIndex(const unsigned int uni_VecIndex);
    string GetSearchFullLine(const unsigned int uni_VecIndex);

    /****************************************/
    //   同步修改操作区
    /****************************************/
    void InsertLine(const unsigned int uni_VecIndex, const unsigned int uni_LineType,\
                    const int int_LineValue, const string str_LineContent);
    void InsertBlankLine(const unsigned int uni_VecIndex);
    void ModifyLineValue(const unsigned int uni_VecIndex, const int int_LineValue);
    void ModifyLineContent(const unsigned int uni_VecIndex, const char *cha_LineContent);
    void DeleteLine(const unsigned int uni_VecIndex);

    /****************************************/
    //   计算操作区
    /****************************************/
    int CountRange(const unsigned int uni_RangeBeginIndex, const unsigned int uni_RangeEndIndex);
    int CountRangeType(const unsigned int uni_RangeBeginIndex, const unsigned int uni_RangeEndIndex,\
                       unsigned int uni_LineType);

private:
    string m_str_FilePath;                      // .md文件路径
    string m_str_FileName;                      // .md文件名称
    CFileOPer m_cls_FileOPer;                   // .md文件
    int m_int_LineNum;                          // 行数
    vector<CLineEPer> m_vec_cls_Line;           // 行
    vector<unsigned int> m_vec_uni_LineIndex;   // 匹配行
};

//------------------------------//
//   River flows in summer
//------------------------------//
