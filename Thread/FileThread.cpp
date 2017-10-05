
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <regex>
#include "FileThread.h"

using namespace std;

string pattern_end_t = "^---$";
regex RE_end_t(pattern_end_t);

CFileThread::CFileThread()
{
    //m_str_FilePath
    //m_str_FileName
    m_bol_ModFlag = false;
    m_int_LineNum = 0;
    m_vec_Line.push_back("LINE 0 BY SUMMER");
}

CFileThread::CFileThread(const char *cha_FileName)
{
    m_bol_ModFlag = false;
    m_int_LineNum = 0;
    m_vec_Line.push_back("LINE 0 BY SUMMER");

    char cha_buffer[MAX_LINE_CHAR];
    
    ifstream ifile(cha_FileName);

    if(ifile.is_open() == 0)
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

CFileThread::~CFileThread()
{
    // Do Nothing
}

int CFileThread::GetLineNum()
{
    return m_int_LineNum;
}

string CFileThread::GetLine(const int int_LineIndex)
{
    return m_vec_Line.at(int_LineIndex);
}

bool CFileThread::GetModFlag()
{
    return m_bol_ModFlag;
}

int CFileThread::InsertLine(const int int_LineIndex, const string str_LineContent)
{
    vector<string>::iterator iter;
    iter = m_vec_Line.begin();
    iter += int_LineIndex;

    m_vec_Line.insert(iter, str_LineContent);
    m_int_LineNum++;
    m_bol_ModFlag = true;

    return 0;
}

int CFileThread::ModifyLine(const int int_LineIndex, const string str_LineContent)
{
    vector<string>::iterator iter;
    iter = m_vec_Line.begin();
    iter += int_LineIndex;

    m_vec_Line.erase(iter);
    m_vec_Line.insert(iter, str_LineContent);
    m_bol_ModFlag = true;

    return 0;
}

int CFileThread::DeleteLine(const int int_LineIndex)
{
    vector<string>::iterator iter;
    iter = m_vec_Line.begin();
    iter += int_LineIndex;

    m_vec_Line.erase(iter);
    m_int_LineNum--;
    m_bol_ModFlag = true;

    return 0;
}

int CFileThread::FileWriter(const char *cha_FileName)
{
    ofstream ofile(cha_FileName);
    
    if(!ofile.is_open())
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>         Write File Error         <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }
        
    for(int i = 1; i <= m_int_LineNum; i++)
    {
        ofile << m_vec_Line.at(i).c_str() << endl;
            
        if( regex_match(m_vec_Line.at(i), RE_end_t) )
        {
            break;
        }
    }

    ofile.close();
        
    return 0;
}

void CFileThread::Run()
{  
    pthread_mutex_lock(&mutex);
	
	while(m_bol_ModFlag == false)
	{
        cout << "before pthread_cond_wait()" << endl;
        pthread_cond_wait(&cond, &mutex);
        cout << "after pthread_cond_wait()" << endl;

        FileWriter("./FA_TVT_VeXT.md");
        cout << "Call FileWriter()" << endl;
        m_bol_ModFlag = false;

        continue;
    }
    
	pthread_mutex_unlock(&mutex);
}

//------------------------------//
//   River flows in summer
//------------------------------//
