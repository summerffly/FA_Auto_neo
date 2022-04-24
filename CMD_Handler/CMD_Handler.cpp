
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Handler.h"

#include "./DefCMDHelp.h"
#include "./../X_Frame/DefLib.h"
#include "./../X_Frame/X_Tool.h"

CTool *ms_ptr_Tool = new CTool();
CXonfigLoader* CCMDHandler::ms_ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
CFAitfX* CCMDHandler::ms_ptr_FAitfX = Singleton<CFAitfX>::GetInstance();
CASitfX* CCMDHandler::ms_ptr_ASitfX = Singleton<CASitfX>::GetInstance();

string CCMDHandler::ms_str_FM_Type = "";
string CCMDHandler::ms_str_FM_Key = "";
string CCMDHandler::ms_str_FM_Month = "";
bool CCMDHandler::ms_bol_PR_Valid = false;


/**************************************************/
//   CMD_MAP()宏
/**************************************************/
X_BEGIN_CMD_MAP(CCMDHandler)
	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_FA, CMD_HELP_CHECK_FA, "", OnCmdCheckFA)

	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_FA, CMD_HELP_UPDATE_FA, "", OnCmdUpdateFA)

	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_FA, CMD_HELP_SHOW_FA, "", OnCmdShowFA)

	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_SUM, CMD_HELP_CHECK_SUM, "", OnCmdCheckSum)

	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_SUM, CMD_HELP_UPDATE_SUM, "", OnCmdUpdateSum)

	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_SUM, CMD_HELP_SHOW_SUM, "", OnCmdShowSum)

    X_ON_CMD_TYPE(X_CMD_TYPE_MODIFY_LIFE, CMD_HELP_MODIFY_LIFE, \
        CMD_HELP_PATCH_MODIFY_LIFE, OnCmdModifyLife)

	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_MONTH, CMD_HELP_CHECK_MONTH, "", OnCmdCheckMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_MONTH, CMD_HELP_UPDATE_MONTH, "", OnCmdUpdateMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_MONTH, CMD_HELP_SHOW_MONTH, "", OnCmdShowMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_EXMONTH, CMD_HELP_CHECK_EXMONTH, "", OnCmdCheckExMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_EXMONTH, CMD_HELP_UPDATE_EXMONTH, "", OnCmdUpdateExMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_EXMONTH, CMD_HELP_SHOW_EXMONTH, "", OnCmdShowExMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_SUBMONTH, CMD_HELP_CHECK_SUBMONTH, \
        CMD_HELP_PATCH_CHECK_SUBMONTH, OnCmdCheckSubMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_SUBMONTH, CMD_HELP_UPDATE_SUBMONTH, "", OnCmdUpdateSubMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_SUBMONTH, CMD_HELP_SHOW_SUBMONTH, "", OnCmdShowSubMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_TITLE, CMD_HELP_CHECK_TITLE, \
        CMD_HELP_PATCH_CHECK_TITLE, OnCmdCheckTitle)

    X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_TITLE, CMD_HELP_UPDATE_TITLE, "", OnCmdUpdateTitle)

    X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_TITLE, CMD_HELP_SHOW_TITLE, "", OnCmdShowTitle)

    X_ON_CMD_TYPE(X_CMD_TYPE_TRANSFER, CMD_HELP_TRANSFER, CMD_HELP_PATCH_TRANSFER, OnCmdTransfer)

    X_ON_CMD_TYPE(X_CMD_TYPE_ANALYSIS_TREND, CMD_HELP_ANALYSIS_TREND, \
        CMD_HELP_PATCH_ANALYSIS_TREND, OnCmdAnalysisTrend)

    X_ON_CMD_TYPE(X_CMD_TYPE_ANALYSIS_PROPORTION, CMD_HELP_ANALYSIS_PROPORTION, "", OnCmdAnalysisProportion)

    X_ON_CMD_TYPE(X_CMD_TYPE_COMPARE_MONTH, CMD_HELP_COMPARE_MONTH, "", OnCmdCompareMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_SUMMARIZE, CMD_HELP_SUMMARIZE, \
        CMD_HELP_PATCH_SUMMARIZE, OnCmdSummarize)

	X_ON_CMD_TYPE(X_CMD_TYPE_FORECAST, CMD_HELP_FORECAST, "", OnCmdForecast)

    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_SUM, CMD_HELP_PRINT_SUM, "", OnCmdPrintSum)

    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_MONTH, CMD_HELP_PRINT_MONTH, "", OnCmdPrintMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_SUBMONTH, CMD_HELP_PRINT_SUBMONTH, \
        CMD_HELP_PATCH_PRINT_SUBMONTH, OnCmdPrintSubMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_TITLE, CMD_HELP_PRINT_TITLE, \
        CMD_HELP_PATCH_PRINT_TITLE, OnCmdPrintTitle)

    X_ON_CMD_TYPE(X_CMD_TYPE_INSERT_LINE, CMD_HELP_INSERT_LINE, "", OnCmdInsertLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_INSERT_BLANK_LINE, CMD_HELP_INSERT_BLANK_LINE, "", OnCmdInsertBlankLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_MODIFY_LINE, CMD_HELP_MODIFY_LINE, "", OnCmdModifyLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_COPY_LINE, CMD_HELP_COPY_LINE, "", OnCmdCopyLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_MOVE_LINE, CMD_HELP_MOVE_LINE, "", OnCmdMoveLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_DELETE_LINE, CMD_HELP_DELETE_LINE, "", OnCmdDeleteLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_APPEND_MONTH, CMD_HELP_APPEND_MONTH, "", OnCmdAppendMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_FILE, CMD_HELP_CHECK_FILE, "", OnCmdCheckFile)

    X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_TIME, CMD_HELP_CHECK_TIME, "", OnCmdCheckTime)

	X_ON_CMD_TYPE(X_CMD_TYPE_SYNC, CMD_HELP_SYNC, "", OnCmdSync)

	X_ON_CMD_TYPE(X_CMD_TYPE_WRITE, CMD_HELP_WRITE, "", OnCmdWrite)

	X_ON_CMD_TYPE(X_CMD_TYPE_BACKUP, CMD_HELP_BACKUP, "", OnCmdBackup)

    X_ON_CMD_TYPE(X_CMD_TYPE_HELP, CMD_HELP_HELP, "", OnCmdHelp)

    X_ON_CMD_TYPE(X_CMD_TYPE_TEST, "", "", OnCmdTest)

    X_ON_CMD_TYPE(X_CMD_TYPE_TESTT, "", "", OnCmdTestt)

    X_ON_CMD_TYPE(X_CMD_TYPE_TESTTT, "", "", OnCmdTesttt)

	X_ON_CMD_TYPE(X_CMD_TYPE_CANCEL, CMD_HELP_CANCEL, "", OnCmdCancel)

	X_ON_CMD_TYPE(X_CMD_TYPE_EXIT, CMD_HELP_EXIT, "", OnCmdExit)
