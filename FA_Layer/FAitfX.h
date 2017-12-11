
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

    void CheckMonthExpense(const string str_SelMonth);
    void CheckMonthSurplus(const string str_SelMonth);
    void UpdateMonthSurplus(const string str_SelMonth);
    void ModifyMonthSurplus(const string str_SelMonth, const string str_MonthKey,\
                            const unsigned int uni_ModValueABS);

    void CheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth);

    void CheckTitleExpense(const string str_TitleKey);
    void UpdateTitleExpense(const string str_TitleKey);

    void WriteAllFile();

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
