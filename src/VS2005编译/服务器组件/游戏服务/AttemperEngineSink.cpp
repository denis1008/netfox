#include "StdAfx.h"
#include "TableFrame.h"
#include "DataBaseSink.h"
#include "AttemperEngineSink.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CAttemperEngineSink::CAttemperEngineSink()
{
	//游戏变量
	m_wMaxUserItem=0;
	m_pTableFrame=NULL;
	m_pNormalParameter=NULL;
	m_pAndroidParameter=NULL;

	//消息变量
	m_cbRoomMsgIndex=0;
	m_cbGameMsgIndex=0;

	//配置变量
	m_dwCenterServer=0L;
	m_pGameServiceAttrib=NULL;
	m_pGameServiceOption=NULL;

	//控制变量
	m_bShallClose=false;
	m_bAllowWisper=true;
	m_bAllowRoomChat=true;
	m_bAllowGameChat=true;
	m_bAllowEnterRoom=true;
	m_bAllowEnterGame=true;

	//中心服务器
	m_pCenterSocket=NULL;
	m_SocketState=SocketState_NoConnect;

	//辅助变量
	m_wColumnInfoSize=0;
	m_wOnLineInfoSize=0;
	memset(&m_ColumnInfo,0,sizeof(m_ColumnInfo));
	memset(&m_OnLineCountInfo,0,sizeof(m_OnLineCountInfo));

	//游戏组件
	m_hDllInstance=NULL;
	m_pIGameServiceManager=NULL;

	//接口变量
	m_pITimerEngine=NULL;
	m_pIEventService=NULL;
	m_pIAttemperEngine=NULL;
	m_pITCPSocketEngine=NULL;

	return;
}

//析构函数
CAttemperEngineSink::~CAttemperEngineSink()
{
	//删除内存
	SafeDeleteArray(m_pTableFrame);
	SafeDeleteArray(m_pNormalParameter);
	SafeDeleteArray(m_pAndroidParameter);

	return;
}

//接口查询
void * __cdecl CAttemperEngineSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IAttemperEngineSink,Guid,dwQueryVer);
	QUERYINTERFACE(IGameServiceFrame,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IAttemperEngineSink,Guid,dwQueryVer);
	return NULL;
}

//调度模块启动
bool __cdecl CAttemperEngineSink::StartService(IUnknownEx * pIUnknownEx)
{
	//效验参数
	ASSERT(pIUnknownEx!=NULL);

	//设置变量
	m_wColumnInfoSize=0;
	m_wOnLineInfoSize=0;
	memset(&m_ColumnInfo,0,sizeof(m_ColumnInfo));
	memset(&m_OnLineCountInfo,0,sizeof(m_OnLineCountInfo));

	//创建辅助变量
	m_wMaxUserItem=m_pGameServiceOption->wMaxConnect;
	m_pNormalParameter=new tagConnectItemInfo [m_wMaxUserItem];
	m_pAndroidParameter=new tagConnectItemInfo [MAX_ANDROID];
	memset(m_pNormalParameter,0,sizeof(tagConnectItemInfo)*m_wMaxUserItem);
	memset(m_pAndroidParameter,0,sizeof(tagConnectItemInfo)*MAX_ANDROID);

	//加载游戏组件
	if (m_pIGameServiceManager->RectifyServiceOption(m_pGameServiceOption)==false) return false;

	//创建游戏桌子
	ASSERT(m_pGameServiceOption->wTableCount!=0);
	m_pTableFrame=new CTableFrame [m_pGameServiceOption->wTableCount];
	if (m_pTableFrame==NULL) return false;

	//初始化桌子
	bool bSuccess=false;
	tagTableFrameParameter TableFrameParameter;
	TableFrameParameter.pGameServiceAttrib=m_pGameServiceAttrib;
	TableFrameParameter.pGameServiceOption=m_pGameServiceOption;
	TableFrameParameter.pIGameServiceFrame=GET_MYSELF_INTERFACE(IUnknownEx);
	TableFrameParameter.pIGameServiceManager=GET_OBJECTPTR_INTERFACE(m_pIGameServiceManager,IUnknownEx);
	for (WORD i=0;i<m_pGameServiceOption->wTableCount;i++)
	{
		bSuccess=(m_pTableFrame+i)->InitTableFrame(i,&TableFrameParameter);
		if (bSuccess==false) return false;
	}

	//机器人类
	m_AndroidUserManager.m_pITimerEngine=m_pITimerEngine;
	m_AndroidUserManager.m_pGameServiceAttrib=m_pGameServiceAttrib;
	m_AndroidUserManager.m_pGameServiceOption=m_pGameServiceOption;
	m_AndroidUserManager.m_pIGameServiceManager=m_pIGameServiceManager;
	m_AndroidUserManager.m_pIServerUserManager=GET_OBJECT_INTERFACE(m_ServerUserManager,IServerUserManager);

	//构造列表解释
	switch (m_pGameServiceOption->wServerType)
	{
	case GAME_GENRE_GOLD:	//金币类型
		{
			//变量定义
			tagColumnItem ColumnItem[]=
			{
				115,DTP_USER_ACCOUNTS,TEXT("用户名"),
					60,DTP_GAME_ID,TEXT("ID 号码"),
					60,DTP_USER_SCORE,TEXT("游戏币"),
					40,DTP_USER_TABLE,TEXT("桌号"),
					85,DTP_GAME_LEVEL,TEXT("游戏级别"),
					50,DTP_USER_EXPERIENCE,TEXT("经验值"),
					60,DTP_WIN_RATE,TEXT("胜率"),
					60,DTP_FLEE_RATE,TEXT("逃率"),
					60,DTP_USER_PLAY_COUNT,TEXT("总局"),
					60,DTP_USER_WIN,TEXT("赢局"),
					60,DTP_USER_LOST,TEXT("输局"),
					60,DTP_USER_DRAW,TEXT("和局"),
					60,DTP_USER_FLEE,TEXT("逃局"),
					200,DTP_UNDER_WRITE,TEXT("个性签名"),
			};

			//设置变量
			m_ColumnInfo.wColumnCount=CountArray(ColumnItem);
			CopyMemory(m_ColumnInfo.ColumnItem,ColumnItem,sizeof(ColumnItem));

			break;
		}
	case GAME_GENRE_MATCH:	//比赛类型
		{
			//变量定义
			tagColumnItem ColumnItem[]=
			{
				115,DTP_USER_ACCOUNTS,TEXT("用户名"),
					60,DTP_GAME_ID,TEXT("ID 号码"),
					60,DTP_USER_SCORE,TEXT("赛币"),
					40,DTP_USER_TABLE,TEXT("桌号"),
					85,DTP_GAME_LEVEL,TEXT("游戏级别"),
					50,DTP_USER_EXPERIENCE,TEXT("经验值"),
					60,DTP_WIN_RATE,TEXT("胜率"),
					60,DTP_FLEE_RATE,TEXT("逃率"),
					60,DTP_USER_PLAY_COUNT,TEXT("总局"),
					60,DTP_USER_WIN,TEXT("赢局"),
					60,DTP_USER_LOST,TEXT("输局"),
					60,DTP_USER_DRAW,TEXT("和局"),
					60,DTP_USER_FLEE,TEXT("逃局"),
					200,DTP_UNDER_WRITE,TEXT("个性签名"),
			};

			//设置变量
			m_ColumnInfo.wColumnCount=CountArray(ColumnItem);
			CopyMemory(m_ColumnInfo.ColumnItem,ColumnItem,sizeof(ColumnItem));

			break;
		}
	default:
		{
			//变量定义
			tagColumnItem ColumnItem[]=
			{
				115,DTP_USER_ACCOUNTS,TEXT("用户名"),
					60,DTP_GAME_ID,TEXT("ID 号码"),
					60,DTP_USER_SCORE,TEXT("积分"),
					40,DTP_USER_TABLE,TEXT("桌号"),
					85,DTP_GAME_LEVEL,TEXT("游戏级别"),
					50,DTP_USER_EXPERIENCE,TEXT("经验值"),
					60,DTP_WIN_RATE,TEXT("胜率"),
					60,DTP_FLEE_RATE,TEXT("逃率"),
					60,DTP_USER_PLAY_COUNT,TEXT("总局"),
					60,DTP_USER_WIN,TEXT("赢局"),
					60,DTP_USER_LOST,TEXT("输局"),
					60,DTP_USER_DRAW,TEXT("和局"),
					60,DTP_USER_FLEE,TEXT("逃局"),
					200,DTP_UNDER_WRITE,TEXT("个性签名"),
			};

			//设置变量
			m_ColumnInfo.wColumnCount=CountArray(ColumnItem);
			CopyMemory(m_ColumnInfo.ColumnItem,ColumnItem,sizeof(ColumnItem));

			break;
		}
	}

	//设置列表
	WORD wColumnInfoHandSize=sizeof(m_ColumnInfo)-sizeof(m_ColumnInfo.ColumnItem);
	m_wColumnInfoSize=wColumnInfoHandSize+m_ColumnInfo.wColumnCount*sizeof(m_ColumnInfo.ColumnItem[0]);

	//随机数字
	srand((DWORD)time(NULL));

	//连接中心服务器
	m_pCenterSocket->Connect(m_dwCenterServer,PORT_CENTER_SERVER);

	//系统消息
	m_pITimerEngine->SetTimer(IDI_SEND_SYSTEM_MESSAGE,300000L,(DWORD)(-1),0);

	//启动机器
	IQueueService * pIQueueService=(IQueueService *)m_pIAttemperEngine->GetQueueService(IID_IQueueService,VER_IQueueService);
	m_AndroidUserManager.m_AttemperEvent.SetQueueService(pIQueueService);
	if (m_AndroidUserManager.StartService()==false) return false;

	//加载用户
	m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LOAD_ANDROID,0,0,NULL,0);

	//分配用户
	m_pITimerEngine->SetTimer(IDI_DISTRIBUTE_ANDROID,TIME_DISTRIBUTE_ANDROID*1000L,(DWORD)(-1),NULL);

	return true;
}

//调度模块关闭
bool __cdecl CAttemperEngineSink::StopService(IUnknownEx * pIUnknownEx)
{
	//注销房间
	if (m_SocketState==SocketState_Connected)
	{
		CMD_CS_UnRegGameServer UnRegGameServer;
		memset(&UnRegGameServer,0,sizeof(UnRegGameServer));
		UnRegGameServer.wKindID=m_pGameServiceAttrib->wKindID;
		UnRegGameServer.wServerID=m_pGameServiceOption->wServerID;
		m_pCenterSocket->SendData(MDM_CS_SERVER_MANAGER,SUB_CS_UNREG_GAME_SERVER,&UnRegGameServer,sizeof(UnRegGameServer));
	}

	//关闭组件
	m_AndroidUserManager.StopService();
	m_pCenterSocket->CloseSocket(false);
	m_ServerUserManager.ResetUserManager();

	//删除数据
	m_wMaxUserItem=0;
	SafeDeleteArray(m_pTableFrame);
	SafeDeleteArray(m_pNormalParameter);
	SafeDeleteArray(m_pAndroidParameter);

	//控制变量
	m_bShallClose=false;
	m_bAllowWisper=true;
	m_bAllowRoomChat=true;
	m_bAllowGameChat=true;
	m_bAllowEnterRoom=true;
	m_bAllowEnterGame=true;

	//消息变量
	m_cbRoomMsgIndex=0;
	m_cbGameMsgIndex=0;

	//设置变量
	m_wColumnInfoSize=0;
	m_wOnLineInfoSize=0;
	memset(&m_ColumnInfo,0,sizeof(m_ColumnInfo));
	memset(&m_OnLineCountInfo,0,sizeof(m_OnLineCountInfo));

	return true;
}

//事件处理接口
bool __cdecl CAttemperEngineSink::OnAttemperEvent(WORD wIdentifier, void * pDataBuffer, WORD wDataSize, DWORD dwInsertTime)
{
	switch (wIdentifier)
	{
	case EVENT_CENTER_CONNECT:	//中心连接事件
		{
			//效验大小
			ASSERT(wDataSize==sizeof(NTY_CenterConnect));
			if (wDataSize!=sizeof(NTY_CenterConnect)) return false;

			//消息处理
			NTY_CenterConnect * pCenterSocketConnect=(NTY_CenterConnect *)pDataBuffer;

			return OnEventCenterSocketConnect(pCenterSocketConnect->iErrorCode);
		}
	case EVENT_CENTER_READ:		//中心读取事件
		{
			//效验大小
			NTY_CenterRead * pCenterSocketRead=(NTY_CenterRead *)pDataBuffer;
			ASSERT(wDataSize>=((sizeof(NTY_CenterRead)-sizeof(pCenterSocketRead->cbReadBuffer))));
			ASSERT(wDataSize==(sizeof(NTY_CenterRead)-sizeof(pCenterSocketRead->cbReadBuffer)+pCenterSocketRead->wDataSize));
			if (wDataSize<(sizeof(NTY_CenterRead)-sizeof(pCenterSocketRead->cbReadBuffer))) return false;
			if (wDataSize!=sizeof(NTY_CenterRead)-sizeof(pCenterSocketRead->cbReadBuffer)+pCenterSocketRead->wDataSize) return false;

			//处理消息
			bool bSuccess=false;
			try 
			{ 
				bSuccess=OnEventCenterSocketRead(pCenterSocketRead->Command,pCenterSocketRead->cbReadBuffer,pCenterSocketRead->wDataSize);
			}
			catch (...)	{ }
			if (bSuccess==false) m_pCenterSocket->CloseSocket(true);

			return true;
		}
	case EVENT_CENTER_CLOSE:		//中心关闭事件
		{
			//效验大小
			ASSERT(wDataSize==sizeof(NTY_CenterClose));
			if (wDataSize!=sizeof(NTY_CenterClose)) return false;

			//消息处理
			NTY_CenterClose * pCenterSocketClose=(NTY_CenterClose *)pDataBuffer;
			OnEventCenterSocketClose(pCenterSocketClose->bCloseByServer);

			return true;
		}
	}

	return false;
}

