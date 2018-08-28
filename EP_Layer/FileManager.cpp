
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "FileManager.h"

#include "./../X_Frame/DefLib.h"

using namespace std;


CFileManager::CFileManager()
{
    // Do Nothing
}

CFileManager::CFileManager(const char *cha_FullFileName)
{
    m_cls_FileOPer = CFileOPer(cha_FullFileName);
    m_int_LineNum = m_cls_FileOPer.GetLineNum();
    m_str_FilePath = m_cls_FileOPer.GetFilePath();
    m_str_FileName = m_cls_FileOPer.GetFileName();

    SyncVecLine();
}

CFileManager::~CFileManager()
{
    // Do Nothing
}

void CFileManager::SyncVecLine()
{
    m_vec_cls_Line.clear();
    // tips 番茄@20171129 - 指针才需要new空间
    //CLineEPer cls_LineEPer_zero = new CLineEPer();
    CLineEPer cls_LineEPer_zero = CLineEPer();
    m_vec_cls_Line.push_back(cls_LineEPer_zero);

    for(int i=1; i<=m_int_LineNum; i++)
    {
        CLineEPer cls_LineEPer_temp = CLineEPer(m_cls_FileOPer.GetLine(i).c_str());
        m_vec_cls_Line.push_back(cls_LineEPer_temp);
    }
}

void CFileManager::SyncFile()
{
    m_cls_FileOPer.FileReader();
    // tips 番茄@20180102 - m_int_LineNum同样需要同步
    m_int_LineNum = m_cls_FileOPer.GetLineNum();
    SyncVecLine();
}

int CFileManager::GetLineNum()
{
    return m_int_LineNum;
}

int CFileManager::FileComparer()
{
    return m_cls_FileOPer.FileComparer();
}

int CFileManager::FileComparer(const char *cha_FullFileName)
{
    return m_cls_FileOPer.FileComparer(cha_FullFileName);
}

int CFileManager::FileWriter()
{
    return m_cls_FileOPer.FileWriter();
}

int CFileManager::FileWriter(const char *cha_FullFileName)
{
    return m_cls_FileOPer.FileWriter(cha_FullFileName);
}

int CFileManager::BackUpFile(const string str_BackUpPath)
{
    string str_FullFileName = str_BackUpPath;
    str_FullFileName += m_str_FileName;
    return m_cls_FileOPer.FileWriter(str_FullFileName.c_str());
}

string CFileManager::GetFileName()
{
    return m_str_FileName;
}

unsigned int CFileManager::GetLineType(const int int_LineIndex)
{
    return m_vec_cls_Line.at(int_LineIndex).GetLineType();
}

int CFileManager::GetLineValue(const int int_LineIndex)
{
    return m_vec_cls_Line.at(int_LineIndex).GetLineValue();
}

unsigned int CFileManager::GetLineValueABS(const int int_LineIndex)
{
    return m_vec_cls_Line.at(int_LineIndex).GeLineValueABS();
}

string CFileManager::GetLineContent(const int int_LineIndex)
{
    return m_vec_cls_Line.at(int_LineIndex).GetLineContent();
}

string CFileManager::GetFullLine(const int int_LineIndex)
{
    return m_vec_cls_Line.at(int_LineIndex).GetFullLine();
}

int CFileManager::SearchLineKey(const char *cha_Key)
{
    m_vec_uni_LineIndex.clear();

    for(int i=1; i <= m_int_LineNum; i++)
    {
        if( m_vec_cls_Line.at(i).IsContainKey(cha_Key) )
        {
            m_vec_uni_LineIndex.push_back(i);
        }
    }

    return m_vec_uni_LineIndex.size();
}

int CFileManager::SearchFirstLineKey(const char *cha_Key)
{
    unsigned int uni_VecIndex = 0;

    for(int i=1; i <= m_int_LineNum; i++)
    {
        if( m_vec_cls_Line.at(i).IsContainKey(cha_Key) )
        {
            uni_VecIndex = i;
            break;
        }
    }

    return uni_VecIndex;
}

