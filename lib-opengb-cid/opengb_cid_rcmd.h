// lib-opengb-cid Recommand
// Please include this before inlcude other lib-opengb-cid headers.

#if !defined(__opengb_cid_rcmd_h_)
	#define __opengb_cid_rcmd_h_
	
	#if !defined(OPENGB_CODE_PERFER_FAST) && !defined(OPENGB_CODE_PERFER_TIGHT)
		#define OPENGB_CODE_PERFER_FAST
	#endif
	
	#include "ctzidn.h"
	#include "mod11_2.h"
	#include "opengbex.h"
	
#endif