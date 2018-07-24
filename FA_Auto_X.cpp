
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
    if(0 != CTool::CheckFilesExist())
    {
        CTool::MassageOutFotmat("File Missing", 'X');
        return -1;
    }

    //***********************************//
    //### 初始化
    //***********************************//
    CCMDHandler *ptr_CMDHandler = Singleton<CCMDHandler>::GetInstance();
    ptr_CMDHandler->CMD_Init();

    //***********************************//
    //### 开始CMD命令循环
    //***********************************//
    ptr_CMDHandler->CMD_Loop();

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
