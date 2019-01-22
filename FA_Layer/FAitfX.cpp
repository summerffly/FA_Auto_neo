
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "FAitfX.h"

#include "./../X_Frame/DefLib.h"
#include "./../CMD_Handler/DefCMD.h"

using namespace std;


/**************************************************/
//   CFAitfX 构造函数
/**************************************************/
CFAitfX::CFAitfX()
{
    m_int_OriginSum = 0;
    m_int_CurrentSum = 0;
    m_int_CAFSum = 0;

    m_int_MonthSalarySum = 0;
    m_int_MonthExpenseSum = 0;
    m_int_MonthSurplusSum = 0;

    m_int_TitleSum = 0;
    m_int_TailSum = 0;

    // tips 番茄@20180919 - 扩展添加点2/3
    m_ptr_FM_SUM = new CFileManager("./FA_SUM.md");
    m_ptr_FM_life = new CFileManager("./life.M.md");
    m_ptr_FM_sm_DGtler = new CFileManager("./DGtler.M.md");
    m_ptr_FM_sm_Books = new CFileManager("./Books.M.md");
    m_ptr_FM_sm_KEEP = new CFileManager("./KEEP.M.md");
    m_ptr_FM_sm_TB = new CFileManager("./TB.M.md");
    m_ptr_FM_sm_sa = new CFileManager("./sa.M.md");
    m_ptr_FM_tt_DK = new CFileManager("./DK.md");
    m_ptr_FM_tt_NS = new CFileManager("./NS.md");
    m_ptr_FM_tt_NR = new CFileManager("./NR411.md");
    m_ptr_FM_tt_travel = new CFileManager("./travel.md");
    m_ptr_FM_tt_lottery = new CFileManager("./lottery.md");
    m_ptr_FM_tt_BOX = new CFileManager("./BOX.md");
    m_ptr_FM_NULL = NULL;

    m_ptr_FM_array[0] = m_ptr_FM_SUM;
    m_ptr_FM_array[1] = m_ptr_FM_life;
    m_ptr_FM_array[2] = m_ptr_FM_sm_DGtler;
    m_ptr_FM_array[3] = m_ptr_FM_sm_Books;
    m_ptr_FM_array[4] = m_ptr_FM_sm_KEEP;
    m_ptr_FM_array[5] = m_ptr_FM_sm_TB;
    m_ptr_FM_array[6] = m_ptr_FM_sm_sa;
    m_ptr_FM_array[7] = m_ptr_FM_tt_DK;
    m_ptr_FM_array[8] = m_ptr_FM_tt_NS;
    m_ptr_FM_array[9] = m_ptr_FM_tt_NR;
    m_ptr_FM_array[10] = m_ptr_FM_tt_travel;
    m_ptr_FM_array[11] = m_ptr_FM_tt_lottery;
    m_ptr_FM_array[12] = m_ptr_FM_tt_BOX;
}

/**************************************************/
//   CFAitfX 构造函数
/**************************************************/
CFAitfX::~CFAitfX()
{
    // Nothing To Do
}

/**************************************************/
//   Summarize区OFlag输出规范
//   0 >>> 空输出
//   1 >>> 嵌入输出
//   2 >>> 完整输出
//   9 >>> 测试输出
/**************************************************/

/**************************************************/
//   读取 初始&当前&可支配 Sum
/**************************************************/
void CFAitfX::LoadSum(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    string str_OriginSum = ptr_ScriptRipper->GetOriginSum();
    string str_CurrentSum = ptr_ScriptRipper->GetCurrentSum();
    string str_CAFSum = ptr_ScriptRipper->GetCAFSum();

    m_int_OriginSum = m_ptr_FM_SUM->GetUniqueSearchLineValue(str_OriginSum.c_str());
    m_int_CurrentSum = m_ptr_FM_SUM->GetUniqueSearchLineValue(str_CurrentSum.c_str());
    m_int_CAFSum = m_ptr_FM_SUM->GetUniqueSearchLineValue(str_CAFSum.c_str());

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << str_OriginSum << ": " << CTool::TransOutFormat(m_int_OriginSum) << endl;
        cout << str_CurrentSum << ": " << CTool::TransOutFormat(m_int_CurrentSum) << endl;
    }

    if(int_OFlag == 2)
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
void CFAitfX::SummarizeMonth(int int_OFlag)
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
        str_MonthKey = "## life.M" + *itr_Month;
        uni_MonthLine = m_ptr_FM_SUM->GetFirstSearchLineIndex(str_MonthKey.c_str());

        int_MonthSalarySum += m_ptr_FM_SUM->GetLineValue(uni_MonthLine+1);
        int_MonthExpenseSum += m_ptr_FM_SUM->GetLineValue(uni_MonthLine+2);
        int_MonthSurplusSum += m_ptr_FM_SUM->GetLineValue(uni_MonthLine+3);
    }

    m_int_MonthSalarySum = int_MonthSalarySum;
    m_int_MonthExpenseSum = int_MonthExpenseSum;
    m_int_MonthSurplusSum = int_MonthSurplusSum;

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << "Month累计收入: " << CTool::TransOutFormat(m_int_MonthSalarySum) << endl;
        cout << "Month累计支出: " << CTool::TransOutFormat(m_int_MonthExpenseSum) << endl;
        cout << "Month累计结余: " << CTool::TransOutFormat(m_int_MonthSurplusSum) << endl;
    }

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << "### Month累计收支统计 ###" << endl;
        cout << endl;
        cout << "Month累计收入: " << CTool::TransOutFormat(m_int_MonthSalarySum) << endl;
        cout << "Month累计支出: " << CTool::TransOutFormat(m_int_MonthExpenseSum) << endl;
        cout << "Month累计结余: " << CTool::TransOutFormat(m_int_MonthSurplusSum) << endl;
        cout << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   汇总 Month 分类累计收支
/**************************************************/
void CFAitfX::SummarizeMonthCLS(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    /********** Get Month Sum **********/
    m_int_MonthSalarySum = m_ptr_FM_SUM->GetSearchLineValueSum("月薪资");
    m_int_MonthExpenseSum = m_ptr_FM_SUM->GetSearchLineValueSum("月支出");
    m_int_MonthSurplusSum = m_ptr_FM_SUM->GetSearchLineValueSum("月结余");

    /********** Get Life & Room Sum **********/
    int int_MonthLifeSum = m_ptr_FM_life->GetSearchLineValueSum("生活费");
    int int_MonthRoomSum = m_ptr_FM_life->GetSearchLineValueSum("房租");
    int_MonthRoomSum += m_ptr_FM_life->GetSearchLineValueSum("水电费");
    int_MonthRoomSum += m_ptr_FM_life->GetSearchLineValueSum("网络费");

    /********** Get SM Sum **********/
    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    unsigned int uni_SubMonthNum = ptr_ScriptRipper->GetSubMonthNum();

    int *ptr_int_SMSum = new int[uni_SubMonthNum];
    int int_SMindex = 0;

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        string str_SubMonth = CMD_SMTranslate(*itr_SubMonth);
        *(ptr_int_SMSum+int_SMindex) = m_ptr_FM_life->GetSearchLineValueSum(str_SubMonth.c_str());
        int_SMindex++;
    }

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << "--> Month累计收入: " << CTool::TransOutFormat(m_int_MonthSalarySum) << endl;
        cout << "Life累计支出: " << CTool::TransOutFormat(int_MonthLifeSum) << endl;
        cout << "Room累计支出: " << CTool::TransOutFormat(int_MonthRoomSum) << endl;

        int_SMindex = 0;
        for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
        {
            string str_SubMonth = CMD_SMTranslate(*itr_SubMonth);
            cout << str_SubMonth << "累计支出: " << CTool::TransOutFormat(*(ptr_int_SMSum+int_SMindex)) << endl;
            int_SMindex++;
        }

        cout << "--> Month累计支出: " << CTool::TransOutFormat(m_int_MonthExpenseSum) << endl;
        cout << "--> Month累计结余: " << CTool::TransOutFormat(m_int_MonthSurplusSum) << endl;
    }

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << "### Month累计收支统计 ###" << endl;
        cout << endl;

        cout << "--> Month累计收入: " << CTool::TransOutFormat(m_int_MonthSalarySum) << endl;
        cout << endl;

        cout << "Life累计支出: " << CTool::TransOutFormat(int_MonthLifeSum) << endl;
        cout << "Room累计支出: " << CTool::TransOutFormat(int_MonthRoomSum) << endl;
        cout << endl;

        int_SMindex = 0;
        for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
        {
            string str_SubMonth = CMD_SMTranslate(*itr_SubMonth);
            cout << str_SubMonth << "累计支出: " << CTool::TransOutFormat(*(ptr_int_SMSum+int_SMindex)) << endl;
            int_SMindex++;
        }
        cout << endl;

        cout << "--> Month累计支出: " << CTool::TransOutFormat(m_int_MonthExpenseSum) << endl;
        cout << "--> Month累计结余: " << CTool::TransOutFormat(m_int_MonthSurplusSum) << endl;
        cout << endl;
        cout << "----------------------------------------" << endl;
    }

    delete[] ptr_int_SMSum;
}

