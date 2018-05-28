
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

    m_vec_str_Month.clear();
    m_vec_str_Title.clear();
    m_vec_str_SubMonth.clear();
    m_vec_str_Tail.clear();
    m_vec_str_DPS.clear();

    VersionRipper();
    MonthRipper();
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
