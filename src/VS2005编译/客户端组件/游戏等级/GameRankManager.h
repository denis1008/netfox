
#pragma once

#include "Interface.h"


//游戏等级管理
class CGameRankManager : public IGameRankManager
{
	//函数定义
public:
	CGameRankManager(void);
	virtual ~CGameRankManager(void);

	//基础接口
public:
	//释放对象
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//是否有效
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CGameRankManager))?true:false; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//组件接口
public:
	//获取等级
	virtual LPCTSTR __cdecl GetGameRank(WORD wKindID, LONG lScore, WORD wGameGenre);

	//金币游戏
	static LPCTSTR __cdecl GetSHOWHANDRank(LONG lScore);			//梭哈
	static LPCTSTR __cdecl GetHKFIVECARDRank(LONG lScore);			//港式五张牌

	//牌类
	static LPCTSTR __cdecl GetLANDRank(LONG lScore);			    //斗地主
	static LPCTSTR __cdecl GetLANDEXRank(LONG lScore);				//两副斗地主
	static LPCTSTR __cdecl GetLANDCRAZYRank(LONG lScore);			//疯狂斗地主
	static LPCTSTR __cdecl GetUPGRADERank(LONG lScore);				//两副升级
	static LPCTSTR __cdecl GetUPGRADEEXRank(LONG lScore);			//四副升级
	static LPCTSTR __cdecl GetHOERank(LONG lScore);					//锄大地
	static LPCTSTR __cdecl GetUNCOVERPIGRank(LONG lScore);			//拱猪
	static LPCTSTR __cdecl GetTRENCHRank(LONG lScore);				//挖坑
//	static LPCTSTR __cdecl GetRUNFASTRank(LONG lScore);				//跑得快	
	static LPCTSTR __cdecl GetSHUANGKOURank(LONG lScore);			//双扣
//	static LPCTSTR __cdecl GetSHUANGKOURank(LONG lScore);			//百变双扣
//	static LPCTSTR __cdecl GetSHUANGKOURank(LONG lScore);			//千变双扣
	static LPCTSTR __cdecl GetGUANPAIRank(LONG lScore);				//关牌
//	static LPCTSTR __cdecl GetSANDAYIRank(LONG lScore);				//三打一
//	static LPCTSTR __cdecl GetCATCHPOCKRank(LONG lScore);			//捉老麻子
//	static LPCTSTR __cdecl GetPAOHUZIRank(LONG lScore);				//跑胡子
	static LPCTSTR __cdecl GetREDTENRank(LONG lScore);				//丹东红十
	static LPCTSTR __cdecl GetLIGUNRank(LONG lScore);				//朝阳立棍
	static LPCTSTR __cdecl GetWULANGTUIRank(LONG lScore);			//丹东五狼脚
//	static LPCTSTR __cdecl Get510KRank(LONG lScore);				//福州 510K
	static LPCTSTR __cdecl GetBLACKSEVENRank(LONG lScore);			//河南黑七
//	static LPCTSTR __cdecl GetQINGDUNRank(LONG lScore);				//清墩	
	static LPCTSTR __cdecl GetBIAOFENRank(LONG lScore);				//广西标分
	static LPCTSTR __cdecl GetREDFIVERank(LONG lScore);				//冲击红五
//	static LPCTSTR __cdecl GetJIAOERRank(LONG lScore);				//潮汕叫二
//	static LPCTSTR __cdecl GetUPGRADECSRank(LONG lScore);			//潮汕升级
//	static LPCTSTR __cdecl GetGUAILURank(LONG lScore);				//怪路	
//	static LPCTSTR __cdecl GetNIUGUIRank(LONG lScore);				//牛鬼
//	static LPCTSTR __cdecl GetLIANGFUTOURank(LONG lScore);			//两副头
	static LPCTSTR __cdecl GetHONGWURank(LONG lScore);				//红五三打一(两副)
//	static LPCTSTR __cdecl GetHONGWUEXRank(LONG lScore);			//红五三打一(三副)
	//棋类
	static LPCTSTR __cdecl GetCHINACHESSRank(LONG lScore);			//象棋
//	static LPCTSTR __cdecl GetCHESSRank(LONG lScore);				//国际象棋
	static LPCTSTR __cdecl GetFOURENSIGNRank(LONG lScore);			//四国军棋
	static LPCTSTR __cdecl GetGOBANGRank(LONG lScore);				//五子棋
	static LPCTSTR __cdecl GetDOUSHOUQIRank(LONG lScore);			//斗兽棋
	static LPCTSTR __cdecl GetWEIQIRank(LONG lScore);				//围棋
	
	//麻将类
	static LPCTSTR __cdecl GetSPARROWRank(LONG lScore);			    //麻将模版
/*	static LPCTSTR __cdecl GetSPARROWGDRank(LONG lScore);			//广东麻将
	static LPCTSTR __cdecl GetSPARROWJSRank(LONG lScore);			//江苏麻将
	static LPCTSTR __cdecl GetSPARROWCSRank(LONG lScore);			//长沙麻将
	static LPCTSTR __cdecl GetSPARROWHYRank(LONG lScore);			//衡阳麻将
	static LPCTSTR __cdecl GetSPARROWZJRank(LONG lScore);			//浙江麻将
	static LPCTSTR __cdecl GetSPARROWCJRank(LONG lScore);			//冲击麻将
	static LPCTSTR __cdecl GetSPARROWXSRank(LONG lScore);			//象山麻将
	static LPCTSTR __cdecl GetSPARROWFZRank(LONG lScore);			//福州麻将*/
	static LPCTSTR __cdecl GetSPARROWXYRank(LONG lScore);			//信阳麻将
//	static LPCTSTR __cdecl GetSPARROWGXRank(LONG lScore);			//广西麻将

	//休闲类
	static LPCTSTR __cdecl GetLLSHOWRank(LONG lScore);			    //连连看
	static LPCTSTR __cdecl GetPLANERank(LONG lScore);				//飞行棋
//	static LPCTSTR __cdecl GetBILLIARDSRank(LONG lScore);			//台球
	//视频游戏
//	static LPCTSTR __cdecl GetUPGRADEVDRank(LONG lScore);           //升级

	

	static LPCTSTR __cdecl GetDefaultRank(LONG lScore);
};


//-----------------------------------------------
//					the end
//-----------------------------------------------
