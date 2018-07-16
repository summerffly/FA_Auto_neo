
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class CMD_Packet
{
public:
    CMD_Packet();
    ~CMD_Packet();

    int CMDRipper(char *CMD_LineBuffer);
    int CMDFilter();
    int CMDParser();

private:
    string m_str_CmdType;          // CMD类型
    
    int m_int_PreCmdNum;           // CMD预处理数量
    vector<string> m_vec_PreCmd;   // CMD预处理内容
    int m_int_CmdNum;              // CMD数量
    vector<string> m_vec_Cmd;      // CMD内容

    int m_int_ParamValue;
    string m_str_ParamMonth;
    string m_str_ParamSubMonth;
    string m_str_ParamTitle;
    string m_str_ParamDate;

    int m_int_ResParam;      // Reserved Param Int
    string m_str_ResParam;   // Reserved Param String
};

//------------------------------//
//   River flows in summer
//------------------------------//
