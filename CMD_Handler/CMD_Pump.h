
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include "DefCMDType.h"
#include "CMD_Packet.h"
#include "./../X_Frame/Singleton.h"

using namespace std;


// 定义函数指针
typedef void (*PTRFUNC)(CMD_Packet srt_CMD);

/****************************************/
//   定义CMD_TYPE_ENTRY
/****************************************/
struct X_CMD_TYPE_ENTRY
{
    string str_CmdType;
    string str_CmdHelpTip;
    PTRFUNC pfn_CmdCBFunc;
};

/****************************************/
//   定义CMD_MAP()宏
/****************************************/
#define  X_DECLARE_CMD_MAP()   \
public:   \
    static int CmdNotify(CMD_Packet srt_CMD);   \
private:   \
    static const X_CMD_TYPE_ENTRY CmdTypeEntries[];   \

#define  X_BEGIN_CMD_MAP(thisClass)   \
    const X_CMD_TYPE_ENTRY thisClass::CmdTypeEntries[] =   \
    {   \

#define  X_END_CMD_MAP()   \
        {"EndOfCmdMap", "", NULL}   \
    };   \

/****************************************/
//   定义ON_CMD_TYPE()宏
/****************************************/
#define  X_ON_CMD_TYPE(CmdType, CmdHelpTip, memberFxn)   \
        {CmdType, CmdHelpTip, memberFxn},   \

/****************************************/
//   定义CMD_LOOP()宏
/****************************************/
#define  CMD_LOOP(thisClass)   \
    int thisClass::CmdNotify(CMD_Packet srt_CMD)   \
    {   \
        for(int i=0; ;i++)   \
        {   \
            if(srt_CMD.m_str_CmdType == CmdTypeEntries[i].str_CmdType)   \
            {   \
                if(CmdTypeEntries[i].pfn_CmdCBFunc != NULL)   \
                {   \
                    CmdTypeEntries[i].pfn_CmdCBFunc(srt_CMD);   \
                    if(srt_CMD.m_str_CmdType == X_CMD_TYPE_EXIT)   \
                        return 1;   \
                    else   \
                        return 0;   \
                }   \
            }   \
            else if("EndOfCmdMap" == CmdTypeEntries[i].str_CmdType)   \
            {   \
                return -1;   \
            }   \
        }   \
    }   \

//------------------------------//
//   River flows in summer
//------------------------------//
