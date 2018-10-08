
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include "DefCMD.h"


string  CMD_HELP_CHECK_FA  = CHECK;
string  CMD_HELP_UPDATE_FA = UPDATE;
string  CMD_HELP_SHOW_FA   = SHOW;

string  CMD_HELP_CHECK_SUM  = CHECK + " " + SUM;
string  CMD_HELP_UPDATE_SUM = UPDATE + " " + SUM;
string  CMD_HELP_SHOW_SUM   = SHOW + " " + SUM;

string  CMD_HELP_MODIFY_LIFE = MODIFY_LIFE + " VALUE -sp SRC";
string  CMD_HELP_PATCH_MODIFY_LIFE = "SRC = " + WEIXIN;

string  CMD_HELP_CHECK_MONTH  = CHECK + " " + MONTH + " -m MONTH -sp " + TRAVERSAL;
string  CMD_HELP_UPDATE_MONTH = UPDATE + " " + MONTH;
string  CMD_HELP_SHOW_MONTH   = SHOW + " " + MONTH;

string  CMD_HELP_CHECK_SUBMONTH  = CHECK + " -sm SM";
string  CMD_HELP_PATCH_CHECK_SUBMONTH = "SM = " + ALL + "/" + DGTLER + "/" + BOOKS + "/" + KEEP + "/" + TB + "/" + SA;
string  CMD_HELP_UPDATE_SUBMONTH  = UPDATE + " -sm SM";
string  CMD_HELP_SHOW_SUBMONTH  = SHOW + " -sm SM";

string  CMD_HELP_CHECK_TITLE = CHECK + " -tt TT";
string  CMD_HELP_PATCH_CHECK_TITLE = "TT = " + DK + "/" + NS + "/" + NR + "/" + TRAVEL + "/" + LOTTERY;
string  CMD_HELP_UPDATE_TITLE = UPDATE + " -tt TT";
string  CMD_HELP_SHOW_TITLE = SHOW + " -tt TT -sp tag";

string  CMD_HELP_TRANSFER = TRANSFER + " VALUE -sp SRC";
string  CMD_HELP_PATCH_TRANSFER = "SRC = " + WEIXIN + "/" + JINGDONG;
string  CMD_HELP_LOTTERY = LOTTERY + " -f VALUE -d DATE";

string  CMD_HELP_ANALYSIS_TREND = ANALYSIS + " " + TREND + " -sp TO";
string  CMD_HELP_PATCH_ANALYSIS_TREND = "TO = " + EXPENSE + "/" + LIFE + "/" + ROOM + "/" + CONSUMPTION;
string  CMD_HELP_ANALYSIS_PROPORTION = ANALYSIS + " " + PROPORTION + " -m MONTH";
string  CMD_HELP_COMPARE_MONTH = COMPARE + " -m MONTH -sp MONTH";

string  CMD_HELP_SUMMARIZE = SUMMARIZE + " -sp TAR";
string  CMD_HELP_PATCH_SUMMARIZE = "TAR = " + MONTH + "/" + TITLE + "/" + TAIL;
string  CMD_HELP_FORECAST = FORECAST + " -sp MONTH -ip SALARY_PATCH";

string  CMD_HELP_PRINT_SUM    = PRINT + " " + SUM;
string  CMD_HELP_PRINT_MONTH    = PRINT + " " + MONTH + " -m MONTH";
string  CMD_HELP_PRINT_SUBMONTH = PRINT + " -sm SM -m MONTH -sp " + TRAVERSAL;
string  CMD_HELP_PATCH_PRINT_SUBMONTH = "SM = " + ALL + "/" + DGTLER + "/" + BOOKS + "/" + KEEP + "/" + TB + "/" + SA;
string  CMD_HELP_PRINT_TITLE    = PRINT + " -tt TT";
string  CMD_HELP_PATCH_PRINT_TITLE = "TT = " + DK + "/" + NS + "/" + NR + "/" + TRAVEL + "/" + LOTTERY;

string  CMD_HELP_INSERT_LINE = INSERT + " -l LINE -ip VALUE -sp CONTENT";
string  CMD_HELP_INSERT_BLANK_LINE = INSERT + " " + BLANK + " -l LINE";
string  CMD_HELP_MODIFY_LINE = MODIFY + " -l LINE -ip VALUE -sp CONTENT";
string  CMD_HELP_COPY_LINE   = COPY + " -l LINE -ip NEWLINE";
string  CMD_HELP_MOVE_LINE   = MOVE + " -l LINE -ip NEWLINE";
string  CMD_HELP_DELETE_LINE = DELETE + " -l LINE";

string  CMD_HELP_APPEND_MONTH = APPEND + " " + MONTH + " -sp MONTH";

string  CMD_HELP_CHECK_FILE = CHECK + " " + FFILE;
string  CMD_HELP_CHECK_TIME = CHECK + " " + TIME;
string  CMD_HELP_SYNC   = SYNC;
string  CMD_HELP_WRITE  = WRITE;
string  CMD_HELP_BACKUP = BACKUP;

string  CMD_HELP_HELP = HELP;

string  CMD_HELP_CANCEL = CANCEL;
string  CMD_HELP_EXIT   = EXIT;


//------------------------------//
//   River flows in summer
//------------------------------//
