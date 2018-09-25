#ifndef VIDEO_SERVICE_HEAD_FILE
#define VIDEO_SERVICE_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//平台头文件
#include "Template.h"
#include "GlobalDef.h"

//消息定义
#include "CMD_Video.h"

//组件头文件
#include "IUnknownEx.h"
#include "GameFrame.h"
#include "SkinControls.h"

//////////////////////////////////////////////////////////////////////////
//公共宏定义

//导出定义
#ifndef VIDEO_SERVICE_CLASS
	#ifdef  VIDEO_SERVICE_DLL
		#define VIDEO_SERVICE_CLASS _declspec(dllexport)
	#else
		#define VIDEO_SERVICE_CLASS _declspec(dllimport)
	#endif
#endif

//模块定义
#ifndef _DEBUG
	#define VIDEO_SERVICE_DLL_NAME	TEXT("VideoService.dll")			//组件 DLL 名字
#else
	#define VIDEO_SERVICE_DLL_NAME	TEXT("VideoServiceD.dll")			//组件 DLL 名字
#endif

//////////////////////////////////////////////////////////////////////////
//结构定义

//连接信息
struct tagVideoNetwordInfo
{
	WORD							wNatPort;							//网络端口
	WORD							wLocalPort;							//网络端口
	DWORD							dwNatAddr;							//网络地址
	DWORD							dwLocalAddr;						//本地地址
};

//////////////////////////////////////////////////////////////////////////
//全局定义

//赠送结构
struct tagGiftResInfo
{
	WORD							wGiftID;							//赠送索引
	CHAR							szShowMsg[256];						//显示信息
};

//赠送信息
tagGiftResInfo	const g_GiftResInfo[GIFT_COUNT]= 
{
	{ FLOWER_1, TEXT("[ %s ] 给 [ %s ] 赠送了红玫瑰%ld，[ %s ] 魅力+1，[ %s ] 魅力+1") },
	{ FLOWER_2, TEXT("[ %s ] 给 [ %s ] 赠送了小玫瑰%ld，[ %s ] 魅力+2，[ %s ] 魅力+2")},
	{ FLOWER_3, TEXT("[ %s ] 给 [ %s ] 赠送了百合%ld，[ %s ] 魅力+2，[ %s ] 魅力+2")}
};

//////////////////////////////////////////////////////////////////////////
//导出类头文件

#include "VideoServiceControl.h"

//////////////////////////////////////////////////////////////////////////

#endif
