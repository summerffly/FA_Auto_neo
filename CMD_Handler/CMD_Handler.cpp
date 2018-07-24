
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Handler.h"

#include "./DefCMDHelp.h"
#include "./../X_Frame/DefLib.h"
#include "./../X_Frame/X_Tool.h"


CScriptRipper* CCMDHandler::m_ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
CFAitfX* CCMDHandler::m_ptr_FAitfX = Singleton<CFAitfX>::GetInstance();
CASitfX* CCMDHandler::m_ptr_ASitfX = Singleton<CASitfX>::GetInstance();

/**************************************************/
//   CMD_MAP()宏
/**************************************************/
X_BEGIN_CMD_MAP(CCMDHandler)
	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_FA, HELP_CMD_TYPE_CHECK_FA, "", OnCmdCheckFA)
	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_FA, HELP_CMD_TYPE_UPDATE_FA, "", OnCmdUpdateFA)
	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_FA, HELP_CMD_TYPE_SHOW_FA, "", OnCmdShowFA)
	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_SUM, HELP_CMD_TYPE_CHECK_SUM, "", OnCmdCheckSum)
	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_SUM, HELP_CMD_TYPE_UPDATE_SUM, "", OnCmdUpdateSum)
	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_SUM, HELP_CMD_TYPE_SHOW_SUM, "", OnCmdShowSum)
    X_ON_CMD_TYPE(X_CMD_TYPE_MODIFY_LIFE, HELP_CMD_TYPE_MODIFY_LIFE, "", OnCmdModifyLife)
	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_MONTH, "", "", OnCmdCheckMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_MONTH, "", "", OnCmdUpdateMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_MONTH, "", "", OnCmdShowMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_SUBMONTH, "", "", OnCmdCheckSubMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_SUBMONTH, "", "", OnCmdUpdateSubMonth)
    X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_TITLE, "", "", OnCmdCheckTitle)
    X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_TITLE, "", "", OnCmdUpdateTitle)
    X_ON_CMD_TYPE(X_CMD_TYPE_TRANSFER, "", "", OnCmdTransfer)
    X_ON_CMD_TYPE(X_CMD_TYPE_LOTTERY, "", "", OnCmdLottery)
    X_ON_CMD_TYPE(X_CMD_TYPE_ANALYSIS_TREND, "", "", OnCmdAnalysisTrend)
    X_ON_CMD_TYPE(X_CMD_TYPE_ANALYSIS_PROPORTION, "", "", OnCmdAnalysisProportion)
    X_ON_CMD_TYPE(X_CMD_TYPE_SUMMARIZE, "", "", OnCmdSummarize)
	X_ON_CMD_TYPE(X_CMD_TYPE_FORECAST, "", "", OnCmdForecast)
    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_MONTH, HELP_CMD_TYPE_PRINT_MONTH, "", OnCmdPrintMonth)
    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_SUBMONTH, HELP_CMD_TYPE_PRINT_SUBMONTH, "", OnCmdPrintSubMonth)
    X_ON_CMD_TYPE(X_CMD_TYPE_PRINT_TITLE, HELP_CMD_TYPE_PRINT_TITLE, "", OnCmdPrintTitle)
    X_ON_CMD_TYPE(X_CMD_TYPE_APPEND_MONTH, HELP_CMD_TYPE_APPEND_MONTH, "", OnCmdAppendMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_SYNC, "", "", OnCmdSync)
	X_ON_CMD_TYPE(X_CMD_TYPE_WRITE, "", "", OnCmdWrite)
	X_ON_CMD_TYPE(X_CMD_TYPE_BACKUP, "", "", OnCmdBackup)
    X_ON_CMD_TYPE(X_CMD_TYPE_TEST, "", "", OnCmdTest)
	X_ON_CMD_TYPE(X_CMD_TYPE_CANCEL, "", "", OnCmdCancel)
	X_ON_CMD_TYPE(X_CMD_TYPE_EXIT, "", "", OnCmdExit)
    X_ON_CMD_TYPE(X_CMD_TYPE_HELP, "", "", CMD_Help)
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
    m_ptr_FAitfX->LoadSum(0);
    m_ptr_FAitfX->SummarizeMonth(0);
    m_ptr_FAitfX->SummarizeTitle(0);
    m_ptr_FAitfX->SummarizeTail(0);
    m_ptr_FAitfX->SummarizeCAF(0);

    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          FA_Auto X Pro           ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***         Version: " << m_ptr_ScriptRipper->GetVersion() << "          ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          初始月度: " << m_ptr_ScriptRipper->GetOriginMonth() << "            ***" << endl;
    cout << "***          当前月度: " << m_ptr_ScriptRipper->GetCurrentMonth() << "            ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***      >>>  番茄_summer  <<<       ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
}

