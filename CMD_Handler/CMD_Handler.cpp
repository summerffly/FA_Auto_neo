
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Handler.h"

#include "./../X_Frame/X_Tool.h"


CScriptRipper* CCMDHandler::m_ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
CFAitfX* CCMDHandler::m_ptr_FAitfX = Singleton<CFAitfX>::GetInstance();
CASitfX* CCMDHandler::m_ptr_ASitfX = Singleton<CASitfX>::GetInstance();

/**************************************************/
//   CMD_MAP()宏
/**************************************************/
X_BEGIN_CMD_MAP(CCMDHandler)
	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_FA, "", OnCmdCheckFA)
	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_FA, "", OnCmdUpdateFA)
	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_FA, "", OnCmdShowFA)
	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_MONTH, "", OnCmdCheckMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_MONTH, "", OnCmdUpdateMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_SHOW_MONTH, "", OnCmdShowMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_CHECK_SUBMONTH, "", OnCmdCheckSubMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_UPDATE_SUBMONTH, "", OnCmdUpdateSubMonth)
	X_ON_CMD_TYPE(X_CMD_TYPE_FORECAST, "", OnCmdForecast)
	X_ON_CMD_TYPE(X_CMD_TYPE_SYNC, "", OnCmdSync)
	X_ON_CMD_TYPE(X_CMD_TYPE_WRITE, "", OnCmdWrite)
	X_ON_CMD_TYPE(X_CMD_TYPE_BACKUP, "", OnCmdBackup)
	X_ON_CMD_TYPE(X_CMD_TYPE_CANCEL, "", OnCmdCancel)
	X_ON_CMD_TYPE(X_CMD_TYPE_EXIT, "", OnCmdExit)
	X_ON_CMD_TYPE(X_CMD_TYPE_TEST, "", OnCmdTest)
X_END_CMD_MAP()

/**************************************************/
//   CMD_LOOP()宏
/**************************************************/
CMD_LOOP(CCMDHandler)

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
	if( srt_CMD.m_str_ParamSubMonth == BOOKS )
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
	if( srt_CMD.m_str_ParamSubMonth == BOOKS )
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

void CCMDHandler::OnCmdForecast(CMD_Packet srt_CMD)
{
	m_ptr_FAitfX->ForecastFutureSum(srt_CMD.m_str_ResParam.c_str(), srt_CMD.m_int_ResParam);
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

void CCMDHandler::OnCmdTest(CMD_Packet srt_CMD)
{
	cout << srt_CMD.m_int_ParamValue << endl;
	cout << srt_CMD.m_str_ParamMonth << endl;
	cout << srt_CMD.m_str_ResParam << endl;
	cout << srt_CMD.m_int_CmdNum << endl;
	cout << srt_CMD.m_int_CmdProNum << endl;
}

//------------------------------//
//   River flows in summer
//------------------------------//
