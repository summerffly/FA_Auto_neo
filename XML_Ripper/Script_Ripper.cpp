
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "Script_Ripper.h"

using namespace std;


/**************************************************/
//   CScriptRipper 构造函数
/**************************************************/
CScriptRipper::CScriptRipper(const char *cha_xmlPath):
m_cls_XMLRipper(cha_xmlPath)
{
    m_str_ScriptFilePath = cha_xmlPath;

    m_str_Version = "";

    m_str_OriginSum = "";
    m_str_CurrentSum = "";
    //m_str_CAFSum = "";

    m_str_OriginMonth = "";
    m_str_CurrentMonth = "";
    m_str_PreviousMonth = "";
    m_uni_OriginMonth = 0;
    m_uni_CurrentMonth = 0;
    m_uni_PreviousMonth = 0;

    m_uni_MonthSalary = 0;

    m_vec_str_Month.clear();

    m_vec_str_Title.clear();
    m_vec_str_TitleDeep.clear();
    m_map_TitleDeep.clear();
    m_vec_str_Room.clear();
    m_vec_str_SubMonth.clear();
    m_map_SubMonth.clear();
    m_vec_str_Tail.clear();
    m_vec_str_CAF.clear();

    m_vec_str_File.clear();
    m_vec_str_BakupPath.clear();

    VersionRipper();
    MonthRipper();
    SalaryRipper();
    SumRipper();
    TitleRipper();
    TitleDeepRipper();
    TailRipper();
    CAFRipper();
    RoomRipper();
    SubMonthRipper();
    FileRipper();
    BakupPathRipper();
}

/**************************************************/
//   CScriptRipper 析构函数
/**************************************************/
CScriptRipper::~CScriptRipper()
{
    // Nothing To Do
}

/**************************************************/
//   读取&解析 Version
/**************************************************/
void CScriptRipper::VersionRipper()
{
    m_str_Version = m_cls_XMLRipper.GetRootNodeAttr("version");
}

/**************************************************/
//   读取&解析 Month
/**************************************************/
void CScriptRipper::MonthRipper()
{
    m_str_OriginMonth = m_cls_XMLRipper.GetL1NodeAttr_UNI("OriginMonth", "month");
    m_str_CurrentMonth = m_cls_XMLRipper.GetL1NodeAttr_UNI("CurrentMonth", "month");
    //m_str_PreviousMonth = CTool::GeneratePreMonth(m_str_CurrentMonth);

    m_uni_OriginMonth = CTool::GenerateMonthInt(m_str_OriginMonth);
    m_uni_CurrentMonth = CTool::GenerateMonthInt(m_str_CurrentMonth);
    //m_uni_PreviousMonth = CTool::GenerateMonthInt(m_str_PreviousMonth);
}

/**************************************************/
//   读取&解析 MonthSalary
/**************************************************/
void CScriptRipper::SalaryRipper()
{
    string str_MonthSalary = m_cls_XMLRipper.GetL1NodeAttr_UNI("MonthSalary", "value");
    m_uni_MonthSalary = atoi(str_MonthSalary.c_str());
}

/**************************************************/
//   读取&解析 Sum
/**************************************************/
void CScriptRipper::SumRipper()
{
    m_str_OriginSum = m_cls_XMLRipper.GetL2NodeAttr_UNI("FA_SUM", "OriginSum", "content");
    m_str_CurrentSum = m_cls_XMLRipper.GetL2NodeAttr_UNI("FA_SUM", "CurrentSum", "content");
    m_str_CAFSum = m_cls_XMLRipper.GetL2NodeAttr_UNI("FA_SUM", "CAFSum", "content");
}

