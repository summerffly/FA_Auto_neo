
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <map>
#include "./../X_Frame/X_Tool.h"
#include "./../X_Frame/X_CFGLoader.h"
#include "./../EP_Layer/FileManager.h"

using namespace std;


class CFAitfX
{
public:
    CFAitfX();
    ~CFAitfX();

    /****************************************/
    //   总收支 操作区
    /****************************************/
    void CheckAggrSurplus();
    void UpdateAggrSurplus();

    /****************************************/
    //   月度 操作区
    /****************************************/
    void CheckMonthExpense(const string str_SelMonth);
    int RCheckMonthSurplus(const string str_SelMonth);
    void CheckMonthSurplus(const string str_SelMonth);
    void UpdateMonthSurplus(const string str_SelMonth);
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
    int RCheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth);
    void CheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth);
    void UpdateSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth);
    void AppendSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth,\
                               const int int_LineValue, const string str_LineContent);

    /****************************************/
    //   Tt分项 操作区
    /****************************************/
    int RCheckTitleExpense(const string str_TitleKey);
    void CheckTitleExpense(const string str_TitleKey);
    void UpdateTitleExpense(const string str_TitleKey);
    void AppendTitleExpense(const string str_TitleKey,\
                            const int int_LineValue, const string str_LineContent);
    void AppendLottery(const bool bol_LineFlag, const unsigned int int_LineValueABS,\
                       const string str_LineDate);

    /****************************************/
    //   综合 操作区
    /****************************************/
    void TransferBalance(const string str_FirstKey, const string str_SecondKey,
                         const bool bol_TransferFlag, const unsigned int uni_BalanceValueABS);
    void CheckTempExpense();

    /****************************************/
    //   文件读写 操作区
    /****************************************/
    void SyncAllFile();
    void WriteAllFile();
    void BackUpAllFile(const string str_BackUpPath);

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
    CFileManager m_cls_FM_temp_BOX;
    CFileManager m_cls_FM_temp_travelXM;   // 暂时使用
};

//------------------------------//
//   River flows in summer
//------------------------------//
