
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>

#include "CMD_Pump.h"
#include "./../XML_Ripper/Script_Ripper.h"
#include "./../FA_Layer/FAitfX.h"
#include "./../AS_Layer/ASitfX.h"

using namespace std;


class CCMDHandler
{
public:
	friend class Singleton<CCMDHandler>;

    CCMDHandler();
    ~CCMDHandler();

    X_DECLARE_CMD_MAP()

public:
	static void CMD_Loop();
	static void CMD_Init();

	static void CMD_Help(CMD_Packet srt_CMD);

public:
	static void OnCmdCheckFA(CMD_Packet srt_CMD);
	static void OnCmdUpdateFA(CMD_Packet srt_CMD);
	static void OnCmdShowFA(CMD_Packet srt_CMD);

	static void OnCmdCheckSum(CMD_Packet srt_CMD);
	static void OnCmdUpdateSum(CMD_Packet srt_CMD);
	static void OnCmdShowSum(CMD_Packet srt_CMD);

	static void OnCmdModifyLife(CMD_Packet srt_CMD);

	static void OnCmdCheckMonth(CMD_Packet srt_CMD);
	static void OnCmdUpdateMonth(CMD_Packet srt_CMD);
	static void OnCmdShowMonth(CMD_Packet srt_CMD);

	static void OnCmdCheckSubMonth(CMD_Packet srt_CMD);
	static void OnCmdUpdateSubMonth(CMD_Packet srt_CMD);

	static void OnCmdCheckTitle(CMD_Packet srt_CMD);
	static void OnCmdUpdateTitle(CMD_Packet srt_CMD);

	static void OnCmdTransfer(CMD_Packet srt_CMD);
	static void OnCmdLottery(CMD_Packet srt_CMD);

	static void OnCmdAnalysisTrend(CMD_Packet srt_CMD);
	static void OnCmdAnalysisProportion(CMD_Packet srt_CMD);

	static void OnCmdSummarize(CMD_Packet srt_CMD);
	static void OnCmdForecast(CMD_Packet srt_CMD);

	static void OnCmdPrintMonth(CMD_Packet srt_CMD);
	static void OnCmdPrintSubMonth(CMD_Packet srt_CMD);
	static void OnCmdPrintTitle(CMD_Packet srt_CMD);

	static void OnCmdAppendMonth(CMD_Packet srt_CMD);

	static void OnCmdSync(CMD_Packet srt_CMD);
	static void OnCmdWrite(CMD_Packet srt_CMD);
	static void OnCmdBackup(CMD_Packet srt_CMD);

	static void OnCmdTest(CMD_Packet srt_CMD);

	static void OnCmdCancel(CMD_Packet srt_CMD);
	static void OnCmdExit(CMD_Packet srt_CMD);

private:
	static CScriptRipper *m_ptr_ScriptRipper;
    static CFAitfX *m_ptr_FAitfX;
    static CASitfX *m_ptr_ASitfX;
};

//------------------------------//
//   River flows in summer
//------------------------------//
