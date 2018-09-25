
#include "StdAfx.h"
#include "GameRankManager.h"
#include "..\..\开发库\Include\GlobalDef.h"


typedef LPCTSTR (*PRANK)(LONG lScore);


CGameRankManager::CGameRankManager(void)
{
}

CGameRankManager::~CGameRankManager(void)
{
}

//
//接口查询
//
void * __cdecl CGameRankManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameRankManager,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameRankManager,Guid,dwQueryVer);
	return NULL;
}

				
//
//获取等级
//

//
//金币类型
//

LPCTSTR __cdecl CGameRankManager::GetGameRank(WORD wKindID, 
											  LONG lScore, 
											  WORD wGameGenre)
{



	if (wGameGenre==GAME_GENRE_GOLD)
	{
		return GetSHOWHANDRank(lScore);					//梭哈
/*		return GetHKFIVECARDRank(lScore);				//港式五张牌	
		return GetSHOWHANDRank(LONG lScore);			//炸金花
		return GetSHOWHANDRank(LONG lScore);			//百家乐
		return GetSHOWHANDRank(LONG lScore);			//牛牛
		return GetSHOWHANDRank(LONG lScore);			//四张
		return GetSHOWHANDRank(LONG lScore);			//德州扑克
		return GetSHOWHANDRank(LONG lScore);			//摆十三
		return GetSHOWHANDRank(LONG lScore);			//三公
		return GetSHOWHANDRank(LONG lScore);			//21 点*/
	}
	else 
	{
		switch (wKindID)
		{
		case 10001:{return GetSHOWHANDRank(lScore);}				//梭哈
 //棋类
/*		case ID_LAND:{return GetLANDRank(lScore);}						//斗地主
		case ID_LANDEX:{return GetLANDRank(lScore);}					//两副斗地主
		case ID_LANDCRAZY:{return GetLANDRank(lScore);}					//疯狂斗地主
		case ID_UPGRADE:{return GetUPGRADERank(lScore);}				//两副升级
		case ID_UPGRADEEX:{return GetUPGRADERank(lScore);}				//四副升级
		case ID_HOE:{return GetHOERank(lScore);}						//锄大地
		case ID_UNCOVERPIG:{return GetUNCOVERPIGRank(lScore);}			//拱猪
		case ID_TRENCH:{return GetTRENCHRank(lScore);}					//挖坑
//		case ID_RUNFAST:{return GetRank(lScore);}						//跑得快	
		case ID_SHUANGKOU:{return GetSHUANGKOURank(lScore);}			//双扣
		case ID_SHUANGKOUBB:{return GetSHUANGKOURank(lScore);}			//百变双扣
		case ID_SHUANGKOUQB:{return GetSHUANGKOURank(lScore);}			//千变双扣
		case ID_GUANPAI:{return GetGUANPAIRank(lScore);}				//关牌
//		case ID_SANDAYI:{return GetRank(lScore);}						//三打一
//		case ID_CATCHPOCK:{return GetRank(lScore);}						//捉老麻子
//		case ID_PAOHUZI:{return GetRank(lScore);}						//跑胡子
		case ID_REDTEN:{return GetREDTENRank(lScore);}					//丹东红十
		case ID_LIGUN:{return GetLIGUNRank(lScore);}					//朝阳立棍
		case ID_WULANGTUI:{return GetWULANGTUIRank(lScore);}			//丹东五狼脚
		case ID_510K:{return GetWULANGTUIRank(lScore);}					//福州 510K
		case ID_BLACKSEVEN:{return GetBLACKSEVENRank(lScore);}			//河南黑七
//		case ID_QINGDUN:{return Getank(lScore);}						//清墩	
		case ID_BIAOFEN:{return GetBIAOFENRank(lScore);}				//广西标分
		case ID_REDFIVE:{return GetREDFIVERank(lScore);}				//冲击红五
/*		case ID_JIAOER:{return GetRank(lScore);}						//潮汕叫二
		case ID_UPGRADECS:{return GetRank(lScore);}						//潮汕升级
		case ID_GUAILU:{return GetRank(lScore);}						//怪路	
		case ID_NIUGUI:{return GetRank(lScore);}						//牛鬼
		case ID_LIANGFUTOU:{return GetRank(lScore);}					//两副头*/
/*		case ID_HONGWU:{return GetHONGWURank(lScore);}					//红五三打一(两副)
		case ID_HONGWUEX:{return GetHONGWURank(lScore);}				//红五三打一(三副)
//棋类
		case ID_CHINACHESS:{return GetCHINACHESSRank(lScore);}			//象棋
		case ID_CHESS:{return GetCHINACHESSRank(lScore);}				//国际象棋
		case ID_FOURENSIGN:{return GetFOURENSIGNRank(lScore);}			//四国军棋
		case ID_GOBANG:{return GetGOBANGRank(lScore);}					//五子棋
		case ID_DOUSHOUQI:{return GetDOUSHOUQIRank(lScore);}			//斗兽棋
		case ID_WEIQI:{return GetWEIQIRank(lScore);}					//围棋
//麻将类
		case ID_SPARROW:{return GetSPARROWRank(lScore);}				//麻将模版
		case ID_SPARROWGD:{return GetSPARROWRank(lScore);}		*/		//广东麻将
/*		case ID_SPARROWJS:{return GetRank(lScore);}						//江苏麻将
		case ID_SPARROWCS:{return GetRank(lScore);}						//长沙麻将
		case ID_SPARROWHY:{return GetRank(lScore);}						//衡阳麻将
		case ID_SPARROWZJ:{return GetRank(lScore);}						//浙江麻将
		case ID_SPARROWCJ:{return GetRank(lScore);}						//冲击麻将
		case ID_SPARROWXS:{return GetRank(lScore);}						//象山麻将
		case ID_SPARROWFZ:{return GetRank(lScore);}						//福州麻将
		case ID_SPARROWXY:{return GetRank(lScore);}						//信阳麻将
		case ID_SPARROWGX:{return GetRank(lScore);}						//广西麻将*/
//休闲类
		//case ID_LLSHOW:{return GetLLSHOWRank(lScore);}					//连连看
		//case ID_PLANE:{return GetPLANERank(lScore);}					//飞行棋
//		case ID_BILLIARDS:{return GetRank(lScore);}						//台球
//视频游戏
//		case ID_UPGRADEVD:{return GetLANDRank(lScore);}					//升级

		default:
			{
				return GetLANDRank(lScore);
			}
		}
	}

	return NULL;
}



