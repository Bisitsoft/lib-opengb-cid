// Citizen Identification Number
// GB 11643-1999

#include "ctzidn.h"

#include <stdlib.h>
#include <string.h>

// Judge whether it is a 6-digit number.
#define _OPENGB_IS_6N(n) (100000<=(n)&&(n)<=999999)
// Judge whether it is a 8-digit number.
#define _OPENGB_IS_8N(n) (10000000<=(n)&&(n)<=99999999)



int CId_GetSex(const CitizenId* const cid){
	return cid->order%2 == 0 ? OPENGB_CID_SEX_FEMALE : OPENGB_CID_SEX_MALE;
}



bool Is18CId(const CitizenId* const cid){
	return _OPENGB_IS_8N(cid->birthday);
}
bool Is15CId(const CitizenId* const cid){
	return _OPENGB_IS_6N(cid->birthday); //理论上应该不存在190X年的生日。 Theoretically, there should be no birthday in 190X.
}
int CompareCId(const CitizenId* const x, const CitizenId* const y){
	CitizenIdZip1 zipped_x=CId_ToZip1(x);
	CitizenIdZip1 zipped_y=CId_ToZip1(y);

	return CompareZip1CId(zipped_x,zipped_y);
}
int CompareZip1CId(const CitizenIdZip1 x, const CitizenIdZip1 y){
	if(x>y){
		return 1;
	}else if (x==y){
		return 0;
	}else{
		return -1;
	}
	
}
bool IsNullCId(const CitizenId* const cid){
	return cid->area==0&&cid->birthday==0&&cid->order==0&&cid->checksum==0;
}
bool IsNullCIdZip1(const CitizenIdZip1 cid){
	return cid==OPENGB_CID_ZIP1_NULL;
}
//!WIP: GetCIdType(). Return `OPENGB_CID_TYPE_*`.



CitizenId To18CId(const CitizenId* cid){
	CitizenId r=OPENGB_CID_NULL;
	if(Is15CId(cid)){
		r.area=cid->area;
		r.birthday=cid->birthday+19000000UL;
		r.order=cid->order;
		r.checksum=_OPENGB_MOD11_2_METHOD(&r);
	}else if(Is18CId(cid)){
		return *cid;
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
		return *cid;
	}else{
		_OPENGB_THROW(OPENGB_BASE_EC_ARGUMENT_NULL)
	}
	return r;
}



bool VerifyCId(const CitizenId* const cid){
	if(!_VerifyCIdArea(cid)) return false;
	if(!_VerifyCIdBirthday(cid)) return false;
	if(!_VerifyCIdOrder(cid)) return false;
	
	if(Is15CId(cid)){
		if(cid->checksum!=0) return false;
	}else if(Is18CId(cid)){
		if(!_VerifyCIdChecksum(cid)) return false;
	}else{
		return false;
	}

	return true;
}
inline bool _VerifyCIdArea(const CitizenId* const cid){
//!WIP:	Use `lib-opengb-acd` to verify whether the area code is existed. \
		Attention: Don't forget area code could be delete and change. So it will just return a warning, not error.
	return 0<=cid->area&&cid->area<=999999;
}
inline bool _VerifyCIdBirthday(const CitizenId* const cid){
	return _OPENGB_IS_8N(cid->birthday) || _OPENGB_IS_6N(cid->birthday);
}
inline bool _VerifyCIdOrder(const CitizenId* const cid){
	return 0<=cid->order&&cid->order<=999;
}
inline bool _VerifyCIdChecksum(const CitizenId* const _18cid){
	return _18cid->checksum==_OPENGB_MOD11_2_METHOD(_18cid);
}


