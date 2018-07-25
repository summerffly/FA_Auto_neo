
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Handler.h"

#include "./DefCMDHelp.h"
#include "./../X_Frame/DefLib.h"
#include "./../X_Frame/X_Tool.h"


CScriptRipper* CCMDHandler::ms_ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
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

	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_MONTH, "", "", OnCmdCheckMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_MONTH, "", "", OnCmdUpdateMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_MONTH, "", "", OnCmdShowMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_SUBMONTH, "", "", OnCmdCheckSubMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_SUBMONTH, "", "", OnCmdUpdateSubMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_TITLE, "", "", OnCmdCheckTitle)

    X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_TITLE, "", "", OnCmdUpdateTitle)

    X_ON_CMD_TYPE(X_CMD_TYPE_TRANSFER, "", "", OnCmdTransfer)

    X_ON_CMD_TYPE(X_CMD_TYPE_LOTTERY, "", "", OnCmdLottery)

    X_ON_CMD_TYPE(X_CMD_TYPE_ANALYSIS_TREND, CMD_HELP_ANALYSIS_TREND, \
        CMD_HELP_PATCH_ANALYSIS_TREND, OnCmdAnalysisTrend)

    X_ON_CMD_TYPE(X_CMD_TYPE_ANALYSIS_PROPORTION, "", "", OnCmdAnalysisProportion)

    X_ON_CMD_TYPE(X_CMD_TYPE_SUMMARIZE, "", "", OnCmdSummarize)

	X_ON_CMD_TYPE(X_CMD_TYPE_FORECAST, "", "", OnCmdForecast)

    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_SUM, "", "", OnCmdPrintSum)

    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_MONTH, CMD_HELP_PRINT_MONTH, "", OnCmdPrintMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_SUBMONTH, CMD_HELP_PRINT_SUBMONTH, CMD_HELP_PATCH_PRINT_SUBMONTH, OnCmdPrintSubMonth)

    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_TITLE, CMD_HELP_PRINT_TITLE, CMD_HELP_PATCH_PRINT_TITLE, OnCmdPrintTitle)

    X_ON_CMD_TYPE(X_CMD_TYPE_INSERT_BLANK_LINE, "", "", OnCmdInsertBlankLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_INSERT_LINE, CMD_HELP_INSERT_LINE, "", OnCmdInsertLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_MODIFY_LINE, CMD_HELP_MODIFY_LINE, "", OnCmdModifyLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_DELETE_LINE, CMD_HELP_DELETE_LINE, "", OnCmdDeleteLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_MOVE_LINE, CMD_HELP_MOVE_LINE, "", OnCmdMoveLine)

    X_ON_CMD_TYPE(X_CMD_TYPE_APPEND_MONTH, CMD_HELP_APPEND_MONTH, "", OnCmdAppendMonth)

	X_ON_CMD_TYPE(X_CMD_TYPE_SYNC, "", "", OnCmdSync)

	X_ON_CMD_TYPE(X_CMD_TYPE_WRITE, "", "", OnCmdWrite)

	X_ON_CMD_TYPE(X_CMD_TYPE_BACKUP, "", "", OnCmdBackup)

    X_ON_CMD_TYPE(X_CMD_TYPE_HELP, "", "", OnCmdHelp)

    X_ON_CMD_TYPE(X_CMD_TYPE_TEST, "", "", OnCmdTest)

	X_ON_CMD_TYPE(X_CMD_TYPE_CANCEL, "", "", OnCmdCancel)

	X_ON_CMD_TYPE(X_CMD_TYPE_EXIT, "", "", OnCmdExit)
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
        cout << "CMD >>> ";
        cin.getline(CMD_linebuffer, MAX_COMMAND);

        CMD_Packet xCmdPacket = CMD_Packet();

        if(-1 == xCmdPacket.CMDRipper(CMD_linebuffer))
        {
            CTool::MassageOutFotmat("Blank CMD", '!');
            continue;
        }

        if(0 != xCmdPacket.CMDFilter())
        {
            CTool::MassageOutFotmat("Error-Format CMD", '!');
            continue;
        }

        int int_RetParser = xCmdPacket.CMDParser();
        if(-1 == int_RetParser)
        {
            CTool::MassageOutFotmat("Error-Format CMD Param", '!');
            continue;
        }
        else if(-2 == int_RetParser)
        {
            CTool::MassageOutFotmat("Conflict CMD Param", '!');
            continue;
        }
        else if(-3 == int_RetParser)
        {
            CTool::MassageOutFotmat("Invalid Month Param", '!');
            continue;
        }
        else if(-4 == int_RetParser)
        {
            // 未定义CMDType
        }

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
            break;
        else
        {
            CTool::MassageOutFotmat("Error CMD", '!');
            continue;
        }
    }
}

