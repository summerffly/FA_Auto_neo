
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Ripper.h"


struct timeval CCMDRipper::m_tvl_begin;
struct timeval CCMDRipper::m_tvl_end;

/**************************************************/
//   CCMDRipper 构造函数
/**************************************************/
CCMDRipper::CCMDRipper()
{
    m_int_CmdNum = 0;
}

/**************************************************/
//   CCMDRipper 析构函数
/**************************************************/
CCMDRipper::~CCMDRipper()
{
    // Do Nothing
}

int CCMDRipper::CmdParser(char *CMD_buffer)
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

int CCMDRipper::GetCmdNum()
{
    return m_int_CmdNum;
}

string CCMDRipper::GetCmdFront()
{
    return m_vec_Cmd.front();
}

string CCMDRipper::GetCmdBack()
{
    return m_vec_Cmd.back();
}

string CCMDRipper::GetCmd(const int int_CmdIndex)
{
    return m_vec_Cmd.at(int_CmdIndex-1);
}

int CCMDRipper::CmpSoloCmd(const string str_CMD)
{
    if( m_int_CmdNum != 1)
    {
        return 0;
    }

    if( m_vec_Cmd.front().compare(str_CMD) == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CCMDRipper::CmpCmdFront(const string str_CMD)
{
    if( m_vec_Cmd.front().compare(str_CMD) == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CCMDRipper::CmpCmdBack(const string str_CMD)
{
    if( m_vec_Cmd.back().compare(str_CMD) == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CCMDRipper::CmpCmd(const unsigned int int_CmdIndex, const string str_CMD)
{
    if( m_vec_Cmd.at(int_CmdIndex-1).compare(str_CMD) == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void CCMDRipper::TagTimeBait()
{
    gettimeofday(&m_tvl_begin, NULL);
}

double CCMDRipper::ShowTimeGap()
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