//发送状态
bool __cdecl CAttemperEngineSink::SendTableStatus(WORD wTableID)
{
	//效验参数
	ASSERT(wTableID<m_pGameServiceOption->wTableCount);
	if (wTableID>=m_pGameServiceOption->wTableCount) return false;

	//构造变量
	CMD_GR_TableStatus TableStatus;
	memset(&TableStatus,0,sizeof(TableStatus));
	TableStatus.wTableID=wTableID;
	TableStatus.bTableLock=(m_pTableFrame+wTableID)->IsTableLocked()?TRUE:FALSE;
	TableStatus.bPlayStatus=(m_pTableFrame+wTableID)->IsGameStarted()?TRUE:FALSE;

	//发送数据
	m_pITCPSocketEngine->SendDataBatch(MDM_GR_STATUS,SUB_GR_TABLE_STATUS,&TableStatus,sizeof(TableStatus));
	m_AndroidUserManager.SendDataToClient(MDM_GR_STATUS,SUB_GR_TABLE_STATUS,&TableStatus,sizeof(TableStatus));

	return true;
}

//发送分数
bool __cdecl CAttemperEngineSink::SendUserScore(IServerUserItem * pIServerUserItem)
{
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();

	//发送数据
	CMD_GR_UserScore UserScore;
	UserScore.dwUserID=pUserData->dwUserID;
	UserScore.UserScore=pUserData->UserScoreInfo;
	UserScore.UserScore.lScore=pUserData->UserScoreInfo.lScore+pUserData->lStorageScore;
	m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_SCORE,&UserScore,sizeof(UserScore));
	m_AndroidUserManager.SendDataToClient(MDM_GR_USER,SUB_GR_USER_SCORE,&UserScore,sizeof(UserScore));

	return true;
}

//发送状态
bool __cdecl CAttemperEngineSink::SendUserStatus(IServerUserItem* pIServerUserItem)
{
	//效验参数
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(pIServerUserItem->IsActive()==true);
	if(pIServerUserItem->IsActive()==false)
		return	false;

	//变量定义
	CMD_GR_UserStatus	UserStatus;
	memset(&UserStatus, 0, sizeof(UserStatus));
	tagServerUserData*	pUserData	= pIServerUserItem->GetUserData();

	//构造数据
	UserStatus.dwUserID		= pUserData->dwUserID;
	UserStatus.wTableID		= pUserData->wTableID;
	UserStatus.wChairID		= pUserData->wChairID;
	UserStatus.cbUserStatus = pUserData->cbUserStatus;

	//发送数据
	m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_STATUS,&UserStatus,sizeof(UserStatus));
	m_AndroidUserManager.SendDataToClient(MDM_GR_USER,SUB_GR_USER_STATUS,&UserStatus,sizeof(UserStatus));

	return true;
}

//删除用户
bool __cdecl CAttemperEngineSink::DeleteUserItem(IServerUserItem * pIServerUserItem)
{
	//效验参数
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem==NULL) return false;

	//效验状态
	ASSERT(pIServerUserItem->GetTableID()==INVALID_TABLE);
	ASSERT(pIServerUserItem->GetChairID()==INVALID_CHAIR);

	//写入积分
	DBR_GR_LeaveGameServer LeaveGameServer;
	memset(&LeaveGameServer,0,sizeof(LeaveGameServer));
	LeaveGameServer.dwUserID=pIServerUserItem->GetUserID();
	LeaveGameServer.dwClientIP=pIServerUserItem->GetClientIP();
	LeaveGameServer.dwPlayTimeCount=pIServerUserItem->GetPlayTimeCount();
	LeaveGameServer.dwOnlineTimeCount=pIServerUserItem->GetOnlineTimeCount();
	pIServerUserItem->GetUserScoreInfo(LeaveGameServer.ScoreModifyInfo);
	m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LEAVE_GAME_SERVER,0,0,&LeaveGameServer,sizeof(LeaveGameServer));

	//发送状态
	CMD_GR_UserStatus UserStatus;
	memset(&UserStatus,0,sizeof(UserStatus));
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();
	UserStatus.dwUserID=pIServerUserItem->GetUserID();
	UserStatus.wTableID=INVALID_TABLE;
	UserStatus.wChairID=INVALID_CHAIR;
	UserStatus.cbUserStatus=US_NULL;
	m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_STATUS,&UserStatus,sizeof(UserStatus));
	m_AndroidUserManager.SendDataToClient(MDM_GR_USER,SUB_GR_USER_STATUS,&UserStatus,sizeof(UserStatus));

	//常规连接
	WORD wBindIndex=pIServerUserItem->GetUserIndex();
	if (wBindIndex<m_pGameServiceOption->wMaxConnect)
	{
		(m_pNormalParameter+wBindIndex)->pIServerUserItem=NULL;
	}
	else if ((wBindIndex>=INDEX_ANDROID)&&(wBindIndex<(INDEX_ANDROID+MAX_ANDROID)))
	{
		(m_pAndroidParameter+(wBindIndex-INDEX_ANDROID))->pIServerUserItem=NULL;
	}
	else
	{
		ASSERT(FALSE);
	}

	//删除用户
	m_ServerUserManager.DeleteUserItem(pIServerUserItem);

	return true;
}

//发送数据
bool __cdecl CAttemperEngineSink::SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID)
{
	//效验参数
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(pIServerUserItem->IsActive()==true);
	if (pIServerUserItem->IsActive()==false) return false;

	//发送数据
	WORD wIndex=pIServerUserItem->GetUserIndex();
	if (wIndex!=0xFFFF)
	{
		tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wIndex);
		if (wIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wIndex,pConnectItemInfo->wRoundID);
			m_AndroidUserManager.SendDataToClient(dwID,wMainCmdID,wSubCmdID,NULL,0);
		}
		else
		{
			m_pITCPSocketEngine->SendData(wIndex,pConnectItemInfo->wRoundID,wMainCmdID,wSubCmdID);
		}
	}

	return true;
}

//发送数据
bool __cdecl CAttemperEngineSink::SendData(IServerUserItem * pIServerUserItem, WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
	//效验参数
	ASSERT(pIServerUserItem!=NULL);
	ASSERT(pIServerUserItem->IsActive()==true);
	if (pIServerUserItem->IsActive()==false) return false;

	//发送数据
	WORD wIndex=pIServerUserItem->GetUserIndex();
	if (wIndex!=0xFFFF)
	{
		tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wIndex);
		if (wIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wIndex,pConnectItemInfo->wRoundID);
			m_AndroidUserManager.SendDataToClient(dwID,wMainCmdID,wSubCmdID,pData,wDataSize);
		}
		else
		{
			m_pITCPSocketEngine->SendData(wIndex,pConnectItemInfo->wRoundID,wMainCmdID,wSubCmdID,pData,wDataSize);
		}
	}

	return true;
}

//设置定时器
bool __cdecl CAttemperEngineSink::SetTableTimer(WORD wTableID, DWORD dwTimerID, DWORD dwElapse, DWORD dwRepeat, WPARAM wBindParam)
{
	//效验参数
	ASSERT(dwTimerID<RANGE_TABLE_TIME);
	ASSERT(wTableID<m_pGameServiceOption->wTableCount);

	//设置定时器
	if (wTableID>=m_pGameServiceOption->wTableCount) return false;
	DWORD dwTableTimeID=IDI_TABLE_FRAME_START+wTableID*RANGE_TABLE_TIME+dwTimerID;
	return m_pITimerEngine->SetTimer(dwTableTimeID,dwElapse,dwRepeat,wBindParam);
}

//删除定时器
bool __cdecl CAttemperEngineSink::KillTableTimer(WORD wTableID, DWORD dwTimerID)
{
	//效验参数
	ASSERT(dwTimerID<RANGE_TABLE_TIME);
	ASSERT(wTableID<m_pGameServiceOption->wTableCount);

	//删除定时器
	if (wTableID>=m_pGameServiceOption->wTableCount) return false;
	DWORD dwTableTimeID=IDI_TABLE_FRAME_START+wTableID*RANGE_TABLE_TIME+dwTimerID;
	return m_pITimerEngine->KillTimer(dwTableTimeID);
}

//输出信息
void __cdecl CAttemperEngineSink::ExportInformation(LPCTSTR pszString, enTraceLevel TraceLevel)
{
	if (m_pIEventService!=NULL) m_pIEventService->ShowEventNotify(pszString,TraceLevel);
	return;
}

//设置事件
bool CAttemperEngineSink::SetEventService(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pIEventService=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IEventService);
	ASSERT(m_pIEventService!=NULL);

	return (m_pIEventService!=NULL);
}

//配置函数
bool CAttemperEngineSink::InitAttemperSink(tagAttemperSinkParameter * pAttemperSinkParameter, IUnknownEx * pIUnknownEx)
{
	//效验参数
	ASSERT(pIUnknownEx!=NULL);
	ASSERT(pAttemperSinkParameter!=NULL);

	//设置变量
	m_pCenterSocket=pAttemperSinkParameter->pCenterSocket;
	m_dwCenterServer=pAttemperSinkParameter->dwCenterServer;
	m_pIAttemperEngine=pAttemperSinkParameter->pIAttemperEngine;
	m_pGameServiceAttrib=pAttemperSinkParameter->pGameServiceAttrib;
	m_pGameServiceOption=pAttemperSinkParameter->pGameServiceOption;
	m_pIGameServiceManager=pAttemperSinkParameter->pIGameServiceManager;

	//服务引擎
	IServiceEngine * pIServiceEngine=(IServiceEngine *)pIUnknownEx->QueryInterface(IID_IServiceEngine,VER_IServiceEngine);
	if (pIServiceEngine==NULL)
	{
		ExportInformation(TEXT("获取服务引擎服务失败"),Level_Exception);
		return false;
	}

	//定时器引擎
	m_pITimerEngine=(ITimerEngine *)pIServiceEngine->GetTimerEngine(IID_ITimerEngine,VER_ITimerEngine);
	if (m_pITimerEngine==NULL)
	{
		ExportInformation(TEXT("获取定时器引擎服务失败"),Level_Exception);
		return false;
	}

	//网络引擎
	m_pITCPSocketEngine=(ITCPSocketEngine *)pIServiceEngine->GetTCPSocketEngine(IID_ITCPSocketEngine,VER_ITCPSocketEngine);
	if (m_pITCPSocketEngine==NULL)
	{
		ExportInformation(TEXT("获取网络引擎服务失败"),Level_Exception);
		return false;
	}

	//数据库引擎
	IDataBaseEngine * pIDataBaseEngine=(IDataBaseEngine *)pIServiceEngine->GetDataBaseEngine(IID_IDataBaseEngine,VER_IDataBaseEngine);
	if (pIDataBaseEngine==NULL)
	{
		ExportInformation(TEXT("获取数据库引擎服务失败"),Level_Exception);
		return false;
	}

	//数据库触发
	IUnknownEx * pIQueueService=(IUnknownEx *)pIDataBaseEngine->GetQueueService(IID_IUnknownEx,VER_IUnknownEx);
	if (m_DataBaseEvent.SetQueueService(pIQueueService)==false)
	{
		ExportInformation(TEXT("获取数据库触发服务失败"),Level_Exception);
		return false;
	}

	return true;
}

//发送登录失败
bool CAttemperEngineSink::SendLogonFailed(WORD wIndex, WORD wRoundID, LPCTSTR pszMessage, LONG lErrorCode)
{
	//构造数据
	CMD_GR_LogonError LogonError;
	LogonError.lErrorCode=lErrorCode;
	lstrcpyn(LogonError.szErrorDescribe,pszMessage,sizeof(LogonError.szErrorDescribe));
	WORD wDescribeSize=CountString(LogonError.szErrorDescribe);

	//发送数据
	WORD wSendSize=sizeof(LogonError)-sizeof(LogonError.szErrorDescribe)+wDescribeSize;
	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
		m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_LOGON,SUB_GR_LOGON_ERROR,&LogonError,wSendSize);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_LOGON,SUB_GR_LOGON_ERROR,&LogonError,wSendSize);

	return true;
}

