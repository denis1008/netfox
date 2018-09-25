
#pragma once

#include "Interface.h"


//��Ϸ�ȼ�����
class CGameRankManager : public IGameRankManager
{
	//��������
public:
	CGameRankManager(void);
	virtual ~CGameRankManager(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CGameRankManager))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��ȡ�ȼ�
	virtual LPCTSTR __cdecl GetGameRank(WORD wKindID, LONG lScore, WORD wGameGenre);

	//�����Ϸ
	static LPCTSTR __cdecl GetSHOWHANDRank(LONG lScore);			//���
	static LPCTSTR __cdecl GetHKFIVECARDRank(LONG lScore);			//��ʽ������

	//����
	static LPCTSTR __cdecl GetLANDRank(LONG lScore);			    //������
	static LPCTSTR __cdecl GetLANDEXRank(LONG lScore);				//����������
	static LPCTSTR __cdecl GetLANDCRAZYRank(LONG lScore);			//��񶷵���
	static LPCTSTR __cdecl GetUPGRADERank(LONG lScore);				//��������
	static LPCTSTR __cdecl GetUPGRADEEXRank(LONG lScore);			//�ĸ�����
	static LPCTSTR __cdecl GetHOERank(LONG lScore);					//�����
	static LPCTSTR __cdecl GetUNCOVERPIGRank(LONG lScore);			//����
	static LPCTSTR __cdecl GetTRENCHRank(LONG lScore);				//�ڿ�
//	static LPCTSTR __cdecl GetRUNFASTRank(LONG lScore);				//�ܵÿ�	
	static LPCTSTR __cdecl GetSHUANGKOURank(LONG lScore);			//˫��
//	static LPCTSTR __cdecl GetSHUANGKOURank(LONG lScore);			//�ٱ�˫��
//	static LPCTSTR __cdecl GetSHUANGKOURank(LONG lScore);			//ǧ��˫��
	static LPCTSTR __cdecl GetGUANPAIRank(LONG lScore);				//����
//	static LPCTSTR __cdecl GetSANDAYIRank(LONG lScore);				//����һ
//	static LPCTSTR __cdecl GetCATCHPOCKRank(LONG lScore);			//׽������
//	static LPCTSTR __cdecl GetPAOHUZIRank(LONG lScore);				//�ܺ���
	static LPCTSTR __cdecl GetREDTENRank(LONG lScore);				//������ʮ
	static LPCTSTR __cdecl GetLIGUNRank(LONG lScore);				//��������
	static LPCTSTR __cdecl GetWULANGTUIRank(LONG lScore);			//�������ǽ�
//	static LPCTSTR __cdecl Get510KRank(LONG lScore);				//���� 510K
	static LPCTSTR __cdecl GetBLACKSEVENRank(LONG lScore);			//���Ϻ���
//	static LPCTSTR __cdecl GetQINGDUNRank(LONG lScore);				//���	
	static LPCTSTR __cdecl GetBIAOFENRank(LONG lScore);				//�������
	static LPCTSTR __cdecl GetREDFIVERank(LONG lScore);				//�������
//	static LPCTSTR __cdecl GetJIAOERRank(LONG lScore);				//���ǽж�
//	static LPCTSTR __cdecl GetUPGRADECSRank(LONG lScore);			//��������
//	static LPCTSTR __cdecl GetGUAILURank(LONG lScore);				//��·	
//	static LPCTSTR __cdecl GetNIUGUIRank(LONG lScore);				//ţ��
//	static LPCTSTR __cdecl GetLIANGFUTOURank(LONG lScore);			//����ͷ
	static LPCTSTR __cdecl GetHONGWURank(LONG lScore);				//��������һ(����)
//	static LPCTSTR __cdecl GetHONGWUEXRank(LONG lScore);			//��������һ(����)
	//����
	static LPCTSTR __cdecl GetCHINACHESSRank(LONG lScore);			//����
//	static LPCTSTR __cdecl GetCHESSRank(LONG lScore);				//��������
	static LPCTSTR __cdecl GetFOURENSIGNRank(LONG lScore);			//�Ĺ�����
	static LPCTSTR __cdecl GetGOBANGRank(LONG lScore);				//������
	static LPCTSTR __cdecl GetDOUSHOUQIRank(LONG lScore);			//������
	static LPCTSTR __cdecl GetWEIQIRank(LONG lScore);				//Χ��
	
	//�齫��
	static LPCTSTR __cdecl GetSPARROWRank(LONG lScore);			    //�齫ģ��
/*	static LPCTSTR __cdecl GetSPARROWGDRank(LONG lScore);			//�㶫�齫
	static LPCTSTR __cdecl GetSPARROWJSRank(LONG lScore);			//�����齫
	static LPCTSTR __cdecl GetSPARROWCSRank(LONG lScore);			//��ɳ�齫
	static LPCTSTR __cdecl GetSPARROWHYRank(LONG lScore);			//�����齫
	static LPCTSTR __cdecl GetSPARROWZJRank(LONG lScore);			//�㽭�齫
	static LPCTSTR __cdecl GetSPARROWCJRank(LONG lScore);			//����齫
	static LPCTSTR __cdecl GetSPARROWXSRank(LONG lScore);			//��ɽ�齫
	static LPCTSTR __cdecl GetSPARROWFZRank(LONG lScore);			//�����齫*/
	static LPCTSTR __cdecl GetSPARROWXYRank(LONG lScore);			//�����齫
//	static LPCTSTR __cdecl GetSPARROWGXRank(LONG lScore);			//�����齫

	//������
	static LPCTSTR __cdecl GetLLSHOWRank(LONG lScore);			    //������
	static LPCTSTR __cdecl GetPLANERank(LONG lScore);				//������
//	static LPCTSTR __cdecl GetBILLIARDSRank(LONG lScore);			//̨��
	//��Ƶ��Ϸ
//	static LPCTSTR __cdecl GetUPGRADEVDRank(LONG lScore);           //����

	

	static LPCTSTR __cdecl GetDefaultRank(LONG lScore);
};


//-----------------------------------------------
//					the end
//-----------------------------------------------
