
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "X_XMLParser.h"


CXMLParser::CXMLParser()
{
    m_str_FilePath = "";
}


CXMLParser::CXMLParser(const char *cha_xmlPath)
{
    m_str_FilePath = cha_xmlPath;
    m_xml_dom.LoadFile(cha_xmlPath);
}


CXMLParser::~CXMLParser()
{
    // Do Nothing
}


void CXMLParser::PrintXML()
{
    m_xml_dom.Print();
}


int CXMLParser::InsertElement()
{
    XMLElement *xml_root = m_xml_dom.RootElement();

    XMLElement *xml_element = m_xml_dom.NewElement("Test");
    xml_element->SetAttribute("Name", "summer");
    xml_root->InsertEndChild(xml_element);

    XMLElement *xml_subelement_A = m_xml_dom.NewElement("Phone");
    xml_subelement_A->InsertEndChild(m_xml_dom.NewText("iPhone"));
    xml_element->InsertEndChild(xml_subelement_A);

    XMLElement *xml_subelement_B = m_xml_dom.NewElement("Phone");
    xml_subelement_B->InsertEndChild(m_xml_dom.NewText("smartisan"));
    xml_element->InsertEndChild(xml_subelement_B);

    return m_xml_dom.SaveFile(m_str_FilePath.c_str());
}


void CXMLParser::QueryElement()
{
    XMLElement *xml_root = m_xml_dom.RootElement();

    XMLElement *xml_element = xml_root->FirstChildElement("Test");
    while(xml_element != NULL)
    {
        string name("summer");
        if(xml_element->Attribute("Name") == name)   // name.c_str()就会无效，为什么？
        {
            XMLElement *xml_subelement = xml_element->FirstChildElement("Phone");
            cout << "SubElement: " << xml_subelement->GetText() << endl;
            break;
        }
        
        xml_element = xml_element -> NextSiblingElement();   //下一个兄弟节点
    }
}


int CXMLParser::ModifyElement()
{
    XMLElement *xml_root = m_xml_dom.RootElement();

    XMLElement *xml_element = xml_root->FirstChildElement("Test");
    while(xml_element != NULL)
    {
        string name("summmer");
        if(xml_element->Attribute("Name") == name)   // name.c_str()就会无效，为什么？
        {
            xml_element->SetAttribute("Name", "summer");
            XMLElement *xml_subelement = xml_element->FirstChildElement("Phone");
            xml_subelement->SetText("iPhone 8 Plus");
            break;
        }
        
        xml_element = xml_element -> NextSiblingElement();   //下一个兄弟节点
    }

    return m_xml_dom.SaveFile(m_str_FilePath.c_str());
}


int CXMLParser::CreateXML(const char *cha_xmlPath, const char *cha_xmlRoot)
{
    const char *declaration ="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

    XMLDocument xml_dom;

    //XML_dom.Parse(declaration);   //会覆盖xml所有内容

    //添加申明可以使用如下两行
    XMLDeclaration *XML_declaration = xml_dom.NewDeclaration();
    xml_dom.InsertFirstChild(XML_declaration);

    XMLElement *root = xml_dom.NewElement(cha_xmlRoot);
    xml_dom.InsertEndChild(root);

    return xml_dom.SaveFile(cha_xmlPath);
}

//------------------------------//
//   River flows in summer
//------------------------------//