//发送房间消息
bool CAttemperEngineSink::SendRoomMessage(WORD wIndex, WORD wRoundID, LPCTSTR lpszMessage, WORD wMessageType)
{
	//构造数据包
	CMD_GR_Message Message;
	Message.wMessageType=wMessageType;
	lstrcpyn(Message.szContent,lpszMessage,CountArray(Message.szContent));
	Message.wMessageLength=CountString(Message.szContent);

	//发送数据
	WORD wSendSize=sizeof(Message)-sizeof(Message.szContent)+Message.wMessageLength*sizeof(TCHAR);
	if (wIndex==INDEX_ALL_SOCKET)
	{
		m_pITCPSocketEngine->SendDataBatch(MDM_GR_SYSTEM,SUB_GR_MESSAGE,&Message,wSendSize);
		m_AndroidUserManager.SendDataToClient(MDM_GR_SYSTEM,SUB_GR_MESSAGE,&Message,wSendSize);
	}
	else
	{
		if (wIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wIndex,wRoundID);
			m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_SYSTEM,SUB_GR_MESSAGE,&Message,wSendSize);
		}
		else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_SYSTEM,SUB_GR_MESSAGE,&Message,wSendSize);
	}

	return true;
}

//发送游戏消息
bool CAttemperEngineSink::SendGameMessage(WORD wIndex, WORD wRoundID, LPCTSTR lpszMessage, WORD wMessageType)
{
	//构造数据包
	CMD_GF_Message Message;
	Message.wMessageType=wMessageType;
	lstrcpyn(Message.szContent,lpszMessage,CountArray(Message.szContent));
	Message.wMessageLength=CountString(Message.szContent);

	//发送数据
	WORD wSendSize=sizeof(Message)-sizeof(Message.szContent)+Message.wMessageLength*sizeof(TCHAR);
	if (wIndex==INDEX_ALL_SOCKET)
	{
		m_pITCPSocketEngine->SendDataBatch(MDM_GF_FRAME,SUB_GF_MESSAGE,&Message,wSendSize);
		m_AndroidUserManager.SendDataToClient(MDM_GF_FRAME,SUB_GF_MESSAGE,&Message,wSendSize);
	}
	else
	{
		if (wIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wIndex,wRoundID);
			m_AndroidUserManager.SendDataToClient(dwID,MDM_GF_FRAME,SUB_GF_MESSAGE,&Message,wSendSize);
		}
		else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GF_FRAME,SUB_GF_MESSAGE,&Message,wSendSize);
	}

	return true;
}

//发送房间消息
bool CAttemperEngineSink::SendRoomMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)
{
	//效验用户
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem==NULL) return false;

	//发送数据
	WORD wIndex=pIServerUserItem->GetUserIndex();
	if (wIndex!=0xFFFF)
	{
		tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wIndex);
		SendRoomMessage(wIndex,pConnectItemInfo->wRoundID,lpszMessage,wMessageType);
		return true;
	}

	return false;
}

//发送游戏消息
bool CAttemperEngineSink::SendGameMessage(IServerUserItem * pIServerUserItem, LPCTSTR lpszMessage, WORD wMessageType)
{
	//效验用户
	ASSERT(pIServerUserItem!=NULL);
	if (pIServerUserItem==NULL) return false;

	//用户过滤
	if ((pIServerUserItem->GetTableID()==INVALID_TABLE)||(pIServerUserItem->GetChairID()==INVALID_CHAIR)) return false;

	//发送数据
	WORD wIndex=pIServerUserItem->GetUserIndex();
	if (wIndex!=0xFFFF)
	{
		tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wIndex);
		SendGameMessage(wIndex,pConnectItemInfo->wRoundID,lpszMessage,wMessageType);

		return true;
	}

	return false;
}

//定时器事件
bool __cdecl CAttemperEngineSink::OnEventTimer(DWORD dwTimerID, WPARAM wBindParam)
{
	//内核定时器
	if ((dwTimerID>=IDI_ATTEMPER_START)&&(dwTimerID<=IDI_ATTEMPER_CONCLUDE))
	{
		switch (dwTimerID)
		{
		case IDI_CONNECT_CENTER_SERVER:		//连接服务器
			{
				m_pCenterSocket->Connect(m_dwCenterServer,PORT_CENTER_SERVER);
				return true;
			}
		case IDI_UPDATE_SERVER_LIST:		//更新列表
			{
				if (m_SocketState==SocketState_Connected)
				{
					m_pCenterSocket->SendData(MDM_CS_SERVER_LIST,SUB_CS_GET_SERVER_LIST,NULL,0);
				}
				return true;
			}
		case IDI_UPDATE_ONLINE_COUNT:		//更新人数
			{
				if (m_SocketState==SocketState_Connected)
				{
					CMD_CS_ServerOnLineCount ServerOnLineCount;
					ServerOnLineCount.wKindID=m_pGameServiceOption->wKindID;
					ServerOnLineCount.wServerID=m_pGameServiceOption->wServerID;
					ServerOnLineCount.dwOnLineCount=(m_ServerUserManager.GetOnLineCount()+m_ServerUserManager.GetOffLineCount());
					m_pCenterSocket->SendData(MDM_CS_SERVER_MANAGER,SUB_CS_SERVER_ONLINE_COUNT,&ServerOnLineCount,sizeof(ServerOnLineCount));
				}

				return true;
			}
		case IDI_SEND_SYSTEM_MESSAGE:		//系统消息
			{
				//获取目录
				TCHAR szPath[MAX_PATH]=TEXT("");
				GetCurrentDirectory(sizeof(szPath),szPath);

				//读取配置
				TCHAR szFileName[MAX_PATH],szMessage[1024];
				_snprintf(szFileName,sizeof(szFileName),TEXT("%s\\GameService.ini"),szPath);
				
				//循环消息
				TCHAR szRoomMsgName[64],szGameMsgName[64];
				_snprintf(szRoomMsgName,sizeof(szRoomMsgName),TEXT("RoomMessage%d"),m_cbRoomMsgIndex++);
				_snprintf(szGameMsgName,sizeof(szGameMsgName),TEXT("GameMessage%d"),m_cbGameMsgIndex++);

				//系统消息
				GetPrivateProfileString(TEXT("Message"),szRoomMsgName,TEXT(""),szMessage,sizeof(szMessage),szFileName);
				if (szMessage[0]!=0) SendRoomMessage(INDEX_ALL_SOCKET,0,szMessage,SMT_INFO);
				else m_cbRoomMsgIndex=0;

				//游戏消息
				GetPrivateProfileString(TEXT("Message"),szGameMsgName,TEXT(""),szMessage,sizeof(szMessage),szFileName);
				if (szMessage[0]!=0) SendGameMessage(INDEX_ALL_SOCKET,0,szMessage,SMT_INFO);
				else m_cbGameMsgIndex=0;

				return true;
			}
		case IDI_LOAD_ANDROID_INFO:		//加载用户
			{
				//投递请求
				m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LOAD_ANDROID,0,0,NULL,0);

				return true;
			}
		case IDI_DISTRIBUTE_ANDROID:	//分配用户
			{
				//用户统计
				tagAndroidUserStatus AndroidUserStatus;
				WORD wAndroidCount=GetAndroidUserStatus(AndroidUserStatus);
				WORD wAndroidBusyCount=AndroidUserStatus.wPlayUserCount+AndroidUserStatus.wSitdownUserCount;

				//动作处理
				if (wAndroidCount>0)
				{
					//分析变量
					tagTableUserStatus TableUserStatus;
					ZeroMemory(&TableUserStatus,sizeof(TableUserStatus));

					//陪打处理
					if (AndroidUserStatus.wFreeUserCount>0)
					{
						for (INT_PTR i=0;i<m_pGameServiceOption->wTableCount;i++)
						{
							//获取桌子
							CTableFrame * pTableFrame=(m_pTableFrame+i);
							if (pTableFrame->IsGameStarted()==true) continue;

							//桌子状况
							WORD wUserSitCount=GetTableUserStatus(pTableFrame,TableUserStatus);

							//数目过虑
							if (wUserSitCount==0) continue;
							if (TableUserStatus.wTableUserCount==0) continue;
							if (wUserSitCount>=TableUserStatus.wLessUserCount) continue;

							//提取空位
							IServerUserItem * pIServerUserItem=NULL;
							WORD wChairID=pTableFrame->GetNullChairID();

							//坐下处理
							for (WORD j=0;j<AndroidUserStatus.wFreeUserCount;j++)
							{
								pIServerUserItem=AndroidUserStatus.pServerUserFree[j];
								if (pTableFrame->PerformSitDownAction(wChairID,pIServerUserItem)==true) return true;
							}
						}
					}

					//起立处理
					if (AndroidUserStatus.wSitdownUserCount>0)
					{
						for (INT_PTR i=0;i<m_pGameServiceOption->wTableCount;i++)
						{
							//获取桌子
							CTableFrame * pTableFrame=(m_pTableFrame+i);
							if (pTableFrame->IsGameStarted()==true) continue;

							//桌子状况
							GetTableUserStatus(pTableFrame,TableUserStatus);

							//用户过虑
							if (TableUserStatus.wTableUserCount>0) continue;
							if (TableUserStatus.wTableAndroidCount==0) continue;

							//起立处理
							for (WORD j=0;j<pTableFrame->GetChairCount();j++)
							{
								IServerUserItem * pIServerUserItem=pTableFrame->GetServerUserItem(j);
								if (pIServerUserItem==NULL) continue;
								if (pTableFrame->PerformStandUpAction(pIServerUserItem)==true) return true;
							}
						}
					}
				}

				return true;
			}
		}

		return false;
	}

	//机器定时器
	if ((dwTimerID>=IDI_ANDROID_START)&&(dwTimerID<=IDI_ANDROID_CONCLUDE))
	{
		//时间处理
		m_AndroidUserManager.OnEventTimerPulse(dwTimerID,wBindParam);

		return false;
	}

	//桌子定时器
	if (dwTimerID>=IDI_TABLE_FRAME_START)
	{
		//变量定义
		WORD wTableID=(WORD)((dwTimerID-IDI_TABLE_FRAME_START)/RANGE_TABLE_TIME);
		DWORD dwTableTimeID=(DWORD)((dwTimerID-IDI_TABLE_FRAME_START)%RANGE_TABLE_TIME);

		//定时器处理
		ASSERT(wTableID<m_pGameServiceOption->wTableCount);
		return (m_pTableFrame+wTableID)->OnEventTimer(dwTableTimeID,wBindParam);
	}

	return false;
}

//数据库事件
bool __cdecl CAttemperEngineSink::OnEventDataBase(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	switch (pDataBaseEvent->wRequestID)
	{
	case DBR_GR_LOGON_SUCCESS:		//登录成功
		{
			return OnDBLogonSuccess(pDataBuffer,wDataSize,pDataBaseEvent);
		}
	case DBR_GR_LOGON_ERROR:		//登录失败
		{
			return OnDBLogonError(pDataBuffer,wDataSize,pDataBaseEvent);
		}
	case DBR_GR_ANDROID_USER:	//机器信息
		{
			return OnDBAndroidUser(pDataBuffer,wDataSize,pDataBaseEvent);
		}
	case DBR_GR_SEND_GIFT_RESULT:	//赠送结果
		{
			return OnDBSendGiftResult(pDataBuffer,wDataSize,pDataBaseEvent);
		}
	}

	return false;
}

