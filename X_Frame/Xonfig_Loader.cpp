
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "Xonfig_Loader.h"

using namespace std;

static const char *emptyString = "";


/**************************************************/
//   CXonfigLoader 构造函数
/**************************************************/
CXonfigLoader::CXonfigLoader(const char *cha_xmlPath):
m_cls_Xonfig(cha_xmlPath)
{
    m_str_ScriptFilePath = cha_xmlPath;

    m_str_Version = "";

    m_str_OriginSum = "";
    m_str_CurrentSum = "";
    //m_str_CAFSum = "";   // tag summer@20210805 - why comments ?

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
//   CXonfigLoader 析构函数
/**************************************************/
CXonfigLoader::~CXonfigLoader()
{
    // Nothing To Do
}

/**************************************************/
//   读取&解析 Version
/**************************************************/
void CXonfigLoader::VersionRipper()
{
    string emptyString = "";

    m_str_Version = m_cls_Xonfig.Read("FA_Auto_Version", emptyString);
}

/**************************************************/
//   读取&解析 Month
/**************************************************/
void CXonfigLoader::MonthRipper()
{
    string emptyString = "";

    m_str_OriginMonth = m_cls_Xonfig.Read("OriginMonth", emptyString);
    m_str_CurrentMonth = m_cls_Xonfig.Read("CurrentMonth", emptyString);

    m_uni_OriginMonth = CTool::GenerateMonthInt(m_str_OriginMonth);
    m_uni_CurrentMonth = CTool::GenerateMonthInt(m_str_CurrentMonth);
}

/**************************************************/
//   读取&解析 MonthSalary
/**************************************************/
void CXonfigLoader::SalaryRipper()
{
    m_uni_MonthSalary = m_cls_Xonfig.Read("MonthSalary", 0);
}

/**************************************************/
//   读取&解析 Sum
/**************************************************/
void CXonfigLoader::SumRipper()
{
    //m_str_OriginSum = m_cls_XMLRipper.GetL2NodeAttr_UNI("FA_SUM", "OriginSum", "content");
    //m_str_CurrentSum = m_cls_XMLRipper.GetL2NodeAttr_UNI("FA_SUM", "CurrentSum", "content");
    //m_str_CAFSum = m_cls_XMLRipper.GetL2NodeAttr_UNI("FA_SUM", "CAFSum", "content");
}

/**************************************************/
//   读取&解析 Title
/**************************************************/
void CXonfigLoader::TitleRipper()
{
    m_uni_TitleCount = m_cls_Xonfig.Read("TitleCount", 0);

    string str_Temp;
    int index = 1;
    char nameLabel[64];
    while(index <= m_uni_TitleCount)
    {
        memset(&nameLabel, 0, sizeof(nameLabel));
        sprintf(nameLabel, "TitleItem_%d", index++);
        str_Temp = emptyString;
        str_Temp = m_cls_Xonfig.Read(nameLabel, str_Temp);
        m_vec_str_Title.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 TitleDeep
/**************************************************/
void CXonfigLoader::TitleDeepRipper()
{
    m_uni_TitleDeepCount = m_cls_Xonfig.Read("TitleDeepCount", 0);

    string str_TempCMD;
    string str_TempKey;
    int index = 1;
    char nameLabel[64];
    while(index <= m_uni_TitleDeepCount)
    {
        memset(&nameLabel, 0, sizeof(nameLabel));
        sprintf(nameLabel, "TitleDeepCMD_%d", index);
        str_TempCMD = emptyString;
        str_TempCMD = m_cls_Xonfig.Read(nameLabel, str_TempCMD);

        memset(&nameLabel, 0, sizeof(nameLabel));
        sprintf(nameLabel, "TitleDeepKey_%d", index);
        str_TempKey = emptyString;
        str_TempKey = m_cls_Xonfig.Read(nameLabel, str_TempKey);

        m_vec_str_TitleDeep.push_back(str_TempCMD);
        m_map_TitleDeep.insert(make_pair(str_TempCMD, str_TempKey));

        index++;
    }
}

/**************************************************/
//   读取&解析 Tail
/**************************************************/
void CXonfigLoader::TailRipper()
{
    //string str_TailNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_Tail", "num");
    //m_uni_TailNum = atoi(str_TailNum.c_str());

    //string str_Temp;
    //for(int i=1; i<=m_uni_TailNum; i++)
    //{
    //    str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_Tail", "TailItem", i,"item");
    //    m_vec_str_Tail.push_back(str_Temp);
    //}
}

/**************************************************/
//   读取&解析 CAF   // Consum Availible Fund
/**************************************************/
void CXonfigLoader::CAFRipper()
{
    //string str_CAFNum = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_CAF", "num");
    //m_uni_CAFNum = atoi(str_CAFNum.c_str());

    //string str_CAFIndex = m_cls_XMLRipper.GetL1NodeAttr_UNI("FA_CAF", "index");
    //m_uni_CAFIndex = atoi(str_CAFIndex.c_str());

    //string str_Temp;
    //for(int i=1; i<=m_uni_CAFNum; i++)
    //{
    //    str_Temp = m_cls_XMLRipper.GetL2NodeAttr_IDX("FA_CAF", "CAFItem", i,"item");
    //    m_vec_str_CAF.push_back(str_Temp);
    //}
}

/**************************************************/
//   读取&解析 Room
/**************************************************/
void CXonfigLoader::RoomRipper()
{
    m_uni_RoomCount = m_cls_Xonfig.Read("RoomCount", 0);

    string str_Temp;
    int index = 1;
    char nameLabel[64];
    while(index <= m_uni_RoomCount)
    {
        memset(&nameLabel, 0, sizeof(nameLabel));
        sprintf(nameLabel, "RoomItem_%d", index++);
        str_Temp = emptyString;
        str_Temp = m_cls_Xonfig.Read(nameLabel, str_Temp);
        m_vec_str_Room.push_back(str_Temp);
    }
}

/**************************************************/
//   读取&解析 SubMonth
/**************************************************/
void CXonfigLoader::SubMonthRipper()
{
    m_uni_SubMonthCount = m_cls_Xonfig.Read("SubMonthCount", 0);

    string str_TempCMD;
    string str_TempKey;
    int index = 1;
    char nameLabel[64];
    while( index <= m_uni_SubMonthCount )
    {
        memset(&nameLabel, 0, sizeof(nameLabel));
        sprintf(nameLabel, "SubMonthCMD_%d", index);
        str_TempCMD = emptyString;
        str_TempCMD = m_cls_Xonfig.Read(nameLabel, str_TempCMD);

        memset(&nameLabel, 0, sizeof(nameLabel));
        sprintf(nameLabel, "SubMonthKey_%d", index);
        str_TempKey = emptyString;
        str_TempKey = m_cls_Xonfig.Read(nameLabel, str_TempKey);

        m_vec_str_SubMonth.push_back(str_TempCMD);
        m_map_SubMonth.insert(make_pair(str_TempCMD, str_TempKey));

        index++;
    }
}

/**************************************************/
//   读取&解析 File
/**************************************************/
void CXonfigLoader::FileRipper()
{
    m_uni_FileCount = m_cls_Xonfig.Read("FileCount", 0);

    string str_Temp;
    char nameLabel[64];
    int index = 1;
    while(index <= m_uni_TitleDeepCount)
    {
        memset(&nameLabel, 0, sizeof(nameLabel));
        sprintf(nameLabel, "File_%d", index);
        str_Temp = emptyString;
        str_Temp = m_cls_Xonfig.Read(nameLabel, str_Temp);
        m_vec_str_File.push_back(str_Temp);

        index++;
    }
}

/**************************************************/
//   读取&解析 BakupPath
/**************************************************/
void CXonfigLoader::BakupPathRipper()
{
    m_uni_BakupPathCount = m_cls_Xonfig.Read("BakupPathCount", 0);

    string str_Temp;
    char nameLabel[64];
    int index = 1;
    while(index <= m_uni_BakupPathCount)
    {
        memset(&nameLabel, 0, sizeof(nameLabel));
        sprintf(nameLabel, "BakupPath_%d", index);
        str_Temp = emptyString;
        str_Temp = m_cls_Xonfig.Read(nameLabel, str_Temp);
        m_vec_str_BakupPath.push_back(str_Temp);

        index++;
    }
}

/**************************************************/
//   生成 ExMonth
/**************************************************/
void CXonfigLoader::ExMonthGenerator()
{
    m_str_PreviousMonth = CTool::GeneratePreMonth(m_str_CurrentMonth);
    m_uni_PreviousMonth = CTool::GenerateMonthInt(m_str_PreviousMonth);
}

/**************************************************/
//   生成 Month Range
//   支持 单月度 e.g. [2017.03 ~ 2017.03]
//   支持 最大 (24-1) 个月
/**************************************************/
void CXonfigLoader::MonthRangeGenerator()
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
bool CXonfigLoader::IsIncludeMonthRange(const string str_SelMonth)
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
string CXonfigLoader::GetVersion()
{
    return m_str_Version;
}

/**************************************************/
//   获取 OriginMonth
/**************************************************/
string CXonfigLoader::GetOriginMonth()
{
    return m_str_OriginMonth;
}

/**************************************************/
//   获取 CurrentMonth
/**************************************************/
string CXonfigLoader::GetCurrentMonth()
{
    return m_str_CurrentMonth;
}

/**************************************************/
//   获取 PreviousMonth
/**************************************************/
string CXonfigLoader::GetPreviousMonth()
{
    return m_str_PreviousMonth;
}

/**************************************************/
//   获取 OriginSum
/**************************************************/
string CXonfigLoader::GetOriginSum()
{
    // return m_str_OriginSum;
    return " ";
}

/**************************************************/
//   获取 CurrentSum
/**************************************************/
string CXonfigLoader::GetCurrentSum()
{
    // return m_str_CurrentSum;
    return " ";
}

/**************************************************/
//   获取 CAFSum
/**************************************************/
string CXonfigLoader::GetCAFSum()
{
    // return m_str_CAFSum;
    return " ";
}

/**************************************************/
//   获取 CAFSum
/**************************************************/
int CXonfigLoader::GetCAFIndex()
{
    // return m_uni_CAFIndex;
    return 0;
}

/**************************************************/
//   获取 SubMonthNum
/**************************************************/
int CXonfigLoader::GetSubMonthCount()
{
    return m_uni_SubMonthCount;
}

/**************************************************/
//   获取 MonthSalary
/**************************************************/
unsigned int CXonfigLoader::GetMonthSalary()
{
    return m_uni_MonthSalary;
}

/**************************************************/
//   拷贝 Month Range
/**************************************************/
void CXonfigLoader::MonthRangeDuplicator(vector<string> &vec_str_DestMonth)
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
void CXonfigLoader::TitleDuplicator(vector<string> &vec_str_Dest)
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
void CXonfigLoader::TitleDeepDuplicator(vector<string> &vec_str_Dest)
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
void CXonfigLoader::TailDuplicator(vector<string> &vec_str_Dest)
{
    // vec_str_Dest.clear();

    // vector<string>::iterator itr_Tail;
    // for(itr_Tail = m_vec_str_Tail.begin(); itr_Tail != m_vec_str_Tail.end(); itr_Tail++)
    // {
    //     vec_str_Dest.push_back(*itr_Tail);
    // }
}

/**************************************************/
//   拷贝 CAF
/**************************************************/
void CXonfigLoader::CAFDuplicator(vector<string> &vec_str_Dest)
{
    // vec_str_Dest.clear();

    // vector<string>::iterator itr_CAF;
    // for(itr_CAF = m_vec_str_CAF.begin(); itr_CAF != m_vec_str_CAF.end(); itr_CAF++)
    // {
    //     vec_str_Dest.push_back(*itr_CAF);
    // }
}

/**************************************************/
//   拷贝 Room
/**************************************************/
void CXonfigLoader::RoomDuplicator(vector<string> &vec_str_Dest)
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
void CXonfigLoader::SubMonthDuplicator(vector<string> &vec_str_Dest)
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
void CXonfigLoader::FileDuplicator(vector<string> &vec_str_Dest)
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
void CXonfigLoader::BakupPathDuplicator(vector<string> &vec_str_Dest)
{
    vec_str_Dest.clear();

    vector<string>::iterator itr_BakupPath;
    for(itr_BakupPath = m_vec_str_BakupPath.begin(); itr_BakupPath != m_vec_str_BakupPath.end(); itr_BakupPath++)
    {
        vec_str_Dest.push_back(*itr_BakupPath);
    }
}

string CXonfigLoader::TitleTranslater(const string str_TitleCMD)
{
    // string str_TranslateKey("");

    // map<string, string>::iterator itr_Title;
    // itr_Title = m_map_TitleDeep.find(str_TitleCMD);
    // if(itr_Title != m_map_TitleDeep.end())
    //     str_TranslateKey = itr_Title->second;
    // else
    //     str_TranslateKey = "ERROR";

    // return str_TranslateKey;
    return " ";
}

string CXonfigLoader::SubMonthTranslater(const string str_SubMonthCMD)
{
    // string str_TranslateKey("");

    // map<string, string>::iterator itr_SubMonth;
    // itr_SubMonth = m_map_SubMonth.find(str_SubMonthCMD);
    // if(itr_SubMonth != m_map_SubMonth.end())
    //     str_TranslateKey = itr_SubMonth->second;
    // else
    //     str_TranslateKey = "ERROR";

    // return str_TranslateKey;
    return " ";
}

/**************************************************/
//   修改 当前Month
/**************************************************/
void CXonfigLoader::ModifyCurrentMonth(const string str_SelMonth)
{
    m_str_CurrentMonth = str_SelMonth;
    m_str_PreviousMonth = CTool::GeneratePreMonth(m_str_CurrentMonth);

    m_cls_Xonfig.Modify("CurrentMonth", str_SelMonth);
}

//------------------------------//
//   River flows in summer
//------------------------------//
