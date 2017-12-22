
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

    //CFileOPer FileVe = CFileOPer("./FA_TVT_VeX.md");
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
        if( X_CMD.CmpCmdBack(EXIT) )
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
        //   CMD >>> sync file
        /**************************************************/
        else if( X_CMD.CmpCmdFront(SYNC) && X_CMD.CmpCmdBack(MDFILE) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.SyncAllFile();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   写回 所有.md
        //   CMD >>> write file
        /**************************************************/
        else if( X_CMD.CmpCmdFront(WRITE) && X_CMD.CmpCmdBack(MDFILE) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.WriteAllFile();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   备份 所有.md
        //   CMD >>> write file
        /**************************************************/
        else if( X_CMD.CmpCmdFront(BACKUP) && X_CMD.CmpCmdBack(MDFILE) )
        {   
            CCmdTarget::TagTimeBait();

            FAitfX.BackUpAllFile("./bakup/");

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

            FAitfX.CheckAggrSurplus();

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

            FAitfX.UpdateAggrSurplus();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 当月/上月 支出
        //   CMD >>> check expense month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmd(2, EXPENSE) &&\
                 ( X_CMD.CmpCmd(3, MONTH) || X_CMD.CmpCmd(3, EX_MONTH) ) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmd(3, MONTH) )
            {
                FAitfX.CheckMonthExpense(CCFGLoader::m_str_CurrentMonth);
            }
            else if( X_CMD.CmpCmd(3, EX_MONTH) )
            {
                FAitfX.CheckMonthExpense(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth));
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   校验 当月/上月 收支
        //   CMD >>> check surplus month/exmonth
        /**************************************************/
        else if( X_CMD.CmpCmdFront(CHECK) && X_CMD.CmpCmd(2, SURPLUS) &&\
                 ( X_CMD.CmpCmd(3, MONTH) || X_CMD.CmpCmd(3, EX_MONTH) ) )
        {   
            CCmdTarget::TagTimeBait();

            if( X_CMD.CmpCmd(3, MONTH) )
            {
                FAitfX.CheckMonthSurplus(CCFGLoader::m_str_CurrentMonth);
            }
            else if( X_CMD.CmpCmd(3, EX_MONTH) )
            {
                FAitfX.CheckMonthSurplus(CTool::GeneratePreMonth(CCFGLoader::m_str_CurrentMonth));
            }

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
                FAitfX.AppendLottery(true, atoi(X_CMD.GetCmd(3).c_str()), X_CMD.GetCmd(4));
            }
            else if( X_CMD.CmpCmd(2, "--") )
            {
                FAitfX.AppendLottery(false, atoi(X_CMD.GetCmd(3).c_str()), X_CMD.GetCmd(4));
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << "!!!            Error Param           !!!" << endl;
                cout << "----------------------------------------" << endl;
            }

            FAitfX.UpdateAggrSurplus();

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