//梭哈
LPCTSTR __cdecl CGameRankManager::GetSHOWHANDRank(LONG lScore)
{

	static __int64 lScoreInfo[18] = 	{	4000,		8000,			20000,		40000L,	
	80000L,		150000L,		300000L,	500000L,	
	1000000L,	2000000L,		5000000L,	10000000L,	
	50000000L,	100000000L,		500000000L,	1000000000L,
	5000000000L,10000000000L
	};	LPCTSTR pszOrderName[19] = 	{	_T("务农"),			_T("佃户"),		_T("雇工"),		_T("作坊主"),	_T("农场主"),		_T("地主"),		_T("大地主"),	_T("土豪"),	_T("财主"),			_T("大财主"),	_T("富翁"),		_T("大富翁"),	_T("小财神"),		_T("大财神"),	_T("赌棍"),		_T("赌侠"),	_T("赌王"),			_T("赌圣"),		_T("赌神"),	};	for(int i=0; i<18; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[18];
}




//港式五张牌
//
LPCTSTR __cdecl CGameRankManager::GetHKFIVECARDRank(LONG lScore)
{


//分数

	static __int64 lScoreInfo[15] = 	{	1,	201,	501,	961,	
	1701,	2601,	4201,	6401,	
	9801,	15001,	22601,	34001L,	
	52001L,	120001L,99999999L
	};	LPCTSTR pszOrderName[16] = 	{	_T("平民"),	_T("小混混"),	_T("老油条"),	_T("小头目"),	_T("老千"),	_T("抗把子"),	_T("帮会大哥"),	_T("江湖大佬"),	_T("至尊"),	_T("千王"),		_T("梭霸"),		_T("梭侠"),	_T("梭王"),	_T("梭圣"),		_T("梭神"),		_T("梭神")	};	for(int i=0; i<15; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[15];
}



//
//锄大地
//
LPCTSTR __cdecl CGameRankManager::GetHOERank(LONG lScore)
{


	//分数


	LONG lScoreInfo[19] = 
	{		0,		100,	400,	900,	
			1600,	2500,	3700,	5500,	
			7700,	10500,	15500,	22500,	
			31500,	46500,	66500,	106500,	
			186500,	286500,	573000
	};

	LPCTSTR pszOrderName[20] = 
	{
		_T("游民"),		_T("游侠"),		_T("侠客"),		_T("侠圣"),	
		_T("骑士"),		_T("百眼巨人"),	_T("精灵王"),	_T("天使"),
		_T("月亮神"),	_T("战神"),		_T("胜利神"),	_T("太阳神"),
		_T("爱神"),		_T("大地神"),	_T("火神"),		_T("海神"),
		_T("冥神"),		_T("天王"),		_T("终极天王"),	_T("究极天王")
	};

	for(int i=0; i<19; i++)	
	{	
		if(lScore < lScoreInfo[i])
		{		
			return pszOrderName[i];	
		}
	}	
	
	return pszOrderName[19];
}



//双扣
//
LPCTSTR __cdecl CGameRankManager::GetSHUANGKOURank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[15] = 	{	-11999,		-5999,		1,			4001,
	8001,		16001,		32001L,		64001L,
	128001L,	256001L,	512001L,	1024001L,
	2048001L,	4096001L,	999999999L
	};	LPCTSTR pszOrderName[16] = 	{	_T("火柴棍"),		_T("烧火棍"),		_T("木棍"),		_T("齐眉棍"),	_T("双截棍"),		_T("三节棍"),		_T("五行棍"),	_T("镔铁棍"),		_T("赤铜棍"),		_T("亮银棍"),		_T("金棍"),		_T("打狗棒"),	_T("虎尾棍"),		_T("盘龙棍"),		_T("定海神针"),	_T("定海神针")	};			for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}



/*
//240 分
//
LPCTSTR __cdecl CGameRankManager::GetTFZGameRank(LONG lScore)
{
	static __int64 lScoreInfo[27] = 	{	51L,		101L,		151L,		251,		
	401,		651,		1151,		1801,		
	2951,		4751,		7701,		12451,	
	20151,		32601L,		52751L,		85351L,	
	138101L,		223451L,		361551L,		585001L,
	946551L,		1431551L,	2378101L,	3809651L,
	6187751L,	9997401L,	16185151L
	};	LPCTSTR pszOrderName[28] = 	{	_T("待业"),		_T("科员"),		_T("科长助理"),	_T("副科长"),	_T("第一副科"),	_T("正科长"),	_T("处长助理"),	_T("副处长"),	_T("第一副处"),	_T("正处长"),	_T("局长助理"),	_T("副局长"),	_T("第一副局"),	_T("正局长"),	_T("厅长助理"),	_T("副厅长"),	_T("第一副厅"),	_T("正厅长"),	_T("部长助理"),	_T("副部长"),	_T("第一副部"),	_T("正部长"),	_T("总理助理"),_T("副总理"),	_T("第一副总理"),_T("总理"),	_T("副主席"),	_T("主席")	};	for(int i=0; i<27; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[27];
}

*/



//关牌
//
LPCTSTR __cdecl CGameRankManager::GetGUANPAIRank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[19] = 	{	101,		301,		801,		1501,
	2201,		3001,		4001,		5501,
	7701,		10001,		14001,		20001,
	30001L,		45001,		72001L,		100001L,
	150001,		300001,		999999999L
	};	LPCTSTR pszOrderName[20] = 	{	_T("列兵"),		_T("下等兵"),	_T("上等兵"),		_T("下士"),	_T("中士"),		_T("上士"),		_T("准军士长"),		_T("军士长"),	_T("总军士长"),	_T("准尉"),		_T("少尉"),			_T("中尉"),		_T("上尉"),		_T("少校"),		_T("中校"),			_T("上校"),	_T("少将"),		_T("中将"),		_T("上将"),			_T("无帅")	};			for(int i=0; i<19; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[19];
}



//红十游戏
//
LPCTSTR __cdecl CGameRankManager::GetREDTENRank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[19] = 	{	101,		301,		801,		1501,
	2201,		3001,		4001,		5501,
	7701,		10001,		14001,		20001,
	30001L,		45001,		72001L,		100001L,
	150001,		300001,		999999999L
	};	LPCTSTR pszOrderName[20] = 	{	_T("列兵"),		_T("下等兵"),	_T("上等兵"),		_T("下士"),	_T("中士"),		_T("上士"),		_T("准军士长"),		_T("军士长"),	_T("总军士长"),	_T("准尉"),		_T("少尉"),			_T("中尉"),		_T("上尉"),		_T("少校"),		_T("中校"),			_T("上校"),	_T("少将"),		_T("中将"),		_T("上将"),			_T("无帅")	};			for(int i=0; i<19; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[19];
}




//
//余姚麻将
//
/*
LPCTSTR __cdecl CGameRankManager::GetSparrowCXRank(LONG lScore)
{
	static __int64 lScoreInfo[16] = 	{	100,	500,	2000,	
	5000,	20000,	100000,	500000,	
	1000000,	3000000,	5000000,	8000000,	
	10000000,	15000000,	20000000,	50000000,	
	100000000
	};	LPCTSTR pszOrderName[17] = 	{	_T("白板"),	_T("一万"),		_T("二万"),	_T("三万"),	_T("四万"),	_T("五万"),		_T("六万"),	_T("七万"),	_T("八万"),	_T("九万"),		_T("东风"),	_T("西风"),	_T("南风"),	_T("北风"),		_T("中"),	_T("发"),	_T("雀神")	};	for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}
*/


//
//拱猪
//
LPCTSTR __cdecl CGameRankManager::GetUNCOVERPIGRank(LONG lScore)
{

//拱猪
//分数

	LONG lScoreInfo[19] = 	{	-5000000,	-1000000,	-200000,	-100000,
	0,			5000,		20000,		60000,
	100000,		150000,		240000,		380000,
	550000,		700000,		1000000,	2800000,
	5000000,	10000000,	20000000	};	LPCTSTR pszOrderName[20] = 	{	_T("世界猪圣"),		_T("国家猪神"),	_T("地区猪王"),		_T("农场猪王"),	_T("猪小弟"),		_T("小猪倌"),	_T("业余饲养员"),	_T("优秀饲养员"),	_T("养猪专业户"),	_T("养猪标兵"),	_T("养猪状元"),		_T("养猪专家"),	_T("养猪大王"),		_T("农场组长"),	_T("农场经理"),		_T("小农场主"),	_T("大农场主"),		_T("小资本家"),	_T("大资本家"),		_T("富甲一方")	};	for(int i=0; i<19; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[19];
}

//
//升级
//
LPCTSTR __cdecl CGameRankManager::GetUPGRADERank(LONG lScore)
{


//分数


	LONG lScoreInfo[16] = 	{	11,		31,		71,		151,	
	311,	631,	1271,	2251,	
	5111,	10231,	20471,	40951L,	
	81911L,	159201L,300001L,99999999L
	};	LPCTSTR pszOrderName[17] = 	{	_T("庶民"),		_T("秀才"),		_T("举人"),		_T("九品芝官"),	_T("八品县丞"),	_T("七品知县"),	_T("六品通判"),	_T("五品知州"),	_T("四品知府"),	_T("三品侍郎"),	_T("二品巡抚"),	_T("一品总督"),	_T("宰相"),		_T("郡王"),		_T("亲王"),		_T("皇帝"),	_T("皇帝")	};	for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}




//
//河南黑七
//

LPCTSTR __cdecl CGameRankManager::GetBLACKSEVENRank(LONG lScore)
{

	static __int64 lScoreInfo[22] =
	{
		-30000,		-3000,		0,			10,		
		30,			150,		310,		630,
		1270,		2550,		5110,		10230,
		20470,		40950L,		81910L,		163820L,
		327640L,	655280,		1310560L,	2660000,
		5000000L,	50000001L,
	};

	
	LPCTSTR pszOrderName[23] = 
	{
			_T("瞎打哩"),			_T("牌喽子"),			_T("陪练"),			_T("菜鸟"),
			_T("新手"),				_T("中不溜"),			_T("高手"),			_T("牌混子"),
			_T("小牌仙"),			_T("大牌仙"),			_T("小牌神"),		_T("大牌神"),
			_T("牌界领袖"),			_T("黑七王子"),			_T("黑七王"),		_T("信阳牌神"),
			_T("浉河区黑七王"),		_T("信阳黑七王子"),		_T("信阳黑七王"),	_T("信阳黑七至尊"),
			_T("黑七我最爱"),		_T("打遍信阳无敌手"),	_T("天下至尊")
	};  	
	
	for(int i=0; i<22; i++)	 
	{ 		
		if(lScore < lScoreInfo[i]) 
		{ 			
			return pszOrderName[i]; 
		} 	
	}  

	return pszOrderName[22];
}


//
//挖坑
//
LPCTSTR __cdecl CGameRankManager::GetTRENCHRank(LONG lScore)
{


//分数

	LONG lScoreInfo[21] = 	{	-75000,-50000,	-30000,	-20000,	
	-10000,	-5000,	0,	200,	
	500,	1000,	2200,	3000,	
	5000,	7700,	10000,	14000,	
	20000,	30000,50000,75000,100000
	};	LPCTSTR pszOrderName[22] = 	{	_T("大裂谷"),	_T("大盆地"),		_T("小盆地"),	_T("大水沟"),	_T("小水沟"),	_T("大土坑"),		_T("小土坑"),	_T("铁耙子"),_T("铁锄子"),	_T("铁铲子"),	_T("钢耙子"),		_T("钢锄头"),	_T("钢铲子"),	_T("银耙子"),	_T("银锄头"),		_T("银铲子"),	_T("金锄头"),	_T("金铲子"),	_T("神锄头"),		_T("神铲子"),	_T("九齿钉耙"),	_T("如意金箍棒")	};	for(int i=0; i<21; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[21];
}


//
//中国象棋
//
LPCTSTR __cdecl CGameRankManager::GetCHINACHESSRank(LONG lScore)
{


//分数

	LONG lScoreInfo[14] = 	{	1,		101,	301,	601,
	1001,	1501,	2201,	3101,
	4101,	5201,	6401,	7901,
	20001L,	99999999L
	};	LPCTSTR pszOrderName[15] = 	{	_T("棋童"),		_T("一级棋士"),		_T("二级棋士"),	_T("三级棋士"),	_T("四级棋士"),	_T("五级棋士"),		_T("六级棋士"),	_T("七级棋士"),	_T("八级棋士"),	_T("九级棋士"),		_T("一级大师"),	_T("二级大师"),	_T("三级大师"),	_T("特级大师"),		_T("特级大师")	};	for(int i=0; i<14; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[14];
}

//
//连连看
//
LPCTSTR __cdecl CGameRankManager::GetLLSHOWRank(LONG lScore)	
{
	__int64 lScoreInfo[17] = 	{	101,	201,	501,	1001,	
	2001,	3001,	5001,	8001,	
	12001,	20001,	30001L,	40001L,	
	80001L,	120001L,160001L,300001L,
	99999999L
	};	LPCTSTR pszOrderName[18] = 	{	_T("小星星"),	_T("魔羯座"),		_T("水瓶座"),	_T("双鱼座"),	_T("白羊座"),	_T("金牛座"),		_T("双子座"),	_T("巨蟹座"),	_T("狮子座"),	_T("处女座"),		_T("天秤座"),	_T("天蝎座"),	_T("射手座"),	_T("月亮座"),		_T("太阳座"),	_T("金眼火睛"),	_T("神眼"),		_T("神眼")	};	for(int i=0; i<17; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[17];
}


//四国军棋
LPCTSTR __cdecl CGameRankManager::GetFOURENSIGNRank(LONG lScore)
{
	
	static __int64 lScoreInfo[17] = 	{	
	81,		121,	201,	401,
	601,	881,	1401,	2001,
	3001,	4001,	6201,	8601,
	12601,	20001,	30001L,	50001L,
	99999999L
	};	LPCTSTR pszOrderName[18] = 	{	_T("儿童团"),	_T("民兵"),		_T("预备役军人"),	_T("三等兵"),	_T("二等兵"),	_T("一等兵"),	_T("班长"),			_T("排长"),	_T("连长"),		_T("营长"),		_T("旅长"),			_T("师长"),	_T("副师长"),	_T("军长"),	_T("集团军长"),	_T("集团军司令"),	_T("三军总司令"),_T("三军总司令")	};	for(int i=0; i<17; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[17];
}


//
//斗兽棋
//

LPCTSTR __cdecl CGameRankManager::GetDOUSHOUQIRank(LONG lScore)
{
	
	LONG lScoreInfo[16] = 	{	10,		50,		80,		110,
	150,	200,	300,	400,
	500,	700,	800,    900,	
	1000,	1500,	2000,	3000
	};	LPCTSTR pszOrderName[17] = 	{	_T("虫宝宝"),	   _T("幼虫"),	     _T("小飞虫"),	    _T("成虫"),	_T("花壳虫"),	   _T("两翼虫"),	 _T("四翼虫"),      _T("轻翼虫"),	_T("战虫"),  	   _T("天虫"),	     _T("右道神虫"),	_T("左道神虫"),		_T("天虫王子"),    _T("天虫王后"),	 _T("天虫头领"),	_T("无敌天虫"),	_T("无敌天虫")		};	for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}

//围棋
LPCTSTR __cdecl CGameRankManager::GetWEIQIRank(LONG lScore)
{
	
	LONG lScoreInfo[22] = 	{	-74999,-49999,	-29999,	-19999,	
	-9999,	-4999,	0,	200,	
	500,	1000,	2200,	3000,	
	5000,	7700,	10000,	14000,	
	20000,	30000,50000,75000,100000,130000
	};	LPCTSTR pszOrderName[23] = 	{	_T("黄粱一梦"),	_T("无可救药"),		_T("一无是处"),	_T("醉生梦死"),	_T("糊里糊涂"),	_T("马马虎虎"),		_T("粗心大意"),	_T("业余1段"),	_T("业余2段"),	_T("业余3段"),		_T("业余4段"),	_T("业余5段"),	_T("业余6段"),	_T("业余7段"),		_T("职业初段"),	_T("职业2段"),	_T("职业3段"),	_T("职业4段"),		_T("职业5段"),	_T("职业6段"),		_T("职业7段"),	_T("职业8段"),		_T("职业9段")	};	for(int i=0; i<22; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[22];
}

//
//斗地主
//
LPCTSTR __cdecl CGameRankManager::GetLANDRank(LONG lScore)
{

//分数


	static __int64 lScoreInfo[19] = 	{	60,		160,		320,		560,	
	920,		1400,	2080,	3200,	
	4800,	7200,	1080,	16000L,	
	27200L,	48000L,	80000L,	136000L,	
	240000L,400000L,1000000L
	};	LPCTSTR pszOrderName[20] = 	{	_T("农奴"),		_T("乞丐"),		_T("佃农"),		_T("流浪汉"),	_T("包身工"),	_T("短工"),		_T("长工"),		_T("贫农"),	_T("中农"),		_T("富农"),		_T("富翁"),		_T("地主"),	_T("土财主"),	_T("大财主"),	_T("恶霸地主"),	_T("恶霸财主"),	_T("奴隶主"),	_T("大奴隶主"),	_T("地主豪强"),	_T("诸侯")	};	for(int i=0; i<19; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[19];

}


//五子棋
//
LPCTSTR __cdecl CGameRankManager::GetGOBANGRank(LONG lScore)
{


//分数


	static __int64 lScoreInfo[20] = 	{	-499,	-129,	-119,	-49,
	1,		21,		51,		81,
	131,	301,	601,	1001,
	1501,	2101,	2801,	3701,
	5001,	7001,	10001L,99999999L
	};	LPCTSTR pszOrderName[21] = 	{	_T("9级"),		_T("8级"),		_T("7级"),		_T("6级"),	_T("5级"),		_T("4级"),		_T("3级"),		_T("2级"),	_T("1级"),		_T("棋童"),		_T("入门棋手"),	_T("段进阶棋手"),	_T("布衣棋士"),	_T("铁甲棋士"),	_T("铜甲棋士"),	_T("银甲棋士"),	_T("金甲棋士"),	_T("棋王"),		_T("棋圣"),	_T("棋仙"),	_T("棋仙")	};	for(int i=0; i<20; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[20];
}
/*
//炸金花
//
LPCTSTR __cdecl CGameRankManager::GetTHREELEAFRank(LONG lScore)
{


//分数


	static __int64 lScoreInfo[21] = 	{	-75000,-50000,	-30000,	-20000,	
	-10000,	-5000,	0,	200,	
	500,	1000,	2200,	3000,	
	5000,	7700,	10000,	14000,	
	20000,	30000,50000,75000,100000
	};	LPCTSTR pszOrderName[22] = 	{	_T("赤色骷髅"),	_T("黑色木乃伊"),		_T("冰封僵尸"),	_T("诡异食尸妖"),	_T("掘墓妖"),	_T("御鬼术士"),		_T("撒旦追随者"),	_T("圣殿随从"),	_T("圣殿门徒"),	_T("圣殿祈祷士"),		_T("圣殿牧师"),	_T("圣殿武士"),	_T("圣殿护法"),	_T("圣殿祭祀"),		_T("神殿门徒"),	_T("神殿牧师"),	_T("神殿武士"),	_T("神殿护法"),		_T("神殿法师"),	_T("神殿主祭"),		_T("神殿守护神"),		_T("无极天使")	};	for(int i=0; i<21; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[21];
}

*/

/*
//黑杰克
//
LPCTSTR __cdecl CGameRankManager::GetBlackJackRank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[15] = 	{	1,	201,	501,	961,	
	1701,	2601,	4201,	6401,	
	9801,	15001,	22601,	34001L,	
	52001L,	120001L,99999999
	};	LPCTSTR pszOrderName[16] = 	{	_T("方片2"),	_T("梅花3"),		_T("方片4"),	_T("梅花5"),	_T("红心6"),	_T("方片7"),		_T("梅花8"),	_T("红心9"),	_T("黑桃10"),	_T("黑桃J"),		_T("黑桃Q"),	_T("黑桃K"),	_T("黑桃A"),	_T("五龙"),			_T("BlackJack"),_T("BlackJack")	};	for(int i=0; i<15; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[15];

}
*/


//麻将
//
LPCTSTR __cdecl CGameRankManager::GetSPARROWRank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[18] = 	{	4000,		8000,		20000L,		40000L,	
	80000L,		150000L,	300000L,	500000L,	
	1000000L,	2000000L,	5000000L,	10000000L,	
	50000000L,	100000000L,	500000000L,	1000000000L,	
	5000000000L,10000000000L
	};	LPCTSTR pszOrderName[19] = 	{	_T("红中"),		_T("发财"),			_T("白板"),		_T("九筒"),	_T("九条"),		_T("九万"),			_T("东风"),		_T("南风"),	_T("西风"),		_T("北风"),			_T("四暗客"),	_T("清一色"),	_T("小三元"),	_T("大三元"),		_T("小四喜"),	_T("大四喜"),	_T("九连宝灯"),	_T("十八罗汉"),		_T("国士无双")	};		for(int i=0; i<18; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[18];
}




//丹东五狼脚
//
LPCTSTR __cdecl CGameRankManager::GetWULANGTUIRank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[15] = 	{	-11999,		-5999,		1,			4000,
	8000,		16000,		32000L,		64001L,
	128000L,	256000L,	512000L,	1024000L,
	2048000L,	4096000L,	8192000L
	};	LPCTSTR pszOrderName[16] = 	{	_T("腿毛"),		_T("无影腿"),	_T("看眼"),		_T("牌架子"),	_T("小弥人"),	_T("花拳秀腿"),	_T("双后"),		_T("双王"),	_T("梅花腿"),	_T("黑桃腿"),	_T("方块腿"),	_T("红心腿"),	_T("腿王"),		_T("腿圣"),		_T("腿神")	};			for(int i=0; i<15; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[15];
}




//朝阳立棍
//
LPCTSTR __cdecl CGameRankManager::GetLIGUNRank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[15] = 	{	-11999,		-5999,		1,			4001,
	8001,		16001,		32001L,		64001L,
	128001L,	256001L,	512001L,	1024001L,
	2048001L,	4096001L,	999999999L
	};	LPCTSTR pszOrderName[16] = 	{	_T("火柴棍"),		_T("烧火棍"),		_T("木棍"),		_T("齐眉棍"),	_T("双截棍"),		_T("三节棍"),		_T("五行棍"),	_T("镔铁棍"),		_T("赤铜棍"),		_T("亮银棍"),		_T("金棍"),		_T("打狗棒"),	_T("虎尾棍"),		_T("盘龙棍"),		_T("定海神针"),	_T("定海神针")	};			for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}



//
//广西标分
//

LPCTSTR __cdecl CGameRankManager::GetBIAOFENRank(LONG lScore)
{
	
	static __int64 lScoreInfo[20] =
	{
		20,		50,		100,		180,
		250,		350,		450,		550,		
		850,		1250,		1750,		2350,	
		3100,		4100,		5000,		25000,	
		50000L,		100000L,		150000L,		200000L
	};
	
	
	LPCTSTR pszOrderName[21] = 
	{
		_T("新手"),		_T("初学者"),		_T("打手"),	_T("金牌打手"),
		_T("保镖"),	_T("镖师"),	_T("习武者"),	_T("苦行者"),
		_T("武术家"),	_T("教头"),	_T("武术师傅"),	_T("无名侠客"),
		_T("小侠"),	_T("少侠"),	_T("大侠"),	_T("少年英雄"),
		_T("一代宗师"),	_T("开山老祖"),	_T("武林盟主"),	_T("武林泰斗"),
		_T("天下第一")
	};
	
	for(int i=0; i<20; i++)	
	{
		if(lScore < lScoreInfo[i]) 
		{
			return pszOrderName[i];
		}
	}
	
	return pszOrderName[20];
}



//冲击红五
//
LPCTSTR __cdecl CGameRankManager::GetREDFIVERank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[20] = 	{	19,			39,			79,			159,
	319,		639,		1279,		2559,
	5119,		10239,		20479,		40959L,
	81919L,		163839L,	327679L,	655359L,
	1310719,	2621439L,	5242879L,	5242880L
	};	LPCTSTR pszOrderName[21] = 	{	_T("科员"),		_T("主任"),		_T("副科长"),		_T("科长"),		_T("副处长"),	_T("处长"),		_T("副局长"),		_T("局长"),			_T("副县长"),	_T("县长"),		_T("副厅长"),		_T("厅长"),				_T("副市长"),	_T("市长"),		_T("副部长"),		_T("部长"),				_T("副省长"),	_T("省长"),		_T("副总理"),		_T("总理"),	_T("主席")	};			for(int i=0; i<20; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[20];
}




//
//象山红五三打一
//

LPCTSTR __cdecl CGameRankManager::GetHONGWURank(LONG lScore)
{
//分数

	static __int64 lScoreInfo[21] = 	{	20,			40,			80,
	160,		320,		640,		1280,
	2560,		5120,		12340,		20480,
	40960L,		81920L,		163840L,	327680L,
	655360L,	1310720L,	2621440L,	5242880L,
	6242880L
	};	LPCTSTR pszOrderName[22] = 	{	_T("科员"),		_T("主任"),		_T("副科长"),		_T("科长"),		_T("副处长"),	_T("处长"),		_T("副局长"),		_T("局长"),			_T("副县长"),	_T("县长"),		_T("副厅长"),		_T("厅长"),				_T("副市长"),	_T("市长"),		_T("副部长"),		_T("部长"),				_T("副省长"),	_T("省长"),		_T("副总理"),		_T("总理"),	_T("主席")	};			for(int i=0; i<21; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[21];
}





//
//信阳麻将
//

LPCTSTR __cdecl CGameRankManager::GetSPARROWXYRank(LONG lScore)
{

	static __int64 lScoreInfo[22] =
	{
		-30000,		-3000,		0,			10,		
		30,			150,		310,		630,
		1270,		2550,		5110,		10230,
		20470,		40950L,		81910L,		163820L,
		327640L,	655280,		1310560L,	2660000,
		5000000L,	50000001L,
	};

	
	LPCTSTR pszOrderName[23] = 
	{
			_T("瞎打"),			_T("臭手"),			_T("陪练"),			_T("初学"),
			_T("生手"),				_T("赌棍"),			_T("赌鬼"),			_T("老手"),
			_T("高手"),			_T("高人"),			_T("小千王"),		_T("小赌王"),
			_T("千王"),			_T("赌王"),			_T("小千霸"),		_T("小赌神"),
			_T("小赌圣"),		_T("千霸"),		_T("赌神"),	_T("赌圣"),
			_T("世界赌王"),		_T("世界赌神"),	_T("至尊雀圣")
	};  	
	
	for(int i=0; i<22; i++)	 
	{ 		
		if(lScore < lScoreInfo[i]) 
		{ 			
			return pszOrderName[i]; 
		} 	
	}  

	return pszOrderName[22];
}




//飞行棋
//
LPCTSTR __cdecl CGameRankManager::GetPLANERank(LONG lScore)
{

//分数

	static __int64 lScoreInfo[16] = 	{	101,		201,		501,		1001,
	2001,		3001,		5001,		8001,
	12001,		20001,		30001,		40001L,
	80001,		120001L,	160001L,	300001L,
	};	LPCTSTR pszOrderName[17] = 	{	_T("飞行学员"),		_T("初级飞行员"),	_T("中级飞行员"),		_T("高级飞行员"),	_T("战斗机飞行员"),		_T("飞行教练"),		_T("王牌飞行员"),		_T("飞行中尉"),	_T("飞行少校"),	_T("飞行中校"),		_T("飞行上校"),			_T("空军司令"),		_T("黑蝙蝠中队队员"),		_T("黑蝙蝠中队队长"),		_T("黑蝙蝠中队大队长"),			_T("黑蝙蝠中队参谋"),	_T("黑蝙蝠中队司令")	};			for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}





LPCTSTR __cdecl CGameRankManager::GetDefaultRank(LONG lScore)
{
	return _T("");
}


//
//建立对象函数
//
extern "C" __declspec(dllexport) 
void * __cdecl CreateGameRankManager(const GUID & Guid, 
									 DWORD dwInterfaceVer)
{
	//建立对象
	CGameRankManager *pGameRankManager=NULL;
	try
	{
		pGameRankManager = new CGameRankManager();
		if(pGameRankManager==NULL) 
		{
			throw _T("创建失败");
		}

		void *pObject = pGameRankManager->QueryInterface(Guid,dwInterfaceVer);
		if(pObject==NULL) 
		{
			throw _T("接口查询失败");
		}
		return pObject;
	}
	catch (...) 
	{
	}

	//清理对象
	SafeDelete(pGameRankManager);
	return NULL;
}


//-----------------------------------------------
//					the end
//-----------------------------------------------
