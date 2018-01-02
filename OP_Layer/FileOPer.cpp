
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "FileOPer.h"

#include "./../X_Frame/DefLib.h"
#include "./../X_Frame/RegExLib.h"

using namespace std;


extern regex RE_fullfilename;
extern regex RE_eof;

CFileOPer::CFileOPer()
{
    m_str_FilePath = "";
    m_str_FileName = "";
    m_bol_ModFlag = false;
    m_int_LineNum = 0;
    m_vec_Line.push_back("LINE 0 BY SUMMER");
}

CFileOPer::CFileOPer(const char *cha_FullFileName)
{
    FullFileNameParser(cha_FullFileName);

    m_bol_ModFlag = false;
    
    FileReader();
}

CFileOPer::~CFileOPer()
{
    // Do Nothing
}

void CFileOPer::FullFileNameParser(const char *cha_FullFileName)
{
    smatch str_Match;
    string str_FullFileName = cha_FullFileName;

    if( regex_match(str_FullFileName, str_Match, RE_fullfilename) )
    {
        m_str_FilePath = str_Match[1];
        m_str_FileName = str_Match[2];
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!      FileName Format Error       !!!" << endl;
        cout << "----------------------------------------" << endl;
    }
}

string CFileOPer::GetLine(const int int_LineIndex)
{
    return m_vec_Line.at(int_LineIndex);
}

int CFileOPer::InsertLine(const int int_LineIndex, const string str_LineContent)
{
    vector<string>::iterator iter;
    iter = m_vec_Line.begin();
    iter += int_LineIndex;

    m_vec_Line.insert(iter, str_LineContent);
    m_int_LineNum++;
    m_bol_ModFlag = true;

    return 0;
}

int CFileOPer::ModifyLine(const int int_LineIndex, const string str_LineContent)
{
    vector<string>::iterator iter;
    iter = m_vec_Line.begin();
    iter += int_LineIndex;

    m_vec_Line.erase(iter);
    m_vec_Line.insert(iter, str_LineContent);
    m_bol_ModFlag = true;

    return 0;
}

int CFileOPer::DeleteLine(const int int_LineIndex)
{
    vector<string>::iterator iter;
    iter = m_vec_Line.begin();
    iter += int_LineIndex;

    m_vec_Line.erase(iter);
    m_int_LineNum--;
    m_bol_ModFlag = true;

    return 0;
}

string CFileOPer::GetFilePath()
{
    return m_str_FilePath;
}

string CFileOPer::GetFileName()
{
    return m_str_FileName;
}

int CFileOPer::GetLineNum()
{
    return m_int_LineNum;
}

bool CFileOPer::GetModFlag()
{
    return m_bol_ModFlag;
}

int CFileOPer::FileReader()
{
    // tips 番茄@20180102 - m_int_LineNum需在Read操作前清零
    m_int_LineNum = 0;
    m_vec_Line.clear();
    m_vec_Line.push_back("LINE 0 BY SUMMER");

    string str_FullFileName = m_str_FilePath + m_str_FileName;
    // tips 番茄@20171127 - c_str()返回常量char字符串，不能赋值给变量指针
    //char *cha_FullFileName = str_FullFileName.c_str();
    char *cha_FullFileName = new char[MAX_FULLFILENAME];
    strcpy(cha_FullFileName, str_FullFileName.c_str());

    ifstream ifile(cha_FullFileName);

    if(ifile.is_open() == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!          Read File Error         !!!" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }

    char cha_buffer[MAX_LINE_CHAR];

    while(!ifile.eof())
    {
        ifile.getline(cha_buffer, MAX_LINE_CHAR);
        m_vec_Line.push_back(cha_buffer);
        m_int_LineNum++;
    }
    
    ifile.close();

    delete []cha_FullFileName;

    return 0;
}

int CFileOPer::FileReader(const char *cha_FullFileName)
{
    m_int_LineNum = 0;
    m_vec_Line.clear();
    m_vec_Line.push_back("LINE 0 BY SUMMER");

    ifstream ifile(cha_FullFileName);

    if(ifile.is_open() == 0)
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!          Read File Error         !!!" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }

    char cha_buffer[MAX_LINE_CHAR];

    while(!ifile.eof())
    {
        ifile.getline(cha_buffer, MAX_LINE_CHAR);
        m_vec_Line.push_back(cha_buffer);
        m_int_LineNum++;
    }
    
    ifile.close();

    return 0;
}

int CFileOPer::FileWriter()
{
    string str_FullFileName = m_str_FilePath + m_str_FileName;
    char *cha_FullFileName = new char[MAX_FULLFILENAME];
    strcpy(cha_FullFileName, str_FullFileName.c_str());

    ofstream ofile(cha_FullFileName);
    
    if(!ofile.is_open())
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!         Write File Error         !!!" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }
        
    for(int i = 1; i <= m_int_LineNum; i++)
    {
        ofile << m_vec_Line.at(i).c_str() << endl;
            
        if( regex_match(m_vec_Line.at(i), RE_eof) )
        {
            break;
        }
    }

    ofile.close();

    delete []cha_FullFileName;
        
    return 0;
}

int CFileOPer::FileWriter(const char *cha_FullFileName)
{
    ofstream ofile(cha_FullFileName);
    
    if(!ofile.is_open())
    {
        cout << "----------------------------------------" << endl;
        cout << "!!!         Write File Error         !!!" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }
        
    for(int i = 1; i <= m_int_LineNum; i++)
    {
        ofile << m_vec_Line.at(i).c_str() << endl;
        
        if( regex_match(m_vec_Line.at(i), RE_eof) )
        {
            break;
        }
    }

    ofile.close();
        
    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
