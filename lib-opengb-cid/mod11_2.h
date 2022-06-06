// ISO 7064:1983 Mod11-2 for GB 11643-1999

#if !defined(__mod11_2_h_)
	#define __mod11_2_h_
	
	//检查宏定义
	#if !defined(OPENGB_CODE_PERFER_FAST)
		#if !defined(OPENGB_CODE_PERFER_TIGHT)
			#error Please define OPENGB_CODE_PERFER_FAST or OPENGB_CODE_PERFER_TIGHT for continuing compilation.
		#endif
	#elif defined(OPENGB_CODE_PERFER_TIGHT)
		#error You can only define one between OPENGB_CODE_PERFER_FAST and OPENGB_CODE_PERFER_TIGHT for compilation.
	#endif
	
	#include <cmath>
	
	#include "ctzidn.h"
	#include "opengbex.h"
	
namespace opengb{

	#define _OPENGB_MOD11_2_MOD_CONSTANT_NUMBER 11

	#if defined(OPENGB_CODE_PERFER_FAST)
		#define OPENGB_MOD11_2_W_LIST_TYPE unsigned int
	const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[OPENGB_CID_18CID_LENGTH] = {1,2,4,8,5,10,9,7,3,6,1,2,4,8,5,10,9,7};
	#elif defined(OPENGB_CODE_PERFER_TIGHT)
		#define OPENGB_MOD11_2_W_LIST_TYPE unsigned char
	const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[10] = {1,2,4,8,5,10,9,7,3,6};
	#endif

	#if defined(OPENGB_CODE_PERFER_FAST)
		#define _OPENGB_MOD11_2_METHOD(_18cid) (opengb::_gb11643_1999_mod11_2_fst(_18cid))
	OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(opengb::cizidn::CitizenId _18cid){
		unsigned int sum=0;
		const OPENGB_MOD11_2_W_LIST_TYPE *ptr_w=_mod11_2_w_list+1;
		int i, iend;
		div_t div_result;
		OPENGB_CID_CHECKSUM_TYPE r;
		
//#warning Commented!
		//if(!_18cid.Is18CId()){
		//	throw ;
		//}
		
		for(i=0, iend=OPENGB_CID_18CID_ORDER_LENGTH;i<iend;i++){
			div_result = div(_18cid.m_cid.order,10);
//#warning 测试此处指针是否比直接用数组快
			sum+=div_result.rem*(*(ptr_w++));
			_18cid.m_cid.order=div_result.quot;
		}
		for(iend+=OPENGB_CID_18CID_BIRTHDAY_LENGTH;i<iend;i++){
			div_result = div(_18cid.m_cid.birthday,10);
			sum+=div_result.rem*(*(ptr_w++));
			_18cid.m_cid.birthday=div_result.quot;
		}
		for(iend+=OPENGB_CID_18CID_AREA_LENGTH;i<iend;i++){
			div_result = div(_18cid.m_cid.area,10);
			sum+=div_result.rem*(*(ptr_w++));
			_18cid.m_cid.area=div_result.quot;
		}
		
		r=_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		return r==_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER?0:r;
	}
	#elif defined(OPENGB_CODE_PERFER_TIGHT)
		#define _OPENGB_MOD11_2_METHOD(_18cid) (opengb::_gb11643_1999_mod11_2_tt(_18cid))
	OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_tt(opengb::cizidn::CitizenId _18cid){
		unsigned char i, sum=0;
		div_t div_result;
		
//#warning Commented!
		//if(!_18cid.Is18CId()){
		//	throw ;
		//}
		
		for(i=1;i<=OPENGB_CID_18CID_ORDER_LENGTH;i++){
			div_result = div(_18cid.m_cid.order,10);
			sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
			_18cid.m_cid.order=div_result.quot;
		}
		for(;i<=OPENGB_CID_18CID_ORDER_LENGTH+OPENGB_CID_18CID_BIRTHDAY_LENGTH;i++){
			div_result = div(_18cid.m_cid.birthday,10);
			sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
			_18cid.m_cid.birthday=div_result.quot;
		}
		for(;i<=OPENGB_CID_18CID_ORDER_LENGTH+OPENGB_CID_18CID_BIRTHDAY_LENGTH+OPENGB_CID_18CID_AREA_LENGTH;i++){
			div_result = div(_18cid.m_cid.area,10);
			sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
			_18cid.m_cid.area=div_result.quot;
		}
		
		return _OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER == _OPENGB_MOD11_2_MOD_CONSTANT_NUMBER
			? 0 : _OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%_OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
	}
	#endif

}

#endif