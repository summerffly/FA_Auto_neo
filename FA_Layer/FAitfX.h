
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <map>
#include "./../X_Frame/X_Tool.h"
#include "./../X_Frame/Singleton.h"
#include "./../X_Frame/X_CFGLoader.h"
#include "./../EP_Layer/FileManager.h"

using namespace std;


class CFAitfX
{
public:
    friend class Singleton<CFAitfX>;
    
    CFAitfX();
    ~CFAitfX();

    /****************************************/
    //   总收支 操作区
    /****************************************/
    int CheckAggrSurplus(unsigned int &uni_AliRest, bool bol_OFlag);
    void UpdateAggrSurplus(bool bol_OFlag);
    void CheckFA(const string str_CurMonth);

    /****************************************/
    //   月度 操作区
    /****************************************/
    int CheckMonthExpense(const string str_SelMonth, bool bol_OFlag);
    int CheckMonthSurplus(const string str_SelMonth, bool bol_OFlag);
    void UpdateMonthSurplus(const string str_SelMonth, bool bol_OFlag);
    void ModifyMonthSurplus(const string str_SelMonth, const string str_MonthKey,\
                            const unsigned int uni_ModValueABS);
    void SyncMonthSurplus(const string str_SelMonth);

    /****************************************/
    //   月度 操作区 Plus
    /****************************************/
    void AnalysisMonthTrend(const string str_MonthKey);
    void AnalysisMonthProportion(const string str_SelMonth);

    /****************************************/
    //   子项.M 操作区
    /****************************************/
    int CheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth, bool bol_OFlag);
    void UpdateSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth, bool bol_OFlag);
    void AppendSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth,\
                               const int int_LineValue, const string str_LineContent);

    /****************************************/
    //   Tt分项 操作区
    /****************************************/
    int CheckTitleExpense(const string str_TitleKey, bool bol_OFlag);
    void UpdateTitleExpense(const string str_TitleKey, bool bol_OFlag);
    void AppendTitleExpense(const string str_TitleKey,\
                            const int int_LineValue, const string str_LineContent);
    void AppendLottery(const bool bol_LineFlag, const unsigned int int_LineValueABS,\
                       const string str_LineDate);

    /****************************************/
    //   综合 操作区
    /****************************************/
    void TransferBalance(const string str_FirstKey, const string str_SecondKey,
                         const bool bol_TransferFlag, const unsigned int uni_BalanceValueABS);
    void AppendMonth(const string str_SelMonth);
    void AppendsubMonth(const string str_SubMonthKey, const string str_SelMonth);
    void CheckTempExpense();

    /****************************************/
    //   文件读写 操作区
    /****************************************/
    void SyncAllFile();
    void WriteAllFile();
    void BackUpAllFile(const string str_BackUpPath);

private:
    CFileManager m_cls_FM_AF;
    CFileManager m_cls_FM_life;
    CFileManager m_cls_FM_sm_Books;
    CFileManager m_cls_FM_sm_KEEP;
    CFileManager m_cls_FM_sm_TB;
    CFileManager m_cls_FM_sm_sa;
    CFileManager m_cls_FM_tt_DK;
    CFileManager m_cls_FM_tt_NS;
    CFileManager m_cls_FM_tt_travel;
    CFileManager m_cls_FM_tt_lottery;
    CFileManager m_cls_FM_temp_BOX;
};

//------------------------------//
//   River flows in summer
//------------------------------//
