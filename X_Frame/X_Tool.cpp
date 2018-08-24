
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "X_Tool.h"

using namespace std;


struct timeval CTool::m_tvl_begin;
struct timeval CTool::m_tvl_end;

CTool::CTool()
{
    // Do Nothing
}

CTool::~CTool()
{
    // Do Nothing
}

int CTool::CheckFilesExist()
{
    int int_RetFC = 0;
    int_RetFC += access("./FA_Auto_Script.xml", 0);
    int_RetFC += access("./FA_SUM.md", 0);
    int_RetFC += access("./life.M.md", 0);
    int_RetFC += access("./DGtler.M.md", 0);
    int_RetFC += access("./Books.M.md", 0);
    int_RetFC += access("./KEEP.M.md", 0);
    int_RetFC += access("./TB.M.md", 0);
    int_RetFC += access("./sa.M.md", 0);
    int_RetFC += access("./DK.md", 0);
    int_RetFC += access("./NS.md", 0);
    int_RetFC += access("./NR411.md", 0);
    int_RetFC += access("./travel.md", 0);
    int_RetFC += access("./lottery.md", 0);

    return int_RetFC;
}

bool CTool::ParseMonth(const string str_Input)
{
    smatch str_Match;
    regex REP_Month("^(\\d{2})$");

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

string CTool::GenerateMonth(const int int_Month)
{
    char *cha_Month = new char[3];

    if(int_Month < 10)
        sprintf(cha_Month, "0%d", int_Month);
    else
        sprintf(cha_Month, "%d", int_Month);

    delete []cha_Month;
    string str_Month(cha_Month);

    return str_Month;
}

string CTool::GenerateNextMonth(const string str_CurMonth)
{
    string str_NextMonth = string("");
    unsigned int uni_CurMonth = atoi(str_CurMonth.c_str());

    if( !ParseMonth(str_CurMonth) )
    {
        MassageOutFotmat("Invalid Month Input", '!');
        return str_NextMonth;
    }

    switch(uni_CurMonth)
    {
        case 12:
            str_NextMonth += "01";
            break;
        default:
            int int_NextMonth = uni_CurMonth+1;
            str_NextMonth += GenerateMonth(int_NextMonth);
            break;
    }

    return str_NextMonth;
}

string CTool::GeneratePreMonth(const string str_CurMonth)
{
    string str_NextMonth = string("");
    unsigned int uni_CurMonth = atoi(str_CurMonth.c_str());

    if( !ParseMonth(str_CurMonth) )
    {
        MassageOutFotmat("Invalid Month Input", '!');
        return str_NextMonth;
    }

    switch(uni_CurMonth)
    {
        case 1:
            str_NextMonth += "12";
            break;
        default:
            int int_NextMonth = uni_CurMonth-1;
            str_NextMonth += GenerateMonth(int_NextMonth);
            break;
    }

    return str_NextMonth;
}

unsigned int CTool::CountMonth(const string str_OriMonth, const string str_CurMonth)
{
    int int_MonthCounter = 0;
    
    int_MonthCounter = atoi(str_CurMonth.c_str()) - atoi(str_OriMonth.c_str()) + 1;

    if(int_MonthCounter<0)
        int_MonthCounter += 12;

    return (unsigned int)int_MonthCounter;
}

string CTool::TransOutFormat(const int int_Value)
{
    string str_OutValue = string("");
    char *cha_OutValue = new char[9];     // tips 番茄@20171205 - 支持到百万级

    if(int_Value > 0)
    {
        sprintf(cha_OutValue, "+%d", int_Value);
        str_OutValue += cha_OutValue;
    }
    else
    {
        sprintf(cha_OutValue, "%d", int_Value);
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

    sprintf(cha_TimeStampDay, "%d-%02d-%02d", 1900 + ptr_stc_CurrentTime->tm_year,\
                                            1 + ptr_stc_CurrentTime->tm_mon, ptr_stc_CurrentTime->tm_mday);
    sprintf(cha_TimeStampSec, "%02d:%02d:%02d", ptr_stc_CurrentTime->tm_hour,\
                                          ptr_stc_CurrentTime->tm_min, ptr_stc_CurrentTime->tm_sec);
    sprintf(cha_TimeStampFF, "%s %s", cha_TimeStampDay, cha_TimeStampSec);

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
