@echo off

TITLE �������ݿ⡾Ver6.5_Spreader�� �����ű�������... [�ڼ�����ر�]

md D:\���ݿ�

Rem �������ݿ�����
set rootPath=���ݿ�ű�\
osql -E -i "%rootPath%���ݿ�ɾ��.sql"
osql -E -i "%rootPath%ƽ̨���ݿ�.sql"
osql -E -i "%rootPath%������ݿ�.sql"
osql -E -i "%rootPath%�û����ݿ�.sql"
osql -E -i "%rootPath%�������ݿ�.sql"
osql -E -i "%rootPath%ѵ�����ݿ�.sql"

Rem �����ӷ�����������
set rootPath=���ݽű�\
osql -E -i "%rootPath%������Ϣ.sql"
osql -E -i "%rootPath%��Ϸ�б�.sql"
osql -E -i "%rootPath%�Ƹ�����.sql"
osql -E -i "%rootPath%ƽ̨����.sql"
osql -E -i "%rootPath%�û�����.sql"

Rem �洢����
set rootPath=�洢����\�û����ݿ�\
osql -E  -i "%rootPath%��ʶ��¼.sql"
osql -E  -i "%rootPath%�ʺŵ�¼.sql"
osql -E  -i "%rootPath%ע���ʺ�.sql"

set rootPath=�洢����\ƽ̨���ݿ�\
osql -E  -i "%rootPath%��������.sql"
osql -E  -i "%rootPath%��������.sql"
osql -E  -i "%rootPath%������Ϣ.sql"
osql -E  -i "%rootPath%���ؽڵ�.sql"

set rootPath=�洢����\������ݿ�\
osql -E  -i "%rootPath%��ʶ��¼.sql"
osql -E  -i "%rootPath%���ػ�����.sql"
osql -E  -i "%rootPath%�뿪����.sql"
osql -E  -i "%rootPath%��Ϸд��.sql"
osql -E  -i "%rootPath%��Ϸ��¼.sql"
osql -E  -i "%rootPath%�����ʻ�.sql"

set rootPath=�洢����\�������ݿ�\
osql -E  -i "%rootPath%��ʶ��¼.sql"
osql -E  -i "%rootPath%���ػ�����.sql"
osql -E  -i "%rootPath%�뿪����.sql"
osql -E  -i "%rootPath%��Ϸд��.sql"
osql -E  -i "%rootPath%��Ϸ��¼.sql"
osql -E  -i "%rootPath%�����ʻ�.sql"

set rootPath=�洢����\ѵ�����ݿ�\
osql -E  -i "%rootPath%��ʶ��¼.sql"
osql -E  -i "%rootPath%���ػ�����.sql"
osql -E  -i "%rootPath%�뿪����.sql"
osql -E  -i "%rootPath%��Ϸ��¼.sql"
osql -E  -i "%rootPath%��Ϸд��.sql"
osql -E  -i "%rootPath%�����ʻ�.sql"

pause

CLS
@echo off
@echo ����������ϷID ����
set rootPath=���ݽű�\
osql -E  -i "%rootPath%��ʶ����.sql"

COLOR 0A
CLS
@echo off
cls
echo ------------------------------
echo.
echo	��Ҫ���ݿ⽨����ɣ�������Լ�ƽ̨�Ļ�����Ϸִ�� 
echo.
echo.
echo	��Ȩ���У� �����������Ƽ����޹�˾
echo ------------------------------

pause


