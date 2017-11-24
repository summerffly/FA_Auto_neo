
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "LineEPer.h"
#include "EP_Layer_DEF.h"

using namespace std;


CLineEPer::CLineEPer()
{
    m_str_ParentFileName = "";
    m_uni_LineIndex = 0;
    m_uni_LineType = 0;
    m_bol_LineValuePM = true;
    m_uni_LineValue = 0;
    m_str_LineContent = "";
    m_str_FullLine = "";
    m_bol_LineModFlag = false;
}

CLineEPer::CLineEPer(const char *cha_FileName, const int int_LineIndex, const char *cha_LineBuffer)
{
    m_str_ParentFileName = cha_FileName;
    m_uni_LineIndex = int_LineIndex;
    m_str_FullLine = cha_LineBuffer;
    m_bol_LineModFlag = false;

    LineParser();
}

CLineEPer::~CLineEPer()
{
    // Do Nothing
}

int CLineEPer::LineParser()
{
    smatch str_Match;

    while(1)
    {
        if( regex_match(m_str_FullLine, str_Match, REP_HeadTitle) )
        {
            m_uni_LineType = LTYPE_HEADTITLE;
            m_bol_LineValuePM = true;
            m_uni_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        // tips 番茄@20171121 - REP_MonthTitle和REP_SubTitle有包含关系，REP_MonthTitle必须前置
        else if( regex_match(m_str_FullLine, str_Match, REP_MonthTitle) )
        {
            m_uni_LineType = LTYPE_MONTHTITLE;
            m_bol_LineValuePM = true;
            m_uni_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_SubTitle) )
        {
            m_uni_LineType = LTYPE_SUBTITLE;
            m_bol_LineValuePM = true;
            m_uni_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_Blank) )
        {
            m_uni_LineType = LTYPE_BLANK;
            m_bol_LineValuePM = true;
            m_uni_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_Delimiter) )
        {
            m_uni_LineType = LTYPE_DELIMITER;
            m_bol_LineValuePM = true;
            m_uni_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_EOF) )
        {
            m_uni_LineType = LTYPE_EOF;
            m_bol_LineValuePM = true;
            m_uni_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        // tips 番茄@20171121 - REP_FBric_MonthSum和REP_FBric_Aggr有包含关系，REP_FBric_MonthSum必须前置
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_MonthSum) )
        {
            m_uni_LineType = LTYPE_FBIRC_MONTHSUM;
            ValuePMParser(str_Match[5]);
            string str_ValueTemp = str_Match[6];
            m_uni_LineValue = atoi(str_ValueTemp.c_str());
            m_str_LineContent = str_Match[2];
            m_str_LineContent += str_Match[3];

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_Aggr) )
        {
            m_uni_LineType = LTYPE_FBIRC_AGGR;
            ValuePMParser(str_Match[3]);
            string str_ValueTemp = str_Match[4];
            m_uni_LineValue = atoi(str_ValueTemp.c_str());
            m_str_LineContent = str_Match[1];

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_TitleSum) )
        {
            m_uni_LineType = LTYPE_FBIRC_TITLESUM;
            ValuePMParser(str_Match[2]);
            string str_ValueTemp = str_Match[3];
            m_uni_LineValue = atoi(str_ValueTemp.c_str());
            m_str_LineContent = "";
            
            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_LineUnit) )
        {
            m_uni_LineType = LTYPE_FBIRC_LINEUINT;
            ValuePMParser(str_Match[2]);
            string str_ValueTemp = str_Match[4];
            m_uni_LineValue = atoi(str_ValueTemp.c_str());
            m_str_LineContent = str_Match[6];

            break;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << "!!!       Line Type Un-Matched       !!!" << endl;
            cout << "----------------------------------------" << endl;

            return -1;
        }
    }
    return 0;
}

void CLineEPer::ValuePMParser(string str_ValuePM)
{
    if('+' == str_ValuePM.at(0))
    {
        m_bol_LineValuePM = true;
    }
    else
    {
        m_bol_LineValuePM = false;
    }
}

string CLineEPer::GetParentFileName()
{
    return m_str_ParentFileName;
}

unsigned int CLineEPer::GetLineIndex()
{
    return m_uni_LineIndex;
}

unsigned int CLineEPer::GetLineType()
{
    return m_uni_LineType;
}

bool CLineEPer::GetLineValuePM()
{
    return m_bol_LineValuePM;
}

unsigned int CLineEPer::GeLineValue()
{
    return m_uni_LineValue;
}

string CLineEPer::GetLineContent()
{
    return m_str_LineContent;
}

string CLineEPer::GetFullLine()
{
    return m_str_FullLine;
}

bool CLineEPer::GetLineModFlag()
{
    return m_bol_LineModFlag;
}

void CLineEPer::SetLineValuePM(const bool bol_LineValuePM)
{
    m_bol_LineValuePM = bol_LineValuePM;
    m_bol_LineModFlag = true;
}

void CLineEPer::SetLineValue(const unsigned int uni_LineValue)
{
    m_uni_LineValue = uni_LineValue;
    m_bol_LineModFlag = true;
}

void CLineEPer::SetLineModFlag(const bool bol_LineModFlag)
{
    m_bol_LineModFlag = bol_LineModFlag;
}

void CLineEPer::UpdateFullLine()
{
    if(m_bol_LineModFlag == false)
        return;

    char *cha_Value = new char[8];     // tips 番茄@20171121 - 支持到十万级
    
    switch(m_uni_LineType)
    {
        case(LTYPE_FBIRC_AGGR):
            {
                m_str_FullLine.clear();
                m_str_FullLine += m_str_LineContent;
                m_str_FullLine += " : ";
                if(m_bol_LineValuePM)
                    m_str_FullLine += "+";
                else
                    m_str_FullLine += "-";
                sprintf(cha_Value, "%d", m_uni_LineValue);
                m_str_FullLine += cha_Value;
            }
            break;
        case(LTYPE_FBIRC_TITLESUM):
            {
                m_str_FullLine.clear();
                m_str_FullLine += "> ";
                if(m_bol_LineValuePM)
                    m_str_FullLine += "+";
                else
                    m_str_FullLine += "-";
                sprintf(cha_Value, "%d", m_uni_LineValue);
                m_str_FullLine += cha_Value;
            }
            break;
        case(LTYPE_FBIRC_MONTHSUM):
            {
                m_str_FullLine.clear();
                m_str_FullLine += "> ";
                m_str_FullLine += m_str_LineContent;
                m_str_FullLine += " : ";
                if(m_bol_LineValuePM)
                    m_str_FullLine += "+";
                else
                    m_str_FullLine += "-";
                sprintf(cha_Value, "%d", m_uni_LineValue);
                m_str_FullLine += cha_Value;
            }
            break;
        case(LTYPE_FBIRC_LINEUINT):
            {
                m_str_FullLine.clear();
                m_str_FullLine += "`";
                if(m_bol_LineValuePM)
                    m_str_FullLine += "+";
                else
                    m_str_FullLine += "-";
                m_str_FullLine += " ";
                sprintf(cha_Value, "%d", m_uni_LineValue);
                m_str_FullLine += cha_Value;
                m_str_FullLine += "` ";
                m_str_FullLine += m_str_LineContent;
            }
            break;
        default:
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!          Line Type Error         !!!" << endl;
                cout << "----------------------------------------" << endl;
            }
    }

    m_bol_LineModFlag = false;

    delete []cha_Value;
}




//------------------------------//
//   river flows in summer
//------------------------------//
