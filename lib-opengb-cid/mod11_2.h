// ISO 7064:1983 in GB 11643-1999

#ifndef __mod11_2_h_
	#define __mod11_2_h_
	
	#include <cmath>
	
	#include "ctzidn.h"
	
namespace opengb{

	#define _OPENGB_MOD11_2_MOD_CONSTANT_NUMBER 11

	#ifdef OPENGB_CODE_PERFER_FAST
		#define OPENGB_MOD11_2_W_LIST_TYPE int
	OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[OPENGB_CID_18CID_LENGTH] = {1,2,4,8,5,10,9,7,3,6,1,2,4,8,5,9,7};
	#elif OPENGB_CODE_PERFER_TIGHT
		#define OPENGB_MOD11_2_W_LIST_TYPE unsigned char
	OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[10] = {1,2,4,8,5,10,9,7,3,6};
	#endif

	#ifndef OPENGB_CODE_PERFER_FAST
		#define _OPENGB_MOD11_2_METHOD(arg) (_gb11643_1999_mod11_2_fst(arg))
	OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(opengb::cid::CitizenId &_18cid){
		unsigned int sum=0;
		OPENGB_MOD11_2_W_LIST_TYPE *ptr_w=w+1;
		int i, iend;
		div_t div_result;
		OPENGB_CID_CHECKSUM_TYPE r;
		
		if(!_18cid.Is18CId()){
			throw ;
		}
		
		for(i=1, iend=OPENGB_CID_18CID_ORDER_LENGTH;i<iend;i++){
			div_result = div(_18cid.order,10);
#warning 测试此处指针是否比直接用数组快
			sum+=div_result.rem*(*(w++));
			_18cid.order=div_result.quot;
		}
		for(iend+=OPENGB_CID_18CID_BIRTHDAY_LENGTH;i<iend;i++){
			div_result = div(_18cid.birthday,10);
			sum+=div_result.rem*(*(w++));
			_18cid.order=div_result.quot;
		}
		for(iend+=OPENGB_CID_18CID_AREA_LENGTH;i<iend;i++){
			div_result = div(_18cid.area,10);
			sum+=div_result.rem*(*(w++));
			_18cid.order=div_result.quot;
		}
		
		r=_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		return r==_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER?0:r;
	}
	#elif OPENGB_CODE_PERFER_TIGHT
		#define _OPENGB_MOD11_2_METHOD(arg) (_gb11643_1999_mod11_2_fst(arg))
	OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(opengb::cid::CitizenId &_18cid){
		unsigned char i, sum=0;
		
		if(!_18cid.Is18CId()){
			throw ;
		}
		
		for(i=1；i<OPENGB_CID_18CID_ORDER_LENGTH;i++){
			div_result = div(_18cid.order,10);
			sum+=div_result.rem*w[(i++)/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
			_18cid.order=div_result.quot;
		}
		for(;i<OPENGB_CID_18CID_ORDER_LENGTH+OPENGB_CID_18CID_BIRTHDAY_LENGTH;i++){
			div_result = div(_18cid.birthday,10);
			sum+=div_result.rem*w[(i++)/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
			_18cid.order=div_result.quot;
		}
		for(;i<OPENGB_CID_18CID_ORDER_LENGTH+OPENGB_CID_18CID_BIRTHDAY_LENGTH+OPENGB_CID_18CID_AREA_LENGTH;i++){
			div_result = div(_18cid.area,10);
			sum+=div_result.rem*w[(i++)/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
			_18cid.order=div_result.quot;
		}
		
		return _OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER == _OPENGB_MOD11_2_MOD_CONSTANT_NUMBER
			? 0 : _OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
	}
	#endif

}

#endif