/**************************************************/
//   汇总 Title累计收支
/**************************************************/
void CFAitfX::SummarizeTitle(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_TitleSum = 0;

    vector<string> vec_str_Title;
    ptr_ScriptRipper->TitleDuplicator(vec_str_Title);

    string str_TitleKey;
    unsigned int uni_TitleLine = 0;

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
    }

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << "### Title累计统计 ###" << endl;
        cout << endl;
    }

    vector<string>::iterator itr_Title;
    for(itr_Title = vec_str_Title.begin(); itr_Title != vec_str_Title.end(); itr_Title++)
    {
        str_TitleKey = "## " + *itr_Title;
        uni_TitleLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_TitleKey.c_str());
        int int_TitleCount = m_ptr_FM_SUM->GetLineValue(uni_TitleLine+1);
        int_TitleSum += int_TitleCount;

        if(int_OFlag > 0)
        {
            cout << *itr_Title << ": " << CTool::TransOutFormat(int_TitleCount) << endl;
        }
    }

    m_int_TitleSum = int_TitleSum;

    if(int_OFlag == 1)
    {
        cout << "--> Title累计支出: " << CTool::TransOutFormat(m_int_TitleSum) << endl;
    }
    else if(int_OFlag == 2)
    {
        cout << endl;
        cout << "--> Title累计支出: " << CTool::TransOutFormat(m_int_TitleSum) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   汇总 Tail累计收支
/**************************************************/
void CFAitfX::SummarizeTail(int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_TailSum = 0;

    vector<string> vec_str_Tail;
    ptr_ScriptRipper->TailDuplicator(vec_str_Tail);

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
    }

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << "### Tail累计统计 ###" << endl;
        cout << endl;
    }

    vector<string>::iterator itr_Tail;
    for(itr_Tail = vec_str_Tail.begin(); itr_Tail != vec_str_Tail.end(); itr_Tail++)
    {
        string str_TailKey = *itr_Tail;
        int int_TailCount = m_ptr_FM_SUM->GetUniqueSearchLineValue(str_TailKey.c_str());
        int_TailSum += int_TailCount;

        if(int_OFlag > 0)
        {
            cout << *itr_Tail << ": " << CTool::TransOutFormat(int_TailCount) << endl;
        }
    }

    m_int_TailSum = int_TailSum;

    if(int_OFlag == 2)
    {
        cout << endl;
        cout << "--> Tail累计收支: " << CTool::TransOutFormat(m_int_TailSum) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   汇总 CAF累计收支
/**************************************************/
void CFAitfX::SummarizeCAF(int int_OFlag)
{
    if(0 != CheckCAF())
    {
        CTool::MassageOutFotmat("CAF Allocation Error", '!');
        return;
    }

    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    vector<string> vec_str_CAF;
    ptr_ScriptRipper->CAFDuplicator(vec_str_CAF);

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << "--> 可支配财富: " << CTool::TransOutFormat(m_int_CAFSum) << endl;
    }

    int int_CAFSum = 0;
    vector<string>::iterator itr_CAF;
    for(itr_CAF = vec_str_CAF.begin(); itr_CAF != vec_str_CAF.end(); itr_CAF++)
    {
        string str_CAFKey = *itr_CAF;
        int int_CAFCount = m_ptr_FM_SUM->GetUniqueSearchLineValue(str_CAFKey.c_str());
        int_CAFSum += int_CAFCount;

        if(int_OFlag == 1)
        {
            cout << *itr_CAF << ": " << CTool::TransOutFormat(int_CAFCount) << endl;
        }
    }
}

/**************************************************/
//   更新 当前财富
/**************************************************/
void CFAitfX::UpdateCurrentSum(const int int_CurrentSum)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    string str_CurrentSum = ptr_ScriptRipper->GetCurrentSum();
    m_ptr_FM_SUM->ModifyUniqueSearchLineValue(str_CurrentSum.c_str(), int_CurrentSum);
}

/**************************************************/
//   检查 CAF
/**************************************************/
int CFAitfX::CheckCAF()
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    vector<string> vec_str_CAF;
    ptr_ScriptRipper->CAFDuplicator(vec_str_CAF);

    int int_CAFSum = 0;
    vector<string>::iterator itr_CAF;
    for(itr_CAF = vec_str_CAF.begin(); itr_CAF != vec_str_CAF.end(); itr_CAF++)
    {
        string str_CAFKey = *itr_CAF;
        int int_CAFCount = m_ptr_FM_SUM->GetUniqueSearchLineValue(str_CAFKey.c_str());
        int_CAFSum += int_CAFCount;
    }

    if( int_CAFSum == m_int_CAFSum )
    {
        return 0;   // 0 >>> CAF读取值 == 校验值
    }
    else
    {
        return -1;   // -1 >>> CAF读取值 != 校验值
    }
}

/**************************************************/
//   更新 CAF
/**************************************************/
void CFAitfX::UpdateCAF(const int int_CAFSum)
{
    if(0 != CheckCAF())
    {
        CTool::MassageOutFotmat("CAF Allocation Error", '!');
        return;
    }

    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_CAFDelta = int_CAFSum - m_int_CAFSum;

    // 修改 CAF Sum
    string str_CAFSum = ptr_ScriptRipper->GetCAFSum();
    m_ptr_FM_SUM->ModifyUniqueSearchLineValue(str_CAFSum.c_str(), int_CAFSum);
    m_int_CAFSum = int_CAFSum;

    // 修改 CAF 子项
    vector<string> vec_str_CAF;
    ptr_ScriptRipper->CAFDuplicator(vec_str_CAF);
    vector<string>::iterator itr_CAF = vec_str_CAF.begin();
    itr_CAF += ptr_ScriptRipper->GetCAFIndex() -1;

    string str_CAFKey = *itr_CAF;
    int int_CAFCount = m_ptr_FM_SUM->GetUniqueSearchLineValue(str_CAFKey.c_str());
    int_CAFCount += int_CAFDelta;
    m_ptr_FM_SUM->ModifyUniqueSearchLineValue(str_CAFKey.c_str(), int_CAFCount);
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

    unsigned int uni_RangeTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeBottom.c_str());

    int int_MonthExpenseEX = m_ptr_FM_life->GetLineValue(uni_RangeTop+2);
    int int_MonthExpenseCK = m_ptr_FM_life->CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_SelMonth << "月/支出 ###" << endl;
        cout << "读取值: " << CTool::TransOutFormat(m_ptr_FM_life->GetLineValue(uni_RangeTop+2)) << endl;
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

    unsigned int uni_AFLine = m_ptr_FM_SUM->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeBottom.c_str());

    unsigned int uni_AFMonthSalaryEX = m_ptr_FM_SUM->GetLineValue(uni_AFLine+1);
    int int_AFMonthExpenseEX = m_ptr_FM_SUM->GetLineValue(uni_AFLine+2);
    int int_AFMonthRestEX = m_ptr_FM_SUM->GetLineValue(uni_AFLine+3);

    unsigned int uni_MonthSalaryEX = m_ptr_FM_life->GetLineValue(uni_RangeTop+1);
    int int_MonthExpenseEX = m_ptr_FM_life->GetLineValue(uni_RangeTop+2);
    int int_MonthExpenseCK = m_ptr_FM_life->CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);
    int int_MonthRestEX = m_ptr_FM_life->GetLineValue(uni_RangeTop+3);
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

    unsigned int uni_RangeTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeBottom.c_str());

    unsigned int uni_MonthSalaryEX = m_ptr_FM_life->GetLineValue(uni_RangeTop+1);
    int int_MonthExpenseEX = m_ptr_FM_life->GetLineValue(uni_RangeTop+2);
    int int_MonthSurplusEX = m_ptr_FM_life->GetLineValue(uni_RangeTop+3);
    int int_MonthExpenseUD = m_ptr_FM_life->CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);
    int int_MonthSurplusUD = uni_MonthSalaryEX + int_MonthExpenseUD;

    m_ptr_FM_life->ModifyLineValue(uni_RangeTop+2, int_MonthExpenseUD);
    m_ptr_FM_life->ModifyLineValue(uni_RangeTop+3, int_MonthSurplusUD);

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

    unsigned int uni_RangeTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeBottom.c_str());

    m_ptr_FM_life->SearchRangeLineKey(str_MonthKey.c_str(), uni_RangeTop, uni_RangeBottom);
    unsigned int uni_KeyLine = m_ptr_FM_life->GetSearchLineIndex(1);

    // tips 番茄@20171209 - 手动可能输错的地方，增加ERROR校验
    if(m_ptr_FM_life->GetSearchFullLine(1).compare("ERROR") == 0)
    {
        CTool::MassageOutFotmat("No Line Contain Input Key", '!');
        return;
    }

    // 修改 单行金额
    int int_LineValue = m_ptr_FM_life->GetLineValue(uni_KeyLine);
    m_ptr_FM_life->ModifyLineValue(uni_KeyLine, int_LineValue-uni_ModValueABS);

    cout << m_ptr_FM_life->GetSearchFullLine(1) << endl;

    // 读取 初始收支金额
    unsigned int uni_MonthSalary = m_ptr_FM_life->GetLineValue(uni_RangeTop+1);
    int int_MonthExpense = m_ptr_FM_life->GetLineValue(uni_RangeTop+2);
    int int_MonthSurplus = m_ptr_FM_life->GetLineValue(uni_RangeTop+3);

    // 计算 更新收支金额
    int int_MonthExpenseUD = m_ptr_FM_life->CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);
    int int_MonthSurplusUD = uni_MonthSalary + int_MonthExpenseUD;

    // 修改 更新收支金额
    m_ptr_FM_life->ModifyLineValue(uni_RangeTop+2, int_MonthExpenseUD);
    m_ptr_FM_life->ModifyLineValue(uni_RangeTop+3, int_MonthSurplusUD);

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
    string str_SelMonthFL = "## life.M" + str_SelMonth;

    unsigned int uni_SelMonth = m_ptr_FM_life->GetFirstSearchLineIndex(str_SelMonthFL.c_str());
    unsigned int uni_AFSelMonth = m_ptr_FM_SUM->GetFirstSearchLineIndex(str_SelMonthFL.c_str());

    // 读取 life.M 月度收支
    unsigned int uni_MonthSalary = m_ptr_FM_life->GetLineValue(uni_SelMonth+1);
    int int_MonthExpense = m_ptr_FM_life->GetLineValue(uni_SelMonth+2);
    int int_MonthSurplus = m_ptr_FM_life->GetLineValue(uni_SelMonth+3);

    // 同步 总收支
    m_ptr_FM_SUM->ModifyLineValue(uni_AFSelMonth+1, uni_MonthSalary);
    m_ptr_FM_SUM->ModifyLineValue(uni_AFSelMonth+2, int_MonthExpense);
    m_ptr_FM_SUM->ModifyLineValue(uni_AFSelMonth+3, int_MonthSurplus);
}

