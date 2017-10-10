
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "X_CmdTarget.h"


struct timeval CCmdTarget::m_tvl_begin;
struct timeval CCmdTarget::m_tvl_end;

CCmdTarget::CCmdTarget()
{
    m_int_CmdNum = 0;
}

CCmdTarget::~CCmdTarget()
{
    // Do Nothing
}

int CCmdTarget::CmdParser(char *CMD_buffer)
{
    m_int_CmdNum = 0;
    m_vec_Cmd.clear();

    const char *delimiters = " ";

    char *CMD_temp = strtok(CMD_buffer, delimiters);
    while( CMD_temp )
    {
        m_int_CmdNum++;
        m_vec_Cmd.push_back(CMD_temp);
        CMD_temp = strtok(NULL, delimiters);
    }

    if( m_int_CmdNum == 0 )
    {
        return -1;
    }

    return 0;
}

int CCmdTarget::GetCmdNum()
{
    return m_int_CmdNum;
}

string CCmdTarget::GetCmd(const int int_CmdIndex)
{
    return m_vec_Cmd.at(int_CmdIndex);
}

string CCmdTarget::GetCmdFront()
{
    return m_vec_Cmd.front();
}

string CCmdTarget::GetCmdBack()
{
    return m_vec_Cmd.back();
}

void CCmdTarget::TagTimeBait()
{
    gettimeofday(&m_tvl_begin, NULL);
}

double CCmdTarget::ShowTimeGap()
{
    gettimeofday(&m_tvl_end, NULL);

    long tgap_us;
    double tgap_ms;

    tgap_us = (m_tvl_end.tv_sec - m_tvl_begin.tv_sec) * 1000000 + m_tvl_end.tv_usec - m_tvl_begin.tv_usec;
    tgap_ms = (double)tgap_us/1000;

    cout << "CMD_TIME_GAP: " << tgap_ms << " ms" << endl;

    return tgap_ms;
}


//------------------------------//
//   River flows in summer
//------------------------------//