void CCMDHandler::CMD_Init()
{
    ms_ptr_FAitfX->LoadSum(0);
    ms_ptr_FAitfX->SummarizeMonth(0);
    ms_ptr_FAitfX->SummarizeTitle(0);
    ms_ptr_FAitfX->SummarizeTail(0);
    ms_ptr_FAitfX->SummarizeCAF(0);

    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          FA_Auto X Pro           ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***         Version: " << ms_ptr_ScriptRipper->GetVersion() << "          ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          初始月度: " << ms_ptr_ScriptRipper->GetOriginMonth() << "            ***" << endl;
    cout << "***          当前月度: " << ms_ptr_ScriptRipper->GetCurrentMonth() << "            ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***      >>>  番茄_summer  <<<       ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
}

void CCMDHandler::CMD_PrintRecode(CMD_Packet srt_CMD)
{
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
    else if(X_CMD_TYPE_INSERT_BLANK_LINE == srt_CMD.m_str_CmdType)
    {
        return;
    }
    else if(X_CMD_TYPE_INSERT_LINE == srt_CMD.m_str_CmdType)
    {
        return;
    }
    else if(X_CMD_TYPE_MODIFY_LINE == srt_CMD.m_str_CmdType)
    {
        return;
    }
    else if(X_CMD_TYPE_DELETE_LINE == srt_CMD.m_str_CmdType)
    {
        return;
    }
    else if(X_CMD_TYPE_MOVE_LINE == srt_CMD.m_str_CmdType)
    {
        return;
    }
    else if(X_CMD_TYPE_TEST == srt_CMD.m_str_CmdType)
    {
        return;
    }
    else
    {
        ms_bol_PR_Valid = false;
    }
}

void CCMDHandler::CMD_PrintRecovery()
{
    //
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
        ms_ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, srt_CMD.m_int_ParamValue);
    }
}

void CCMDHandler::OnCmdCheckMonth(CMD_Packet srt_CMD)
{
    ms_ptr_ASitfX->CheckMonth(srt_CMD.m_str_ParamMonth, 1);
}

