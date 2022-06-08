/*
dic = {int AreaCode(MainKey), AreaCodeDescription[] AreaCodeDescriptions}
class AreaCodeDescription{DocCodeEnum DocCode, LinkedList<AreaInfo> Nodes}
class AreaInfo{AreaLevelEnum AreaLevel, string Name}

AreaCode即6位地区编码。
DocCodeEnum是枚举值，用于表示当前内容所属标准、或者公文等。


AreaLevelEnum 不带“级”字。两个字节，前一个字节表示等级，后一个字节表示具体行政区划（依据《中华人民共和国宪法（自2018年3月11日修正案）》）：
                          省、自治区、直辖市、特别行政区*,市*,区*、自治州、县、自治县,乡、民族乡、镇；；；；；；；；；；； 自治州、县、自治县、市,市辖区、县级市、县、自治县、自治旗、林区、特区???
                          注意自治区、自治州、自治县的集合关系，不存在市-自治县。
AreaInfo.Name 应当不带地区级别名称。
GetFullAreaName(AreaInfo)->EnumName(CultureInfo,AreaLevelEnum)+AreaInfo.Name
*/