//用户登录成功
bool CAttemperEngineSink::OnDBLogonSuccess(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	//效验参数
	ASSERT(pDataBaseEvent->wRequestID==DBR_GR_LOGON_SUCCESS);
	ASSERT(wDataSize==sizeof(DBR_GR_LogonSuccess));
	if (wDataSize!=sizeof(DBR_GR_LogonSuccess)) return false;

	//判断在线
	tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pDataBaseEvent->wIndex);
	if (pConnectItemInfo==NULL) return true;
	if (pConnectItemInfo->bConnect==false) return true;
	if (pConnectItemInfo->wRoundID!=pDataBaseEvent->wRoundID) return true;
	ASSERT(pConnectItemInfo->pIServerUserItem==NULL);

	//消息处理
	DBR_GR_LogonSuccess * pLogonSuccess=(DBR_GR_LogonSuccess *)pDataBuffer;

	//在线判断
	IServerUserItem * pIServerUserItem=m_ServerUserManager.SearchOnLineUser(pLogonSuccess->dwUserID);
	if (pIServerUserItem!=NULL) return false;

	//变量定义
	WORD wIndex=pDataBaseEvent->wIndex;
	WORD wRoundID=pDataBaseEvent->wRoundID;

	//状态判断
	if ((m_bAllowEnterRoom==false)&&(pLogonSuccess->dwMasterRight==0L))
	{
		//发送消息
		LPCTSTR pszMessage=TEXT("抱歉，由于系统维护的原因，本游戏房间不允许任何玩家登录进入！");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_EJECT|SMT_INFO|SMT_INTERMIT_LINE|SMT_CLOSE_ROOM);

		//解除锁定
		DBR_GR_LeaveGameServer LeaveGameServer;
		ZeroMemory(&LeaveGameServer,sizeof(LeaveGameServer));
		LeaveGameServer.dwUserID=pLogonSuccess->dwUserID;
		LeaveGameServer.dwClientIP=pConnectItemInfo->dwClientIP;
		m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LEAVE_GAME_SERVER,0,0,&LeaveGameServer,sizeof(LeaveGameServer));

		return true;
	}

	//判断数目
	DWORD dwUserCount=m_ServerUserManager.GetOnLineCount()+m_ServerUserManager.GetOffLineCount();
	if ((pLogonSuccess->cbMemberOrder==0)&&(pLogonSuccess->cbMasterOrder==0)&&((dwUserCount+50L)>=m_pGameServiceOption->wMaxConnect))
	{
		//发送消息
		LPCTSTR pszMessage=TEXT("抱歉，本游戏房间已经满人，禁止非会员玩家登录进入！");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_EJECT|SMT_INFO|SMT_INTERMIT_LINE|SMT_CLOSE_ROOM);

		//解除锁定
		DBR_GR_LeaveGameServer LeaveGameServer;
		ZeroMemory(&LeaveGameServer,sizeof(LeaveGameServer));
		LeaveGameServer.dwUserID=pLogonSuccess->dwUserID;
		LeaveGameServer.dwClientIP=pConnectItemInfo->dwClientIP;
		m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LEAVE_GAME_SERVER,0,0,&LeaveGameServer,sizeof(LeaveGameServer));

		return true;
	}

	//构造用户信息
	tagServerUserData ServerUserData;
	memset(&ServerUserData,0,sizeof(ServerUserData));
	ServerUserData.wFaceID=pLogonSuccess->wFaceID;
	ServerUserData.cbGender=pLogonSuccess->cbGender;
	ServerUserData.dwUserID=pLogonSuccess->dwUserID;
	ServerUserData.dwGameID=pLogonSuccess->dwGameID;
	ServerUserData.dwGroupID=pLogonSuccess->dwGroupID;
	ServerUserData.dwUserRight=pLogonSuccess->dwUserRight;
	ServerUserData.dwMasterRight=pLogonSuccess->dwMasterRight;
	ServerUserData.cbMemberOrder=pLogonSuccess->cbMemberOrder;
	ServerUserData.cbMasterOrder=pLogonSuccess->cbMasterOrder;
	ServerUserData.UserScoreInfo.lWinCount=pLogonSuccess->lWinCount;
	ServerUserData.UserScoreInfo.lLostCount=pLogonSuccess->lLostCount;
	ServerUserData.UserScoreInfo.lDrawCount=pLogonSuccess->lDrawCount;
	ServerUserData.UserScoreInfo.lFleeCount=pLogonSuccess->lFleeCount;
	ServerUserData.UserScoreInfo.lExperience=pLogonSuccess->lExperience;
	lstrcpyn(ServerUserData.szAccounts,pLogonSuccess->szAccounts,CountArray(ServerUserData.szAccounts));
	lstrcpyn(ServerUserData.szGroupName,pLogonSuccess->szGroupName,CountArray(ServerUserData.szGroupName));
	lstrcpyn(ServerUserData.szUnderWrite,pLogonSuccess->szUnderWrite,CountArray(ServerUserData.szUnderWrite));

	//提取积分
	ServerUserData.lStorageScore=0L;
	ServerUserData.UserScoreInfo.lScore=pLogonSuccess->lScore;

	//存储积分
	if ((m_pGameServiceOption->wServerType==GAME_GENRE_GOLD)&&(m_pGameServiceOption->lRestrictScore>0L))
	{
		if (pLogonSuccess->lScore>m_pGameServiceOption->lRestrictScore)
		{
			ServerUserData.UserScoreInfo.lScore=m_pGameServiceOption->lRestrictScore;
			ServerUserData.lStorageScore=pLogonSuccess->lScore-m_pGameServiceOption->lRestrictScore;
		}
	}

	//状态信息
	ServerUserData.cbUserStatus=US_FREE;
	ServerUserData.wTableID=INVALID_TABLE;
	ServerUserData.wChairID=INVALID_CHAIR;

	//激活用户
	pConnectItemInfo->wRoundID=wRoundID;
	pConnectItemInfo->pIServerUserItem=m_ServerUserManager.ActiveUserItem(ServerUserData,pConnectItemInfo->dwClientIP,wIndex,pLogonSuccess->szPassWord);

	//发送房间信息
	SendGameServerInfo(pConnectItemInfo->pIServerUserItem,wIndex,wRoundID);

	//广播用户信息
	SendUserItem(pConnectItemInfo->pIServerUserItem,INDEX_ALL_SOCKET,0xFFFF);

	//发送消息
	LPCTSTR pszMessage=TEXT("亲爱的用户，欢迎你多提宝贵建议！");
	SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_INFO);

	//练习判断
	if (m_pGameServiceOption->wServerType&GAME_GENRE_EDUCATE)
	{
		LPCTSTR pszMessage=TEXT("请注意，这是游戏练习房间，你将得到一定数目的模拟游戏币，游戏成绩将不会记录到数据库！");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_INFO);
	}

	//比赛判断
	if (m_pGameServiceOption->wServerType&GAME_GENRE_MATCH)
	{
		LPCTSTR pszMessage=TEXT("请注意，这是游戏比赛房间，非比赛选手将不能在此房间进行游戏！");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_INFO);
	}

	//发送消息
	if (m_bShallClose==true)
	{
		LPCTSTR pszMessage=TEXT("请注意，由于需要进行游戏房间维护更新工作，此游戏房间即将暂停服务！");
		SendRoomMessage(wIndex,wRoundID,pszMessage,SMT_INFO);
	}

	//设置群发
	if (wIndex<INDEX_ANDROID) m_pITCPSocketEngine->AllowBatchSend(wIndex,wRoundID,true);

	return true;
}

//用户登录失败
bool CAttemperEngineSink::OnDBLogonError(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	//效验参数
	ASSERT(pDataBaseEvent->wRequestID==DBR_GR_LOGON_ERROR);
	ASSERT(wDataSize==sizeof(DBR_GR_LogonError));

	//判断在线
	tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pDataBaseEvent->wIndex);
	if (pConnectItemInfo==NULL) return true;
	if (pConnectItemInfo->bConnect==false) return true;
	if (pConnectItemInfo->wRoundID!=pDataBaseEvent->wRoundID) return true;

	//发送消息
	DBR_GR_LogonError * pLogonError=(DBR_GR_LogonError *)pDataBuffer;
	pLogonError->szErrorDescribe[CountString(pLogonError->szErrorDescribe)-1]=0;
	SendLogonFailed(pDataBaseEvent->wIndex,pDataBaseEvent->wRoundID,pLogonError->szErrorDescribe,pLogonError->lErrorCode);

	if (pDataBaseEvent->wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(pDataBaseEvent->wIndex,pConnectItemInfo->wRoundID);
		m_AndroidUserManager.DeleteAndroidUserItem(dwID);
	}
	else m_pITCPSocketEngine->ShutDownSocket(pDataBaseEvent->wIndex,pDataBaseEvent->wRoundID);

	return true;
}

//用户信息
bool CAttemperEngineSink::OnDBAndroidUser(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	//变量定义
	DBO_GR_AndroidUser * pAndroidUser=(DBO_GR_AndroidUser *)pDataBuffer;
	WORD wHeadSize=sizeof(DBO_GR_AndroidUser)-sizeof(pAndroidUser->dwAndroidID);

	//效验参数
	ASSERT((wDataSize>=wHeadSize)&&(wDataSize==(wHeadSize+pAndroidUser->wAndroidCount*sizeof(DWORD))));
	if ((wDataSize<wHeadSize)||(wDataSize!=(wHeadSize+pAndroidUser->wAndroidCount*sizeof(DWORD)))) return false;

	//设置用户
	if (pAndroidUser->lResultCode==0)
	{
		m_AndroidUserManager.SetAndroidStock(pAndroidUser->dwAndroidID,pAndroidUser->wAndroidCount);
	}

	//设置时间
	m_pITimerEngine->SetTimer(IDI_LOAD_ANDROID_INFO,TIME_LOAD_ANDROID_INFO*1000L,1,NULL);

	return true;
}

//赠送结果
bool CAttemperEngineSink::OnDBSendGiftResult(void * pDataBuffer, WORD wDataSize, NTY_DataBaseEvent * pDataBaseEvent)
{
	//效验参数
	ASSERT(pDataBaseEvent->wRequestID==DBR_GR_SEND_GIFT_RESULT);
	ASSERT(wDataSize==sizeof(DBR_GR_SendGiftResult));
	if (wDataSize!=sizeof(DBR_GR_SendGiftResult)) return false;

	//消息处理
	DBR_GR_SendGiftResult * pSendGiftResult=(DBR_GR_SendGiftResult *)pDataBuffer;

	//获取玩家
	IServerUserItem *pSendIServerUserItem = m_ServerUserManager.SearchOnLineUser(pSendGiftResult->dwSendUserID);
	tagServerUserData *pSendUserData = pSendIServerUserItem->GetUserData();

	//获取桌子
	CTableFrame *pTableFrame = (m_pTableFrame+pSendUserData->wTableID);

	//成功判断
	if ( pSendGiftResult->bSuccess )
	{
		//消息通知
		CMD_GF_GiftNotify GiftNotify;
		ZeroMemory( &GiftNotify, sizeof( GiftNotify ) );
		GiftNotify.dwSendUserID = pSendGiftResult->dwSendUserID;
		GiftNotify.dwRcvUserID = pSendGiftResult->dwRcvUserID;
		GiftNotify.wGiftID = pSendGiftResult->wGiftID;

		//玩家通知
		for ( WORD wChairID = 0; wChairID < m_pGameServiceAttrib->wChairCount; ++wChairID )
		{
			//获取玩家
			IServerUserItem *pPlayServerUserItem = pTableFrame->GetServerUserItem( wChairID );
			if ( pPlayServerUserItem == NULL ) continue;

			//发送消息
			SendData( pPlayServerUserItem, MDM_GF_FRAME, SUB_GF_GIFT, &GiftNotify, sizeof( GiftNotify ) );
		}

		//旁观通知
		IServerUserItem *pLookonServerUserItem = NULL;
		WORD wIndex = 0;
		do
		{
			//获取旁观
			pLookonServerUserItem = pTableFrame->EnumLookonUserItem( wIndex++ );

			//发送消息
			if ( pLookonServerUserItem != NULL ) SendData( pLookonServerUserItem, MDM_GF_FRAME, SUB_GF_GIFT, &GiftNotify, sizeof( GiftNotify ) );

		}while( pLookonServerUserItem != NULL );
	}
	else
	{
		//发送消息
		TCHAR szDescribe[128]=TEXT("");
		_snprintf(szDescribe,sizeof(szDescribe),TEXT("赠送失败！"));
		SendGameMessage(pSendIServerUserItem,szDescribe,SMT_EJECT|SMT_INFO);		
		return true;
	}

	return true;
}

//网络应答事件
bool __cdecl CAttemperEngineSink::OnEventSocketAccept(NTY_SocketAcceptEvent * pSocketAcceptEvent)
{
	tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pSocketAcceptEvent->wIndex);
	if (pConnectItemInfo==NULL) return false;

	//效验参数
	ASSERT(pConnectItemInfo->pIServerUserItem==NULL);

	//设置数据
	pConnectItemInfo->bConnect=true;
	pConnectItemInfo->wRoundID=pSocketAcceptEvent->wRoundID;
	pConnectItemInfo->dwClientIP=pSocketAcceptEvent->dwClientIP;

	return true;
}

