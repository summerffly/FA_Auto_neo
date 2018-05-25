
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "XML_Ripper.h"


/**************************************************/
//   CXMLRipper 构造函数
/**************************************************/
CXMLRipper::CXMLRipper(const char *cha_xmlPath)
{
    m_str_FilePath = cha_xmlPath;
    pugi::xml_parse_result pxml_result = m_pxml_dom.load_file(cha_xmlPath);
    if( pxml_result.status != pugi::status_ok )
    {
        // cout << pxml_result.status << endl;   // tips 番茄@20180525 - Error:14 标识XML格式问题
        CTool::MassageOutFotmat("Read XML Error", '!');
    }
    else
    {
        m_pxml_root = m_pxml_dom.child("FA_Auto_Script");
        cout << m_pxml_root.value() << endl;
    }
}


/**************************************************/
//   CXMLRipper 析构函数
/**************************************************/
CXMLRipper::~CXMLRipper()
{
    // Do Nothing
}


/**************************************************/
//   查询L1层节点属性
/**************************************************/
string CXMLRipper::QueryL1NodeAttr(const string str_L1Node, const string str_L1NodeAttr)
{
    string str_RetL1NodeAttr = string("");

    pugi::xml_node pxml_node = m_pxml_root.child(str_L1Node.c_str());
    if( !pxml_node )
    {
        CTool::MassageOutFotmat("None Node Found", '!');
        return str_RetL1NodeAttr;
    }

    str_RetL1NodeAttr = pxml_node.attribute(str_L1NodeAttr.c_str()).value();
    
    return str_RetL1NodeAttr;
}



//------------------------------//
//   River flows in summer
//------------------------------//
