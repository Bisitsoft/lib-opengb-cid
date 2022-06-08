#include <stdio.h>

#define OPENGB_CODE_PREFER_FAST
//#define OPENGB_CODE_PREFER_TIGHT
#include "ctzidn.h"
#include "mod11_2.h"
#include "opengbex.h"

bool read_cid_number(const int length, unsigned long long &_out_result);
bool read_cid_checksum(OPENGB_CID_CHECKSUM_TYPE &_out_result);
char cid_checksum_to_char(OPENGB_CID_CHECKSUM_TYPE checksum);
void clear_stdin();

/*
GB11643-1999�ĵ��ĸ�¼B�и��������֤�����ӣ�
11010519491231002X
440524188001010014
*/

int main(){
	unsigned long long _out;
	OPENGB_CID_CHECKSUM_TYPE checksum;
	
	//printf("%s\n",opengb::ctzidn::Not18CIdException("A"));
	
	opengb::ctzidn::S_CitizenId _cid;
	
	while(true){
		printf("������һ��18λ���֤����: ");
		clear_stdin();
		
		if(!read_cid_number(OPENGB_CID_18CID_AREA_LENGTH, _out)) { clear_stdin(); continue; }
		_cid.area = (OPENGB_CID_AREA_TYPE)_out;
		
		if(!read_cid_number(OPENGB_CID_18CID_BIRTHDAY_LENGTH, _out)) { clear_stdin(); continue; }
		_cid.birthday = (OPENGB_CID_BIRTHDAY_TYPE)_out;
		
		if(!read_cid_number(OPENGB_CID_18CID_ORDER_LENGTH, _out)) { clear_stdin(); continue; }
		_cid.order = (OPENGB_CID_ORDER_TYPE)_out;
		
		if(!read_cid_checksum(checksum)) { clear_stdin(); continue; }
		_cid.checksum = checksum;
		opengb::ctzidn::CitizenId cid(_cid);
		
		checksum = _OPENGB_MOD11_2_METHOD(cid);
		
		printf(
			"��������֤���ǣ�%06d%08d%03d%c\n",
			cid.get_Area(),
			cid.get_Birthday(),
			cid.get_Order(),
			cid_checksum_to_char(cid.get_Checksum())
		);
		printf(
			"��������֤���е�У���루ĩβ���֣���%c��У������%c��У���㷨�����%s\n",
			cid_checksum_to_char(cid.get_Checksum()),
			cid_checksum_to_char(checksum),
			checksum==cid.get_Checksum()?"��ȷ��":"�����"
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