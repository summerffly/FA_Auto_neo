
//------------------------------//
//   Coded by 番茄_summer
//   @20171002
//   @summer studio
//
//   River flows in summer
//------------------------------//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#define MAX_LINE_CHAR   128     // 每行最大字符数

using namespace std;

class CFileOper
{
public:
    CFileOper();
    CFileOper(const char *cha_FileName);
    ~CFileOper();
    int GetLineNum();
    string GetLine(const int int_LineIndex);
private:
    string m_str_FilePath;   // .md文件路径
    string m_str_FileName;   // .md文件名称
    bool m_bol_ModFlag;   // 文件修改标识
    int m_int_LineNum;   // 行数
    vector<string> m_vec_Line;   // 行内容
};