void CCMDHandler::CMD_Help(CMD_Packet srt_CMD)
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
            if("" != CmdTypeEntries[i].str_CmdHelpExample)
            {
                cout << "*** " <<CmdTypeEntries[i].str_CmdType << " ***" << endl;
                cout << ">>> " << CmdTypeEntries[i].str_CmdHelpExample << endl;
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
	m_ptr_ASitfX->CheckFA();
}

void CCMDHandler::OnCmdUpdateFA(CMD_Packet srt_CMD)
{
	m_ptr_ASitfX->UpdateFA();
}

void CCMDHandler::OnCmdShowFA(CMD_Packet srt_CMD)
{
	m_ptr_ASitfX->ShowFA();
}

void CCMDHandler::OnCmdCheckSum(CMD_Packet srt_CMD)
{
	m_ptr_ASitfX->CheckSum(1);
}

void CCMDHandler::OnCmdUpdateSum(CMD_Packet srt_CMD)
{
	m_ptr_ASitfX->UpdateSum(1);
}

void CCMDHandler::OnCmdShowSum(CMD_Packet srt_CMD)
{
	m_ptr_ASitfX->ShowSum();
}

void CCMDHandler::OnCmdModifyLife(CMD_Packet srt_CMD)
{
    m_ptr_FAitfX->ModifyMonthSurplus(srt_CMD.m_str_ParamMonth, "生活费", srt_CMD.m_int_ParamValue);
    m_ptr_FAitfX->SyncMonthSurplus(srt_CMD.m_str_ParamMonth);
    m_ptr_ASitfX->UpdateSum(0);

    if( srt_CMD.m_str_ResParam == WEIXIN )
    {
        m_ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, srt_CMD.m_int_ParamValue);
    }
}

void CCMDHandler::OnCmdCheckMonth(CMD_Packet srt_CMD)
{
    m_ptr_ASitfX->CheckMonth(srt_CMD.m_str_ParamMonth, 1);
}

