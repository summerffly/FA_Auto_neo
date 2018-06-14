
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

    // Check Month
    if( 0 != CheckMonth(str_CurMonth, 0) )
    {
        return;
    }

    if( 0 != CheckSum(0) )
    {
        CTool::MassageOutFotmat("FA_SUM NOT Pass Check", '!');
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "###   FA全系统校验Pass :)   ###" << endl;
        cout << "当前财富: " << CTool::TransOutFormat(ptr_FAitfX->m_int_CurrentSum) << endl;
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

    // Update CurrentMonth
    UpdateMonth(str_CurMonth, 0);

    // Update Sum
    UpdateSum(1);
}

/**************************************************/
//   展示 FA全系统总收支
/**************************************************/
void CASitfX::ShowFA()
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->ShowLife(ptr_ScriptRipper->GetCurrentMonth(), 1);
    ptr_FAitfX->ShowRoom(ptr_ScriptRipper->GetCurrentMonth(), 3);
    ptr_FAitfX->ShowSubMonth(ptr_ScriptRipper->GetCurrentMonth(), 2);
    ptr_FAitfX->ShowMonthSurplus(ptr_ScriptRipper->GetCurrentMonth(), 2);
    ptr_FAitfX->LoadSum(1);
    ptr_FAitfX->SummerizeCAF(1);

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   校验 SUM收支
/**************************************************/
int CASitfX::CheckSum(int int_OFlag)
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->LoadSum(0);
    ptr_FAitfX->SummerizeMonth(0);
    ptr_FAitfX->SummerizeTitle(0);
    ptr_FAitfX->SummerizeTail(0);
    ptr_FAitfX->SummerizeCAF(0);

    int int_OriginSum = ptr_FAitfX->m_int_OriginSum;
    int int_CurrentSum = ptr_FAitfX->m_int_CurrentSum;

    int int_MonthSalarySum = ptr_FAitfX->m_int_MonthSalarySum;
    int int_MonthExpenseSum = ptr_FAitfX->m_int_MonthExpenseSum;
    int int_MonthSurplusSum = ptr_FAitfX->m_int_MonthSurplusSum;

    int int_TitleSum = ptr_FAitfX->m_int_TitleSum;
    int int_TailSum = ptr_FAitfX->m_int_TailSum;
    int int_CAFSum = ptr_FAitfX->m_int_CAFSum;

    int int_CurrentSumCK = int_OriginSum + int_MonthSurplusSum + int_TitleSum;
    int int_CAFSumCK = int_CurrentSumCK + int_TailSum;

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << "### 当前财富 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(int_CurrentSum) << endl;
        cout << "校验值: " << CTool::TransOutFormat(int_CurrentSumCK) << endl;
        cout << "----------------------------------------" << endl;
        cout << "### 支配财富 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(int_CAFSum) << endl;
        cout << "校验值: " << CTool::TransOutFormat(int_CAFSumCK) << endl;
        cout << "----------------------------------------" << endl;
    }

    if(int_CurrentSum != int_CurrentSumCK)
    {
        return -1;
    }
    else if(int_CAFSum != int_CAFSumCK)
    {
        return -2;
    }
    else
    {
        return 0;
    }
}

/**************************************************/
//   更新 SUM收支
/**************************************************/
void CASitfX::UpdateSum(int int_OFlag)
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->LoadSum(0);
    ptr_FAitfX->SummerizeMonth(0);
    ptr_FAitfX->SummerizeTitle(0);
    ptr_FAitfX->SummerizeTail(0);
    ptr_FAitfX->SummerizeCAF(0);

    int int_OriginSum = ptr_FAitfX->m_int_OriginSum;
    int int_CurrentSum = ptr_FAitfX->m_int_CurrentSum;

    int int_MonthSalarySum = ptr_FAitfX->m_int_MonthSalarySum;
    int int_MonthExpenseSum = ptr_FAitfX->m_int_MonthExpenseSum;
    int int_MonthSurplusSum = ptr_FAitfX->m_int_MonthSurplusSum;

    int int_TitleSum = ptr_FAitfX->m_int_TitleSum;
    int int_TailSum = ptr_FAitfX->m_int_TailSum;
    int int_CAFSum = ptr_FAitfX->m_int_CAFSum;

    int int_CurrentSumUD = int_OriginSum + int_TitleSum + int_MonthSurplusSum;
    int int_CAFSumUD = int_CurrentSumUD + int_TailSum;

    ptr_FAitfX->UpdateCurrentSum(int_CurrentSumUD);
    ptr_FAitfX->UpdateCAF(int_CAFSumUD);

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << "### 当前财富 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(int_CurrentSum) << endl;
        cout << "更新值: " << CTool::TransOutFormat(int_CurrentSumUD) << endl;
        cout << "----------------------------------------" << endl;
        cout << "### 支配财富 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(int_CAFSum) << endl;
        cout << "更新值: " << CTool::TransOutFormat(int_CAFSumUD) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   展示 SUM收支