int CFileManager::SearchRangeLineKey(const char *cha_Key, const unsigned int uni_RangeBeginIndex,\
                                     const unsigned int uni_RangeEndIndex)
{
    m_vec_uni_LineIndex.clear();

    for(int i=uni_RangeBeginIndex; i <= uni_RangeEndIndex; i++)
    {
        if( m_vec_cls_Line.at(i).IsContainKey(cha_Key) )
        {
            m_vec_uni_LineIndex.push_back(i);
        }
    }

    return m_vec_uni_LineIndex.size();
}

unsigned int CFileManager::GetSearchLineIndex(const unsigned int uni_VecIndex)
{
    if(0 == m_vec_uni_LineIndex.size())
    {
        CTool::MassageOutFotmat("No Search Line Found", '!');
        return 0;
    }
    else if(uni_VecIndex > m_vec_uni_LineIndex.size())
    {
        CTool::MassageOutFotmat("Over Search Size", '!');
        return 0;
    }
    else
    {
        return m_vec_uni_LineIndex.at(uni_VecIndex - 1);
    }
}

string CFileManager::GetSearchFullLine(const unsigned int uni_VecIndex)
{
    if(0 == m_vec_uni_LineIndex.size())
    {
        CTool::MassageOutFotmat("No Search Line Found", '!');
        return "ERROR";
    }
    else if(uni_VecIndex > m_vec_uni_LineIndex.size())
    {
        CTool::MassageOutFotmat("Over Search Size", '!');
        return "ERROR";
    }
    else
    {
        return m_vec_cls_Line.at(m_vec_uni_LineIndex.at(uni_VecIndex - 1)).GetFullLine();
    }
}

unsigned int CFileManager::GetUniqueSearchLineIndex(const char *cha_Key)
{
    m_vec_uni_LineIndex.clear();

    for(int i=1; i <= m_int_LineNum; i++)
    {
        if( m_vec_cls_Line.at(i).IsContainKey(cha_Key) )
        {
            m_vec_uni_LineIndex.push_back(i);
        }
    }

    if(0 == m_vec_uni_LineIndex.size())
    {
        CTool::MassageOutFotmat("No Search Line Found", '!');
        return 0;
    }
    else if(m_vec_uni_LineIndex.size() > 1)
    {
        CTool::MassageOutFotmat("Multi Search Line Found", '!');
        return 0;
    }

    return m_vec_uni_LineIndex.at(0);
}

int CFileManager::GetUniqueSearchLineValue(const char *cha_Key)
{
    m_vec_uni_LineIndex.clear();

    for(int i=1; i <= m_int_LineNum; i++)
    {
        if( m_vec_cls_Line.at(i).IsContainKey(cha_Key) )
        {
            m_vec_uni_LineIndex.push_back(i);
        }
    }

    if(0 == m_vec_uni_LineIndex.size())
    {
        CTool::MassageOutFotmat("No Search Line Found", '!');
        return 0;
    }
    else if(m_vec_uni_LineIndex.size() > 1)
    {
        CTool::MassageOutFotmat("Multi Search Line Found", '!');
        return 0;
    }

    return m_vec_cls_Line.at(m_vec_uni_LineIndex.at(0)).GetLineValue();
}

void CFileManager::InsertLine(const unsigned int uni_VecIndex, const unsigned int uni_LineType,\
                              const int int_LineValue, const string str_LineContent)
{
    CLineEPer cls_LineEPer_temp = CLineEPer(uni_LineType, int_LineValue, str_LineContent);
    vector<CLineEPer>::iterator vec_cls_Iter = m_vec_cls_Line.begin();
    vec_cls_Iter += uni_VecIndex;
    m_vec_cls_Line.insert(vec_cls_Iter, cls_LineEPer_temp);
    m_int_LineNum++;

    m_cls_FileOPer.InsertLine(uni_VecIndex, cls_LineEPer_temp.GetFullLine());
}