X_END_CMD_MAP()

/**************************************************/
//   CMD_NOTIFY()宏
/**************************************************/
CMD_NOTIFY(CCMDHandler)

/**************************************************/
//   CCMDHandler 构造函数
/**************************************************/
CCMDHandler::CCMDHandler()
{
    // Nothing To Do
}

/**************************************************/
//   CCMDHandler 析构函数
/**************************************************/
CCMDHandler::~CCMDHandler()
{
    // Nothing To Do
}

/**************************************************/
//   CMD 命令循环
/**************************************************/
void CCMDHandler::CMD_Loop()
{
    char CMD_linebuffer[MAX_COMMAND];
    
    while(1)
    {
        cout << "[CMD] # " << "\033[0;32m";
        cin.getline(CMD_linebuffer, MAX_COMMAND);
        cout << "\033[0m";

        CMD_Packet xCmdPacket = CMD_Packet();

        /**************************************************/

        if(-1 == xCmdPacket.CMDRipper(CMD_linebuffer))
        {
            //CTool::MassageOutFotmat("Blank CMD", '!');
            continue;
        }

        /**************************************************/

        if(0 != xCmdPacket.CMDFilter())
        {
            CTool::MassageOutFotmat("Error-Format CMD", '!');
            continue;
        }

        /**************************************************/

        int int_RetParser = xCmdPacket.CMDParser();
        if(-1 == int_RetParser)
        {
            CTool::MassageOutFotmat("Error -Option", '!');
            continue;
        }
        else if(-2 == int_RetParser)
        {
            CTool::MassageOutFotmat("SM&TT-Conflict Param", '!');
            continue;
        }
        else if(-3 == int_RetParser)
        {
            CTool::MassageOutFotmat("Invalid Month Param", '!');
            continue;
        }
        else if(-4 == int_RetParser)
        {
            CTool::MassageOutFotmat("Error CMD (BL)", '!');
            continue;
        }

        /**************************************************/

        int int_RetParamChecker = xCmdPacket.CMDParamChecker();
        if(-1 == int_RetParamChecker)
        {
            CTool::MassageOutFotmat("SM-Param Error", '!');
            continue;
        }
        else if(-2 == int_RetParamChecker)
        {
            CTool::MassageOutFotmat("TT-Param Error", '!');
            continue;
        }

        /**************************************************/

        CTool::TagTimeBait();

        CMD_PrintRecode(xCmdPacket);
        int int_RetNotify = CmdNotify(xCmdPacket);

        if(0 == int_RetNotify)
        {
            CTool::ShowTimeGap();
            cout << "----------------------------------------" << endl;
            continue;
        }
        else if(1 == int_RetNotify)
        {
            break;
        }
        else
        {
            CTool::MassageOutFotmat("Error CMD (AL)", '!');
            continue;
        }

        /**************************************************/
    }
}