void CCMDHandler::OnCmdUpdateMonth(CMD_Packet srt_CMD)
{
    ms_ptr_ASitfX->UpdateMonth(srt_CMD.m_str_ParamMonth, 1);
    ms_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdShowMonth(CMD_Packet srt_CMD)
{
    ms_ptr_ASitfX->ShowMonth(srt_CMD.m_str_ParamMonth);
}

void CCMDHandler::OnCmdCheckSubMonth(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamSubMonth == DGTLER )
    {
        ms_ptr_FAitfX->CheckSubMonthExpense("DGtler", srt_CMD.m_str_ParamMonth, true);
    }
	else if( srt_CMD.m_str_ParamSubMonth == BOOKS )
    {
        ms_ptr_FAitfX->CheckSubMonthExpense("Books", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == KEEP )
    {
        ms_ptr_FAitfX->CheckSubMonthExpense("KEEP", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == TB )
    {
        ms_ptr_FAitfX->CheckSubMonthExpense("TB", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == SA )
    {
        ms_ptr_FAitfX->CheckSubMonthExpense("sa", srt_CMD.m_str_ParamMonth, true);
    }
    else
    {
        CTool::MassageOutFotmat("Error SM Param", '!');
    }
}

void CCMDHandler::OnCmdUpdateSubMonth(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamSubMonth == DGTLER )
    {
        ms_ptr_FAitfX->UpdateSubMonthExpense("DGtler", srt_CMD.m_str_ParamMonth, true);
    }
	else if( srt_CMD.m_str_ParamSubMonth == BOOKS )
    {
        ms_ptr_FAitfX->UpdateSubMonthExpense("Books", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == KEEP )
    {
        ms_ptr_FAitfX->UpdateSubMonthExpense("KEEP", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == TB )
    {
        ms_ptr_FAitfX->UpdateSubMonthExpense("TB", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == SA )
    {
        ms_ptr_FAitfX->UpdateSubMonthExpense("sa", srt_CMD.m_str_ParamMonth, true);
    }
    else
    {
        CTool::MassageOutFotmat("Error SM Param", '!');
    }

    ms_ptr_FAitfX->UpdateMonthSurplus(srt_CMD.m_str_ParamMonth, false);
    ms_ptr_FAitfX->SyncMonthSurplus(srt_CMD.m_str_ParamMonth);
    ms_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdCheckTitle(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamTitle == DK )
    {
        ms_ptr_FAitfX->CheckTitleExpense("DK", true);
    }
    else if( srt_CMD.m_str_ParamTitle == NS )
    {
        ms_ptr_FAitfX->CheckTitleExpense("NS", true);
    }
    else if( srt_CMD.m_str_ParamTitle == TRAVEL )
    {
        ms_ptr_FAitfX->CheckTitleExpense("travel", true);
    }
    else if( srt_CMD.m_str_ParamTitle == LOTTERY )
    {
        ms_ptr_FAitfX->CheckTitleExpense("lottery", true);
    }
    else
    {
        CTool::MassageOutFotmat("Error TT Param", '!');
    }
}

void CCMDHandler::OnCmdUpdateTitle(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamTitle == DK )
    {
        ms_ptr_FAitfX->UpdateTitleExpense("DK", true);
    }
    else if( srt_CMD.m_str_ParamTitle == NS )
    {
        ms_ptr_FAitfX->UpdateTitleExpense("NS", true);
    }
    else if( srt_CMD.m_str_ParamTitle == TRAVEL )
    {
        ms_ptr_FAitfX->UpdateTitleExpense("travel", true);
    }
    else if( srt_CMD.m_str_ParamTitle == LOTTERY )
    {
        ms_ptr_FAitfX->UpdateTitleExpense("lottery", true);
    }
    else
    {
        CTool::MassageOutFotmat("Error TT Param", '!');

        return;
    }

    ms_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdTransfer(CMD_Packet srt_CMD)
{
    if(srt_CMD.m_int_ParamValue > 0)
    {
        ms_ptr_FAitfX->TransferBalance("零钱通", "余额宝", true, srt_CMD.m_int_ParamValue);
    }
    else
    {
        ms_ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, (-1)*srt_CMD.m_int_ParamValue);
    }
}

void CCMDHandler::OnCmdLottery(CMD_Packet srt_CMD)
{
    if(srt_CMD.m_int_ParamValue > 0)
    {
        ms_ptr_FAitfX->TransferBalance("零钱通", "余额宝", true, srt_CMD.m_int_ParamValue);
        ms_ptr_FAitfX->AppendLottery(true, srt_CMD.m_int_ParamValue, srt_CMD.m_str_ParamDate);
    }
    else
    {
        ms_ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, (-1)*srt_CMD.m_int_ParamValue);
        ms_ptr_FAitfX->AppendLottery(false, (-1)*srt_CMD.m_int_ParamValue, srt_CMD.m_str_ParamDate);
    }
    ms_ptr_ASitfX->UpdateSum(0);
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

void CCMDHandler::OnCmdSummarize(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ResParam == MONTH )
    {
        ms_ptr_FAitfX->SummarizeMonth(2);
    }
    else if( srt_CMD.m_str_ResParam == TITLE )
    {
        ms_ptr_FAitfX->SummarizeTitle(1);
    }
    else if( srt_CMD.m_str_ResParam == TAIL )
    {
        ms_ptr_FAitfX->SummarizeTail(1);
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
        ms_ptr_ASitfX->PrintSubMonthTraversal(srt_CMD.m_str_ParamMonth, false);
    }
    else if( srt_CMD.m_str_ParamSubMonth == DGTLER )
    {
        ms_ptr_FAitfX->PrintSubMonth("DGtler", srt_CMD.m_str_ParamMonth, true, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == BOOKS )
    {
        ms_ptr_FAitfX->PrintSubMonth("Books", srt_CMD.m_str_ParamMonth, true, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == KEEP )
    {
        ms_ptr_FAitfX->PrintSubMonth("KEEP", srt_CMD.m_str_ParamMonth, true, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == TB )
    {
        ms_ptr_FAitfX->PrintSubMonth("TB", srt_CMD.m_str_ParamMonth, true, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == SA )
    {
        ms_ptr_FAitfX->PrintSubMonth("sa", srt_CMD.m_str_ParamMonth, true, true);
    }
    else
    {
        CTool::MassageOutFotmat("Error SM Param", '!');
    }
}

void CCMDHandler::OnCmdPrintTitle(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamTitle == DK )
    {
        ms_ptr_FAitfX->PrintTitle("DK", true);
    }
    else if( srt_CMD.m_str_ParamTitle == NS )
    {
        ms_ptr_FAitfX->PrintTitle("NS", true);
    }
    else if( srt_CMD.m_str_ParamTitle == TRAVEL )
    {
        ms_ptr_FAitfX->PrintTitle("travel", true);
    }
    else if( srt_CMD.m_str_ParamTitle == LOTTERY )
    {
        ms_ptr_FAitfX->PrintTitle("lottery", true);
    }
    else
    {
        CTool::MassageOutFotmat("Error TT Param", '!');
    }
}

void CCMDHandler::OnCmdInsertBlankLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        ms_ptr_FAitfX->InsertLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine,\
                                    srt_CMD.m_int_ResParam, srt_CMD.m_str_ResParam);
    }
    else
        CTool::MassageOutFotmat("Print File Missing", '!');
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
}

void CCMDHandler::OnCmdModifyLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        ms_ptr_FAitfX->ModifyLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine,\
                                    srt_CMD.m_int_ResParam, srt_CMD.m_str_ResParam);
    }
    else
        CTool::MassageOutFotmat("Print File Missing", '!');
}

