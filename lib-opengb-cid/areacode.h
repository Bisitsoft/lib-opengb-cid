/*
dic = {int AreaCode(MainKey), AreaCodeDescription[] AreaCodeDescriptions}
class AreaCodeDescription{DocCodeEnum DocCode, LinkedList<AreaInfo> Nodes}
class AreaInfo{AreaLevelEnum AreaLevel, string Name}

AreaCode��6λ�������롣
DocCodeEnum��ö��ֵ�����ڱ�ʾ��ǰ����������׼�����߹��ĵȡ�


AreaLevelEnum �����������֡������ֽڣ�ǰһ���ֽڱ�ʾ�ȼ�����һ���ֽڱ�ʾ�����������������ݡ��л����񹲺͹��ܷ�����2018��3��11����������������
                          ʡ����������ֱϽ�С��ر�������*,��*,��*�������ݡ��ء�������,�硢�����硢�򣻣������������������� �����ݡ��ء������ء���,��Ͻ�����ؼ��С��ء������ء������졢����������???
                          ע���������������ݡ������صļ��Ϲ�ϵ����������-�����ء�
AreaInfo.Name Ӧ�����������������ơ�
GetFullAreaName(AreaInfo)->EnumName(CultureInfo,AreaLevelEnum)+AreaInfo.Name
*/