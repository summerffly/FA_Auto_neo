
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "FAitfX.h"

#include "./../X_Frame/DefLib.h"

using namespace std;


// tips 番茄@20171211 - 使用带参宏函数Key填错会有风险，用m_cls_FM_TVT的head进行校验
#define FM_SUBMONTH(str)  ((!(str).compare("Books"))?(m_cls_FM_sm_Books):\
                           ((!(str).compare("KEEP"))?(m_cls_FM_sm_KEEP):\
                           ((!(str).compare("TB"))?(m_cls_FM_sm_TB):\
                           ((!(str).compare("sa"))?(m_cls_FM_sm_sa):(m_cls_FM_TVT)))) )

// tips 番茄@20171211 - 使用带参宏函数Key填错会有风险，用m_cls_FM_TVT的head进行校验
#define FM_TITLE(str)  ((!(str).compare("DK"))?(m_cls_FM_tt_DK):\
                        ((!(str).compare("NS"))?(m_cls_FM_tt_NS):\
                        ((!(str).compare("travel"))?(m_cls_FM_tt_travel):\
                        ((!(str).compare("lottery"))?(m_cls_FM_tt_lottery):(m_cls_FM_TVT)))) )
                    
typedef struct
{
    string str_UnitContent;
    unsigned int uni_UnitValueABS;
}UNIT_INFO;

typedef struct
{
    string str_TrendMonth;
    unsigned int uni_TrendValueABS;
}TREND_INFO;

CFAitfX::CFAitfX()
{
    m_cls_FM_TVT = CFileManager("./FA_TVT.md");
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

CFAitfX::~CFAitfX()
{
    // Do Nothing
}

/**************************************************/
//   校验 总收支
//   校验结果只通过返回值体现
//   不会打印结果
/**************************************************/
int CFAitfX::RCheckAggrSurplus(unsigned int &uni_AliRest)
{
    unsigned int uni_ItemSize = CCFGLoader::m_vec_stc_FAItem.size();
    unsigned int uni_ItemCounter = 0;

    int int_AggrSurplus = 0;
    int int_AggrSurplusCK = 0;
    int int_AggrSurplusPlus = 0;
    int int_AggrSurplusPlusCK = 0;

    string str_ItemFlagContent("");
    string str_ItemFlagAttrbute("");
    unsigned int uni_ItemFlag = 0;

    while( uni_ItemCounter < uni_ItemSize )
    {
        str_ItemFlagContent.clear();
        str_ItemFlagAttrbute.clear();
        str_ItemFlagContent += CCFGLoader::m_vec_stc_FAItem.at(uni_ItemCounter).str_ItemContent;
        str_ItemFlagAttrbute += CCFGLoader::m_vec_stc_FAItem.at(uni_ItemCounter).str_ItemAttrbute;

        m_cls_FM_TVT.SearchLineKey(str_ItemFlagContent.c_str());
        uni_ItemFlag = m_cls_FM_TVT.GetSearchLineIndex(1);

        if( str_ItemFlagAttrbute.compare("FO")==0 )
        {
            int_AggrSurplusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
            int_AggrSurplusPlusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("Title")==0 )
        {
            int_AggrSurplusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+1);
            int_AggrSurplusPlusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+1);
        }
        else if( str_ItemFlagAttrbute.compare("Month")==0 )
        {
            int_AggrSurplusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+3);
            int_AggrSurplusPlusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+3);
        }
        else if( str_ItemFlagAttrbute.compare("FC")==0 )
        {
            int_AggrSurplus = m_cls_FM_TVT.GetLineValue(uni_ItemFlag);

            if( int_AggrSurplus != int_AggrSurplusCK )
            {
                return -1;
            }
        }
        else if( str_ItemFlagAttrbute.compare("FTail")==0 )
        {
            int_AggrSurplusPlusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("FB")==0 )
        {
            // tips 番茄@20171218 - balance项，需要执行减法
            int_AggrSurplusPlusCK -= m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("FF")==0 )
        {
            int_AggrSurplusPlus = m_cls_FM_TVT.GetLineValue(uni_ItemFlag);

            if( int_AggrSurplusPlus != int_AggrSurplusPlusCK )
            {
                return -2;
            }
        }

        uni_ItemCounter++;
    }

    uni_AliRest = (unsigned int)int_AggrSurplusPlus;

    return 0;
}

