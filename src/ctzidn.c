// Citizen Identification Number
// GB 11643-1999

#include "ctzidn.h"

#include <stdlib.h>
#include <string.h>

#define _OPENGB_IS_6N(n) (100000<=(n)&&(n)<=999999) //Judge whether it is a 6-digit number.
#define _OPENGB_IS_8N(n) (10000000<=(n)&&(n)<=99999999) //Judge whether it is a 8-digit number.

int GetSex(const CitizenId* const cid){
	return cid->order%2 == 0 ? OPENGB_CID_SEX_FEMALE : OPENGB_CID_SEX_MALE;
}



bool Is18CId(const CitizenId* const cid){
	return _OPENGB_IS_8N(cid->birthday);
}
bool Is15CId(const CitizenId* const cid){
	return _OPENGB_IS_6N(cid->birthday); //理论上应该不存在190X年的生日。 Theoretically, there should be no birthday in 190X.

}
bool IsNullCId(const CitizenId* const cid){
	return cid->area==0&&cid->birthday==0&&cid->order==0&&cid->checksum==0;
}
bool IsNullCId(const CitizenIdZip1 cid){
	return cid==OPENGB_CID_ZIP1_NULL;
}



CitizenId CloneCId(const CitizenId* cid){
	CitizenId r;
	memcpy(&r,cid,sizeof(CitizenId));
	return r;
}
CitizenId To18CId(const CitizenId* cid){
	CitizenId r=OPENGB_CID_NULL;
	if(Is15CId(cid)){
		r.area=cid->area;
		r.birthday=cid->birthday+19000000UL;
		r.order=cid->order;
		r.checksum=_OPENGB_MOD11_2_METHOD(&r);
	}else if(Is18CId(cid)){
		r=CloneCId(cid);
	}else{
		_OPENGB_THROW(OPENGB_BASE_EC_ARGUMENT_NULL)
	}
	return r;
}
CitizenId To15CId(const CitizenId* cid){
	CitizenId r=OPENGB_CID_NULL;
	if(Is18CId(cid)){
		r.area=cid->area;
		r.birthday=cid->birthday%1000000UL;
		r.order=cid->order;
		r.checksum=0;
	}else if(Is15CId(cid)){
		r=CloneCId(cid);
	}else{
		_OPENGB_THROW(OPENGB_BASE_EC_ARGUMENT_NULL)
	}
	return r;
}



bool VerifyCId(const CitizenId* const cid){
	if(Is15CId(cid)){
		if(cid->checksum!=0) return false;
	}else if(Is18CId(cid)){
		if(!VerifyCIdOrder(cid)) return false;
	}else{
		return false;
	}

	if(!_VerifyCIdArea(cid)) return false;
	if(!_VerifyCIdBirthday(cid)) return false;
	if(!_VerifyCIdOrder(cid)) return false;
	if(!_VerifyCIdChecksum(cid)) return false;

	return true;
}


bool ToCId(const char const * text, const int text_Length, CitizenId * const _out){
	strnlen_s
}
int ToString(const CitizenId * const cid, char* const _out, const int out_buffer_size){
	errno_t r;
	if(Is18CId(cid)){
		if(out_buffer_size<19){
			_OPENGB_THROW(OPENGB_BASE_EC_BUFFER_NOT_ENOUGH)
			return -1;
		}
		return sprintf_s(_out,out_buffer_size,"%06u%08u%03u%1u",cid->area,cid->birthday,cid->order,cid->checksum);
	}else if(Is15CId(cid)){
		if(out_buffer_size<16){
			_OPENGB_THROW(OPENGB_BASE_EC_BUFFER_NOT_ENOUGH)
			return -1;
		}
		return sprintf_s(_out,out_buffer_size,"%06u%06u%03u",cid->area,cid->birthday,cid->order);
	}

	_OPENGB_THROW(OPENGB_CID_EC_CID_DATA_ERROR_MSG)
	return -1;
}

CitizenIdZip1 Zip1(const CitizenId* const cid){
	CitizenIdZip1 r=0;

	r|=((CitizenIdZip1)cid->area)<<44;
	r|=((CitizenIdZip1)cid->birthday)<<14;
	r|=((CitizenIdZip1)cid->order)<<4;
	r|=(CitizenIdZip1)cid->checksum;

	return r;
}
CitizenId Unzip1(const CitizenIdZip1 cid){
	CitizenId r;

	r.area=_UNZIP1_CID_AREA(cid);
	r.birthday=_UNZIP1_CID_BIRTHDAY(cid);
	r.order=_UNZIP1_CID_ORDER(cid);
	r.checksum=_UNZIP1_CID_CHECKSUM(cid);

	return r;
}

#if defined(OPENGB_CODE_PREFER_FAST)
const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[OPENGB_CID_18CID_LENGTH] = {1,2,4,8,5,10,9,7,3,6,1,2,4,8,5,10,9,7};
const OPENGB_CID_CHECKSUM_TYPE _mod11_2_trs_list[OPENGB_MOD11_2_MOD_CONSTANT_NUMBER]={1,0,10,9,8,7,6,5,4,3,2}; //transform list
#elif defined(OPENGB_CODE_PREFER_TIGHT)
const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[11] = {2,4,8,5,10,9,7,3,6,1,2};
#endif

#if defined(OPENGB_CODE_PREFER_FAST)

OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(const CitizenId* const _18cid){
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
	
	for(i=0, iend=OPENGB_CID_18CID_ORDER_LENGTH;i<iend;++i){
		div_result = div(cid.order,10);
//#warning 测试此处指针是否比直接用数组快
		sum+=div_result.rem*(*(ptr_w++));
		cid.order=div_result.quot;
	}
	for(iend+=OPENGB_CID_18CID_BIRTHDAY_LENGTH;i<iend;++i){
		div_result = div(cid.birthday,10);
		sum+=div_result.rem*(*(ptr_w++));
		cid.birthday=div_result.quot;
	}
	for(iend+=OPENGB_CID_18CID_AREA_LENGTH;i<iend;++i){
		div_result = div(cid.area,10);
		sum+=div_result.rem*(*(ptr_w++));
		cid.area=div_result.quot;
	}
	
	//r=OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
	r=_mod11_2_trs_list[sum%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER];
	return r==OPENGB_MOD11_2_MOD_CONSTANT_NUMBER?0:r;
}

#elif defined(OPENGB_CODE_PREFER_TIGHT)

// Because `div` use `int` as parameter, we use `int` as type of `value`.
inline void _gb11643_1999_mod11_2_tt_sub(unsigned char* sum, int value, int begin){
	div_t div_result;

	while(value>0){
		div_result = div(value,10);
		(*sum)+=div_result.rem*_mod11_2_w_list[begin]%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		value=div_result.quot;
		++begin;
	}
}

OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_tt(const CitizenId* const _18cid){
	unsigned char sum=0;
	CitizenId cid=*_18cid;
	div_t div_result;
	
	if(!Is18CId(_18cid)){
		_OPENGB_THROW(OPENGB_CID_EC_NOT_18CID)
		return _OPENGB_MOD11_2_METHOD_BAD_RETURN;
	}
	
	_gb11643_1999_mod11_2_tt_sub(&sum, _18cid->order, 0);
	_gb11643_1999_mod11_2_tt_sub(&sum, _18cid->birthday, 3);
	_gb11643_1999_mod11_2_tt_sub(&sum, _18cid->area, 1);
	
	return OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER == OPENGB_MOD11_2_MOD_CONSTANT_NUMBER
		? 0 : OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
}

#endif
