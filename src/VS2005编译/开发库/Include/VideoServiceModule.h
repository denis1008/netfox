#ifndef VIDEO_SERVICE_HEAD_FILE
#define VIDEO_SERVICE_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//ƽ̨ͷ�ļ�
#include "Template.h"
#include "GlobalDef.h"

//��Ϣ����
#include "CMD_Video.h"

//���ͷ�ļ�
#include "IUnknownEx.h"
#include "GameFrame.h"
#include "SkinControls.h"

//////////////////////////////////////////////////////////////////////////
//�����궨��

//��������
#ifndef VIDEO_SERVICE_CLASS
	#ifdef  VIDEO_SERVICE_DLL
		#define VIDEO_SERVICE_CLASS _declspec(dllexport)
	#else
		#define VIDEO_SERVICE_CLASS _declspec(dllimport)
	#endif
#endif

//ģ�鶨��
#ifndef _DEBUG
	#define VIDEO_SERVICE_DLL_NAME	TEXT("VideoService.dll")			//��� DLL ����
#else
	#define VIDEO_SERVICE_DLL_NAME	TEXT("VideoServiceD.dll")			//��� DLL ����
#endif

//////////////////////////////////////////////////////////////////////////
//�ṹ����

//������Ϣ
struct tagVideoNetwordInfo
{
	WORD							wNatPort;							//����˿�
	WORD							wLocalPort;							//����˿�
	DWORD							dwNatAddr;							//�����ַ
	DWORD							dwLocalAddr;						//���ص�ַ
};

//////////////////////////////////////////////////////////////////////////
//ȫ�ֶ���

//���ͽṹ
struct tagGiftResInfo
{
	WORD							wGiftID;							//��������
	CHAR							szShowMsg[256];						//��ʾ��Ϣ
};

//������Ϣ
tagGiftResInfo	const g_GiftResInfo[GIFT_COUNT]= 
{
	{ FLOWER_1, TEXT("[ %s ] �� [ %s ] �����˺�õ��%ld��[ %s ] ����+1��[ %s ] ����+1") },
	{ FLOWER_2, TEXT("[ %s ] �� [ %s ] ������Сõ��%ld��[ %s ] ����+2��[ %s ] ����+2")},
	{ FLOWER_3, TEXT("[ %s ] �� [ %s ] �����˰ٺ�%ld��[ %s ] ����+2��[ %s ] ����+2")}
};

//////////////////////////////////////////////////////////////////////////
//������ͷ�ļ�

#include "VideoServiceControl.h"

//////////////////////////////////////////////////////////////////////////

#endif
