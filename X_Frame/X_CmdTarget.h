
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


class CCmdTarget
{
public:
    CCmdTarget();
    ~CCmdTarget();

    int CmdParser(char *CMD_buffer);
    int GetCmdNum();
    string GetCmd(const int int_CmdIndex);
    string GetCmdTail();

private:
    int m_int_CmdNum;   // CMD数量
    vector<string> m_vec_Cmd;   // CMD内容

public:
    static struct timeval m_tvl_begin;
    static struct timeval m_tvl_end;
    static double ShowTimeGap();
};

//------------------------------//
//   River flows in summer
//------------------------------//
