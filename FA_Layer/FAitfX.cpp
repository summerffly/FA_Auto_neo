
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "FAitfX.h"

#include "./../X_Frame/DefLib.h"

using namespace std;


// tips 番茄@20171211 - 使用带参宏函数Key填错会有风险，用m_cls_FM_SUM的head进行校验
#define FM_SUBMONTH(str)  ((!(str).compare("Books"))?(m_cls_FM_sm_Books):\
                           ((!(str).compare("KEEP"))?(m_cls_FM_sm_KEEP):\
                           ((!(str).compare("TB"))?(m_cls_FM_sm_TB):\
                           ((!(str).compare("sa"))?(m_cls_FM_sm_sa):(m_cls_FM_SUM)))) )

// tips 番茄@20171211 - 使用带参宏函数Key填错会有风险，用m_cls_FM_SUM的head进行校验
#define FM_TITLE(str)  ((!(str).compare("DK"))?(m_cls_FM_tt_DK):\
                        ((!(str).compare("NS"))?(m_cls_FM_tt_NS):\
                        ((!(str).compare("travel"))?(m_cls_FM_tt_travel):\
                        ((!(str).compare("lottery"))?(m_cls_FM_tt_lottery):(m_cls_FM_SUM)))) )

/**************************************************/
//   CFAitfX 构造函数
/**************************************************/
CFAitfX::CFAitfX()
{
    m_int_OriginSum = 0;
    m_int_CurrentSum = 0;

    m_int_MonthSalarySum = 0;
    m_int_MonthExpenseSum = 0;
    m_int_MonthSurplusSum = 0;

    m_int_TitleSum = 0;
    m_int_TailSum = 0;
    m_int_CAFSum = 0;

    m_cls_FM_SUM = CFileManager("./FA_SUM.md");
    m_cls_FM_life = CFileManager("./life.M.md");
    m_cls_FM_sm_Books = CFileManager("./Books.M.md");
    m_cls_FM_sm_KEEP = CFileManager("./KEEP.M.md");
    m_cls_FM_sm_TB = CFileManager("./TB.M.md");
    m_cls_FM_sm_sa = CFileManager("./sa.M.md");
    m_cls_FM_tt_DK = CFileManager("./DK.md");
    m_cls_FM_tt_NS = CFileManager("./NS.md");
    m_cls_FM_tt_travel = CFileManager("./travel.md");
    m_cls_FM_tt_lottery = CFileManager("./lottery.md");
    m_cls_FM_temp_BOX = CFileManager("./temp.BOX.md");
}

/**************************************************/
//   CFAitfX 构造函数
/**************************************************/
CFAitfX::~CFAitfX()
{
    // Nothing To Do
}

