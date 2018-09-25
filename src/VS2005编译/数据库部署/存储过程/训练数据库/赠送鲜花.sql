
----------------------------------------------------------------------------------------------------

USE QPEducateDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GR_RecordGiftGrant]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[GSP_GR_RecordGiftGrant]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

-- �ʻ�����
CREATE PROC GSP_GR_RecordGiftGrant
	@dwSendUserID INT,			-- ������
	@dwRcvUserID INT,			-- ������
	@strGift VARCHAR(64),		-- ��������
	@lGiftPay BIGINT,			-- ���͸���		
	@wKindID INT,				-- ���ͱ�ʶ
	@wServerID INT,				-- �����ʶ
	@strGrantIP	VARCHAR(15)		-- ���͵�ַ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN
	-- ��������
	DECLARE @Score BIGINT

	-- ��Ϸ�ж�
	IF EXISTS (SELECT UserID FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreLocker WHERE UserID=@dwSendUserID)
	RETURN 1

	-- �����û�
	INSERT QPTreasureDBLink.QPTreasureDB.dbo.GameScoreLocker (UserID,KindID,ServerID)
	VALUES (@dwSendUserID, @wKindID, @wServerID)

	-- ����ж�
	SELECT @Score=Score FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo WHERE UserID=@dwSendUserID
	IF @Score IS NULL OR @Score<=0 OR @lGiftPay>@Score
	BEGIN	
		-- �Ӵ�����	
		DELETE FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreLocker WHERE UserID=@dwSendUserID
		RETURN 1
	END
		
	-- ���½��
	UPDATE QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo SET Score=Score-@lGiftPay WHERE UserID=@dwSendUserID
	
	-- �Ӵ�����
	DELETE FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreLocker WHERE UserID=@dwSendUserID	

	-- д���¼
	INSERT QPTreasureDBLink.QPTreasureDB.dbo.RecordGiftGrant (SendUserID,RcvUserID,KindID,ServerID,Gift,GiftPay,GrantIP)
	VALUES (@dwSendUserID,@dwRcvUserID,@wKindID,@wServerID,@strGift,@lGiftPay,@strGrantIP)
	
END

RETURN 0

GO

----------------------------------------------------------------------------------------------------