/**************************************************/
//   校验 SubMonth 支出
/**************************************************/
int CFAitfX::CheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth, bool bol_OFlag)
{
    string str_RangeTop = CMD_SMTranslate(str_SubMonthKey) + ".M" + str_SelMonth;
    string str_RangeBottom = CMD_SMTranslate(str_SubMonthKey) + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    unsigned int uni_lifeLine = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeTop = GetPtrFM("SM", str_SubMonthKey)->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = GetPtrFM("SM", str_SubMonthKey)->GetFirstSearchLineIndex(str_RangeBottom.c_str());

    int int_LMSubMonthExpenseEX = m_ptr_FM_life->GetLineValue(uni_lifeLine);
    int int_SubMonthExpenseEX = GetPtrFM("SM", str_SubMonthKey)->GetLineValue(uni_RangeTop+1);
    int int_SubMonthExpenseCK = GetPtrFM("SM", str_SubMonthKey)->CountRangeType(uni_RangeTop+2, uni_RangeBottom-1,\
                                       LTYPE_FBIRC_LINEUINT);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_SelMonth << "月/" << CMD_SMTranslate(str_SubMonthKey) << "支出 ###" << endl;
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
//   更新 SubMonth 支出
/**************************************************/
void CFAitfX::UpdateSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth, bool bol_OFlag)
{
    string str_RangeTop = CMD_SMTranslate(str_SubMonthKey) + ".M" + str_SelMonth;
    string str_RangeBottom = CMD_SMTranslate(str_SubMonthKey) + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    unsigned int uni_lifeLine = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeTop = GetPtrFM("SM", str_SubMonthKey)->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = GetPtrFM("SM", str_SubMonthKey)->GetFirstSearchLineIndex(str_RangeBottom.c_str());

    int int_SubMonthExpense = GetPtrFM("SM", str_SubMonthKey)->GetLineValue(uni_RangeTop+1);
    int int_SubMonthExpenseUD = GetPtrFM("SM", str_SubMonthKey)->CountRangeType(uni_RangeTop+2, uni_RangeBottom-1,\
                                            LTYPE_FBIRC_LINEUINT);
    
    m_ptr_FM_life->ModifyLineValue(uni_lifeLine, int_SubMonthExpenseUD);
    GetPtrFM("SM", str_SubMonthKey)->ModifyLineValue(uni_RangeTop+1, int_SubMonthExpenseUD);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_SelMonth << "月/" << CMD_SMTranslate(str_SubMonthKey) << "支出 ###" << endl;
        cout << "sub.M_初始值: " << CTool::TransOutFormat(int_SubMonthExpense) << endl;
        cout << "sub.M_更新值: " << CTool::TransOutFormat(int_SubMonthExpenseUD) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   校验 Tt分项 支出
/**************************************************/
int CFAitfX::CheckTitleExpense(const string str_TitleKey, bool bol_OFlag)
{
    string str_RangeTop = "## " + CMD_TTTranslate(str_TitleKey);
    string str_RangeBottom("## Total");

    unsigned int uni_AFLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeTop = 2;
    unsigned int uni_RangeBottom = GetPtrFM("TT", str_TitleKey)->GetUniqueSearchLineIndex(str_RangeBottom.c_str());

    int int_AFTitleExpenseEX = m_ptr_FM_SUM->GetLineValue(uni_AFLine+1);

    int int_TitleExpenseEX = GetPtrFM("TT", str_TitleKey)->GetLineValue(uni_RangeBottom+2);
    int int_TitleExpenseCK = GetPtrFM("TT", str_TitleKey)->CountRangeType(uni_RangeTop, uni_RangeBottom-1,\
                                       LTYPE_FBIRC_LINEUINT);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << CMD_TTTranslate(str_TitleKey) << "/支出 ###" << endl;
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
//   更新 Tt分项 支出
/**************************************************/
void CFAitfX::UpdateTitleExpense(const string str_TitleKey, bool bol_OFlag)
{
    string str_RangeTop = "## " + CMD_TTTranslate(str_TitleKey);
    string str_RangeBottom("## Total");

    unsigned int uni_AFLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeTop = 2;
    unsigned int uni_RangeBottom = GetPtrFM("TT", str_TitleKey)->GetUniqueSearchLineIndex(str_RangeBottom.c_str());

    int int_TitleExpense = GetPtrFM("TT", str_TitleKey)->GetLineValue(uni_RangeBottom+2);
    int int_TitleExpenseUD = GetPtrFM("TT", str_TitleKey)->CountRangeType(uni_RangeTop, uni_RangeBottom-1,\
                                      LTYPE_FBIRC_LINEUINT);

    GetPtrFM("TT", str_TitleKey)->ModifyLineValue(uni_RangeBottom+2, int_TitleExpenseUD);
    m_ptr_FM_SUM->ModifyLineValue(uni_AFLine+1, int_TitleExpenseUD);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << CMD_TTTranslate(str_TitleKey) << "/支出 ###" << endl;
        cout << "Tt_初始值: " << CTool::TransOutFormat(int_TitleExpense) << endl;
        cout << "Tt_更新值: " << CTool::TransOutFormat(int_TitleExpenseUD) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   校验 Tt分项 Lottery
/**************************************************/
int CFAitfX::CheckLottery(bool bol_OFlag)
{
    /********** Init Index ********************/

    string str_RangeTop("## lottery");
    string str_RangeBottom("## Total");

    unsigned int uni_AFLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeTop = 2;
    unsigned int uni_RangeBottom = m_ptr_FM_tt_lottery->GetUniqueSearchLineIndex(str_RangeBottom.c_str());

    /********** EX ********************/

    int int_AFLotteryEX = m_ptr_FM_SUM->GetLineValue(uni_AFLine+1);

    int int_LotteryInvestEX = m_ptr_FM_tt_lottery->GetLineValue(uni_RangeBottom+2);
    int int_LotteryRewardEX = m_ptr_FM_tt_lottery->GetLineValue(uni_RangeBottom+3);
    int int_LotteryRevenueEX = m_ptr_FM_tt_lottery->GetLineValue(uni_RangeBottom+4);
    int int_LotteryROIEX = m_ptr_FM_tt_lottery->GetLineValue(uni_RangeBottom+5);

    /********** CK ********************/

    int int_LotteryInvestCK = 0;
    int int_LotteryRewardCK = 0;
    int int_LotteryRevenueCK = 0;
    int int_LotteryROICK  = 0;

    for(int i = uni_RangeTop; i <= uni_RangeBottom-1; i++)
    {
        int int_LotteryLineValue = m_ptr_FM_tt_lottery->GetLineValue(i);

        if( int_LotteryLineValue < 0 )
        {
            int_LotteryInvestCK += int_LotteryLineValue;
            int_LotteryRevenueCK += int_LotteryLineValue;
        }
        else if ( int_LotteryLineValue > 0 )
        {
            int_LotteryRewardCK += int_LotteryLineValue;
            int_LotteryRevenueCK += int_LotteryLineValue;
        }
    }

    int_LotteryROICK = int_LotteryRevenueCK * 100 / int_LotteryInvestCK;

    /********** Output ********************/

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### lottery ROI ###" << endl;
        cout << "AF_读取值: " << CTool::TransOutFormat(int_AFLotteryEX) << endl;
        cout << "lottery_读取值: " << CTool::TransOutFormat(int_LotteryRevenueEX) << endl;
        cout << "lottery_校验值: " << CTool::TransOutFormat(int_LotteryRevenueCK) << endl;
        cout << "----------------------------------------" << endl;
    }

    /********** Return ********************/

    if( int_LotteryRevenueEX != int_LotteryRevenueCK )
    {
        return -1;
    }
    else if( int_AFLotteryEX != int_LotteryRevenueCK )
    {
        return -2;
    }
    else
    {
        return 0;
    }
}

/**************************************************/
//   更新 Tt分项 Lottery
/**************************************************/
void CFAitfX::UpdateLottery(bool bol_OFlag)
{
    /********** Init Index **********/

    string str_RangeTop("## lottery");
    string str_RangeBottom("## Total");

    unsigned int uni_AFLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeTop = 2;
    unsigned int uni_RangeBottom = m_ptr_FM_tt_lottery->GetUniqueSearchLineIndex(str_RangeBottom.c_str());

    /********** UD **********/
    int int_LotteryInvestUD = 0;
    int int_LotteryRewardUD = 0;
    int int_LotteryRevenueUD = 0;

    for(int i = uni_RangeTop; i <= uni_RangeBottom-1; i++)
    {
        int int_LotteryLineValue = m_ptr_FM_tt_lottery->GetLineValue(i);

        if( int_LotteryLineValue < 0 )
        {
            int_LotteryInvestUD += int_LotteryLineValue;
            int_LotteryRevenueUD += int_LotteryLineValue;
        }
        else if ( int_LotteryLineValue > 0 )
        {
            int_LotteryRewardUD += int_LotteryLineValue;
            int_LotteryRevenueUD += int_LotteryLineValue;
        }
    }

    int int_LotteryROIUD = int_LotteryRevenueUD * 100 / (int_LotteryInvestUD * (-1));

    /********** Line Modify ********************/

    m_ptr_FM_tt_lottery->ModifyLineValue(uni_RangeBottom+2, int_LotteryInvestUD);
    m_ptr_FM_tt_lottery->ModifyLineValue(uni_RangeBottom+3, int_LotteryRewardUD);
    m_ptr_FM_tt_lottery->ModifyLineValue(uni_RangeBottom+4, int_LotteryRevenueUD);
    m_ptr_FM_tt_lottery->ModifyLineValue(uni_RangeBottom+5, int_LotteryROIUD);

    /********** Transfer Balance ********************/

    int int_AFLotteryRevenueOrigin = m_ptr_FM_SUM->GetLineValue(uni_AFLine+1);
    int int_AFLotteryRevenueDelta = int_LotteryRevenueUD - int_AFLotteryRevenueOrigin;

    m_ptr_FM_SUM->ModifyLineValue(uni_AFLine+1, int_LotteryRevenueUD);
    TransferBalance("微信-零钱通", "阿里-余额宝", int_AFLotteryRevenueDelta);

    /********** Output ********************/

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### lottery ROI ###" << endl;
        cout << "lottery投资更新值: " << CTool::TransOutFormat(int_LotteryInvestUD) << endl;
        cout << "lottery回报更新值: " << CTool::TransOutFormat(int_LotteryRewardUD) << endl;
        cout << "lottery收益更新值: " << CTool::TransOutFormat(int_LotteryRevenueUD) << endl;
        cout << "lottery ROI更新值: " << CTool::TransOutFormat(int_LotteryROIUD) << "%" << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   附加 Tt分项 Lottery
/**************************************************/
void CFAitfX::AppendLottery(const bool bol_LineFlag, const unsigned int uni_LineValueABS,\
                            const string str_LineDate)
{
    string str_LotteryTop("## lottery");
    string str_LotteryBottom("## Total");

    unsigned int uni_AFLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_LotteryTop.c_str());
    unsigned int uni_LotteryTop = 2;
    unsigned int uni_LotteryBottom = m_ptr_FM_tt_lottery->GetUniqueSearchLineIndex(str_LotteryBottom.c_str());

    int int_LotterySurplus = m_ptr_FM_tt_lottery->GetLineValue(uni_LotteryBottom+2);

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

    m_ptr_FM_tt_lottery->InsertLine(uni_LotteryBottom-1, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);

    // tips 番茄@20171212 - 注意计算总支出的时候要增加一行
    //int int_LotterySurplusAP = m_ptr_FM_tt_lottery->CountRangeType(uni_LotteryTop, uni_LotteryBottom,\
                                                                  LTYPE_FBIRC_LINEUINT);

    // tips 番茄@20171212 - 注意计算总支出的时候要增加一行
    //m_ptr_FM_tt_lottery->ModifyLineValue(uni_LotteryBottom+3, int_LotterySurplusAP);
    //m_ptr_FM_SUM->ModifyLineValue(uni_AFLine+1, int_LotterySurplusAP);

    // tips 番茄@20171225 - 在支出前，增加一行空行
    if(!bol_LineFlag)
    {
        m_ptr_FM_tt_lottery->InsertBlankLine(uni_LotteryBottom-1);
    }

    /*
    cout << "----------------------------------------" << endl;
    cout << "### lottery ###" << endl;
    cout << "lottery_初始值: " << CTool::TransOutFormat(int_LotterySurplus) << endl;
    cout << "lottery_更新值: " << CTool::TransOutFormat(int_LotterySurplusAP) << endl;
    cout << "----------------------------------------" << endl;
    */
}

/**************************************************/
//   默认从 str_FirstKey 进行操作
/**************************************************/
void CFAitfX::TransferBalance(const string str_FirstKey, const string str_SecondKey,
                              const int int_BalanceValue)
{
    unsigned int uni_FirstLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_FirstKey.c_str());
    int int_FirstValue = m_ptr_FM_SUM->GetLineValue(uni_FirstLine);

    unsigned int uni_SecondLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_SecondKey.c_str());
    int int_SecondValue = m_ptr_FM_SUM->GetLineValue(uni_SecondLine);

    m_ptr_FM_SUM->ModifyLineValue(uni_FirstLine, int_FirstValue + int_BalanceValue);
    m_ptr_FM_SUM->ModifyLineValue(uni_SecondLine, int_SecondValue - int_BalanceValue);
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

    unsigned int uni_SUMLine = m_ptr_FM_SUM->GetUniqueSearchLineIndex("## Summary");

    m_ptr_FM_SUM->InsertBlankLine(uni_SUMLine-1);
    m_ptr_FM_SUM->InsertLine(uni_SUMLine, LTYPE_MONTHTITLE, 0, str_SUMMonthTitle);
    m_ptr_FM_SUM->InsertLine(uni_SUMLine+1, LTYPE_FBIRC_MONTHSUM, 0, str_SUMMonthSalary);
    m_ptr_FM_SUM->InsertLine(uni_SUMLine+2, LTYPE_FBIRC_MONTHSUM, 0, str_SUMMonthExpense);
    m_ptr_FM_SUM->InsertLine(uni_SUMLine+3, LTYPE_FBIRC_MONTHSUM, 0, str_SUMMonthRest);
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

    unsigned int uni_lifeLine = m_ptr_FM_life->GetUniqueSearchLineIndex("---");
    unsigned int uni_InsertLine = uni_lifeLine-4;

    m_ptr_FM_life->InsertBlankLine(uni_InsertLine++);
    m_ptr_FM_life->InsertLine(uni_InsertLine++, LTYPE_MONTHTITLE, 0, str_lifeMonthTitle);
    m_ptr_FM_life->InsertLine(uni_InsertLine++, LTYPE_FBIRC_MONTHSUM, 0, str_lifeMonthSalary);
    m_ptr_FM_life->InsertLine(uni_InsertLine++, LTYPE_FBIRC_MONTHSUM, 0, str_lifeMonthExpense);
    m_ptr_FM_life->InsertLine(uni_InsertLine++, LTYPE_FBIRC_MONTHSUM, 0, str_lifeMonthRest);

    string str_lifeMonthLife = str_SelMonth + "月_" + "生活费{&霞}";
    uni_InsertLine = uni_lifeLine-4;

    m_ptr_FM_life->InsertBlankLine(uni_InsertLine++);
    m_ptr_FM_life->InsertLine(uni_InsertLine++, LTYPE_FBIRC_LINEUINT, 0, str_lifeMonthLife);
    
    vector<string> vec_str_Room;
    ptr_ScriptRipper->RoomDuplicator(vec_str_Room);

    vector<string>::iterator itr_Room;
    for(itr_Room = vec_str_Room.begin(); itr_Room != vec_str_Room.end(); itr_Room++)
    {
        string str_lifeRM = str_SelMonth + "月_" + *itr_Room;
        m_ptr_FM_life->InsertLine(uni_InsertLine++, LTYPE_FBIRC_LINEUINT, 0, str_lifeRM);
    }

    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    m_ptr_FM_life->InsertBlankLine(uni_InsertLine++);
    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        string str_lifeSM = CMD_SMTranslate(*itr_SubMonth) + ".M" + str_SelMonth;
        m_ptr_FM_life->InsertLine(uni_InsertLine++, LTYPE_FBIRC_LINEUINT, 0, str_lifeSM);
    }
}

