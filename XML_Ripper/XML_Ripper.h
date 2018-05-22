
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>

#include "pugiconfig.hpp"
#include "pugixml.hpp"

using namespace std;


class CXMLRipper
{
public:
    CXMLRipper(const char *cha_xmlPath);
    ~CXMLRipper();

private:
    string  m_str_FilePath;          // XML文件路径名称
    pugi::xml_document  m_xml_dom;   // XML解析文件
};

//------------------------------//
//   River flows in summer
//------------------------------//
