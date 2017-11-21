
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <string>
#include <regex>

using namespace std;


#define LTYPE_HEADTITLE     1   // 总标题
#define LTYPE_SUBTITLE      2   // 单项标题
#define LTYPE_MONTHTITLE    3   // 月度标题

#define LTYPE_BLANK         7   // 空行
#define LTYPE_DELIMITER     8   // 分隔线
#define LTYPE_EOF           9   // 结束线

#define LTYPE_FBIRC_AGGR        11   // 总金额
#define LTYPE_FBIRC_TITLESUM    12   // 单项金额
#define LTYPE_FBIRC_MONTHSUM    13   // 月度金额
#define LTYPE_FBIRC_LINEUINT    14   // 单行金额


regex REP_HeadTitle("^(# )(.{1,})$");
regex REP_SubTitle("^(## )(.{1,})$");
regex REP_MonthTitle("^(## )(.{1,})(\\.M\\d{2})$");

regex REP_Blank("^$");
regex REP_Delimiter("^(```)$");
regex REP_EOF("^(---)$");

regex REP_FBric_Aggr("^(.{1,})( : )(\\+|-)(\\d{1,})$");
regex REP_FBric_TitleSum("^(> )(\\+|-)(\\d{1,})$");
regex REP_FBric_MonthSum("^(> )(\\d{1,})(.{1,})( : )(\\+|-)(\\d{1,})$");
regex REP_FBric_LineUnit("^(`)(\\+|-)( )(\\d{1,})(` )(.{1,})$");


//------------------------------//
//   river flows in summer
//------------------------------//
