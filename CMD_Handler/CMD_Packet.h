
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct CMD_Packet
{
public:
    CMD_Packet();
    ~CMD_Packet();

    int CMDRipper(char *CMD_LineBuffer);
    int CMDFilter();
    int CMDParser();

public:
    string m_str_CmdType;          // CMD类型
    
    int m_int_PreCmdNum;           // CMD预处理数量
    vector<string> m_vec_PreCmd;   // CMD预处理内容
    int m_int_CmdNum;              // CMD数量
    int m_int_CmdProNum;           // CMD主数量
    vector<string> m_vec_Cmd;      // CMD内容

    int m_int_ParamValue;         // -f
    string m_str_ParamMonth;      // -m
    string m_str_ParamDate;       // -d
    string m_str_ParamSubMonth;   // -sm
    string m_str_ParamTitle;      // -tt
    int m_int_ParamLine;          // -l

    int m_int_ResParam;      // -ip
    string m_str_ResParam;   // -sp
};

//------------------------------//
//   River flows in summer
//------------------------------//