/**************************************************/
//   读取 初始&当前Sum
/**************************************************/
void CFAitfX::LoadSum(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    string str_OriginSum = ptr_ScriptRipper->GetOriginSum();
    string str_CurrentSum = ptr_ScriptRipper->GetCurrentSum();

    unsigned int uni_SumLine = 0;

    m_cls_FM_SUM.SearchLineKey(str_OriginSum.c_str());
    uni_SumLine = m_cls_FM_SUM.GetSearchLineIndex(1);
    m_int_OriginSum = m_cls_FM_SUM.GetLineValue(uni_SumLine);

    m_cls_FM_SUM.SearchLineKey(str_CurrentSum.c_str());
    uni_SumLine = m_cls_FM_SUM.GetSearchLineIndex(1);
    m_int_CurrentSum = m_cls_FM_SUM.GetLineValue(uni_SumLine);

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << str_OriginSum << ": " << CTool::TransOutFormat(m_int_OriginSum) << endl;
        cout << str_CurrentSum << ": " << CTool::TransOutFormat(m_int_CurrentSum) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   汇总 Month累计收支
/**************************************************/
void CFAitfX::SummerizeMonth(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_MonthSalarySum = 0;
    int int_MonthExpenseSum = 0;
    int int_MonthSurplusSum = 0;

    vector<string> vec_str_MonthRange;
    ptr_ScriptRipper->MonthRangeDuplicator(vec_str_MonthRange);

    string str_MonthKey;
    unsigned int uni_MonthLine = 0;

    vector<string>::iterator itr_Month;
    for(itr_Month = vec_str_MonthRange.begin(); itr_Month != vec_str_MonthRange.end(); itr_Month++)
    {
        str_MonthKey = "## life." + *itr_Month;
        m_cls_FM_SUM.SearchLineKey(str_MonthKey.c_str());
        uni_MonthLine = m_cls_FM_SUM.GetSearchLineIndex(1);

        int_MonthSalarySum += m_cls_FM_SUM.GetLineValue(uni_MonthLine+1);
        int_MonthExpenseSum += m_cls_FM_SUM.GetLineValue(uni_MonthLine+2);
        int_MonthSurplusSum += m_cls_FM_SUM.GetLineValue(uni_MonthLine+3);
    }

    m_int_MonthSalarySum = int_MonthSalarySum;
    m_int_MonthExpenseSum = int_MonthExpenseSum;
    m_int_MonthSurplusSum = int_MonthSurplusSum;

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << "### Month累计收支统计 ###" << endl;
        cout << endl;

        cout << "Month累计收入: " << CTool::TransOutFormat(m_int_MonthSalarySum) << endl;
        cout << "Month累计支出: " << CTool::TransOutFormat(m_int_MonthExpenseSum) << endl;
        cout << "Month累计结余: " << CTool::TransOutFormat(m_int_MonthSurplusSum) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   汇总 Title累计收支
/**************************************************/
void CFAitfX::SummerizeTitle(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_TitleSum = 0;

    vector<string> vec_str_Title;
    ptr_ScriptRipper->TitleDuplicator(vec_str_Title);

    string str_TitleKey;
    unsigned int uni_TitleLine = 0;

    vector<string>::iterator itr_Title;
    for(itr_Title = vec_str_Title.begin(); itr_Title != vec_str_Title.end(); itr_Title++)
    {
        str_TitleKey = "## " + *itr_Title;
        m_cls_FM_SUM.SearchLineKey(str_TitleKey.c_str());
        uni_TitleLine = m_cls_FM_SUM.GetSearchLineIndex(1);

        int int_TitleCount = m_cls_FM_SUM.GetLineValue(uni_TitleLine+1);
        int_TitleSum += int_TitleCount;

        if(int_OFlag == 1)
        {
            cout << *itr_Title << ": " << CTool::TransOutFormat(int_TitleCount) << endl;
        }
    }

    m_int_TitleSum = int_TitleSum;

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << "### Title累计统计 ###" << endl;
        cout << endl;

        cout << "Title累计支出: " << CTool::TransOutFormat(m_int_TitleSum) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   汇总 Tail累计收支
/**************************************************/
void CFAitfX::SummerizeTail(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_TailSum = 0;

    vector<string> vec_str_Tail;
    ptr_ScriptRipper->TailDuplicator(vec_str_Tail);

    string str_TailKey;
    unsigned int uni_TailLine = 0;

    vector<string>::iterator itr_Tail;
    for(itr_Tail = vec_str_Tail.begin(); itr_Tail != vec_str_Tail.end(); itr_Tail++)
    {
        str_TailKey = *itr_Tail;
        m_cls_FM_SUM.SearchLineKey(str_TailKey.c_str());
        uni_TailLine = m_cls_FM_SUM.GetSearchLineIndex(1);

        int int_TailCount = m_cls_FM_SUM.GetLineValue(uni_TailLine);
        int_TailSum += int_TailCount;

        if(int_OFlag == 1)
        {
            cout << *itr_Tail << ": " << CTool::TransOutFormat(int_TailCount) << endl;
        }
    }

    m_int_TailSum = int_TailSum;

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << "### Tail累计统计 ###" << endl;
        cout << endl;

        cout << "Tail累计收支: " << CTool::TransOutFormat(m_int_TailSum) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   汇总 CAF累计收支
/**************************************************/
void CFAitfX::SummerizeCAF(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_CAFSum = 0;

    vector<string> vec_str_CAF;
    ptr_ScriptRipper->CAFDuplicator(vec_str_CAF);

    string str_CAFKey;
    unsigned int uni_CAFLine = 0;

    vector<string>::iterator itr_CAF;
    for(itr_CAF = vec_str_CAF.begin(); itr_CAF != vec_str_CAF.end(); itr_CAF++)
    {
        str_CAFKey = *itr_CAF;
        m_cls_FM_SUM.SearchLineKey(str_CAFKey.c_str());
        uni_CAFLine = m_cls_FM_SUM.GetSearchLineIndex(1);

        int int_CAFCount = m_cls_FM_SUM.GetLineValue(uni_CAFLine);
        int_CAFSum += int_CAFCount;

        if(int_OFlag == 1)
        {
            cout << *itr_CAF << ": " << CTool::TransOutFormat(int_CAFCount) << endl;
        }
    }

    m_int_CAFSum = int_CAFSum;

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << "### CAF累计统计 ###" << endl;
        cout << endl;

        cout << "CAF累计收支: " << CTool::TransOutFormat(m_int_CAFSum) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   更新 当前财富
/**************************************************/
void CFAitfX::UpdateCurrentSum(const int int_CurrentSum)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    string str_CurrentSum = ptr_ScriptRipper->GetCurrentSum();
    m_cls_FM_SUM.SearchLineKey(str_CurrentSum.c_str());
    unsigned int uni_SumLine = m_cls_FM_SUM.GetSearchLineIndex(1);
    m_cls_FM_SUM.ModifyLineValue(uni_SumLine, int_CurrentSum);
}

/**************************************************/
//   更新 CAF
//   默认逻辑最后项扣费
/**************************************************/
void CFAitfX::UpdateCAF(const int int_CAFSum)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    vector<string> vec_str_CAF;
    ptr_ScriptRipper->CAFDuplicator(vec_str_CAF);

    string str_CAFKey;
    unsigned int uni_CAFLine = 0;
    int int_CAFCount = 0;
    int int_CAFSumRest = int_CAFSum;

    vector<string>::iterator itr_CAF;
    for(itr_CAF = vec_str_CAF.begin(); itr_CAF != vec_str_CAF.end(); itr_CAF++)
    {
        str_CAFKey = *itr_CAF;
        m_cls_FM_SUM.SearchLineKey(str_CAFKey.c_str());
        uni_CAFLine = m_cls_FM_SUM.GetSearchLineIndex(1);
        int_CAFCount = m_cls_FM_SUM.GetLineValue(uni_CAFLine);
        int_CAFSumRest -= int_CAFCount;
    }
    int_CAFSumRest += int_CAFCount;   // tips 番茄@20189604 - 补加最后项

    m_cls_FM_SUM.ModifyLineValue(uni_CAFLine, int_CAFSumRest);
}

/**************************************************/
//   增加行 life.M
/**************************************************/
void CFAitfX::InsertMonth(const unsigned int uni_VecIndex, const int int_LineValue, const string str_LineContent)
{
    //m_cls_FM_life.InsertLine(uni_VecIndex, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);
}

/**************************************************/
//   校验 life.M 月度支出
/**************************************************/
int CFAitfX::CheckMonthExpense(const string str_SelMonth, bool bol_OFlag)
{
    string str_RangeTop("## life.M");
    str_RangeTop += str_SelMonth;
    string str_RangeBottom("## life.M");
    str_RangeBottom += CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    int int_MonthExpenseEX = m_cls_FM_life.GetLineValue(uni_RangeTop+2);
    int int_MonthExpenseCK = m_cls_FM_life.CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_SelMonth << "月/支出 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(m_cls_FM_life.GetLineValue(uni_RangeTop+2)) << endl;
        cout << "校验值: " << CTool::TransOutFormat(int_MonthExpenseCK) << endl;
        cout << "----------------------------------------" << endl;
    }

    if( int_MonthExpenseEX == int_MonthExpenseCK )
    {
        return 0;   // 0 >>> 支出读取值 == 校验值
    }
    else
    {
        return -1;   // -1 >>> 支出读取值 != 校验值
    }
}

/**************************************************/
//   校验 life.M 月度收支
/**************************************************/
int CFAitfX::CheckMonthSurplus(const string str_SelMonth, bool bol_OFlag)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_SUM.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_AFLine = m_cls_FM_SUM.GetSearchLineIndex(1);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    unsigned int uni_AFMonthSalaryEX = m_cls_FM_SUM.GetLineValue(uni_AFLine+1);
    int int_AFMonthExpenseEX = m_cls_FM_SUM.GetLineValue(uni_AFLine+2);
    int int_AFMonthRestEX = m_cls_FM_SUM.GetLineValue(uni_AFLine+3);

    unsigned int uni_MonthSalaryEX = m_cls_FM_life.GetLineValue(uni_RangeTop+1);
    int int_MonthExpenseEX = m_cls_FM_life.GetLineValue(uni_RangeTop+2);
    int int_MonthExpenseCK = m_cls_FM_life.CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);
    int int_MonthRestEX = m_cls_FM_life.GetLineValue(uni_RangeTop+3);
    int int_MonthRestCK = uni_MonthSalaryEX + int_MonthExpenseCK;

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_SelMonth << "月/薪资 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(uni_MonthSalaryEX) << endl;
        cout << "### " << str_SelMonth << "月/支出 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(int_MonthExpenseEX) << endl;
        cout << "校验值: " << CTool::TransOutFormat(int_MonthExpenseCK) << endl;
        cout << "### " << str_SelMonth << "月/结余 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(int_MonthRestEX) << endl;
        cout << "校验值: " << CTool::TransOutFormat(int_MonthRestCK) << endl;
        cout << "----------------------------------------" << endl;
    }

    if( int_MonthExpenseEX != int_MonthExpenseCK )
    {
        return -1;
    }
    else if( int_MonthRestEX != int_MonthRestCK )
    {
        return -2;
    }
    else if( uni_MonthSalaryEX != uni_AFMonthSalaryEX )
    {
        return -3;
    }
    else if( int_MonthExpenseEX != int_AFMonthExpenseEX )
    {
        return -4;
    }
    else if( int_MonthRestEX !=  int_AFMonthRestEX )
    {
        return -5;
    }
    else
    {
        return 0;
    }
}

