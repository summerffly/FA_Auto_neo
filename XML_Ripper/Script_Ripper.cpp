
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "Script_Ripper.h"

using namespace std;


/**************************************************/
//   CScriptRipper 构造函数
/**************************************************/
CScriptRipper::CScriptRipper(const char *cha_xmlPath):
m_cls_XMLRipper(cha_xmlPath)
{
    m_str_ScriptFilePath = cha_xmlPath;

    m_str_Version = "";
    m_str_OriginMonth = "";
    m_str_CurrentMonth = "";
    m_uni_OriginMonth = 0;
    m_uni_CurrentMonth = 0;

    m_vec_str_Title.clear();
    m_vec_str_SubMonth.clear();
    m_vec_str_Tail.clear();
    m_vec_str_DPS.clear();

    m_vec_str_Month.clear();

    VersionRipper();
    MonthRipper();
    MonthRangeGenerator();
    TitleRipper();
    TailRipper();
}

/**************************************************/
//   CScriptRipper 析构函数
/**************************************************/
CScriptRipper::~CScriptRipper()
{
    // Nothing To Do
}

/**************************************************/
//   读取&解析 Version
/**************************************************/
void CScriptRipper::VersionRipper()
{
    m_str_Version = m_cls_XMLRipper.GetRootNodeAttr("version");
}

/**************************************************/
//   读取&解析 Month
/**************************************************/
void CScriptRipper::MonthRipper()
{
    m_str_OriginMonth = m_cls_XMLRipper.GetL1NodeAttr_UNI("OriginMonth", "month");
    m_str_CurrentMonth = m_cls_XMLRipper.GetL1NodeAttr_UNI("CurrentMonth", "month");

    m_uni_OriginMonth = atoi(m_str_OriginMonth.c_str());
    m_uni_CurrentMonth = atoi(m_str_CurrentMonth.c_str());
}

/**************************************************/
//   读取&解析 Title
/**************************************************/
void CScriptRipper::TitleRipper()
{
    string str_TitleNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_Title", "num");
    m_uni_TitleNum = atoi(str_TitleNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_TitleNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_Title", "TitleItem", i,"item");
        m_vec_str_Title.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 TitleDeep
/**************************************************/
void CScriptRipper::TitleDeepRipper()
{
    string str_TitleDeepNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_TitleDeep", "num");
    m_uni_TitleDeepNum = atoi(str_TitleDeepNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_TitleDeepNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_TitleDeep", "TitleItem", i,"item");
        m_vec_str_TitleDeep.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 SubMonth
/**************************************************/
void CScriptRipper::SubMonthRipper()
{
    string str_SubMonthNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_SubMonth", "num");
    m_uni_SubMonthNum = atoi(str_SubMonthNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_SubMonthNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_SubMonth", "SMItem", i,"item");
        m_vec_str_SubMonth.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 Tail
/**************************************************/
void CScriptRipper::TailRipper()
{
    string str_TailNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_Tail", "num");
    m_uni_TailNum = atoi(str_TailNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_TailNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_Tail", "TailItem", i,"item");
        m_vec_str_Tail.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 DPS
/**************************************************/
void CScriptRipper::DPSRipper()
{
    string str_DPSNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_DPS", "num");
    m_uni_DPSNum = atoi(str_DPSNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_DPSNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_DPS", "DPSItem", i,"item");
        m_vec_str_DPS.push_back(str_Temp);
    }
}

/**************************************************/
//   生成 Month Range
//   只能用于生成12个月内的情况
//   2017.03 ~ 2017.03 >>> 可行
//   2017.03 ~ 2018.03 >>> 不可行
/**************************************************/
void CScriptRipper::MonthRangeGenerator()
{
    string str_OriginMonth = "M" + m_str_OriginMonth;
    string str_CurrentMonth = "M" + m_str_CurrentMonth;

    m_vec_str_Month.push_back(str_OriginMonth);

    if( m_uni_OriginMonth == m_uni_CurrentMonth )
    {
        return;
    }
    else if( m_uni_OriginMonth < m_uni_CurrentMonth )
    {
        unsigned int uni_MonthCounter = m_uni_CurrentMonth - m_uni_OriginMonth;
        string str_InsertMonth = m_str_OriginMonth;

        while( uni_MonthCounter > 0 )
        {
            str_InsertMonth = CTool::GenerateNextMonth(str_InsertMonth);
            m_vec_str_Month.push_back("M" + str_InsertMonth);
            uni_MonthCounter--;
        }

        return;
    }
    else
    {
        unsigned int uni_MonthCounter = 12 - m_uni_OriginMonth;
        string str_InsertMonth = m_str_OriginMonth;

        while( uni_MonthCounter > 0 )
        {
            str_InsertMonth = CTool::GenerateNextMonth(str_InsertMonth);
            m_vec_str_Month.push_back("M" + str_InsertMonth);
            uni_MonthCounter--;
        }

        uni_MonthCounter = m_uni_CurrentMonth;
        str_InsertMonth = "01";
        m_vec_str_Month.push_back("M" + str_InsertMonth);

        while( uni_MonthCounter > 1 )
        {
            str_InsertMonth = CTool::GenerateNextMonth(str_InsertMonth);
            m_vec_str_Month.push_back("M" + str_InsertMonth);
            uni_MonthCounter--;
        }

        return;
    }
}

/**************************************************/
//   拷贝 Month Range
/**************************************************/
void CScriptRipper::MonthRangeDuplicator(vector<string> &vec_str_DestMonth)
{
    vec_str_DestMonth.clear();

    vector<string>::iterator itr_Month;
    for(itr_Month = m_vec_str_Month.begin(); itr_Month != m_vec_str_Month.end(); itr_Month++)
    {
        vec_str_DestMonth.push_back(*itr_Month);
    }
}

/**************************************************/
//   拷贝 Title
/**************************************************/
void CScriptRipper::TitleDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_Title;
    for(itr_Title = m_vec_str_Title.begin(); itr_Title != m_vec_str_Title.end(); itr_Title++)
    {
        vec_str_Dest.push_back(*itr_Title);
    }
}

/**************************************************/
//   拷贝 Tail
/**************************************************/
void CScriptRipper::TailDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_Tail;
    for(itr_Tail = m_vec_str_Tail.begin(); itr_Tail != m_vec_str_Tail.end(); itr_Tail++)
    {
        vec_str_Dest.push_back(*itr_Tail);
    }
}

/**************************************************/
//   判断是否存在 Month Range
/**************************************************/
bool CScriptRipper::IsIncludeMonthRange(const string str_SelMonth)
{
    string str_JudgeMonth("M" + str_SelMonth);

    vector<string>::iterator itr_Month;
    for(itr_Month = m_vec_str_Month.begin(); itr_Month != m_vec_str_Month.end(); itr_Month++)
    {
        if( *itr_Month == str_JudgeMonth )
        {
            return true;
        }
    }

    return false;
}

/**************************************************/
//   获取 Version
/**************************************************/
string CScriptRipper::GetVersion()
{
    return m_str_Version;
}

/**************************************************/
//   获取 OriginMonth
/**************************************************/
string CScriptRipper::GetOriginMonth()
{
    return m_str_OriginMonth;
}

/**************************************************/
//   获取 CurrentMonth
/**************************************************/
string CScriptRipper::GetCurrentMonth()
{
    return m_str_CurrentMonth;
}


//------------------------------//
//   River flows in summer
//------------------------------//