/**************************************************/
//   读取&解析 Title
/**************************************************/
void CScriptRipper::TitleRipper()
{
    string str_TitleNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_Title", "num");
    m_uni_TitleNum = atoi(str_TitleNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_TitleNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_Title", "TitleItem", i,"item");
        m_vec_str_Title.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 TitleDeep
/**************************************************/
void CScriptRipper::TitleDeepRipper()
{
    string str_TitleDeepNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_TitleDeep", "num");
    m_uni_TitleDeepNum = atoi(str_TitleDeepNum.c_str());

    string str_Temp;
    string str_TempKey;
    for(int i=1; i<=m_uni_TitleDeepNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_TitleDeep", "TitleItem", i,"cmd");
        m_vec_str_TitleDeep.push_back(str_Temp);
        str_TempKey = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_TitleDeep", "TitleItem", i,"key");
        m_map_TitleDeep.insert(make_pair(str_Temp,str_TempKey));
    }
}

/**************************************************/
//   读取&解析 Tail
/**************************************************/
void CScriptRipper::TailRipper()
{
    string str_TailNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_Tail", "num");
    m_uni_TailNum = atoi(str_TailNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_TailNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_Tail", "TailItem", i,"item");
        m_vec_str_Tail.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 CAF   // Consum Availible Fund
/**************************************************/
void CScriptRipper::CAFRipper()
{
    string str_CAFNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_CAF", "num");
    m_uni_CAFNum = atoi(str_CAFNum.c_str());

    string str_CAFIndex = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_CAF", "index");
    m_uni_CAFIndex = atoi(str_CAFIndex.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_CAFNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_CAF", "CAFItem", i,"item");
        m_vec_str_CAF.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 Room
/**************************************************/
void CScriptRipper::RoomRipper()
{
    string str_RoomNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_Room", "num");
    m_uni_RoomNum = atoi(str_RoomNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_RoomNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_Room", "RMItem", i,"item");
        m_vec_str_Room.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 SubMonth
/**************************************************/
void CScriptRipper::SubMonthRipper()
{
    string str_SubMonthNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_SubMonth", "num");
    m_uni_SubMonthNum = atoi(str_SubMonthNum.c_str());

    string str_Temp;
    string str_TempKey;
    for(int i=1; i<=m_uni_SubMonthNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_SubMonth", "SMItem", i, "cmd");
        m_vec_str_SubMonth.push_back(str_Temp);
        str_TempKey = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_SubMonth", "SMItem", i, "key");
        m_map_SubMonth.insert(make_pair(str_Temp,str_TempKey));
    }
}

/**************************************************/
//   读取&解析 File
/**************************************************/
void CScriptRipper::FileRipper()
{
    string str_FileNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_File", "num");
    m_uni_FileNum = atoi(str_FileNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_FileNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_File", "File", i, "file");
        m_vec_str_File.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 BakupPath
/**************************************************/
void CScriptRipper::BakupPathRipper()
{
    string str_BakupPathNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_BakupPath", "num");
    m_uni_BakupPathNum = atoi(str_BakupPathNum.c_str());

    string str_Temp;
    for(int i=1; i<=m_uni_BakupPathNum; i++)
    {
        str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_BakupPath", "BakupPath", i, "path");
        m_vec_str_BakupPath.push_back(str_Temp);
    }
}

/**************************************************/
//   生成 ExMonth
/**************************************************/
void CScriptRipper::ExMonthGenerator()
{
    m_str_PreviousMonth = CTool::GeneratePreMonth(m_str_CurrentMonth);
    m_uni_PreviousMonth = CTool::GenerateMonthInt(m_str_PreviousMonth);
}

/**************************************************/
//   生成 Month Range
//   最大月度支持到 (24-1) 个月
//   支持 单月度 计算
//   2017.03 ~ 2017.03 >>> 可行
/**************************************************/
void CScriptRipper::MonthRangeGenerator()
{
    string str_OriginMonth = m_str_OriginMonth;
    string str_CurrentMonth = m_str_CurrentMonth;

    string str_InsertMonth = str_OriginMonth;
    m_vec_str_Month.push_back(str_OriginMonth);

    if( CTool::CompareString(m_str_OriginMonth, m_str_CurrentMonth) )
    {
        return;
    }
    else
    {
        do{
            str_InsertMonth = CTool::GenerateNextMonth(str_InsertMonth);
            m_vec_str_Month.push_back(str_InsertMonth);

        }while( !CTool::CompareString(str_InsertMonth, m_str_CurrentMonth) );

        return;
    }
}

/**************************************************/
//   判断是否存在 Month Range
/**************************************************/
bool CScriptRipper::IsIncludeMonthRange(const string str_SelMonth)
{
    string str_JudgeMonth(str_SelMonth);

    vector<string>::iterator itr_Month;
    for(itr_Month = m_vec_str_Month.begin(); itr_Month != m_vec_str_Month.end(); itr_Month++)
    {
        if( CTool::CompareString(*itr_Month, str_JudgeMonth) )
        {
            return true;
        }
    }

    return false;
}

/**************************************************/
//   获取 Version
/**************************************************/
string CScriptRipper::GetVersion()
{
    return m_str_Version;
}

/**************************************************/
//   获取 OriginMonth
/**************************************************/
string CScriptRipper::GetOriginMonth()
{
    return m_str_OriginMonth;
}

/**************************************************/
//   获取 CurrentMonth
/**************************************************/
string CScriptRipper::GetCurrentMonth()
{
    return m_str_CurrentMonth;
}

/**************************************************/
//   获取 PreviousMonth
/**************************************************/
string CScriptRipper::GetPreviousMonth()
{
    return m_str_PreviousMonth;
}

/**************************************************/
//   获取 OriginSum
/**************************************************/
string CScriptRipper::GetOriginSum()
{
    return m_str_OriginSum;
}

/**************************************************/
//   获取 CurrentSum
/**************************************************/
string CScriptRipper::GetCurrentSum()
{
    return m_str_CurrentSum;
}

/**************************************************/
//   获取 CAFSum
/**************************************************/
string CScriptRipper::GetCAFSum()
{
    return m_str_CAFSum;
}

/**************************************************/
//   获取 CAFSum
/**************************************************/
int CScriptRipper::GetCAFIndex()
{
    return m_uni_CAFIndex;
}

/**************************************************/
//   获取 SubMonthNum
/**************************************************/
int CScriptRipper::GetSubMonthNum()
{
    return m_uni_SubMonthNum;
}

/**************************************************/
//   获取 MonthSalary
/**************************************************/
unsigned int CScriptRipper::GetMonthSalary()
{
    return m_uni_MonthSalary;
}

/**************************************************/
//   拷贝 Month Range
/**************************************************/
void CScriptRipper::MonthRangeDuplicator(vector<string> &vec_str_DestMonth)
{
    vec_str_DestMonth.clear();

    vector<string>::iterator itr_Month;
    for(itr_Month = m_vec_str_Month.begin(); itr_Month != m_vec_str_Month.end(); itr_Month++)
    {
        vec_str_DestMonth.push_back(*itr_Month);
    }
}

/**************************************************/
//   拷贝 Title
/**************************************************/
void CScriptRipper::TitleDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_Title;
    for(itr_Title = m_vec_str_Title.begin(); itr_Title != m_vec_str_Title.end(); itr_Title++)
    {
        vec_str_Dest.push_back(*itr_Title);
    }
}

/**************************************************/
//   拷贝 TitleDeep
/**************************************************/
void CScriptRipper::TitleDeepDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_TitleDeep;
    for(itr_TitleDeep = m_vec_str_TitleDeep.begin(); itr_TitleDeep != m_vec_str_TitleDeep.end(); itr_TitleDeep++)
    {
        vec_str_Dest.push_back(*itr_TitleDeep);
    }
}

/**************************************************/
//   拷贝 Tail
/**************************************************/
void CScriptRipper::TailDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_Tail;
    for(itr_Tail = m_vec_str_Tail.begin(); itr_Tail != m_vec_str_Tail.end(); itr_Tail++)
    {
        vec_str_Dest.push_back(*itr_Tail);
    }
}

/**************************************************/
//   拷贝 CAF
/**************************************************/
void CScriptRipper::CAFDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_CAF;
    for(itr_CAF = m_vec_str_CAF.begin(); itr_CAF != m_vec_str_CAF.end(); itr_CAF++)
    {
        vec_str_Dest.push_back(*itr_CAF);
    }
}

/**************************************************/
//   拷贝 Room
/**************************************************/
void CScriptRipper::RoomDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_Room;
    for(itr_Room = m_vec_str_Room.begin(); itr_Room != m_vec_str_Room.end(); itr_Room++)
    {
        vec_str_Dest.push_back(*itr_Room);
    }
}

/**************************************************/
//   拷贝 SubMonth
/**************************************************/
void CScriptRipper::SubMonthDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_SubMonth;
    for(itr_SubMonth = m_vec_str_SubMonth.begin(); itr_SubMonth != m_vec_str_SubMonth.end(); itr_SubMonth++)
    {
        vec_str_Dest.push_back(*itr_SubMonth);
    }
}

/**************************************************/
//   拷贝 File
/**************************************************/
void CScriptRipper::FileDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_FilePath;
    for(itr_FilePath = m_vec_str_File.begin(); itr_FilePath != m_vec_str_File.end(); itr_FilePath++)
    {
        vec_str_Dest.push_back(*itr_FilePath);
    }
}

/**************************************************/
//   拷贝 BakupPath
/**************************************************/
void CScriptRipper::BakupPathDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_BakupPath;
    for(itr_BakupPath = m_vec_str_BakupPath.begin(); itr_BakupPath != m_vec_str_BakupPath.end(); itr_BakupPath++)
    {
        vec_str_Dest.push_back(*itr_BakupPath);
    }
}

string CScriptRipper::TitleTranslater(const string str_TitleCMD)
{
    string str_TranslateKey("");

    map<string, string>::iterator itr_Title;
    itr_Title = m_map_TitleDeep.find(str_TitleCMD);
    if(itr_Title != m_map_TitleDeep.end())
        str_TranslateKey = itr_Title->second;
    else
        str_TranslateKey = "ERROR";

    return str_TranslateKey;
}

string CScriptRipper::SubMonthTranslater(const string str_SubMonthCMD)
{
    string str_TranslateKey("");

    map<string, string>::iterator itr_SubMonth;
    itr_SubMonth = m_map_SubMonth.find(str_SubMonthCMD);
    if(itr_SubMonth != m_map_SubMonth.end())
        str_TranslateKey = itr_SubMonth->second;
    else
        str_TranslateKey = "ERROR";

    return str_TranslateKey;
}

/**************************************************/
//   修改 当前Month
/**************************************************/
void CScriptRipper::ModifyCurrentMonth(const string str_SelMonth)
{
    m_cls_XMLRipper.SetL1NodeAttr_UNI("CurrentMonth", "month", str_SelMonth);
    m_cls_XMLRipper.XMLSaver();

    m_str_CurrentMonth = str_SelMonth;
    m_str_PreviousMonth = CTool::GeneratePreMonth(m_str_CurrentMonth);
}

//------------------------------//
//   River flows in summer
//------------------------------//
