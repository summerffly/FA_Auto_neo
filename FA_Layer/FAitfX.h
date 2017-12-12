
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

    /****************************************/
    //   月度 操作区
    /****************************************/

    void CheckMonthExpense(const string str_SelMonth);
    void CheckMonthSurplus(const string str_SelMonth);
    void UpdateMonthSurplus(const string str_SelMonth);
    void ModifyMonthSurplus(const string str_SelMonth, const string str_MonthKey,\
                            const unsigned int uni_ModValueABS);

    /****************************************/
    //   子项.M 操作区
    /****************************************/

    void CheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth);
    void UpdateSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth);
    void AppendSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth,\
                               const int int_LineValue, const string str_LineContent);

    /****************************************/
    //   TVT_分项 操作区
    /****************************************/

    void CheckTitleExpense(const string str_TitleKey);
    void UpdateTitleExpense(const string str_TitleKey);
    void AppendTitleExpense(const string str_TitleKey,\
                            const int int_LineValue, const string str_LineContent);

    /****************************************/
    //   文件读写 操作区
    /****************************************/

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
//   River flows in summer
//------------------------------//
