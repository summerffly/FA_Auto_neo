
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
    m_int_LineIndex = 0;
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
    m_int_LineIndex = int_LineIndex;
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
        else if( regex_match(m_str_FullLine, str_Match, REP_SubTitle) )
        {
            m_uni_LineType = LTYPE_SUBTITLE;

            if( regex_match(m_str_FullLine, str_Match, REP_MonthTitle) )
            {
                m_uni_LineType = LTYPE_MONTHTITLE;
            }

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
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_Aggr) )
        {
            m_uni_LineType = LTYPE_FBIRC_AGGR;
            ValuePMParser(str_Match[3]);

            m_str_LineContent = str_Match[1];

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_TitleSum) )
        {
            m_uni_LineType = LTYPE_FBIRC_TITLESUM;
            ValuePMParser(str_Match[2]);

            m_str_LineContent = "";
            
            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_MonthSum) )
        {
            m_uni_LineType = LTYPE_FBIRC_MONTHSUM;
            ValuePMParser(str_Match[5]);

            m_str_LineContent = str_Match[2];
            m_str_LineContent += str_Match[3];

            break;
        }
        else if( regex_match(m_str_FullLine, str_Match, REP_FBric_LineUnit) )
        {
            m_uni_LineType = LTYPE_FBIRC_LINEUINT;
            ValuePMParser(str_Match[2]);

            m_str_LineContent = str_Match[6];

            break;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << "!!!    Line Type RegEx Un-matched    !!!" << endl;
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

int CLineEPer::GetLineType()
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





//------------------------------//
//   River flows in summer
//------------------------------//
