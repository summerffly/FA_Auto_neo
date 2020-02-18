
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
    // tips 番茄@20200218
    // 全局变量初始化，程序最早入口点
    CTool::SetExecutablePath();

    m_str_FilePath = cha_xmlPath;
    pugi::xml_parse_result pxml_result = m_pxml_dom.load_file(cha_xmlPath);
    if( pxml_result.status != pugi::status_ok )
    {
        // tips 番茄@20180525 - Error:14 标识XML格式问题
        // cout << pxml_result.status << endl;
        CTool::MassageOutFotmat("Read XML Error", '!');
    }
    else
    {
        m_pxml_root = m_pxml_dom.child("FA_Auto_Script");
    }
}


/**************************************************/
//   CXMLRipper 析构函数
/**************************************************/
CXMLRipper::~CXMLRipper()
{
    // Nothing To Do
}


/**************************************************/
//   保存XML
/**************************************************/
bool CXMLRipper::XMLSaver()
{
    return m_pxml_dom.save_file(m_str_FilePath.c_str());
}


/**************************************************/
//   查询Root节点属性
/**************************************************/
string CXMLRipper::GetRootNodeAttr(const string str_RootNodeAttr)
{
    string str_RetRootNodeAttr = string("");

    str_RetRootNodeAttr = m_pxml_root.attribute(str_RootNodeAttr.c_str()).value();
    
    return str_RetRootNodeAttr;
}

/**************************************************/
//   查询L1层节点属性
/**************************************************/
string CXMLRipper::GetL1NodeAttr_UNI(const string str_L1Node, const string str_L1NodeAttr)
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


/**************************************************/
//   查询L2层节点属性
//   唯一型节点
/**************************************************/
string CXMLRipper::GetL2NodeAttr_UNI(const string str_L1Node, const string str_L2Node, const string str_L2NodeAttr)
{
    string str_RetL2NodeAttr = string("");

    pugi::xml_node pxml_node_L1 = m_pxml_root.child(str_L1Node.c_str());
    if( !pxml_node_L1 )
    {
        CTool::MassageOutFotmat("None Node Found", '!');
        return str_RetL2NodeAttr;
    }

    pugi::xml_node pxml_node_L2 = pxml_node_L1.child(str_L2Node.c_str());
    if( !pxml_node_L2 )
    {
        CTool::MassageOutFotmat("None Node Found", '!');
        return str_RetL2NodeAttr;
    }

    str_RetL2NodeAttr = pxml_node_L2.attribute(str_L2NodeAttr.c_str()).value();
    
    return str_RetL2NodeAttr;
}


/**************************************************/
//   查询L2层节点属性
//   Index标识并列型节点
/**************************************************/
string CXMLRipper::GetL2NodeAttr_IDX(const string str_L1Node, const string str_L2Node,\
                                       const unsigned int uni_L2NodeIndex, const string str_L2NodeAttr)
{
    unsigned int uni_L2NodeCounter = 1;
    string str_RetL2NodeAttr = string("");

    pugi::xml_node pxml_node_L1 = m_pxml_root.child(str_L1Node.c_str());
    if( !pxml_node_L1 )
    {
        CTool::MassageOutFotmat("None Node Found", '!');
        return str_RetL2NodeAttr;
    }

    pugi::xml_node pxml_node_L2 = pxml_node_L1.child(str_L2Node.c_str());
    if( !pxml_node_L2 )
    {
        CTool::MassageOutFotmat("None Node Found", '!');
        return str_RetL2NodeAttr;
    }
    else
    {
        if( uni_L2NodeIndex == 0 )
        {
            CTool::MassageOutFotmat("Node Index Error", '!');
            return str_RetL2NodeAttr;
        }
        else if( uni_L2NodeIndex == 1 )
        {
            str_RetL2NodeAttr = pxml_node_L2.attribute(str_L2NodeAttr.c_str()).value();
            return str_RetL2NodeAttr;
        }
        else
        {
            while( uni_L2NodeCounter < uni_L2NodeIndex )
            {
                pxml_node_L2 = pxml_node_L2.next_sibling(str_L2Node.c_str());
                uni_L2NodeCounter++;
            }

            if( !pxml_node_L2 )
            {
                CTool::MassageOutFotmat("Node Index Error", '!');
                return str_RetL2NodeAttr;
            }
            else
            {
                str_RetL2NodeAttr = pxml_node_L2.attribute(str_L2NodeAttr.c_str()).value();
                return str_RetL2NodeAttr;
            }
        }
    }
}


/**************************************************/
//   修改L1层节点属性
//   唯一型节点
/**************************************************/
bool CXMLRipper::SetL1NodeAttr_UNI(const string str_L1Node, const string str_L1NodeAttr, const string str_L1NodeValue)
{
    pugi::xml_node pxml_node = m_pxml_root.child(str_L1Node.c_str());
    if( !pxml_node )
    {
        CTool::MassageOutFotmat("None Node Found", '!');
        return -1;
    }
    else
    {
        pugi::xml_attribute pxml_attr = pxml_node.attribute(str_L1NodeAttr.c_str());
        return pxml_attr.set_value(str_L1NodeValue.c_str());
    }
}


//------------------------------//
//   River flows in summer
//------------------------------//
