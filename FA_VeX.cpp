
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
#include "./X_Frame/X_CmdTarget.h"
#include "./X_Frame/X_XMLParser.h"

#include "./OP_Layer/FileOPer.h"
#include "./EP_Layer/LineEPer.h"
#include "./EP_Layer/FileManager.h"
#include "./FA_Layer/FAitfX.h"

#include "./Thread/MultiThread.h"
#include "./Thread/FileThread.h"

using namespace std;


int main(int argc, char **argv, char *env[])
{
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |         Verify X Project         | |" << endl;
    cout << "| |      >>>  番茄_summer  <<<       | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;

    CFileOPer FileVe = CFileOPer("./FA_TVT_VeX.md");
    CFileManager FileManagerVe = CFileManager("./FA_TVT_VeX.md");
    CFAitfX FAitfX = CFAitfX();

    CFileThread FileVeT = CFileThread("./FA_TVT_VeXT.md");

    // Advanced_CMD循环模式
    CCmdTarget X_CMD = CCmdTarget();
    char CMD_linebuffer[MAX_COMMAND];
    
    while(1)
    {
        cout << "CMD >>> ";
        cin.getline(CMD_linebuffer, MAX_COMMAND);

        /**************************************************/
        //   判断是否输入空行
        /**************************************************/
        if( X_CMD.CmdParser(CMD_linebuffer) == -1 )
        {
            cout << "### Blank CMD !!!" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }
        
        /**************************************************/
        //   判断是否输入撤销CMD
        /**************************************************/
        if( X_CMD.GetCmdBack().compare("cancel") == 0 )
        {
            cout << "### CMD canceled !" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }

        /**************************************************/
        //   关闭X工程
        /**************************************************/
        if( X_CMD.GetCmdFront().compare("sd") == 0 )
        {
            cout << "----------------------------------------" << endl;            
            cout << "----------------------------------------" << endl;
            cout << "|-----      Verify X SHUTDOWN     -----|" << endl;
            cout << "----------------------------------------" << endl;
            cout << "----------------------------------------" << endl;            

            break;
        }

        /**************************************************/
        //   Verify FileOPer
        /**************************************************/
        else if( X_CMD.GetCmdFront().compare("ve-file") == 0 )
        {   
            CCmdTarget::TagTimeBait();

            CFileOPer FileVeV = CFileOPer("./FileTest/FileTestTest/FA_TVT_VeX.md");

            cout << FileVeV.GetFilePath() << endl;
            cout << FileVeV.GetFileName() << endl;

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Verify LineEPer
        /**************************************************/
        else if( X_CMD.GetCmdFront().compare("ve-line") == 0 )
        {
            CCmdTarget::TagTimeBait();

            int lineindex = atoi(X_CMD.GetCmd(1).c_str());

            CLineEPer LineEPVe = CLineEPer(FileVe.GetLine(lineindex).c_str());

            cout << LineEPVe.GetFullLine() << endl;

            LineEPVe.SetLineValue(-888);
            LineEPVe.UpdateFullLine();

            FileVe.ModifyLine(lineindex, LineEPVe.GetFullLine());
            FileVe.FileWriter();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Verify FileManager
        /**************************************************/
        else if( X_CMD.GetCmdFront().compare("ve-fm") == 0 )
        {
            CCmdTarget::TagTimeBait();

            // 验证搜索操作
            //cout << FileManagerVe.SearchLineKey(X_CMD.GetCmd(1).c_str()) << endl;
            //cout << FileManagerVe.GetSearchLine(atoi(X_CMD.GetCmd(2).c_str())) << endl;

            #if 0   // 验证同步修改操作
            if(1 == atoi(X_CMD.GetCmd(1).c_str()))
            {
                FileManagerVe.InsertLine(4, 14, -1129, "fm-test");
            }
            else if(2 == atoi(X_CMD.GetCmd(1).c_str()))
            {
                FileManagerVe.ModifyLineValue(4, 998);
            }
            else if(3 == atoi(X_CMD.GetCmd(1).c_str()))
            {
                FileManagerVe.DeleteLine(4);
            }

            FileManagerVe.FileWriter();
            #endif

            // 验证计算操作
            CFileManager FMve = CFileManager("./life.M.md");

            FMve.SearchLineKey("## life.M11");
            int begin_index = FMve.GetSearchLineIndex(1) + 4;

            FMve.SearchLineKey("## life.M12");
            int end_index = FMve.GetSearchLineIndex(1) - 1;

            cout << FMve.CountRange(begin_index, end_index) << endl;

            //FileManagerVe.FileWriter();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Verify FAitfX
        /**************************************************/
        else if( X_CMD.GetCmdFront().compare("ve-itfx") == 0 )
        {
            CCmdTarget::TagTimeBait();

            // 

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   Verify tinyxml2
        /**************************************************/
        else if( X_CMD.GetCmdFront().compare("ve-xml") == 0 )
        {   
            CCmdTarget::TagTimeBait();

            CXMLParser xml_ve("./FA_script_Ve.xml");
            //xml_ve.InsertElement();
            //xml_ve.ModifyElement();
            //cout << xml_ve.QueryElementL1Index(X_CMD.GetCmd(1), atoi(X_CMD.GetCmd(2).c_str())) << endl;
            cout << xml_ve.QueryElementL1Attribute(X_CMD.GetCmd(1), X_CMD.GetCmd(2), X_CMD.GetCmd(3)) << endl;
            //cout << xml_ve.QueryElementL2(X_CMD.GetCmd(1), X_CMD.GetCmd(2), atoi(X_CMD.GetCmd(3).c_str())) << endl;
            //xml_ve.PrintXML();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        //   Verify FileThread线程
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( !X_CMD.GetCmdFront().compare("ve-filet") )
        {
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
//   river flows in summer
//------------------------------//
