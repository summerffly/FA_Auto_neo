
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Packet.h"

#include "DefCMDType.h"
#include "DefCMD.h"
#include "./../XML_Ripper/Script_Ripper.h"


/**************************************************/
//   CMD_Packet 构造函数
/**************************************************/
CMD_Packet::CMD_Packet()
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    m_str_CmdType = "";

    m_int_PreCmdNum = 0;
    m_vec_PreCmd.clear();
    m_int_CmdNum = 0;
    m_int_CmdProNum = 0;
    m_vec_Cmd.clear();

    m_int_ParamValue = 0;
    m_str_ParamMonth = ptr_ScriptRipper->GetCurrentMonth();
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
        return -1;   // Blank Line Buffer
    }

    return 0;
}

/**************************************************/
//   CMD "" & - 格式检查
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

            continue;
        }
        else
        {
            string str_CMDtemp(*itr_PreCmd);

            if(chr_PreCmdLastLetter == '\"')
            {
                if(str_CMDtemp.length()<3)
                    return -1;   // ERROR: ""内容不完整

                str_CMDtemp.erase(0, 1);
                str_CMDtemp.erase(str_CMDtemp.length()-1, 1);

                m_vec_Cmd.push_back(str_CMDtemp);
                m_int_CmdNum++;

                continue;
            }
            else
            {
                while(1)
                {
                    itr_PreCmd++;
                    if(itr_PreCmd == m_vec_PreCmd.end())
                        return -1;   // ERROR: ""内容不完整

                    chr_PreCmdFirstLetter = (*itr_PreCmd)[0];
                    chr_PreCmdLastLetter = (*itr_PreCmd)[(*itr_PreCmd).length()-1];

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
    m_int_CmdProNum = m_int_CmdNum;
    int int_ParamType = 0;

    vector<string>::iterator itr_Cmd;
    for(itr_Cmd = m_vec_Cmd.begin(); itr_Cmd != m_vec_Cmd.end(); itr_Cmd++)
    {
        if((*itr_Cmd) == "-f")
        {
            itr_Cmd++;
            m_int_ParamValue = atoi((*itr_Cmd).c_str());
            m_int_CmdProNum -= 2;

            continue;
        }
        else if((*itr_Cmd) == "-m")
        {
            itr_Cmd++;
            m_str_ParamMonth = *itr_Cmd;
            m_int_CmdProNum -= 2;

            CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
            if( !ptr_ScriptRipper->IsIncludeMonthRange(m_str_ParamMonth) )
                return -3;

            continue;
        }
        else if((*itr_Cmd) == "-d")
        {
            itr_Cmd++;
            m_str_ParamDate = *itr_Cmd;
            m_int_CmdProNum -= 2;

            continue;
        }
        else if((*itr_Cmd) == "-sm")
        {
            itr_Cmd++;
            m_str_ParamSubMonth = *itr_Cmd;
            m_int_CmdProNum -= 2;

            if(int_ParamType == 0)
                int_ParamType = 1;
            else
                return -2;   // ERROR: Param冲突

            continue;
        }
        else if((*itr_Cmd) == "-tt")
        {
            itr_Cmd++;
            m_str_ParamTitle = *itr_Cmd;
            m_int_CmdProNum -= 2;

            if(int_ParamType == 0)
                int_ParamType = 2;
            else
                return -2;   // ERROR: Param冲突

            continue;
        }
        else if((*itr_Cmd) == "-ip")
        {
            itr_Cmd++;
            m_int_ResParam = atoi((*itr_Cmd).c_str());
            m_int_CmdProNum -= 2;
            
            continue;
        }
        else if((*itr_Cmd) == "-sp")
        {
            itr_Cmd++;
            m_str_ResParam = *itr_Cmd;
            m_int_CmdProNum -= 2;
            
            continue;
        }
        else if((*itr_Cmd).compare(0, 1, "-") == 0)
        {
            return -1;   // ERROR: 未定义的Param
        }
    }

    // tips 番茄@20180719 - 最大支持3个CmdPro
    string str_CmdPro_A("");
    string str_CmdPro_B("");
    string str_CmdPro_C("");

    str_CmdPro_A = m_vec_Cmd.at(0);
    if(m_int_CmdProNum == 2)
        str_CmdPro_B = m_vec_Cmd.at(1);
    if(m_int_CmdProNum == 3)
        str_CmdPro_C = m_vec_Cmd.at(2);

    if((m_int_CmdProNum == 1) && (int_ParamType == 0))
    {
        if(str_CmdPro_A == CHECK)
            m_str_CmdType = X_CMD_TYPE_CHECK_FA;
        else if(str_CmdPro_A == UPDATE)
            m_str_CmdType = X_CMD_TYPE_UPDATE_FA;
        else if(str_CmdPro_A == SHOW)
            m_str_CmdType = X_CMD_TYPE_SHOW_FA;
        else if(str_CmdPro_A == SYNC)
            m_str_CmdType = X_CMD_TYPE_SYNC;
        else if(str_CmdPro_A == WRITE)
            m_str_CmdType = X_CMD_TYPE_WRITE;
        else if(str_CmdPro_A == FORECAST)
            m_str_CmdType = X_CMD_TYPE_FORECAST;
        else if(str_CmdPro_A == BACKUP)
            m_str_CmdType = X_CMD_TYPE_BACKUP;
        else if(str_CmdPro_A == CANCEL)
            m_str_CmdType = X_CMD_TYPE_CANCEL;
        else if(str_CmdPro_A == EXIT)
            m_str_CmdType = X_CMD_TYPE_EXIT;
        else if(str_CmdPro_A == TEST)
            m_str_CmdType = X_CMD_TYPE_TEST;
        else
            return -4;   // ERROR: 未定义的CmdType
    }
    else if((m_int_CmdProNum == 1) && (int_ParamType > 0))
    {
        if((str_CmdPro_A == CHECK) && (int_ParamType = 1))
            m_str_CmdType = X_CMD_TYPE_CHECK_SUBMONTH;
        else if((str_CmdPro_A == UPDATE) && (int_ParamType = 1))
            m_str_CmdType = X_CMD_TYPE_UPDATE_SUBMONTH;
        else
            return -4;   // ERROR: 未定义的CmdType
    }
    else if(m_int_CmdProNum == 2)
    {
        if((str_CmdPro_A == CHECK) && (str_CmdPro_B == MONTH))
            m_str_CmdType = X_CMD_TYPE_CHECK_MONTH;
        else if((str_CmdPro_A == UPDATE) && (str_CmdPro_B == MONTH))
            m_str_CmdType = X_CMD_TYPE_UPDATE_MONTH;
        else if((str_CmdPro_A == SHOW) && (str_CmdPro_B == MONTH))
            m_str_CmdType = X_CMD_TYPE_SHOW_MONTH;
        else
            return -4;   // ERROR: 未定义的CmdType
    }
    else if(m_int_CmdProNum == 3)
    {
        //
    }

    return 0;   // CORRECT
}


//------------------------------//
//   River flows in summer
//------------------------------//