void CFileManager::InsertBlankLine(const unsigned int uni_VecIndex)
{
    CLineEPer cls_LineEPer_temp = CLineEPer(LTYPE_BLANK, 0, "");
    vector<CLineEPer>::iterator vec_cls_Iter = m_vec_cls_Line.begin();
    vec_cls_Iter += uni_VecIndex;
    m_vec_cls_Line.insert(vec_cls_Iter, cls_LineEPer_temp);
    m_int_LineNum++;

    m_cls_FileOPer.InsertLine(uni_VecIndex, cls_LineEPer_temp.GetFullLine());
}

void CFileManager::ModifyLineValue(const unsigned int uni_VecIndex, const int int_LineValue)
{
    m_vec_cls_Line.at(uni_VecIndex).SetLineValue(int_LineValue);

    m_cls_FileOPer.ModifyLine(uni_VecIndex, m_vec_cls_Line.at(uni_VecIndex).GetFullLine());
}

void CFileManager::ModifyLineContent(const unsigned int uni_VecIndex, const char *cha_LineContent)
{
    m_vec_cls_Line.at(uni_VecIndex).SetLineContent(cha_LineContent);

    m_cls_FileOPer.ModifyLine(uni_VecIndex, m_vec_cls_Line.at(uni_VecIndex).GetFullLine());
}

void CFileManager::DeleteLine(const unsigned int uni_VecIndex)
{
    vector<CLineEPer>::iterator vec_cls_Iter = m_vec_cls_Line.begin();
    vec_cls_Iter += uni_VecIndex;
    m_vec_cls_Line.erase(vec_cls_Iter);
    m_int_LineNum--;

    m_cls_FileOPer.DeleteLine(uni_VecIndex);
}

int CFileManager::CountRange(const unsigned int uni_RangeBeginIndex, const unsigned int uni_RangeEndIndex)
{
    int int_Counter = 0;

    for(int i = uni_RangeBeginIndex; i <= uni_RangeEndIndex; i++)
    {
        int_Counter += m_vec_cls_Line.at(i).GetLineValue();
    }

    return int_Counter;
}

int CFileManager::CountRangeType(const unsigned int uni_RangeBeginIndex, const unsigned int uni_RangeEndIndex,\
                                 unsigned int uni_LineType)
{
    int int_Counter = 0;

    for(int i = uni_RangeBeginIndex; i <= uni_RangeEndIndex; i++)
    {
        if( m_vec_cls_Line.at(i).GetLineType() == uni_LineType )
        {
            int_Counter += m_vec_cls_Line.at(i).GetLineValue();
        }
    }

    return int_Counter;
}

void CFileManager::UpdateTimeStamp()
{
    for(int i = 0 ;i < m_int_LineNum ;i++)
    {
        if( m_vec_cls_Line.at(m_int_LineNum - i).GetLineType() != LTYPE_TIMESTAMP )
        {
            continue;
        }

        char *cha_TimeStamp = new char[40];

        //sprintf(cha_TimeStamp, "*Update Time : %s*", CTool::TimeOut().c_str());
        sprintf(cha_TimeStamp, "%s", CTool::TimeOut().c_str());
        m_vec_cls_Line.at(m_int_LineNum-i).SetLineContent(cha_TimeStamp);
        m_cls_FileOPer.ModifyLine((m_int_LineNum-i), m_vec_cls_Line.at(m_int_LineNum-i).GetFullLine());

        delete []cha_TimeStamp;

        break;
    }
}

string CFileManager::GetTimeStamp()
{
    for(int i=1; i <= m_int_LineNum; i++)
    {
        if( LTYPE_TIMESTAMP == m_vec_cls_Line.at(i).GetLineType() )
        {
            return m_vec_cls_Line.at(i).GetLineContent();
        }
    }

    string str_Ret = "TIME ERROR";
    return str_Ret;
}

//------------------------------//
//   River flows in summer
//------------------------------//
