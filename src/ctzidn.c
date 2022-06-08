#include "ctzidn.h"

int GetNumberLength(unsigned long int n);



int GetNumberLength(unsigned long int n){
	int count=0;
	while(n>0){
		n/=10;
		count++;
	}
	return count;
}


			
int GetSex(const CitizenId *cid){
	return cid->order%2 == 0 ? OPENGB_CID_SEX_FEMALE : OPENGB_CID_SEX_MALE;
}



bool Is18CId(const CitizenId *cid){
	return GetNumberLength(cid->birthday)==8;
}
bool Is15CId(const CitizenId *cid){
	return GetNumberLength(cid->birthday)==6; //理论上应该不存在190X年的生日。
		//&& m_cid.birthday == 0;
}



bool VerifyCIdChecksum(const CitizenId *_18cid){
	return _18cid->checksum==_OPENGB_MOD11_2_METHOD(_18cid);
}

#if defined(OPENGB_CODE_PREFER_FAST)

OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(const CitizenId *_18cid){
	unsigned int sum=0;
	const OPENGB_MOD11_2_W_LIST_TYPE *ptr_w=_mod11_2_w_list+1;
	int i, iend;
	CitizenId cid=*_18cid;
	div_t div_result;
	OPENGB_CID_CHECKSUM_TYPE r;
	
//#warning Commented!
	//if(!_18cid.Is18CId()){
	//	throw ;
	//}
	
	for(i=0, iend=OPENGB_CID_18CID_ORDER_LENGTH;i<iend;i++){
		div_result = div(cid.order,10);
//#warning 测试此处指针是否比直接用数组快
		sum+=div_result.rem*(*(ptr_w++));
		cid.order=div_result.quot;
	}
	for(iend+=OPENGB_CID_18CID_BIRTHDAY_LENGTH;i<iend;i++){
		div_result = div(cid.birthday,10);
		sum+=div_result.rem*(*(ptr_w++));
		cid.birthday=div_result.quot;
	}
	for(iend+=OPENGB_CID_18CID_AREA_LENGTH;i<iend;i++){
		div_result = div(cid.area,10);
		sum+=div_result.rem*(*(ptr_w++));
		cid.area=div_result.quot;
	}
	
	//r=OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
	r=_mod11_2_trs_list[sum%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER];
	return r==OPENGB_MOD11_2_MOD_CONSTANT_NUMBER?0:r;
}

#if defined(OPENGB_CODE_PREFER_FAST)
const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[OPENGB_CID_18CID_LENGTH] = {1,2,4,8,5,10,9,7,3,6,1,2,4,8,5,10,9,7};
const OPENGB_CID_CHECKSUM_TYPE _mod11_2_trs_list[OPENGB_MOD11_2_MOD_CONSTANT_NUMBER]={1,0,10,9,8,7,6,5,4,3,2}; //transform list
#elif defined(OPENGB_CODE_PREFER_TIGHT)
const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[10] = {1,2,4,8,5,10,9,7,3,6};
#endif

#elif defined(OPENGB_CODE_PREFER_TIGHT)

OPENGB_CID_CHECKSUM_TYPE opengb::_gb11643_1999_mod11_2_tt(const CitizenId *_18cid){
	unsigned char i, sum=0;
	CitizenId cid=*_18cid;
	div_t div_result;
	
//#warning Commented!
	//if(!_18cid.Is18CId()){
	//	throw ;
	//}
	
	for(i=1;i<=OPENGB_CID_18CID_ORDER_LENGTH;i++){
		div_result = div(cid.order,10);
		sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		cid.order=div_result.quot;
	}
	for(;i<=OPENGB_CID_18CID_ORDER_LENGTH+OPENGB_CID_18CID_BIRTHDAY_LENGTH;i++){
		div_result = div(cid.birthday,10);
		sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		cid.birthday=div_result.quot;
	}
	for(;i<=OPENGB_CID_18CID_ORDER_LENGTH+OPENGB_CID_18CID_BIRTHDAY_LENGTH+OPENGB_CID_18CID_AREA_LENGTH;i++){
		div_result = div(id.area,10);
		sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		cid.area=div_result.quot;
	}
	
	return OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER == OPENGB_MOD11_2_MOD_CONSTANT_NUMBER
		? 0 : OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
}

#endif
