
----------------------------------------------------------------------------------------------------

USE QPServerInfoDB
GO

----------------------------------------------------------------------------------------------------

-- 删除数据
DELETE GameTypeItem
DELETE GameKindItem
DELETE GameNodeItem
GO

----------------------------------------------------------------------------------------------------

-- 类型数据
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 1, '财富游戏',100, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 2, '牌类游戏',200, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 3, '棋类游戏',300, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 4, '麻将游戏',400, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 5, '休闲游戏',500, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 6, '视频游戏',600, 0)

----------------------------------------------------------------------------------------------------

-- 财富游戏
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 1, 1, '梭哈', 'ShowHand.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 2, 1, '21点', 'BlackJack.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 3, 1, '炸金花', 'ZaJinHua.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 4, 1, '百家乐', 'Baccarat.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 5, 1, '牛牛', 'Ox.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 6, 1, '港式五张', 'HKFiveCard.exe', 66822, 100, 0, 'QPTreasureDB')

-- 牌类游戏
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 100, 2, '斗地主', 'Land.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 101, 2, '锄大地', 'Hoe.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 102, 2, '疯狂斗地主', 'LandCrazy.exe', 66822, 100, 0, 'QPLandCrazyDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 103, 2, '两副升级', 'UpGrade.exe', 66822, 100, 0, 'QPUpGradeDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 104, 2, '拱猪', 'UncoverPig.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 105, 2, '捉麻子', 'CatchPock.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 106, 2, '百变双扣', 'ShuangKouBB.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 107, 2, '挖坑', 'Trench.exe', 66822, 100, 0, 'QPTrenchDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 109, 2, '双扣', 'ShuangKou.exe', 66822, 100, 0, 'QPShuangKouDB')

-- 棋类游戏
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 200, 3, '中国象棋', 'ChinaChess.exe', 66822, 100, 0, 'QPChinaChessDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 203, 3, '五子棋', 'GoBang.exe', 66822, 100, 0, 'QPGoBangDB')

-- 麻将游戏
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 301, 4, '广东麻将', 'SparrowGD.exe', 66822, 100, 0, 'QPSparrowGDDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 312, 4, '大众麻将', 'SparrowDZ.exe', 66822, 100, 0, 'QPSparrowDZDB')

-- 休闲游戏
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 400, 5, '连连看', 'LLShow.exe', 66822, 100, 0, 'QPLLShowDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 401, 5, '飞行棋', 'Plane.exe', 66822, 100, 0, 'QPPlaneDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 402, 5, '台球', 'Billiards.exe', 66822, 100, 0, 'QPBilliardsDB')


----视频类
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 513, 6, '锄大地', 'HoeVD.exe', 66822, 100, 0, 'QPHoeDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 522, 6, '疯狂斗地主', 'LandCrazyVD.exe', 66822, 100, 0, 'QPLandCrazyDB')
----------------------------------------------------------------------------------------------------

GO