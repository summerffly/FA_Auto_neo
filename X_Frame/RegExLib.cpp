
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "RegExLib.h"

using namespace std;

/****************************************/
//   OP_Layer RE
/****************************************/

regex RE_fullfilename("^(.+/)(.+\\.md)$");   // tips 番茄@20171127 - "贪心"匹配模式，匹配尽可能长的字符串
regex RE_eof("^---$");

/****************************************/
//   EP_Layer RE
/****************************************/

regex REP_HeadTitle("^(# )(.{1,})$");
regex REP_SubTitle("^(## )(.{1,})$");
regex REP_MonthTitle("^(## )(.{1,})(\\.M\\d{2})(n*)$");
regex REP_TTTag("^(### )(.{1,})$");

regex REP_Blank("^$");
regex REP_Delimiter("^(```)$");
regex REP_TimeStamp("^(\\*)(Update Time)( : )(.{1,})(\\*)$");
regex REP_EOF("^(---)$");

regex REP_FBric_Aggr("^(.{1,})( : )(\\+|-)(\\d{1,})$");
regex REP_FBric_TitleSum("^(> )(\\+|-)(\\d{1,})$");
regex REP_FBric_SubTitleSum("^(>> )(\\+|-)(\\d{1,})$");
regex REP_FBric_MonthSum("^(> )(\\d{2})(.{1,})( : )(\\+|-)(\\d{1,})$");
regex REP_FBric_LineUnit("^(`)(\\+|-)( )(\\d{1,})(` )(.{1,})$");
regex REP_FBric_RateOI("^(.{1,})( : )(\\+|-)(\\d{1,})(%)$");

//------------------------------//
//   River flows in summer
//------------------------------//
