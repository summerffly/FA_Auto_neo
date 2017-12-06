
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "FAitfX.h"

#include "./../X_Frame/DefLib.h"

using namespace std;


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
}

CFAitfX::~CFAitfX()
{
    // Do Nothing
}

/**************************************************/
//   校验 life.M 月度支出
/**************************************************/
void CFAitfX::CheckMonthExpense(const string str_CurMonth)
{
    string str_RangeTop("## life.M");
    str_RangeTop += str_CurMonth;
    string str_RangeBottom("## life.M");
    str_RangeBottom += CTool::GenerateNextMonth(str_CurMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    int int_MonthExpense = m_cls_FM_life.CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);

    cout << "----------------------------------------" << endl;
    cout << "### " << str_CurMonth << "月/支出 ###" << endl;
    cout << "读取值: " << CTool::TransOutFormat(m_cls_FM_life.GetLineValue(uni_RangeTop+2)) << endl;
    cout << "校验值: " << CTool::TransOutFormat(int_MonthExpense) << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   校验 life.M 月度收支
/**************************************************/
void CFAitfX::CheckMonthSurplus(const string str_CurMonth)
{
    string str_RangeTop("## life.M");
    str_RangeTop += str_CurMonth;
    string str_RangeBottom("## life.M");
    str_RangeBottom += CTool::GenerateNextMonth(str_CurMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    unsigned int uni_MonthSalary = m_cls_FM_life.GetLineValue(uni_RangeTop+1);
    int int_MonthExpense = m_cls_FM_life.CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);

    cout << "----------------------------------------" << endl;
    cout << "### " << str_CurMonth << "月/薪资 ###" << endl;
    cout << "读取值: " << CTool::TransOutFormat(uni_MonthSalary) << endl;
    cout << "### " << str_CurMonth << "月/支出 ###" << endl;
    cout << "读取值: " << CTool::TransOutFormat(m_cls_FM_life.GetLineValue(uni_RangeTop+2)) << endl;
    cout << "校验值: " << CTool::TransOutFormat(int_MonthExpense) << endl;
    cout << "### " << str_CurMonth << "月/结余 ###" << endl;
    cout << "读取值: " << CTool::TransOutFormat(m_cls_FM_life.GetLineValue(uni_RangeTop+3)) << endl;
    cout << "校验值: " << CTool::TransOutFormat(uni_MonthSalary + int_MonthExpense) << endl;
    cout << "----------------------------------------" << endl;
}

/**************************************************/
//   校验 子项.M 月度支出
/**************************************************/
void CFAitfX::CheckSubMonthExpense(const string str_SubMonthKey, const string str_CurMonth)
{
    string str_RangeTop = str_SubMonthKey + ".M" + str_CurMonth;
    string str_RangeBottom = str_SubMonthKey + ".M" + CTool::GenerateNextMonth(str_CurMonth);

    m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    unsigned int uni_lifeLine = m_cls_FM_life.GetSearchLineIndex(1);
    //m_cls_FM_life.SearchLineKey(str_RangeTop.c_str());
    //unsigned int uni_RangeTop = m_cls_FM_life.GetSearchLineIndex(1);
    //m_cls_FM_life.SearchLineKey(str_RangeBottom.c_str());
    //unsigned int uni_RangeBottom = m_cls_FM_life.GetSearchLineIndex(1);

    //int int_MonthExpense = m_cls_FM_life.CountRangeType(uni_RangeTop+4, uni_RangeBottom-1, LTYPE_FBIRC_LINEUINT);

    cout << "----------------------------------------" << endl;
    cout << "### " << str_CurMonth << "月/" << str_SubMonthKey << "支出 ###" << endl;
    cout << "life.M读取值: " << CTool::TransOutFormat(m_cls_FM_life.GetLineValue(uni_lifeLine)) << endl;
    //cout << "校验值: " << CTool::TransOutFormat(int_MonthExpense) << endl;
    cout << "----------------------------------------" << endl;
}

//------------------------------//
//   river flows in summer
//------------------------------//
