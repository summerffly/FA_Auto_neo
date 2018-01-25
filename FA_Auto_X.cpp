
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
#include "./X_Frame/X_CmdTarget.h"
#include "./X_Frame/X_XMLParser.h"
#include "./X_Frame/X_CFGLoader.h"

#include "./OP_Layer/FileOPer.h"
#include "./EP_Layer/LineEPer.h"
#include "./EP_Layer/FileManager.h"
#include "./FA_Layer/FAitfX.h"

#include "./Thread/MultiThread.h"
#include "./Thread/FileThread.h"

using namespace std;


int main(int argc, char **argv, char *env[])
{
    CCFGLoader::LoadCFG("./FA_Script.xml");
    CCFGLoader::LoadVersion();
    CCFGLoader::LoadMonth();
    CCFGLoader::LoadFA();

    CFAitfX FAitfX = CFAitfX();
    
    cout << "****************************************" << endl;
    cout << "****************************************" << endl;
    cout << "***                                  ***" << endl;
    cout << "***          FA_Auto X Pro           ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***  ------------------------------  ***" << endl;
    cout << "***                                  ***" << endl;
    cout << "***      Version: " << CCFGLoader::m_str_Version << "       ***" << endl;
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

            FAitfX.SyncAllFile();

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

            FAitfX.WriteAllFile();

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

            FAitfX.BackUpAllFile("./FA_TVT.bak/");

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

            FAitfX.BackUpAllFile("./../Desktop/FA_Auto_X/");

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

            unsigned int uni_AliRest = 0;
            FAitfX.CheckAggrSurplus(uni_AliRest, true);

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

            FAitfX.UpdateAggrSurplus(true);

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

            FAitfX.CheckFA(CCFGLoader::m_str_CurrentMonth);

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
                FAitfX.CheckMonthExpense(CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                FAitfX.CheckMonthExpense(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth), true);
            }

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
                FAitfX.CheckMonthSurplus(CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                FAitfX.CheckMonthSurplus(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth), true);
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

            FAitfX.CheckMonthSurplus(X_CMD.GetCmd(3), true);

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
                FAitfX.UpdateMonthSurplus(CCFGLoader::m_str_CurrentMonth, true);
                FAitfX.SyncMonthSurplus(CCFGLoader::m_str_CurrentMonth);
            }
            else if( X_CMD.CmpCmdBack(EX_MONTH) )
            {
                FAitfX.UpdateMonthSurplus(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth), true);
                FAitfX.SyncMonthSurplus(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth));
            }

            FAitfX.UpdateAggrSurplus(false);

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

            FAitfX.ModifyMonthSurplus(CCFGLoader::m_str_CurrentMonth, "生活费", atoi(X_CMD.GetCmd(2).c_str()));
            FAitfX.SyncMonthSurplus(CCFGLoader::m_str_CurrentMonth);
            FAitfX.UpdateAggrSurplus(false);

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

            FAitfX.AnalysisMonthTrend(X_CMD.GetCmd(3));

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

            FAitfX.AnalysisMonthProportion(X_CMD.GetCmd(3));

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
                FAitfX.CheckSubMonthExpense("Books", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(KEEP) )
            {
                FAitfX.CheckSubMonthExpense("KEEP", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(TB) )
            {
                FAitfX.CheckSubMonthExpense("TB", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(SA) )
            {
                FAitfX.CheckSubMonthExpense("sa", CCFGLoader::m_str_CurrentMonth, true);
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
                FAitfX.UpdateSubMonthExpense("Books", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(KEEP) )
            {
                FAitfX.UpdateSubMonthExpense("KEEP", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(TB) )
            {
                FAitfX.UpdateSubMonthExpense("TB", CCFGLoader::m_str_CurrentMonth, true);
            }
            else if( X_CMD.CmpCmdBack(SA) )
            {
                FAitfX.UpdateSubMonthExpense("sa", CCFGLoader::m_str_CurrentMonth, true);
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            FAitfX.UpdateMonthSurplus(CCFGLoader::m_str_CurrentMonth, false);
            FAitfX.SyncMonthSurplus(CCFGLoader::m_str_CurrentMonth);
            FAitfX.UpdateAggrSurplus(false);

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
                FAitfX.CheckTitleExpense("DK", true);
            }
            else if( X_CMD.CmpCmdBack(NS) )
            {
                FAitfX.CheckTitleExpense("NS", true);
            }
            else if( X_CMD.CmpCmdBack(TRAVEL) )
            {
                FAitfX.CheckTitleExpense("travel", true);
            }
            else if( X_CMD.CmpCmdBack(LOTTERY) )
            {
                FAitfX.CheckTitleExpense("lottery", true);
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
                FAitfX.UpdateTitleExpense("DK", true);
            }
            else if( X_CMD.CmpCmdBack(NS) )
            {
                FAitfX.UpdateTitleExpense("NS", true);
            }
            else if( X_CMD.CmpCmdBack(TRAVEL) )
            {
                FAitfX.UpdateTitleExpense("travel", true);
            }
            else if( X_CMD.CmpCmdBack(LOTTERY) )
            {
                FAitfX.UpdateTitleExpense("lottery", true);
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            FAitfX.UpdateAggrSurplus(false);

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
                FAitfX.TransferBalance("广发银行", "余额宝", true, atoi(X_CMD.GetCmd(3).c_str()));
                FAitfX.AppendLottery(true, atoi(X_CMD.GetCmd(3).c_str()), X_CMD.GetCmd(4));
            }
            else if( X_CMD.CmpCmd(2, "--") )
            {
                FAitfX.TransferBalance("广发银行", "余额宝", false, atoi(X_CMD.GetCmd(3).c_str()));
                FAitfX.AppendLottery(false, atoi(X_CMD.GetCmd(3).c_str()), X_CMD.GetCmd(4));
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            FAitfX.UpdateAggrSurplus(false);

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
                FAitfX.TransferBalance("广发银行", "余额宝", true, atoi(X_CMD.GetCmd(3).c_str()));
            }
            else if( X_CMD.CmpCmd(2, "--") )
            {
                FAitfX.TransferBalance("广发银行", "余额宝", false, atoi(X_CMD.GetCmd(3).c_str()));
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

            FAitfX.AppendMonth(X_CMD.GetCmd(3));

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

            FAitfX.CheckTempExpense();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

#if 0
        /* * * * * * * * * * * * * * * * * * * * * * */
        //   Verify FileThread线程
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( !X_CMD.GetCmdFront().compare("ve-filet") )
        {
            CFileThread FileVeT = CFileThread("./FA_TVT_VeX.md");

            FileVeT.Start();

            sleep(10);

            FileVeT.InsertLine(8, "THREAD TEST");
            FileVeT.Control();

            sleep(10);

            FileVeT.DeleteLine(8);
            FileVeT.Control();

            sleep(5);

            FileVeT.Join();

            //cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        //   验证多线程同步机制
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( X_CMD.GetCmdFront().compare("ve-mutex") == 0 )
        {   
            CMultiThread mttest_a;
            CMultiThread mttest_b;
            CMultiThread mttest_c;

            mttest_a.Start();
            mttest_b.Start();
            mttest_c.Start();
            
            mttest_a.Join();
            mttest_b.Join();
            mttest_c.Join();

            continue;
        }
#endif

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
