
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "LineEPer.h"

#include "./../X_Frame/DefLib.h"
#include "./../X_Frame/RegExLib.h"

using namespace std;


CLineEPer::CLineEPer()
{
    m_uni_LineType = 0;
    m_bol_LineValuePM = true;
    m_uni_LineValueABS = 0;
    m_int_LineValue = 0;
    m_str_LineContent = "";
    m_str_FullLine = "";
    m_bol_LineModFlag = false;
}

CLineEPer::CLineEPer(const char *cha_LineBuffer)
{
    m_str_FullLine = cha_LineBuffer;
    m_bol_LineModFlag = false;

    LineParser();
    UpdateValue(true);
}

CLineEPer::CLineEPer(const unsigned int uni_LineType, const int int_LineValue, const string str_LineContent)
{
    m_uni_LineType = uni_LineType;
    m_int_LineValue = int_LineValue;
    m_str_LineContent = str_LineContent;
    m_bol_LineModFlag = true;

    UpdateValue(false);
    UpdateFullLine();
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
            m_uni_LineValueABS = 0;
            m_int_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        // tips 番茄@20171121 - REP_MonthTitle和REP_SubTitle有包含关系，REP_MonthTitle必须前置
        else if( regex_match(m_str_FullLine, str_Match, REP_MonthTitle) )
        {
            m_uni_LineType = LTYPE_MONTHTITLE;
            m_bol_LineValuePM = true;
            m_uni_LineValueABS = 0;
            m_int_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_SubTitle) )
        {
            m_uni_LineType = LTYPE_SUBTITLE;
            m_bol_LineValuePM = true;
            m_uni_LineValueABS = 0;
            m_int_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_TTTag) )
        {
            m_uni_LineType = LTYPE_TTTAG;
            m_bol_LineValuePM = true;
            m_uni_LineValueABS = 0;
            m_int_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_Blank) )
        {
            m_uni_LineType = LTYPE_BLANK;
            m_bol_LineValuePM = true;
            m_uni_LineValueABS = 0;
            m_int_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_Delimiter) )
        {
            m_uni_LineType = LTYPE_DELIMITER;
            m_bol_LineValuePM = true;
            m_uni_LineValueABS = 0;
            m_int_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_TimeStamp) )
        {
            m_uni_LineType = LTYPE_TIMESTAMP;
            m_bol_LineValuePM = true;
            m_uni_LineValueABS = 0;
            m_int_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_EOF) )
        {
            m_uni_LineType = LTYPE_EOF;
            m_bol_LineValuePM = true;
            m_uni_LineValueABS = 0;
            m_int_LineValue = 0;
            m_str_LineContent = m_str_FullLine;

            break;
        }
        // tips 番茄@20171121 - REP_FBric_MonthSum和REP_FBric_Aggr有包含关系，REP_FBric_MonthSum必须前置
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_MonthSum) )
        {
            m_uni_LineType = LTYPE_FBIRC_MONTHSUM;
            ValuePMParser(str_Match[5]);
            string str_ValueTemp = str_Match[6];
            m_uni_LineValueABS = atoi(str_ValueTemp.c_str());
            m_str_LineContent = str_Match[2];
            m_str_LineContent += str_Match[3];

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_Aggr) )
        {
            m_uni_LineType = LTYPE_FBIRC_AGGR;
            ValuePMParser(str_Match[3]);
            string str_ValueTemp = str_Match[4];
            m_uni_LineValueABS = atoi(str_ValueTemp.c_str());
            m_str_LineContent = str_Match[1];

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_TitleSum) )
        {
            m_uni_LineType = LTYPE_FBIRC_TITLESUM;
            ValuePMParser(str_Match[2]);
            string str_ValueTemp = str_Match[3];
            m_uni_LineValueABS = atoi(str_ValueTemp.c_str());
            m_str_LineContent = "";
            
            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_LineUnit) )
        {
            m_uni_LineType = LTYPE_FBIRC_LINEUINT;
            ValuePMParser(str_Match[2]);
            string str_ValueTemp = str_Match[4];
            m_uni_LineValueABS = atoi(str_ValueTemp.c_str());
            m_str_LineContent = str_Match[6];

            break;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << "ERROR LINE" << endl;
            cout << ">>> " << m_str_FullLine << endl;
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

unsigned int CLineEPer::GetLineType()
{
    return m_uni_LineType;
}

string CLineEPer::GetLineContent()
{
    return m_str_LineContent;
}

string CLineEPer::GetFullLine()
{
    return m_str_FullLine;
}

bool CLineEPer::GetLineValuePM()
{
    return m_bol_LineValuePM;
}

unsigned int CLineEPer::GeLineValueABS()
{
    return m_uni_LineValueABS;
}

int CLineEPer::GetLineValue()
{
    return m_int_LineValue;
}

bool CLineEPer::GetLineModFlag()
{
    return m_bol_LineModFlag;
}

void CLineEPer::SetLineValuePM(const bool bol_LineValuePM)
{
    m_bol_LineValuePM = bol_LineValuePM;
    UpdateValue(true);
    m_bol_LineModFlag = true;
    UpdateFullLine();
}

void CLineEPer::SetLineValueABS(const unsigned int uni_LineValueABS)
{
    m_uni_LineValueABS = uni_LineValueABS;
    UpdateValue(true);
    m_bol_LineModFlag = true;
    UpdateFullLine();
}

void CLineEPer::SetLineValue(const int int_LineValue)
{
    m_int_LineValue = int_LineValue;
    UpdateValue(false);
    m_bol_LineModFlag = true;
    UpdateFullLine();
}

void CLineEPer::SetLineContent(const char *cha_LineContent)
{
    m_str_LineContent = cha_LineContent;
    m_bol_LineModFlag = true;
    UpdateFullLine();
}

void CLineEPer::SetLineModFlag(const bool bol_LineModFlag)
{
    m_bol_LineModFlag = bol_LineModFlag;
}

// 通过UpdateValue()，保证了Value/ValuePM&ABS的同步一致性
void CLineEPer::UpdateValue(bool bol_UpdateDirection)
{
    if(bol_UpdateDirection)   // TRUE: 更新Value
    {
        if(m_bol_LineValuePM)
            m_int_LineValue = m_uni_LineValueABS;
        else
            m_int_LineValue = (-1) * (int)m_uni_LineValueABS;
    }
    else   // FALSE: 更新ValuePM&ABS
    {
        if(m_int_LineValue > 0)
        {
            m_bol_LineValuePM = true;
            m_uni_LineValueABS = m_int_LineValue;
        }
        else
        {
            m_bol_LineValuePM = false;
            m_uni_LineValueABS = (-1) * m_int_LineValue;
        }
    }

}

// tips 番茄@20171125 - 目前只支持更新包含金额的行
void CLineEPer::UpdateFullLine()
{
    if(m_bol_LineModFlag == false)
        return;

    char *cha_ValueABS = new char[9];     // tips 番茄@20171121 - 支持到百万级
    
    switch(m_uni_LineType)
    {
        case(LTYPE_MONTHTITLE):
            {
                m_str_FullLine.clear();
                m_str_FullLine += m_str_LineContent;
            }
            break;
        case(LTYPE_FBIRC_AGGR):
            {
                m_str_FullLine.clear();
                m_str_FullLine += m_str_LineContent;
                m_str_FullLine += " : ";
                if(m_bol_LineValuePM)
                    m_str_FullLine += "+";
                else
                    m_str_FullLine += "-";
                sprintf(cha_ValueABS, "%d", m_uni_LineValueABS);
                m_str_FullLine += cha_ValueABS;
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
                sprintf(cha_ValueABS, "%d", m_uni_LineValueABS);
                m_str_FullLine += cha_ValueABS;
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
                sprintf(cha_ValueABS, "%d", m_uni_LineValueABS);
                m_str_FullLine += cha_ValueABS;
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
                sprintf(cha_ValueABS, "%d", m_uni_LineValueABS);
                m_str_FullLine += cha_ValueABS;
                m_str_FullLine += "` ";
                m_str_FullLine += m_str_LineContent;
            }
            break;
        case(LTYPE_BLANK):
            {
                m_str_FullLine.clear();
                m_str_FullLine += m_str_LineContent;
                m_bol_LineValuePM = true;   // tips 番茄@20171225 - 保持BLANK一致性
            }
            break;
        case(LTYPE_TIMESTAMP):
            {
                m_str_FullLine.clear();
                m_str_FullLine += m_str_LineContent;
                m_bol_LineValuePM = true;
            }
            break;
        default:
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!      Line Type Un-Supported      !!!" << endl;
                cout << "----------------------------------------" << endl;
            }
    }

    m_bol_LineModFlag = false;

    delete []cha_ValueABS;
}

bool CLineEPer::IsContainKey(const char *cha_Key)
{
    smatch str_Match;
    string pattern_key = cha_Key;
    regex RE_key(pattern_key);

    if( regex_search(m_str_LineContent, str_Match, RE_key) )
    {
        return true;
    }
    else
    {
        return false;
    }
}


//------------------------------//
//   River flows in summer
//------------------------------//
