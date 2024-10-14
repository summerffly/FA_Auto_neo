
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <cstring>
// add 番茄@20200218 - macOS头文件，不可移植性，最小包含原则
#include <mach-o/dyld.h>
#include "X_Tool.h"

using namespace std;


string CTool::ms_str_ExecutablePath;

string CTool::ms_str_OriginMonth;
string CTool::ms_str_CurrentMonth;

struct timeval CTool::m_tvl_begin;
struct timeval CTool::m_tvl_end;


CTool::CTool()
{
    // add 番茄@20211105
    // 程序最早入口点
	// 全局/静态变量初始化

    uint32_t uni_size = 0;
    char *buf = NULL;
    // add 番茄@20210210 - macOS接口
    _NSGetExecutablePath(buf, &uni_size);

    char *p_cha_exefullpath = (char *)malloc(uni_size+1);
    _NSGetExecutablePath(p_cha_exefullpath, &uni_size);

    char *p_cha_exefilename = strrchr(p_cha_exefullpath, '/');
    string str_ExeFile = p_cha_exefilename;
    int int_exelength = str_ExeFile.size() - 1;

    ms_str_ExecutablePath = string(p_cha_exefullpath);
    ms_str_ExecutablePath.erase(ms_str_ExecutablePath.end()-int_exelength, ms_str_ExecutablePath.end());

    // add 番茄@20200218 - macOS/Unix/Linux通用接口
    chdir(ms_str_ExecutablePath.c_str());

    free(p_cha_exefullpath);
}

CTool::~CTool()
{
    // Do Nothing
}

void CTool::SetExecutablePath()
{
    uint32_t uni_size = 0;
    char *buf = NULL;
    // add 番茄@20210210 - macOS接口
    _NSGetExecutablePath(buf, &uni_size);

    char *p_cha_exefullpath = (char *)malloc(uni_size+1);
    _NSGetExecutablePath(p_cha_exefullpath, &uni_size);

    char *p_cha_exefilename = strrchr(p_cha_exefullpath, '/');
    string str_ExeFile = p_cha_exefilename;
    int int_exelength = str_ExeFile.size() - 1;

    ms_str_ExecutablePath = string(p_cha_exefullpath);
    ms_str_ExecutablePath.erase(ms_str_ExecutablePath.end()-int_exelength, ms_str_ExecutablePath.end());

    // add 番茄@20200218 - macOS/Unix/Linux通用接口
    chdir(ms_str_ExecutablePath.c_str());

    free(p_cha_exefullpath);
}

int CTool::CheckFilesExist(vector<string> vec_str_FilePath)
{
    int int_RetFC = 0;

    vector<string>::iterator itr_FilePath;
    for(itr_FilePath = vec_str_FilePath.begin(); itr_FilePath != vec_str_FilePath.end(); itr_FilePath++)
    {
        string str_File = ms_str_ExecutablePath;
        str_File += *itr_FilePath;
        //string str_File = *itr_FilePath;
        int_RetFC += access(str_File.c_str(), 0);
    }

    return int_RetFC;
}