void CCMDHandler::OnCmdDeleteLine(CMD_Packet srt_CMD)
{
    if(ms_bol_PR_Valid)
    {
        ms_ptr_FAitfX->DeleteLine(ms_str_FM_Type, ms_str_FM_Key, srt_CMD.m_int_ParamLine);
    }
    else
        CTool::MassageOutFotmat("Print File Missing", '!');
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
}

void CCMDHandler::OnCmdAppendMonth(CMD_Packet srt_CMD)
{
    ms_ptr_ASitfX->AppendNextMonth(srt_CMD.m_str_ResParam);
}

void CCMDHandler::OnCmdSync(CMD_Packet srt_CMD)
{
	ms_ptr_FAitfX->SyncAllFile();
}

void CCMDHandler::OnCmdWrite(CMD_Packet srt_CMD)
{
	ms_ptr_FAitfX->WriteAllFile();
}

void CCMDHandler::OnCmdBackup(CMD_Packet srt_CMD)
{
	ms_ptr_FAitfX->BackUpAllFile("./FA_SZ.bak/");
    ms_ptr_FAitfX->BackUpAllFile("./../Hacker/FA_Auto_X/X_Executable/");
}

void CCMDHandler::OnCmdHelp(CMD_Packet srt_CMD)
{
    CCMDHandler::CMD_Help();
}

void CCMDHandler::OnCmdTest(CMD_Packet srt_CMD)
{
    cout << "****************************************" << endl;
    cout << "***          BEGIN OF TEST           ***" << endl;
    cout << "****************************************" << endl;

    cout << ms_str_FM_Type << endl;
    cout << ms_str_FM_Key << endl;

    if(ms_bol_PR_Valid)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    cout << "****************************************" << endl;
    cout << "***           END OF TEST            ***" << endl;
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
