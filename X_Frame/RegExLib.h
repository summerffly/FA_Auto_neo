
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#ifndef _REGEXLIB_H_
#define _REGEXLIB_H_

#include <string>
#include <regex>

using namespace std;

/****************************************/
//   OP_Layer RE
/****************************************/

extern regex RE_fullfilename;
extern regex RE_eof;

/****************************************/
//   EP_Layer RE
/****************************************/

extern regex REP_HeadTitle;
extern regex REP_SubTitle;
extern regex REP_MonthTitle;
extern regex REP_TTTag;

extern regex REP_Blank;
extern regex REP_Delimiter;
extern regex REP_TimeStamp;
extern regex REP_EOF;

extern regex REP_FBric_Aggr;
extern regex REP_FBric_TitleSum;
extern regex REP_FBric_SubTitleSum;
extern regex REP_FBric_MonthSum;
extern regex REP_FBric_LineUnit;
extern regex REP_FBric_RateOI;


#endif

//------------------------------//
//   River flows in summer
//------------------------------//
