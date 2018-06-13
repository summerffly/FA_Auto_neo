
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
#include "./X_Frame/CmdLib.h"
#include "./X_Frame/X_Tool.h"
#include "./X_Frame/Singleton.h"
#include "./X_Frame/X_CmdTarget.h"

#include "./XML_Ripper/Script_Ripper.h"

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

    // Advanced_CMD循环模式
    CCmdTarget X_CMD = CCmdTarget();
    char CMD_linebuffer[MAX_COMMAND];
    
    while(1)
    {
        cout << "CMD >>> ";
        cin.getline(CMD_linebuffer, MAX_COMMAND);

        /**************************************************/
        //   判断 空行
        /**************************************************/
        if( X_CMD.CmdParser(CMD_linebuffer) == -1 )
        {
            CTool::MassageOutFotmat("Blank CMD", '!');
            
            continue;
        }
        
        /**************************************************/
        //   撤销 输入
        /**************************************************/
        if( X_CMD.CmpCmdBack(CANCEL) )
        {
            cout << "----------------------------------------" << endl;
            cout << "###           CMD canceled           ###" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }

        /**************************************************/
        //   退出 FA_Auto_X
        /**************************************************/
        if( X_CMD.CmpSoloCmd(EXIT) )
        {
            cout << endl;
            cout << "****************************************" << endl;
            cout << "***          FA_Auto X Pro           ***" << endl;
            cout << "***              EXIT                ***" << endl;
            cout << "****************************************" << endl;
            cout << endl;

            break;
        }

        /**************************************************/
        //   同步 所有.md
        //   CMD >>> sync
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(SYNC) )
        {
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->SyncAllFile();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   写回 所有.md
        //   CMD >>> write
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(WRITE) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->WriteAllFile();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   备份 所有.md
        //   CMD >>> bakup
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(BACKUP) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->BackUpAllFile("./FA_SZ.bak/");
            ptr_FAitfX->BackUpAllFile("./../Hacker/FA_Auto_X/X_Executable/");

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 SUM总收支
        //   CMD >>> check sum
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmdBack(SUM) )
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
        //   校验 FA全系统总收支
        //   CMD >>> check
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(CHECK) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->CheckFA();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 FA全系统总收支
        //   CMD >>> update
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(UPDATE) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->UpdateFA();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 任意Month 收支
        //   CMD >>> check month 09
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmd(2, MONTH) &&\
                (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            if( !ptr_ScriptRipper->IsIncludeMonthRange(X_CMD.GetCmd(3)) )
            {
                CTool::MassageOutFotmat("Invalid Month Input", '!');
                continue;
            }

            ptr_ASitfX->CheckMonth(X_CMD.GetCmd(3), 1);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 当月/上月 收支
        //   CMD >>> check month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                ptr_ASitfX->CheckMonth(ptr_ScriptRipper->GetCurrentMonth(), 1);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                ptr_ASitfX->CheckMonth(ptr_ScriptRipper->GetPreviousMonth(), 1);
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 任意Month 收支
        //   CMD >>> update month 09
        /**************************************************/
        else if( X_CMD.CmpCmdFront(UPDATE) && X_CMD.CmpCmd(2, MONTH) &&\
                (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            if( !ptr_ScriptRipper->IsIncludeMonthRange(X_CMD.GetCmd(3)) )
            {
                CTool::MassageOutFotmat("Invalid Month Input", '!');
                continue;
            }

            ptr_ASitfX->UpdateMonth(X_CMD.GetCmd(3), 1);
            ptr_ASitfX->UpdateSum(0);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 当月/上月 收支
        //   CMD >>> update month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(UPDATE) &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                ptr_ASitfX->UpdateMonth(ptr_ScriptRipper->GetCurrentMonth(), 1);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                ptr_ASitfX->UpdateMonth(ptr_ScriptRipper->GetPreviousMonth(), 1);
            }

            ptr_ASitfX->UpdateSum(0);

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
        //   校验 子项.M 支出
        //   CMD >>> check sm books/keep/tb/sa
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 3) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(BOOKS) )
            {
                ptr_FAitfX->CheckSubMonthExpense("Books", ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else if( X_CMD.CmpCmdBack(KEEP) )
            {
                ptr_FAitfX->CheckSubMonthExpense("KEEP", ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else if( X_CMD.CmpCmdBack(TB) )
            {
                ptr_FAitfX->CheckSubMonthExpense("TB", ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else if( X_CMD.CmpCmdBack(SA) )
            {
                ptr_FAitfX->CheckSubMonthExpense("sa", ptr_ScriptRipper->GetCurrentMonth(), true);
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
        //   更新 子项.M 支出
        //   CMD >>> update sm books/keep/tb/sa
        /**************************************************/
        else if( X_CMD.CmpCmdFront(UPDATE) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 3) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(BOOKS) )
            {
                ptr_FAitfX->UpdateSubMonthExpense("Books", ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else if( X_CMD.CmpCmdBack(KEEP) )
            {
                ptr_FAitfX->UpdateSubMonthExpense("KEEP", ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else if( X_CMD.CmpCmdBack(TB) )
            {
                ptr_FAitfX->UpdateSubMonthExpense("TB", ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else if( X_CMD.CmpCmdBack(SA) )
            {
                ptr_FAitfX->UpdateSubMonthExpense("sa", ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else
            {
                CTool::MassageOutFotmat("Error Param", '!');

                continue;
            }

            ptr_FAitfX->UpdateMonthSurplus(ptr_ScriptRipper->GetCurrentMonth(), false);
            ptr_FAitfX->SyncMonthSurplus(ptr_ScriptRipper->GetCurrentMonth());
            ptr_ASitfX->UpdateSum(0);

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
        //   分析 月度趋势
        //   CMD >>> as tt Books
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, TREND) && (X_CMD.GetCmdNum() == 3)
                 && !X_CMD.CmpCmdBack(CONSUMPTION) && !X_CMD.CmpCmdBack(ROOM) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->AnalysisMonthTrend(X_CMD.GetCmd(3));

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
        //   分析月度趋势 租房支出
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
        //   展示.md 月度 当月/上月
        //   CMD >>> print month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && (X_CMD.GetCmdNum() == 2) &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                ptr_FAitfX->ShowMDRawMonth(ptr_ScriptRipper->GetCurrentMonth(), true);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                ptr_FAitfX->ShowMDRawMonth(ptr_ScriptRipper->GetPreviousMonth(), true);
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   展示.md 月度 任意月份
        //   CMD >>> print month 04
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, MONTH) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_FAitfX->ShowMDRawMonth(X_CMD.GetCmd(3), true);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   展示.md 月度.M 任意月份
        //   CMD >>> print sm tb 04
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 4) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmd(3, BOOKS) )
            {
                ptr_FAitfX->ShowMDRawSubMonth("Books", X_CMD.GetCmd(4), true, true);
            }
            else if( X_CMD.CmpCmd(3, KEEP) )
            {
                ptr_FAitfX->ShowMDRawSubMonth("KEEP", X_CMD.GetCmd(4), true, true);
            }
            else if( X_CMD.CmpCmd(3, TB) )
            {
                ptr_FAitfX->ShowMDRawSubMonth("TB", X_CMD.GetCmd(4), true, true);
            }
            else if( X_CMD.CmpCmd(3, SA) )
            {
                ptr_FAitfX->ShowMDRawSubMonth("sa", X_CMD.GetCmd(4), true, true);
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
        //   展示.md 全部月度.M 当月/上月
        //   CMD >>> print sm month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 3)  &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                ptr_ASitfX->ShowMDRawSubMonthTraversal(ptr_ScriptRipper->GetCurrentMonth(), false);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                ptr_ASitfX->ShowMDRawSubMonthTraversal(ptr_ScriptRipper->GetPreviousMonth(), false);
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   展示.md 全部月度.M 任意月份
        //   CMD >>> print sm 04
        /**************************************************/
        else if( X_CMD.CmpCmdFront(PRINT) && X_CMD.CmpCmd(2, SUBMONTH) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->ShowMDRawSubMonthTraversal(X_CMD.GetCmd(3), false);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   展示 当月/上月 收支
        //   CMD >>> show month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SHOW) &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                ptr_FAitfX->ShowMonthSurplus(ptr_ScriptRipper->GetCurrentMonth(), 4);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                ptr_FAitfX->ShowMonthSurplus(ptr_ScriptRipper->GetPreviousMonth(), 4);
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
        //   展示 FA当前状态
        //   CMD >>> show
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(SHOW) )
        {
            CCmdTarget::TagTimeBait();

            ptr_ASitfX->ShowFA();

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
        //   FA_Auto_X 接口测试
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(TEST) )
        {

            CCmdTarget::TagTimeBait();

            //ptr_ASitfX->CheckSum(1);

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
