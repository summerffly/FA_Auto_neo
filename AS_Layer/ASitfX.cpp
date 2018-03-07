
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
    // Do Nothing
}

/**************************************************/
//   CASitfX 析构函数
/**************************************************/
CASitfX::~CASitfX()
{
    // Do Nothing
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


//------------------------------//
//   River flows in summer
//------------------------------//
