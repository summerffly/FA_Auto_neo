
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "XML_Ripper.h"


CXMLRipper::CXMLRipper()
{
    m_str_FilePath = "";
}


CXMLRipper::CXMLRipper(const char *cha_xmlPath)
{
    m_str_FilePath = cha_xmlPath;
    m_xml_dom.load_file(cha_xmlPath);
}


CXMLRipper::~CXMLRipper()
{
    // Do Nothing
}




//------------------------------//
//   River flows in summer
//------------------------------//