//网络事件
bool CAttemperEngineSink::OnEventSocketRead(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:	//登录消息
		{
			return OnSocketMainLogon(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GR_USER:	//用户消息
		{
			return OnSocketMainUser(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GR_MANAGER://管理消息
		{
			return OnSocketMainManager(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GF_FRAME:	//框架消息
		{
			return OnSocketMainFrame(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GF_GAME:	//游戏消息
		{
			return OnSocketMainGame(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	case MDM_GF_VIDEO:	//视频消息
		{
			return OnSocketMainVideo(Command,pDataBuffer,wDataSize,pSocketReadEvent);
		}
	}

	return false;
}

//网络关闭事件
bool CAttemperEngineSink::OnEventSocketClose(NTY_SocketCloseEvent * pSocketCloseEvent)
{
	//用户处理
	tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pSocketCloseEvent->wIndex);
	if (pConnectItemInfo==NULL) return true;
	IServerUserItem * pIServerUserItem=pConnectItemInfo->pIServerUserItem;
	if (pIServerUserItem!=NULL)
	{
		//判断游戏
		bool bOffLine=false;
		if (pIServerUserItem->GetTableID()!=INVALID_TABLE)
		{
			//变量定义
			CTableFrame * pTableFrame=(m_pTableFrame+pIServerUserItem->GetTableID());

			//断线注册
			WORD wChairID=pIServerUserItem->GetChairID();
			if ((pTableFrame->IsUserPlaying(pIServerUserItem)==true)&&(pTableFrame->OnUserReqOffLine(wChairID)==true))
			{
				bOffLine=m_ServerUserManager.RegOffLineUserItem(pIServerUserItem);
			}

			//断线处理
			if (bOffLine==true) pTableFrame->OnUserOffLine(wChairID);
			else pTableFrame->PerformStandUpAction(pIServerUserItem);
		}

		//删除用户
		if (bOffLine==false) DeleteUserItem(pIServerUserItem);
	}

	//设置数据
	pConnectItemInfo->wRoundID++;
	pConnectItemInfo->dwClientIP=0;
	pConnectItemInfo->bConnect=false;
	pConnectItemInfo->pIServerUserItem=NULL;

	return true;
}

//中心连接事件
bool __cdecl CAttemperEngineSink::OnEventCenterSocketConnect(int iErrorCode)
{
	//错误判断
	if (iErrorCode!=0)
	{
		m_SocketState=SocketState_NoConnect;
		m_pITimerEngine->SetTimer(IDI_CONNECT_CENTER_SERVER,TIME_RECONNECT,1,NULL);
		return true;
	}

	//设置变量
	m_SocketState=SocketState_Connected;

	//注册房间
	CMD_CS_RegGameServer RegGameServer;
	memset(&RegGameServer,0,sizeof(RegGameServer));
	RegGameServer.GameServer.wSortID=0;
	RegGameServer.GameServer.wKindID=m_pGameServiceOption->wKindID;
	RegGameServer.GameServer.wServerID=m_pGameServiceOption->wServerID;
	RegGameServer.GameServer.wStationID=m_pGameServiceOption->wStationID;
	RegGameServer.GameServer.wServerPort=m_pGameServiceOption->wServerPort;
	RegGameServer.GameServer.dwServerAddr=m_pGameServiceOption->dwServerAddr;
	RegGameServer.GameServer.dwOnLineCount=(m_ServerUserManager.GetOnLineCount()+m_ServerUserManager.GetOffLineCount())*2;
	lstrcpyn(RegGameServer.GameServer.szServerName,m_pGameServiceOption->szGameRoomName,CountArray(RegGameServer.GameServer.szServerName));
	m_pCenterSocket->SendData(MDM_CS_SERVER_MANAGER,SUB_CS_REG_GAME_SERVER,&RegGameServer,sizeof(RegGameServer));

	//获取列表
	m_pCenterSocket->SendData(MDM_CS_SERVER_LIST,SUB_CS_GET_SERVER_LIST,NULL,0);

	//设置定时器
	m_pITimerEngine->SetTimer(IDI_UPDATE_SERVER_LIST,TIME_UPDATE_LIST,TIMER_REPEAT_TIMER,NULL);
	m_pITimerEngine->SetTimer(IDI_UPDATE_ONLINE_COUNT,TIME_UPDATE_ONLINE,TIMER_REPEAT_TIMER,NULL);

	return true;
}

//中心读取事件
bool __cdecl CAttemperEngineSink::OnEventCenterSocketRead(CMD_Command Command, void * pDataBuffer, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_CS_SERVER_LIST:	//列表消息
		{
			return OnCenterMainServerList(Command,pDataBuffer,wDataSize);
		}
	}
	return true;
}

//中心关闭事件
bool __cdecl CAttemperEngineSink::OnEventCenterSocketClose(bool bCloseByServer)
{
	//设置变量
	m_SocketState=SocketState_NoConnect;

	//重新连接
	m_pITimerEngine->KillTimer(IDI_UPDATE_SERVER_LIST);
	m_pITimerEngine->KillTimer(IDI_UPDATE_ONLINE_COUNT);
	m_pITimerEngine->SetTimer(IDI_CONNECT_CENTER_SERVER,TIME_RECONNECT,1,NULL);

	return true;
}

//登录消息处理
bool CAttemperEngineSink::OnSocketMainLogon(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	ASSERT(Command.wMainCmdID==MDM_GR_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_USERID:		//ID 登录
		{
			//效验参数
			ASSERT(wDataSize>=sizeof(CMD_GR_LogonByUserID));
			if (wDataSize<sizeof(CMD_GR_LogonByUserID)) return false;

			//处理消息
			CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)pDataBuffer;
			pLogonByUserID->szPassWord[CountArray(pLogonByUserID->szPassWord)-1]=0;

			//重复判断
			tagConnectItemInfo * pConnectItemInfo=GetBindParameter(pSocketReadEvent->wIndex);
			if (pConnectItemInfo==NULL) return false;
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem!=NULL) return false;

			//在线判断
			pIServerUserItem=m_ServerUserManager.SearchOnLineUser(pLogonByUserID->dwUserID);
			if (pIServerUserItem!=NULL)
			{
				//效验密码
				if (lstrcmp(pIServerUserItem->GetPassword(),pLogonByUserID->szPassWord)!=0)
				{
					TCHAR szMessage[]=TEXT("帐户密码有误，请查证后再次尝试登录！");
					SendLogonFailed(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,szMessage,0);

					if (pSocketReadEvent->wIndex>=INDEX_ANDROID)
					{
						DWORD dwID=MAKELONG(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);
						m_AndroidUserManager.DeleteAndroidUserItem(dwID);
					}
					else m_pITCPSocketEngine->ShutDownSocket(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);

					return true;
				}

				//发送通知
				WORD wSourceIndex=pIServerUserItem->GetUserIndex();
				tagConnectItemInfo * pConnectItemInfo=GetBindParameter(wSourceIndex);
				if (pConnectItemInfo!=NULL)
				{
					WORD wSourceRoundID=pConnectItemInfo->wRoundID;
					LPCTSTR pszMessage=TEXT("请注意，你的帐号在另一地方进入此游戏房间了，你被迫离开！");
					SendRoomMessage(wSourceIndex,wSourceRoundID,pszMessage,SMT_INFO|SMT_EJECT|SMT_GLOBAL|SMT_CLOSE_ROOM);

					//断开原用户
					pConnectItemInfo->pIServerUserItem=NULL;

					if (wSourceIndex>=INDEX_ANDROID)
					{
						DWORD dwID=MAKELONG(wSourceIndex,wSourceRoundID);
						m_AndroidUserManager.DeleteAndroidUserItem(dwID);
					}
					else m_pITCPSocketEngine->ShutDownSocket(wSourceIndex,wSourceRoundID);
				}

				//激活新用户
				pConnectItemInfo->pIServerUserItem=pIServerUserItem;
				pConnectItemInfo->wRoundID=pSocketReadEvent->wRoundID;
				m_ServerUserManager.SwitchOnLineUserItem(pIServerUserItem,pConnectItemInfo->dwClientIP,pSocketReadEvent->wIndex);

				//发送房间信息
				SendGameServerInfo(pIServerUserItem,pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);

				//设置群发
				if (pSocketReadEvent->wIndex<INDEX_ANDROID)
				{
					m_pITCPSocketEngine->AllowBatchSend(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,true);
				}

				return true;
			}

			//断线判断
			pIServerUserItem=m_ServerUserManager.SearchOffLineUser(pLogonByUserID->dwUserID);
			if (pIServerUserItem!=NULL)
			{
				//效验密码
				if (lstrcmp(pIServerUserItem->GetPassword(),pLogonByUserID->szPassWord)!=0)
				{
					TCHAR szMessage[]=TEXT("帐户密码有误，请查证后再次尝试登录！");
					SendLogonFailed(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,szMessage,0);

					if (pSocketReadEvent->wIndex>=INDEX_ANDROID)
					{
						DWORD dwID=MAKELONG(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);
						m_AndroidUserManager.DeleteAndroidUserItem(dwID);
					}
					else m_pITCPSocketEngine->ShutDownSocket(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);

					return true;
				}

				//设置用户
				pConnectItemInfo->pIServerUserItem=pIServerUserItem;
				pConnectItemInfo->wRoundID=pSocketReadEvent->wRoundID;
				m_ServerUserManager.ActiveOffLineUserItem(pIServerUserItem,pConnectItemInfo->dwClientIP,pSocketReadEvent->wIndex);

				//断线重入
				WORD wTableID=pIServerUserItem->GetTableID();
				WORD wChairID=pIServerUserItem->GetChairID();
				(m_pTableFrame+wTableID)->OnUserReConnect(wChairID);

				//发送房间信息
				SendGameServerInfo(pIServerUserItem,pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID);

				//设置群发
				if (pSocketReadEvent->wIndex<INDEX_ANDROID)
				{
					m_pITCPSocketEngine->AllowBatchSend(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,true);
				}

				return true;
			}

			//构造数据
			DBR_GR_LogonByUserID LogonByUserID;
			memset(&LogonByUserID,0,sizeof(LogonByUserID));
			LogonByUserID.dwUserID=pLogonByUserID->dwUserID;
			LogonByUserID.dwClientIP=pConnectItemInfo->dwClientIP;
			lstrcpyn(LogonByUserID.szPassWord,pLogonByUserID->szPassWord,sizeof(LogonByUserID.szPassWord));

			//变量定义
			VOID * pDataBuffer=NULL;
			tagDataDescribe DataDescribe;
			CRecvPacketHelper RecvPacket(pLogonByUserID+1,wDataSize-sizeof(CMD_GR_LogonByUserID));

			//扩展信息
			while (true)
			{
				//提取数据
				pDataBuffer=RecvPacket.GetData(DataDescribe);
				if (DataDescribe.wDataDescribe==DTP_NULL) break;

				//数据分析
				switch (DataDescribe.wDataDescribe)
				{
				case DTP_COMPUTER_ID:		//机器标识
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize==sizeof(tagClientSerial));
						if (DataDescribe.wDataSize==sizeof(tagClientSerial))
						{
							BYTE * pcbByte=(BYTE *)pDataBuffer;
							for (INT i=0;i<sizeof(tagClientSerial)/sizeof(BYTE);i++)
							{
								ASSERT(CountArray(LogonByUserID.szComputerID)>((i*2)+1));
								_stprintf(&LogonByUserID.szComputerID[i*2],TEXT("%02X"),*(pcbByte+i));
							}
						}

						break;
					}
				}
			}

			//投递数据库
			m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LOGON_BY_USERID,pSocketReadEvent->wIndex,
				pSocketReadEvent->wRoundID,&LogonByUserID,sizeof(LogonByUserID));

			return true;
		}
	}

	return false;
}

//用户消息处理
bool CAttemperEngineSink::OnSocketMainUser(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_USER);

	switch (Command.wSubCmdID)
	{
	case SUB_GR_USER_SIT_REQ:		//坐下桌子
	case SUB_GR_USER_LOOKON_REQ:	//旁观桌子
		{
			//变量定义
			CMD_GR_UserSitReq * pUserSitReq=(CMD_GR_UserSitReq *)pDataBuffer;
			WORD wHeadSize=sizeof(CMD_GR_UserSitReq)-sizeof(pUserSitReq->szTablePass);
				
			//效验数据
			ASSERT((wDataSize>=wHeadSize)&&(wDataSize<=sizeof(CMD_GR_UserSitReq)));
			if ((wDataSize<wHeadSize)||(wDataSize>sizeof(CMD_GR_UserSitReq))) return false;
			ASSERT((wHeadSize+pUserSitReq->cbPassLen)==wDataSize);
			if ((wHeadSize+pUserSitReq->cbPassLen)!=wDataSize) return false;

			//判断位置
			if (pUserSitReq->wTableID>=m_pGameServiceOption->wTableCount) return false;
			if (pUserSitReq->wChairID>=m_pGameServiceAttrib->wChairCount) return false;

			//获取用户
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//处理过虑
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if ((pUserData->wTableID==pUserSitReq->wTableID)&&(pUserData->wChairID==pUserSitReq->wChairID))
			{
				if ((pUserData->cbUserStatus!=US_LOOKON)&&(Command.wSubCmdID==SUB_GR_USER_SIT_REQ)) return true;
				if ((pUserData->cbUserStatus==US_LOOKON)&&(Command.wSubCmdID==SUB_GR_USER_LOOKON_REQ)) return true;
			}

			//离开位置
			if (pUserData->wTableID!=INVALID_TABLE)
			{
				CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
				if (pTableFrame->IsUserPlaying(pIServerUserItem)==true)
				{
					//构造数据
					CMD_GR_SitFailed SitFailed;
					memset(&SitFailed,0,sizeof(SitFailed));
					_snprintf(SitFailed.szFailedDescribe,sizeof(SitFailed.szFailedDescribe),TEXT("你正在的 [ %d ] 号游戏桌游戏，暂时不能离开位置！"),pUserData->wTableID+1);

					//发送数据
					WORD wSendSize=sizeof(SitFailed)-sizeof(SitFailed.szFailedDescribe)+CountString(SitFailed.szFailedDescribe);
					SendData(pIServerUserItem,MDM_GR_USER,SUB_GR_SIT_FAILED,&SitFailed,wSendSize);

					return true;
				}
				pTableFrame->PerformStandUpAction(pIServerUserItem);
			}

			//坐下位置
			CTableFrame * pTableFrame=(m_pTableFrame+pUserSitReq->wTableID);
			if(Command.wSubCmdID==SUB_GR_USER_SIT_REQ)	
			{
				////位置变更
				//if((m_pGameServiceAttrib->wKindID==4)||(m_pGameServiceAttrib->wKindID==14))
				//{
				//	//变更位置
				//	pUserSitReq->wChairID=1;

				//	//搜索位置
				//	for (WORD i=1;i<m_pGameServiceAttrib->wChairCount;i++)
				//	{
				//		if (pTableFrame->GetServerUserItem(i)==NULL)
				//		{
				//			pUserSitReq->wChairID=i;
				//			break;
				//		}
				//	}
				//}

				//坐下动作
				pTableFrame->PerformSitDownAction(pUserSitReq->wChairID,pIServerUserItem);
			}
			else
			{
				pTableFrame->PerformLookonAction(pUserSitReq->wChairID,pIServerUserItem);
			}

			return true;
		}
	case SUB_GR_USER_STANDUP_REQ:	//起立请求
	case SUB_GR_USER_LEFT_GAME_REQ:	//强退请求
		{
			//获取用户
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//处理过虑
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if ((pUserData->wTableID==INVALID_TABLE)||(pUserData->wChairID==INVALID_CHAIR)) return true;

			//起立位置
			CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
			if ((Command.wSubCmdID==SUB_GR_USER_STANDUP_REQ)&&(pTableFrame->IsUserPlaying(pIServerUserItem)==true))
			{
				TCHAR szMessage[256]=TEXT("");
				_snprintf(szMessage,sizeof(szMessage),TEXT("您正在的 [ %d ] 号游戏桌游戏，暂时不能离开位置！"),pUserData->wTableID+1);
				SendRoomMessage(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,szMessage,SMT_EJECT);
				return true;
			}

			//离开位置
			pTableFrame->PerformStandUpAction(pIServerUserItem);

			return true;
		}
	case SUB_GR_USER_CHAT:			//聊天消息
		{
			//效验参数
			CMD_GR_UserChat * pUserChat=(CMD_GR_UserChat *)pDataBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)));
			ASSERT(wDataSize==(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength));
			if (wDataSize<(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage))) return false;
			if (wDataSize!=(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength)) return false;

			//获取用户
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//寻找用户
			IServerUserItem * pIServerUserItemRecv=NULL;
			if (pUserChat->dwTargetUserID!=0) 
			{
				pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pUserChat->dwTargetUserID);
				if (pIServerUserItemRecv==NULL) return true;
			}

			//状态判断
			if (m_bAllowRoomChat==false)
			{
				LPCTSTR pszMessage=TEXT("抱歉，本游戏房间不允许进行大厅公聊！");
				SendRoomMessage(pIServerUserItem,pszMessage,SMT_EJECT|SMT_INFO);
				return true;
			}

			//权限判断
			if (CUserRight::CanRoomChat(pIServerUserItem->GetUserData()->dwUserRight)==false)
			{
				LPCTSTR pszMessage=TEXT("抱歉，你没有大厅公聊的权限，若需要帮助，请联系游戏客服咨询！");
				SendRoomMessage(pIServerUserItem,pszMessage,SMT_EJECT|SMT_INFO);
				return true;
			}

			//转发消息
			m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_CHAT,pUserChat,wDataSize);
			m_AndroidUserManager.SendDataToClient(MDM_GR_USER,SUB_GR_USER_CHAT,pUserChat,wDataSize);

			return true;
		}
	case SUB_GR_USER_WISPER:		//私语消息
		{
			//效验参数
			CMD_GR_Wisper * pWisper=(CMD_GR_Wisper *)pDataBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)));
			ASSERT(wDataSize==(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)+pWisper->wChatLength));
			if (wDataSize<(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage))) return false;
			if (wDataSize!=(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)+pWisper->wChatLength)) return false;

			//获取用户
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pWisper->dwTargetUserID);
			if (pIServerUserItemRecv==NULL) return true;

			//状态判断
			DWORD dwMasterRightSend=pIServerUserItemSend->GetUserData()->dwMasterRight;
			DWORD dwMasterRightRecv=pIServerUserItemRecv->GetUserData()->dwMasterRight;
			if ((m_bAllowWisper==false)&&(dwMasterRightSend==0L)&&(dwMasterRightRecv==0L))
			{
				LPCTSTR pszMessage=TEXT("抱歉，本游戏房间不能进行玩家私聊！");
				SendRoomMessage(pIServerUserItemSend,pszMessage,SMT_EJECT|SMT_INFO);
				return true;
			}

			//权限判断
			DWORD dwUserRightSend=pIServerUserItemSend->GetUserData()->dwUserRight;
			if ((dwMasterRightRecv==0L)&&(CUserRight::CanWisper(dwUserRightSend)==false))
			{
				TCHAR szMessage[256]=TEXT("你暂时没有向玩家发送私聊消息的权限，只能与管理员私聊！");
				SendRoomMessage(pSocketReadEvent->wIndex,pSocketReadEvent->wRoundID,szMessage,SMT_EJECT);
				return true;
			}

			//转发消息
			SendData(pIServerUserItemSend,MDM_GR_USER,SUB_GR_USER_WISPER,pWisper,wDataSize);
			SendData(pIServerUserItemRecv,MDM_GR_USER,SUB_GR_USER_WISPER,pWisper,wDataSize);

			return true;
		}
	case SUB_GR_USER_RULE:		//用户规则
		{
			//效验参数
			ASSERT(wDataSize==sizeof(CMD_GR_UserRule));
			if (wDataSize!=sizeof(CMD_GR_UserRule)) return false;

			//消息处理
			CMD_GR_UserRule * pUserRule=(CMD_GR_UserRule *)pDataBuffer;
			pUserRule->szPassword[CountArray(pUserRule->szPassword)-1]=0;

			//获取用户
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//构造规则
			tagUserRule UserRule;
			UserRule.bLimitWin=pUserRule->bLimitWin;
			UserRule.bPassword=pUserRule->bPassword;
			UserRule.bLimitFlee=pUserRule->bLimitFlee;
			UserRule.bLimitScore=pUserRule->bLimitScore;
			UserRule.bCheckSameIP=pUserRule->bCheckSameIP;
			UserRule.wWinRate=pUserRule->wWinRate;
			UserRule.wFleeRate=pUserRule->wFleeRate;
			UserRule.lMaxScore=pUserRule->lMaxScore;
			UserRule.lLessScore=pUserRule->lLessScore;
			lstrcpyn(UserRule.szPassword,pUserRule->szPassword,CountArray(UserRule.szPassword));

			//设置规则
			pIServerUserItem->SetUserRule(UserRule);

			return true;
		}

	case SUB_GR_USER_INVITE_REQ:		//邀请用户
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_GR_UserInviteReq));
			if (wDataSize!=sizeof(CMD_GR_UserInviteReq)) return false;

			//消息处理
			CMD_GR_UserInviteReq * pUserInviteReq=(CMD_GR_UserInviteReq *)pDataBuffer;

			//获取用户
			IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItem==NULL) return false;

			//效验状态
			if (pUserInviteReq->wTableID==INVALID_TABLE) return true;
			if (pIServerUserItem->GetTableID()!=pUserInviteReq->wTableID) return true;

			//目标用户
			IServerUserItem * pITargetUserItem=m_ServerUserManager.SearchOnLineUser(pUserInviteReq->dwUserID);
			if (pITargetUserItem==NULL) return true;

			//发送消息
			CMD_GR_UserInvite UserInvite;
			memset(&UserInvite,0,sizeof(UserInvite));
			UserInvite.wTableID=pUserInviteReq->wTableID;
			UserInvite.dwUserID=pIServerUserItem->GetUserID();
			SendData(pITargetUserItem,MDM_GR_USER,SUB_GR_USER_INVITE,&UserInvite,sizeof(UserInvite));

			return true;
		}
	}

	return true;
}