void CCMDHandler::CMD_Init()
{    
    ms_ptr_FAitfX->LoadSum(0);
    ms_ptr_FAitfX->SummarizeMonth(0);
    ms_ptr_FAitfX->SummarizeTitle(0);
    ms_ptr_FAitfX->SummarizeTail(0);
    ms_ptr_FAitfX->SummarizeCAF(0);

    cout << "\033[0;36m"
         << "****************************************" << endl
         << "****************************************" << endl
         << "***                                  ***" << endl
         << "***          "
                << "\033[1;33m FA_Auto_neo \033[0;36m"
                                   << "           ***" << endl
         << "***                                  ***" << endl
         << "***  ------------------------------  ***" << endl
         << "***                                  ***" << endl
         << "***        "
                << "\033[1;33m Version: " << ms_ptr_XonfigLoader->GetVersion() << "\033[0;36m"
                                    << "          ***" << endl
         << "***                                  ***" << endl
         << "***  ------------------------------  ***" << endl
         << "***                                  ***" << endl
         << "***         "
                << "\033[0m 初始月度: " << ms_ptr_XonfigLoader->GetOriginMonth() << "\033[0;36m"
                                  << "            ***" << endl
         << "***         "
                << "\033[0m 当前月度: " << ms_ptr_XonfigLoader->GetCurrentMonth() << "\033[0;36m"
                                  << "            ***" << endl
         << "***                                  ***" << endl
         << "***  ------------------------------  ***" << endl
         << "***                                  ***" << endl
         << "***      "
                << "\033[0;34m>>>  番茄_summer  <<<\033[0;36m"
                                       << "       ***" << endl
         << "***                                  ***" << endl
         << "****************************************" << endl
         << "****************************************" << endl
         << "\033[0m";
}