/**************************************************/
//   更新 life.M 月度收支
/**************************************************/
void CFAitfX::UpdateMonthSurplus(const string str_SelMonth, bool bol_OFlag)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    unsigned int uni_MonthSalaryEX = m_cls_FM_life.GetLineValue(uni_RangeTop+1);
    int int_MonthExpenseEX = m_cls_FM_life.GetLineValue(uni_RangeTop+2);
    int int_MonthSurplusEX = m_cls_FM_life.GetLineValue(uni_RangeTop+3);
    int int_MonthExpenseUD = m_cls_FM_life.CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);
    int int_MonthSurplusUD = uni_MonthSalaryEX + int_MonthExpenseUD;

    m_cls_FM_life.ModifyLineValue(uni_RangeTop+2, int_MonthExpenseUD);
    m_cls_FM_life.ModifyLineValue(uni_RangeTop+3, int_MonthSurplusUD);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### 更新" << str_SelMonth << "月/收支 ###" << endl;
        cout << "初始薪资值: " << CTool::TransOutFormat(uni_MonthSalaryEX) << endl;
        cout << "初始支出值: " << CTool::TransOutFormat(int_MonthExpenseEX) << endl;
        cout << "初始结余值: " << CTool::TransOutFormat(int_MonthSurplusEX) << endl;
        cout << "----------------------------------------" << endl;
        cout << "更新支出值: " << CTool::TransOutFormat(int_MonthExpenseUD) << endl;
        cout << "更新结余值: " << CTool::TransOutFormat(int_MonthSurplusUD) << endl;
        cout << "----------------------------------------" << endl;
    }   
}

/**************************************************/
//   修改 life.M 月度收支
//   默认为单行增加支出的操作
/**************************************************/
void CFAitfX::ModifyMonthSurplus(const string str_SelMonth, const string str_MonthKey,\
                                 const unsigned int uni_ModValueABS)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchRangeLineKey(str_MonthKey.c_str(), uni_RangeTop, uni_RangeBottom);
    unsigned int uni_KeyLine = m_cls_FM_life.GetSearchLineIndex(1);

    // tips 番茄@20171209 - 手动可能输错的地方，增加ERROR校验
    if(m_cls_FM_life.GetSearchFullLine(1).compare("ERROR") == 0)
    {
        CTool::MassageOutFotmat("No Line Contain Input Key", '!');
        return;
    }

    // 修改 单行金额
    int int_LineValue = m_cls_FM_life.GetLineValue(uni_KeyLine);
    m_cls_FM_life.ModifyLineValue(uni_KeyLine, int_LineValue-uni_ModValueABS);

    cout << m_cls_FM_life.GetSearchFullLine(1) << endl;

    // 读取 初始收支金额
    unsigned int uni_MonthSalary = m_cls_FM_life.GetLineValue(uni_RangeTop+1);
    int int_MonthExpense = m_cls_FM_life.GetLineValue(uni_RangeTop+2);
    int int_MonthSurplus = m_cls_FM_life.GetLineValue(uni_RangeTop+3);

    // 计算 更新收支金额
    int int_MonthExpenseUD = m_cls_FM_life.CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);
    int int_MonthSurplusUD = uni_MonthSalary + int_MonthExpenseUD;

    // 修改 更新收支金额
    m_cls_FM_life.ModifyLineValue(uni_RangeTop+2, int_MonthExpenseUD);
    m_cls_FM_life.ModifyLineValue(uni_RangeTop+3, int_MonthSurplusUD);

    cout << "----------------------------------------" << endl;
    cout << "### 更新" << str_SelMonth << "月/收支 ###" << endl;
    cout << "初始薪资值: " << CTool::TransOutFormat(uni_MonthSalary) << endl;
    cout << "初始支出值: " << CTool::TransOutFormat(int_MonthExpense) << endl;
    cout << "初始结余值: " << CTool::TransOutFormat(int_MonthSurplus) << endl;
    cout << "----------------------------------------" << endl;
    cout << "修改支出值: " << CTool::TransOutFormat(int_MonthExpenseUD) << endl;
    cout << "修改结余值: " << CTool::TransOutFormat(int_MonthSurplusUD) << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   同步 life.M 月度收支 >>> 总收支
/**************************************************/
void CFAitfX::SyncMonthSurplus(const string str_SelMonth)
{
    string str_SelMonthFL = "## life.M" + str_SelMonth;   // tips 番茄@20171219 - FullLine

    m_cls_FM_life.SearchLineKey(str_SelMonthFL.c_str());
    unsigned int uni_SelMonth = m_cls_FM_life.GetSearchLineIndex(1);

    m_cls_FM_SUM.SearchLineKey(str_SelMonthFL.c_str());
    unsigned int uni_AFSelMonth = m_cls_FM_SUM.GetSearchLineIndex(1);

    // 读取 life.M 月度收支
    unsigned int uni_MonthSalary = m_cls_FM_life.GetLineValue(uni_SelMonth+1);
    int int_MonthExpense = m_cls_FM_life.GetLineValue(uni_SelMonth+2);
    int int_MonthSurplus = m_cls_FM_life.GetLineValue(uni_SelMonth+3);

    // 同步 总收支
    m_cls_FM_SUM.ModifyLineValue(uni_AFSelMonth+1, uni_MonthSalary);
    m_cls_FM_SUM.ModifyLineValue(uni_AFSelMonth+2, int_MonthExpense);
    m_cls_FM_SUM.ModifyLineValue(uni_AFSelMonth+3, int_MonthSurplus);
}

