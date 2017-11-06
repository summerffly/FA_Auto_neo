
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
#include "./FileOPer/FileOPer.h"
#include "./Thread/MultiThread.h"
#include "./Thread/FileThread.h"

#include "./EP_Layer/LineEPer.h"

#include "./X_Frame/tinyxml2.h"


using namespace std;
using namespace tinyxml2;


int main(int argc, char **argv, char *env[])
{
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |         Verify X Project         | |" << endl;
    cout << "| |      >>>  番茄_summer  <<<       | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;

    CFileOper FileVe = CFileOper("./FA_TVT_VeX.md");
    CFileThread FileVeT = CFileThread("./FA_TVT_VeXT.md");    

    // Advanced_CMD循环模式
    CCmdTarget X_CMD = CCmdTarget();
    char CMD_linebuffer[MAX_COMMAND];
    
    while(1)
    {
        cout << "CMD >>> ";
        cin.getline(CMD_linebuffer, MAX_COMMAND);

        // 判断是否输入空行
        if( X_CMD.CmdParser(CMD_linebuffer) == -1 )
        {
            cout << "### Blank CMD !!!" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }
        
        // 判断是否输入撤销CMD
        if( X_CMD.GetCmdBack().compare("cancel") == 0 )
        {
            cout << "### CMD canceled !" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        //   关闭X工程
        /* * * * * * * * * * * * * * * * * * * * * * */
        if( X_CMD.GetCmdFront().compare("sd") == 0 )
        {
            cout << "----------------------------------------" << endl;            
            cout << "----------------------------------------" << endl;
            cout << "|-----      Verify X SHUTDOWN     -----|" << endl;
            cout << "----------------------------------------" << endl;
            cout << "----------------------------------------" << endl;            

            break;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        //   Verify CLineEPer
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( !X_CMD.GetCmd(0).compare("ve") && !X_CMD.GetCmd(1).compare("line") )
        {   
            CCmdTarget::TagTimeBait();

            cout << "ve line" << endl;

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
        //   Verify file读写类
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( X_CMD.GetCmdFront().compare("ve-file") == 0 )
        {   
            CCmdTarget::TagTimeBait();

            FileVe.DeleteLine(8);
            if(FileVe.GetModFlag() == true)
            {
                FileVe.FileWriter("./FA_TVT_VeX.md");
            }

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

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

        /* * * * * * * * * * * * * * * * * * * * * * */
        //   验证RegEx
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( X_CMD.GetCmdFront().compare("ve-re") == 0 )
        {   
            //CFileOper FileVe = CFileOper("./FA_TVT_VeX.md");
            int lineindex = atoi(X_CMD.GetCmd(1).c_str());
            cout << lineindex << endl;

            CLineEPer LineEPVe = CLineEPer("./FA_TVT_VeX.md", lineindex, FileVe.GetLine(lineindex).c_str());

            cout << LineEPVe.GetLineContent() << endl;

            #if 0
            regex REP("^(`)(\\+|-)( )(\\d{1,})(` )(.{1,})$");
            smatch sm;

            if( regex_match(FileVe.GetLine(1), sm, REP) )
            {
                cout << "string matched" << endl;
                cout << "size: " << sm.size() << endl;
            }

            for(int i = 0; i < sm.size(); i++ )
            {
                cout << sm[i] << endl;
            }
            #endif

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        //   Verify tinyxml2
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( X_CMD.GetCmdFront().compare("ve-xml") == 0 )
        {   
            CCmdTarget::TagTimeBait();

            // 定义一个XMLDocument类指针
            XMLDocument *pDoc = new XMLDocument();
            if (NULL==pDoc)
            {
                return false;
            }

            pDoc->LoadFile("./test.xml");

            pDoc->Print();

            CCmdTarget::ShowTimeGap();
            cout << "----------------------------------------" << endl;

            continue;
        }

        else
        {
            cout << "### Error CMD !!!" << endl;
            cout << "----------------------------------------" << endl;

            continue;
        }
    }

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