void CCMDHandler::CMD_PrintRecode(CMD_Packet srt_CMD)
{
    string str_LineOperation_CMD[] = {X_CMD_TYPE_INSERT_LINE,
                                      X_CMD_TYPE_INSERT_BLANK_LINE,
                                      X_CMD_TYPE_MODIFY_LINE,
                                      X_CMD_TYPE_COPY_LINE,
                                      X_CMD_TYPE_MOVE_LINE,
                                      X_CMD_TYPE_DELETE_LINE};

    int int_LO_length = sizeof(str_LineOperation_CMD)/sizeof(str_LineOperation_CMD[0]);

    for(int i = 0; i < int_LO_length; i++)
    {
        if(str_LineOperation_CMD[i] == srt_CMD.m_str_CmdType)
            return;
    }

    if(X_CMD_TYPE_PRINT_SUM == srt_CMD.m_str_CmdType)
    {
        ms_str_FM_Type = "SUM";
        ms_str_FM_Key = "";
        ms_str_FM_Month = srt_CMD.m_str_ParamMonth;
        ms_bol_PR_Valid = true;
    }
    else if(X_CMD_TYPE_PRINT_MONTH == srt_CMD.m_str_CmdType)
    {
        ms_str_FM_Type = "MONTH";
        ms_str_FM_Key = "";
        ms_str_FM_Month = srt_CMD.m_str_ParamMonth;
        ms_bol_PR_Valid = true;
    }
    else if(X_CMD_TYPE_PRINT_SUBMONTH == srt_CMD.m_str_CmdType)
    {
        ms_str_FM_Type = "SM";
        ms_str_FM_Key = srt_CMD.m_str_ParamSubMonth;
        ms_str_FM_Month = srt_CMD.m_str_ParamMonth;
        ms_bol_PR_Valid = true;
    }
    else if(X_CMD_TYPE_PRINT_TITLE == srt_CMD.m_str_CmdType)
    {
        ms_str_FM_Type = "TT";
        ms_str_FM_Key = srt_CMD.m_str_ParamTitle;
        ms_str_FM_Month = srt_CMD.m_str_ParamMonth;
        ms_bol_PR_Valid = true;
    }
    else
    {
        ms_bol_PR_Valid = false;
    }
}

void CCMDHandler::CMD_PrintRecovery()
{
    if(ms_bol_PR_Valid == false)
        return;

    if(ms_str_FM_Type == "SUM")
    {
        ms_ptr_FAitfX->PrintSum(true);
    }
    else if(ms_str_FM_Type == "MONTH")
    {
        ms_ptr_FAitfX->PrintMonth(ms_str_FM_Month, true);
    }
    else if(ms_str_FM_Type == "SM")
    {
        ms_ptr_FAitfX->PrintSubMonth(ms_str_FM_Key, ms_str_FM_Month, true, true);
    }
    else if(ms_str_FM_Type == "TT")
    {
        ms_ptr_FAitfX->PrintTitle(ms_str_FM_Key, true);
    }
    else
        return;
}

void CCMDHandler::CMD_Help()
{
    cout << "****************************************" << endl;
    cout << "***          BEGIN OF HELP           ***" << endl;
    cout << "****************************************" << endl;

    for(int i=0; ;i++)
    {
        if("EndOfCmdMap" == CmdTypeEntries[i].str_CmdType)
        {
            break;
        }
        else
        {
            if("" != CmdTypeEntries[i].str_CmdHelp)
            {
                cout << "*** " <<CmdTypeEntries[i].str_CmdType << " ***" << endl;
                cout << ">>> " << CmdTypeEntries[i].str_CmdHelp << endl;

                if("" != CmdTypeEntries[i].str_CmdHelpPatch)
                    cout << ">>> " << CmdTypeEntries[i].str_CmdHelpPatch << endl;

                cout << endl;
            }

            continue;
        }
    }

    cout << "****************************************" << endl;
    cout << "***            END OF HELP           ***" << endl;
    cout << "****************************************" << endl;
}

void CCMDHandler::CMD_Help(const string str_HelpKey)
{
    cout << "****************************************" << endl;
    cout << "***          BEGIN OF HELP           ***" << endl;
    cout << "****************************************" << endl;

    for(int i=0; ;i++)
    {
        if("EndOfCmdMap" == CmdTypeEntries[i].str_CmdType)
        {
            break;
        }
        else
        {
            if("" != CmdTypeEntries[i].str_CmdHelp)
            {
                if( !CTool::ParseContainKey(CmdTypeEntries[i].str_CmdType, str_HelpKey) )
                    if( !CTool::ParseContainKey(CmdTypeEntries[i].str_CmdHelp, str_HelpKey) )
                        continue;

                cout << "*** " <<CmdTypeEntries[i].str_CmdType << " ***" << endl;
                cout << ">>> " << CmdTypeEntries[i].str_CmdHelp << endl;

                if("" != CmdTypeEntries[i].str_CmdHelpPatch)
                    cout << ">>> " << CmdTypeEntries[i].str_CmdHelpPatch << endl;

                cout << endl;
            }

            continue;
        }
    }

    cout << "****************************************" << endl;
    cout << "***            END OF HELP           ***" << endl;
    cout << "****************************************" << endl;
}