/**************************************************/
//   校验 子项.M 月度支出
/**************************************************/
int CFAitfX::CheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth, bool bol_OFlag)
{
    if(FM_SUBMONTH(str_SubMonthKey).GetFullLine(1).compare("# Financial Allocation of SUMMARY") == 0)
    {
        CTool::MassageOutFotmat("SubMonth KeyWord Error", '!');
        return -9;
    }

    string str_RangeTop = str_SubMonthKey + ".M" + str_SelMonth;
    string str_RangeBottom = str_SubMonthKey + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_lifeLine = m_cls_FM_life.GetSearchLineIndex(1);

    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);
    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);

    int int_LMSubMonthExpenseEX = m_cls_FM_life.GetLineValue(uni_lifeLine);
    int int_SubMonthExpenseEX = FM_SUBMONTH(str_SubMonthKey).GetLineValue(uni_RangeTop+1);
    int int_SubMonthExpenseCK = FM_SUBMONTH(str_SubMonthKey).CountRangeType(uni_RangeTop+2, uni_RangeBottom-1,\
                                       LTYPE_FBIRC_LINEUINT);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_SelMonth << "月/" << str_SubMonthKey << "支出 ###" << endl;
        cout << "life.M_读取值: " << CTool::TransOutFormat(int_LMSubMonthExpenseEX) << endl;
        cout << "sub.M_读取值: " << CTool::TransOutFormat(int_SubMonthExpenseEX) << endl;
        cout << "sub.M_校验值: " << CTool::TransOutFormat(int_SubMonthExpenseCK) << endl;
        cout << "----------------------------------------" << endl;
    }

    if( int_SubMonthExpenseCK != int_SubMonthExpenseEX )
    {
        return -1;
    }
    else if( int_SubMonthExpenseCK != int_LMSubMonthExpenseEX )
    {
        return -2;
    }
    else
    {
        return 0;
    }
}

/**************************************************/
//   更新 子项.M 月度支出
/**************************************************/
void CFAitfX::UpdateSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth, bool bol_OFlag)
{
    if(FM_SUBMONTH(str_SubMonthKey).GetFullLine(1).compare("# Financial Allocation of SUMMARY") == 0)
    {
        CTool::MassageOutFotmat("SubMonth KeyWord Error", '!');
        return;
    }

    string str_RangeTop = str_SubMonthKey + ".M" + str_SelMonth;
    string str_RangeBottom = str_SubMonthKey + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_lifeLine = m_cls_FM_life.GetSearchLineIndex(1);

    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);
    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);

    int int_SubMonthExpense = FM_SUBMONTH(str_SubMonthKey).GetLineValue(uni_RangeTop+1);
    int int_SubMonthExpenseUD = FM_SUBMONTH(str_SubMonthKey).CountRangeType(uni_RangeTop+2, uni_RangeBottom-1,\
                                            LTYPE_FBIRC_LINEUINT);
    
    m_cls_FM_life.ModifyLineValue(uni_lifeLine, int_SubMonthExpenseUD);
    FM_SUBMONTH(str_SubMonthKey).ModifyLineValue(uni_RangeTop+1, int_SubMonthExpenseUD);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_SelMonth << "月/" << str_SubMonthKey << "支出 ###" << endl;
        cout << "sub.M_初始值: " << CTool::TransOutFormat(int_SubMonthExpense) << endl;
        cout << "sub.M_更新值: " << CTool::TransOutFormat(int_SubMonthExpenseUD) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   添加行 子项.M 月度支出
/**************************************************/
void CFAitfX::AppendSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth,\
                                    const int int_LineValue, const string str_LineContent)
{
    if(FM_SUBMONTH(str_SubMonthKey).GetFullLine(1).compare("# Financial Allocation of SUMMARY") == 0)
    {
        CTool::MassageOutFotmat("SubMonth KeyWord Error", '!');
        return;
    }

    string str_RangeTop = str_SubMonthKey + ".M" + str_SelMonth;
    string str_RangeBottom = str_SubMonthKey + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_lifeLine = m_cls_FM_life.GetSearchLineIndex(1);

    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);
    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);

    int int_SubMonthExpense = FM_SUBMONTH(str_SubMonthKey).GetLineValue(uni_RangeTop+1);

    FM_SUBMONTH(str_SubMonthKey).InsertLine(uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);

    // tips 番茄@20171212 - 注意计算总支出的时候要增加一行
    int int_SubMonthExpenseAP = FM_SUBMONTH(str_SubMonthKey).CountRangeType(uni_RangeTop+2, uni_RangeBottom,\
                                            LTYPE_FBIRC_LINEUINT);
    
    m_cls_FM_life.ModifyLineValue(uni_lifeLine, int_SubMonthExpenseAP);
    FM_SUBMONTH(str_SubMonthKey).ModifyLineValue(uni_RangeTop+1, int_SubMonthExpenseAP);

    cout << "----------------------------------------" << endl;
    cout << "### " << str_SelMonth << "月/" << str_SubMonthKey << "支出 ###" << endl;
    cout << "sub.M_初始值: " << CTool::TransOutFormat(int_SubMonthExpense) << endl;
    cout << "sub.M_更新值: " << CTool::TransOutFormat(int_SubMonthExpenseAP) << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   校验 Tt分项 月度支出
/**************************************************/
int CFAitfX::CheckTitleExpense(const string str_TitleKey, bool bol_OFlag)
{
    if(FM_TITLE(str_TitleKey).GetFullLine(1).compare("# Financial Allocation of SUMMARY") == 0)
    {
        CTool::MassageOutFotmat("Title KeyWord Error", '!');
        return -9;
    }

    string str_RangeTop = "## " + str_TitleKey;
    string str_RangeBottom("## Total");

    m_cls_FM_SUM.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_AFLine = m_cls_FM_SUM.GetSearchLineIndex(1);

    unsigned int uni_RangeTop = 2;
    FM_TITLE(str_TitleKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_TITLE(str_TitleKey).GetSearchLineIndex(1);

    int int_AFTitleExpenseEX = m_cls_FM_SUM.GetLineValue(uni_AFLine+1);

    int int_TitleExpenseEX = FM_TITLE(str_TitleKey).GetLineValue(uni_RangeBottom+2);
    int int_TitleExpenseCK = FM_TITLE(str_TitleKey).CountRangeType(uni_RangeTop, uni_RangeBottom-1,\
                                       LTYPE_FBIRC_LINEUINT);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_TitleKey << "/支出 ###" << endl;
        cout << "AF_读取值: " << CTool::TransOutFormat(int_AFTitleExpenseEX) << endl;
        cout << "Tt_读取值: " << CTool::TransOutFormat(int_TitleExpenseEX) << endl;
        cout << "Tt_校验值: " << CTool::TransOutFormat(int_TitleExpenseCK) << endl;
        cout << "----------------------------------------" << endl;
    }

    if( int_TitleExpenseCK != int_TitleExpenseEX )
    {
        return -1;
    }
    else if( int_TitleExpenseCK != int_AFTitleExpenseEX )
    {
        return -2;
    }
    else
    {
        return 0;
    }
}

