
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>

#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "../X_Frame/X_Tool.h"

using namespace std;


class CXMLRipper
{
public:
    CXMLRipper(const char *cha_xmlPath);
    ~CXMLRipper();

    bool XMLSaver();

    /****************************************/
    //   读取 XML
    /****************************************/
    string GetRootNodeAttr(const string str_RootNodeAttr);
    string GetL1NodeAttr_UNI(const string str_L1Node, const string str_L1NodeAttr);
    string GetL2NodeAttr_UNI(const string str_L1Node, const string str_L2Node, const string str_L2NodeAttr);
    string GetL2NodeAttr_IDX(const string str_L1Node, const string str_L2Node,\
                             const unsigned int uni_L2NodeIndex, const string str_L2NodeAttr);
    
    /****************************************/
    //   修改 XML
    /****************************************/
    bool SetL1NodeAttr_UNI(const string str_L1Node, const string str_L1NodeAttr, const string str_L1NodeValue);

private:
    string  m_str_FilePath;           // XML文件路径名称
    pugi::xml_document  m_pxml_dom;   // XML文件DOM
    pugi::xml_node  m_pxml_root;      // XML文件根节点
};

//------------------------------//
//   River flows in summer
//------------------------------//
