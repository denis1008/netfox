#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#endif



#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯����Ϊ��ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �����ؼ���֧��
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "../../Include/flypublicdefine.h"
#define HOME_WEB_URL "http://www.cctvdodo.com/FlyGameWeb"

#include "..\..\�������\����ؼ�\SkinControls.h"

#define MAX_SCENE_NUM	10//��󳡾���
#define ONE_SCENE_MAX_TEXT_NUM	15//ÿ������TEXT�����

//��������
typedef struct _SOUND_TEXT_ITEM
{
	char showInfo[50];
	char playSound[50];
}
SOUND_TEXT_ITEM;

//����
typedef struct _SCENE_ITEM
{
	int	 useTextInt;//�Ѿ�ʹ�õĸ���
	char TypeName[50];
	SOUND_TEXT_ITEM TextList[ONE_SCENE_MAX_TEXT_NUM];
}
SCENE_ITEM;

extern void WriteLog(CString strFileName, CString strText);

//////////////////////////////////////////////////////////////////////////
