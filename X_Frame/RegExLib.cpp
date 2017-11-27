
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "RegExLib.h"

using namespace std;


string pattern_fullfilename = "^(.+/)(.+\\.md)$";   // tips 番茄@20171127 - "贪心"匹配模式，匹配尽可能长的字符串
regex RE_fullfilename(pattern_fullfilename);

string pattern_eof = "^---$";
regex RE_eof(pattern_eof);


//------------------------------//
//   River flows in summer
//------------------------------//
