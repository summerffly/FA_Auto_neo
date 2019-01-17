
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <iostream>
#include <string>

#include "./X_Frame/DefLib.h"
#include "./X_Frame/X_Tool.h"
#include "./CMD_Handler/CMD_Handler.h"

using namespace std;


int main(int argc, char **argv, char *env[])
{
    //***********************************//
    //### 检查.md文件存在
    //***********************************//

    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    vector<string> vec_str_File;
    ptr_ScriptRipper->FileDuplicator(vec_str_File);

    if(0 != CTool::CheckFilesExist(vec_str_File))
    {
        CTool::MassageOutFotmat("File Missing", 'X');
        return -1;
    }

    //***********************************//
    //### 初始化
    //***********************************//

    CTool::ms_str_OriginMonth = ptr_ScriptRipper->GetOriginMonth();
    CTool::ms_str_CurrentMonth = ptr_ScriptRipper->GetCurrentMonth();

    // tips 番茄@20190117 - CTool::Month初始化后才能MonthRangeGenerator
    ptr_ScriptRipper->MonthRangeGenerator();

    CCMDHandler *ptr_CMDHandler = Singleton<CCMDHandler>::GetInstance();
    ptr_CMDHandler->CMD_Init();

    //***********************************//
    //### 开始 CMD 命令循环
    //***********************************//

    ptr_CMDHandler->CMD_Loop();

    //***********************************//
    //### 结束 CMD 命令循环
    //***********************************//

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
