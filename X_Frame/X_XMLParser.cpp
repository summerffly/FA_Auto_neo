
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

            xml_subelement = xml_subelement->NextSiblingElement();
            cout << "SubElement: " << xml_subelement->GetText() << endl;
            break;
        }
        
        xml_element = xml_element -> NextSiblingElement();   //下一个兄弟节点
    }
}

string CXMLParser::QueryElementL1Index(const string str_ChildElementL1, const unsigned int uni_ChildIndex)
{
    XMLElement *xml_root = m_xml_dom.RootElement();
    string str_RetChildElement = string("");
    unsigned int uni_ClildCounter = 1;

    XMLElement *xml_elementL1 = xml_root->FirstChildElement(str_ChildElementL1.c_str());

    if(uni_ChildIndex == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!         Error Child Index        !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_RetChildElement;
    }

    if( uni_ChildIndex == 1 )
    {
        if( xml_elementL1 != NULL )
        {
            str_RetChildElement += xml_elementL1->GetText();
            return str_RetChildElement;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << "!!!       Empty Element in XML       !!!" << endl;
            cout << "----------------------------------------" << endl;
            return str_RetChildElement;
        }
    }
    else
    {
        while( uni_ClildCounter < uni_ChildIndex )
        {
            xml_elementL1 = xml_elementL1->NextSiblingElement();
            uni_ClildCounter++;
        }
        
        if( xml_elementL1 != NULL )
        {
            // tips 番茄@20171204 - 当xml_elementL1不存在Text时，调用GetText()就会崩溃!!!
            str_RetChildElement += xml_elementL1->GetText();
            return str_RetChildElement;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << "!!!       Empty Element in XML       !!!" << endl;
            cout << "----------------------------------------" << endl;
            return str_RetChildElement;
        }
    }
}

string CXMLParser::QueryElementL1Attribute(const string str_ChildElementL1, const string str_ChildAttribute,\
                                           const string str_ChildAttributeContent)
{
    XMLElement *xml_root = m_xml_dom.RootElement();
    string str_RetChildElement = string("");

    XMLElement *xml_elementL1 = xml_root->FirstChildElement(str_ChildElementL1.c_str());

    if( xml_elementL1 == NULL )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!       Empty Element in XML       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_RetChildElement;
    }
    else
    {
        while( xml_elementL1 != NULL )
        {
            // tips 番茄@20171204 - 当xml_elementL1不存在Attribute时，调用Attribute()会崩溃!!!
            if( xml_elementL1->Attribute(str_ChildAttribute.c_str()) == str_ChildAttributeContent )
            {
                str_RetChildElement += xml_elementL1->GetText();
                return str_RetChildElement;
            }
            xml_elementL1 = xml_elementL1->NextSiblingElement();
        }

        cout << "----------------------------------------" << endl;
        cout << "!!!       Empty Element in XML       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_RetChildElement;
    }

}

string CXMLParser::QueryElementL2(const string str_ChildElementL1, const string str_ChildElementL2,\
                                  const unsigned int uni_ChildIndex)
{
    XMLElement *xml_root = m_xml_dom.RootElement();
    string str_RetChildElement = string("");
    unsigned int uni_ClildCounter = 1;

    XMLElement *xml_elementL1 = xml_root->FirstChildElement(str_ChildElementL1.c_str());
    XMLElement *xml_elementL2;

    if( xml_elementL1 != NULL )
    {
        xml_elementL2 = xml_elementL1->FirstChildElement(str_ChildElementL2.c_str());
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!       Empty Element in XML       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_RetChildElement;
    }

    if(uni_ChildIndex == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!         Error Child Index        !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_RetChildElement;
    }
    
    if( uni_ChildIndex == 1 )
    {
        if( xml_elementL2 != NULL )
        {
            str_RetChildElement += xml_elementL2->GetText();
            return str_RetChildElement;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << "!!!       Empty Element in XML       !!!" << endl;
            cout << "----------------------------------------" << endl;
            return str_RetChildElement;
        }
    }
    else
    {
        while( uni_ClildCounter < uni_ChildIndex )
        {
            xml_elementL2 = xml_elementL2->NextSiblingElement();
            uni_ClildCounter++;
        }
        
        if( xml_elementL2 != NULL )
        {
            str_RetChildElement += xml_elementL2->GetText();
            return str_RetChildElement;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << "!!!       Empty Element in XML       !!!" << endl;
            cout << "----------------------------------------" << endl;
            return str_RetChildElement;
        }
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
