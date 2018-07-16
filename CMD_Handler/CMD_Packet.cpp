
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Packet.h"
#include "DefCMDType.h"


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

int CMD_Packet::CMDFilter()
{
    m_int_CmdNum = 0;
    m_vec_Cmd.clear();

    vector<string>::iterator itr_PreCmd;
    for(itr_PreCmd = m_vec_PreCmd.begin(); itr_PreCmd != m_vec_PreCmd.end(); itr_PreCmd++)
    {
        if((*itr_PreCmd).compare(0, 1, "-") == 0)
        {
            if(itr_PreCmd == m_vec_PreCmd.begin())
            {
                // ERROR: 第一个CMD不能为Param
                return -1;
            }

            itr_PreCmd++;
            if(itr_PreCmd == m_vec_PreCmd.end())
            {
                // ERROR: Param为空
                return -2;
            }
            else if((*itr_PreCmd).compare(0, 1, "-") == 0)
            {
                // ERROR: Param为空
                return -3;
            }

            itr_PreCmd++;
            if(itr_PreCmd == m_vec_PreCmd.end())
            {
                // CORRECT
                return 0;
            }
            else if((*itr_PreCmd).compare(0, 1, "-") != 0)
            {
                // ERROR: Param重复
                return -4;
            }
        }
    }

    // CORRECT
    return 0;
}

int CMD_Packet::CMDParser()
{
    return 0;
}


//------------------------------//
//   River flows in summer
//------------------------------//
