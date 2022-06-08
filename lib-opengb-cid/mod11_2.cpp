

#include "mod11_2.h"

using opengb;

#if defined(OPENGB_CODE_PREFER_FAST)

ctzidn::OPENGB_CID_CHECKSUM_TYPE opengb::_gb11643_1999_mod11_2_fst(OPENGB_MOD11_2_METHOD_ARG_TYPE _18cid){
	unsigned int sum=0;
	const OPENGB_MOD11_2_W_LIST_TYPE *ptr_w=_mod11_2_w_list+1;
	int i, iend;
	div_t div_result;
	ctzidn::OPENGB_CID_CHECKSUM_TYPE r;
	
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
	
	//r=OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
	r=_mod11_2_trs_list[sum%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER];
	return r==OPENGB_MOD11_2_MOD_CONSTANT_NUMBER?0:r;
}

#elif defined(OPENGB_CODE_PREFER_TIGHT)

ctzidn::OPENGB_CID_CHECKSUM_TYPE opengb::_gb11643_1999_mod11_2_tt(OPENGB_MOD11_2_METHOD_ARG_TYPE _18cid){
	unsigned char i, sum=0;
	div_t div_result;
	
//#warning Commented!
	//if(!_18cid.Is18CId()){
	//	throw ;
	//}
	
	for(i=1;i<=OPENGB_CID_18CID_ORDER_LENGTH;i++){
		div_result = div(_18cid.m_cid.order,10);
		sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		_18cid.m_cid.order=div_result.quot;
	}
	for(;i<=OPENGB_CID_18CID_ORDER_LENGTH+OPENGB_CID_18CID_BIRTHDAY_LENGTH;i++){
		div_result = div(_18cid.m_cid.birthday,10);
		sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		_18cid.m_cid.birthday=div_result.quot;
	}
	for(;i<=OPENGB_CID_18CID_ORDER_LENGTH+OPENGB_CID_18CID_BIRTHDAY_LENGTH+OPENGB_CID_18CID_AREA_LENGTH;i++){
		div_result = div(_18cid.m_cid.area,10);
		sum+=div_result.rem*_mod11_2_w_list[i/(sizeof(_mod11_2_w_list)/sizeof(OPENGB_MOD11_2_W_LIST_TYPE))]%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
		_18cid.m_cid.area=div_result.quot;
	}
	
	return OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER == OPENGB_MOD11_2_MOD_CONSTANT_NUMBER
		? 0 : OPENGB_MOD11_2_MOD_CONSTANT_NUMBER-(sum-1)%OPENGB_MOD11_2_MOD_CONSTANT_NUMBER;
}

#endif