/**************************************************/
//   添加SubMonth脚本
/**************************************************/
void CFAitfX::AddScriptSubMonth(const string str_SubMonthKey, const string str_SelMonth)
{
    string str_SMTitle = string("## ");
    str_SMTitle += CMD_SMTranslate(str_SubMonthKey);
    str_SMTitle += ".M";
    str_SMTitle += str_SelMonth;

    unsigned int uni_SMLine = GetPtrFM("SM", str_SubMonthKey)->GetUniqueSearchLineIndex("---");

    GetPtrFM("SM", str_SubMonthKey)->InsertBlankLine(uni_SMLine-4);
    GetPtrFM("SM", str_SubMonthKey)->InsertLine(uni_SMLine-3, LTYPE_MONTHTITLE, 0, str_SMTitle);
    GetPtrFM("SM", str_SubMonthKey)->InsertLine(uni_SMLine-2, LTYPE_FBIRC_TITLESUM, 0, "");
    GetPtrFM("SM", str_SubMonthKey)->InsertBlankLine(uni_SMLine-1);
    GetPtrFM("SM", str_SubMonthKey)->InsertLine(uni_SMLine, LTYPE_FBIRC_LINEUINT, 0, "~");
}

/**************************************************/
//   生成 月度趋势Vector
/**************************************************/
unsigned int CFAitfX::GenerateMonthTrendVector(vector<TREND_INFO> &vec_stc_TrendInfo, const string str_MonthKey)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    
    unsigned int uni_TrendIndex = 0;
    unsigned int uni_TrendSum = 0;
    TREND_INFO stc_TrendInfo;

    string str_TrendMonth = ptr_ScriptRipper->GetOriginMonth();
    string str_TerminalMonth = CTool::GenerateNextMonth(ptr_ScriptRipper->GetCurrentMonth());

    while( str_TrendMonth != str_TerminalMonth )
    {
        string str_RangeTop = "## life.M" + str_TrendMonth;
        string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_TrendMonth);

        unsigned int uni_RangeTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
        unsigned int uni_RangeBottom = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeBottom.c_str());

        if( m_ptr_FM_life->SearchRangeLineKey(str_MonthKey.c_str(), uni_RangeTop, uni_RangeBottom) )
        {
            uni_TrendIndex = m_ptr_FM_life->GetSearchLineIndex(1);

            stc_TrendInfo.str_TrendMonth = str_TrendMonth;
            stc_TrendInfo.uni_TrendValueABS = m_ptr_FM_life->GetLineValueABS(uni_TrendIndex);
            uni_TrendSum += m_ptr_FM_life->GetLineValueABS(uni_TrendIndex);

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

    return uni_TrendSum;
}

