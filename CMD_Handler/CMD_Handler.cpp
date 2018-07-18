
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include "CMD_Handler.h"

#include "./../FA_Layer/FAitfX.h"
#include "./../AS_Layer/ASitfX.h"


/**************************************************/
//   CMD_MAP()宏
/**************************************************/
X_BEGIN_CMD_MAP(CCMDHandler)
	//X_ON_CMD_TYPE(X_CMD_TYPE_TEST, "", OnCmdTest)
X_END_CMD_MAP()

/**************************************************/
//   CMD_LOOP()宏
/**************************************************/
CMD_LOOP(CCMDHandler)

/**************************************************/
//   CCMDHandler 构造函数
/**************************************************/
CCMDHandler::CCMDHandler()
{
    // Nothing To Do
}

/**************************************************/
//   CCMDHandler 析构函数
/**************************************************/
CCMDHandler::~CCMDHandler()
{
    // Nothing To Do
}

void CCMDHandler::OnCmdTest(CMD_Packet cls_CMD)
{
	cout << "CMD_MAP() test success" << endl;
}

//------------------------------//
//   River flows in summer
//------------------------------//
