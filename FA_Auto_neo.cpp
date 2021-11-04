
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
    //CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");

    vector<string> vec_str_File;
    ptr_XonfigLoader->FileDuplicator(vec_str_File);

    if(0 != CTool::CheckFilesExist(vec_str_File))
    {
        CTool::MassageOutFotmat("File Missing", 'X');
        return -1;
    }

    //***********************************//
    //### 初始化
    // CTool::Month初始化后
    // 才能ExMonthGenerator
    // 才能MonthRangeGenerator
    //***********************************//

    CTool::SetOriginMonth(ptr_XonfigLoader->GetOriginMonth());
    CTool::SetCurrentMonth(ptr_XonfigLoader->GetCurrentMonth());

    //ptr_ScriptRipper->ExMonthGenerator();
    //ptr_ScriptRipper->MonthRangeGenerator();
    
    ptr_XonfigLoader->ExMonthGenerator();
    ptr_XonfigLoader->MonthRangeGenerator();

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
