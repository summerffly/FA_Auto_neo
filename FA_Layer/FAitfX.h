
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
    void SummarizeMonth(int int_OFlag);
    void SummarizeTitle(int int_OFlag);
    void SummarizeTail(int int_OFlag);
    void SummarizeCAF(int int_OFlag);

    void UpdateCurrentSum(const int int_CurrentSum);
    void UpdateCAF(const int int_CAFSum);

    /****************************************/
    //   Month 计算区
    /****************************************/
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

    /****************************************/
    //   Title 计算区
    /****************************************/
    int CheckTitleExpense(const string str_TitleKey, bool bol_OFlag);
    void UpdateTitleExpense(const string str_TitleKey, bool bol_OFlag);
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

    /****************************************/
    //   统计区
    /****************************************/
    void GenerateMonthTrendVector(vector<TREND_INFO> &vec_stc_TrendInfo, const string str_MonthKey);
    void AppendMonthTrendVector(vector<TREND_INFO> &vec_stc_TrendInfo, const string str_MonthKey);
    unsigned int GetMonthTrendVectorMax(const vector<TREND_INFO> vec_stc_TrendInfo);
    void DrawMonthTrendVector(const vector<TREND_INFO> vec_stc_TrendInfo, const string str_MonthKey);

    unsigned int GenerateMonthVector(vector<UNIT_INFO> &vec_stc_UnitInfoo, const string str_SelMonth);
    void AnalysisMonthProportion(const string str_SelMonth);
    void CompareMonth(const string str_SelMonth, const string str_CmpMonth);

    void ForecastFutureSum(const string str_SelMonth, const int int_MonthPatch);

    /****************************************/
    //   展示区
    /****************************************/
    void ShowMonthSurplus(const string str_SelMonth, int int_OFlag);
    void ShowLife(const string str_SelMonth, int int_OFlag);
    void ShowRoom(const string str_SelMonth, int int_OFlag);
    void ShowSM(const string str_SelMonth, int int_OFlag);

    int ShowSubMonth(const string str_SubMonthKey, const string str_SelMonth, int int_OFlag);
    void ShowTitle(const string str_TitleKey, const int int_OFlag);

    /****************************************/
    //   操作区
    /****************************************/
    void PrintSum(bool bol_NumFlag);
    void PrintMonth(const string str_SelMonth, bool bol_NumFlag);
    void PrintSubMonth(const string str_SubMonthKey, const string str_SelMonth, bool bol_NumFlag, bool bol_ShowFlag);
    void PrintTitle(const string str_TitleKey, bool bol_NumFlag);

    void InsertBlankLine(const string str_Type, const string str_Key,\
                         const unsigned int uni_LineIndex);
    void InsertLine(const string str_Type, const string str_Key,\
                    const unsigned int uni_LineIndex, const int int_LineValue, const string str_LineContent);
    void ModifyLine(const string str_Type, const string str_Key,\
                    const unsigned int uni_LineIndex, const int int_LineValue, const string str_LineContent);
    void ModifyLineValue(const string str_Type, const string str_Key,\
                         const unsigned int uni_LineIndex, const int int_LineValue);
    void ModifyLineContent(const string str_Type, const string str_Key,\
                           const unsigned int uni_LineIndex, const string str_LineContent);
    void CopyLine(const string str_Type, const string str_Key,\
                  const unsigned int uni_LineIndex, const unsigned int uni_LineIndexNew);
    void MoveLine(const string str_Type, const string str_Key,\
                  const unsigned int uni_LineIndex, const unsigned int uni_LineIndexNew);
    void DeleteLine(const string str_Type, const string str_Key,\
                    const unsigned int uni_LineIndex);

    /****************************************/
    //   文件读写区
    /****************************************/
    void CheckTimeStamp();
    void CheckEqualAllFile();
    void CheckEqualAllFile(const string str_Path);   // 函数重载
    void SyncAllFile();
    void WriteAllFile();
    void BackUpAllFile(const string str_BackUpPath);

    /****************************************/
    //   Ptr
    /****************************************/
    CFileManager *GetPtrFM(const string str_Type, const string str_Key);

/****************************************/
//   SUM成员
/****************************************/
private:
    int m_int_OriginSum;
    int m_int_CurrentSum;
    int m_int_CAFSum;

    int m_int_MonthSalarySum;
    int m_int_MonthExpenseSum;
    int m_int_MonthSurplusSum;

    int m_int_TitleSum;
    int m_int_TailSum;

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
    CFileManager *m_ptr_FM_tt_NR;
    CFileManager *m_ptr_FM_tt_travel;
    CFileManager *m_ptr_FM_tt_lottery;
    CFileManager *m_ptr_FM_NULL;

    static const unsigned int m_uni_FM_aszie = 12;
    CFileManager *m_ptr_FM_array[m_uni_FM_aszie];
};


string CMD_SMTranslate(const string str_SubMonthKey);
string CMD_TTTranslate(const string str_TitleKey);

//------------------------------//
//   River flows in summer
//------------------------------//
