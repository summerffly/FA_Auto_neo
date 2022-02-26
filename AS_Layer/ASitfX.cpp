
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
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    string str_CurMonth = ptr_XonfigLoader->GetCurrentMonth();

    // Check TitleDeep
    vector<string> vec_str_TitleDeep;
    ptr_XonfigLoader->TitleDeepDuplicator(vec_str_TitleDeep);

    vector<string>::iterator itr_TitleDeep;
    for(itr_TitleDeep = vec_str_TitleDeep.begin(); itr_TitleDeep != vec_str_TitleDeep.end(); itr_TitleDeep++)
    {
        if( 0 != ptr_FAitfX->CheckTitleExpense(*itr_TitleDeep, false) )
        {
            string str_Message = CMD_TTTranslate(*itr_TitleDeep) + " NOT Pass Check";
            CTool::MassageOutFotmat(str_Message, '!');
            return;
        }
    }

    // Check Month
    if( 0 != CheckMonth(str_CurMonth, 0) )
    {
        return;
    }

    // Check CAF
    if(0 != ptr_FAitfX->CheckCAF())
    {
        CTool::MassageOutFotmat("CAF Allocation Error", '!');
        return;
    }

    if( 0 != CheckSum(0) )
    {
        CTool::MassageOutFotmat("FA_SUM NOT Pass Check", '!');
        return;
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "###   FA全系统校验Pass :)   ###" << endl;
        cout << "当前财富: " << CTool::TransOutFormat(ptr_FAitfX->m_int_CurrentSum) << endl;
        cout << "----------------------------------------" << endl;
        return;
    }
}

/**************************************************/
//   更新 FA全系统总收支
/**************************************************/
void CASitfX::UpdateFA()
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    string str_CurMonth = ptr_XonfigLoader->GetCurrentMonth();

    // Update TitleDeep
    vector<string> vec_str_TitleDeep;
    ptr_XonfigLoader->TitleDeepDuplicator(vec_str_TitleDeep);

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
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->ShowLife(ptr_XonfigLoader->GetCurrentMonth(), 3);
    ptr_FAitfX->ShowRoom(ptr_XonfigLoader->GetCurrentMonth(), 3);
    ptr_FAitfX->ShowSM(ptr_XonfigLoader->GetCurrentMonth(), 3);
    ptr_FAitfX->ShowMonthSurplus(ptr_XonfigLoader->GetCurrentMonth(), 1);
    ptr_FAitfX->LoadSum(1);
    ptr_FAitfX->SummarizeCAF(1);

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   校验 SUM收支
/**************************************************/
int CASitfX::CheckSum(int int_OFlag)
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->LoadSum(0);
    ptr_FAitfX->SummarizeMonth(0);
    ptr_FAitfX->SummarizeTitle(0);
    ptr_FAitfX->SummarizeTail(0);
    ptr_FAitfX->SummarizeCAF(0);

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
        cout << "### 可支配财富 ###" << endl;
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
    ptr_FAitfX->SummarizeMonth(0);
    ptr_FAitfX->SummarizeTitle(0);
    ptr_FAitfX->SummarizeTail(0);
    ptr_FAitfX->SummarizeCAF(0);

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
        cout << "### 可支配财富 ###" << endl;
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

    ptr_FAitfX->SummarizeTitle(1);
    ptr_FAitfX->SummarizeMonthCLS(1);
    
    ptr_FAitfX->LoadSum(1);
    
    ptr_FAitfX->SummarizeTail(1);
    ptr_FAitfX->SummarizeCAF(1);

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   校验 Month收支
/**************************************************/
int CASitfX::CheckMonth(const string str_SelMonth, int int_OFlag)
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    // Check SubMonth
    vector<string> vec_str_SubMonth;
    ptr_XonfigLoader->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        if( 0 != ptr_FAitfX->CheckSubMonthExpense(*itr_SubMonth, str_SelMonth, false) )
        {
            string str_Message = CMD_SMTranslate(*itr_SubMonth) + "." + "M" + str_SelMonth + " NOT Pass Check";
            CTool::MassageOutFotmat(str_Message, '!');
            return -1;
        }
    }

    // Check Month
    if( 0 != ptr_FAitfX->CheckMonthSurplus(str_SelMonth, false) )
    {
        string str_Message = "Month " + str_SelMonth + " NOT Pass Check";
        CTool::MassageOutFotmat(str_Message, '!');
        return -2;
    }

    if(int_OFlag == 1)
    {
        ptr_FAitfX->ShowMonthSurplus(str_SelMonth, 4);
    }

    return 0;
}