/**************************************************/
//   Month 格式校验
//   最大月度支持到 24 个月
/**************************************************/
bool CTool::ParseMonth(const string str_Input)
{
    smatch str_Match;
    regex REP_Month("^(\\d{2})(n*)$");

    if( regex_match(str_Input, str_Match, REP_Month) )
    {
        string str_Month = str_Match[1];
        int int_Month = atoi(str_Month.c_str());

        if((int_Month>0) && (int_Month<=12))
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

/**************************************************/
//   Month 数串转换生成
/**************************************************/
string CTool::GenerateMonthString(const int int_Month)
{
    char *cha_Month = new char[3];

    if(int_Month < 10)
        snprintf(cha_Month, sizeof(cha_Month), "0%d", int_Month);
    else
        snprintf(cha_Month, sizeof(cha_Month), "%d", int_Month);

    // update summer@20211029
    // it works in OS Big Sur
    // but not work in OS Monterey
    // Apple changed Memory-Management-Mechanism
    //delete []cha_Month;
    string str_Month(cha_Month);
    delete []cha_Month;

    return str_Month;
}

/**************************************************/
//   Month 串数转换生成
/**************************************************/
int CTool::GenerateMonthInt(const string str_Month)
{
    smatch str_Match;
    regex REP_Month("^(\\d{2})(n*)$");

    if( regex_match(str_Month, str_Match, REP_Month) )
    {
        string str_Month = str_Match[1];
        int int_Month = atoi(str_Month.c_str());

        if((int_Month>0) && (int_Month<=12))
            return int_Month;
        else
            return 0;
    }
    else
    {
        return 0;
    }
}

/**************************************************/
//   生成 Next Month
//   最大月度支持到 24 个月
/**************************************************/
string CTool::GenerateNextMonth(const string str_CurMonth)
{
    string str_NextMonth = string("");

    if( !ParseMonth(str_CurMonth) )
    {
        MassageOutFotmat("Invalid Month Input", '!');
        return str_NextMonth;
    }

    smatch str_Match;
    regex REP_Month("^(\\d{2})(n*)$");

    if( regex_match(str_CurMonth, str_Match, REP_Month) )
    {
        string str_Month = str_Match[1];
        string str_nFlag = str_Match[2];

        unsigned int uni_CurMonth = atoi(str_CurMonth.c_str());

        switch(uni_CurMonth)
        {
            case 12:
                str_NextMonth += "01";
                break;
            default:
                int int_NextMonth = uni_CurMonth+1;
                str_NextMonth += GenerateMonthString(int_NextMonth);
                break;
        }

        if( str_nFlag == "n" )
        {
            str_NextMonth += "n";
        }

        if( str_NextMonth == ms_str_OriginMonth )
        {
            str_NextMonth += "n";
        }
    }
    else
    {
        MassageOutFotmat("Invalid Month Input", '!');
        return str_NextMonth;
    }

    return str_NextMonth;
}

/**************************************************/
//   生成 Pre Month
//   最大月度支持到 24 个月
/**************************************************/
string CTool::GeneratePreMonth(const string str_CurMonth)
{
    string str_PreMonth = string("");

    if( !ParseMonth(str_CurMonth) )
    {
        MassageOutFotmat("Invalid Month Input", '!');
        return str_PreMonth;
    }

    smatch str_Match;
    regex REP_Month("^(\\d{2})(n*)$");

    if( regex_match(str_CurMonth, str_Match, REP_Month) )
    {
        string str_Month = str_Match[1];
        string str_nFlag = str_Match[2];

        unsigned int uni_CurMonth = atoi(str_CurMonth.c_str());

        switch(uni_CurMonth)
        {
            case 1:
                str_PreMonth += "12";
                break;
            default:
                int int_PreMonth = uni_CurMonth-1;
                str_PreMonth += GenerateMonthString(int_PreMonth);
                break;
        }

        string str_nOriginMonth = ms_str_OriginMonth + "n";
        if( str_CurMonth == str_nOriginMonth )
        {
            return str_PreMonth;
        }

        if( str_nFlag == "n" )
        {
            str_PreMonth += "n";
        }
    }
    else
    {
        MassageOutFotmat("Invalid Month Input", '!');
        return str_PreMonth;
    }

    return str_PreMonth;
}

/**************************************************/
//   Month Counter
//   最大月度支持到 (24-1) 个月
/**************************************************/
unsigned int CTool::CountMonth(const string str_OriMonth, const string str_CurMonth)
{
    smatch str_OriMatch;
    smatch str_CurMatch;

    string str_nOriFlag;
    string str_nCurFlag;

    regex REP_Month("^(\\d{2})(n*)$");

    if( regex_match(str_OriMonth, str_OriMatch, REP_Month) )
        str_nOriFlag = str_OriMatch[2];

    if( regex_match(str_CurMonth, str_CurMatch, REP_Month) )
        str_nCurFlag = str_OriMatch[2];

    int int_MonthCounter = 0;
    
    int_MonthCounter = atoi(str_CurMonth.c_str()) - atoi(str_OriMonth.c_str()) + 1;

    if(int_MonthCounter<0)
        int_MonthCounter += 12;

    if( (str_nCurFlag == "n") && (str_nOriFlag != "n") )
        int_MonthCounter += 12;

    return (unsigned int)int_MonthCounter;
}

string CTool::TransOutFormat(const int int_Value)
{
    string str_OutValue = string("");
    char *cha_OutValue = new char[9];     // tips 番茄@20171205 - 支持到百万级

    if(int_Value > 0)
    {
        snprintf(cha_OutValue, sizeof(cha_OutValue), "+%d", int_Value);
        str_OutValue += cha_OutValue;
    }
    else
    {
        snprintf(cha_OutValue, sizeof(cha_OutValue), "%d", int_Value);
        str_OutValue += cha_OutValue;
    }

    delete []cha_OutValue;
    return str_OutValue;
}

void CTool::MassageOutFotmat(const string str_Message, const char cha_Flag)
{
    // X长度40个ASCII字符

    unsigned int uni_MseeageLength = str_Message.size();
    unsigned int uni_MessageBeLength = (40-6-uni_MseeageLength)/2;
    unsigned int uni_MessageAfLength = 40-6-uni_MessageBeLength-uni_MseeageLength;

    cout << "----------------------------------------" << endl;
    cout << cha_Flag << cha_Flag << cha_Flag;
    while( uni_MessageBeLength>0 )
    {
        cout << " ";
        uni_MessageBeLength--;
    }

    cout << str_Message;

    while( uni_MessageAfLength>0 )
    {
        cout << " ";
        uni_MessageAfLength--;
    }
    cout << cha_Flag << cha_Flag << cha_Flag << endl;
    cout << "----------------------------------------" << endl;
}

string CTool::TimeOut()
{
    time_t tmt_CurrentTime;
    struct tm *ptr_stc_CurrentTime;
    
    time(&tmt_CurrentTime);
    ptr_stc_CurrentTime = localtime(&tmt_CurrentTime);

    char *cha_TimeStampFF = new char[40];
    char *cha_TimeStampDay = new char[20];
    char *cha_TimeStampSec = new char[20];

    snprintf(cha_TimeStampDay, sizeof(cha_TimeStampDay), "%d-%02d-%02d", 1900 + ptr_stc_CurrentTime->tm_year,\
                                            1 + ptr_stc_CurrentTime->tm_mon, ptr_stc_CurrentTime->tm_mday);
    snprintf(cha_TimeStampSec, sizeof(cha_TimeStampSec), "%02d:%02d:%02d", ptr_stc_CurrentTime->tm_hour,\
                                          ptr_stc_CurrentTime->tm_min, ptr_stc_CurrentTime->tm_sec);
    snprintf(cha_TimeStampFF, sizeof(cha_TimeStampFF), "%s %s", cha_TimeStampDay, cha_TimeStampSec);

    string str_TimeOut(cha_TimeStampFF);

    delete []cha_TimeStampFF;
    delete []cha_TimeStampDay;
    delete []cha_TimeStampSec;
    
    return str_TimeOut;
}

bool CTool::ParseNumber(const string str_Input, int& int_RetNum)
{
    smatch str_Match;
    regex REP_Number("^(\\+|-?)(\\d+)$");

    string str_NumPM("");
    string str_NumBody("");
    int int_NumPM = 1;
    int int_NumBody = 0;

    if( regex_match(str_Input, str_Match, REP_Number) )
    {
        str_NumPM = str_Match[1];
        str_NumBody = str_Match[2];

        if("" == str_NumPM)
            int_NumPM = 1;
        else if('+' == str_NumPM.at(0))
            int_NumPM = 1;
        else if('-' == str_NumPM.at(0))
            int_NumPM = -1;

        int_NumBody = atoi(str_NumBody.c_str());

        int_RetNum = int_NumBody * int_NumPM;

        return true;
    }
    else
    {
        int_RetNum = 0;
        return false;
    }
}

bool CTool::ParseContainKey(const string str_Main, const string str_Key)
{
    smatch str_Match;
    // tips 番茄@20180824 - 不区分大小写
    regex RE_key(str_Key, regex_constants::icase);

    if( regex_search(str_Main, str_Match, RE_key) )
        return true;
    else
        return false;
}

bool CTool::ParseDate(const string str_Input, unsigned int& uni_Year, unsigned int& uni_Month, unsigned int& uni_Day)
{
    smatch str_Match;
    regex REP_DateFormat("^(.*)(20)(\\d{2})(\\d{2})(\\d{2})$");

    if( regex_match(str_Input, str_Match, REP_DateFormat) )
    {
        string str_Year = str_Match[3];
        string str_Month = str_Match[4];
        string str_Day = str_Match[5];

        uni_Year = 2000 + atoi(str_Year.c_str());
        uni_Month = atoi(str_Month.c_str());
        uni_Day = atoi(str_Day.c_str());

        return true;
    }
    else
    {
        return false;
    }
}

bool CTool::CompareString(const string str_CmpA, const string str_CmpB)
{
    if( str_CmpA.length() != str_CmpB.length() )
        return false;

    if( str_CmpA == str_CmpB )
        return true;
    else
        return false;
}

void CTool::SetOriginMonth(const string str_OriginMonth)
{
    ms_str_OriginMonth = str_OriginMonth;
}

void CTool::SetCurrentMonth(const string str_CurrentMonth)
{
    ms_str_CurrentMonth = str_CurrentMonth;
}

void CTool::TagTimeBait()
{
    gettimeofday(&m_tvl_begin, NULL);
}

double CTool::ShowTimeGap()
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
//   river flows in summer
//------------------------------//
