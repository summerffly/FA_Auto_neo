
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sys/time.h>

#include "./X_Frame/DefLib.h"
#include "./X_Frame/X_Tool.h"
#include "./X_Frame/Singleton.h"
#include "./X_Frame/X_CmdTarget.h"

#include "./XML_Ripper/Script_Ripper.h"

#include "./CMD_Handler/CMD_Handler.h"

#include "./OP_Layer/FileOPer.h"
#include "./EP_Layer/LineEPer.h"
#include "./EP_Layer/FileManager.h"
#include "./FA_Layer/FAitfX.h"
#include "./AS_Layer/ASitfX.h"

using namespace std;


int main(int argc, char **argv, char *env[])
{
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
        //   校验 SUM总收支
        //   CMD >>> check sum
        /**************************************************/
        if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmdBack(SUM) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->CheckSum(1);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 SUM总收支
        //   CMD >>> update sum
        /**************************************************/
        else if( X_CMD.CmpCmdFront(UPDATE) && X_CMD.CmpCmdBack(SUM) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->UpdateSum(1);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 当月 生活费
        //   CMD >>> life 50
        /**************************************************/
        else if( X_CMD.CmpCmdFront(MODIFY_LIFE) && (X_CMD.GetCmdNum() == 2) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->ModifyMonthSurplus(ptr_ScriptRipper->GetCurrentMonth(), "生活费", atoi(X_CMD.GetCmd(2).c_str()));
            ptr_FAitfX->SyncMonthSurplus(ptr_ScriptRipper->GetCurrentMonth());
            ptr_ASitfX->UpdateSum(0);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 当月 微信生活费
        //   CMD >>> wlife 50
        /**************************************************/
        else if( X_CMD.CmpCmdFront(MODIFY_LIFE_WC) && (X_CMD.GetCmdNum() == 2) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->ModifyMonthSurplus(ptr_ScriptRipper->GetCurrentMonth(), "生活费", atoi(X_CMD.GetCmd(2).c_str()));
            ptr_FAitfX->SyncMonthSurplus(ptr_ScriptRipper->GetCurrentMonth());
            ptr_ASitfX->UpdateSum(0);

            ptr_FAitfX->TransferBalance("零钱通", "余额宝", false, atoi(X_CMD.GetCmd(2).c_str()));

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 Tt分项 支出
        //   CMD >>> check tt dk/ns/travel/lottery
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmd(2, TITLE) && (X_CMD.GetCmdNum() == 3) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(DK) )
            {
                ptr_FAitfX->CheckTitleExpense("DK", true);
            }
            else if( X_CMD.CmpCmdBack(NS) )
            {
                ptr_FAitfX->CheckTitleExpense("NS", true);
            }
            else if( X_CMD.CmpCmdBack(TRAVEL) )
            {
                ptr_FAitfX->CheckTitleExpense("travel", true);
            }
            else if( X_CMD.CmpCmdBack(LOTTERY) )
            {
                ptr_FAitfX->CheckTitleExpense("lottery", true);
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
        //   更新 Tt分项 支出
        //   CMD >>> update tt dk/ns/travel/lottery
        /**************************************************/
        else if( X_CMD.CmpCmdFront(UPDATE) && X_CMD.CmpCmd(2, TITLE) && (X_CMD.GetCmdNum() == 3) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(DK) )
            {
                ptr_FAitfX->UpdateTitleExpense("DK", true);
            }
            else if( X_CMD.CmpCmdBack(NS) )
            {
                ptr_FAitfX->UpdateTitleExpense("NS", true);
            }
            else if( X_CMD.CmpCmdBack(TRAVEL) )
            {
                ptr_FAitfX->UpdateTitleExpense("travel", true);
            }
            else if( X_CMD.CmpCmdBack(LOTTERY) )
            {
                ptr_FAitfX->UpdateTitleExpense("lottery", true);
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
        //   增加 lottery 收支
        //   CMD >>> lottery ++/-- 200 20171222
        /**************************************************/
        else if( X_CMD.CmpCmdFront(LOTTERY) && (X_CMD.GetCmdNum() == 4) )
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
        //   插入 月度 脚本
        //   CMD >>> append month 02
        /**************************************************/
        else if( X_CMD.CmpCmdFront(APPEND) && X_CMD.CmpCmd(2, MONTH) &&\
                 (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->AppendNextMonth(X_CMD.GetCmd(3));

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 temp 支出
        //   CMD >>> check temp
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmdBack(TEMP) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->CheckTempExpense();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   分析月度趋势 LIFE生活支出
        //   CMD >>> as tt life
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, TREND) && X_CMD.CmpCmdBack(MODIFY_LIFE) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->AnalysisMonthTrend_LIFE();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   分析月度趋势 ROOM租房支出
        //   CMD >>> as tt room
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, TREND) && X_CMD.CmpCmdBack(ROOM) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->AnalysisMonthTrend_ROOM();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   分析月度趋势 CSM消费支出
        //   CMD >>> as tt csm
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, TREND) && X_CMD.CmpCmdBack(CONSUMPTION) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->AnalysisMonthTrend_CSM();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   分析 月度趋势
        //   CMD >>> as tt Books
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, TREND) && (X_CMD.GetCmdNum() == 3)
                 && !X_CMD.CmpCmdBack(CONSUMPTION) && !X_CMD.CmpCmdBack(ROOM) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->AnalysisMonthTrend(X_CMD.GetCmd(3));

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   分析 月度百分占比
        //   CMD >>> as pp 12
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, PROPORTION) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->AnalysisMonthProportion(X_CMD.GetCmd(3));

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
        //   Print 月度 当月/上月
        //   CMD >>> print month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && (X_CMD.GetCmdNum() == 2) &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                ptr_FAitfX->PrintMonth(ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                ptr_FAitfX->PrintMonth(ptr_ScriptRipper->GetPreviousMonth(), true);
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Print 月度 任意月份
        //   CMD >>> print month 04
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, MONTH) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->PrintMonth(X_CMD.GetCmd(3), true);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Print 月度.M 任意月份
        //   CMD >>> print sm tb 04
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 4) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmd(3, BOOKS) )
            {
                ptr_FAitfX->PrintSubMonth("Books", X_CMD.GetCmd(4), true, true);
            }
            else if( X_CMD.CmpCmd(3, KEEP) )
            {
                ptr_FAitfX->PrintSubMonth("KEEP", X_CMD.GetCmd(4), true, true);
            }
            else if( X_CMD.CmpCmd(3, TB) )
            {
                ptr_FAitfX->PrintSubMonth("TB", X_CMD.GetCmd(4), true, true);
            }
            else if( X_CMD.CmpCmd(3, SA) )
            {
                ptr_FAitfX->PrintSubMonth("sa", X_CMD.GetCmd(4), true, true);
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
        //   Print 全部月度.M 当月/上月
        //   CMD >>> print sm month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 3)  &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                ptr_ASitfX->PrintSubMonthTraversal(ptr_ScriptRipper->GetCurrentMonth(), false);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                ptr_ASitfX->PrintSubMonthTraversal(ptr_ScriptRipper->GetPreviousMonth(), false);
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Print 全部月度.M 任意月份
        //   CMD >>> print sm 04
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->PrintSubMonthTraversal(X_CMD.GetCmd(3), false);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Print 全部月度.M 任意月份
        //   CMD >>> print sm 04
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->PrintSubMonthTraversal(X_CMD.GetCmd(3), false);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Print Tt分项
        //   CMD >>> print tt dk
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, TITLE) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmd(3, DK) )
            {
                ptr_FAitfX->PrintTitle("DK", true);
            }
            else if( X_CMD.CmpCmd(3, NS) )
            {
                ptr_FAitfX->PrintTitle("NS", true);
            }
            else if( X_CMD.CmpCmd(3, TRAVEL) )
            {
                ptr_FAitfX->PrintTitle("travel", true);
            }
            else if( X_CMD.CmpCmd(3, LOTTERY) )
            {
                ptr_FAitfX->PrintTitle("lottery", true);
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
        //   展示 SUM总收支
        //   CMD >>> show sum
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SHOW) && X_CMD.CmpCmdBack(SUM) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->ShowSum();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   FA_Auto_X 帮助提示
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(HELP) )
        {

            CCmdTarget::TagTimeBait();

            ptr_ASitfX->HelpAll();

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
