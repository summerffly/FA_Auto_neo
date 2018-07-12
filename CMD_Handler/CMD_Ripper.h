
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

using namespace std;


class CCMDRipper
{
public:
    CCMDRipper();
    ~CCMDRipper();

    int CmdParser(char *CMD_buffer);
    int GetCmdNum();
    string GetCmdFront();
    string GetCmdBack();
    string GetCmd(const int int_CmdIndex);
    int CmpSoloCmd(const string str_CMD);
    int CmpCmdFront(const string str_CMD);
    int CmpCmdBack(const string str_CMD);
    int CmpCmd(const unsigned int int_CmdIndex, const string str_CMD);

private:
    int m_int_CmdNum;           // CMD数量
    vector<string> m_vec_Cmd;   // CMD内容

public:
    static void TagTimeBait();
    static double ShowTimeGap();

private:
    static struct timeval m_tvl_begin;
    static struct timeval m_tvl_end;
};

//------------------------------//
//   River flows in summer
//------------------------------//
