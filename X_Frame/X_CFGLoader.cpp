
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "X_CFGLoader.h"
#include "X_XMLParser.h"

using namespace std;


string CCFGLoader::m_str_CFGPathName = "";
string CCFGLoader::m_str_OriginMonth = "00";
string CCFGLoader::m_str_CurrentMonth = "00";
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

void CCFGLoader::LoadMonth()
{
    CXMLParser xml_CFG(m_str_CFGPathName.c_str());

    m_str_OriginMonth = xml_CFG.QueryElementL1Attribute("Month", "Atr", "origin");
    m_str_CurrentMonth = xml_CFG.QueryElementL1Attribute("Month", "Atr", "current");
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

//------------------------------//
//   River flows in summer
//------------------------------//
