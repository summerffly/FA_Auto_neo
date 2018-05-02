
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "X_CFGLoader.h"
#include "X_XMLParser.h"

using namespace std;


string CCFGLoader::m_str_CFGPathName = "";
string CCFGLoader::m_str_Version = "";
string CCFGLoader::m_str_OriginMonth = "00";
string CCFGLoader::m_str_CurrentMonth = "00";
unsigned int CCFGLoader::m_uni_OriginMonth = 0;
unsigned int CCFGLoader::m_uni_CurrentMonth = 0;
vector<FA_ITEM> CCFGLoader::m_vec_stc_FAItem;

CCFGLoader::CCFGLoader()
{
    // Do Nothing
}

CCFGLoader::~CCFGLoader()
{
    // Do Nothing
}

void CCFGLoader::LoadCFG(const char *cha_FileName)
{
    m_str_CFGPathName = cha_FileName;
}

void CCFGLoader::LoadVersion()
{
    CXMLParser xml_CFG(m_str_CFGPathName.c_str());

    m_str_Version = xml_CFG.QueryElementL1Attribute("Version", "Atr", "version");
}

void CCFGLoader::LoadMonth()
{
    CXMLParser xml_CFG(m_str_CFGPathName.c_str());

    m_str_OriginMonth = xml_CFG.QueryElementL1Attribute("Month", "Atr", "origin");
    m_str_CurrentMonth = xml_CFG.QueryElementL1Attribute("Month", "Atr", "current");

    m_uni_OriginMonth = atoi(m_str_OriginMonth.c_str());
    m_uni_CurrentMonth = atoi(m_str_CurrentMonth.c_str());
}

void CCFGLoader::LoadFA()
{
    CXMLParser xml_CFG(m_str_CFGPathName.c_str());

    int ItemCounter = 1;

    while( xml_CFG.QueryElementL2Index("FA_Struct", "FAItem", ItemCounter).compare("") != 0 )
    {
        FA_ITEM stc_FA;
        stc_FA.str_ItemContent = xml_CFG.QueryElementL2Index("FA_Struct", "FAItem", ItemCounter);
        stc_FA.str_ItemAttrbute = xml_CFG.QueryAttrbuteL2Index("FA_Struct", "FAItem", "Atr", ItemCounter);
        m_vec_stc_FAItem.push_back(stc_FA);
        ItemCounter++;
    }
}

bool CCFGLoader::CompareMonthRange(const string str_SelMonth)
{
    unsigned int uni_SelMonth = atoi(str_SelMonth.c_str());

    if( m_uni_OriginMonth <= m_uni_CurrentMonth )
    {
        if( m_uni_CurrentMonth < uni_SelMonth )
        {
            return false;
        }
        else if( uni_SelMonth < m_uni_OriginMonth )
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        // tips 番茄@20180328 - 需要考虑月份的另一种情况
        return true;
    }

}

//------------------------------//
//   River flows in summer
//------------------------------//