void CCMDHandler::OnCmdCheckFA(CMD_Packet srt_CMD)
{
	ms_ptr_ASitfX->CheckFA();
}

void CCMDHandler::OnCmdUpdateFA(CMD_Packet srt_CMD)
{
	ms_ptr_ASitfX->UpdateFA();
}

void CCMDHandler::OnCmdShowFA(CMD_Packet srt_CMD)
{
	ms_ptr_ASitfX->ShowFA();
}

void CCMDHandler::OnCmdCheckSum(CMD_Packet srt_CMD)
{
	ms_ptr_ASitfX->CheckSum(1);
}

void CCMDHandler::OnCmdUpdateSum(CMD_Packet srt_CMD)
{
	ms_ptr_ASitfX->UpdateSum(1);
}

void CCMDHandler::OnCmdShowSum(CMD_Packet srt_CMD)
{
	ms_ptr_ASitfX->ShowSum();
}

void CCMDHandler::OnCmdModifyLife(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->ModifyMonthSurplus(srt_CMD.m_str_ParamMonth, "生活费", srt_CMD.m_int_ParamValue);
    ms_ptr_FAitfX->SyncMonthSurplus(srt_CMD.m_str_ParamMonth);
    ms_ptr_ASitfX->UpdateSum(0);

    if( srt_CMD.m_str_ResParam == WEIXIN )
    {
        ms_ptr_FAitfX->TransferBalance("微信-零钱通", "阿里-余额宝", (-1)*srt_CMD.m_int_ParamValue);
    }
}

void CCMDHandler::OnCmdCheckMonth(CMD_Packet srt_CMD)
{
    if(srt_CMD.m_str_ResParam == TRAVERSAL)
    {
        ms_ptr_ASitfX->CheckMonthTraversal();
    }
    else
    {
        ms_ptr_ASitfX->CheckMonth(srt_CMD.m_str_ParamMonth, 1);
    }
}

void CCMDHandler::OnCmdUpdateMonth(CMD_Packet srt_CMD)
{
    if(srt_CMD.m_str_ResParam == TRAVERSAL)
    {
        ms_ptr_ASitfX->UpdateMonthTraversal();
        ms_ptr_ASitfX->UpdateSum(0);
    }
    else
    {
        ms_ptr_ASitfX->UpdateMonth(srt_CMD.m_str_ParamMonth, 1);
        ms_ptr_ASitfX->UpdateSum(0);
    }
}

void CCMDHandler::OnCmdShowMonth(CMD_Packet srt_CMD)
{
    ms_ptr_ASitfX->ShowMonth(srt_CMD.m_str_ParamMonth);
}

void CCMDHandler::OnCmdCheckExMonth(CMD_Packet srt_CMD)
{
    ms_ptr_ASitfX->CheckMonth(ms_ptr_XonfigLoader->GetPreviousMonth(), 1);
}

