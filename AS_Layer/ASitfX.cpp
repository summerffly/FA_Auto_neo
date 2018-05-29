
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "ASitfX.h"

#include "./../X_Frame/DefLib.h"

using namespace std;


/**************************************************/
//   CASitfX 构造函数
/**************************************************/
CASitfX::CASitfX()
{
    // Nothing To Do
}

/**************************************************/
//   CASitfX 析构函数
/**************************************************/
CASitfX::~CASitfX()
{
    // Nothing To Do
}

/**************************************************/
//   FA全系统更新 总收支
/**************************************************/
void CASitfX::UpdateFA(const string str_CurMonth)
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->UpdateTitleExpense("lottery", false);
    ptr_FAitfX->UpdateTitleExpense("DK", false);
    ptr_FAitfX->UpdateTitleExpense("NS", false);
    ptr_FAitfX->UpdateTitleExpense("travel", false);

    ptr_FAitfX->UpdateSubMonthExpense("Books", CTool::GeneratePreMonth(str_CurMonth), false);
    ptr_FAitfX->UpdateSubMonthExpense("KEEP", CTool::GeneratePreMonth(str_CurMonth), false);
    ptr_FAitfX->UpdateSubMonthExpense("TB", CTool::GeneratePreMonth(str_CurMonth), false);
    ptr_FAitfX->UpdateSubMonthExpense("sa", CTool::GeneratePreMonth(str_CurMonth), false);

    ptr_FAitfX->UpdateMonthSurplus(CTool::GeneratePreMonth(str_CurMonth), true);
    ptr_FAitfX->SyncMonthSurplus(CTool::GeneratePreMonth(str_CurMonth));

    ptr_FAitfX->UpdateSubMonthExpense("Books", str_CurMonth, false);
    ptr_FAitfX->UpdateSubMonthExpense("KEEP", str_CurMonth, false);
    ptr_FAitfX->UpdateSubMonthExpense("TB", str_CurMonth, false);
    ptr_FAitfX->UpdateSubMonthExpense("sa", str_CurMonth, false);

    ptr_FAitfX->UpdateMonthSurplus(str_CurMonth, true);
    ptr_FAitfX->SyncMonthSurplus(str_CurMonth);

    ptr_FAitfX->UpdateAggrSurplus(true);
}

/**************************************************/
//   分析月度趋势 CSM消费支出
/**************************************************/
void CASitfX::AnalysisMonthTrend_CSM()
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();
    vector<TREND_INFO> vec_stc_TrendInfo;

    // 建构 趋势Vector
    // tips 番茄@20180307 - 这里需要升级为XML脚本读取
    ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, "Books");
    ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, "KEEP");
    ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, "TB");
    ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, "sa");

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度CSM消费趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, "CSM消费");

    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析月度趋势 租房支出
/**************************************************/
void CASitfX::AnalysisMonthTrend_ROOM()
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();
    vector<TREND_INFO> vec_stc_TrendInfo;

    // 建构 趋势Vector
    // tips 番茄@20180307 - 这里需要升级为XML脚本读取
    ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, "ONE房租");
    ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, "ONE水电费");
    ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, "ONE管理费");
    ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, "ONE网络费");

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度租房支出趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, "租房");

    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   展示.md 全部月度.M