/**************************************************/
//   更新 Tt分项 月度支出
/**************************************************/
void CFAitfX::UpdateTitleExpense(const string str_TitleKey, bool bol_OFlag)
{
    if(FM_TITLE(str_TitleKey).GetFullLine(1).compare("# Financial Allocation of SUMMARY") == 0)
    {
        CTool::MassageOutFotmat("Title KeyWord Error", '!');
        return;
    }

    string str_RangeTop = "## " + str_TitleKey;
    string str_RangeBottom("## Total");

    m_cls_FM_SUM.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_AFLine = m_cls_FM_SUM.GetSearchLineIndex(1);

    unsigned int uni_RangeTop = 2;
    FM_TITLE(str_TitleKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_TITLE(str_TitleKey).GetSearchLineIndex(1);

    int int_TitleExpense = FM_TITLE(str_TitleKey).GetLineValue(uni_RangeBottom+2);
    int int_TitleExpenseUD = FM_TITLE(str_TitleKey).CountRangeType(uni_RangeTop, uni_RangeBottom-1,\
                                      LTYPE_FBIRC_LINEUINT);

    FM_TITLE(str_TitleKey).ModifyLineValue(uni_RangeBottom+2, int_TitleExpenseUD);
    m_cls_FM_SUM.ModifyLineValue(uni_AFLine+1, int_TitleExpenseUD);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_TitleKey << "/支出 ###" << endl;
        cout << "Tt_初始值: " << CTool::TransOutFormat(int_TitleExpense) << endl;
        cout << "Tt_更新值: " << CTool::TransOutFormat(int_TitleExpenseUD) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   添加行 Tt分项 月度支出
/**************************************************/
void CFAitfX::AppendTitleExpense(const string str_TitleKey,\
                                 const int int_LineValue, const string str_LineContent)
{
    if(FM_TITLE(str_TitleKey).GetFullLine(1).compare("# Financial Allocation of SUMMARY") == 0)
    {
        CTool::MassageOutFotmat("Title KeyWord Error", '!');
        return;
    }

    string str_RangeTop = "## " + str_TitleKey;
    string str_RangeBottom("## Total");

    m_cls_FM_SUM.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_AFLine = m_cls_FM_SUM.GetSearchLineIndex(1);

    unsigned int uni_RangeTop = 2;
    FM_TITLE(str_TitleKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_TITLE(str_TitleKey).GetSearchLineIndex(1);

    int int_TitleExpense = FM_TITLE(str_TitleKey).GetLineValue(uni_RangeBottom+2);

    FM_TITLE(str_TitleKey).InsertLine(uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);

    // tips 番茄@20171212 - 注意计算总支出的时候要增加一行
    int int_TitleExpenseAP = FM_TITLE(str_TitleKey).CountRangeType(uni_RangeTop, uni_RangeBottom,\
                                      LTYPE_FBIRC_LINEUINT);

    // tips 番茄@20171212 - 注意计算总支出的时候要增加一行
    FM_TITLE(str_TitleKey).ModifyLineValue(uni_RangeBottom+3, int_TitleExpenseAP);
    m_cls_FM_SUM.ModifyLineValue(uni_AFLine+1, int_TitleExpenseAP);

    cout << "----------------------------------------" << endl;
    cout << "### " << str_TitleKey << "/支出 ###" << endl;
    cout << "Tt_初始值: " << CTool::TransOutFormat(int_TitleExpense) << endl;
    cout << "Tt_更新值: " << CTool::TransOutFormat(int_TitleExpenseAP) << endl;
    cout << "----------------------------------------" << endl;
}

void CFAitfX::AppendLottery(const bool bol_LineFlag, const unsigned int uni_LineValueABS,\
                            const string str_LineDate)
{
    string str_LotteryTop("## lottery");
    string str_LotteryBottom("## Total");

    m_cls_FM_SUM.SearchLineKey(str_LotteryTop.c_str());
    unsigned int uni_AFLine = m_cls_FM_SUM.GetSearchLineIndex(1);

    unsigned int uni_LotteryTop = 2;
    m_cls_FM_tt_lottery.SearchLineKey(str_LotteryBottom.c_str());
    unsigned int uni_LotteryBottom = m_cls_FM_tt_lottery.GetSearchLineIndex(1);

    int int_LotterySurplus = m_cls_FM_tt_lottery.GetLineValue(uni_LotteryBottom+2);

    string str_LineContent("足彩");
    int int_LineValue = 0;
    if( bol_LineFlag )
    {
        int_LineValue = uni_LineValueABS;
        str_LineContent += "收入_";
    }
    else
    {
        int_LineValue = (-1) * uni_LineValueABS;
        str_LineContent += "支出_";
    }
    str_LineContent += str_LineDate;

    m_cls_FM_tt_lottery.InsertLine(uni_LotteryBottom-1, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);

    // tips 番茄@20171212 - 注意计算总支出的时候要增加一行
    int int_LotterySurplusAP = m_cls_FM_tt_lottery.CountRangeType(uni_LotteryTop, uni_LotteryBottom,\
                                                                  LTYPE_FBIRC_LINEUINT);

    // tips 番茄@20171212 - 注意计算总支出的时候要增加一行
    m_cls_FM_tt_lottery.ModifyLineValue(uni_LotteryBottom+3, int_LotterySurplusAP);
    m_cls_FM_SUM.ModifyLineValue(uni_AFLine+1, int_LotterySurplusAP);

    // tips 番茄@20171225 - 在支出前，增加一行空行
    if(!bol_LineFlag)
    {
        m_cls_FM_tt_lottery.InsertBlankLine(uni_LotteryBottom-1);
    }

    cout << "----------------------------------------" << endl;
    cout << "### lottery ###" << endl;
    cout << "lottery_初始值: " << CTool::TransOutFormat(int_LotterySurplus) << endl;
    cout << "lottery_更新值: " << CTool::TransOutFormat(int_LotterySurplusAP) << endl;
    cout << "----------------------------------------" << endl;
}

void CFAitfX::TransferBalance(const string str_FirstKey, const string str_SecondKey,
                              const bool bol_TransferFlag, const unsigned int uni_BalanceValueABS)
{
    m_cls_FM_SUM.SearchLineKey(str_FirstKey.c_str());
    unsigned int uni_FirstLine = m_cls_FM_SUM.GetSearchLineIndex(1);
    int int_FirstValue = m_cls_FM_SUM.GetLineValue(uni_FirstLine);

    m_cls_FM_SUM.SearchLineKey(str_SecondKey.c_str());
    unsigned int uni_SecondLine = m_cls_FM_SUM.GetSearchLineIndex(1);
    int int_SecondValue = m_cls_FM_SUM.GetLineValue(uni_SecondLine);

    // bol_TransferFlag为true >>> First++ Second--
    if( bol_TransferFlag == true )
    {
        m_cls_FM_SUM.ModifyLineValue(uni_FirstLine, int_FirstValue + uni_BalanceValueABS);
        m_cls_FM_SUM.ModifyLineValue(uni_SecondLine, int_SecondValue - uni_BalanceValueABS);
    }
    // bol_TransferFlag为false >>> First-- Second++
    else
    {
        m_cls_FM_SUM.ModifyLineValue(uni_FirstLine, int_FirstValue - uni_BalanceValueABS);
        m_cls_FM_SUM.ModifyLineValue(uni_SecondLine, int_SecondValue + uni_BalanceValueABS);
    }
}

/**************************************************/
//   添加Sum脚本
/**************************************************/
void CFAitfX::AddScriptSum(const string str_SelMonth)
{
    string str_SUMMonthTitle = string("## life.M") + str_SelMonth;
    string str_SUMMonthSalary = str_SelMonth + "月薪资";
    string str_SUMMonthExpense = str_SelMonth + "月支出";
    string str_SUMMonthRest = str_SelMonth + "月结余";

    m_cls_FM_SUM.SearchLineKey("## Summary");
    unsigned int uni_SUMLine = m_cls_FM_SUM.GetSearchLineIndex(1);

    m_cls_FM_SUM.InsertBlankLine(uni_SUMLine-1);
    m_cls_FM_SUM.InsertLine(uni_SUMLine, LTYPE_MONTHTITLE, 0, str_SUMMonthTitle);
    m_cls_FM_SUM.InsertLine(uni_SUMLine+1, LTYPE_FBIRC_MONTHSUM, 0, str_SUMMonthSalary);
    m_cls_FM_SUM.InsertLine(uni_SUMLine+2, LTYPE_FBIRC_MONTHSUM, 0, str_SUMMonthExpense);
    m_cls_FM_SUM.InsertLine(uni_SUMLine+3, LTYPE_FBIRC_MONTHSUM, 0, str_SUMMonthRest);
}

/**************************************************/
//   添加Month脚本
/**************************************************/
void CFAitfX::AddScriptMonth(const string str_SelMonth)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    string str_lifeMonthTitle = string("## life.M") + CTool::GenerateNextMonth(str_SelMonth);
    string str_lifeMonthSalary = CTool::GenerateNextMonth(str_SelMonth) + "月薪资";
    string str_lifeMonthExpense = CTool::GenerateNextMonth(str_SelMonth) + "月支出";
    string str_lifeMonthRest = CTool::GenerateNextMonth(str_SelMonth) + "月结余";

    m_cls_FM_life.SearchLineKey("---");
    unsigned int uni_lifeLine = m_cls_FM_life.GetSearchLineIndex(1);

    m_cls_FM_life.InsertBlankLine(uni_lifeLine-4);
    m_cls_FM_life.InsertLine(uni_lifeLine-3, LTYPE_MONTHTITLE, 0, str_lifeMonthTitle);
    m_cls_FM_life.InsertLine(uni_lifeLine-2, LTYPE_FBIRC_MONTHSUM, 0, str_lifeMonthSalary);
    m_cls_FM_life.InsertLine(uni_lifeLine-1, LTYPE_FBIRC_MONTHSUM, 0, str_lifeMonthExpense);
    m_cls_FM_life.InsertLine(uni_lifeLine, LTYPE_FBIRC_MONTHSUM, 0, str_lifeMonthRest);

    string str_lifeMonthLife = str_SelMonth;
    str_lifeMonthLife += "月_生活费{&霞}";

    m_cls_FM_life.InsertBlankLine(uni_lifeLine-4);
    m_cls_FM_life.InsertLine(uni_lifeLine-3, LTYPE_FBIRC_LINEUINT, 0, str_lifeMonthLife);
    m_cls_FM_life.InsertBlankLine(uni_lifeLine-2);

    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string>::iterator itr_SubMonth;
    int int_LineCount = 0;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        string str_lifeSM = *itr_SubMonth + ".M" + str_SelMonth;
        m_cls_FM_life.InsertLine(uni_lifeLine-1+int_LineCount, LTYPE_FBIRC_LINEUINT, 0, str_lifeSM);
        int_LineCount++;
    }
}

/**************************************************/
//   添加SubMonth脚本
/**************************************************/
void CFAitfX::AddScriptSubMonth(const string str_SubMonthKey, const string str_SelMonth)
{
    string str_SMTitle = string("## ");
    str_SMTitle += str_SubMonthKey;
    str_SMTitle += ".M";
    str_SMTitle += str_SelMonth;

    FM_SUBMONTH(str_SubMonthKey).SearchLineKey("---");
    unsigned int uni_SMLine = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);

    FM_SUBMONTH(str_SubMonthKey).InsertBlankLine(uni_SMLine-4);
    FM_SUBMONTH(str_SubMonthKey).InsertLine(uni_SMLine-3, LTYPE_MONTHTITLE, 0, str_SMTitle);
    FM_SUBMONTH(str_SubMonthKey).InsertLine(uni_SMLine-2, LTYPE_FBIRC_TITLESUM, 0, "");
    FM_SUBMONTH(str_SubMonthKey).InsertBlankLine(uni_SMLine-1);
    FM_SUBMONTH(str_SubMonthKey).InsertLine(uni_SMLine, LTYPE_FBIRC_LINEUINT, 0, "~");
}