//!WIP: StringToCId.
//bool ToCId(const char const * text, const int text_Length, CitizenId * const _out){
//	strnlen_s
//}
int CId_ToString(const CitizenId * const cid, char* const _out, const int out_buffer_size){
	if(Is18CId(cid)){
		if(out_buffer_size<19){
			_OPENGB_THROW(OPENGB_BASE_EC_BUFFER_NOT_ENOUGH)
			return -1;
		}
		//return sprintf_s(_out,out_buffer_size,"%06u%08u%03u%c",cid->area,cid->birthday,cid->order,(cid->checksum<10?'0'+cid->checksum:'X'));
		return sprintf(_out,"%06u%08u%03u%c",cid->area,cid->birthday,cid->order,(cid->checksum<10?'0'+cid->checksum:'X'));
	}else if(Is15CId(cid)){
		if(out_buffer_size<16){
			_OPENGB_THROW(OPENGB_BASE_EC_BUFFER_NOT_ENOUGH)
			return -1;
		}
		//return sprintf_s(_out,out_buffer_size,"%06u%06u%03u",cid->area,cid->birthday,cid->order);
		return sprintf(_out,"%06u%06u%03u",cid->area,cid->birthday,cid->order);
	}

	_OPENGB_THROW(OPENGB_CID_EC_CID_DATA_ERROR)
	return -1;
}

CitizenIdZip1 CId_ToZip1(const CitizenId* const cid){
	CitizenIdZip1 r=0;

	r|=((CitizenIdZip1)(cid->area))<<43;
	r|=((CitizenIdZip1)(cid->birthday))<<14;
	r|=((CitizenIdZip1)(cid->order))<<4;
	r|=(CitizenIdZip1)(cid->checksum);

	return r;
}
CitizenId CId_FromZip1(const CitizenIdZip1 cid){
	CitizenId r;

	r.area=_UNZIP1_CID_AREA(cid);
	r.birthday=_UNZIP1_CID_BIRTHDAY(cid);
	r.order=_UNZIP1_CID_ORDER(cid);
	r.checksum=_UNZIP1_CID_CHECKSUM(cid);

	return r;
}

const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[OPENGB_CID_18CID_LENGTH] = {2,4,8,5,10,9,7,3,6,1,2};
const OPENGB_CID_CHECKSUM_TYPE _mod11_2_trs_list[OPENGB_MOD11_2_MOD_CONSTANT_NUMBER]={1,0,10,9,8,7,6,5,4,3,2}; //transform list

void _gb11643_1999_mod11_2_sub(unsigned char* sum, int value, const OPENGB_MOD11_2_W_LIST_TYPE* w_begin);

const OPENGB_MOD11_2_W_LIST_TYPE* const _mod11_2_w_list_1=_mod11_2_w_list+1;
const OPENGB_MOD11_2_W_LIST_TYPE* const _mod11_2_w_list_3=_mod11_2_w_list+3;

OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2(const CitizenId* const _18cid){
	unsigned char sum=0;
	CitizenId cid=*_18cid;
	div_t div_result;
	OPENGB_CID_CHECKSUM_TYPE r;
	
	if(!Is18CId(_18cid)){
		_OPENGB_THROW(OPENGB_CID_EC_NOT_18CID)
		return _OPENGB_MOD11_2_METHOD_BAD_RETURN;
	}
	
	_gb11643_1999_mod11_2_sub(&sum, _18cid->order, _mod11_2_w_list);
	_gb11643_1999_mod11_2_sub(&sum, _18cid->birthday, _mod11_2_w_list_3);
	_gb11643_1999_mod11_2_sub(&sum, _18cid->area, _mod11_2_w_list_1);
	
	//r=OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
	r=_mod11_2_trs_list[sum%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER];
	return r==OPENGB_MOD11_2_MOD_CONSTANT_NUMBER?0:r;
}

// Because `div` use `int` as parameter, we use `int` as type of `value`.
void _gb11643_1999_mod11_2_sub(unsigned char* sum, int value, const OPENGB_MOD11_2_W_LIST_TYPE* w_begin){
	div_t div_result;

	while(value>9){
		div_result = div(value,10);
		(*sum)+=div_result.rem*_mod11_2_w_list[*(w_begin++)];
		value=div_result.quot;
	}
	if(value!=0){
		(*sum)+=value*_mod11_2_w_list[*w_begin];
	}
}
