
//------------------------------//
//   Coded by 番茄_summer
//   @20171002
//   @summer studio
//
//   River flows in summer
//------------------------------//

/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

#include "./FileOPer/FileOPer.h"
#include "./Thread/MultiThread.h"


/*--------------------  DEFINE Library  --------------------*/

#define MAX_COMMAND     128      // 命令最大字符数
#define MAX_LINE_CHAR   128     // 每行最大字符数
#define MAX_LINE        256     // 最大支持行数

using namespace std;

/*--------------------  函数声明  --------------------*/

int CMD_Line_Parser(char *CMD_ad_buffer, int &CMD_argc, vector<string> &CMD_argv);
double showtcost(struct timeval tst, struct timeval ted);

/*--------------------  MAIN  --------------------*/

int main(int argc, char **argv, char *env[])
{
    CFileOper FileDemo = CFileOper("./FA_TVT.md");

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
        /* * * * * * * *     demo      * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare("demoaa") == 0 )
        {   
            int lineIndex = 0;
            cout << "LineInedx: ";
            cin >> lineIndex;

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            cout << "File Line: " << FileDemo.GetLine(lineIndex) << endl;

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *     demo      * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare("demobb") == 0 )
        {   
            CMultiThread mttest_a;
            CMultiThread mttest_b;
            mttest_a.Start();
            sleep(1);
            mttest_b.Start();
            mttest_a.Join();
            mttest_b.Join();

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


/*--------------------  CODE_END @ 番茄  --------------------*/