/**************************************************/
//   校验 Temp 支出
/**************************************************/
void CFAitfX::CheckTempExpense()
{
    string str_RangeBottom("---");

    unsigned int uni_RangeTop = 2;
    unsigned int uni_RangeBottom = 0;
    int int_TempExpenseCK = 0;

    m_cls_FM_temp_BOX.SearchLineKey(str_RangeBottom.c_str());
    uni_RangeBottom = m_cls_FM_temp_BOX.GetSearchLineIndex(1);
    int_TempExpenseCK = m_cls_FM_temp_BOX.CountRangeType(uni_RangeTop, uni_RangeBottom-1,\
                                                         LTYPE_FBIRC_LINEUINT);

    cout << "----------------------------------------" << endl;
    cout << "### temp/支出 ###" << endl;
    cout << "Temp_校验值: " << CTool::TransOutFormat(int_TempExpenseCK) << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   生成 月度趋势Vector
/**************************************************/
void CFAitfX::GenerateMonthTrendVector(vector<TREND_INFO> &vec_stc_TrendInfo, const string str_MonthKey)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    
    unsigned int uni_TrendIndex = 0;
    TREND_INFO stc_TrendInfo;

    string str_TrendMonth = ptr_ScriptRipper->GetOriginMonth();
    string str_TerminalMonth = CTool::GenerateNextMonth(ptr_ScriptRipper->GetCurrentMonth());

    while( str_TrendMonth != str_TerminalMonth )
    {
        string str_RangeTop = "## life.M" + str_TrendMonth;
        string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_TrendMonth);

        m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
        unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
        m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
        unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

        if( m_cls_FM_life.SearchRangeLineKey(str_MonthKey.c_str(), uni_RangeTop, uni_RangeBottom) )
        {
            uni_TrendIndex = m_cls_FM_life.GetSearchLineIndex(1);

            stc_TrendInfo.str_TrendMonth = str_TrendMonth;
            stc_TrendInfo.uni_TrendValueABS = m_cls_FM_life.GetLineValueABS(uni_TrendIndex);

            vec_stc_TrendInfo.push_back(stc_TrendInfo);
        }
        else
        {
            stc_TrendInfo.str_TrendMonth = str_TrendMonth;
            stc_TrendInfo.uni_TrendValueABS = 0;

            vec_stc_TrendInfo.push_back(stc_TrendInfo);
        }

        str_TrendMonth = CTool::GenerateNextMonth(str_TrendMonth);
    }
}

