
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "FileManager.h"

#define LTYPE_HEADTITLE     1   // 总标题
#define LTYPE_SUBTITLE      2   // 单项标题
#define LTYPE_MONTHTITLE    3   // 月度标题

#define LTYPE_BLANK         7   // 空行
#define LTYPE_DELIMITER     8   // 分隔线
#define LTYPE_EOF           9   // 结束线

#define LTYPE_FBIRC_AGGR        11   // 总金额
#define LTYPE_FBIRC_TITLESUM    12   // 单项金额
#define LTYPE_FBIRC_MONTHSUM    13   // 月度金额
#define LTYPE_FBIRC_LINEUINT    14   // 单行金额

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
    // tips 番茄@20171129 - 指针才需要new空间
    //CLineEPer cls_LineEPer_zero = new CLineEPer();
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

int CFileManager::FileWriter()
{
    return m_cls_FileOPer.FileWriter();
}

int CFileManager::FileWriter(const char *cha_FullFileName)
{
    return m_cls_FileOPer.FileWriter(cha_FullFileName);
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

string CFileManager::GetSearchLine(const int int_VecIndex)
{
    if( int_VecIndex > m_vec_uni_LineIndex.size())
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!      Over Search Vector Size     !!!" << endl;
        cout << "----------------------------------------" << endl;

        return "ERROR";
    }
    else
    {
        return m_vec_cls_Line.at(m_vec_uni_LineIndex.at(int_VecIndex - 1)).GetFullLine();
    }
}

void CFileManager::InsertLine(const int int_LineIndex, const unsigned int uni_LineType,\
                              const int int_LineValue, const string str_LineContent)
{
    CLineEPer cls_LineEPer_temp = CLineEPer(m_str_FileName.c_str(), int_LineIndex, uni_LineType,\
                                            int_LineValue, str_LineContent);
    vector<CLineEPer>::iterator vec_cls_Iter = m_vec_cls_Line.begin();
    m_vec_cls_Line.insert(vec_cls_Iter, cls_LineEPer_temp);
    m_cls_FileOPer.InsertLine(int_LineIndex, cls_LineEPer_temp.GetFullLine());
}


//------------------------------//
//   river flows in summer
//------------------------------//
