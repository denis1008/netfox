
----------------------------------------------------------------------------------------------------

USE QPServerInfoDB
GO

----------------------------------------------------------------------------------------------------

-- ɾ������
DELETE GameTypeItem
DELETE GameKindItem
DELETE GameNodeItem
GO

----------------------------------------------------------------------------------------------------

-- ��������
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 1, '�Ƹ���Ϸ',100, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 2, '������Ϸ',200, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 3, '������Ϸ',300, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 4, '�齫��Ϸ',400, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 5, '������Ϸ',500, 0)
INSERT GameTypeItem (TypeID, TypeName, SortID, Nullity) VALUES ( 6, '��Ƶ��Ϸ',600, 0)

----------------------------------------------------------------------------------------------------

-- �Ƹ���Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 1, 1, '���', 'ShowHand.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 2, 1, '21��', 'BlackJack.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 3, 1, 'ը��', 'ZaJinHua.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 4, 1, '�ټ���', 'Baccarat.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 5, 1, 'ţţ', 'Ox.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 6, 1, '��ʽ����', 'HKFiveCard.exe', 66822, 100, 0, 'QPTreasureDB')

-- ������Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 100, 2, '������', 'Land.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 101, 2, '�����', 'Hoe.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 102, 2, '��񶷵���', 'LandCrazy.exe', 66822, 100, 0, 'QPLandCrazyDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 103, 2, '��������', 'UpGrade.exe', 66822, 100, 0, 'QPUpGradeDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 104, 2, '����', 'UncoverPig.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 105, 2, '׽����', 'CatchPock.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 106, 2, '�ٱ�˫��', 'ShuangKouBB.exe', 66822, 100, 0, 'QPTreasureDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 107, 2, '�ڿ�', 'Trench.exe', 66822, 100, 0, 'QPTrenchDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 109, 2, '˫��', 'ShuangKou.exe', 66822, 100, 0, 'QPShuangKouDB')

-- ������Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 200, 3, '�й�����', 'ChinaChess.exe', 66822, 100, 0, 'QPChinaChessDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 203, 3, '������', 'GoBang.exe', 66822, 100, 0, 'QPGoBangDB')

-- �齫��Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 301, 4, '�㶫�齫', 'SparrowGD.exe', 66822, 100, 0, 'QPSparrowGDDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 312, 4, '�����齫', 'SparrowDZ.exe', 66822, 100, 0, 'QPSparrowDZDB')

-- ������Ϸ
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 400, 5, '������', 'LLShow.exe', 66822, 100, 0, 'QPLLShowDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 401, 5, '������', 'Plane.exe', 66822, 100, 0, 'QPPlaneDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 402, 5, '̨��', 'Billiards.exe', 66822, 100, 0, 'QPBilliardsDB')


----��Ƶ��
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 513, 6, '�����', 'HoeVD.exe', 66822, 100, 0, 'QPHoeDB')
INSERT GameKindItem (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Nullity, DataBaseName) VALUES ( 522, 6, '��񶷵���', 'LandCrazyVD.exe', 66822, 100, 0, 'QPLandCrazyDB')
----------------------------------------------------------------------------------------------------

GO