/**************************************************/
//   遍历校验 Month收支
/**************************************************/
void CASitfX::CheckMonthTraversal()
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    int int_CRet = 0;

    vector<string> vec_str_Month;
    ptr_XonfigLoader->MonthRangeDuplicator(vec_str_Month);

    vector<string>::iterator itr_Month;
    for(itr_Month = vec_str_Month.begin(); itr_Month != vec_str_Month.end(); itr_Month++)
    {
        if( 0 != CheckMonth(*itr_Month, 0) )
            int_CRet++;
    }

    if( 0 == int_CRet )
    {
        CTool::MassageOutFotmat("Every Month Pass Check :)", '#');
    }
}

/**************************************************/
//   更新 Month收支
/**************************************************/
void CASitfX::UpdateMonth(const string str_SelMonth, int int_OFlag)
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    // Update SubMonth
    vector<string> vec_str_SubMonth;
    ptr_XonfigLoader->SubMonthDuplicator(vec_str_SubMonth);

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
//   遍历更新 Month收支
/**************************************************/
void CASitfX::UpdateMonthTraversal()
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    vector<string> vec_str_Month;
    ptr_XonfigLoader->MonthRangeDuplicator(vec_str_Month);

    vector<string> vec_str_SubMonth;
    ptr_XonfigLoader->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_Month;
    for(itr_Month = vec_str_Month.begin(); itr_Month != vec_str_Month.end(); itr_Month++)
    {
        vector<string>::iterator itr_SubMonth;
        for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
        {
            ptr_FAitfX->UpdateSubMonthExpense(*itr_SubMonth, *itr_Month, false);
        }

        // Update Month
        ptr_FAitfX->UpdateMonthSurplus(*itr_Month, false);
        ptr_FAitfX->SyncMonthSurplus(*itr_Month);
    }

    CTool::MassageOutFotmat("Every Month Updated :)", '#');
}

/**************************************************/
//   展示 Month收支
/**************************************************/
void CASitfX::ShowMonth(const string str_SelMonth)
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    ptr_FAitfX->ShowLife(str_SelMonth, 2);
    ptr_FAitfX->ShowRoom(str_SelMonth, 2);
    ptr_FAitfX->ShowSM(str_SelMonth, 2);
    ptr_FAitfX->ShowMonthSurplus(str_SelMonth, 1);

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析月度趋势 EXP总支出
/**************************************************/
void CASitfX::AnalysisMonthTrend_EXP()
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    vector<TREND_INFO> vec_stc_TrendInfo;
    unsigned int uni_TrendSum = 0;

    uni_TrendSum = ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, "月支出");

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度EXP趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, "EXP");

    cout << endl;
    cout << "--> 月度EXP 累计支出: -" << uni_TrendSum << endl;
    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析月度趋势 LIFE生活支出
/**************************************************/
void CASitfX::AnalysisMonthTrend_LIFE()
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    vector<TREND_INFO> vec_stc_TrendInfo;
    unsigned int uni_TrendSum = 0;

    uni_TrendSum = ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, "生活费");

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度LIFE趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, "LIFE");

    cout << endl;
    cout << "--> 月度LIFE 累计支出: -" << uni_TrendSum << endl;
    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析月度趋势 ROOM租房支出
/**************************************************/
void CASitfX::AnalysisMonthTrend_ROOM()
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    vector<TREND_INFO> vec_stc_TrendInfo;
    unsigned int uni_TrendSum = 0;

    vector<string> vec_str_Room;
    ptr_XonfigLoader->RoomDuplicator(vec_str_Room);

    vector<string>::iterator itr_Room;
    for(itr_Room = vec_str_Room.begin(); itr_Room != vec_str_Room.end(); itr_Room++)
    {
        if(itr_Room == vec_str_Room.begin())
        {
            uni_TrendSum += ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, *itr_Room);
            continue;
        }

        uni_TrendSum += ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, *itr_Room);
    }

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度ROOM趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, "ROOM");

    cout << endl;
    cout << "--> ROOM 累计支出: -" << uni_TrendSum << endl;
    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析月度趋势 CSM消费支出
