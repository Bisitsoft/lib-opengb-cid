#include "ctzidn.h"

#include <stdlib.h>
#include <string.h>

#define _OPENGB_IS_6N(n) (100000<=n&&n<=999999)
#define _OPENGB_IS_8N(n) (10000000<=n&&n<=99999999)

int GetSex(const CitizenId * const cid){
	return cid->order%2 == 0 ? OPENGB_CID_SEX_FEMALE : OPENGB_CID_SEX_MALE;
}



bool Is18CId(const CitizenId * const cid){
	return _OPENGB_IS_8N(cid->birthday);
}
bool Is15CId(const CitizenId * const cid){
	return _OPENGB_IS_6N(cid->birthday); //理论上应该不存在190X年的生日。

}
bool IsNullCId(const CitizenId * const cid){
	return cid->area==0&&cid->birthday==0&&cid->order==0&&cid->checksum==0;
}



CitizenId CloneCId(const CitizenId * const cid){
	CitizenId r;
	memcpy(&r,cid,sizeof(CitizenId));
	return r;
}
CitizenId To18CId(const CitizenId * const cid){
	CitizenId r=OPENGB_CID_NULL;
	if(Is15CId(cid)){
		r.area=cid->area;
		r.birthday=cid->birthday%1000000UL;
		r.order=cid->order;
		r.checksum=0;
	}else if(Is18CId(cid)){
		r=CloneCId(cid);
	}else{
		_OPENGB_THROW(OPENGB_BASE_EC_ARGUMENT_NULL)
	}
	return r;
}
CitizenId To15CId(const CitizenId * const cid);



bool VerifyCId(const CitizenId * const cid){
	bool r=true;

	//bool VerifyCIdArea(const CitizenId *cid)

	if(!VerifyCIdOrder(cid)) return false;

	if(Is15CId(cid)){
		if(cid->checksum!=0) return false;
	}else if(Is18CId(cid)){
		if(!VerifyCIdOrder(cid)) return false;
	}else{
		return false;
	}

	if(r){
		return true;
	}else{
		_OPENGB_THROW(OPENGB_CID_EC_CID_DATA_ERROR)
		return false;
	}
}
//bool VerifyCIdArea(const CitizenId *cid);
inline bool VerifyCIdBirthday(const CitizenId * const cid){
	return _OPENGB_IS_8N(cid->birthday) || _OPENGB_IS_6N(cid->birthday);
}
inline bool VerifyCIdOrder(const CitizenId * const cid){
	return 0<=cid->order&&cid->order<=999;
}
inline bool VerifyCIdChecksum(const CitizenId * const _18cid){
	return _18cid->checksum==_OPENGB_MOD11_2_METHOD(_18cid);
}

#if defined(OPENGB_CODE_PREFER_FAST)
const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[OPENGB_CID_18CID_LENGTH] = {1,2,4,8,5,10,9,7,3,6,1,2,4,8,5,10,9,7};
const OPENGB_CID_CHECKSUM_TYPE _mod11_2_trs_list[OPENGB_MOD11_2_MOD_CONSTANT_NUMBER]={1,0,10,9,8,7,6,5,4,3,2}; //transform list
#elif defined(OPENGB_CODE_PREFER_TIGHT)
const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[10] = {1,2,4,8,5,10,9,7,3,6};
#endif

#if defined(OPENGB_CODE_PREFER_FAST)

OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(const CitizenId * const _18cid){
	unsigned int sum=0;
	const OPENGB_MOD11_2_W_LIST_TYPE *ptr_w=_mod11_2_w_list+1;
	int i, iend;
	CitizenId cid=*_18cid;
	div_t div_result;
	OPENGB_CID_CHECKSUM_TYPE r;
	
	if(!Is18CId(_18cid)){
		_OPENGB_THROW(OPENGB_CID_EC_NOT_18CID)
		return _OPENGB_MOD11_2_METHOD_BAD_RETURN;
	}
	
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

#elif defined(OPENGB_CODE_PREFER_TIGHT)

OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_tt(const CitizenId * const _18cid){
	unsigned char i, sum=0;
	CitizenId cid=*_18cid;
	div_t div_result;
	
	if(!Is18CId(_18cid)){
		_OPENGB_THROW(OPENGB_CID_EC_NOT_18CID)
		return _OPENGB_MOD11_2_METHOD_BAD_RETURN;
	}
	
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
		div_result = div(cid.area,10);
		sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		cid.area=div_result.quot;
	}
	
	return OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER == OPENGB_MOD11_2_MOD_CONSTANT_NUMBER
		? 0 : OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
}

#endif