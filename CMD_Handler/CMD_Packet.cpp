
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
    m_int_ParamLine = 0;

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

    vector<string>::iterator itr_Cmd = m_vec_Cmd.begin();
    if((*itr_Cmd).compare(0, 1, "-") == 0)
        return -2;   // ERROR: 第一个CMD不能为Param

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
    itr_Cmd = m_vec_Cmd.end();
    if((*(--itr_Cmd)) == CANCEL)
    {
        m_str_CmdType = X_CMD_TYPE_CANCEL;
        return 0;   // CANCEL CORRECT
    }

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
        else if((*itr_Cmd) == "-l")
        {
            itr_Cmd++;
            m_int_ParamLine = atoi((*itr_Cmd).c_str());
            m_int_CmdProNum -= 2;

            int_ParamType = 3;

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

    if(str_CmdPro_A == TEST)
    {
        m_str_CmdType = X_CMD_TYPE_TEST;
        return 0;
    }

    if((m_int_CmdProNum == 1) && (int_ParamType == 0))
    {
        if(str_CmdPro_A == CHECK)
            m_str_CmdType = X_CMD_TYPE_CHECK_FA;
        else if(str_CmdPro_A == UPDATE)
            m_str_CmdType = X_CMD_TYPE_UPDATE_FA;
        else if(str_CmdPro_A == SHOW)
            m_str_CmdType = X_CMD_TYPE_SHOW_FA;
        else if(str_CmdPro_A == MODIFY_LIFE)
            m_str_CmdType = X_CMD_TYPE_MODIFY_LIFE;
        else if(str_CmdPro_A == TRANSFER)
            m_str_CmdType = X_CMD_TYPE_TRANSFER;
        else if(str_CmdPro_A == LOTTERY)
            m_str_CmdType = X_CMD_TYPE_LOTTERY;
        else if(str_CmdPro_A == SUMMARIZE)
            m_str_CmdType = X_CMD_TYPE_SUMMARIZE;
        else if(str_CmdPro_A == FORECAST)
            m_str_CmdType = X_CMD_TYPE_FORECAST;
        else if(str_CmdPro_A == SYNC)
            m_str_CmdType = X_CMD_TYPE_SYNC;
        else if(str_CmdPro_A == WRITE)
            m_str_CmdType = X_CMD_TYPE_WRITE;
        else if(str_CmdPro_A == BACKUP)
            m_str_CmdType = X_CMD_TYPE_BACKUP;
        else if(str_CmdPro_A == HELP)
            m_str_CmdType = X_CMD_TYPE_HELP;
        else if(str_CmdPro_A == CANCEL)
            m_str_CmdType = X_CMD_TYPE_CANCEL;
        else if(str_CmdPro_A == EXIT)
            m_str_CmdType = X_CMD_TYPE_EXIT;
        else
            return -4;   // ERROR: 未定义的CmdType
    }
    else if((m_int_CmdProNum == 1) && (int_ParamType > 0))
    {
        if((str_CmdPro_A == CHECK) && (int_ParamType == 1))
            m_str_CmdType = X_CMD_TYPE_CHECK_SUBMONTH;
        else if((str_CmdPro_A == UPDATE) && (int_ParamType == 1))
            m_str_CmdType = X_CMD_TYPE_UPDATE_SUBMONTH;
        else if((str_CmdPro_A == SHOW) && (int_ParamType == 1))
            m_str_CmdType = X_CMD_TYPE_SHOW_SUBMONTH;
        else if((str_CmdPro_A == CHECK) && (int_ParamType == 2))
            m_str_CmdType = X_CMD_TYPE_CHECK_TITLE;
        else if((str_CmdPro_A == UPDATE) && (int_ParamType == 2))
            m_str_CmdType = X_CMD_TYPE_UPDATE_TITLE;
        else if((str_CmdPro_A == SHOW) && (int_ParamType == 2))
            m_str_CmdType = X_CMD_TYPE_SHOW_TITLE;
        else if((str_CmdPro_A == PRINT) && (int_ParamType == 1))
            m_str_CmdType = X_CMD_TYPE_PRINT_SUBMONTH;
        else if((str_CmdPro_A == PRINT) && (int_ParamType == 2))
            m_str_CmdType = X_CMD_TYPE_PRINT_TITLE;
        else if((str_CmdPro_A == INSERT) && (int_ParamType == 3))
            m_str_CmdType = X_CMD_TYPE_INSERT_LINE;
        else if((str_CmdPro_A == MODIFY) && (int_ParamType == 3))
            m_str_CmdType = X_CMD_TYPE_MODIFY_LINE;
        else if((str_CmdPro_A == COPY) && (int_ParamType == 3))
            m_str_CmdType = X_CMD_TYPE_COPY_LINE;
        else if((str_CmdPro_A == MOVE) && (int_ParamType == 3))
            m_str_CmdType = X_CMD_TYPE_MOVE_LINE;
        else if((str_CmdPro_A == DELETE) && (int_ParamType == 3))
            m_str_CmdType = X_CMD_TYPE_DELETE_LINE;
        else
            return -4;   // ERROR: 未定义的CmdType
    }
    else if(m_int_CmdProNum == 2)
    {
        if((str_CmdPro_A == CHECK) && (str_CmdPro_B == SUM))
            m_str_CmdType = X_CMD_TYPE_CHECK_SUM;
        else if((str_CmdPro_A == UPDATE) && (str_CmdPro_B == SUM))
            m_str_CmdType = X_CMD_TYPE_UPDATE_SUM;
        else if((str_CmdPro_A == SHOW) && (str_CmdPro_B == SUM))
            m_str_CmdType = X_CMD_TYPE_SHOW_SUM;
        else if((str_CmdPro_A == CHECK) && (str_CmdPro_B == MONTH))
            m_str_CmdType = X_CMD_TYPE_CHECK_MONTH;
        else if((str_CmdPro_A == UPDATE) && (str_CmdPro_B == MONTH))
            m_str_CmdType = X_CMD_TYPE_UPDATE_MONTH;
        else if((str_CmdPro_A == SHOW) && (str_CmdPro_B == MONTH))
            m_str_CmdType = X_CMD_TYPE_SHOW_MONTH;
        else if((str_CmdPro_A == ANALYSIS) && (str_CmdPro_B == TREND))
            m_str_CmdType = X_CMD_TYPE_ANALYSIS_TREND;
        else if((str_CmdPro_A == ANALYSIS) && (str_CmdPro_B == PROPORTION))
            m_str_CmdType = X_CMD_TYPE_ANALYSIS_PROPORTION;
        else if((str_CmdPro_A == PRINT) && (str_CmdPro_B == SUM))
            m_str_CmdType = X_CMD_TYPE_PRINT_SUM;
        else if((str_CmdPro_A == PRINT) && (str_CmdPro_B == MONTH))
            m_str_CmdType = X_CMD_TYPE_PRINT_MONTH;
        else if((str_CmdPro_A == APPEND) && (str_CmdPro_B == MONTH))
            m_str_CmdType = X_CMD_TYPE_APPEND_MONTH;
        else if((str_CmdPro_A == INSERT) && (str_CmdPro_B == BLANK))
            m_str_CmdType = X_CMD_TYPE_INSERT_BLANK_LINE;
        else if((str_CmdPro_A == CHECK) && (str_CmdPro_B == EQUAL))
            m_str_CmdType = X_CMD_TYPE_CHECK_EQUAL;
        else
            return -4;   // ERROR: 未定义的CmdType
    }
    else if(m_int_CmdProNum == 3)
    {
        // Reserved CMD Pro
        return -4;   // ERROR: 未定义的CmdType
    }

    return 0;   // CORRECT
}

/**************************************************/
//   CMD Param 检查
/**************************************************/
int CMD_Packet::CMDParamChecker()
{
    if("" != m_str_ParamSubMonth)
    {
        if(DGTLER == m_str_ParamSubMonth)
            return 0;
        else if(BOOKS == m_str_ParamSubMonth)
            return 0;
        else if(KEEP == m_str_ParamSubMonth)
            return 0;
        else if(TB == m_str_ParamSubMonth)
            return 0;
        else if(SA == m_str_ParamSubMonth)
            return 0;
        else if(ALL == m_str_ParamSubMonth)
            return 0;
        else
            return -1;
    }

    if("" != m_str_ParamTitle)
    {
        if(DK == m_str_ParamTitle)
            return 0;
        else if(NS == m_str_ParamTitle)
            return 0;
        else if(TRAVEL == m_str_ParamTitle)
            return 0;
        else if(LOTTERY == m_str_ParamTitle)
            return 0;
        else
            return -2;
    }

    return 0;
}


//------------------------------//
//   River flows in summer
//------------------------------//
