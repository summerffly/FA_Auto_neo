
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string>
#include <iostream>

using namespace std;


typedef enum
{
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
}ENUM_MOMTH;

class CTool
{
public:
    CTool();
    ~CTool();

    static int CheckFilesExist();

    static string GenerateNextMonth(const string str_CurMonth);
    static string GenerateNextMonth(const int int_CurMonth);
    static string GeneratePreMonth(const string str_CurMonth);
    static string GeneratePreMonth(const int int_CurMonth);

    static unsigned int CountMonth(const string str_OriMonth, const string str_CurMonth);
    
    static string TransOutFormat(const int int_Value);
    static void MassageOutFotmat(const string str_Message, const char cha_Flag);
    static string TimeOut();

public:
    static void TagTimeBait();
    static double ShowTimeGap();

private:
    static struct timeval m_tvl_begin;
    static struct timeval m_tvl_end;
};


//------------------------------//
//   river flows in summer
//------------------------------//