void CCMDHandler::OnCmdUpdateMonth(CMD_Packet srt_CMD)
{
    m_ptr_ASitfX->UpdateMonth(srt_CMD.m_str_ParamMonth, 1);
    m_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdShowMonth(CMD_Packet srt_CMD)
{
    m_ptr_ASitfX->ShowMonth(srt_CMD.m_str_ParamMonth);
}

void CCMDHandler::OnCmdCheckSubMonth(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamSubMonth == DGTLER )
    {
        m_ptr_FAitfX->CheckSubMonthExpense("DGtler", srt_CMD.m_str_ParamMonth, true);
    }
	else if( srt_CMD.m_str_ParamSubMonth == BOOKS )
    {
        m_ptr_FAitfX->CheckSubMonthExpense("Books", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == KEEP )
    {
        m_ptr_FAitfX->CheckSubMonthExpense("KEEP", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == TB )
    {
        m_ptr_FAitfX->CheckSubMonthExpense("TB", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == SA )
    {
        m_ptr_FAitfX->CheckSubMonthExpense("sa", srt_CMD.m_str_ParamMonth, true);
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
        m_ptr_FAitfX->UpdateSubMonthExpense("DGtler", srt_CMD.m_str_ParamMonth, true);
    }
	else if( srt_CMD.m_str_ParamSubMonth == BOOKS )
    {
        m_ptr_FAitfX->UpdateSubMonthExpense("Books", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == KEEP )
    {
        m_ptr_FAitfX->UpdateSubMonthExpense("KEEP", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == TB )
    {
        m_ptr_FAitfX->UpdateSubMonthExpense("TB", srt_CMD.m_str_ParamMonth, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == SA )
    {
        m_ptr_FAitfX->UpdateSubMonthExpense("sa", srt_CMD.m_str_ParamMonth, true);
    }
    else
    {
        CTool::MassageOutFotmat("Error SM Param", '!');
    }

    m_ptr_FAitfX->UpdateMonthSurplus(srt_CMD.m_str_ParamMonth, false);
    m_ptr_FAitfX->SyncMonthSurplus(srt_CMD.m_str_ParamMonth);
    m_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdCheckTitle(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamTitle == DK )
    {
        m_ptr_FAitfX->CheckTitleExpense("DK", true);
    }
    else if( srt_CMD.m_str_ParamTitle == NS )
    {
        m_ptr_FAitfX->CheckTitleExpense("NS", true);
    }
    else if( srt_CMD.m_str_ParamTitle == TRAVEL )
    {
        m_ptr_FAitfX->CheckTitleExpense("travel", true);
    }
    else if( srt_CMD.m_str_ParamTitle == LOTTERY )
    {
        m_ptr_FAitfX->CheckTitleExpense("lottery", true);
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
        m_ptr_FAitfX->UpdateTitleExpense("DK", true);
    }
    else if( srt_CMD.m_str_ParamTitle == NS )
    {
        m_ptr_FAitfX->UpdateTitleExpense("NS", true);
    }
    else if( srt_CMD.m_str_ParamTitle == TRAVEL )
    {
        m_ptr_FAitfX->UpdateTitleExpense("travel", true);
    }
    else if( srt_CMD.m_str_ParamTitle == LOTTERY )
    {
        m_ptr_FAitfX->UpdateTitleExpense("lottery", true);
    }
    else
    {
        CTool::MassageOutFotmat("Error TT Param", '!');

        return;
    }

    m_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdTransfer(CMD_Packet srt_CMD)
{
    if(srt_CMD.m_int_ParamValue > 0)
    {
        m_ptr_FAitfX->TransferBalance("零钱通", "余额宝", true, srt_CMD.m_int_ParamValue);
    }
    else
    {
        m_ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, (-1)*srt_CMD.m_int_ParamValue);
    }
}

void CCMDHandler::OnCmdLottery(CMD_Packet srt_CMD)
{
    if(srt_CMD.m_int_ParamValue > 0)
    {
        m_ptr_FAitfX->TransferBalance("零钱通", "余额宝", true, srt_CMD.m_int_ParamValue);
        m_ptr_FAitfX->AppendLottery(true, srt_CMD.m_int_ParamValue, srt_CMD.m_str_ParamDate);
    }
    else
    {
        m_ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, (-1)*srt_CMD.m_int_ParamValue);
        m_ptr_FAitfX->AppendLottery(false, (-1)*srt_CMD.m_int_ParamValue, srt_CMD.m_str_ParamDate);
    }
    m_ptr_ASitfX->UpdateSum(0);
}

void CCMDHandler::OnCmdAnalysisTrend(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ResParam == EXPENSE )
    {
        m_ptr_ASitfX->AnalysisMonthTrend_EXP();
    }
    else if( srt_CMD.m_str_ResParam == MODIFY_LIFE )
    {
        m_ptr_ASitfX->AnalysisMonthTrend_LIFE();
    }
    else if( srt_CMD.m_str_ResParam == ROOM )
    {
        m_ptr_ASitfX->AnalysisMonthTrend_ROOM();
    }
    else if( srt_CMD.m_str_ResParam == CONSUMPTION )
    {
        m_ptr_ASitfX->AnalysisMonthTrend_CSM();
    }
    else
    {
        m_ptr_ASitfX->AnalysisMonthTrend(srt_CMD.m_str_ResParam);
    }
}

void CCMDHandler::OnCmdAnalysisProportion(CMD_Packet srt_CMD)
{
    m_ptr_FAitfX->AnalysisMonthProportion(srt_CMD.m_str_ParamMonth);
}

void CCMDHandler::OnCmdSummarize(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ResParam == MONTH )
    {
        m_ptr_FAitfX->SummarizeMonth(2);
    }
    else if( srt_CMD.m_str_ResParam == TITLE )
    {
        m_ptr_FAitfX->SummarizeTitle(1);
    }
    else if( srt_CMD.m_str_ResParam == TAIL )
    {
        m_ptr_FAitfX->SummarizeTail(1);
    }
}

void CCMDHandler::OnCmdForecast(CMD_Packet srt_CMD)
{
	m_ptr_FAitfX->ForecastFutureSum(srt_CMD.m_str_ResParam.c_str(), srt_CMD.m_int_ResParam);
}

void CCMDHandler::OnCmdPrintMonth(CMD_Packet srt_CMD)
{
    m_ptr_FAitfX->PrintMonth(srt_CMD.m_str_ParamMonth, true);
}

void CCMDHandler::OnCmdPrintSubMonth(CMD_Packet srt_CMD)
{
    if( srt_CMD.m_str_ParamSubMonth == ALL )
    {
        m_ptr_ASitfX->PrintSubMonthTraversal(srt_CMD.m_str_ParamMonth, false);
    }
    else if( srt_CMD.m_str_ParamSubMonth == DGTLER )
    {
        m_ptr_FAitfX->PrintSubMonth("DGtler", srt_CMD.m_str_ParamMonth, true, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == BOOKS )
    {
        m_ptr_FAitfX->PrintSubMonth("Books", srt_CMD.m_str_ParamMonth, true, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == KEEP )
    {
        m_ptr_FAitfX->PrintSubMonth("KEEP", srt_CMD.m_str_ParamMonth, true, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == TB )
    {
        m_ptr_FAitfX->PrintSubMonth("TB", srt_CMD.m_str_ParamMonth, true, true);
    }
    else if( srt_CMD.m_str_ParamSubMonth == SA )
    {
        m_ptr_FAitfX->PrintSubMonth("sa", srt_CMD.m_str_ParamMonth, true, true);
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
        m_ptr_FAitfX->PrintTitle("DK", true);
    }
    else if( srt_CMD.m_str_ParamTitle == NS )
    {
        m_ptr_FAitfX->PrintTitle("NS", true);
    }
    else if( srt_CMD.m_str_ParamTitle == TRAVEL )
    {
        m_ptr_FAitfX->PrintTitle("travel", true);
    }
    else if( srt_CMD.m_str_ParamTitle == LOTTERY )
    {
        m_ptr_FAitfX->PrintTitle("lottery", true);
    }
    else
    {
        CTool::MassageOutFotmat("Error TT Param", '!');
    }
}

void CCMDHandler::OnCmdAppendMonth(CMD_Packet srt_CMD)
{
    m_ptr_ASitfX->AppendNextMonth(srt_CMD.m_str_ResParam);
}

void CCMDHandler::OnCmdSync(CMD_Packet srt_CMD)
{
	m_ptr_FAitfX->SyncAllFile();
}

void CCMDHandler::OnCmdWrite(CMD_Packet srt_CMD)
{
	m_ptr_FAitfX->WriteAllFile();
}

void CCMDHandler::OnCmdBackup(CMD_Packet srt_CMD)
{
	m_ptr_FAitfX->BackUpAllFile("./FA_SZ.bak/");
    m_ptr_FAitfX->BackUpAllFile("./../Hacker/FA_Auto_X/X_Executable/");
}

void CCMDHandler::OnCmdTest(CMD_Packet srt_CMD)
{
    cout << srt_CMD.m_int_ParamValue << endl;
    cout << srt_CMD.m_str_ParamMonth << endl;
    cout << srt_CMD.m_str_ResParam << endl;
    cout << srt_CMD.m_int_CmdNum << endl;
    cout << srt_CMD.m_int_CmdProNum << endl;
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