//管理消息处理
bool CAttemperEngineSink::OnSocketMainManager(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GR_MANAGER);

	//消息处理
	switch (Command.wSubCmdID)
	{
	case SUB_GR_SEND_WARNING:	//警告消息
		{
			//效验参数
			CMD_GR_SendWarning * pSendWarning=(CMD_GR_SendWarning *)pDataBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_SendWarning)-sizeof(pSendWarning->szWarningMessage)));
			ASSERT(wDataSize==(sizeof(CMD_GR_SendWarning)-sizeof(pSendWarning->szWarningMessage)+pSendWarning->wChatLength));
			if (wDataSize<(sizeof(CMD_GR_SendWarning)-sizeof(pSendWarning->szWarningMessage))) return false;
			if (wDataSize!=(sizeof(CMD_GR_SendWarning)-sizeof(pSendWarning->szWarningMessage)+pSendWarning->wChatLength)) return false;

			//管理用户
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;

			//权限判断
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (CUserRight::CanSendWarning(dwMasterRight)==false) return true;

			//目标用户
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pSendWarning->dwTargetUserID);
			if (pIServerUserItemRecv==NULL) return true;

			//发送消息
			SendGameMessage(pIServerUserItemRecv,pSendWarning->szWarningMessage,SMT_INFO);
			SendRoomMessage(pIServerUserItemRecv,pSendWarning->szWarningMessage,SMT_INFO|SMT_EJECT);

			return true;
		}
	case SUB_GR_LOOK_USER_IP:	//查看地址
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_GR_LookUserIP));
			if (wDataSize!=sizeof(CMD_GR_LookUserIP)) return false;

			//消息处理
			CMD_GR_LookUserIP * pLookUserIP=(CMD_GR_LookUserIP *)pDataBuffer;

			//管理用户
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;

			//权限判断
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (CUserRight::CanSeeUserIP(dwMasterRight)==false) return true;

			//目标用户
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pLookUserIP->dwTargetUserID);
			if (pIServerUserItemRecv==NULL) return true;

			//变量定义
			DWORD dwUserIP=pIServerUserItemRecv->GetClientIP();

			//构造信息
			TCHAR szMessage[128]=TEXT("");
			BYTE * pcbUserIP=(BYTE *)(&dwUserIP);
			_snprintf(szMessage,CountArray(szMessage),TEXT("[ %s ]：%d.%d.%d.%d"),pIServerUserItemRecv->GetAccounts(),
				pcbUserIP[0],pcbUserIP[1],pcbUserIP[2],pcbUserIP[3]);

			//发送消息
			SendRoomMessage(pIServerUserItemSend,szMessage,SMT_INFO);

			return true;
		}
	case SUB_GR_KILL_USER:		//踢出用户
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_GR_KillUser));
			if (wDataSize!=sizeof(CMD_GR_KillUser)) return false;

			//消息处理
			CMD_GR_KillUser * pKillUser=(CMD_GR_KillUser *)pDataBuffer;

			//管理用户
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;

			//权限判断
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (CUserRight::CanCutUser(dwMasterRight)==false) return true;

			//目标用户
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pKillUser->dwTargetUserID);
			if (pIServerUserItemRecv==NULL) return true;

			//发送消息
			LPCTSTR szMessage=TEXT("抱歉，您被管理员踢出房间，若有任何疑问，请联系游戏客服！");
			SendRoomMessage(pIServerUserItemRecv,szMessage,SMT_INFO|SMT_EJECT|SMT_INTERMIT_LINE);

			return true;
		}
	case SUB_GR_LIMIT_ACCOUNS:	//禁用帐户
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_GR_LimitAccounts));
			if (wDataSize!=sizeof(CMD_GR_LimitAccounts)) return false;

			//消息处理
			CMD_GR_LimitAccounts * pLimitAccounts=(CMD_GR_LimitAccounts *)pDataBuffer;

			//管理用户
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;

			//权限判断
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (CUserRight::CanForbidAccounts(dwMasterRight)==false) return true;

			//目标用户
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pLimitAccounts->dwTargetUserID);
			if (pIServerUserItemRecv==NULL) return true;

			//投递数据库
			DBR_GR_LimitAccounts LimitAccounts;
			LimitAccounts.dwUserID=pLimitAccounts->dwTargetUserID;
			LimitAccounts.dwMasterUserID=pIServerUserItemSend->GetUserID();
			LimitAccounts.dwMasterClientIP=pIServerUserItemSend->GetClientIP();
			m_DataBaseEvent.PostDataBaseEvent(DBR_GR_LIMIT_ACCOUNTS,0,0,&LimitAccounts,sizeof(LimitAccounts));

			//发送消息
			LPCTSTR szMessage=TEXT("抱歉，您的帐号被冻结了，若有任何疑问，请联系游戏客服！");
			SendRoomMessage(pIServerUserItemRecv,szMessage,SMT_INFO|SMT_EJECT|SMT_INTERMIT_LINE);

			return true;
		}
	case SUB_GR_SET_USER_RIGHT:	//用户权限
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_GR_SetUserRight));
			if (wDataSize!=sizeof(CMD_GR_SetUserRight)) return false;

			//消息处理
			CMD_GR_SetUserRight * pSetUserRight=(CMD_GR_SetUserRight *)pDataBuffer;

			//管理用户
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;

			//目标用户
			IServerUserItem * pIServerUserItemRecv=m_ServerUserManager.SearchOnLineUser(pSetUserRight->dwTargetUserID);
			if (pIServerUserItemRecv==NULL) return true;

			//权限判断
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (dwMasterRight==0L) return true;

			//获取权限
			tagServerUserData * pUserData=pIServerUserItemRecv->GetUserData();

			//权限设置
			if (CUserRight::CanLimitPlay(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitPlayGame==TRUE) pUserData->dwUserRight|=UR_CANNOT_PLAY;
				else pUserData->dwUserRight&=~UR_CANNOT_PLAY;
			}
			if (CUserRight::CanLimitLookon(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitLookonGame==TRUE) pUserData->dwUserRight|=UR_CANNOT_LOOKON;
				else pUserData->dwUserRight&=~UR_CANNOT_LOOKON;
			}
			if (CUserRight::CanLimitWisper(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitSendWisper==TRUE) pUserData->dwUserRight|=UR_CANNOT_WISPER;
				else pUserData->dwUserRight&=~UR_CANNOT_WISPER;
			}
			if (CUserRight::CanLimitRoomChat(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitRoomChat==TRUE) pUserData->dwUserRight|=UR_CANNOT_ROOM_CHAT;
				else pUserData->dwUserRight&=~UR_CANNOT_ROOM_CHAT;
			}
			if (CUserRight::CanLimitGameChat(dwMasterRight)==true)
			{
				if (pSetUserRight->cbLimitGameChat==TRUE) pUserData->dwUserRight|=UR_CANNOT_GAME_CHAT;
				else pUserData->dwUserRight&=~UR_CANNOT_GAME_CHAT;
			}

			//设置权限
			DBR_GR_SetUserRight SetUserRight;
			SetUserRight.dwUserRight=pUserData->dwUserRight;
			SetUserRight.dwUserID=pSetUserRight->dwTargetUserID;
			SetUserRight.dwMasterUserID=pIServerUserItemSend->GetUserID();
			SetUserRight.dwMasterClientIP=pIServerUserItemSend->GetClientIP();
			SetUserRight.cbGame=(CUserRight::CanBindGame(dwMasterRight)==true)?TRUE:FALSE;
			SetUserRight.cbAccounts=(CUserRight::CanBindGlobal(dwMasterRight)==true)?TRUE:FALSE;

			//投递数据
			if ((SetUserRight.cbAccounts==TRUE)||(SetUserRight.cbGame==TRUE))
			{
				m_DataBaseEvent.PostDataBaseEvent(DBR_GR_SET_USER_RIGHT,0,0,&SetUserRight,sizeof(SetUserRight));
			}

			return true;
		}
	case SUB_GR_SEND_MESSAGE:	//发送消息
		{
			//效验参数
			CMD_GR_SendMessage * pSendMessage=(CMD_GR_SendMessage *)pDataBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_SendMessage)-sizeof(pSendMessage->szSystemMessage)));
			ASSERT(wDataSize==(sizeof(CMD_GR_SendMessage)-sizeof(pSendMessage->szSystemMessage)+pSendMessage->wChatLength));
			if (wDataSize<(sizeof(CMD_GR_SendMessage)-sizeof(pSendMessage->szSystemMessage))) return false;
			if (wDataSize!=(sizeof(CMD_GR_SendMessage)-sizeof(pSendMessage->szSystemMessage)+pSendMessage->wChatLength)) return false;

			//管理用户
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;

			//权限判断
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (CUserRight::CanIssueMessage(dwMasterRight)==false) return true;

			//发送消息
			if (pSendMessage->cbGame==TRUE) SendGameMessage(INDEX_ALL_SOCKET,0,pSendMessage->szSystemMessage,SMT_INFO);
			if (pSendMessage->cbRoom==TRUE) SendRoomMessage(INDEX_ALL_SOCKET,0,pSendMessage->szSystemMessage,SMT_INFO);

			return true;
		}
	case SUB_GR_OPTION_SERVER:	//房间设置
		{
			//效验数据
			ASSERT(wDataSize==sizeof(CMD_GR_OptionServer));
			if (wDataSize!=sizeof(CMD_GR_OptionServer)) return false;

			//消息处理
			CMD_GR_OptionServer * pOptionServer=(CMD_GR_OptionServer *)pDataBuffer;

			//管理用户
			IServerUserItem * pIServerUserItemSend=GetServerUserItem(pSocketReadEvent->wIndex);
			if (pIServerUserItemSend==NULL) return false;

			//权限判断
			DWORD dwMasterRight=pIServerUserItemSend->GetUserData()->dwMasterRight;
			if (CUserRight::CanServerOption(dwMasterRight)==false) return true;

			//大厅聊天
			if (pOptionServer->cbOptionFlags==OSF_ROOM_CHAT)
			{
				m_bAllowRoomChat=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//游戏聊天
			if (pOptionServer->cbOptionFlags==OSF_GAME_CHAT)
			{
				m_bAllowGameChat=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//大厅私聊
			if (pOptionServer->cbOptionFlags==OSF_ROOM_WISPER)
			{
				m_bAllowWisper=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//进入游戏
			if (pOptionServer->cbOptionFlags==OSF_ENTER_GAME)
			{
				m_bAllowEnterGame=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//进入房间
			if (pOptionServer->cbOptionFlags==OSF_ENTER_ROOM)
			{
				m_bAllowEnterRoom=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//即将关闭
			if (pOptionServer->cbOptionFlags==OSF_SHALL_CLOSE)
			{
				m_bShallClose=(pOptionServer->cbOptionValue==TRUE)?true:false;
			}

			//发送消息
			LPCTSTR pszMessage=TEXT("服务器房间配置参数选项设置成功！");
			SendRoomMessage(pIServerUserItemSend,pszMessage,SMT_INFO);

			return true;
		}
	}

	return false;
}

//框架消息处理
bool CAttemperEngineSink::OnSocketMainFrame(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GF_FRAME);

	//获取用户
	IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
	if (pIServerUserItem==NULL) return false;

	//处理过虑
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();
	if ((pUserData->wTableID==INVALID_TABLE)||(pUserData->wChairID==INVALID_CHAIR)) return true;

	//赠送处理
	bool bSuccess = OnSendGift(Command.wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);

	//消息处理 
	if ( ! bSuccess )
	{
		CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
		return pTableFrame->OnEventSocketFrame(Command.wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);
	}

	return true;
}

//游戏消息处理
bool CAttemperEngineSink::OnSocketMainGame(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GF_GAME);

	//获取用户
	IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
	if (pIServerUserItem==NULL) return false;

	//处理过虑
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();
	if ((pUserData->wTableID==INVALID_TABLE)||(pUserData->wChairID==INVALID_CHAIR)) return true;

	//消息处理 
	CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
	return pTableFrame->OnEventSocketGame(Command.wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);
}

//视频消息处理
bool CAttemperEngineSink::OnSocketMainVideo(CMD_Command Command, void * pDataBuffer, WORD wDataSize, NTY_SocketReadEvent * pSocketReadEvent)
{
	//效验参数
	ASSERT(Command.wMainCmdID==MDM_GF_VIDEO);

	//获取用户
	IServerUserItem * pIServerUserItem=GetServerUserItem(pSocketReadEvent->wIndex);
	if (pIServerUserItem==NULL) return false;

	//处理过虑
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();
	if ((pUserData->wTableID==INVALID_TABLE)||(pUserData->wChairID==INVALID_CHAIR)) return true;

	//消息处理 
	CTableFrame * pTableFrame=(m_pTableFrame+pUserData->wTableID);
	return pTableFrame->OnEventSocketVideo(Command.wSubCmdID,pDataBuffer,wDataSize,pIServerUserItem);
}

//发送用户
bool CAttemperEngineSink::SendUserItem(IServerUserItem * pIServerUserItem, WORD wTargetIndex, WORD wTargetRoundID)
{
	//效验参数
	ASSERT(pIServerUserItem!=NULL);

	//构造数据
	BYTE cbBuffer[SOCKET_PACKAGE];
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)cbBuffer;
	tagServerUserData * pUserData=pIServerUserItem->GetUserData();

	//填写数据
	memset(pUserInfoHead,0,sizeof(tagUserInfoHead));
	pUserInfoHead->wFaceID=pUserData->wFaceID;
	pUserInfoHead->wTableID=pUserData->wTableID;
	pUserInfoHead->wChairID=pUserData->wChairID;
	pUserInfoHead->cbGender=pUserData->cbGender;
	pUserInfoHead->cbUserStatus=pUserData->cbUserStatus;
	pUserInfoHead->dwUserID=pUserData->dwUserID;
	pUserInfoHead->dwGameID=pUserData->dwGameID;
	pUserInfoHead->dwGroupID=pUserData->dwGroupID;
	pUserInfoHead->dwUserRight=pUserData->dwUserRight;
	pUserInfoHead->dwMasterRight=pUserData->dwMasterRight;
	pUserInfoHead->cbGender=pUserData->cbGender;
	pUserInfoHead->cbMemberOrder=pUserData->cbMemberOrder;
	pUserInfoHead->cbMasterOrder=pUserData->cbMasterOrder;
	pUserInfoHead->UserScoreInfo=pUserData->UserScoreInfo;
	pUserInfoHead->UserScoreInfo.lScore=pUserData->UserScoreInfo.lScore+pUserData->lStorageScore;

	//叠加数据
	CSendPacketHelper SendPacket(cbBuffer+sizeof(tagUserInfoHead),sizeof(cbBuffer)-sizeof(tagUserInfoHead));
	SendPacket.AddPacket(pUserData->szAccounts,CountString(pUserData->szAccounts),DTP_USER_ACCOUNTS);
	if (pUserData->szUnderWrite[0]!=0) SendPacket.AddPacket(pUserData->szUnderWrite,CountString(pUserData->szUnderWrite),DTP_UNDER_WRITE);
	if (pUserData->szGroupName[0]!=0) SendPacket.AddPacket(pUserData->szGroupName,CountString(pUserData->szGroupName),DTP_USER_GROUP_NAME);

	//发送数据
	WORD wSendLength=sizeof(tagUserInfoHead)+SendPacket.GetDataSize();
	if (wTargetIndex!=INDEX_ALL_SOCKET) 
	{
		if (wTargetIndex>=INDEX_ANDROID)
		{
			DWORD dwID=MAKELONG(wTargetIndex,wTargetRoundID);
			m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_USER,SUB_GR_USER_COME,cbBuffer,wSendLength);
		}
		else m_pITCPSocketEngine->SendData(wTargetIndex,wTargetRoundID,MDM_GR_USER,SUB_GR_USER_COME,cbBuffer,wSendLength);
	}
	else m_pITCPSocketEngine->SendDataBatch(MDM_GR_USER,SUB_GR_USER_COME,cbBuffer,wSendLength);

	return true;
}

