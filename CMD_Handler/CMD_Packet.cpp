
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Packet.h"

#include "DefCMDType.h"
#include "DefCMD.h"


/**************************************************/
//   CMD_Packet 构造函数
/**************************************************/
CMD_Packet::CMD_Packet()
{
    m_str_CmdType = "";

    m_int_PreCmdNum = 0;
    m_vec_PreCmd.clear();
    m_int_CmdNum = 0;
    m_vec_Cmd.clear();

    m_int_ParamValue = 0;
    m_str_ParamMonth = "";
    m_str_ParamSubMonth = "";
    m_str_ParamTitle = "";
    m_str_ParamDate = "";

    m_int_ResParam = 0;
    m_str_ResParam = "";
}

/**************************************************/
//   CMD_Packet 析构函数
/**************************************************/
CMD_Packet::~CMD_Packet()
{
    // Do Nothing
}

/**************************************************/
//   CMD Ripper 预处理
/**************************************************/
int CMD_Packet::CMDRipper(char *CMD_LineBuffer)
{
    m_int_PreCmdNum = 0;
    m_vec_PreCmd.clear();

    const char *delimiters = " ";

    char *CMD_temp = strtok(CMD_LineBuffer, delimiters);
    while( CMD_temp )
    {
        m_int_PreCmdNum++;
        m_vec_PreCmd.push_back(CMD_temp);
        CMD_temp = strtok(NULL, delimiters);
    }

    if( m_int_PreCmdNum == 0 )
    {
        return -1;   // 空行
    }

    return 0;
}

/**************************************************/
//   CMD "" - 格式检查
/**************************************************/
int CMD_Packet::CMDFilter()
{
    m_int_CmdNum = 0;
    m_vec_Cmd.clear();

    vector<string>::iterator itr_PreCmd;
    for(itr_PreCmd = m_vec_PreCmd.begin(); itr_PreCmd != m_vec_PreCmd.end(); itr_PreCmd++)
    {
        char chr_PreCmdFirstLetter = (*itr_PreCmd)[0];
        char chr_PreCmdLastLetter = (*itr_PreCmd)[(*itr_PreCmd).length()-1];

        if(chr_PreCmdFirstLetter != '\"')
        {
            m_vec_Cmd.push_back(*itr_PreCmd);
            m_int_CmdNum++;
        }
        else
        {
            string str_CMDtemp(*itr_PreCmd);

            while(1)
            {
                itr_PreCmd++;
                chr_PreCmdFirstLetter = (*itr_PreCmd)[0];
                chr_PreCmdLastLetter = (*itr_PreCmd)[(*itr_PreCmd).length()-1];

                if(itr_PreCmd == m_vec_PreCmd.end())
                    return -1;   // ERROR: ""内容不完整

                if(chr_PreCmdLastLetter == '\"')
                {
                    str_CMDtemp += " ";
                    str_CMDtemp += *itr_PreCmd;
                    str_CMDtemp.erase(0, 1);
                    str_CMDtemp.erase(str_CMDtemp.length()-1, 1);
                    m_vec_Cmd.push_back(str_CMDtemp);
                    m_int_CmdNum++;
                    break;
                }
                else
                {
                    str_CMDtemp += " ";
                    str_CMDtemp += *itr_PreCmd;
                    continue;
                }
            }
        }
    }

    vector<string>::iterator itr_Cmd;
    for(itr_Cmd = m_vec_Cmd.begin(); itr_Cmd != m_vec_Cmd.end(); itr_Cmd++)
    {
        if((*itr_Cmd).compare(0, 1, "-") == 0)
        {
            if(itr_Cmd == m_vec_Cmd.begin())
            {
                return -11;   // ERROR: 第一个CMD不能为Param
            }

            itr_Cmd++;
            if(itr_Cmd == m_vec_Cmd.end())
            {
                return -12;   // ERROR: Param为空
            }
            else if((*itr_Cmd).compare(0, 1, "-") == 0)
            {
                return -13;   // ERROR: Param为空
            }

            itr_Cmd++;
            if(itr_Cmd == m_vec_Cmd.end())
            {
                return 0;   // CORRECT
            }
            else if((*itr_Cmd).compare(0, 1, "-") != 0)
            {
                return -14;   // ERROR: Param重复
            }
        }
    }

    return 0;   // CORRECT
}

/**************************************************/
//   CMD Type 分析
/**************************************************/
int CMD_Packet::CMDParser()
{
    vector<string>::iterator itr_Cmd;
    for(itr_Cmd = m_vec_Cmd.begin(); itr_Cmd != m_vec_Cmd.end(); itr_Cmd++)
    {
        if((*itr_Cmd) == "-f")
        {
            itr_Cmd++;
            m_int_ParamValue = atoi((*itr_Cmd).c_str());
            continue;
        }
        else if((*itr_Cmd) == "-m")
        {
            itr_Cmd++;
            m_str_ParamMonth = *itr_Cmd;
            continue;
        }
        else if((*itr_Cmd) == "-d")
        {
            itr_Cmd++;
            m_str_ParamDate = *itr_Cmd;
            continue;
        }
        else if((*itr_Cmd) == "-sm")
        {
            itr_Cmd++;
            m_str_ParamSubMonth = *itr_Cmd;
            continue;
        }
        else if((*itr_Cmd) == "-tt")
        {
            itr_Cmd++;
            m_str_ParamTitle = *itr_Cmd;
            continue;
        }
        else if((*itr_Cmd).compare(0, 1, "-") == 0)
        {
            return -1;
        }
    }

    for(itr_Cmd = m_vec_Cmd.begin(); itr_Cmd != m_vec_Cmd.end(); itr_Cmd++)
    {
        if((*itr_Cmd) == TEST)
        {
            if(m_int_CmdNum == 1)
                m_str_CmdType = X_CMD_TYPE_TEST;
        }
    }

    return 0;
}


//------------------------------//
//   River flows in summer
//------------------------------//