/**************************************************/
void CASitfX::AnalysisMonthTrend_CSM()
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    vector<TREND_INFO> vec_stc_TrendInfo;
    unsigned int uni_TrendSum = 0;

    vector<string> vec_str_SubMonth;
    ptr_XonfigLoader->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        if(itr_SubMonth == vec_str_SubMonth.begin())
        {
            uni_TrendSum += ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, CMD_SMTranslate(*itr_SubMonth));
            continue;
        }

        uni_TrendSum += ptr_FAitfX->AppendMonthTrendVector(vec_stc_TrendInfo, CMD_SMTranslate(*itr_SubMonth));
    }

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度CSM趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, "CSM");

    cout << endl;
    cout << "--> CSM 累计支出: -" << uni_TrendSum << endl;
    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析 月度变化趋势
/**************************************************/
void CASitfX::AnalysisMonthTrend(const string str_MonthKey)
{
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    vector<TREND_INFO> vec_stc_TrendInfo;
    unsigned int uni_TrendSum = 0;

    // 建构 趋势Vector
    uni_TrendSum = ptr_FAitfX->GenerateMonthTrendVector(vec_stc_TrendInfo, str_MonthKey);

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度趋势分析 ###" << endl;
    cout << endl;

    ptr_FAitfX->DrawMonthTrendVector(vec_stc_TrendInfo, str_MonthKey);

    cout << endl;
    cout << "--> " << str_MonthKey << " 累计支出: -" << uni_TrendSum << endl;
    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   展示 全部月度.M
/**************************************************/
void CASitfX::ShowAllSubMonth(const string str_SelMonth)
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    int int_TotalSMExpense = 0;

    vector<string> vec_str_SubMonth;
    ptr_XonfigLoader->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        int_TotalSMExpense += ptr_FAitfX->ShowSubMonth(*itr_SubMonth, str_SelMonth, 1);
    }

    cout << "----------------------------------------" << endl;
    cout << endl;
    cout << "****************************************" << endl;
    cout << "--> " << str_SelMonth << "月/CSM总支出: " << CTool::TransOutFormat(int_TotalSMExpense) << endl;
    cout << "****************************************" << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   展示.md 全部月度.M
/**************************************************/
void CASitfX::PrintAllSubMonth(const string str_SelMonth, bool bol_NumFlag)
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    cout << "----------------------------------------" << endl;
    cout << "### 全部月度.M 展示.md ###" << endl;
    cout << endl;

    vector<string> vec_str_SubMonth;
    ptr_XonfigLoader->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        ptr_FAitfX->PrintSubMonth(*itr_SubMonth, str_SelMonth, bol_NumFlag, false);
    }

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   展示.md 遍历月度.M
/**************************************************/
void CASitfX::PrintSubMonthTraversal(const string str_SubMonthKey, bool bol_NumFlag)
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    cout << "----------------------------------------" << endl;
    cout << "### 遍历 月度.M 展示.md ###" << endl;
    cout << endl;

    vector<string> vec_str_Month;
    ptr_XonfigLoader->MonthRangeDuplicator(vec_str_Month);

    vector<string>::iterator itr_Month;
    for(itr_Month = vec_str_Month.begin(); itr_Month != vec_str_Month.end(); itr_Month++)
    {
        ptr_FAitfX->PrintSubMonth(str_SubMonthKey, *itr_Month, bol_NumFlag, false);
    }

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   添加NextMonth脚本
/**************************************************/
void CASitfX::AppendNextMonth(const string str_SelMonth)
{
    CXonfigLoader *ptr_XonfigLoader = Singleton<CXonfigLoader>::GetInstance("./FA_Auto_neo.ini");
    CFAitfX *ptr_FAitfX = Singleton<CFAitfX>::GetInstance();

    string str_NextMonth = CTool::GenerateNextMonth(str_SelMonth);

    // 修改Script
    ptr_XonfigLoader->ModifyCurrentMonth(str_NextMonth);

    // 添加Sum脚本
    ptr_FAitfX->AddScriptSum(str_NextMonth);

    // 添加Month脚本
    ptr_FAitfX->AddScriptMonth(str_NextMonth);

    // 添加SubMonth脚本
    vector<string> vec_str_SubMonth;
    ptr_XonfigLoader->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        ptr_FAitfX->AddScriptSubMonth(*itr_SubMonth, str_NextMonth);
    }
}


//------------------------------//
//   River flows in summer
//------------------------------//