/**************************************************/
//   附加 月度趋势Vector
/**************************************************/
void CFAitfX::AppendMonthTrendVector(vector<TREND_INFO> &vec_stc_TrendInfo, const string str_MonthKey)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    unsigned int uni_TrendIndex = 0;
    unsigned int uni_VecIndex = 0;
    TREND_INFO stc_TrendInfo;

    string str_TrendMonth = ptr_ScriptRipper->GetOriginMonth();
    string str_TerminalMonth = CTool::GenerateNextMonth(ptr_ScriptRipper->GetCurrentMonth());

    while( str_TrendMonth != str_TerminalMonth )
    {
        string str_RangeTop = "## life.M" + str_TrendMonth;
        string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_TrendMonth);

        m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
        unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
        m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
        unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

        if( m_cls_FM_life.SearchRangeLineKey(str_MonthKey.c_str(), uni_RangeTop, uni_RangeBottom) )
        {
            uni_TrendIndex = m_cls_FM_life.GetSearchLineIndex(1);
            vec_stc_TrendInfo.at(uni_VecIndex).uni_TrendValueABS += m_cls_FM_life.GetLineValueABS(uni_TrendIndex);
        }

        str_TrendMonth = CTool::GenerateNextMonth(str_TrendMonth);
        uni_VecIndex++;
    }
}

/**************************************************/
//   获取 月度趋势Vector最大值
/**************************************************/
unsigned int CFAitfX::GetMonthTrendVectorMax(const vector<TREND_INFO> vec_stc_TrendInfo)
{
    unsigned int uni_TrendSize = vec_stc_TrendInfo.size();
    unsigned int uni_MaxTrendValue = 0;

    if(uni_TrendSize == 0)
    {
        CTool::MassageOutFotmat("Analysis KeyWord Error", '!');
        return -1;
    }

    for(int i=0; i<uni_TrendSize; i++)
    {
        if( vec_stc_TrendInfo.at(i).uni_TrendValueABS > uni_MaxTrendValue )
        {
            uni_MaxTrendValue = vec_stc_TrendInfo.at(i).uni_TrendValueABS;
        }
    }

    return uni_MaxTrendValue;
}

/**************************************************/
//   绘制 月度趋势Vector
/**************************************************/
void CFAitfX::DrawMonthTrendVector(const vector<TREND_INFO> vec_stc_TrendInfo, const string str_MonthKey)
{
    // 获取 vector最大值
    unsigned int uni_MaxTrendValue = GetMonthTrendVectorMax(vec_stc_TrendInfo);
    double dob_ScaleRate = (double)50 / uni_MaxTrendValue;

    // 绘制 vector
    unsigned int uni_Scalde = 0;
    double dob_GrowRate = 0.0;
    unsigned int uni_preValue = 0;
    unsigned int uni_nextValue = 0;

    unsigned int uni_TrendSize = vec_stc_TrendInfo.size();

    for(int i=0; i<uni_TrendSize; i++)
    {
        cout << vec_stc_TrendInfo.at(i).str_TrendMonth << "月/" << str_MonthKey << ": ";
        uni_Scalde = dob_ScaleRate * vec_stc_TrendInfo.at(i).uni_TrendValueABS;
        for(int i=1; i<=uni_Scalde; i++)
        {
            cout << "█";
        }
        cout << " " << vec_stc_TrendInfo.at(i).uni_TrendValueABS;

        if( 0==i )
        {
            cout << " (-%)" << endl;
        }
        else
        {
            uni_preValue = vec_stc_TrendInfo.at(i-1).uni_TrendValueABS;
            uni_nextValue = vec_stc_TrendInfo.at(i).uni_TrendValueABS;

            if( uni_preValue == 0 )
            {
                dob_GrowRate = 0.0;
            }
            else
            {
                dob_GrowRate = ((double)uni_nextValue - (double)uni_preValue)/(double)uni_preValue;
            }
            
            if( dob_GrowRate == 0.0 )
            {
                cout << " (==)" << endl;
            }
            else
            {
                cout << " (" << CTool::TransOutFormat((int)(dob_GrowRate*100)) << "%)" << endl;
            }
        }
    }
}

/**************************************************/
//   分析 月度变化趋势
/**************************************************/
void CFAitfX::AnalysisMonthTrend(const string str_MonthKey)
{
    vector<TREND_INFO> vec_stc_TrendInfo;

    // 建构 趋势Vector
    GenerateMonthTrendVector(vec_stc_TrendInfo, str_MonthKey);

    // 绘制 趋势Vector
    cout << "----------------------------------------" << endl;
    cout << "### 月度趋势分析 ###" << endl;
    cout << endl;

    DrawMonthTrendVector(vec_stc_TrendInfo, str_MonthKey);

    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   分析 月度支出占比
/**************************************************/
void CFAitfX::AnalysisMonthProportion(const string str_SelMonth)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    if( 0 == m_cls_FM_life.SearchLineKey(str_RangeTop.c_str()) )
    {
        CTool::MassageOutFotmat("Error Month Input", '!');
        return;
    }
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1) + 4;
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1) - 1;

    // 建构 vector
    unsigned int uni_MonthExpenseABS = m_cls_FM_life.GetLineValueABS(uni_RangeTop-2);
    vector<UNIT_INFO> vec_stc_UnitInfo;
    UNIT_INFO stc_UnitInfo;

    for(int i=uni_RangeTop; i<=uni_RangeBottom; i++)
    {
        if( m_cls_FM_life.GetLineType(i)==LTYPE_FBIRC_LINEUINT )
        {
            stc_UnitInfo.str_UnitContent = m_cls_FM_life.GetLineContent(i);
            stc_UnitInfo.uni_UnitValueABS = m_cls_FM_life.GetLineValueABS(i);

            vec_stc_UnitInfo.push_back(stc_UnitInfo);
        }
    }

    // 获取 vector最大值
    unsigned int uni_PPSize = vec_stc_UnitInfo.size();
    unsigned int uni_MaxPPValue = 0;

    for(int i=0; i<uni_PPSize; i++)
    {
        if( vec_stc_UnitInfo.at(i).uni_UnitValueABS > uni_MaxPPValue )
        {
            uni_MaxPPValue = vec_stc_UnitInfo.at(i).uni_UnitValueABS;
        }
    }
    double dob_ScaleRate = (double)50 / uni_MaxPPValue;

    // 绘制 vector
    unsigned int uni_Scalde = 0;
    double dob_PPRate = 0.0;
    cout << "----------------------------------------" << endl;
    cout << "### 月度占比分析 ###" << endl;
    cout << endl;

    for(int i=0; i<uni_PPSize; i++)
    {
        uni_Scalde = dob_ScaleRate * vec_stc_UnitInfo.at(i).uni_UnitValueABS;
        dob_PPRate = (double)vec_stc_UnitInfo.at(i).uni_UnitValueABS / (double)uni_MonthExpenseABS;

        for(int i=0; i<=uni_Scalde; i++)
        {
            cout << "█";
        }
        cout << "  " << vec_stc_UnitInfo.at(i).str_UnitContent << " (";
        printf("%.1f", (dob_PPRate*100));
        cout << "%)" << endl;
    }

    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   展示.md 月度
