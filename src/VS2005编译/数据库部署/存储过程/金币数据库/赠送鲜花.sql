
----------------------------------------------------------------------------------------------------

USE QPTreasureDB
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

	-- �����¼
	INSERT QPTreasureDBLink.QPTreasureDB.dbo.RecordGiftGrant (SendUserID,RcvUserID,KindID,ServerID,Gift,GiftPay,GrantIP)
	VALUES (@dwSendUserID,@dwRcvUserID,@wKindID,@wServerID,@strGift,@lGiftPay,@strGrantIP)

END

RETURN 0

GO

----------------------------------------------------------------------------------------------------