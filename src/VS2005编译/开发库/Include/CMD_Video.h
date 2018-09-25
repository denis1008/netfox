#ifndef CMD_VIDEO_HEAD_FILE
#define CMD_VIDEO_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

#define MDM_GF_VIDEO				200									//视频通道

#define SUB_GF_C_VIDEO_CONFIG		1									//视频配置
#define SUB_GF_C_VIDEO_CLOSE		2									//关闭视频
#define SUB_GF_C_VIDEO_OPEN			3									//打开视频

#define SUB_GF_S_VIDEO_CONFIG		100									//视频配置
#define SUB_GF_S_VIDEO_CLOSE		101									//关闭视频
#define SUB_GF_S_VIDEO_OPEN			102									//打开视频

//////////////////////////////////////////////////////////////////////////

//视频配置
struct CMD_C_VideoConfig
{
	//连接信息
	WORD							wNatPort;							//网络端口
	WORD							wLocalPort;							//网络端口
	DWORD							dwNatAddr;							//网络地址
	DWORD							dwLocalAddr;						//本地地址

	//用户标识
	DWORD							dwRemoteUserID;						//远程用户
};

//视频配置
struct CMD_S_VideoConfig
{
	//连接信息
	WORD							wNatPort;							//网络端口
	WORD							wLocalPort;							//网络端口
	DWORD							dwNatAddr;							//网络地址
	DWORD							dwLocalAddr;						//本地地址

	//用户标识
	DWORD							dwLocalUserID;						//本地用户
};

//关闭视频
struct CMD_S_VideoClose
{
	WORD							wCloseUser;							//关闭玩家
};

//打开视频
struct CMD_S_VideoOpen
{
	WORD							wOpenUser;							//打开玩家
};

////////////////////////////////////////////////////////////////////////////////////////////////
//礼物数目
#define GIFT_COUNT					3									//礼物数目

//鲜花定义
#define FLOWER_1					0									//红玫瑰
#define FLOWER_2					1									//小玫瑰
#define FLOWER_3					2									//百合花

//////////////////////////////////////////////////////////////////////////
//鲜花结构
struct tagGiftInfo
{
	TCHAR							szName[128];						//鲜花名称
	LONG							lValue;								//鲜花价值
};

//鲜花定义
tagGiftInfo const g_GiftInfo[GIFT_COUNT]=
{
	{TEXT("红玫瑰"),1000},
	{TEXT("小玫瑰"),100},
	{TEXT("百合"),100},
};

#endif