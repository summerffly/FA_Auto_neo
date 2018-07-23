
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "X_Tool.h"

using namespace std;


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
    int_RetFC += access("./travel.md", 0);
    int_RetFC += access("./lottery.md", 0);

    return int_RetFC;
}

string CTool::GenerateNextMonth(const string str_CurMonth)
{
    string str_NextMonth = string("");
    unsigned int uni_CurMonth = atoi(str_CurMonth.c_str());

    if((uni_CurMonth == 0) || (uni_CurMonth > 12))
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        Invalid Month Input       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_NextMonth;
    }

    switch(uni_CurMonth)
    {
        case 1:
            str_NextMonth += "02";
            break;
        case 2:
            str_NextMonth += "03";
            break;
        case 3:
            str_NextMonth += "04";
            break;
        case 4:
            str_NextMonth += "05";
            break;
        case 5:
            str_NextMonth += "06";
            break;
        case 6:
            str_NextMonth += "07";
            break;
        case 7:
            str_NextMonth += "08";
            break;
        case 8:
            str_NextMonth += "09";
            break;
        case 9:
            str_NextMonth += "10";
            break;
        case 10:
            str_NextMonth += "11";
            break;
        case 11:
            str_NextMonth += "12";
            break;
        case 12:
            str_NextMonth += "01";
            break;
        default:
            break;
    }

    return str_NextMonth;
}

string CTool::GenerateNextMonth(const int int_CurMonth)
{
    string str_NextMonth = string("");

    if((int_CurMonth <= 0) || (int_CurMonth > 12))
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        Invalid Month Input       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_NextMonth;
    }

    switch(int_CurMonth)
    {
        case 1:
            str_NextMonth += "02";
            break;
        case 2:
            str_NextMonth += "03";
            break;
        case 3:
            str_NextMonth += "04";
            break;
        case 4:
            str_NextMonth += "05";
            break;
        case 5:
            str_NextMonth += "06";
            break;
        case 6:
            str_NextMonth += "07";
            break;
        case 7:
            str_NextMonth += "08";
            break;
        case 8:
            str_NextMonth += "09";
            break;
        case 9:
            str_NextMonth += "10";
            break;
        case 10:
            str_NextMonth += "11";
            break;
        case 11:
            str_NextMonth += "12";
            break;
        case 12:
            str_NextMonth += "01";
            break;
        default:
            break;
    }

    return str_NextMonth;
}

string CTool::GeneratePreMonth(const string str_CurMonth)
{
    string str_NextMonth = string("");
    unsigned int uni_CurMonth = atoi(str_CurMonth.c_str());

    if((uni_CurMonth == 0) || (uni_CurMonth > 12))
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        Invalid Month Input       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_NextMonth;
    }

    switch(uni_CurMonth)
    {
        case 1:
            str_NextMonth += "12";
            break;
        case 2:
            str_NextMonth += "01";
            break;
        case 3:
            str_NextMonth += "02";
            break;
        case 4:
            str_NextMonth += "03";
            break;
        case 5:
            str_NextMonth += "04";
            break;
        case 6:
            str_NextMonth += "05";
            break;
        case 7:
            str_NextMonth += "06";
            break;
        case 8:
            str_NextMonth += "07";
            break;
        case 9:
            str_NextMonth += "08";
            break;
        case 10:
            str_NextMonth += "09";
            break;
        case 11:
            str_NextMonth += "10";
            break;
        case 12:
            str_NextMonth += "11";
            break;
        default:
            break;
    }

    return str_NextMonth;
}

string CTool::GeneratePreMonth(const int int_CurMonth)
{
    string str_NextMonth = string("");

    if((int_CurMonth <= 0) || (int_CurMonth > 12))
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        Invalid Month Input       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return str_NextMonth;
    }

    switch(int_CurMonth)
    {
        case 1:
            str_NextMonth += "12";
            break;
        case 2:
            str_NextMonth += "01";
            break;
        case 3:
            str_NextMonth += "02";
            break;
        case 4:
            str_NextMonth += "03";
            break;
        case 5:
            str_NextMonth += "04";
            break;
        case 6:
            str_NextMonth += "05";
            break;
        case 7:
            str_NextMonth += "06";
            break;
        case 8:
            str_NextMonth += "07";
            break;
        case 9:
            str_NextMonth += "08";
            break;
        case 10:
            str_NextMonth += "09";
            break;
        case 11:
            str_NextMonth += "10";
            break;
        case 12:
            str_NextMonth += "11";
            break;
        default:
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

//------------------------------//
//   river flows in summer
//------------------------------//
