#include <stdio.h>

#include "ctzidn.h"
#include "mod11_2h"

bool read_cid_number(int length, bool allowX=false)
bool read_cid_checksum(OPENGB_CID_CHECKSUM_TYPE &_out_result){
	char temp=getchar();
	if(temp=='X'||temp=='x'){
		_out_result=10;
	}else if ('0'<=temp&&temp<='9'){
		_out_result=temp-'0';
	}else{
		printf("校验码——身份证最后一位应当为"
		return false;
	}
	return true;
}

int main(){
	int i;
	char temp;
	
	opengb::cid::CitizenId cid;
	
	while(true){
		printf("请输入一个18位身份证号码: ");
		
		for(i=0;i<OPENGB_CID_18CID_AREA_LENGTH;i++){
			temp=getchar();
			
		}
		
		scanf("%6d%8d%3d%c",&area,&birthday,&order,&_checksum);
		if(_checksum=='X'||_checksum=='x'){
			checksum=10;
		}else{
			checksum=_checksum-'0';
		}
		
		opengb::cid::S_CitizenId s_cid;
		s_cid.area=(OPENGB_CID_AREA_TYPE)area;
		s_cid.birthday=(OPENGB_CID_BIRTHDAY_TYPE)birthday;
		s_cid.order=(OPENGB_CID_ORDER_TYPE)order;
		s_cid.checksum=checksum;
		
		
		OPENGB_CID_CHECKSUM_TYPE = _OPENGB_MOD11_2_METHOD()
	}

	return 0;
}