/**************************************************/
void CFAitfX::ShowMDRawMonth(const string str_SelMonth, bool bol_NumFlag)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    if( bol_NumFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### 月度 展示.md ###" << endl;
        cout << endl;

        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << "【" << i << "】" << m_cls_FM_life.GetFullLine(i) << endl;
        }

        cout << "----------------------------------------" << endl;
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "### 月度 展示.md ###" << endl;
        cout << endl;
                
        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << m_cls_FM_life.GetFullLine(i) << endl;
        }

        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   展示.md 月度.M
/**************************************************/
void CFAitfX::ShowMDRawSubMonth(const string str_SubMonthKey, const string str_SelMonth, bool bol_NumFlag, bool bol_ShowFlag)
{
    string str_RangeTop = str_SubMonthKey + ".M" + str_SelMonth;
    string str_RangeBottom = str_SubMonthKey + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);
    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);

    if( bol_ShowFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### 月度.M .md展示 ###" << endl;
        cout << endl;
    }

    if( bol_NumFlag )
    {
        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << "【" << i << "】" << FM_SUBMONTH(str_SubMonthKey).GetFullLine(i) << endl;
        }
    }
    else
    {           
        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << FM_SUBMONTH(str_SubMonthKey).GetFullLine(i) << endl;
        }
    }

    if( bol_ShowFlag )
    {
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   展示 life.M 月度收支
//   int_ShowFlag == 1 >>> 完整显示模式
//   int_ShowFlag == 2 >>> 衔接显示模式
/**************************************************/
void CFAitfX::ShowMonthSurplus(const string str_SelMonth, int int_ShowFlag)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    unsigned int uni_MonthSalary = m_cls_FM_life.GetLineValue(uni_RangeTop+1);
    int int_MonthExpense = m_cls_FM_life.GetLineValue(uni_RangeTop+2);
    int int_MonthRest = m_cls_FM_life.GetLineValue(uni_RangeTop+3);

    if(int_ShowFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << str_SelMonth << "月/薪资: " << CTool::TransOutFormat(uni_MonthSalary) << endl;
        cout << str_SelMonth << "月/支出: " << CTool::TransOutFormat(int_MonthExpense) << endl;
        cout << str_SelMonth << "月/结余: " << CTool::TransOutFormat(int_MonthRest) << endl;
        cout << "----------------------------------------" << endl;
    }
    else if(int_ShowFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << str_SelMonth << "月/支出: " << CTool::TransOutFormat(int_MonthExpense) << endl;
    }
}

void CFAitfX::SyncAllFile()
{
    m_cls_FM_SUM.SyncFile();
    m_cls_FM_life.SyncFile();
    m_cls_FM_sm_Books.SyncFile();
    m_cls_FM_sm_KEEP.SyncFile();
    m_cls_FM_sm_TB.SyncFile();
    m_cls_FM_sm_sa.SyncFile();
    m_cls_FM_tt_DK.SyncFile();
    m_cls_FM_tt_NS.SyncFile();
    m_cls_FM_tt_travel.SyncFile();
    m_cls_FM_tt_lottery.SyncFile();
    m_cls_FM_temp_BOX.SyncFile();
}

void CFAitfX::WriteAllFile()
{
    m_cls_FM_SUM.UpdateTimeStamp();
    m_cls_FM_life.UpdateTimeStamp();
    m_cls_FM_sm_Books.UpdateTimeStamp();
    m_cls_FM_sm_KEEP.UpdateTimeStamp();
    m_cls_FM_sm_TB.UpdateTimeStamp();
    m_cls_FM_sm_sa.UpdateTimeStamp();
    m_cls_FM_tt_DK.UpdateTimeStamp();
    m_cls_FM_tt_NS.UpdateTimeStamp();
    m_cls_FM_tt_travel.UpdateTimeStamp();
    m_cls_FM_tt_lottery.UpdateTimeStamp();
    m_cls_FM_temp_BOX.UpdateTimeStamp();

    m_cls_FM_SUM.FileWriter();
    m_cls_FM_life.FileWriter();
    m_cls_FM_sm_Books.FileWriter();
    m_cls_FM_sm_KEEP.FileWriter();
    m_cls_FM_sm_TB.FileWriter();
    m_cls_FM_sm_sa.FileWriter();
    m_cls_FM_tt_DK.FileWriter();
    m_cls_FM_tt_NS.FileWriter();
    m_cls_FM_tt_travel.FileWriter();
    m_cls_FM_tt_lottery.FileWriter();
    m_cls_FM_temp_BOX.FileWriter();
}

void CFAitfX::BackUpAllFile(const string str_BackUpPath)
{
    m_cls_FM_SUM.BackUpFile(str_BackUpPath);
    m_cls_FM_life.BackUpFile(str_BackUpPath);
    m_cls_FM_sm_Books.BackUpFile(str_BackUpPath);
    m_cls_FM_sm_KEEP.BackUpFile(str_BackUpPath);
    m_cls_FM_sm_TB.BackUpFile(str_BackUpPath);
    m_cls_FM_sm_sa.BackUpFile(str_BackUpPath);
    m_cls_FM_tt_DK.BackUpFile(str_BackUpPath);
    m_cls_FM_tt_NS.BackUpFile(str_BackUpPath);
    m_cls_FM_tt_travel.BackUpFile(str_BackUpPath);
    m_cls_FM_tt_lottery.BackUpFile(str_BackUpPath);
    m_cls_FM_temp_BOX.BackUpFile(str_BackUpPath);
}


//------------------------------//
//   River flows in summer
//------------------------------//
