
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
#include "./X_Frame/X_XMLParser.h"
#include "./X_Frame/X_CFGLoader.h"

#include "./OP_Layer/FileOPer.h"
#include "./EP_Layer/LineEPer.h"
#include "./EP_Layer/FileManager.h"
#include "./FA_Layer/FAitfX.h"

using namespace std;


int main(int argc, char **argv, char *env[])
{
    CCFGLoader::LoadCFG("./FA_Script.xml");
    CCFGLoader::LoadVersion();
    CCFGLoader::LoadMonth();
    CCFGLoader::LoadFA();

    Singleton<CFAitfX> FAitfX;
    
    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          FA_Auto X Pro           ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          Version: " << CCFGLoader::m_str_Version << "          ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          初始月度: " << CCFGLoader::m_str_OriginMonth << "            ***" << endl;
    cout << "***          当前月度: " << CCFGLoader::m_str_CurrentMonth << "            ***" << endl;
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
            cout << "----------------------------------------" << endl;
            cout << "!!!            Blank CMD             !!!" << endl;
            cout << "----------------------------------------" << endl;
            
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

            FAitfX.GetInstance()->SyncAllFile();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   写回 所有.md
        //   CMD >>> wb
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(WRITEBACK) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->WriteAllFile();

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

            FAitfX.GetInstance()->BackUpAllFile("./FA_TVT.bak/");
            FAitfX.GetInstance()->BackUpAllFile("./../Desktop/FA_Auto_X/X_Executable/");

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   备份 所有.md >>> X工程
        //   CMD >>> bakup X
        /**************************************************/
        else if( X_CMD.CmpCmdFront(BACKUP) && X_CMD.CmpCmdBack(X)  )
        {   
            CCmdTarget::TagTimeBait();

            //FAitfX.GetInstance()->BackUpAllFile("./../Desktop/FA_Auto_X/X_Executable/");

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 TVT总收支
        //   CMD >>> check tvt
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmdBack(TVT) )
        {   
            CCmdTarget::TagTimeBait();

            int int_AFRest = 0;
            FAitfX.GetInstance()->CheckAggrSurplus(int_AFRest, true);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 TVT总收支
        //   CMD >>> update tvt
        /**************************************************/
        else if( X_CMD.CmpCmdFront(UPDATE) && X_CMD.CmpCmdBack(TVT) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->UpdateAggrSurplus(true);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   FA全系统校验 TVT总收支
        //   CMD >>> check
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(CHECK) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->CheckFA(CCFGLoader::m_str_CurrentMonth);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   FA全系统更新 TVT总收支
        //   CMD >>> update
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(UPDATE) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->UpdateFA(CCFGLoader::m_str_CurrentMonth);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 当月/上月 支出
        //   CMD >>> check expense month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmd(2, EXPENSE) &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                FAitfX.GetInstance()->CheckMonthExpense(CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                FAitfX.GetInstance()->CheckMonthExpense(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth), true);
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 任意月度 收支
        //   CMD >>> check month 09
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmd(2, MONTH) &&\
                (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->CheckMonthSurplus(X_CMD.GetCmd(3), true);

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
                FAitfX.GetInstance()->CheckMonthSurplus(CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                FAitfX.GetInstance()->CheckMonthSurplus(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth), true);
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 任意月度 收支
        //   CMD >>> update month 09
        /**************************************************/
        else if( X_CMD.CmpCmdFront(UPDATE) && X_CMD.CmpCmd(2, MONTH) &&\
                (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->UpdateMonthSurplus(X_CMD.GetCmd(3), true);
            FAitfX.GetInstance()->SyncMonthSurplus(X_CMD.GetCmd(3));
            FAitfX.GetInstance()->UpdateAggrSurplus(false);

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
                FAitfX.GetInstance()->UpdateMonthSurplus(CCFGLoader::m_str_CurrentMonth, true);
                FAitfX.GetInstance()->SyncMonthSurplus(CCFGLoader::m_str_CurrentMonth);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                FAitfX.GetInstance()->UpdateMonthSurplus(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth), true);
                FAitfX.GetInstance()->SyncMonthSurplus(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth));
            }

            FAitfX.GetInstance()->UpdateAggrSurplus(false);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   修改 当月 生活费
        //   CMD >>> ml 50
        /**************************************************/
        else if( X_CMD.CmpCmdFront(MODIFY_LIFE) && (X_CMD.GetCmdNum() == 2) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->ModifyMonthSurplus(CCFGLoader::m_str_CurrentMonth, "生活费", atoi(X_CMD.GetCmd(2).c_str()));
            FAitfX.GetInstance()->SyncMonthSurplus(CCFGLoader::m_str_CurrentMonth);
            FAitfX.GetInstance()->UpdateAggrSurplus(false);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   分析 月度C4消费趋势
        //   CMD >>> as tt c4
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, TREND) && X_CMD.CmpCmdBack(CONSUMPTION) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->AnalysisMonthCSMTrend();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   分析 月度租房支出趋势
        //   CMD >>> as tt room
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, TREND) && X_CMD.CmpCmdBack(ROOM) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->AnalysisMonthROOMTrend();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   分析 月度趋势
        //   CMD >>> as tt Books
        /**************************************************/
        else if( X_CMD.CmpCmdFront(ANALYSIS) && X_CMD.CmpCmd(2, TREND) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->AnalysisMonthTrend(X_CMD.GetCmd(3));

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

            FAitfX.GetInstance()->AnalysisMonthProportion(X_CMD.GetCmd(3));

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   显示 FA当前状态
        //   CMD >>> show
        /**************************************************/
        else if( X_CMD.CmpSoloCmd(SHOW) )
        {
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->ShowMonthSurplus(CCFGLoader::m_str_CurrentMonth, 2);
            FAitfX.GetInstance()->ShowAggrSurplus(2);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;

        }

        /**************************************************/
        //   显示 TVT总收支
        //   CMD >>> show tvt
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SHOW) && X_CMD.CmpCmdBack(TVT) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->ShowAggrSurplus(1);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   显示 当月/上月 收支
        //   CMD >>> show month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SHOW) &&\
                 ( X_CMD.CmpCmdBack(MONTH) || X_CMD.CmpCmdBack(EX_MONTH) ) )
        {
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmdBack(MONTH) )
            {
                FAitfX.GetInstance()->ShowMonthSurplus(CCFGLoader::m_str_CurrentMonth, 1);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                FAitfX.GetInstance()->ShowMonthSurplus(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth), 1);
            }            

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   统计 累计月度收支
        //   CMD >>> show month aggr
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SHOW) && X_CMD.CmpCmd(2, MONTH) && X_CMD.CmpCmdBack(AGGREGATION) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.GetInstance()->ShowAggrMonthSurplus();

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
                FAitfX.GetInstance()->CheckSubMonthExpense("Books", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(KEEP) )
            {
                FAitfX.GetInstance()->CheckSubMonthExpense("KEEP", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(TB) )
            {
                FAitfX.GetInstance()->CheckSubMonthExpense("TB", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(SA) )
            {
                FAitfX.GetInstance()->CheckSubMonthExpense("sa", CCFGLoader::m_str_CurrentMonth, true);
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;
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
                FAitfX.GetInstance()->UpdateSubMonthExpense("Books", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(KEEP) )
            {
                FAitfX.GetInstance()->UpdateSubMonthExpense("KEEP", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(TB) )
            {
                FAitfX.GetInstance()->UpdateSubMonthExpense("TB", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(SA) )
            {
                FAitfX.GetInstance()->UpdateSubMonthExpense("sa", CCFGLoader::m_str_CurrentMonth, true);
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            FAitfX.GetInstance()->UpdateMonthSurplus(CCFGLoader::m_str_CurrentMonth, false);
            FAitfX.GetInstance()->SyncMonthSurplus(CCFGLoader::m_str_CurrentMonth);
            FAitfX.GetInstance()->UpdateAggrSurplus(false);

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
                FAitfX.GetInstance()->CheckTitleExpense("DK", true);
            }
            else if( X_CMD.CmpCmdBack(NS) )
            {
                FAitfX.GetInstance()->CheckTitleExpense("NS", true);
            }
            else if( X_CMD.CmpCmdBack(TRAVEL) )
            {
                FAitfX.GetInstance()->CheckTitleExpense("travel", true);
            }
            else if( X_CMD.CmpCmdBack(LOTTERY) )
            {
                FAitfX.GetInstance()->CheckTitleExpense("lottery", true);
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;
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
                FAitfX.GetInstance()->UpdateTitleExpense("DK", true);
            }
            else if( X_CMD.CmpCmdBack(NS) )
            {
                FAitfX.GetInstance()->UpdateTitleExpense("NS", true);
            }
            else if( X_CMD.CmpCmdBack(TRAVEL) )
            {
                FAitfX.GetInstance()->UpdateTitleExpense("travel", true);
            }
            else if( X_CMD.CmpCmdBack(LOTTERY) )
            {
                FAitfX.GetInstance()->UpdateTitleExpense("lottery", true);
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            FAitfX.GetInstance()->UpdateAggrSurplus(false);

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
                FAitfX.GetInstance()->TransferBalance("零钱通", "余额宝", true, atoi(X_CMD.GetCmd(3).c_str()));
                FAitfX.GetInstance()->AppendLottery(true, atoi(X_CMD.GetCmd(3).c_str()), X_CMD.GetCmd(4));
            }
            else if( X_CMD.CmpCmd(2, "--") )
            {
                FAitfX.GetInstance()->TransferBalance("零钱通", "余额宝", false, atoi(X_CMD.GetCmd(3).c_str()));
                FAitfX.GetInstance()->AppendLottery(false, atoi(X_CMD.GetCmd(3).c_str()), X_CMD.GetCmd(4));
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            FAitfX.GetInstance()->UpdateAggrSurplus(false);

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   transfer 操作
        //   CMD >>> transfer ++/-- 300
        /**************************************************/
        else if( X_CMD.CmpCmdFront(TRANSFER) && (X_CMD.GetCmdNum() == 3) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmd(2, "++") )
            {
                FAitfX.GetInstance()->TransferBalance("零钱通", "余额宝", true, atoi(X_CMD.GetCmd(3).c_str()));
            }
            else if( X_CMD.CmpCmd(2, "--") )
            {
                FAitfX.GetInstance()->TransferBalance("零钱通", "余额宝", false, atoi(X_CMD.GetCmd(3).c_str()));
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;
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

            FAitfX.GetInstance()->AppendMonth(X_CMD.GetCmd(3));

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

            FAitfX.GetInstance()->CheckTempExpense();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   CMD输入错误
        /**************************************************/
        else
        {
            cout << "----------------------------------------" << endl;
            cout << "!!!            Error CMD             !!!" << endl;
            cout << "----------------------------------------" << endl;

            continue;
        }
    }

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
