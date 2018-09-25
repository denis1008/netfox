
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

-- 鲜花赠送
CREATE PROC GSP_GR_RecordGiftGrant
	@dwSendUserID INT,			-- 赠送者
	@dwRcvUserID INT,			-- 接受者
	@strGift VARCHAR(64),		-- 赠送名称
	@lGiftPay BIGINT,			-- 赠送付费		
	@wKindID INT,				-- 类型标识
	@wServerID INT,				-- 房间标识
	@strGrantIP	VARCHAR(15)		-- 赠送地址
WITH ENCRYPTION AS

-- 属性设置
SET NOCOUNT ON

-- 执行逻辑
BEGIN
	-- 变量定义
	DECLARE @Score BIGINT

	-- 游戏判断
	IF EXISTS (SELECT UserID FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreLocker WHERE UserID=@dwSendUserID)
	RETURN 1

	-- 锁定用户
	INSERT QPTreasureDBLink.QPTreasureDB.dbo.GameScoreLocker (UserID,KindID,ServerID)
	VALUES (@dwSendUserID, @wKindID, @wServerID)

	-- 金币判断
	SELECT @Score=Score FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo WHERE UserID=@dwSendUserID
	IF @Score IS NULL OR @Score<=0 OR @lGiftPay>@Score
	BEGIN	
		-- 接触锁定	
		DELETE FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreLocker WHERE UserID=@dwSendUserID
		RETURN 1
	END
		
	-- 更新金币
	UPDATE QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo SET Score=Score-@lGiftPay WHERE UserID=@dwSendUserID
	
	-- 接触锁定
	DELETE FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreLocker WHERE UserID=@dwSendUserID	

	-- 写入记录
	INSERT QPTreasureDBLink.QPTreasureDB.dbo.RecordGiftGrant (SendUserID,RcvUserID,KindID,ServerID,Gift,GiftPay,GrantIP)
	VALUES (@dwSendUserID,@dwRcvUserID,@wKindID,@wServerID,@strGift,@lGiftPay,@strGrantIP)
	
END

RETURN 0

GO

----------------------------------------------------------------------------------------------------