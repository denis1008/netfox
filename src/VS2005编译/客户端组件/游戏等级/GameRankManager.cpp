
#include "StdAfx.h"
#include "GameRankManager.h"
#include "..\..\������\Include\GlobalDef.h"


typedef LPCTSTR (*PRANK)(LONG lScore);


CGameRankManager::CGameRankManager(void)
{
}

CGameRankManager::~CGameRankManager(void)
{
}

//
//�ӿڲ�ѯ
//
void * __cdecl CGameRankManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameRankManager,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameRankManager,Guid,dwQueryVer);
	return NULL;
}

				
//
//��ȡ�ȼ�
//

//
//�������
//

LPCTSTR __cdecl CGameRankManager::GetGameRank(WORD wKindID, 
											  LONG lScore, 
											  WORD wGameGenre)
{



	if (wGameGenre==GAME_GENRE_GOLD)
	{
		return GetSHOWHANDRank(lScore);					//���
/*		return GetHKFIVECARDRank(lScore);				//��ʽ������	
		return GetSHOWHANDRank(LONG lScore);			//ը��
		return GetSHOWHANDRank(LONG lScore);			//�ټ���
		return GetSHOWHANDRank(LONG lScore);			//ţţ
		return GetSHOWHANDRank(LONG lScore);			//����
		return GetSHOWHANDRank(LONG lScore);			//�����˿�
		return GetSHOWHANDRank(LONG lScore);			//��ʮ��
		return GetSHOWHANDRank(LONG lScore);			//����
		return GetSHOWHANDRank(LONG lScore);			//21 ��*/
	}
	else 
	{
		switch (wKindID)
		{
		case 10001:{return GetSHOWHANDRank(lScore);}				//���
 //����
/*		case ID_LAND:{return GetLANDRank(lScore);}						//������
		case ID_LANDEX:{return GetLANDRank(lScore);}					//����������
		case ID_LANDCRAZY:{return GetLANDRank(lScore);}					//��񶷵���
		case ID_UPGRADE:{return GetUPGRADERank(lScore);}				//��������
		case ID_UPGRADEEX:{return GetUPGRADERank(lScore);}				//�ĸ�����
		case ID_HOE:{return GetHOERank(lScore);}						//�����
		case ID_UNCOVERPIG:{return GetUNCOVERPIGRank(lScore);}			//����
		case ID_TRENCH:{return GetTRENCHRank(lScore);}					//�ڿ�
//		case ID_RUNFAST:{return GetRank(lScore);}						//�ܵÿ�	
		case ID_SHUANGKOU:{return GetSHUANGKOURank(lScore);}			//˫��
		case ID_SHUANGKOUBB:{return GetSHUANGKOURank(lScore);}			//�ٱ�˫��
		case ID_SHUANGKOUQB:{return GetSHUANGKOURank(lScore);}			//ǧ��˫��
		case ID_GUANPAI:{return GetGUANPAIRank(lScore);}				//����
//		case ID_SANDAYI:{return GetRank(lScore);}						//����һ
//		case ID_CATCHPOCK:{return GetRank(lScore);}						//׽������
//		case ID_PAOHUZI:{return GetRank(lScore);}						//�ܺ���
		case ID_REDTEN:{return GetREDTENRank(lScore);}					//������ʮ
		case ID_LIGUN:{return GetLIGUNRank(lScore);}					//��������
		case ID_WULANGTUI:{return GetWULANGTUIRank(lScore);}			//�������ǽ�
		case ID_510K:{return GetWULANGTUIRank(lScore);}					//���� 510K
		case ID_BLACKSEVEN:{return GetBLACKSEVENRank(lScore);}			//���Ϻ���
//		case ID_QINGDUN:{return Getank(lScore);}						//���	
		case ID_BIAOFEN:{return GetBIAOFENRank(lScore);}				//�������
		case ID_REDFIVE:{return GetREDFIVERank(lScore);}				//�������
/*		case ID_JIAOER:{return GetRank(lScore);}						//���ǽж�
		case ID_UPGRADECS:{return GetRank(lScore);}						//��������
		case ID_GUAILU:{return GetRank(lScore);}						//��·	
		case ID_NIUGUI:{return GetRank(lScore);}						//ţ��
		case ID_LIANGFUTOU:{return GetRank(lScore);}					//����ͷ*/
/*		case ID_HONGWU:{return GetHONGWURank(lScore);}					//��������һ(����)
		case ID_HONGWUEX:{return GetHONGWURank(lScore);}				//��������һ(����)
//����
		case ID_CHINACHESS:{return GetCHINACHESSRank(lScore);}			//����
		case ID_CHESS:{return GetCHINACHESSRank(lScore);}				//��������
		case ID_FOURENSIGN:{return GetFOURENSIGNRank(lScore);}			//�Ĺ�����
		case ID_GOBANG:{return GetGOBANGRank(lScore);}					//������
		case ID_DOUSHOUQI:{return GetDOUSHOUQIRank(lScore);}			//������
		case ID_WEIQI:{return GetWEIQIRank(lScore);}					//Χ��
//�齫��
		case ID_SPARROW:{return GetSPARROWRank(lScore);}				//�齫ģ��
		case ID_SPARROWGD:{return GetSPARROWRank(lScore);}		*/		//�㶫�齫
/*		case ID_SPARROWJS:{return GetRank(lScore);}						//�����齫
		case ID_SPARROWCS:{return GetRank(lScore);}						//��ɳ�齫
		case ID_SPARROWHY:{return GetRank(lScore);}						//�����齫
		case ID_SPARROWZJ:{return GetRank(lScore);}						//�㽭�齫
		case ID_SPARROWCJ:{return GetRank(lScore);}						//����齫
		case ID_SPARROWXS:{return GetRank(lScore);}						//��ɽ�齫
		case ID_SPARROWFZ:{return GetRank(lScore);}						//�����齫
		case ID_SPARROWXY:{return GetRank(lScore);}						//�����齫
		case ID_SPARROWGX:{return GetRank(lScore);}						//�����齫*/
//������
		//case ID_LLSHOW:{return GetLLSHOWRank(lScore);}					//������
		//case ID_PLANE:{return GetPLANERank(lScore);}					//������
//		case ID_BILLIARDS:{return GetRank(lScore);}						//̨��
//��Ƶ��Ϸ
//		case ID_UPGRADEVD:{return GetLANDRank(lScore);}					//����

		default:
			{
				return GetLANDRank(lScore);
			}
		}
	}

	return NULL;
}



