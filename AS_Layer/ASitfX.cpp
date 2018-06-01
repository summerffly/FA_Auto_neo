
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
//   检查 FA全系统总收支
/**************************************************/
void CASitfX::CheckFA()
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    string str_CurMonth = ptr_ScriptRipper->GetCurrentMonth();

    // Check TitleDeep
    vector<string> vec_str_TitleDeep;
    ptr_ScriptRipper->TitleDeepDuplicator(vec_str_TitleDeep);

    vector<string>::iterator itr_TitleDeep;
    for(itr_TitleDeep = vec_str_TitleDeep.begin(); itr_TitleDeep != vec_str_TitleDeep.end(); itr_TitleDeep++)
    {
        if( 0 != ptr_FAitfX->CheckTitleExpense(*itr_TitleDeep, false) )
        {
            string str_Message = *itr_TitleDeep + " NOT Pass Check";
            CTool::MassageOutFotmat(str_Message, '!');
            return;
        }
    }

    // Check SubMonth
    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        if( 0 != ptr_FAitfX->CheckSubMonthExpense(*itr_SubMonth, str_CurMonth, false) )
        {
            string str_Message = *itr_SubMonth + " NOT Pass Check";
            CTool::MassageOutFotmat(str_Message, '!');
            return;
        }
    }

    // Check Month
    if( 0 != ptr_FAitfX->CheckMonthSurplus(str_CurMonth, false) )
    {
        CTool::MassageOutFotmat("Month NOT Pass Check", '!');
        return;
    }

    // Check Sum
    int int_AFRest = 0;
    int int_RetCheck = ptr_FAitfX->CheckAggrSurplus(int_AFRest, false);

    if( 0 != int_RetCheck )
    {
        CTool::MassageOutFotmat("FA_SUM NOT Pass Check", '!');
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "###   FA全系统校验Pass :)   ###" << endl;
        cout << "当前财富: " << CTool::TransOutFormat(int_AFRest) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   更新 FA全系统总收支
/**************************************************/
void CASitfX::UpdateFA()
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    string str_CurMonth = ptr_ScriptRipper->GetCurrentMonth();

    // Update TitleDeep
    vector<string> vec_str_TitleDeep;
    ptr_ScriptRipper->TitleDeepDuplicator(vec_str_TitleDeep);

    vector<string>::iterator itr_TitleDeep;
    for(itr_TitleDeep = vec_str_TitleDeep.begin(); itr_TitleDeep != vec_str_TitleDeep.end(); itr_TitleDeep++)
    {
        ptr_FAitfX->UpdateTitleExpense(*itr_TitleDeep, false);
    }

    // Update SubMonth
    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        ptr_FAitfX->UpdateSubMonthExpense(*itr_SubMonth, CTool::GeneratePreMonth(str_CurMonth), false);
        ptr_FAitfX->UpdateSubMonthExpense(*itr_SubMonth, str_CurMonth, false);
    }

    // Update Month
    ptr_FAitfX->UpdateMonthSurplus(CTool::GeneratePreMonth(str_CurMonth), true);
    ptr_FAitfX->SyncMonthSurplus(CTool::GeneratePreMonth(str_CurMonth));

    ptr_FAitfX->UpdateMonthSurplus(str_CurMonth, true);
    ptr_FAitfX->SyncMonthSurplus(str_CurMonth);

    // Update Sum
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
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    
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
    cout << ">>> " << CHECK << ' ' << MONTH << ' ' << ptr_ScriptRipper->GetCurrentMonth() << endl;
    cout << endl;

    cout << "更新 当月/上月 收支" << endl;
    cout << ">>> " << UPDATE << ' ' << MONTH << '/' << EX_MONTH << endl;
    cout << endl;

    cout << "更新 任意月度 收支" << endl;
    cout << ">>> " << UPDATE << ' ' << MONTH << ' ' << ptr_ScriptRipper->GetCurrentMonth() << endl;
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
    cout << ">>> " << APPEND << ' ' << MONTH << ' ' << ptr_ScriptRipper->GetCurrentMonth() << endl;
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
    cout << ">>> " << ANALYSIS << ' ' << PROPORTION << ' ' << ptr_ScriptRipper->GetCurrentMonth() << endl;
    cout << endl;

    cout << "汇总 Month累计收支" << endl;
    cout << ">>> " << SUMMARIZE << ' ' << MONTH << endl;
    cout << endl;

    cout << "汇总 Title累计收支" << endl;
    cout << ">>> " << SUMMARIZE << ' ' << TITLE << endl;
    cout << endl;

    cout << "汇总 Tail累计收支" << endl;
    cout << ">>> " << SUMMARIZE << ' ' << TAIL << endl;
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