void CCMDHandler::OnCmdUpdateExMonth(CMD_Packet srt_CMD)
{
    ms_ptr_ASitfX->UpdateMonth(ms_ptr_XonfigLoader->GetPreviousMonth(), 1);
    ms_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdShowExMonth(CMD_Packet srt_CMD)
{
    ms_ptr_ASitfX->ShowMonth(ms_ptr_XonfigLoader->GetPreviousMonth());
}

void CCMDHandler::OnCmdCheckSubMonth(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->CheckSubMonthExpense(srt_CMD.m_str_ParamSubMonth, srt_CMD.m_str_ParamMonth, true);
}

void CCMDHandler::OnCmdUpdateSubMonth(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->UpdateSubMonthExpense(srt_CMD.m_str_ParamSubMonth, srt_CMD.m_str_ParamMonth, true);

    ms_ptr_FAitfX->UpdateMonthSurplus(srt_CMD.m_str_ParamMonth, false);
    ms_ptr_FAitfX->SyncMonthSurplus(srt_CMD.m_str_ParamMonth);
    ms_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdShowSubMonth(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamSubMonth == ALL )
    {
        ms_ptr_ASitfX->ShowAllSubMonth(srt_CMD.m_str_ParamMonth);
    }
    else
    {
        ms_ptr_FAitfX->ShowSubMonth(srt_CMD.m_str_ParamSubMonth, srt_CMD.m_str_ParamMonth, 4);
    }
}

void CCMDHandler::OnCmdCheckTitle(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->CheckTitleExpense(srt_CMD.m_str_ParamTitle, true);
    ms_ptr_FAitfX->CheckSubTitleExpense(srt_CMD.m_str_ParamTitle, true);
}

void CCMDHandler::OnCmdUpdateTitle(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->UpdateTitleExpense(srt_CMD.m_str_ParamTitle, true);
    ms_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdShowTitle(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ResParam == TAG )
        ms_ptr_FAitfX->ShowTitle(srt_CMD.m_str_ParamTitle, 2);
    else
        ms_ptr_FAitfX->ShowTitle(srt_CMD.m_str_ParamTitle, 1);
}

void CCMDHandler::OnCmdTransfer(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ResParam == WEIXIN )
    {
        ms_ptr_FAitfX->TransferBalance("微信-零钱通", "阿里-余额宝", srt_CMD.m_int_ParamValue);
    }
    else if( srt_CMD.m_str_ResParam == JINGDONG )
    {
        ms_ptr_FAitfX->TransferBalance("京东-小金库", "阿里-余额宝", srt_CMD.m_int_ParamValue);
    }
    else if( srt_CMD.m_str_ResParam.empty() )
    {
        ms_ptr_FAitfX->TransferBalance("微信-零钱通", "阿里-余额宝", srt_CMD.m_int_ParamValue);
    }
    else
    {
        CTool::MassageOutFotmat("SRC Error", '!');
    }
}

void CCMDHandler::OnCmdAnalysisTrend(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ResParam == EXPENSE )
    {
        ms_ptr_ASitfX->AnalysisMonthTrend_EXP();
    }
    else if( srt_CMD.m_str_ResParam == MODIFY_LIFE )
    {
        ms_ptr_ASitfX->AnalysisMonthTrend_LIFE();
    }
    else if( srt_CMD.m_str_ResParam == ROOM )
    {
        ms_ptr_ASitfX->AnalysisMonthTrend_ROOM();
    }
    else if( srt_CMD.m_str_ResParam == CONSUMPTION )
    {
        ms_ptr_ASitfX->AnalysisMonthTrend_CSM();
    }
    else
    {
        ms_ptr_ASitfX->AnalysisMonthTrend(srt_CMD.m_str_ResParam);
    }
}

void CCMDHandler::OnCmdAnalysisProportion(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->AnalysisMonthProportion(srt_CMD.m_str_ParamMonth);
}

void CCMDHandler::OnCmdCompareMonth(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->CompareMonth(srt_CMD.m_str_ParamMonth, srt_CMD.m_str_ResParam);
}

void CCMDHandler::OnCmdSummarize(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ResParam == MONTH )
    {
        ms_ptr_FAitfX->SummarizeMonthCLS(2);
    }
    else if( srt_CMD.m_str_ResParam == TITLE )
    {
        ms_ptr_FAitfX->SummarizeTitle(2);
    }
    else if( srt_CMD.m_str_ResParam == TAIL )
    {
        ms_ptr_FAitfX->SummarizeTail(2);
    }
    else
    {
        CTool::MassageOutFotmat("Invalid Summarize Param", '!');
    }
}

void CCMDHandler::OnCmdForecast(CMD_Packet srt_CMD)
{
	ms_ptr_FAitfX->ForecastFutureSum(srt_CMD.m_str_ResParam.c_str(), srt_CMD.m_int_ResParam);
}

void CCMDHandler::OnCmdPrintSum(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->PrintSum(true);
}

void CCMDHandler::OnCmdPrintMonth(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->PrintMonth(srt_CMD.m_str_ParamMonth, true);
}

void CCMDHandler::OnCmdPrintSubMonth(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamSubMonth == ALL )
    {
        if(srt_CMD.m_str_ResParam == TRAVERSAL)
        {
            CTool::MassageOutFotmat("Error SM-Param Combo", '!');
            return;
        }
        else
            ms_ptr_ASitfX->PrintAllSubMonth(srt_CMD.m_str_ParamMonth, false);
    }
    else
    {
        if(srt_CMD.m_str_ResParam == TRAVERSAL)
        {
            ms_ptr_ASitfX->PrintSubMonthTraversal(srt_CMD.m_str_ParamSubMonth, true);
        }
        else
        {
            ms_ptr_FAitfX->PrintSubMonth(srt_CMD.m_str_ParamSubMonth, srt_CMD.m_str_ParamMonth, true, true);
        }
    }
}