/**************************************************/
void CASitfX::ShowMDRawSubMonthTraversal(const string str_SelMonth, bool bol_NumFlag)
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    cout << "----------------------------------------" << endl;
    cout << "### 全部月度.M 展示.md ###" << endl;
    cout << endl;

    ptr_FAitfX->ShowMDRawSubMonth("Books", str_SelMonth, bol_NumFlag, false);
    ptr_FAitfX->ShowMDRawSubMonth("KEEP", str_SelMonth, bol_NumFlag, false);
    ptr_FAitfX->ShowMDRawSubMonth("TB", str_SelMonth, bol_NumFlag, false);
    ptr_FAitfX->ShowMDRawSubMonth("sa", str_SelMonth, bol_NumFlag, false);

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   帮助提示
/**************************************************/
void CASitfX::HelpAll()
{
    cout << "******************************" << endl;
    cout << endl;
            
    cout << "退出 FA_Auto_X" << endl;
    cout << ">>> " << EXIT << endl;
    cout << endl;

    cout << "同步 所有.md" << endl;
    cout << ">>> " << SYNC << endl;
    cout << endl;

    cout << "写回 所有.md" << endl;
    cout << ">>> " << WRITE << endl;
    cout << endl;

    cout << "备份 所有.md" << endl;
    cout << ">>> " << BACKUP << endl;
    cout << endl;

    cout << "校验 SUM总收支" << endl;
    cout << ">>> " << CHECK << ' ' << SUM << endl;
    cout << endl;

    cout << "更新 SUM总收支" << endl;
    cout << ">>> " << UPDATE << ' ' << SUM << endl;
    cout << endl;
            
    cout << "校验 FA全系统总收支" << endl;
    cout << ">>> " << CHECK << endl;
    cout << endl;            

    cout << "更新 FA全系统总收支" << endl;
    cout << ">>> " << UPDATE << endl;
    cout << endl;

    cout << "校验 当月/上月 支出" << endl;
    cout << ">>> " << CHECK << ' ' << EXPENSE << ' ' << MONTH << '/' << EX_MONTH << endl;
    cout << endl;

    cout << "校验 当月/上月 收支" << endl;
    cout << ">>> " << CHECK << ' ' << MONTH << '/' << EX_MONTH << endl;
    cout << endl;

    cout << "校验 任意月度 收支" << endl;
    cout << ">>> " << CHECK << ' ' << MONTH << ' ' << CCFGLoader::m_str_OriginMonth << endl;
    cout << endl;

    cout << "更新 当月/上月 收支" << endl;
    cout << ">>> " << UPDATE << ' ' << MONTH << '/' << EX_MONTH << endl;
    cout << endl;

    cout << "更新 任意月度 收支" << endl;
    cout << ">>> " << UPDATE << ' ' << MONTH << ' ' << CCFGLoader::m_str_OriginMonth << endl;
    cout << endl;

    cout << "增加 当月 生活费" << endl;
    cout << ">>> " << MODIFY_LIFE << " 100" << endl;
    cout << endl;

    cout << "校验 子项.M 支出" << endl;
    cout << ">>> " << CHECK << ' ' << SUBMONTH << " books/keep/tb/sa" << endl;
    cout << endl;

    cout << "更新 子项.M 支出" << endl;
    cout << ">>> " << UPDATE << ' ' << SUBMONTH << " books/keep/tb/sa" << endl;
    cout << endl;

    cout << "校验 Tt分项 支出" << endl;
    cout << ">>> " << CHECK << ' ' << TITLE << " dk/ns/travel/lottery" << endl;
    cout << endl;

    cout << "更新 Tt分项 支出" << endl;
    cout << ">>> " << UPDATE << ' ' << TITLE << " dk/ns/travel/lottery" << endl;
    cout << endl;

    cout << "增加 lottery 收支" << endl;
    cout << ">>> " << LOTTERY << " ++/-- " << "200 20170906" << endl;
    cout << endl;

    cout << "transfer 操作" << endl;
    cout << ">>> " << TRANSFER << " ++/-- " << "300" << endl;
    cout << endl;

    cout << "插入 月度 脚本" << endl;
    cout << ">>> " << APPEND << ' ' << MONTH << ' ' << CCFGLoader::m_str_CurrentMonth << endl;
    cout << endl;

    cout << "校验 temp 支出" << endl;
    cout << ">>> " << CHECK << ' ' << TEMP << endl;
    cout << endl;

    cout << "分析 月度趋势" << endl;
    cout << ">>> " << ANALYSIS << ' ' << TREND << " 生活费" << endl;
    cout << endl;

    cout << "分析月度趋势 CSM消费支出" << endl;
    cout << ">>> " << ANALYSIS << ' ' << TREND << ' ' << CONSUMPTION << endl;
    cout << endl;

    cout << "分析月度趋势 租房支出" << endl;
    cout << ">>> " << ANALYSIS << ' ' << TREND << ' ' << ROOM << endl;
    cout << endl;

    cout << "分析 月度百分占比" << endl;
    cout << ">>> " << ANALYSIS << ' ' << PROPORTION << ' ' << CCFGLoader::m_str_CurrentMonth << endl;
    cout << endl;

    cout << "统计 累计月度收支" << endl;
    cout << ">>> " << SUMMARIZE << ' ' << MONTH << ' ' << AGGREGATION << endl;
    cout << endl;

    cout << "展示.md 月度 当月/上月" << endl;
    cout << ">>> " << PRINT << ' ' << MONTH << '/' << EX_MONTH << endl;
    cout << endl;

    cout << "展示.md 月度 任意月份" << endl;
    cout << ">>> " << PRINT << ' ' << MONTH << " 04" << endl;
    cout << endl;

    cout << "展示.md 月度.M 任意月份" << endl;
    cout << ">>> " << PRINT << ' ' << SUBMONTH << " books 04" << endl;
    cout << endl;

    cout << "展示.md 全部月度.M 任意月份" << endl;
    cout << ">>> " << PRINT << ' ' << SUBMONTH << " 04" << endl;
    cout << endl;

    cout << "展示 当月/上月 收支" << endl;
    cout << ">>> " << SHOW << ' ' << MONTH << '/' << EX_MONTH << endl;
    cout << endl;

    cout << "展示 SUM总收支" << endl;
    cout << ">>> " << SHOW << ' ' << SUM << endl;
    cout << endl;

    cout << "展示 FA当前状态" << endl;
    cout << ">>> " << SHOW << endl;
    cout << endl;

    cout << "******************************" << endl;

}


//------------------------------//
//   River flows in summer
//------------------------------//
