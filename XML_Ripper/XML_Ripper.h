
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>

#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "./../X_Frame/X_Tool.h"

using namespace std;


class CXMLRipper
{
public:
    CXMLRipper(const char *cha_xmlPath);
    ~CXMLRipper();

    string QueryL1NodeAttr_UNI(const string str_L1Node, const string str_L1NodeAttr);
    string QueryL2NodeAttr_UNI(const string str_L1Node, const string str_L2Node, const string str_L2NodeAttr);
    string QueryL2NodeAttr_IDX(const string str_L1Node, const string str_L2Node,\
                               const unsigned int uni_L2NodeIndex, const string str_L2NodeAttr);

private:
    string  m_str_FilePath;           // XML文件路径名称
    pugi::xml_document  m_pxml_dom;   // XML文件DOM
    pugi::xml_node  m_pxml_root;      // XML文件根节点
};

//------------------------------//
//   River flows in summer
//------------------------------//