/**************************************************/
//   校验 总收支
/**************************************************/
void CFAitfX::CheckAggrSurplus()
{
    unsigned int uni_ItemSize = CCFGLoader::m_vec_stc_FAItem.size();
    unsigned int uni_ItemCounter = 0;

    int int_AggrSurplus = 0;
    int int_AggrSurplusCK = 0;
    int int_AggrSurplusPlus = 0;
    int int_AggrSurplusPlusCK = 0;

    string str_ItemFlagContent("");
    string str_ItemFlagAttrbute("");
    unsigned int uni_ItemFlag = 0;

    while( uni_ItemCounter < uni_ItemSize )
    {
        str_ItemFlagContent.clear();
        str_ItemFlagAttrbute.clear();
        str_ItemFlagContent += CCFGLoader::m_vec_stc_FAItem.at(uni_ItemCounter).str_ItemContent;
        str_ItemFlagAttrbute += CCFGLoader::m_vec_stc_FAItem.at(uni_ItemCounter).str_ItemAttrbute;

        m_cls_FM_TVT.SearchLineKey(str_ItemFlagContent.c_str());
        uni_ItemFlag = m_cls_FM_TVT.GetSearchLineIndex(1);

        if( str_ItemFlagAttrbute.compare("FO")==0 )
        {
            int_AggrSurplusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
            int_AggrSurplusPlusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("Title")==0 )
        {
            int_AggrSurplusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+1);
            int_AggrSurplusPlusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+1);
        }
        else if( str_ItemFlagAttrbute.compare("Month")==0 )
        {
            int_AggrSurplusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+3);
            int_AggrSurplusPlusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+3);
        }
        else if( str_ItemFlagAttrbute.compare("FC")==0 )
        {
            int_AggrSurplus = m_cls_FM_TVT.GetLineValue(uni_ItemFlag);

            cout << "----------------------------------------" << endl;
            cout << "### 当前财富 ###" << endl;
            cout << "读取值: " << CTool::TransOutFormat(int_AggrSurplus) << endl;
            cout << "校验值: " << CTool::TransOutFormat(int_AggrSurplusCK) << endl;
        }
        else if( str_ItemFlagAttrbute.compare("FTail")==0 )
        {
            int_AggrSurplusPlusCK += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("FB")==0 )
        {
            // tips 番茄@20171218 - balance项，需要执行减法
            int_AggrSurplusPlusCK -= m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("FF")==0 )
        {
            int_AggrSurplusPlus = m_cls_FM_TVT.GetLineValue(uni_ItemFlag);

            cout << "----------------------------------------" << endl;
            cout << "### 余额宝 ###" << endl;
            cout << "读取值: " << CTool::TransOutFormat(int_AggrSurplusPlus) << endl;
            cout << "校验值: " << CTool::TransOutFormat(int_AggrSurplusPlusCK) << endl;
            cout << "----------------------------------------" << endl;
        }

        uni_ItemCounter++;
    }
}

