
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
#define LTYPE_TTTAG         4   // 分项Tag

#define LTYPE_BLANK         11   // 空行
#define LTYPE_DELIMITER     12   // 分隔线
#define LTYPE_TIMESTAMP     13   // 更新时间戳
#define LTYPE_EOF           14   // 结束线

#define LTYPE_FBIRC_AGGR           21   // 总金额
#define LTYPE_FBIRC_TITLESUM       22   // 单项金额
#define LTYPE_FBIRC_MONTHSUM       23   // 月度金额
#define LTYPE_FBIRC_LINEUINT       24   // 单行金额
#define LTYPE_FBIRC_RATEOI         25   // ROI
#define LTYPE_FBIRC_SUBTITLESUM    26   // 单项子项金额

#endif

//------------------------------//
//   River flows in summer
//------------------------------//
