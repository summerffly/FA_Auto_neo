
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

#include "./X_Frame/DefLib.h"
#include "./FileOPer/FileOPer.h"
#include "./Thread/MultiThread.h"
#include "./Thread/FileThread.h"

using namespace std;


/*--------------------  函数声明  --------------------*/

int CMD_Line_Parser(char *CMD_ad_buffer, int &CMD_argc, vector<string> &CMD_argv);
double showtcost(struct timeval tst, struct timeval ted);

/*--------------------  MAIN  --------------------*/

int main(int argc, char **argv, char *env[])
{
    CFileOper FileVe = CFileOper("./FA_TVT_VeX.md");

    struct timeval tst,ted;

    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |        DEMO for X Project        | |" << endl;
    cout << "| |      >>>  番茄_summer  <<<       | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;

    // advanced_CMD循环模式
    char advanced_CMD[MAX_COMMAND];
    int CMD_argc = 0;
    vector<string> CMD_argv;
    
    while(1)
    {
        cout << "CMD >>> ";
        cin.getline(advanced_CMD, MAX_COMMAND);

        // 判断是否输入空行
        if( CMD_Line_Parser(advanced_CMD, CMD_argc, CMD_argv) == -1 )
        {
            cout << "CMD is blank line !" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }
        
        // 判断是否输入撤销CMD
        if( CMD_argv.back().compare("cancel") == 0 )
        {
            cout << "CMD canceled !" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *    关闭系统    * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        if( CMD_argv.begin()->compare("sd") == 0 )
        {
            cout << "----------------------------------------" << endl;
            cout << "|-----     DEMO for X SHUTDOWN    -----|" << endl;
            cout << "----------------------------------------" << endl;

            break;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        //   Verify FileThread线程
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare("ve-filet") == 0 )
        {   
            CFileThread FileVeT = CFileThread("./FA_TVT_VeXT.md");

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
        else if( CMD_argv.begin()->compare("ve-file") == 0 )
        {   
            //int lineIndex = 0;
            //cout << "LineInedx: ";
            //cin >> lineIndex;

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            FileVe.DeleteLine(8);
            if(FileVe.GetModFlag() == true)
            {
                FileVe.FileWriter("./FA_TVT_VeX.md");
            }

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            //cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        //   验证多线程同步机制
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare("ve-mutex") == 0 )
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

        else
        {
            cout << "----------------------------------------" << endl;
            cout << ">>>             Error CMD            <<<" << endl;
            cout << "----------------------------------------" << endl;

            continue;
        }
    }

    return 0;
}

/*-------------------------------------------------------------------*/
/*--------------------     CMD处理函数 @ 番茄      --------------------*/
/*-------------------------------------------------------------------*/
int CMD_Line_Parser(char *CMD_ad_buffer, int &CMD_argc, vector<string> &CMD_argv)
{
    const char *delimiters = " ";

    CMD_argc = 0;
    CMD_argv.clear();

    char *CMD_temp = strtok(CMD_ad_buffer, delimiters);
    while( CMD_temp )
    {
        CMD_argc++;
        CMD_argv.push_back(CMD_temp);
        CMD_temp = strtok(NULL, delimiters);
    }

    if( CMD_argc == 0 )
    {
        return -1;
    }

    return 0;
}

/*-------------------------------------------------------------------*/
/*--------------------     Time处理函数 @ 番茄     --------------------*/
/*-------------------------------------------------------------------*/
double showtcost(struct timeval tst, struct timeval ted)
{
    long tcost_us;
    double tcost_ms;

    tcost_us = (ted.tv_sec-tst.tv_sec) * 1000000 + ted.tv_usec-tst.tv_usec;
    tcost_ms = (double)tcost_us/1000;

    cout << "STEP TIME COST: " << tcost_ms << " ms" << endl;

    return tcost_ms;
}

//------------------------------//
//   River flows in summer
//------------------------------//