/**************************************************/
//   更新 总收支
/**************************************************/
void CFAitfX::UpdateAggrSurplus()
{
    unsigned int uni_ItemSize = CCFGLoader::m_vec_stc_FAItem.size();
    unsigned int uni_ItemCounter = 0;

    int int_AggrSurplus = 0;
    int int_AggrSurplusUD = 0;
    int int_AggrSurplusPlus = 0;
    int int_AggrSurplusPlusUD = 0;

    string str_ItemFlagContent("");
    string str_ItemFlagAttrbute("");
    unsigned int uni_ItemFlag = 0;

    while( uni_ItemCounter < uni_ItemSize )
    {
        str_ItemFlagContent.clear();
        str_ItemFlagAttrbute.clear();
        str_ItemFlagContent += CCFGLoader::m_vec_stc_FAItem.at(uni_ItemCounter).str_ItemContent;
        str_ItemFlagAttrbute += CCFGLoader::m_vec_stc_FAItem.at(uni_ItemCounter).str_ItemAttrbute;

        m_cls_FM_TVT.SearchLineKey(str_ItemFlagContent.c_str());
        uni_ItemFlag = m_cls_FM_TVT.GetSearchLineIndex(1);

        if( str_ItemFlagAttrbute.compare("FO")==0 )
        {
            int_AggrSurplusUD += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
            int_AggrSurplusPlusUD += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("Title")==0 )
        {
            int_AggrSurplusUD += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+1);
            int_AggrSurplusPlusUD += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+1);
        }
        else if( str_ItemFlagAttrbute.compare("Month")==0 )
        {
            int_AggrSurplusUD += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+3);
            int_AggrSurplusPlusUD += m_cls_FM_TVT.GetLineValue(uni_ItemFlag+3);
        }
        else if( str_ItemFlagAttrbute.compare("FC")==0 )
        {
            int_AggrSurplus = m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
            m_cls_FM_TVT.ModifyLineValue(uni_ItemFlag, int_AggrSurplusUD);

            cout << "----------------------------------------" << endl;
            cout << "### 当前财富 ###" << endl;
            cout << "初始值: " << CTool::TransOutFormat(int_AggrSurplus) << endl;
            cout << "更新值: " << CTool::TransOutFormat(int_AggrSurplusUD) << endl;
        }
        else if( str_ItemFlagAttrbute.compare("FTail")==0 )
        {
            int_AggrSurplusPlusUD += m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("FB")==0 )
        {
            // tips 番茄@20171218 - balance项，需要执行减法
            int_AggrSurplusPlusUD -= m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
        }
        else if( str_ItemFlagAttrbute.compare("FF")==0 )
        {
            int_AggrSurplusPlus = m_cls_FM_TVT.GetLineValue(uni_ItemFlag);
            m_cls_FM_TVT.ModifyLineValue(uni_ItemFlag, int_AggrSurplusPlusUD);

            cout << "----------------------------------------" << endl;
            cout << "### 余额宝 ###" << endl;
            cout << "初始值: " << CTool::TransOutFormat(int_AggrSurplusPlus) << endl;
            cout << "更新值: " << CTool::TransOutFormat(int_AggrSurplusPlusUD) << endl;
            cout << "----------------------------------------" << endl;
        }

        uni_ItemCounter++;
    }
}