//发送信息
bool CAttemperEngineSink::SendGameServerInfo(IServerUserItem * pIServerUserItem, WORD wIndex, WORD wRoundID)
{
	//发送登录成功
	CMD_GR_LogonSuccess LogonSuccess;
	memset(&LogonSuccess,0,sizeof(LogonSuccess));
	LogonSuccess.dwUserID=pIServerUserItem->GetUserID();

	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
		m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_LOGON,SUB_GR_LOGON_SUCCESS,&LogonSuccess,sizeof(LogonSuccess));
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_LOGON,SUB_GR_LOGON_SUCCESS,&LogonSuccess,sizeof(LogonSuccess));

	//发送配置信息
	BYTE cbBuffer[SOCKET_PACKAGE];
	CMD_GR_ServerInfo * pServerInfo=(CMD_GR_ServerInfo *)cbBuffer;
	memset(pServerInfo,0,sizeof(CMD_GR_ServerInfo));
	pServerInfo->wKindID=m_pGameServiceAttrib->wKindID;
	pServerInfo->wGameGenre=m_pGameServiceOption->wServerType;
	pServerInfo->wTableCount=m_pGameServiceOption->wTableCount;
	pServerInfo->wChairCount=m_pGameServiceAttrib->wChairCount;
	pServerInfo->dwVideoAddr=m_pGameServiceOption->dwVideoServer;
	pServerInfo->cbHideUserInfo=m_pGameServiceOption->cbHideUserInfo;

	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
		m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_INFO,SUB_GR_SERVER_INFO,cbBuffer,sizeof(CMD_GR_ServerInfo));
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_INFO,SUB_GR_SERVER_INFO,cbBuffer,sizeof(CMD_GR_ServerInfo));

	//发送列表解释
	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
		m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_INFO,SUB_GR_COLUMN_INFO,&m_ColumnInfo,m_wColumnInfoSize);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_INFO,SUB_GR_COLUMN_INFO,&m_ColumnInfo,m_wColumnInfoSize);

	//发送配置完成
	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
		m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_INFO,SUB_GR_CONFIG_FINISH,NULL,0);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_INFO,SUB_GR_CONFIG_FINISH);

	//发送自己信息
	SendUserItem(pIServerUserItem,wIndex,wRoundID);

	//发送在线用户
	WORD wEnumIndex=0;
	IServerUserItem * pIServerUserItemSend=NULL;
	while (true)
	{
		pIServerUserItemSend=m_ServerUserManager.EnumOnLineUser(wEnumIndex++);
		if (pIServerUserItemSend==NULL) break;
		if (pIServerUserItemSend==pIServerUserItem) continue;
		SendUserItem(pIServerUserItemSend,wIndex,wRoundID);
	}

	//发送断线用户
	wEnumIndex=0;
	while (true)
	{
		pIServerUserItemSend=m_ServerUserManager.EnumOffLineUser(wEnumIndex++);
		if (pIServerUserItemSend==NULL) break;
		if (pIServerUserItemSend==pIServerUserItem) continue;
		SendUserItem(pIServerUserItemSend,wIndex,wRoundID);
	}

	//发送桌子信息
	CMD_GR_TableInfo TableInfo;
	CTableFrame * pTableFrame=NULL;
	TableInfo.wTableCount=m_pGameServiceOption->wTableCount;
	ASSERT(TableInfo.wTableCount<CountArray(TableInfo.TableStatus));
	for (WORD i=0;i<TableInfo.wTableCount;i++)
	{
		pTableFrame=(m_pTableFrame+i);
		TableInfo.TableStatus[i].bTableLock=pTableFrame->IsTableLocked()?TRUE:FALSE;
		TableInfo.TableStatus[i].bPlayStatus=pTableFrame->IsGameStarted()?TRUE:FALSE;
	}
	WORD wSendSize=sizeof(TableInfo)-sizeof(TableInfo.TableStatus)+TableInfo.wTableCount*sizeof(TableInfo.TableStatus[0]);

	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
		m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_STATUS,SUB_GR_TABLE_INFO,&TableInfo,wSendSize);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_STATUS,SUB_GR_TABLE_INFO,&TableInfo,wSendSize);

	//发送完成
	if (wIndex>=INDEX_ANDROID)
	{
		DWORD dwID=MAKELONG(wIndex,wRoundID);
		m_AndroidUserManager.SendDataToClient(dwID,MDM_GR_LOGON,SUB_GR_LOGON_FINISH,NULL,0);
	}
	else m_pITCPSocketEngine->SendData(wIndex,wRoundID,MDM_GR_LOGON,SUB_GR_LOGON_FINISH);

	return true;
}

