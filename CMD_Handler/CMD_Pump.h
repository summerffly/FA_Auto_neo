
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include "./../X_Frame/X_CmdTarget.h"

using namespace std;


/****************************************/
//   定义所有CMD类型
/****************************************/
//#define  X_CMD_   ("")

// 定义函数指针
typedef void (*PTRFUNC)(CCmdTarget cls_Cmd);

/****************************************/
//   
/****************************************/
struct X_CMD_TYPE_ENTRY
{
    string str_CmdType;
    PTRFUNC pfn_CmdCBFunc;
};

/****************************************/
//   
/****************************************/
#define  X_DECLARE_CMD_MAP()   \
public:   \
    void CmdNotify(CCmdTarget cls_Cmd);   \
private:   \
    static const X_CMD_TYPE_ENTRY CmdEntries[];   \

#define  X_BEGIN_CMD_MAP(thisClass)   \
    const X_CMD_TYPE_ENTRY thisClass::CmdEntries[] =   \
    {   \

#define  X_END_CMD_MAP()   \
        {"", NULL}   \
    };   \

/****************************************/
//   
/****************************************/
#define  X_ON_CMD_TYPE(CmdType, memberFxn)   \
        {CmdType, memberFxn},   \

/****************************************/
//   
/****************************************/
#define  CMD_LOOP(thisClass)   \
    void thisClass::CmdNotify(CCmdTarget cls_Cmd)   \
    {   \
        for(int i=0; ;i++)   \
        {   \
            if()   \
            {   \
                if(memberFxn != NULL)   \
                    memberFxn(cls_Cmd);   \
            }   \
        }   \
    }   \

//------------------------------//
//   River flows in summer
//------------------------------//