void CCMDHandler::OnCmdPrintTitle(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->PrintTitle(srt_CMD.m_str_ParamTitle, true);
}

void CCMDHandler::OnCmdInsertLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        ms_ptr_FAitfX->InsertLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine,\
                                    srt_CMD.m_int_ResParam, srt_CMD.m_str_ResParam);
    }
    else
        CTool::MassageOutFotmat("Print File Missing", '!');

    CMD_PrintRecovery();
}

void CCMDHandler::OnCmdInsertBlankLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        ms_ptr_FAitfX->InsertBlankLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine);
    }
    else
        CTool::MassageOutFotmat("Print File Missing", '!');

    CMD_PrintRecovery();
}

void CCMDHandler::OnCmdModifyLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        if((srt_CMD.m_int_ResParam == 0) && (srt_CMD.m_str_ResParam == ""))
        {
            CTool::MassageOutFotmat("Modify Param Invalid", '!');
            return;
        }
        else if(srt_CMD.m_str_ResParam == "")
        {
            ms_ptr_FAitfX->ModifyLineValue(ms_str_FM_Type, ms_str_FM_Key,
                                           srt_CMD.m_int_ParamLine, srt_CMD.m_int_ResParam);
        }
        else if(srt_CMD.m_int_ResParam == 0)
        {
            ms_ptr_FAitfX->ModifyLineContent(ms_str_FM_Type, ms_str_FM_Key,
                                             srt_CMD.m_int_ParamLine, srt_CMD.m_str_ResParam);
        }
        else
        {
            ms_ptr_FAitfX->ModifyLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine,\
                                      srt_CMD.m_int_ResParam, srt_CMD.m_str_ResParam);
        }
    }
    else
    {
        CTool::MassageOutFotmat("Print File Missing", '!');
        return;
    }

    CMD_PrintRecovery();
}

void CCMDHandler::OnCmdCopyLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        ms_ptr_FAitfX->CopyLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine,\
                                srt_CMD.m_int_ResParam);
    }
    else
        CTool::MassageOutFotmat("Print File Missing", '!');

    CMD_PrintRecovery();
}

void CCMDHandler::OnCmdMoveLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        ms_ptr_FAitfX->MoveLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine,\
                                srt_CMD.m_int_ResParam);
    }
    else
        CTool::MassageOutFotmat("Print File Missing", '!');

    CMD_PrintRecovery();
}

void CCMDHandler::OnCmdDeleteLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        ms_ptr_FAitfX->DeleteLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine);
    }
    else
        CTool::MassageOutFotmat("Print File Missing", '!');

    CMD_PrintRecovery();
}

void CCMDHandler::OnCmdAppendMonth(CMD_Packet srt_CMD)
{
    //ms_ptr_ASitfX->AppendNextMonth(srt_CMD.m_str_ResParam);
    ms_ptr_ASitfX->AppendNextMonth(srt_CMD.m_str_ParamMonth);
}

void CCMDHandler::OnCmdCheckFile(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->CheckEqualAllFile();

    vector<string> vec_str_BakupPath;
    ms_ptr_XonfigLoader->BakupPathDuplicator(vec_str_BakupPath);

    vector<string>::iterator itr_BakupPath;
    for(itr_BakupPath = vec_str_BakupPath.begin(); itr_BakupPath != vec_str_BakupPath.end(); itr_BakupPath++)
    {
        ms_ptr_FAitfX->CheckEqualAllFile(*itr_BakupPath);
    }
}

void CCMDHandler::OnCmdCheckTime(CMD_Packet srt_CMD)
{
    ms_ptr_FAitfX->CheckTimeStamp();
}

void CCMDHandler::OnCmdSync(CMD_Packet srt_CMD)
{
	ms_ptr_FAitfX->SyncAllFile();
}

void CCMDHandler::OnCmdWrite(CMD_Packet srt_CMD)
{
	ms_ptr_FAitfX->WriteAllFile();
    ms_ptr_FAitfX->CheckEqualAllFile();
}

