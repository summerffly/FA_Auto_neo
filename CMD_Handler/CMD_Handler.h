
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
	static void OnCmdCheckFA(CMD_Packet srt_CMD);
	static void OnCmdUpdateFA(CMD_Packet srt_CMD);
	static void OnCmdShowFA(CMD_Packet srt_CMD);

	static void OnCmdSync(CMD_Packet srt_CMD);
	static void OnCmdWrite(CMD_Packet srt_CMD);
	static void OnCmdBackup(CMD_Packet srt_CMD);

	static void OnCmdCancel(CMD_Packet srt_CMD);
	static void OnCmdExit(CMD_Packet srt_CMD);

	static void OnCmdTest(CMD_Packet srt_CMD);

private:
	static CScriptRipper *m_ptr_ScriptRipper;
    static CFAitfX *m_ptr_FAitfX;
    static CASitfX *m_ptr_ASitfX;
};

//------------------------------//
//   River flows in summer
//------------------------------//