/**************************************************/
void CASitfX::ShowSum()
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->SummerizeTitle(1);
    ptr_FAitfX->SummerizeTail(1);
    ptr_FAitfX->SummerizeMonth(1);

    ptr_FAitfX->LoadSum(1);
    ptr_FAitfX->SummerizeCAF(1);

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   校验 Month收支
/**************************************************/
int CASitfX::CheckMonth(const string str_SelMonth, int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    // Check SubMonth
    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        if( 0 != ptr_FAitfX->CheckSubMonthExpense(*itr_SubMonth, str_SelMonth, false) )
        {
            string str_Message = "M" + str_SelMonth + "." + *itr_SubMonth + " NOT Pass Check";
            CTool::MassageOutFotmat(str_Message, '!');
            return -1;
        }
    }

    // Check Month
    if( 0 != ptr_FAitfX->CheckMonthSurplus(str_SelMonth, false) )
    {
        string str_Message = "Month " + str_SelMonth + " NOT Pass Check";
        CTool::MassageOutFotmat("Month NOT Pass Check", '!');
        return -2;
    }

    if(int_OFlag == 1)
    {
        ptr_FAitfX->ShowMonthSurplus(str_SelMonth, 4);
    }

    return 0;
}

/**************************************************/
//   更新 Month收支
/**************************************************/
void CASitfX::UpdateMonth(const string str_SelMonth, int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    // Update SubMonth
    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        ptr_FAitfX->UpdateSubMonthExpense(*itr_SubMonth, str_SelMonth, false);
    }

    // Update Month
    ptr_FAitfX->UpdateMonthSurplus(str_SelMonth, false);
    ptr_FAitfX->SyncMonthSurplus(str_SelMonth);

    if(int_OFlag == 1)
    {
        ptr_FAitfX->ShowMonthSurplus(str_SelMonth, 4);
    }
}

/**************************************************/
//   展示 Month收支
/**************************************************/
void CASitfX::ShowMonth(const string str_SelMonth)
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->ShowLife(str_SelMonth, 1);
    ptr_FAitfX->ShowRoom(str_SelMonth, 2);
    ptr_FAitfX->ShowSubMonth(str_SelMonth, 2);
    ptr_FAitfX->ShowMonthSurplus(str_SelMonth, 2);

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析月度趋势 ROOM租房支出
/**************************************************/
void CASitfX::AnalysisMonthTrend_ROOM()
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    vector<TREND_INFO> vec_stc_TrendInfo;

    vector<string> vec_str_Room;
    ptr_ScriptRipper->RoomDuplicator(vec_str_Room);

    vector<string>::iterator itr_Room;
    for(itr_Room = vec_str_Room.begin(); itr_Room != vec_str_Room.end(); itr_Room++)
    {
        if(itr_Room == vec_str_Room.begin())
        {
            ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, *itr_Room);
            continue;
        }

        ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, *itr_Room);
    }

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度ROOM趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, "ROOM");

    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析月度趋势 CSM消费支出
/**************************************************/
void CASitfX::AnalysisMonthTrend_CSM()
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    vector<TREND_INFO> vec_stc_TrendInfo;

    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        if(itr_SubMonth == vec_str_SubMonth.begin())
        {
            ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, *itr_SubMonth);
            continue;
        }

        ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, *itr_SubMonth);
    }

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度CSM趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, "CSM");

    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   展示.md 全部月度.M
/**************************************************/
void CASitfX::ShowMDRawSubMonthTraversal(const string str_SelMonth, bool bol_NumFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    cout << "----------------------------------------" << endl;
    cout << "### 全部月度.M 展示.md ###" << endl;
    cout << endl;

    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        ptr_FAitfX->ShowMDRawSubMonth(*itr_SubMonth, str_SelMonth, bol_NumFlag, false);
    }

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   添加NextMonth脚本
/**************************************************/
void CASitfX::AppendNextMonth(const string str_SelMonth)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    // 修改Script
    ptr_ScriptRipper->ModifyCurrentMonth(str_SelMonth);

    // 添加Sum脚本
    ptr_FAitfX->AddScriptSum(str_SelMonth);

    // 添加Month脚本
    ptr_FAitfX->AddScriptMonth(str_SelMonth);

    // 添加SubMonth脚本
    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        ptr_FAitfX->AddScriptSubMonth(*itr_SubMonth, CTool::GenerateNextMonth(str_SelMonth));
    }
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

    cout << "校验 任意Month 收支" << endl;
    cout << ">>> " << CHECK << ' ' << MONTH << ' ' << ptr_ScriptRipper->GetCurrentMonth() << endl;
    cout << endl;

    cout << "校验 当月/上月 收支" << endl;
    cout << ">>> " << CHECK << ' ' << MONTH << '/' << EX_MONTH << endl;
    cout << endl;

    cout << "更新 任意Month 收支" << endl;
    cout << ">>> " << UPDATE << ' ' << MONTH << ' ' << ptr_ScriptRipper->GetCurrentMonth() << endl;
    cout << endl;

    cout << "更新 当月/上月 收支" << endl;
    cout << ">>> " << UPDATE << ' ' << MONTH << '/' << EX_MONTH << endl;
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