void CCMDHandler::OnCmdBackup(CMD_Packet srt_CMD)
{
    vector<string> vec_str_BakupPath;
    ms_ptr_XonfigLoader->BakupPathDuplicator(vec_str_BakupPath);

    vector<string>::iterator itr_BakupPath;
    for(itr_BakupPath = vec_str_BakupPath.begin(); itr_BakupPath != vec_str_BakupPath.end(); itr_BakupPath++)
    {        
        ms_ptr_FAitfX->BackUpAllFile(*itr_BakupPath);
        ms_ptr_FAitfX->CheckEqualAllFile(*itr_BakupPath);
    }
}

void CCMDHandler::OnCmdHelp(CMD_Packet srt_CMD)
{
    if("" == srt_CMD.m_str_ResParam)
        CCMDHandler::CMD_Help();
    else
        CCMDHandler::CMD_Help(srt_CMD.m_str_ResParam);
}

void CCMDHandler::OnCmdTest(CMD_Packet srt_CMD)
{
    cout << "****************************************" << endl;
    cout << "***          BEGIN OF TEST           ***" << endl;
    cout << "****************************************" << endl;

    printf("\033[0;30m black \033[0m");
    printf("\033[0;31m red \033[0m");
    printf("\033[0;32m green \033[0m");
    printf("\033[0;33m yellow \033[0m");
    printf("\033[0;34m blue \033[0m");
    printf("\033[0;35m magenta \033[0m");
    printf("\033[0;36m cyan \033[0m");
    printf("\033[0;37m white \n\033[0m");

    printf("\033[1;30m black \033[0m");
    printf("\033[1;31m red \033[0m");
    printf("\033[1;32m green \033[0m");
    printf("\033[1;33m yellow \033[0m");
    printf("\033[1;34m blue \033[0m");
    printf("\033[1;35m magenta \033[0m");
    printf("\033[1;36m cyan \033[0m");
    printf("\033[1;37m white \n\033[0m");

    cout << endl;
    ms_ptr_FAitfX->CheckSubTitleExpense("dk", true);

    cout << "****************************************" << endl;
    cout << "***           END OF TEST            ***" << endl;
    cout << "****************************************" << endl;
}

void CCMDHandler::OnCmdTestt(CMD_Packet srt_CMD)
{
    cout << "****************************************" << endl;
    cout << "***          BEGIN OF TESTT          ***" << endl;
    cout << "****************************************" << endl;

    string emptyString = "";
    //int FileCount = xonfig.Read("FileCount", 0);
    //string File_1 = xonfig.Read("File_1", emptyString);
    //string File_2 = xonfig.Read("File_2", emptyString);
    //string File_3 = xonfig.Read("File_3", emptyString);
    
    //cout << FileCount << endl;
    //cout << File_1 << endl;
    //cout << File_2 << endl;
    //cout << File_3 << endl;

    cout << "****************************************" << endl;
    cout << "***           END OF TESTT           ***" << endl;
    cout << "****************************************" << endl;
}

void CCMDHandler::OnCmdTesttt(CMD_Packet srt_CMD)
{
    cout << "****************************************" << endl;
    cout << "***         BEGIN OF TESTTT          ***" << endl;
    cout << "****************************************" << endl;

    //xonfig.Modify("FileCount", 12345);
    //ofstream out( "FA_Auto_neo.ini" );
    //out << xonfig;

    cout << "****************************************" << endl;
    cout << "***          END OF TESTTT           ***" << endl;
    cout << "****************************************" << endl;
}

void CCMDHandler::OnCmdCancel(CMD_Packet srt_CMD)
{
	cout << "----------------------------------------" << endl;
    cout << "###           CMD canceled           ###" << endl;
    cout << "----------------------------------------" << endl;
}

void CCMDHandler::OnCmdExit(CMD_Packet srt_CMD)
{
	cout << endl;
    cout << "****************************************" << endl;
    cout << "***          FA_Auto X Pro           ***" << endl;
    cout << "***              EXIT                ***" << endl;
    cout << "****************************************" << endl;
    cout << endl;
}

//------------------------------//
//   River flows in summer
//------------------------------//
