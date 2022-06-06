#include <stdio.h>

#define OPENGB_CODE_PREFER_FAST
//#define OPENGB_CODE_PREFER_TIGHT
#include "opengb_cid_rcmd.h"

bool read_cid_number(const int length, unsigned long long &_out_result);
bool read_cid_checksum(OPENGB_CID_CHECKSUM_TYPE &_out_result);
char cid_checksum_to_char(OPENGB_CID_CHECKSUM_TYPE checksum);
void clear_stdin();

int main(){
	unsigned long long _out;
	OPENGB_CID_CHECKSUM_TYPE checksum;
	
	//printf("%s\n",opengb::cizidn::Not18CIdException("A"));
	
	opengb::cizidn::CitizenId cid;
	
	while(true){
		printf("请输入一个18位身份证号码: ");
		clear_stdin();
		
		if(!read_cid_number(OPENGB_CID_18CID_AREA_LENGTH, _out)) { clear_stdin(); continue; }
		cid.m_cid.area = (OPENGB_CID_AREA_TYPE)_out;
		
		if(!read_cid_number(OPENGB_CID_18CID_BIRTHDAY_LENGTH, _out)) { clear_stdin(); continue; }
		cid.m_cid.birthday = (OPENGB_CID_BIRTHDAY_TYPE)_out;
		
		if(!read_cid_number(OPENGB_CID_18CID_ORDER_LENGTH, _out)) { clear_stdin(); continue; }
		cid.m_cid.order = (OPENGB_CID_ORDER_TYPE)_out;
		
		if(!read_cid_checksum(cid.m_cid.checksum)) { clear_stdin(); continue; }
		
		checksum = _OPENGB_MOD11_2_METHOD(cid);
		
		printf(
			"输入的身份证号是：%06d%08d%03d%c\n",
			cid.m_cid.area,
			cid.m_cid.birthday,
			cid.m_cid.order,
			cid_checksum_to_char(cid.m_cid.checksum)
		);
		printf(
			"输入的身份证号中的校验码（末尾数字）是%c，校验码是%c，校验算法结果：%s\n",
			cid_checksum_to_char(cid.m_cid.checksum),
			cid_checksum_to_char(checksum),
			checksum==cid.m_cid.checksum?"正确√":"错误×"
		);
	}

	return 0;
}

bool read_cid_number(const int length, unsigned long long &_out_result){
	int i;
	char temp;
	
	_out_result=0;
	for(i=0;i<length;i++){
		_out_result*=10; //进位
		
		temp=getchar();
		if ('0'<=temp&&temp<='9'){
			_out_result+=temp-'0';
		}else if (temp=='\n'){
			printf("格式错误：身份证号应当为18位！\n");
			return false;
		}else{
			printf("格式错误：省份证号前17位应当为数字！\n");
			return false;
		}
	}
	
	return true;
}
bool read_cid_checksum(OPENGB_CID_CHECKSUM_TYPE &_out_result){
	char temp;
	
	temp=getchar();
	if(temp=='X'||temp=='x'){
		_out_result=10;
	}else if ('0'<=temp&&temp<='9'){
		_out_result=temp-'0';
	}else if (temp=='\n'){
		printf("格式错误：身份证号应当为18位！\n");
		return false;
	}else{
		printf("格式错误：校验码——身份证最后一位应当为数字或者字母“X”！\n");
		return false;
	}
	
	return true;
}

char cid_checksum_to_char(OPENGB_CID_CHECKSUM_TYPE checksum){
	if(0<=checksum&&checksum<=9){
		return checksum+'0';
	}else if(checksum==10){
		return 'X';
	}
	return '?';
}

void clear_stdin(){
	while(stdin->_cnt>0){
		stdin->_ptr++;
		stdin->_cnt--;
	}
}