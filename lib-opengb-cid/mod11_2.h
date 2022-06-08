// ISO 7064:1983 Mod11-2 for GB 11643-1999

#if !defined(__mod11_2_h_)
	#define __mod11_2_h_
	#include "opengb_cid_switches.h"
	
	#include "mod11_2_def.h"
	
	#include <cmath>
	
	#include "ctzidn.h"
	#include "opengbex.h"
	
namespace opengb{
	
	#if defined(OPENGB_CODE_PREFER_FAST)
	const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[OPENGB_CID_18CID_LENGTH] = {1,2,4,8,5,10,9,7,3,6,1,2,4,8,5,10,9,7};
	const OPENGB_CID_CHECKSUM_TYPE _mod11_2_trs_list[OPENGB_MOD11_2_MOD_CONSTANT_NUMBER]={1,0,10,9,8,7,6,5,4,3,2}; //transform list
	#elif defined(OPENGB_CODE_PREFER_TIGHT)
	const OPENGB_MOD11_2_W_LIST_TYPE _mod11_2_w_list[10] = {1,2,4,8,5,10,9,7,3,6};
	#endif
	
	#if defined(OPENGB_CODE_PREFER_FAST)
		#define _OPENGB_MOD11_2_METHOD(_18cid) (opengb::_gb11643_1999_mod11_2_fst(_18cid))
	ctzidn::OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(OPENGB_MOD11_2_METHOD_ARG_TYPE _18cid);
	#elif defined(OPENGB_CODE_PREFER_TIGHT)
		#define _OPENGB_MOD11_2_METHOD(_18cid) (opengb::_gb11643_1999_mod11_2_tt(_18cid))
	ctzidn::OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_tt(OPENGB_MOD11_2_METHOD_ARG_TYPE _18cid);
	#endif

}

#endif