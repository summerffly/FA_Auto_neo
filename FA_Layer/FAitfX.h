
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include "./../X_Frame/X_Tool.h"
#include "./../EP_Layer/FileManager.h"

using namespace std;


class CFAitfX
{
public:
    CFAitfX();
    ~CFAitfX();

    void CheckMonthExpense(const string str_CurMonth);
    void CheckMonthSurplus(const string str_CurMonth);

    void CheckSubMonthExpense(const string str_SubMonthKey, const string str_CurMonth);

private:
    CFileManager m_cls_FM_TVT;
    CFileManager m_cls_FM_life;
    CFileManager m_cls_FM_sm_Books;
    CFileManager m_cls_FM_sm_KEEP;
    CFileManager m_cls_FM_sm_TB;
    CFileManager m_cls_FM_sm_sa;
    CFileManager m_cls_FM_tt_DK;
    CFileManager m_cls_FM_tt_NS;
    CFileManager m_cls_FM_tt_travel;
    CFileManager m_cls_FM_tt_lottery;
};

//------------------------------//
//   river flows in summer
//------------------------------//
