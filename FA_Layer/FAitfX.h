
//------------------------------//
//   coded by 番茄
//   @summer studio
//------------------------------//

#pragma once

#include <map>
#include "./../X_Frame/X_Tool.h"
#include "./../X_Frame/Singleton.h"
#include "./../XML_Ripper/Script_Ripper.h"
#include "./../EP_Layer/FileManager.h"

using namespace std;


typedef struct
{
    string str_TrendMonth;
    unsigned int uni_TrendValueABS;
}TREND_INFO;

typedef struct
{
    string str_UnitContent;
    unsigned int uni_UnitValueABS;
}UNIT_INFO;

class CFAitfX
{
public:
    friend class Singleton<CFAitfX>;
    friend class CASitfX;   // tips 番茄@20180604 - 破坏封装性的风险
    
    CFAitfX();
    ~CFAitfX();

    /****************************************/
    //   SUM 计算区
    /****************************************/
    void LoadSum(int int_OFlag);
    void SummerizeMonth(int int_OFlag);
    void SummerizeTitle(int int_OFlag);
    void SummerizeTail(int int_OFlag);
    void SummerizeCAF(int int_OFlag);

    void UpdateCurrentSum(const int int_CurrentSum);
    void UpdateCAF(const int int_CAFSum);

    /****************************************/
    //   Month 计算区
    /****************************************/
    //void InsertMonth(const unsigned int uni_VecIndex, const int int_LineValue, const string str_LineContent);
    int CheckMonthExpense(const string str_SelMonth, bool bol_OFlag);
    int CheckMonthSurplus(const string str_SelMonth, bool bol_OFlag);
    void UpdateMonthSurplus(const string str_SelMonth, bool bol_OFlag);
    void ModifyMonthSurplus(const string str_SelMonth, const string str_MonthKey,\
                            const unsigned int uni_ModValueABS);
    void SyncMonthSurplus(const string str_SelMonth);

    /****************************************/
    //   SubMonth 计算区
    /****************************************/
    int CheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth, bool bol_OFlag);
    void UpdateSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth, bool bol_OFlag);
    void AppendSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth,\
                               const int int_LineValue, const string str_LineContent);

    /****************************************/
    //   Title 计算区
    /****************************************/
    int CheckTitleExpense(const string str_TitleKey, bool bol_OFlag);
    void UpdateTitleExpense(const string str_TitleKey, bool bol_OFlag);
    void InsertTitle(const string str_TitleKey, const unsigned int uni_VecIndex,\
                     const int int_LineValue, const string str_LineContent);
    void AppendTitleExpense(const string str_TitleKey,\
                            const int int_LineValue, const string str_LineContent);
    void AppendLottery(const bool bol_LineFlag, const unsigned int int_LineValueABS,\
                       const string str_LineDate);

    /****************************************/
    //   综合操作区
    /****************************************/
    void TransferBalance(const string str_FirstKey, const string str_SecondKey,
                         const bool bol_TransferFlag, const unsigned int uni_BalanceValueABS);
    void AddScriptSum(const string str_SelMonth);
    void AddScriptMonth(const string str_SelMonth);
    void AddScriptSubMonth(const string str_SubMonthKey, const string str_SelMonth);
    void CheckTempExpense();

    /****************************************/
    //   统计区
    /****************************************/
    void GenerateMonthTrendVector(vector<TREND_INFO> &vec_stc_TrendInfo, const string str_MonthKey);
    void AppendMonthTrendVector(vector<TREND_INFO> &vec_stc_TrendInfo, const string str_MonthKey);
    unsigned int GetMonthTrendVectorMax(const vector<TREND_INFO> vec_stc_TrendInfo);
    void DrawMonthTrendVector(const vector<TREND_INFO> vec_stc_TrendInfo, const string str_MonthKey);

    void AnalysisMonthProportion(const string str_SelMonth);

    void ForecastFutureSum(const string str_SelMonth, const int int_MonthPatch);

    /****************************************/
    //   展示区
    /****************************************/
    void PrintMonth(const string str_SelMonth, bool bol_NumFlag);
    void PrintSubMonth(const string str_SubMonthKey, const string str_SelMonth, bool bol_NumFlag, bool bol_ShowFlag);
    void PrintTitle(const string str_TitleKey, bool bol_NumFlag);

    void ShowMonthSurplus(const string str_SelMonth, int int_OFlag);
    void ShowLife(const string str_SelMonth, int int_OFlag);
    void ShowRoom(const string str_SelMonth, int int_OFlag);
    void ShowSubMonth(const string str_SelMonth, int int_OFlag);

    /****************************************/
    //   文件读写区
    /****************************************/
    void SyncAllFile();
    void WriteAllFile();
    void BackUpAllFile(const string str_BackUpPath);

    /****************************************/
    //   Ptr
    /****************************************/
    CFileManager *GetPtrSubMonthFM(const string str_SubMonthKey);
    CFileManager *GetPtrTitleFM(const string str_TitleKey);

/****************************************/
//   SUM成员
/****************************************/
private:
    int m_int_OriginSum;
    int m_int_CurrentSum;

    int m_int_MonthSalarySum;
    int m_int_MonthExpenseSum;
    int m_int_MonthSurplusSum;

    int m_int_TitleSum;
    int m_int_TailSum;
    int m_int_CAFSum;

/****************************************/
//   FM成员
/****************************************/
private:    
    CFileManager *m_ptr_FM_SUM;
    CFileManager *m_ptr_FM_life;
    CFileManager *m_ptr_FM_sm_DGtler;
    CFileManager *m_ptr_FM_sm_Books;
    CFileManager *m_ptr_FM_sm_KEEP;
    CFileManager *m_ptr_FM_sm_TB;
    CFileManager *m_ptr_FM_sm_sa;
    CFileManager *m_ptr_FM_tt_DK;
    CFileManager *m_ptr_FM_tt_NS;
    CFileManager *m_ptr_FM_tt_travel;
    CFileManager *m_ptr_FM_tt_lottery;
    CFileManager *m_ptr_FM_temp_BOX;
};

//------------------------------//
//   River flows in summer
//------------------------------//