/**************************************************/
//   附加 月度趋势Vector
/**************************************************/
unsigned int CFAitfX::AppendMonthTrendVector(vector<TREND_INFO> &vec_stc_TrendInfo, const string str_MonthKey)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    unsigned int uni_TrendIndex = 0;
    unsigned int uni_VecIndex = 0;
    unsigned int uni_TrendSum = 0;
    TREND_INFO stc_TrendInfo;

    string str_TrendMonth = ptr_ScriptRipper->GetOriginMonth();
    string str_TerminalMonth = CTool::GenerateNextMonth(ptr_ScriptRipper->GetCurrentMonth());

    while( str_TrendMonth != str_TerminalMonth )
    {
        string str_RangeTop = "## life.M" + str_TrendMonth;
        string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_TrendMonth);

        unsigned int uni_RangeTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
        unsigned int uni_RangeBottom = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeBottom.c_str());

        if( m_ptr_FM_life->SearchRangeLineKey(str_MonthKey.c_str(), uni_RangeTop, uni_RangeBottom) )
        {
            uni_TrendIndex = m_ptr_FM_life->GetSearchLineIndex(1);
            vec_stc_TrendInfo.at(uni_VecIndex).uni_TrendValueABS += m_ptr_FM_life->GetLineValueABS(uni_TrendIndex);
            uni_TrendSum += m_ptr_FM_life->GetLineValueABS(uni_TrendIndex);
        }

        str_TrendMonth = CTool::GenerateNextMonth(str_TrendMonth);
        uni_VecIndex++;
    }

    return uni_TrendSum;
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
//   生成 月度支出Vector
/**************************************************/
unsigned int CFAitfX::GenerateMonthVector(vector<UNIT_INFO> &vec_stc_UnitInfo, const string str_SelMonth)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    if( 0 == m_ptr_FM_life->SearchLineKey(str_RangeTop.c_str()) )
    {
        CTool::MassageOutFotmat("Error Month Input", '!');
        return -1;
    }
    unsigned int uni_RangeTop = m_ptr_FM_life->GetSearchLineIndex(1) + 4;
    m_ptr_FM_life->SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_ptr_FM_life->GetSearchLineIndex(1) - 1;

    // 建构 vector
    UNIT_INFO stc_UnitInfo;

    for(int i=uni_RangeTop; i<=uni_RangeBottom; i++)
    {
        if( m_ptr_FM_life->GetLineType(i)==LTYPE_FBIRC_LINEUINT )
        {
            stc_UnitInfo.str_UnitContent = m_ptr_FM_life->GetLineContent(i);
            stc_UnitInfo.uni_UnitValueABS = m_ptr_FM_life->GetLineValueABS(i);

            vec_stc_UnitInfo.push_back(stc_UnitInfo);
        }
    }

    return uni_RangeTop;
}

/**************************************************/
//   分析 月度支出占比
/**************************************************/
void CFAitfX::AnalysisMonthProportion(const string str_SelMonth)
{
    // 建构 vector
    vector<UNIT_INFO> vec_stc_UnitInfo;
    unsigned int uni_RangeTop = GenerateMonthVector(vec_stc_UnitInfo, str_SelMonth);
    // tips 番茄@20180817 - 默认房租为最大支出项
    unsigned int uni_MonthExpenseABS = m_ptr_FM_life->GetLineValueABS(uni_RangeTop-2);

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
//   比较 月度支出
/**************************************************/
void CFAitfX::CompareMonth(const string str_SelMonth, const string str_CmpMonth)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    // 建构 Sel_vector
    vector<UNIT_INFO> vec_stc_SelUnitInfo;
    GenerateMonthVector(vec_stc_SelUnitInfo, str_SelMonth);

    // 建构 Cmp_vector
    vector<UNIT_INFO> vec_stc_CmpUnitInfo;
    GenerateMonthVector(vec_stc_CmpUnitInfo, str_CmpMonth);

    // 构建 analysis_vector
    vector<string> vec_str_Room;
    ptr_ScriptRipper->RoomDuplicator(vec_str_Room);

    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    vector<string> vec_str_TransSubMonth;
    vec_str_TransSubMonth.clear();
    for(int i = 0; i < vec_str_SubMonth.size(); i++)
    {
        string str_SMTranslate = CMD_SMTranslate(vec_str_SubMonth[i]);
        vec_str_TransSubMonth.push_back(str_SMTranslate);
    }
    vec_str_SubMonth.swap(vec_str_TransSubMonth);

    vector<string> vec_str_StdMonth;
    vec_str_StdMonth.push_back("生活费");
    vec_str_StdMonth.insert(vec_str_StdMonth.end(), vec_str_Room.begin(), vec_str_Room.end());
    vec_str_StdMonth.push_back("蚂蚁还款");   // tips 番茄@20180817 - 之后需要删除
    vec_str_StdMonth.insert(vec_str_StdMonth.end(), vec_str_SubMonth.begin(), vec_str_SubMonth.end());

    // ...
    cout << "----------------------------------------" << endl;
    cout << "### 月度对比分析 ###" << endl;
    cout << endl;

    vector<string>::iterator itr_StdMonth;
    for(itr_StdMonth = vec_str_StdMonth.begin(); itr_StdMonth != vec_str_StdMonth.end(); itr_StdMonth++)
    {
        unsigned int uni_SelUnitValueABS = 0;
        vector<UNIT_INFO>::iterator itr_SelUnitInfo;
        for(itr_SelUnitInfo = vec_stc_SelUnitInfo.begin(); itr_SelUnitInfo != vec_stc_SelUnitInfo.end(); itr_SelUnitInfo++)
        {
            string::size_type idx;
            idx = (itr_SelUnitInfo->str_UnitContent).find(*itr_StdMonth);
            if(idx != string::npos)
            {
                uni_SelUnitValueABS = itr_SelUnitInfo->uni_UnitValueABS;
                break;
            }
        }

        unsigned int uni_CmpUnitValueABS = 0;
        vector<UNIT_INFO>::iterator itr_CmpUnitInfo;
        for(itr_CmpUnitInfo = vec_stc_CmpUnitInfo.begin(); itr_CmpUnitInfo != vec_stc_CmpUnitInfo.end(); itr_CmpUnitInfo++)
        {
            string::size_type idx;
            idx = (itr_CmpUnitInfo->str_UnitContent).find(*itr_StdMonth);
            if(idx != string::npos)
            {
                uni_CmpUnitValueABS = itr_CmpUnitInfo->uni_UnitValueABS;
                break;
            }
        }

        unsigned int uni_SelScalde = 0;
        unsigned int uni_CmpScalde = 0;

        double dob_CmpRate = 0.0;
        if(uni_CmpUnitValueABS != 0)
            dob_CmpRate = ((double)uni_SelUnitValueABS - (double)uni_CmpUnitValueABS)/(double)uni_CmpUnitValueABS;
        else
            dob_CmpRate = 1.0;

        if(uni_SelUnitValueABS > uni_CmpUnitValueABS)
        {
            uni_SelScalde = 40;
            uni_CmpScalde = 40 / (1+dob_CmpRate);

            if(dob_CmpRate == 1.0)
                uni_CmpScalde = 0;
        }
        else if(uni_SelUnitValueABS < uni_CmpUnitValueABS)
        {
            uni_SelScalde = (1+dob_CmpRate) * 40;
            uni_CmpScalde = 40;
        }
        else
        {
            uni_SelScalde = 35;
            uni_CmpScalde = 35;
        }


        cout << "----- " << *itr_StdMonth << " -----" << endl;

        cout << str_CmpMonth << "月: ";
        for(int i=1; i<=uni_CmpScalde; i++)
        {
            cout << "█";
        }
        cout << " " << uni_CmpUnitValueABS << endl;

        cout << str_SelMonth << "月: ";
        for(int j=1; j<=uni_SelScalde; j++)
        {
            cout << "█";
        }
        cout << " " << uni_SelUnitValueABS << " (";
        if(dob_CmpRate>0)
            cout << "+";
        printf("%.1f", (dob_CmpRate*100));
        cout << "%)" << endl;

        cout << endl;
    }

    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   预测 未来财富
/**************************************************/
void CFAitfX::ForecastFutureSum(const string str_SelMonth, const int int_MonthPatch)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    if(ptr_ScriptRipper->GetCurrentMonth() == ptr_ScriptRipper->GetOriginMonth())
    {
        // tips 番茄@20180706 - 后期需要完善优化
        CTool::MassageOutFotmat("OriginMonth-UnSupported", '!');
        return;
    }

    int int_SurveySum = 0;
    int int_SurveyCounter = 0;
    int int_AverageMonthExpense = 0;

    string str_SurveyMonth = ptr_ScriptRipper->GetCurrentMonth();

    for(int i=0; ; i++)
    {
        str_SurveyMonth = CTool::GeneratePreMonth(str_SurveyMonth);
        
        string str_SurveyMonthTop = "## life.M" + str_SurveyMonth;
        unsigned int uni_SurveyMonthTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_SurveyMonthTop.c_str());

        int_SurveySum += m_ptr_FM_life->GetLineValue(uni_SurveyMonthTop+2);
        int_SurveyCounter++;

        if(str_SurveyMonth == ptr_ScriptRipper->GetOriginMonth())
            break;
    }

    int_AverageMonthExpense = int_SurveySum / int_SurveyCounter;

    int int_MonthSalary = ptr_ScriptRipper->GetMonthSalary();
    int int_MonthSurplus = int_MonthSalary + int_AverageMonthExpense;
    int int_MonthCounter = CTool::CountMonth(ptr_ScriptRipper->GetCurrentMonth(), str_SelMonth);
    int_MonthCounter--;

    int int_FutureSum = m_int_CurrentSum + (int_MonthSurplus * int_MonthCounter);
    int_FutureSum += int_MonthSalary * int_MonthPatch;
    int int_CAFSum = m_int_CAFSum + (int_MonthSurplus * int_MonthCounter);
    int_CAFSum += int_MonthSalary * int_MonthPatch;

    cout << "----------------------------------------" << endl;
    cout << "### 未来财富预测 ###" << endl;
    cout << endl;

    cout << "平均月度结余: " << int_MonthSurplus << endl;
    cout << "未来财富: " << int_FutureSum << endl;
    cout << "可支配财富: " << int_CAFSum << endl;

    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   生成 Lottery Vector
