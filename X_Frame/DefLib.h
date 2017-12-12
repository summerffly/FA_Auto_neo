
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#ifndef _DEFLIB_H_
#define _DEFLIB_H_

/****************************************/
//   Global Scope DEF
/****************************************/

#define MAX_COMMAND         128     // CMD最大字符数
#define MAX_FULLFILENAME    128     // .md文件_最大文件全名长度
#define MAX_LINE_CHAR       128     // .md文件_每行最大字符数
#define MAX_LINE            512     // .md文件_最大支持行数

/****************************************/
//   EP_Layer DEF
/****************************************/

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


#endif

//------------------------------//
//   River flows in summer
//------------------------------//
