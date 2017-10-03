
//------------------------------//
//   Coded by 番茄_summer
//   @20171003
//   @summer studio
//
//   River flows in summer
//------------------------------//

#include "FileOPer.h"

using namespace std;

CFileOper::CFileOper()
{
    //m_str_FilePath
    //m_str_FileName
    m_bol_ModFlag = false;
    m_int_LineNum = 0;
    m_vec_Line.push_back("LINE 0 BY SUMMER");
}

CFileOper::CFileOper(const char *cha_FileName)
{
    m_bol_ModFlag = false;
    m_int_LineNum = 0;
    m_vec_Line.push_back("LINE 0 BY SUMMER");

    char cha_buffer[MAX_LINE_CHAR];
    
    ifstream ifile(cha_FileName);

    if(ifile.is_open() != 0)
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>          Read File Error         <<<" << endl;
        cout << "----------------------------------------" << endl;
    }

    while(!ifile.eof())
    {
        ifile.getline(cha_buffer, MAX_LINE_CHAR);
        m_vec_Line.push_back(cha_buffer);
        m_int_LineNum++;
    }
    
    ifile.close();
}

CFileOper::~CFileOper()
{
    // do nothing
}

int CFileOper::GetLineNum()
{
    return m_int_LineNum;
}

string CFileOper::GetLine(const int int_LineIndex)
{
    return m_vec_Line.at(int_LineIndex);
}
