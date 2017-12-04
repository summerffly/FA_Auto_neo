
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>

#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


class CXMLParser
{
public:
    CXMLParser();
    CXMLParser(const char *cha_xmlPath);
    ~CXMLParser();

    int InsertElement();
    void QueryElement();
    string QueryElementL1Index(const string str_ChildElementL1, const unsigned int uni_ChildIndex);
    string QueryElementL1Attribute(const string str_ChildElementL1, const string str_ChildAttribute,\
                                   const string str_ChildAttributeContent);
    string QueryElementL2(const string str_ChildElementL1, const string str_ChildElementL2,\
                          const unsigned int uni_ChildIndex);
    int ModifyElement();
    void PrintXML();

private:
    string m_str_FilePath;   // XML文件路径名称
    XMLDocument m_xml_dom;   // XML文件

public:
    static int CreateXML(const char *cha_xmlPath, const char *cha_xmlRoot);

};

//------------------------------//
//   River flows in summer
//------------------------------//
