
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <iostream>
#include <string>

#include "./X_Frame/DefLib.h"
#include "./X_Frame/X_Tool.h"
#include "./X_Frame/X_CmdTarget.h"

#include "./XML_Ripper/Script_Ripper.h"
#include "./CMD_Handler/CMD_Handler.h"
#include "./FA_Layer/FAitfX.h"
#include "./AS_Layer/ASitfX.h"

using namespace std;


int main(int argc, char **argv, char *env[])
{
    if(0 != CTool::CheckFilesExist())
    {
        CTool::MassageOutFotmat("File Missing", 'X');
        return -1;
    }

    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();
    CASitfX *ptr_ASitfX = Singleton<CASitfX>::GetInstance();

    CCMDHandler *ptr_CMDHandler = Singleton<CCMDHandler>::GetInstance();

    ptr_FAitfX->LoadSum(0);
    ptr_FAitfX->SummerizeMonth(0);
    ptr_FAitfX->SummerizeTitle(0);
    ptr_FAitfX->SummerizeTail(0);
    ptr_FAitfX->SummerizeCAF(0);

    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          FA_Auto X Pro           ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***         Version: " << ptr_ScriptRipper->GetVersion() << "          ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          初始月度: " << ptr_ScriptRipper->GetOriginMonth() << "            ***" << endl;
    cout << "***          当前月度: " << ptr_ScriptRipper->GetCurrentMonth() << "            ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***      >>>  番茄_summer  <<<       ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "****************************************" << endl;
    cout << "****************************************" << endl;

    // NEX_CMD循环模式
    char CMD_linebuffer[MAX_COMMAND];

    // Advance_CMD循环模式
    CCmdTarget X_CMD = CCmdTarget();   // ToDel 番茄
    char CMD_xlinebuffer[MAX_COMMAND];   // ToDel 番茄
    
    while(1)
    {
        cout << "CMD >>> ";
        cin.getline(CMD_linebuffer, MAX_COMMAND);
        strcpy(CMD_xlinebuffer, CMD_linebuffer);   // ToDel 番茄

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
            // 完成后切换ERROR提示
        }

        CCmdTarget::TagTimeBait();
        int int_RetNotify = ptr_CMDHandler->CmdNotify(xCmdPacket);

        if(0 == int_RetNotify)
        {
            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;
            continue;
        }
        else if(1 == int_RetNotify)
            break;
        else
        {
            // 目前交付while()消息循环处理
            // 完成后切换ERROR提示
        }

        /**************************************************/
        //   while()循环 消息 预处理
        /**************************************************/
        X_CMD.CmdParser(CMD_xlinebuffer);

        /**************************************************/
        //   增加 lottery 收支
        //   CMD >>> lottery ++/-- 200 20171222
        /**************************************************/
        if( X_CMD.CmpCmdFront(LOTTERY) && (X_CMD.GetCmdNum() == 4) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmd(2, "++") )
            {
                ptr_FAitfX->TransferBalance("零钱通", "余额宝", true, atoi(X_CMD.GetCmd(3).c_str()));
                ptr_FAitfX->AppendLottery(true, atoi(X_CMD.GetCmd(3).c_str()), X_CMD.GetCmd(4));
            }
            else if( X_CMD.CmpCmd(2, "--") )
            {
                ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, atoi(X_CMD.GetCmd(3).c_str()));
                ptr_FAitfX->AppendLottery(false, atoi(X_CMD.GetCmd(3).c_str()), X_CMD.GetCmd(4));
            }
            else
            {
                CTool::MassageOutFotmat("Error Param", '!');

                continue;
            }

            ptr_ASitfX->UpdateSum(0);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   transfer 操作
        //   CMD >>> tf ++/-- 300
        /**************************************************/
        else if( X_CMD.CmpCmdFront(TRANSFER) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmd(2, "++") )
            {
                ptr_FAitfX->TransferBalance("零钱通", "余额宝", true, atoi(X_CMD.GetCmd(3).c_str()));
            }
            else if( X_CMD.CmpCmd(2, "--") )
            {
                ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, atoi(X_CMD.GetCmd(3).c_str()));
            }
            else
            {
                CTool::MassageOutFotmat("Error Param", '!');

                continue;
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   汇总 Month累计收支
        //   CMD >>> sz month
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SUMMARIZE) && X_CMD.CmpCmdBack(MONTH) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->SummerizeMonth(2);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   汇总 Title累计收支
        //   CMD >>> sz tt
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SUMMARIZE) && X_CMD.CmpCmdBack(TITLE) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->SummerizeTitle(1);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   汇总 Tail累计收支
        //   CMD >>> sz tail
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SUMMARIZE) && X_CMD.CmpCmdBack(TAIL) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->SummerizeTail(1);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   CMD输入错误
        /**************************************************/
        else
        {
            CTool::MassageOutFotmat("Error CMD", '!');

            continue;
        }
    }

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
