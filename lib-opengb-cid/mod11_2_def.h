#if !defined(__mod11_2_def_h_)
	#define __mod11_2_def_h_
	
	#define OPENGB_MOD11_2_MOD_CONSTANT_NUMBER 11
	
	#if defined(OPENGB_CODE_PREFER_FAST)
typedef unsigned int OPENGB_MOD11_2_W_LIST_TYPE;
	#elif defined(OPENGB_CODE_PREFER_TIGHT)
typedef unsigned char OPENGB_MOD11_2_W_LIST_TYPE;
	#endif
	
	#include "ctzidn.h"

typedef const opengb::ctzidn::CitizenId OPENGB_MOD11_2_METHOD_ARG_TYPE;
	
#endif