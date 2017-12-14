
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;


typedef struct
{
    string str_ItemContent;
    string str_ItemAttrbute;
}FA_ITEM;

class CCFGLoader
{
public:
    /****************************************/
    //   初始化
    /****************************************/
    CCFGLoader();
    ~CCFGLoader();

    /****************************************/
    //   方法
    /****************************************/
    static void LoadCFG(const char *cha_FileName);
    static void LoadMonth();
    static void LoadFA();

    /****************************************/
    //   属性
    /****************************************/
    static string m_str_CFGPathName;
    static string m_str_OriginMonth;
    static string m_str_CurrentMonth;
    static vector<FA_ITEM> m_vec_stc_FAItem;
};


//------------------------------//
//   River flows in summer
//------------------------------//