/**************************************************/
//   FA全系统校验 总收支
/**************************************************/
void CFAitfX::CheckFA(const string str_CurMonth)
{
    int int_RetCheck = 0;
    unsigned int uni_AliRest = 0;

    if( 0 != CheckTitleExpense("lottery", false) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!      lottery NOT Pass Check      !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    if( 0 != CheckTitleExpense("DK", false) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!         DK NOT Pass Check        !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    if( 0 != CheckTitleExpense("NS", false) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!         NS NOT Pass Check        !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    if( 0 != CheckTitleExpense("travel", false) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!       travel NOT Pass Check      !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    if( -1 == RCheckSubMonthExpense("Books", str_CurMonth) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!       Books NOT Pass Check       !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    if( -1 == RCheckSubMonthExpense("KEEP", str_CurMonth) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        KEEP NOT Pass Check       !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    if( -1 == RCheckSubMonthExpense("TB", str_CurMonth) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!         TB NOT Pass Check        !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    if( -1 == RCheckSubMonthExpense("sa", str_CurMonth) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!         sa NOT Pass Check        !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    if( 0 != CheckMonthSurplus(str_CurMonth, false) )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!       Month NOT Pass Check       !!!" << endl;
        cout << "----------------------------------------" << endl;

        return;
    }

    int_RetCheck = RCheckAggrSurplus(uni_AliRest);

    if( 0 != int_RetCheck )
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        TVT NOT Pass Check        !!!" << endl;
        cout << "----------------------------------------" << endl;
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "###   FA全系统校验Pass :)   ###" << endl;
        cout << "余额宝: " << CTool::TransOutFormat(uni_AliRest) << endl;
        cout << "----------------------------------------" << endl;
    }
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

    m_cls_FM_TVT.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_AFLine = m_cls_FM_TVT.GetSearchLineIndex(1);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    unsigned int uni_AFMonthSalaryEX = m_cls_FM_TVT.GetLineValue(uni_AFLine+1);
    int int_AFMonthExpenseEX = m_cls_FM_TVT.GetLineValue(uni_AFLine+2);
    int int_AFMonthRestEX = m_cls_FM_TVT.GetLineValue(uni_AFLine+3);

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
void CFAitfX::UpdateMonthSurplus(const string str_SelMonth)
{
    string str_RangeTop = "## life.M" + str_SelMonth;
    string str_RangeBottom = "## life.M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    unsigned int uni_MonthSalary = m_cls_FM_life.GetLineValue(uni_RangeTop+1);
    int int_MonthExpense = m_cls_FM_life.GetLineValue(uni_RangeTop+2);
    int int_MonthSurplus = m_cls_FM_life.GetLineValue(uni_RangeTop+3);
    int int_MonthExpenseUD = m_cls_FM_life.CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);
    int int_MonthSurplusUD = uni_MonthSalary + int_MonthExpenseUD;

    m_cls_FM_life.ModifyLineValue(uni_RangeTop+2, int_MonthExpenseUD);
    m_cls_FM_life.ModifyLineValue(uni_RangeTop+3, int_MonthSurplusUD);

    cout << "----------------------------------------" << endl;
    cout << "### 更新" << str_SelMonth << "月/收支 ###" << endl;
    cout << "初始薪资值: " << CTool::TransOutFormat(uni_MonthSalary) << endl;
    cout << "初始支出值: " << CTool::TransOutFormat(int_MonthExpense) << endl;
    cout << "初始结余值: " << CTool::TransOutFormat(int_MonthSurplus) << endl;
    cout << "----------------------------------------" << endl;
    cout << "更新支出值: " << CTool::TransOutFormat(int_MonthExpenseUD) << endl;
    cout << "更新结余值: " << CTool::TransOutFormat(int_MonthSurplusUD) << endl;
    cout << "----------------------------------------" << endl;
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
        cout << "----------------------------------------" << endl;
        cout << "!!!     No Line Contain Input Key    !!!" << endl;
        cout << "----------------------------------------" << endl;

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

    m_cls_FM_TVT.SearchLineKey(str_SelMonthFL.c_str());
    unsigned int uni_SelMonthTVT = m_cls_FM_TVT.GetSearchLineIndex(1);

    // 读取 life.M 月度收支
    unsigned int uni_MonthSalary = m_cls_FM_life.GetLineValue(uni_SelMonth+1);
    int int_MonthExpense = m_cls_FM_life.GetLineValue(uni_SelMonth+2);
    int int_MonthSurplus = m_cls_FM_life.GetLineValue(uni_SelMonth+3);

    // 同步 总收支
    m_cls_FM_TVT.ModifyLineValue(uni_SelMonthTVT+1, uni_MonthSalary);
    m_cls_FM_TVT.ModifyLineValue(uni_SelMonthTVT+2, int_MonthExpense);
    m_cls_FM_TVT.ModifyLineValue(uni_SelMonthTVT+3, int_MonthSurplus);
}

/**************************************************/
//   分析 月度变化趋势
/**************************************************/
void CFAitfX::AnalysisMonthTrend(const string str_MonthKey)
{
    unsigned int uni_TrendIndex = 0;
    string str_TrendMonth = CCFGLoader::m_str_OriginMonth;
    unsigned int uni_TrendValueABS = 0;
    vector<TREND_INFO> vec_stc_TrendInfo;
    TREND_INFO stc_TrendInfo;

    // 建构 vector
    while( str_TrendMonth != CTool::GenerateNextMonth(CCFGLoader::m_str_CurrentMonth) )
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
        str_TrendMonth = CTool::GenerateNextMonth(str_TrendMonth);
    }

    // 获取 vector最大值
    unsigned int uni_TrendSize = vec_stc_TrendInfo.size();
    unsigned int uni_MaxTrendValue = 0;

    if(uni_TrendSize == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!      Analysis KeyWord Error      !!!" << endl;
        cout << "----------------------------------------" << endl;
        return;
    }

    for(int i=0; i<uni_TrendSize; i++)
    {
        if( vec_stc_TrendInfo.at(i).uni_TrendValueABS > uni_MaxTrendValue )
        {
            uni_MaxTrendValue = vec_stc_TrendInfo.at(i).uni_TrendValueABS;
        }
    }
    double dob_ScaleRate = (double)50 / uni_MaxTrendValue;

    // 绘制 vector
    unsigned int uni_Scalde = 0;
    double dob_GrowRate = 0.0;
    unsigned int uni_preValue = 0;
    unsigned int uni_nextValue = 0;
    
    cout << "----------------------------------------" << endl;
    cout << "### 月度趋势分析 ###" << endl;
    cout << endl;

    for(int i=0; i<uni_TrendSize; i++)
    {
        cout << vec_stc_TrendInfo.at(i).str_TrendMonth << "月/" << str_MonthKey << ": ";
        uni_Scalde = dob_ScaleRate * vec_stc_TrendInfo.at(i).uni_TrendValueABS;
        for(int i=1; i<=uni_Scalde; i++)
        {
            cout << "|";
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
        cout << "----------------------------------------" << endl;
        cout << "!!!         Error Month Input        !!!" << endl;
        cout << "----------------------------------------" << endl;
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
            cout << "|";
        }
        cout << "  " << vec_stc_UnitInfo.at(i).str_UnitContent << " (";
        printf("%.1f", (dob_PPRate*100));
        cout << "%)" << endl;
    }

    cout << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   校验 子项.M 月度支出
//   校验结果只通过返回值体现
//   不会打印结果
//   只与上层校验
/**************************************************/
int CFAitfX::RCheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth)
{
    if(FM_SUBMONTH(str_SubMonthKey).GetFullLine(1).compare("# Financial Allocation of TVT") == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!      SubMonth KeyWord Error      !!!" << endl;
        cout << "----------------------------------------" << endl;
        return -2;
    }

    string str_RangeTop = str_SubMonthKey + ".M" + str_SelMonth;
    string str_RangeBottom = str_SubMonthKey + ".M" + CTool::GenerateNextMonth(str_SelMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_lifeLine = m_cls_FM_life.GetSearchLineIndex(1);

    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);
    FM_SUBMONTH(str_SubMonthKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_SUBMONTH(str_SubMonthKey).GetSearchLineIndex(1);

    int int_SubMonthExpenseCK = FM_SUBMONTH(str_SubMonthKey).CountRangeType(uni_RangeTop+2, uni_RangeBottom-1,\
                                            LTYPE_FBIRC_LINEUINT);
    
    if(int_SubMonthExpenseCK == m_cls_FM_life.GetLineValue(uni_lifeLine))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

/**************************************************/
//   校验 子项.M 月度支出
/**************************************************/
void CFAitfX::CheckSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth)
{
    if(FM_SUBMONTH(str_SubMonthKey).GetFullLine(1).compare("# Financial Allocation of TVT") == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!      SubMonth KeyWord Error      !!!" << endl;
        cout << "----------------------------------------" << endl;
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

    int int_SubMonthExpenseCK = FM_SUBMONTH(str_SubMonthKey).CountRangeType(uni_RangeTop+2, uni_RangeBottom-1,\
                                       LTYPE_FBIRC_LINEUINT);

    cout << "----------------------------------------" << endl;
    cout << "### " << str_SelMonth << "月/" << str_SubMonthKey << "支出 ###" << endl;
    cout << "life.M_读取值: " << CTool::TransOutFormat(m_cls_FM_life.GetLineValue(uni_lifeLine)) << endl;
    cout << "sub.M_读取值: " << CTool::TransOutFormat(FM_SUBMONTH(str_SubMonthKey).GetLineValue(uni_RangeTop+1)) << endl;
    cout << "sub.M_校验值: " << CTool::TransOutFormat(int_SubMonthExpenseCK) << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   更新 子项.M 月度支出
/**************************************************/
void CFAitfX::UpdateSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth)
{
    if(FM_SUBMONTH(str_SubMonthKey).GetFullLine(1).compare("# Financial Allocation of TVT") == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!      SubMonth KeyWord Error      !!!" << endl;
        cout << "----------------------------------------" << endl;
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

    cout << "----------------------------------------" << endl;
    cout << "### " << str_SelMonth << "月/" << str_SubMonthKey << "支出 ###" << endl;
    cout << "sub.M_初始值: " << CTool::TransOutFormat(int_SubMonthExpense) << endl;
    cout << "sub.M_更新值: " << CTool::TransOutFormat(int_SubMonthExpenseUD) << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   添加行 子项.M 月度支出
/**************************************************/
void CFAitfX::AppendSubMonthExpense(const string str_SubMonthKey, const string str_SelMonth,\
                                    const int int_LineValue, const string str_LineContent)
{
    if(FM_SUBMONTH(str_SubMonthKey).GetFullLine(1).compare("# Financial Allocation of TVT") == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!      SubMonth KeyWord Error      !!!" << endl;
        cout << "----------------------------------------" << endl;
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
    if(FM_TITLE(str_TitleKey).GetFullLine(1).compare("# Financial Allocation of TVT") == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        Title KeyWord Error       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return -9;
    }

    string str_RangeTop = "## " + str_TitleKey;
    string str_RangeBottom("## Total");

    m_cls_FM_TVT.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_AFLine = m_cls_FM_TVT.GetSearchLineIndex(1);

    unsigned int uni_RangeTop = 2;
    FM_TITLE(str_TitleKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_TITLE(str_TitleKey).GetSearchLineIndex(1);

    int int_AFTitleExpenseEX = m_cls_FM_TVT.GetLineValue(uni_AFLine+1);

    int int_TitleExpenseEX = FM_TITLE(str_TitleKey).GetLineValue(uni_RangeBottom+2);
    int int_TitleExpenseCK = FM_TITLE(str_TitleKey).CountRangeType(uni_RangeTop, uni_RangeBottom-1,\
                                       LTYPE_FBIRC_LINEUINT);

    if( bol_OFlag )
    {
        cout << "----------------------------------------" << endl;
        cout << "### " << str_TitleKey << "/支出 ###" << endl;
        cout << "TVT_读取值: " << CTool::TransOutFormat(int_AFTitleExpenseEX) << endl;
        cout << "Tt_读取值: " << CTool::TransOutFormat(int_TitleExpenseEX) << endl;
        cout << "Tt_校验值: " << CTool::TransOutFormat(int_TitleExpenseCK) << endl;
        cout << "----------------------------------------" << endl;
    }

    if( int_TitleExpenseEX != int_TitleExpenseCK )
    {
        return -1;
    }
    else if( int_TitleExpenseEX != int_AFTitleExpenseEX )
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
void CFAitfX::UpdateTitleExpense(const string str_TitleKey)
{
    if(FM_TITLE(str_TitleKey).GetFullLine(1).compare("# Financial Allocation of TVT") == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        Title KeyWord Error       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return;
    }

    string str_RangeTop = "## " + str_TitleKey;
    string str_RangeBottom("## Total");

    m_cls_FM_TVT.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_TVTLine = m_cls_FM_TVT.GetSearchLineIndex(1);

    unsigned int uni_RangeTop = 2;
    FM_TITLE(str_TitleKey).SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = FM_TITLE(str_TitleKey).GetSearchLineIndex(1);

    int int_TitleExpense = FM_TITLE(str_TitleKey).GetLineValue(uni_RangeBottom+2);
    int int_TitleExpenseUD = FM_TITLE(str_TitleKey).CountRangeType(uni_RangeTop, uni_RangeBottom-1,\
                                      LTYPE_FBIRC_LINEUINT);

    FM_TITLE(str_TitleKey).ModifyLineValue(uni_RangeBottom+2, int_TitleExpenseUD);
    m_cls_FM_TVT.ModifyLineValue(uni_TVTLine+1, int_TitleExpenseUD);

    cout << "----------------------------------------" << endl;
    cout << "### " << str_TitleKey << "/支出 ###" << endl;
    cout << "Tt_初始值: " << CTool::TransOutFormat(int_TitleExpense) << endl;
    cout << "Tt_更新值: " << CTool::TransOutFormat(int_TitleExpenseUD) << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   添加行 Tt分项 月度支出
/**************************************************/
void CFAitfX::AppendTitleExpense(const string str_TitleKey,\
                                 const int int_LineValue, const string str_LineContent)
{
    if(FM_TITLE(str_TitleKey).GetFullLine(1).compare("# Financial Allocation of TVT") == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!        Title KeyWord Error       !!!" << endl;
        cout << "----------------------------------------" << endl;
        return;
    }

    string str_RangeTop = "## " + str_TitleKey;
    string str_RangeBottom("## Total");

    m_cls_FM_TVT.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_TVTLine = m_cls_FM_TVT.GetSearchLineIndex(1);

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
    m_cls_FM_TVT.ModifyLineValue(uni_TVTLine+1, int_TitleExpenseAP);

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

    m_cls_FM_TVT.SearchLineKey(str_LotteryTop.c_str());
    unsigned int uni_TVTLine = m_cls_FM_TVT.GetSearchLineIndex(1);

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
    m_cls_FM_TVT.ModifyLineValue(uni_TVTLine+1, int_LotterySurplusAP);

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
    m_cls_FM_TVT.SearchLineKey(str_FirstKey.c_str());
    unsigned int uni_FirstLine = m_cls_FM_TVT.GetSearchLineIndex(1);
    int int_FirstValue = m_cls_FM_TVT.GetLineValue(uni_FirstLine);

    m_cls_FM_TVT.SearchLineKey(str_SecondKey.c_str());
    unsigned int uni_SecondLine = m_cls_FM_TVT.GetSearchLineIndex(1);
    int int_SecondValue = m_cls_FM_TVT.GetLineValue(uni_SecondLine);

    // bol_TransferFlag为true >>> First++ Second--
    if( bol_TransferFlag == true )
    {
        m_cls_FM_TVT.ModifyLineValue(uni_FirstLine, int_FirstValue + uni_BalanceValueABS);
        m_cls_FM_TVT.ModifyLineValue(uni_SecondLine, int_SecondValue - uni_BalanceValueABS);
    }
    // bol_TransferFlag为false >>> First-- Second++
    else
    {
        m_cls_FM_TVT.ModifyLineValue(uni_FirstLine, int_FirstValue - uni_BalanceValueABS);
        m_cls_FM_TVT.ModifyLineValue(uni_SecondLine, int_SecondValue + uni_BalanceValueABS);
    }
}

/**************************************************/
//   校验 Temp 支出
/**************************************************/
void CFAitfX::CheckTempExpense()
{
    //string str_RangeTop = "## " + str_TempKey;
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

void CFAitfX::SyncAllFile()
{
    m_cls_FM_TVT.SyncFile();
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
    m_cls_FM_TVT.FileWriter();
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
    m_cls_FM_TVT.BackUpFile(str_BackUpPath);
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