/**************************************************/
void CFAitfX::GenerateLotteryVector(vector<UNIT_LOTTERY> &vec_stc_LotteryInfo)
{
    vec_stc_LotteryInfo.clear();

    UNIT_LOTTERY stc_UnitLottery;

    string str_RangeTop = "# lottery";
    string str_RangeBottom = "## Total";

    unsigned int uni_RangeTop = m_ptr_FM_tt_lottery->GetUniqueSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = m_ptr_FM_tt_lottery->GetUniqueSearchLineIndex(str_RangeBottom.c_str());

    for(int i = uni_RangeTop+1; i < uni_RangeBottom ; i++)
    {
        if( LTYPE_FBIRC_LINEUINT == m_ptr_FM_tt_lottery->GetLineType(i) )
        {
            string str_LineContent = m_ptr_FM_tt_lottery->GetLineContent(i);
            CTool::ParseDate(str_LineContent, stc_UnitLottery.uni_Year, stc_UnitLottery.uni_Month, stc_UnitLottery.uni_Day);

            if( LTYPE_FBIRC_LINEUINT == m_ptr_FM_tt_lottery->GetLineType(i+1) )
            {
                stc_UnitLottery.int_Expense = m_ptr_FM_tt_lottery->GetLineValue(i);
                stc_UnitLottery.int_Income = m_ptr_FM_tt_lottery->GetLineValue(++i);
            }
            else
            {
                stc_UnitLottery.int_Expense = m_ptr_FM_tt_lottery->GetLineValue(i);
                stc_UnitLottery.int_Income = 0;
            }
            
            vec_stc_LotteryInfo.push_back(stc_UnitLottery);
        }
        else if( LTYPE_BLANK == m_ptr_FM_tt_lottery->GetLineType(i) )
        {
            continue;
        }
    }
}

