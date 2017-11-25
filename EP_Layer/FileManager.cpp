
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "FileManager.h"

using namespace std;


CFileManager::CFileManager()
{
    // Do Nothing
}

CFileManager::CFileManager(const char *cha_FileName)
{
    m_str_FileName = cha_FileName;
    m_cls_FileOPer = CFileOPer(cha_FileName);
    m_int_LineNum = m_cls_FileOPer.GetLineNum();
    VecLineInit();
}

CFileManager::~CFileManager()
{
    // Do Nothing
}

void CFileManager::VecLineInit()
{
    m_vec_cls_Line.clear();
    CLineEPer cls_LineEPer_zero = CLineEPer();
    m_vec_cls_Line.push_back(cls_LineEPer_zero);

    for(int i=1; i<=m_int_LineNum; i++)
    {
        CLineEPer cls_LineEPer_temp = CLineEPer(m_str_FileName.c_str(), i, m_cls_FileOPer.GetLine(i).c_str());
        m_vec_cls_Line.push_back(cls_LineEPer_temp);
    }
}

int CFileManager::GetLineNum()
{
    return m_int_LineNum;
}

int CFileManager::FileWriter(const char *cha_FileName)
{
    return m_cls_FileOPer.FileWriter(cha_FileName);
}

string CFileManager::GetFullLine(const int int_LineIndex)
{
    return m_vec_cls_Line.at(int_LineIndex).GetFullLine();
}

void CFileManager::SetLineValue(const int int_LineIndex, const int int_LineValue)
{
    m_vec_cls_Line.at(int_LineIndex).SetLineValue(int_LineValue);
    m_cls_FileOPer.ModifyLine(int_LineIndex, m_vec_cls_Line.at(int_LineIndex).GetFullLine());
}


//------------------------------//
//   river flows in summer
//------------------------------//