//���
LPCTSTR __cdecl CGameRankManager::GetSHOWHANDRank(LONG lScore)
{

	static __int64 lScoreInfo[18] = 	{	4000,		8000,			20000,		40000L,	
	80000L,		150000L,		300000L,	500000L,	
	1000000L,	2000000L,		5000000L,	10000000L,	
	50000000L,	100000000L,		500000000L,	1000000000L,
	5000000000L,10000000000L
	};	LPCTSTR pszOrderName[19] = 	{	_T("��ũ"),			_T("�軧"),		_T("�͹�"),		_T("������"),	_T("ũ����"),		_T("����"),		_T("�����"),	_T("����"),	_T("����"),			_T("�����"),	_T("����"),		_T("����"),	_T("С����"),		_T("�����"),	_T("�Ĺ�"),		_T("����"),	_T("����"),			_T("��ʥ"),		_T("����"),	};	for(int i=0; i<18; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[18];
}




//��ʽ������
//
LPCTSTR __cdecl CGameRankManager::GetHKFIVECARDRank(LONG lScore)
{


//����

	static __int64 lScoreInfo[15] = 	{	1,	201,	501,	961,	
	1701,	2601,	4201,	6401,	
	9801,	15001,	22601,	34001L,	
	52001L,	120001L,99999999L
	};	LPCTSTR pszOrderName[16] = 	{	_T("ƽ��"),	_T("С���"),	_T("������"),	_T("СͷĿ"),	_T("��ǧ"),	_T("������"),	_T("�����"),	_T("��������"),	_T("����"),	_T("ǧ��"),		_T("���"),		_T("����"),	_T("����"),	_T("��ʥ"),		_T("����"),		_T("����")	};	for(int i=0; i<15; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[15];
}



//
//�����
//
LPCTSTR __cdecl CGameRankManager::GetHOERank(LONG lScore)
{


	//����


	LONG lScoreInfo[19] = 
	{		0,		100,	400,	900,	
			1600,	2500,	3700,	5500,	
			7700,	10500,	15500,	22500,	
			31500,	46500,	66500,	106500,	
			186500,	286500,	573000
	};

	LPCTSTR pszOrderName[20] = 
	{
		_T("����"),		_T("����"),		_T("����"),		_T("��ʥ"),	
		_T("��ʿ"),		_T("���۾���"),	_T("������"),	_T("��ʹ"),
		_T("������"),	_T("ս��"),		_T("ʤ����"),	_T("̫����"),
		_T("����"),		_T("�����"),	_T("����"),		_T("����"),
		_T("ڤ��"),		_T("����"),		_T("�ռ�����"),	_T("��������")
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



//˫��
//
LPCTSTR __cdecl CGameRankManager::GetSHUANGKOURank(LONG lScore)
{

//����

	static __int64 lScoreInfo[15] = 	{	-11999,		-5999,		1,			4001,
	8001,		16001,		32001L,		64001L,
	128001L,	256001L,	512001L,	1024001L,
	2048001L,	4096001L,	999999999L
	};	LPCTSTR pszOrderName[16] = 	{	_T("����"),		_T("�ջ��"),		_T("ľ��"),		_T("��ü��"),	_T("˫�ع�"),		_T("���ڹ�"),		_T("���й�"),	_T("������"),		_T("��ͭ��"),		_T("������"),		_T("���"),		_T("�򹷰�"),	_T("��β��"),		_T("������"),		_T("��������"),	_T("��������")	};			for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}



/*
//240 ��
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
	};	LPCTSTR pszOrderName[28] = 	{	_T("��ҵ"),		_T("��Ա"),		_T("�Ƴ�����"),	_T("���Ƴ�"),	_T("��һ����"),	_T("���Ƴ�"),	_T("��������"),	_T("������"),	_T("��һ����"),	_T("������"),	_T("�ֳ�����"),	_T("���ֳ�"),	_T("��һ����"),	_T("���ֳ�"),	_T("��������"),	_T("������"),	_T("��һ����"),	_T("������"),	_T("��������"),	_T("������"),	_T("��һ����"),	_T("������"),	_T("��������"),_T("������"),	_T("��һ������"),_T("����"),	_T("����ϯ"),	_T("��ϯ")	};	for(int i=0; i<27; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[27];
}

*/



//����
//
LPCTSTR __cdecl CGameRankManager::GetGUANPAIRank(LONG lScore)
{

//����

	static __int64 lScoreInfo[19] = 	{	101,		301,		801,		1501,
	2201,		3001,		4001,		5501,
	7701,		10001,		14001,		20001,
	30001L,		45001,		72001L,		100001L,
	150001,		300001,		999999999L
	};	LPCTSTR pszOrderName[20] = 	{	_T("�б�"),		_T("�µȱ�"),	_T("�ϵȱ�"),		_T("��ʿ"),	_T("��ʿ"),		_T("��ʿ"),		_T("׼��ʿ��"),		_T("��ʿ��"),	_T("�ܾ�ʿ��"),	_T("׼ξ"),		_T("��ξ"),			_T("��ξ"),		_T("��ξ"),		_T("��У"),		_T("��У"),			_T("��У"),	_T("�ٽ�"),		_T("�н�"),		_T("�Ͻ�"),			_T("��˧")	};			for(int i=0; i<19; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[19];
}



//��ʮ��Ϸ
//
LPCTSTR __cdecl CGameRankManager::GetREDTENRank(LONG lScore)
{

//����

	static __int64 lScoreInfo[19] = 	{	101,		301,		801,		1501,
	2201,		3001,		4001,		5501,
	7701,		10001,		14001,		20001,
	30001L,		45001,		72001L,		100001L,
	150001,		300001,		999999999L
	};	LPCTSTR pszOrderName[20] = 	{	_T("�б�"),		_T("�µȱ�"),	_T("�ϵȱ�"),		_T("��ʿ"),	_T("��ʿ"),		_T("��ʿ"),		_T("׼��ʿ��"),		_T("��ʿ��"),	_T("�ܾ�ʿ��"),	_T("׼ξ"),		_T("��ξ"),			_T("��ξ"),		_T("��ξ"),		_T("��У"),		_T("��У"),			_T("��У"),	_T("�ٽ�"),		_T("�н�"),		_T("�Ͻ�"),			_T("��˧")	};			for(int i=0; i<19; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[19];
}




//
//��Ҧ�齫
//
/*
LPCTSTR __cdecl CGameRankManager::GetSparrowCXRank(LONG lScore)
{
	static __int64 lScoreInfo[16] = 	{	100,	500,	2000,	
	5000,	20000,	100000,	500000,	
	1000000,	3000000,	5000000,	8000000,	
	10000000,	15000000,	20000000,	50000000,	
	100000000
	};	LPCTSTR pszOrderName[17] = 	{	_T("�װ�"),	_T("һ��"),		_T("����"),	_T("����"),	_T("����"),	_T("����"),		_T("����"),	_T("����"),	_T("����"),	_T("����"),		_T("����"),	_T("����"),	_T("�Ϸ�"),	_T("����"),		_T("��"),	_T("��"),	_T("ȸ��")	};	for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}
*/


//
//����
//
LPCTSTR __cdecl CGameRankManager::GetUNCOVERPIGRank(LONG lScore)
{

//����
//����

	LONG lScoreInfo[19] = 	{	-5000000,	-1000000,	-200000,	-100000,
	0,			5000,		20000,		60000,
	100000,		150000,		240000,		380000,
	550000,		700000,		1000000,	2800000,
	5000000,	10000000,	20000000	};	LPCTSTR pszOrderName[20] = 	{	_T("������ʥ"),		_T("��������"),	_T("��������"),		_T("ũ������"),	_T("��С��"),		_T("С����"),	_T("ҵ������Ա"),	_T("��������Ա"),	_T("����רҵ��"),	_T("������"),	_T("����״Ԫ"),		_T("����ר��"),	_T("�������"),		_T("ũ���鳤"),	_T("ũ������"),		_T("Сũ����"),	_T("��ũ����"),		_T("С�ʱ���"),	_T("���ʱ���"),		_T("����һ��")	};	for(int i=0; i<19; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[19];
}

//
//����
//
LPCTSTR __cdecl CGameRankManager::GetUPGRADERank(LONG lScore)
{


//����


	LONG lScoreInfo[16] = 	{	11,		31,		71,		151,	
	311,	631,	1271,	2251,	
	5111,	10231,	20471,	40951L,	
	81911L,	159201L,300001L,99999999L
	};	LPCTSTR pszOrderName[17] = 	{	_T("����"),		_T("���"),		_T("����"),		_T("��Ʒ֥��"),	_T("��Ʒ��ة"),	_T("��Ʒ֪��"),	_T("��Ʒͨ��"),	_T("��Ʒ֪��"),	_T("��Ʒ֪��"),	_T("��Ʒ����"),	_T("��ƷѲ��"),	_T("һƷ�ܶ�"),	_T("����"),		_T("����"),		_T("����"),		_T("�ʵ�"),	_T("�ʵ�")	};	for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}




//
//���Ϻ���
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
			_T("Ϲ����"),			_T("�����"),			_T("����"),			_T("����"),
			_T("����"),				_T("�в���"),			_T("����"),			_T("�ƻ���"),
			_T("С����"),			_T("������"),			_T("С����"),		_T("������"),
			_T("�ƽ�����"),			_T("��������"),			_T("������"),		_T("��������"),
			_T("������������"),		_T("������������"),		_T("����������"),	_T("������������"),
			_T("�������"),		_T("��������޵���"),	_T("��������")
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
//�ڿ�
//
LPCTSTR __cdecl CGameRankManager::GetTRENCHRank(LONG lScore)
{


//����

	LONG lScoreInfo[21] = 	{	-75000,-50000,	-30000,	-20000,	
	-10000,	-5000,	0,	200,	
	500,	1000,	2200,	3000,	
	5000,	7700,	10000,	14000,	
	20000,	30000,50000,75000,100000
	};	LPCTSTR pszOrderName[22] = 	{	_T("���ѹ�"),	_T("�����"),		_T("С���"),	_T("��ˮ��"),	_T("Сˮ��"),	_T("������"),		_T("С����"),	_T("������"),_T("������"),	_T("������"),	_T("�ְ���"),		_T("�ֳ�ͷ"),	_T("�ֲ���"),	_T("������"),	_T("����ͷ"),		_T("������"),	_T("���ͷ"),	_T("�����"),	_T("���ͷ"),		_T("�����"),	_T("�ųݶ���"),	_T("����𹿰�")	};	for(int i=0; i<21; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[21];
}


//
//�й�����
//
LPCTSTR __cdecl CGameRankManager::GetCHINACHESSRank(LONG lScore)
{


//����

	LONG lScoreInfo[14] = 	{	1,		101,	301,	601,
	1001,	1501,	2201,	3101,
	4101,	5201,	6401,	7901,
	20001L,	99999999L
	};	LPCTSTR pszOrderName[15] = 	{	_T("��ͯ"),		_T("һ����ʿ"),		_T("������ʿ"),	_T("������ʿ"),	_T("�ļ���ʿ"),	_T("�弶��ʿ"),		_T("������ʿ"),	_T("�߼���ʿ"),	_T("�˼���ʿ"),	_T("�ż���ʿ"),		_T("һ����ʦ"),	_T("������ʦ"),	_T("������ʦ"),	_T("�ؼ���ʦ"),		_T("�ؼ���ʦ")	};	for(int i=0; i<14; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[14];
}

//
//������
//
LPCTSTR __cdecl CGameRankManager::GetLLSHOWRank(LONG lScore)	
{
	__int64 lScoreInfo[17] = 	{	101,	201,	501,	1001,	
	2001,	3001,	5001,	8001,	
	12001,	20001,	30001L,	40001L,	
	80001L,	120001L,160001L,300001L,
	99999999L
	};	LPCTSTR pszOrderName[18] = 	{	_T("С����"),	_T("ħ����"),		_T("ˮƿ��"),	_T("˫����"),	_T("������"),	_T("��ţ��"),		_T("˫����"),	_T("��з��"),	_T("ʨ����"),	_T("��Ů��"),		_T("�����"),	_T("��Ы��"),	_T("������"),	_T("������"),		_T("̫����"),	_T("���ۻ�"),	_T("����"),		_T("����")	};	for(int i=0; i<17; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[17];
}


//�Ĺ�����
LPCTSTR __cdecl CGameRankManager::GetFOURENSIGNRank(LONG lScore)
{
	
	static __int64 lScoreInfo[17] = 	{	
	81,		121,	201,	401,
	601,	881,	1401,	2001,
	3001,	4001,	6201,	8601,
	12601,	20001,	30001L,	50001L,
	99999999L
	};	LPCTSTR pszOrderName[18] = 	{	_T("��ͯ��"),	_T("���"),		_T("Ԥ���۾���"),	_T("���ȱ�"),	_T("���ȱ�"),	_T("һ�ȱ�"),	_T("�೤"),			_T("�ų�"),	_T("����"),		_T("Ӫ��"),		_T("�ó�"),			_T("ʦ��"),	_T("��ʦ��"),	_T("����"),	_T("���ž���"),	_T("���ž�˾��"),	_T("������˾��"),_T("������˾��")	};	for(int i=0; i<17; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[17];
}


//
//������
//

LPCTSTR __cdecl CGameRankManager::GetDOUSHOUQIRank(LONG lScore)
{
	
	LONG lScoreInfo[16] = 	{	10,		50,		80,		110,
	150,	200,	300,	400,
	500,	700,	800,    900,	
	1000,	1500,	2000,	3000
	};	LPCTSTR pszOrderName[17] = 	{	_T("�汦��"),	   _T("�׳�"),	     _T("С�ɳ�"),	    _T("�ɳ�"),	_T("���ǳ�"),	   _T("�����"),	 _T("�����"),      _T("�����"),	_T("ս��"),  	   _T("���"),	     _T("�ҵ����"),	_T("������"),		_T("�������"),    _T("�������"),	 _T("���ͷ��"),	_T("�޵����"),	_T("�޵����")		};	for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}

//Χ��
LPCTSTR __cdecl CGameRankManager::GetWEIQIRank(LONG lScore)
{
	
	LONG lScoreInfo[22] = 	{	-74999,-49999,	-29999,	-19999,	
	-9999,	-4999,	0,	200,	
	500,	1000,	2200,	3000,	
	5000,	7700,	10000,	14000,	
	20000,	30000,50000,75000,100000,130000
	};	LPCTSTR pszOrderName[23] = 	{	_T("����һ��"),	_T("�޿ɾ�ҩ"),		_T("һ���Ǵ�"),	_T("��������"),	_T("�����Ϳ"),	_T("������"),		_T("���Ĵ���"),	_T("ҵ��1��"),	_T("ҵ��2��"),	_T("ҵ��3��"),		_T("ҵ��4��"),	_T("ҵ��5��"),	_T("ҵ��6��"),	_T("ҵ��7��"),		_T("ְҵ����"),	_T("ְҵ2��"),	_T("ְҵ3��"),	_T("ְҵ4��"),		_T("ְҵ5��"),	_T("ְҵ6��"),		_T("ְҵ7��"),	_T("ְҵ8��"),		_T("ְҵ9��")	};	for(int i=0; i<22; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[22];
}

//
//������
//
LPCTSTR __cdecl CGameRankManager::GetLANDRank(LONG lScore)
{

//����


	static __int64 lScoreInfo[19] = 	{	60,		160,		320,		560,	
	920,		1400,	2080,	3200,	
	4800,	7200,	1080,	16000L,	
	27200L,	48000L,	80000L,	136000L,	
	240000L,400000L,1000000L
	};	LPCTSTR pszOrderName[20] = 	{	_T("ũū"),		_T("��ؤ"),		_T("��ũ"),		_T("���˺�"),	_T("����"),	_T("�̹�"),		_T("����"),		_T("ƶũ"),	_T("��ũ"),		_T("��ũ"),		_T("����"),		_T("����"),	_T("������"),	_T("�����"),	_T("��Ե���"),	_T("��Բ���"),	_T("ū����"),	_T("��ū����"),	_T("������ǿ"),	_T("���")	};	for(int i=0; i<19; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[19];

}


//������
//
LPCTSTR __cdecl CGameRankManager::GetGOBANGRank(LONG lScore)
{


//����


	static __int64 lScoreInfo[20] = 	{	-499,	-129,	-119,	-49,
	1,		21,		51,		81,
	131,	301,	601,	1001,
	1501,	2101,	2801,	3701,
	5001,	7001,	10001L,99999999L
	};	LPCTSTR pszOrderName[21] = 	{	_T("9��"),		_T("8��"),		_T("7��"),		_T("6��"),	_T("5��"),		_T("4��"),		_T("3��"),		_T("2��"),	_T("1��"),		_T("��ͯ"),		_T("��������"),	_T("�ν�������"),	_T("������ʿ"),	_T("������ʿ"),	_T("ͭ����ʿ"),	_T("������ʿ"),	_T("�����ʿ"),	_T("����"),		_T("��ʥ"),	_T("����"),	_T("����")	};	for(int i=0; i<20; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[20];
}
/*
//ը��
//
LPCTSTR __cdecl CGameRankManager::GetTHREELEAFRank(LONG lScore)
{


//����


	static __int64 lScoreInfo[21] = 	{	-75000,-50000,	-30000,	-20000,	
	-10000,	-5000,	0,	200,	
	500,	1000,	2200,	3000,	
	5000,	7700,	10000,	14000,	
	20000,	30000,50000,75000,100000
	};	LPCTSTR pszOrderName[22] = 	{	_T("��ɫ����"),	_T("��ɫľ����"),		_T("���⽩ʬ"),	_T("����ʳʬ��"),	_T("��Ĺ��"),	_T("������ʿ"),		_T("����׷����"),	_T("ʥ�����"),	_T("ʥ����ͽ"),	_T("ʥ����ʿ"),		_T("ʥ����ʦ"),	_T("ʥ����ʿ"),	_T("ʥ���"),	_T("ʥ�����"),		_T("�����ͽ"),	_T("�����ʦ"),	_T("�����ʿ"),	_T("����"),		_T("��ʦ"),	_T("�������"),		_T("����ػ���"),		_T("�޼���ʹ")	};	for(int i=0; i<21; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[21];
}

*/

/*
//�ڽܿ�
//
LPCTSTR __cdecl CGameRankManager::GetBlackJackRank(LONG lScore)
{

//����

	static __int64 lScoreInfo[15] = 	{	1,	201,	501,	961,	
	1701,	2601,	4201,	6401,	
	9801,	15001,	22601,	34001L,	
	52001L,	120001L,99999999
	};	LPCTSTR pszOrderName[16] = 	{	_T("��Ƭ2"),	_T("÷��3"),		_T("��Ƭ4"),	_T("÷��5"),	_T("����6"),	_T("��Ƭ7"),		_T("÷��8"),	_T("����9"),	_T("����10"),	_T("����J"),		_T("����Q"),	_T("����K"),	_T("����A"),	_T("����"),			_T("BlackJack"),_T("BlackJack")	};	for(int i=0; i<15; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[15];

}
*/


//�齫
//
LPCTSTR __cdecl CGameRankManager::GetSPARROWRank(LONG lScore)
{

//����

	static __int64 lScoreInfo[18] = 	{	4000,		8000,		20000L,		40000L,	
	80000L,		150000L,	300000L,	500000L,	
	1000000L,	2000000L,	5000000L,	10000000L,	
	50000000L,	100000000L,	500000000L,	1000000000L,	
	5000000000L,10000000000L
	};	LPCTSTR pszOrderName[19] = 	{	_T("����"),		_T("����"),			_T("�װ�"),		_T("��Ͳ"),	_T("����"),		_T("����"),			_T("����"),		_T("�Ϸ�"),	_T("����"),		_T("����"),			_T("�İ���"),	_T("��һɫ"),	_T("С��Ԫ"),	_T("����Ԫ"),		_T("С��ϲ"),	_T("����ϲ"),	_T("��������"),	_T("ʮ���޺�"),		_T("��ʿ��˫")	};		for(int i=0; i<18; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[18];
}




//�������ǽ�
//
LPCTSTR __cdecl CGameRankManager::GetWULANGTUIRank(LONG lScore)
{

//����

	static __int64 lScoreInfo[15] = 	{	-11999,		-5999,		1,			4000,
	8000,		16000,		32000L,		64001L,
	128000L,	256000L,	512000L,	1024000L,
	2048000L,	4096000L,	8192000L
	};	LPCTSTR pszOrderName[16] = 	{	_T("��ë"),		_T("��Ӱ��"),	_T("����"),		_T("�Ƽ���"),	_T("С����"),	_T("��ȭ����"),	_T("˫��"),		_T("˫��"),	_T("÷����"),	_T("������"),	_T("������"),	_T("������"),	_T("����"),		_T("��ʥ"),		_T("����")	};			for(int i=0; i<15; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[15];
}




//��������
//
LPCTSTR __cdecl CGameRankManager::GetLIGUNRank(LONG lScore)
{

//����

	static __int64 lScoreInfo[15] = 	{	-11999,		-5999,		1,			4001,
	8001,		16001,		32001L,		64001L,
	128001L,	256001L,	512001L,	1024001L,
	2048001L,	4096001L,	999999999L
	};	LPCTSTR pszOrderName[16] = 	{	_T("����"),		_T("�ջ��"),		_T("ľ��"),		_T("��ü��"),	_T("˫�ع�"),		_T("���ڹ�"),		_T("���й�"),	_T("������"),		_T("��ͭ��"),		_T("������"),		_T("���"),		_T("�򹷰�"),	_T("��β��"),		_T("������"),		_T("��������"),	_T("��������")	};			for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}



//
//�������
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
		_T("����"),		_T("��ѧ��"),		_T("����"),	_T("���ƴ���"),
		_T("����"),	_T("��ʦ"),	_T("ϰ����"),	_T("������"),
		_T("������"),	_T("��ͷ"),	_T("����ʦ��"),	_T("��������"),
		_T("С��"),	_T("����"),	_T("����"),	_T("����Ӣ��"),
		_T("һ����ʦ"),	_T("��ɽ����"),	_T("��������"),	_T("����̩��"),
		_T("���µ�һ")
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



//�������
//
LPCTSTR __cdecl CGameRankManager::GetREDFIVERank(LONG lScore)
{

//����

	static __int64 lScoreInfo[20] = 	{	19,			39,			79,			159,
	319,		639,		1279,		2559,
	5119,		10239,		20479,		40959L,
	81919L,		163839L,	327679L,	655359L,
	1310719,	2621439L,	5242879L,	5242880L
	};	LPCTSTR pszOrderName[21] = 	{	_T("��Ա"),		_T("����"),		_T("���Ƴ�"),		_T("�Ƴ�"),		_T("������"),	_T("����"),		_T("���ֳ�"),		_T("�ֳ�"),			_T("���س�"),	_T("�س�"),		_T("������"),		_T("����"),				_T("���г�"),	_T("�г�"),		_T("������"),		_T("����"),				_T("��ʡ��"),	_T("ʡ��"),		_T("������"),		_T("����"),	_T("��ϯ")	};			for(int i=0; i<20; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[20];
}




//
//��ɽ��������һ
//

LPCTSTR __cdecl CGameRankManager::GetHONGWURank(LONG lScore)
{
//����

	static __int64 lScoreInfo[21] = 	{	20,			40,			80,
	160,		320,		640,		1280,
	2560,		5120,		12340,		20480,
	40960L,		81920L,		163840L,	327680L,
	655360L,	1310720L,	2621440L,	5242880L,
	6242880L
	};	LPCTSTR pszOrderName[22] = 	{	_T("��Ա"),		_T("����"),		_T("���Ƴ�"),		_T("�Ƴ�"),		_T("������"),	_T("����"),		_T("���ֳ�"),		_T("�ֳ�"),			_T("���س�"),	_T("�س�"),		_T("������"),		_T("����"),				_T("���г�"),	_T("�г�"),		_T("������"),		_T("����"),				_T("��ʡ��"),	_T("ʡ��"),		_T("������"),		_T("����"),	_T("��ϯ")	};			for(int i=0; i<21; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[21];
}





//
//�����齫
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
			_T("Ϲ��"),			_T("����"),			_T("����"),			_T("��ѧ"),
			_T("����"),				_T("�Ĺ�"),			_T("�Ĺ�"),			_T("����"),
			_T("����"),			_T("����"),			_T("Сǧ��"),		_T("С����"),
			_T("ǧ��"),			_T("����"),			_T("Сǧ��"),		_T("С����"),
			_T("С��ʥ"),		_T("ǧ��"),		_T("����"),	_T("��ʥ"),
			_T("�������"),		_T("�������"),	_T("����ȸʥ")
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




//������
//
LPCTSTR __cdecl CGameRankManager::GetPLANERank(LONG lScore)
{

//����

	static __int64 lScoreInfo[16] = 	{	101,		201,		501,		1001,
	2001,		3001,		5001,		8001,
	12001,		20001,		30001,		40001L,
	80001,		120001L,	160001L,	300001L,
	};	LPCTSTR pszOrderName[17] = 	{	_T("����ѧԱ"),		_T("��������Ա"),	_T("�м�����Ա"),		_T("�߼�����Ա"),	_T("ս��������Ա"),		_T("���н���"),		_T("���Ʒ���Ա"),		_T("������ξ"),	_T("������У"),	_T("������У"),		_T("������У"),			_T("�վ�˾��"),		_T("�������жӶ�Ա"),		_T("�������жӶӳ�"),		_T("�������жӴ�ӳ�"),			_T("�������жӲ�ı"),	_T("�������ж�˾��")	};			for(int i=0; i<16; i++)		{		if(lScore < lScoreInfo[i]) 		{			return pszOrderName[i];		}	}	return pszOrderName[16];
}





LPCTSTR __cdecl CGameRankManager::GetDefaultRank(LONG lScore)
{
	return _T("");
}


//
//����������
//
extern "C" __declspec(dllexport) 
void * __cdecl CreateGameRankManager(const GUID & Guid, 
									 DWORD dwInterfaceVer)
{
	//��������
	CGameRankManager *pGameRankManager=NULL;
	try
	{
		pGameRankManager = new CGameRankManager();
		if(pGameRankManager==NULL) 
		{
			throw _T("����ʧ��");
		}

		void *pObject = pGameRankManager->QueryInterface(Guid,dwInterfaceVer);
		if(pObject==NULL) 
		{
			throw _T("�ӿڲ�ѯʧ��");
		}
		return pObject;
	}
	catch (...) 
	{
	}

	//�������
	SafeDelete(pGameRankManager);
	return NULL;
}


//-----------------------------------------------
//					the end
//-----------------------------------------------