/**************************************************/
//   展示 Month 收支
//   OFlag == 1 >>> 嵌入显示模式
//   OFlag == 2 >>> 嵌入显示模式
//   OFlag == 3 >>> 嵌入显示模式
//   OFlag == 4 >>> 完整显示模式
/**************************************************/
void CFAitfX::ShowMonthSurplus(const string str_SelMonth, int int_OFlag)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    unsigned int uni_RangeTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());

    unsigned int uni_MonthSalary = m_ptr_FM_life->GetLineValue(uni_RangeTop+1);
    int int_MonthExpense = m_ptr_FM_life->GetLineValue(uni_RangeTop+2);
    int int_MonthRest = m_ptr_FM_life->GetLineValue(uni_RangeTop+3);

    if(int_OFlag == 1)
    {
        cout << "----------------------------------------" << endl;
        cout << str_SelMonth << "月/薪资: " << CTool::TransOutFormat(uni_MonthSalary) << endl;
        cout << str_SelMonth << "月/支出: " << CTool::TransOutFormat(int_MonthExpense) << endl;
        cout << str_SelMonth << "月/结余: " << CTool::TransOutFormat(int_MonthRest) << endl;
    }

    if(int_OFlag == 2)
    {
        cout << "----------------------------------------" << endl;
        cout << str_SelMonth << "月/支出: " << CTool::TransOutFormat(int_MonthExpense) << endl;
    }

    if(int_OFlag == 3)
    {
        cout << "----------------------------------------" << endl;
        cout << str_SelMonth << "月/支出: " << CTool::TransOutFormat(int_MonthExpense) << endl;
        cout << "----------------------------------------" << endl;
    }

    if(int_OFlag == 4)
    {
        cout << "----------------------------------------" << endl;
        cout << str_SelMonth << "月/薪资: " << CTool::TransOutFormat(uni_MonthSalary) << endl;
        cout << str_SelMonth << "月/支出: " << CTool::TransOutFormat(int_MonthExpense) << endl;
        cout << str_SelMonth << "月/结余: " << CTool::TransOutFormat(int_MonthRest) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   展示 life 支出
//   OFlag == 1 >>> 嵌入显示模式
//   OFlag == 2 >>> NONE (预留)
//   OFlag == 3 >>> NONE (预留)
//   OFlag == 4 >>> 完整显示模式
/**************************************************/
void CFAitfX::ShowLife(const string str_SelMonth, int int_OFlag)
{
    if( int_OFlag > 0 )
    {
        cout << "----------------------------------------" << endl;
    }

    string str_LifeItem = str_SelMonth + "月_生活费";
    int int_LifeExpense = m_ptr_FM_life->GetFirstSearchLineValue(str_LifeItem.c_str());

    if( int_OFlag > 0 )
    {
        cout << str_SelMonth << "月/生活费: " << CTool::TransOutFormat(int_LifeExpense) << endl;
    }

    if( int_OFlag == 4 )
    {
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   展示 Room 支出
//   OFlag == 1 >>> 嵌入显示模式
//   OFlag == 2 >>> 嵌入显示模式
//   OFlag == 3 >>> 嵌入显示模式
//   OFlag == 4 >>> 完整显示模式
/**************************************************/
void CFAitfX::ShowRoom(const string str_SelMonth, int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_TotalRMExpense = 0;
    vector<string> vec_str_Room;
    ptr_ScriptRipper->RoomDuplicator(vec_str_Room);

    if(int_OFlag > 0)
    {
        cout << "----------------------------------------" << endl;
    }

    vector<string>::iterator itr_Room;
    for(itr_Room = vec_str_Room.begin(); itr_Room != vec_str_Room.end(); itr_Room++)
    {
        string str_RMItem = str_SelMonth + "月_" + *itr_Room;
        int int_RMExpense = m_ptr_FM_life->GetFirstSearchLineValue(str_RMItem.c_str());
        int_TotalRMExpense += int_RMExpense;
        if( (int_OFlag > 0) && (int_OFlag != 3) )
        {
            cout << str_SelMonth << "月/" << *itr_Room << ": " << CTool::TransOutFormat(int_RMExpense) << endl;
        }
    }

    if( int_OFlag == 2 )
    {
        cout << "--> " << str_SelMonth << "月/ROOM支出: " << CTool::TransOutFormat(int_TotalRMExpense) << endl;
    }

    if( int_OFlag == 3 )
    {
        cout << str_SelMonth << "月/ROOM支出: " << CTool::TransOutFormat(int_TotalRMExpense) << endl;
    }

    if( int_OFlag == 4 )
    {
        cout << endl;
        cout << str_SelMonth << "月/ROOM支出: " << CTool::TransOutFormat(int_TotalRMExpense) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   展示 SubMonth 支出
//   OFlag == 1 >>> 嵌入显示模式
//   OFlag == 2 >>> 嵌入显示模式
//   OFlag == 3 >>> NONE (预留)
//   OFlag == 4 >>> 完整显示模式
/**************************************************/
void CFAitfX::ShowSM(const string str_SelMonth, int int_OFlag)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");

    int int_TotalSMExpense = 0;
    vector<string> vec_str_SubMonth;
    ptr_ScriptRipper->SubMonthDuplicator(vec_str_SubMonth);

    if(int_OFlag > 0)
    {
        cout << "----------------------------------------" << endl;
    }

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = vec_str_SubMonth.begin(); itr_SubMonth != vec_str_SubMonth.end(); itr_SubMonth++)
    {
        string str_SMItem = CMD_SMTranslate(*itr_SubMonth) + ".M" + str_SelMonth;
        int int_SMExpense = m_ptr_FM_life->GetFirstSearchLineValue(str_SMItem.c_str());
        int_TotalSMExpense += int_SMExpense;
        cout << str_SelMonth << "月/" << CMD_SMTranslate(*itr_SubMonth) << ": " << CTool::TransOutFormat(int_SMExpense) << endl;
    }

    if( int_OFlag == 2 )
    {
        cout << "--> " << str_SelMonth << "月/CSM支出: " << CTool::TransOutFormat(int_TotalSMExpense) << endl;
    }

    if( int_OFlag == 4 )
    {
        cout << endl;
        cout << str_SelMonth << "月/CSM支出: " << CTool::TransOutFormat(int_TotalSMExpense) << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   展示 SubMonth 支出
//   OFlag == 1 >>> 嵌入显示模式
//   OFlag == 2 >>> NONE (预留)
//   OFlag == 3 >>> NONE (预留)
//   OFlag == 4 >>> 完整显示模式
/**************************************************/
int CFAitfX::ShowSubMonth(const string str_SubMonthKey, const string str_SelMonth, int int_OFlag)
{
    if(int_OFlag > 0)
    {
        cout << "----------------------------------------" << endl;
        cout << endl;
    }

    string str_RangeTop = CMD_SMTranslate(str_SubMonthKey) + ".M" + str_SelMonth;
    string str_RangeBottom = CMD_SMTranslate(str_SubMonthKey) + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    unsigned int uni_RangeTop = GetPtrFM("SM", str_SubMonthKey)->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = GetPtrFM("SM", str_SubMonthKey)->GetFirstSearchLineIndex(str_RangeBottom.c_str());

    for(int i=uni_RangeTop+3; i<uni_RangeBottom-1; i++)
    {
        cout << GetPtrFM("SM", str_SubMonthKey)->GetLineContent(i);
        cout << ": ";
        cout << GetPtrFM("SM", str_SubMonthKey)->GetLineValue(i);
        cout << endl;
    }

    int int_TotalSMExpense = GetPtrFM("SM", str_SubMonthKey)->GetLineValue(uni_RangeTop+1);

    if( int_OFlag == 1 )
    {
        cout << endl;
        cout << "--> " << str_SelMonth << "月/" << CMD_SMTranslate(str_SubMonthKey) << "支出: " << CTool::TransOutFormat(int_TotalSMExpense) << endl;
    }

    if( int_OFlag == 4 )
    {
        cout << endl;
        cout << "--> " << str_SelMonth << "月/" << CMD_SMTranslate(str_SubMonthKey) << "支出: " << CTool::TransOutFormat(int_TotalSMExpense) << endl;
        cout << "----------------------------------------" << endl;
    }

    return int_TotalSMExpense;
}

/**************************************************/
//   展示 Title 支出
//   OFlag == 1 >>> 原始显示模式
//   OFlag == 2 >>> Tag显示模式
//   OFlag == 3 >>> NONE (预留)
//   OFlag == 4 >>> NONE (预留)
/**************************************************/
void CFAitfX::ShowTitle(const string str_TitleKey, const int int_OFlag)
{
    string str_RangeTop("");
    string str_RangeBottom("## Total");

    unsigned int uni_RangeTop = 1;
    unsigned int uni_RangeBottom = GetPtrFM("TT", str_TitleKey)->GetUniqueSearchLineIndex(str_RangeBottom.c_str());

    cout << "----------------------------------------" << endl;

    if( int_OFlag == 1 )
    {

        for(int i=uni_RangeTop+2; i<uni_RangeBottom-1; i++)
        {
            if(LTYPE_FBIRC_LINEUINT == GetPtrFM("TT", str_TitleKey)->GetLineType(i))
            {
                cout << GetPtrFM("TT", str_TitleKey)->GetLineContent(i);
                cout << ": ";
                cout << CTool::TransOutFormat(GetPtrFM("TT", str_TitleKey)->GetLineValue(i));
                cout << endl;
            }
            else if(LTYPE_TTTAG == GetPtrFM("TT", str_TitleKey)->GetLineType(i))
            {
                cout << GetPtrFM("TT", str_TitleKey)->GetFullLine(i);
                cout << " ----------";
                cout << endl;
            }
            else if(LTYPE_BLANK == GetPtrFM("TT", str_TitleKey)->GetLineType(i))
            {
                cout << endl;
            }
        }
    }
    else if( int_OFlag == 2 )
    {
        string str_TagContainer("");
        unsigned int uni_LastTagLine = uni_RangeTop+1;

        for(int i=uni_RangeTop+1; i<=uni_RangeBottom; i++)
        {
            if(i == uni_RangeBottom)
            {
                if(uni_RangeTop+1 == uni_LastTagLine)
                    continue;
                else
                {
                    int int_TagBlockValue = GetPtrFM("TT", str_TitleKey)->CountRangeType(uni_LastTagLine+1, i-1, LTYPE_FBIRC_LINEUINT);
                    if(str_TagContainer != "")
                    {
                        cout << str_TagContainer << ": " << int_TagBlockValue << endl;
                    }
                }
            }
            else if(LTYPE_TTTAG == GetPtrFM("TT", str_TitleKey)->GetLineType(i))
            {
                if(uni_RangeTop+1 == uni_LastTagLine)
                {
                    uni_LastTagLine = i;
                    str_TagContainer = GetPtrFM("TT", str_TitleKey)->GetFullLine(i);

                    continue;
                }
                else
                {
                    int int_TagBlockValue = GetPtrFM("TT", str_TitleKey)->CountRangeType(uni_LastTagLine+1, i-1, LTYPE_FBIRC_LINEUINT);
                    if(str_TagContainer != "")
                    {
                        cout << str_TagContainer << ": " << int_TagBlockValue << endl;
                    }

                    uni_LastTagLine = i;
                    str_TagContainer = GetPtrFM("TT", str_TitleKey)->GetFullLine(i);
                }
            }
        }
    }

    if( str_TitleKey != LOTTERY )
    {
        int int_TotalTTExpense = GetPtrFM("TT", str_TitleKey)->GetLineValue(uni_RangeBottom+2);
    
        cout << "----------------------------------------" << endl;
        cout << "--> " << CMD_TTTranslate(str_TitleKey) << "/总支出: " << CTool::TransOutFormat(int_TotalTTExpense) << endl;
        cout << "----------------------------------------" << endl;
    }
    else
    {
        int int_LotteryInvestEX = m_ptr_FM_tt_lottery->GetLineValue(uni_RangeBottom+2);
        int int_LotteryRewardEX = m_ptr_FM_tt_lottery->GetLineValue(uni_RangeBottom+3);
        int int_LotteryRevenueEX = m_ptr_FM_tt_lottery->GetLineValue(uni_RangeBottom+4);
        int int_LotteryROIEX = m_ptr_FM_tt_lottery->GetLineValue(uni_RangeBottom+5);

        cout << "----------------------------------------" << endl;
        cout << "--> lottery投资: " << CTool::TransOutFormat(int_LotteryInvestEX) << endl;
        cout << "--> lottery回报: " << CTool::TransOutFormat(int_LotteryRewardEX) << endl;
        cout << "--> lottery收益: " << CTool::TransOutFormat(int_LotteryRevenueEX) << endl;
        cout << "--> lottery ROI: " << CTool::TransOutFormat(int_LotteryROIEX) << "%" << endl;
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   Print Sum
/**************************************************/
void CFAitfX::PrintSum(bool bol_NumFlag)
{
    string str_RangeTop = "# Financial Allocation of SUMMARY";
    string str_RangeBottom = "---";

    unsigned int uni_RangeTop = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = m_ptr_FM_SUM->GetUniqueSearchLineIndex(str_RangeBottom.c_str()) - 3;

    if( bol_NumFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### SUM 展示.md ###" << endl;
        cout << endl;

        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << "【" << i << "】" << m_ptr_FM_SUM->GetFullLine(i) << endl;
        }

        cout << "----------------------------------------" << endl;
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "### SUM 展示.md ###" << endl;
        cout << endl;
                
        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << m_ptr_FM_SUM->GetFullLine(i) << endl;
        }

        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   Print 月度
/**************************************************/
void CFAitfX::PrintMonth(const string str_SelMonth, bool bol_NumFlag)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    unsigned int uni_RangeTop = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = m_ptr_FM_life->GetFirstSearchLineIndex(str_RangeBottom.c_str());

    if( bol_NumFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### 月度 展示.md ###" << endl;
        cout << endl;

        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << "【" << i << "】" << m_ptr_FM_life->GetFullLine(i) << endl;
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
            cout << m_ptr_FM_life->GetFullLine(i) << endl;
        }

        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   Print 月度.M
/**************************************************/
void CFAitfX::PrintSubMonth(const string str_SubMonthKey, const string str_SelMonth, bool bol_NumFlag, bool bol_ShowFlag)
{
    string str_RangeTop = CMD_SMTranslate(str_SubMonthKey) + ".M" + str_SelMonth;
    string str_RangeBottom = CMD_SMTranslate(str_SubMonthKey) + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    unsigned int uni_RangeTop = GetPtrFM("SM", str_SubMonthKey)->GetFirstSearchLineIndex(str_RangeTop.c_str());
    unsigned int uni_RangeBottom = GetPtrFM("SM", str_SubMonthKey)->GetFirstSearchLineIndex(str_RangeBottom.c_str());

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
            cout << "【" << i << "】" << GetPtrFM("SM", str_SubMonthKey)->GetFullLine(i) << endl;
        }
    }
    else
    {           
        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << GetPtrFM("SM", str_SubMonthKey)->GetFullLine(i) << endl;
        }
    }

    if( bol_ShowFlag )
    {
        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   Print Tt分项
/**************************************************/
void CFAitfX::PrintTitle(const string str_TitleKey, bool bol_NumFlag)
{
    string str_RangeBottom = "Update Time";

    unsigned int uni_RangeTop = 1;
    unsigned int uni_RangeBottom = GetPtrFM("TT", str_TitleKey)->GetUniqueSearchLineIndex(str_RangeBottom.c_str())-1;

    if( bol_NumFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### Print " << str_TitleKey << ".md ###" << endl;
        cout << endl;

        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << "【" << i << "】" << GetPtrFM("TT", str_TitleKey)->GetFullLine(i) << endl;
        }

        cout << "----------------------------------------" << endl;
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "### Print " << str_TitleKey << ".md ###" << endl;
        cout << endl;
                
        for(int i=uni_RangeTop; i<uni_RangeBottom; i++)
        {
            cout << m_ptr_FM_life->GetFullLine(i) << endl;
        }

        cout << "----------------------------------------" << endl;
    }
}

/**************************************************/
//   添加空白行
/**************************************************/
void CFAitfX::InsertBlankLine(const string str_Type, const string str_Key,\
                              const unsigned int uni_LineIndex)
{
    GetPtrFM(str_Type, str_Key)->InsertBlankLine(uni_LineIndex);
}

/**************************************************/
//   添加行
/**************************************************/
void CFAitfX::InsertLine(const string str_Type, const string str_Key,\
                         const unsigned int uni_LineIndex, const int int_LineValue, const string str_LineContent)
{
    GetPtrFM(str_Type, str_Key)->InsertLine(uni_LineIndex, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);
}

/**************************************************/
//   修改行
/**************************************************/
void CFAitfX::ModifyLine(const string str_Type, const string str_Key,\
                         const unsigned int uni_LineIndex, const int int_LineValue, const string str_LineContent)
{
    GetPtrFM(str_Type, str_Key)->ModifyLineValue(uni_LineIndex, int_LineValue);
    GetPtrFM(str_Type, str_Key)->ModifyLineContent(uni_LineIndex, str_LineContent.c_str());
}

/**************************************************/
//   修改行 Value
/**************************************************/
void CFAitfX::ModifyLineValue(const string str_Type, const string str_Key,\
                              const unsigned int uni_LineIndex, const int int_LineValue)
{
    GetPtrFM(str_Type, str_Key)->ModifyLineValue(uni_LineIndex, int_LineValue);
}

/**************************************************/
//   修改行 Content
/**************************************************/
void CFAitfX::ModifyLineContent(const string str_Type, const string str_Key,\
                                const unsigned int uni_LineIndex, const string str_LineContent)
{
    GetPtrFM(str_Type, str_Key)->ModifyLineContent(uni_LineIndex, str_LineContent.c_str());
}

/**************************************************/
//   复制行
/**************************************************/
void CFAitfX::CopyLine(const string str_Type, const string str_Key,\
                       const unsigned int uni_LineIndex, const unsigned int uni_LineIndexNew)
{
    int int_LineValue = GetPtrFM(str_Type, str_Key)->GetLineValue(uni_LineIndex);
    string str_LineContent = GetPtrFM(str_Type, str_Key)->GetLineContent(uni_LineIndex);

    GetPtrFM(str_Type, str_Key)->InsertLine(uni_LineIndexNew, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);
}

/**************************************************/
//   移动行
/**************************************************/
void CFAitfX::MoveLine(const string str_Type, const string str_Key,\
                       const unsigned int uni_LineIndex, const unsigned int uni_LineIndexNew)
{
    int int_LineValue = GetPtrFM(str_Type, str_Key)->GetLineValue(uni_LineIndex);
    string str_LineContent = GetPtrFM(str_Type, str_Key)->GetLineContent(uni_LineIndex);

    GetPtrFM(str_Type, str_Key)->DeleteLine(uni_LineIndex);

    if(uni_LineIndex < uni_LineIndexNew)
        GetPtrFM(str_Type, str_Key)->InsertLine(uni_LineIndexNew-1, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);
    else if(uni_LineIndex > uni_LineIndexNew)
        GetPtrFM(str_Type, str_Key)->InsertLine(uni_LineIndexNew, LTYPE_FBIRC_LINEUINT, int_LineValue, str_LineContent);
    else
        return;
}

/**************************************************/
//   删除行
/**************************************************/
void CFAitfX::DeleteLine(const string str_Type, const string str_Key,\
                         const unsigned int uni_LineIndex)
{
    GetPtrFM(str_Type, str_Key)->DeleteLine(uni_LineIndex);
}

void CFAitfX::CheckTimeStamp()
{
    cout << "----------------------------------------" << endl;

    for(int i=0; i<m_uni_FM_aszie; i++)
    {
        string str_TimeMsg = m_ptr_FM_array[i]->GetTimeStamp();
        str_TimeMsg += " : ";
        str_TimeMsg += m_ptr_FM_array[i]->GetFileName();
        cout << str_TimeMsg << endl;
    }
    
    cout << "----------------------------------------" << endl;
}

void CFAitfX::CheckEqualAllFile()
{
    for(int i=0; i<m_uni_FM_aszie; i++)
    {
        if(0 != m_ptr_FM_array[i]->FileComparer())
        {
            string str_ErrorMsg = m_ptr_FM_array[i]->GetFileName();
            str_ErrorMsg += " NOT EQUAL";
            CTool::MassageOutFotmat(str_ErrorMsg, '!');
            return;
        }
    }

    CTool::MassageOutFotmat("All File EQUAL", '*');
}

void CFAitfX::CheckEqualAllFile(const string str_Path)
{
    for(int i=0; i<m_uni_FM_aszie; i++)
    {
        string str_BakupFile = str_Path + m_ptr_FM_array[i]->GetFileName();

        if(0 != m_ptr_FM_array[i]->FileComparer(str_BakupFile.c_str()))
        {
            string str_ErrorMsg = m_ptr_FM_array[i]->GetFileName();
            str_ErrorMsg += " NOT EQUAL";
            CTool::MassageOutFotmat(str_ErrorMsg, '!');
            return;
        }
    }

    CTool::MassageOutFotmat("All Bakup File EQUAL", '*');
}

void CFAitfX::SyncAllFile()
{
    for(int i=0; i<m_uni_FM_aszie; i++)
    {
        m_ptr_FM_array[i]->SyncFile();
    }
}

void CFAitfX::WriteAllFile()
{
    for(int i=0; i<m_uni_FM_aszie; i++)
    {
        m_ptr_FM_array[i]->UpdateTimeStamp();
        m_ptr_FM_array[i]->FileWriter();
    }
}

void CFAitfX::BackUpAllFile(const string str_BackUpPath)
{
    for(int i=0; i<m_uni_FM_aszie; i++)
    {
        m_ptr_FM_array[i]->BackUpFile(str_BackUpPath);
    }
}

// tips 番茄@20180919 - 扩展添加点3/3
CFileManager *CFAitfX::GetPtrFM(const string str_Type, const string str_Key)
{
    if(str_Type == "SUM")
        return m_ptr_FM_SUM;
    else if(str_Type == "MONTH")
        return m_ptr_FM_life;
    else if( (str_Type == "SM") && (str_Key == DGTLER) )
        return m_ptr_FM_sm_DGtler;
    else if( (str_Type == "SM") && (str_Key == BOOKS) )
        return m_ptr_FM_sm_Books;
    else if( (str_Type == "SM") && (str_Key == KEEP) )
        return m_ptr_FM_sm_KEEP;
    else if( (str_Type == "SM") && (str_Key == TB) )
        return m_ptr_FM_sm_TB;
    else if( (str_Type == "SM") && (str_Key == SA) )
        return m_ptr_FM_sm_sa;
    else if( (str_Type == "TT") && (str_Key == DK) )
        return m_ptr_FM_tt_DK;
    else if( (str_Type == "TT") && (str_Key == NS) )
        return m_ptr_FM_tt_NS;
    else if( (str_Type == "TT") && (str_Key == NR) )
        return m_ptr_FM_tt_NR;
    else if( (str_Type == "TT") && (str_Key == TRAVEL) )
        return m_ptr_FM_tt_travel;
    else if( (str_Type == "TT") && (str_Key == LOTTERY) )
        return m_ptr_FM_tt_lottery;
    else if( (str_Type == "TT") && (str_Key == BOX) )
        return m_ptr_FM_tt_BOX;
    else
    {
        CTool::MassageOutFotmat("Key Error", '!');
        return m_ptr_FM_NULL;
    }
}

string CMD_SMTranslate(const string str_SubMonthKey)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    return ptr_ScriptRipper->SubMonthTranslater(str_SubMonthKey);
}

string CMD_TTTranslate(const string str_TitleKey)
{
    CScriptRipper *ptr_ScriptRipper = Singleton<CScriptRipper>::GetInstance("./FA_Auto_Script.xml");
    return ptr_ScriptRipper->TitleTranslater(str_TitleKey);
}


//------------------------------//
//   River flows in summer
//------------------------------//
