
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

string  CMD_HELP_MODIFY_LIFE = MODIFY_LIFE + " -f VALUE -sp SRC";
string  CMD_HELP_PATCH_MODIFY_LIFE = "SRC = " + WEIXIN;

//string  HELP_CMD_TYPE_CHECK_MONTH    ("CheckMonth")
//string  HELP_CMD_TYPE_UPDATE_MONTH   ("UpdateMonth")
//string  HELP_CMD_TYPE_SHOW_MONTH     ("ShowMonth")

//string  HELP_CMD_TYPE_CHECK_SUBMONTH    ("CheckSubMonth")
//string  HELP_CMD_TYPE_UPDATE_SUBMONTH   ("UpdateSubMonth")

//string  HELP_CMD_TYPE_CHECK_TITLE    ("CheckTitle")
//string  HELP_CMD_TYPE_UPDATE_TITLE   ("UpdateTitle")

//string  CMD_HELP_TRANSFER    ("Transfer")
//string  CMD_HELP_LOTTERY     ("Lottery")

string  CMD_HELP_ANALYSIS_TREND = ANALYSIS + " " + TREND + " -sp TO";
string  CMD_HELP_PATCH_ANALYSIS_TREND = "TO = " + EXPENSE + "/" + LIFE + "/" + ROOM + "/" + CONSUMPTION;
//string  HELP_CMD_TYPE_ANALYSIS_PROPORTION    ("AnalysisProportion")

//string  HELP_CMD_TYPE_SUMMARIZE    ("Summarize")
string  CMD_HELP_FORECAST = FORECAST + " -sp MONTH -ip SALARY_PATCH";

string  CMD_HELP_PRINT_MONTH    = PRINT + " " + MONTH + " -m MONTH";
string  CMD_HELP_PRINT_SUBMONTH = PRINT + " -sm SM -m MONTH";
string  CMD_HELP_PATCH_PRINT_SUBMONTH = "SM = " + DGTLER + "/" + BOOKS + "/" + KEEP + "/" + TB + "/" + SA;
string  CMD_HELP_PRINT_TITLE    = PRINT + " -tt TT";
string  CMD_HELP_PATCH_PRINT_TITLE = "TT = " + DK + "/" + NS + "/" + TRAVEL + "/" + LOTTERY;

string  CMD_HELP_INSERT_LINE = INSERT + " -l LINE -ip VALUE -sp CONTENT";
string  CMD_HELP_INSERT_BLANK_LINE = INSERT + " " + BLANK + " -l LINE";
string  CMD_HELP_MODIFY_LINE = MODIFY + " -l LINE -ip VALUE -sp CONTENT";
string  CMD_HELP_MODIFY_VALUE_LINE = MODIFY + " " + VALUE + " -l LINE -ip VALUE";
string  CMD_HELP_MODIFY_CONTENT_LINE = MODIFY + " " + CONTENT + " -l LINE -sp CONTENT";
string  CMD_HELP_COPY_LINE   = COPY + " -l LINE -ip NEWLINE";
string  CMD_HELP_MOVE_LINE   = MOVE + " -l LINE -ip NEWLINE";
string  CMD_HELP_DELETE_LINE = DELETE + " -l LINE";

string  CMD_HELP_APPEND_MONTH = APPEND + " " + MONTH + " -sp MONTH";

//string  HELP_CMD_TYPE_SYNC        ("Sync")
//string  HELP_CMD_TYPE_WRITE       ("Write")
//string  HELP_CMD_TYPE_BACKUP      ("Backup")

//string  HELP_CMD_TYPE_HELP    ("Help")
//string  HELP_CMD_TYPE_TEST    ("Test")

//string  HELP_CMD_TYPE_CANCEL      ("Cancel")
//string  HELP_CMD_TYPE_EXIT        ("Exit")


//------------------------------//
//   River flows in summer
//------------------------------//
