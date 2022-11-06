#include <stdio.h>

#include "ctzidn.h"
#include "opengbex.h"

bool read_cid_number(const int length, unsigned long long *_out_result);
bool read_cid_checksum(OPENGB_CID_CHECKSUM_TYPE *_out_result);
char cid_checksum_to_char(OPENGB_CID_CHECKSUM_TYPE checksum);
void clear_stdin();

// GB11643-1999文档的附录B中给出的身份证号例子：
//   11010519491231002X
//   440524188001010014 // 你没看错，就是1880。

int main(){
	unsigned long long _out;
	OPENGB_CID_CHECKSUM_TYPE checksum;
	
	CitizenId cid, temp_cid;
	CitizenIdZip1 zipped_cid;
	
	while(true){
		printf("请输入一个18位身份证号码: ");
		clear_stdin();
		
		if(!read_cid_number(OPENGB_CID_18CID_AREA_LENGTH, &_out)) { clear_stdin(); continue; }
		cid.area = (OPENGB_CID_AREA_TYPE)_out;
		
		if(!read_cid_number(OPENGB_CID_18CID_BIRTHDAY_LENGTH, &_out)) { clear_stdin(); continue; }
		cid.birthday = (OPENGB_CID_BIRTHDAY_TYPE)_out;
		
		if(!read_cid_number(OPENGB_CID_18CID_ORDER_LENGTH, &_out)) { clear_stdin(); continue; }
		cid.order = (OPENGB_CID_ORDER_TYPE)_out;
		
		if(!read_cid_checksum(&checksum)) { clear_stdin(); continue; }
		cid.checksum = checksum;
		
		printf(
			"输入的身份证号是：%06d%08d%03d%c\n",
			cid.area,
			cid.birthday,
			cid.order,
			cid_checksum_to_char(cid.checksum)
		);
		printf(
			"输入的身份证号中的顺序码是%d，性别是:%s。\n",
			cid.order,
			CId_GetSex(&cid) ? "男" : "女"
		);
		checksum = _OPENGB_MOD11_2_METHOD(&cid);
		printf(
			"输入的身份证号中的校验码（末尾数字）是%c，校验码是%c，校验算法结果：%s\n",
			cid_checksum_to_char(cid.checksum),
			cid_checksum_to_char(checksum),
			checksum==cid.checksum?"正确√":"错误×"
		);
		zipped_cid = CId_ToZip1(&cid);
		printf(
			"Zip1编码：%lld\n",
			zipped_cid
		);
		temp_cid = To15CId(&cid);
		zipped_cid = CId_ToZip1(&temp_cid);
		printf(
			"Zip1(To15CId)编码：%llu\n",
			zipped_cid
		);
	}

	return 0;
}

bool read_cid_number(const int length, unsigned long long *_out_result){
	int i;
	char temp;
	
	*_out_result=0;
	for(i=0;i<length;++i){
		*_out_result*=10; //进位
		
		temp=getchar();
		if ('0'<=temp&&temp<='9'){
			*_out_result+=temp-'0';
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
bool read_cid_checksum(OPENGB_CID_CHECKSUM_TYPE *_out_result){
	char temp;
	
	temp=getchar();
	if(temp=='X'||temp=='x'){
		*_out_result=10;
	}else if ('0'<=temp&&temp<='9'){
		*_out_result=temp-'0';
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
	fflush(stdin);
}
