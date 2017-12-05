
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

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
    static string GenerateNextMonth(const string str_CurMonth);
    static string GenerateNextMonth(const int int_CurMonth);
    static string GeneratePreMonth(const string str_CurMonth);
    static string GeneratePreMonth(const int int_CurMonth);
    static string TransOutFormat(const int int_Value);
};


//------------------------------//
//   river flows in summer
//------------------------------//
