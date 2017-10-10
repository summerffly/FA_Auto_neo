
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "LineEPer.h"

using namespace std;


CLineEPer::CLineEPer()
{
    m_str_ParentFileName = "";
    m_bol_LineModFlag = false;
    m_int_LineIndex = 0;
    m_uni_LineType = 0;
    m_uni_LineValuePM = true;
    m_uni_LineValue = 0;
    m_str_LineContent = "";
    m_str_FullLine = "";
}

CLineEPer::CLineEPer(const char *cha_FileName, const char *cha_LineBuffer)
{
    m_str_ParentFileName = cha_FileName;
    LineParser(cha_LineBuffer);
}

CLineEPer::~CLineEPer()
{
    // Do Nothing
}

int CLineEPer::LineParser(const char *cha_LineBuffer)
{
    m_str_FullLine = cha_LineBuffer;

    return 0;
}



//------------------------------//
//   River flows in summer
//------------------------------//