//列表消息处理
bool CAttemperEngineSink::OnCenterMainServerList(CMD_Command Command, void * pDataBuffer, WORD wDataSize)
{
	ASSERT(Command.wMainCmdID==MDM_CS_SERVER_LIST);
	switch (Command.wSubCmdID)
	{
	case SUB_CS_LIST_INFO:		//列表信息
		{
			//效验参数
			ASSERT(wDataSize==sizeof(CMD_CS_ListInfo));
			if (wDataSize!=sizeof(CMD_CS_ListInfo)) return false;

			//消息处理
			m_ServerList.ResetServerListBuffer();

			return true;
		}
	case SUB_CS_LIST_TYPE:		//种类信息
		{
			//效验参数
			ASSERT(wDataSize>=sizeof(tagGameType));
			ASSERT(wDataSize%sizeof(tagGameType)==0);

			//消息处理
			DWORD dwCount=wDataSize/sizeof(tagGameType);
			tagGameType * pGameType=(tagGameType *)pDataBuffer;
			m_ServerList.AppendGameTypeBuffer(pGameType,dwCount);

			return true;
		}
	case SUB_CS_LIST_KIND:		//类型信息
		{
			//效验参数
			ASSERT(wDataSize>=sizeof(tagGameKind));
			ASSERT(wDataSize%sizeof(tagGameKind)==0);

			//消息处理
			DWORD dwCount=wDataSize/sizeof(tagGameKind);
			tagGameKind * pGameKind=(tagGameKind *)pDataBuffer;
			m_ServerList.AppendGameKindBuffer(pGameKind,dwCount);

			return true;
		}
	case SUB_CS_LIST_STATION:	//站点信息
		{
			//效验参数
			ASSERT(wDataSize>=sizeof(tagGameStation));
			ASSERT(wDataSize%sizeof(tagGameStation)==0);

			//消息处理
			DWORD dwCount=wDataSize/sizeof(tagGameStation);
			tagGameStation * pGameStation=(tagGameStation *)pDataBuffer;
			m_ServerList.AppendGameStationBuffer(pGameStation,dwCount);

			return true;
		}
	case SUB_CS_LIST_SERVER:	//房间信息
		{
			//效验参数
			ASSERT(wDataSize>=sizeof(tagGameServer));
			ASSERT(wDataSize%sizeof(tagGameServer)==0);

			//消息处理
			DWORD dwCount=wDataSize/sizeof(tagGameServer);
			tagGameServer * pGameServer=(tagGameServer *)pDataBuffer;
			m_ServerList.AppendGameServerBuffer(pGameServer,dwCount);

			return true;
		}
	case SUB_CS_LIST_FINISH:	//更新完成
		{
			//激活缓冲
			m_ServerList.ActiveServerListBuffer();

			//更新人数
			WORD wInfoCount=m_ServerList.GetOnLineCountInfo(m_OnLineCountInfo,CountArray(m_OnLineCountInfo));
			m_wOnLineInfoSize=wInfoCount*sizeof(tagOnLineCountInfo);

			//发送信息
			if (m_wOnLineInfoSize>0)
			{
				ASSERT(m_pITCPSocketEngine!=NULL);
				m_pITCPSocketEngine->SendDataBatch(MDM_GR_SERVER_INFO,SUB_GR_ONLINE_COUNT_INFO,&m_OnLineCountInfo,m_wOnLineInfoSize);
				m_AndroidUserManager.SendDataToClient(MDM_GR_SERVER_INFO,SUB_GR_ONLINE_COUNT_INFO,&m_OnLineCountInfo,m_wOnLineInfoSize);
			}

			return true;
		}
	}

	return true;
}

//绑定参数
tagConnectItemInfo * CAttemperEngineSink::GetBindParameter(WORD wBindIndex)
{
	//无效连接
	if (wBindIndex==0xFFFF) return NULL;

	//常规连接
	if (wBindIndex<m_pGameServiceOption->wMaxConnect)
	{
		return m_pNormalParameter+wBindIndex;
	}

	//机器连接
	if ((wBindIndex>=INDEX_ANDROID)&&(wBindIndex<(INDEX_ANDROID+MAX_ANDROID)))
	{
		return m_pAndroidParameter+(wBindIndex-INDEX_ANDROID);
	}

	//错误断言
	ASSERT(FALSE);

	return NULL;
}

//绑定用户
IServerUserItem * CAttemperEngineSink::GetServerUserItem(WORD wBindIndex)
{
	//获取参数
	tagConnectItemInfo * pBindParameter=GetBindParameter(wBindIndex);

	//获取用户
	if (pBindParameter!=NULL)
	{
		return pBindParameter->pIServerUserItem;
	}

	//错误断言
	ASSERT(FALSE);

	return NULL;
}

//用户状况
WORD CAttemperEngineSink::GetAndroidUserStatus(tagAndroidUserStatus & AndroidUserStatus)
{
	//变量定义
	WORD wEnumIndex=0;
	IServerUserItem * pIServerUserItem=NULL;

	//设置变量
	ZeroMemory(&AndroidUserStatus,sizeof(AndroidUserStatus));

	//用户信息
	do
	{
		//获取用户
		pIServerUserItem=m_ServerUserManager.EnumOnLineUser(wEnumIndex++);

		//统计判断
		if ((pIServerUserItem!=NULL)&&(pIServerUserItem->IsAndroidUser()==true))
		{
			//获取属性
			BYTE cbUserStatus=pIServerUserItem->GetUserStatus();

			//用户统计
			switch (pIServerUserItem->GetUserStatus())
			{
			case US_FREE:
				{
					ASSERT(AndroidUserStatus.wFreeUserCount<CountArray(AndroidUserStatus.pServerUserFree));
					AndroidUserStatus.pServerUserFree[AndroidUserStatus.wFreeUserCount++]=pIServerUserItem;
					break;
				}
			case US_PLAY:
				{
					ASSERT(AndroidUserStatus.wPlayUserCount<CountArray(AndroidUserStatus.pServerUserPlay));
					AndroidUserStatus.pServerUserPlay[AndroidUserStatus.wPlayUserCount++]=pIServerUserItem;
					break;
				}
			case US_SIT:
			case US_READY:
				{
					ASSERT(AndroidUserStatus.wSitdownUserCount<CountArray(AndroidUserStatus.pServerUserSitdown));
					AndroidUserStatus.pServerUserSitdown[AndroidUserStatus.wSitdownUserCount++]=pIServerUserItem;
					break;
				}
			}
		}

	} while (pIServerUserItem!=NULL);

	return AndroidUserStatus.wFreeUserCount+AndroidUserStatus.wPlayUserCount+AndroidUserStatus.wSitdownUserCount;
}

//桌子状况
WORD CAttemperEngineSink::GetTableUserStatus(CTableFrame * pTableFrame, tagTableUserStatus & TableUserStatus)
{
	//设置变量
	ZeroMemory(&TableUserStatus,sizeof(TableUserStatus));

	//用户分析
	for (WORD i=0;i<m_pGameServiceAttrib->wChairCount;i++)
	{
		//获取用户
		IServerUserItem * pIServerUserItem=pTableFrame->GetServerUserItem(i);
		if (pIServerUserItem==NULL) continue;

		//用户类型
		if (pIServerUserItem->IsAndroidUser()==false)
		{
			TableUserStatus.wTableUserCount++;
		}
		else
		{
			TableUserStatus.wTableAndroidCount++;
		}
	}

	//最少数目
	switch (pTableFrame->m_pITableFrameSink->GetGameStartMode())
	{
	case enStartMode_AllReady:	//所有准备
		{
			TableUserStatus.wLessUserCount=2;
			break;
		}
	default:					//默认模式
		{
			TableUserStatus.wLessUserCount=m_pGameServiceAttrib->wChairCount;
			break;
		}
	}

	return TableUserStatus.wTableAndroidCount+TableUserStatus.wTableUserCount;
}

//赠送鲜花
bool CAttemperEngineSink::OnSendGift(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pSendIServerUserItem)
{
	//赠送鲜花
	if ( wSubCmdID == SUB_GF_GIFT )
	{
		//效验参数
		ASSERT(wDataSize==sizeof(CMD_GF_Gift));
		if (wDataSize!=sizeof(CMD_GF_Gift)) return false;                

		//处理过虑
		tagServerUserData * pSendUserData=pSendIServerUserItem->GetUserData();
		if ((pSendUserData->wTableID==INVALID_TABLE)||(pSendUserData->wChairID==INVALID_CHAIR)) return true;

		//变量定义
		CMD_GF_Gift * pGift=(CMD_GF_Gift *)pDataBuffer;

		//查找用户
		CTableFrame * pTableFrame=(m_pTableFrame+pSendUserData->wTableID);
		IServerUserItem * pIRcvUserItem=NULL;
		for (WORD i=0;i<m_pGameServiceAttrib->wChairCount;i++)
		{
			IServerUserItem *pITmpServerUserItem = pTableFrame->GetServerUserItem(i);
			if ((pITmpServerUserItem!=NULL)&&(pITmpServerUserItem->GetUserID()==pGift->dwRcvUserID))
			{
				pIRcvUserItem = pITmpServerUserItem;
				break;
			}
		}

		if ( pIRcvUserItem != NULL )
		{
			//获取鲜花
			ASSERT(pGift->wGiftID < GIFT_COUNT );
			if ( pGift->wGiftID >= GIFT_COUNT ) return true;
			tagGiftInfo GiftInfo = g_GiftInfo[pGift->wGiftID];

			//房间判断
			if ( m_pGameServiceOption->wServerType == GAME_GENRE_GOLD )
			{
				//积分判断
				if ( GiftInfo.lValue <= pSendUserData->lStorageScore)
				{
					//扣除积分
					pSendUserData->lStorageScore -= GiftInfo.lValue;

					//积分通知
					SendUserScore( pSendIServerUserItem );

					//数据库通知
					DBR_GR_SendGift SendGift;
					SendGift.dwSendUserID = pGift->dwSendUserID;
					SendGift.dwRcvUserID = pGift->dwRcvUserID;
					SendGift.dwClientIP = pSendIServerUserItem->GetClientIP();
					SendGift.wGiftID = pGift->wGiftID;

					m_DataBaseEvent.PostDataBaseEvent(DBR_GR_SEND_GIFT, 0, 0, &SendGift, sizeof( SendGift ) );
				}
				else
				{
					//发送消息
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("您游戏币不够！"));
					SendGameMessage(pSendIServerUserItem,szDescribe,SMT_EJECT|SMT_INFO);		
					return true;
				}
			}
			else
			{
				//数据库通知
				DBR_GR_SendGift SendGift;
				SendGift.dwSendUserID = pGift->dwSendUserID;
				SendGift.dwRcvUserID = pGift->dwRcvUserID;
				SendGift.dwClientIP = pSendIServerUserItem->GetClientIP();
				SendGift.wGiftID = pGift->wGiftID;

				m_DataBaseEvent.PostDataBaseEvent(DBR_GR_SEND_GIFT, 0, 0, &SendGift, sizeof( SendGift ) );
			}


		}
		else
		{
			//发送消息
			TCHAR szDescribe[128]=TEXT("");
			_snprintf(szDescribe,sizeof(szDescribe),TEXT("对方已经离开，赠送失败！"));
			SendGameMessage(pSendIServerUserItem,szDescribe,SMT_EJECT|SMT_INFO);
			return true;
		}

		return true;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////
