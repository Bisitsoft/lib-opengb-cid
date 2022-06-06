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
		printf("������һ��18λ���֤����: ");
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
			"��������֤���ǣ�%06d%08d%03d%c\n",
			cid.m_cid.area,
			cid.m_cid.birthday,
			cid.m_cid.order,
			cid_checksum_to_char(cid.m_cid.checksum)
		);
		printf(
			"��������֤���е�У���루ĩβ���֣���%c��У������%c��У���㷨�����%s\n",
			cid_checksum_to_char(cid.m_cid.checksum),
			cid_checksum_to_char(checksum),
			checksum==cid.m_cid.checksum?"��ȷ��":"�����"
		);
	}

	return 0;
}

bool read_cid_number(const int length, unsigned long long &_out_result){
	int i;
	char temp;
	
	_out_result=0;
	for(i=0;i<length;i++){
		_out_result*=10; //��λ
		
		temp=getchar();
		if ('0'<=temp&&temp<='9'){
			_out_result+=temp-'0';
		}else if (temp=='\n'){
			printf("��ʽ�������֤��Ӧ��Ϊ18λ��\n");
			return false;
		}else{
			printf("��ʽ����ʡ��֤��ǰ17λӦ��Ϊ���֣�\n");
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
		printf("��ʽ�������֤��Ӧ��Ϊ18λ��\n");
		return false;
	}else{
		printf("��ʽ����У���롪�����֤���һλӦ��Ϊ���ֻ�����ĸ��X����\n");
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