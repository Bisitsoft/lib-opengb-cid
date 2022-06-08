// Check Defination of Code Preference
//#if !defined(__ckdef_code_prefer_h_)
//	#define __ckdef_code_prefer_h_
	
	//检查宏定义
	#if !defined(OPENGB_CODE_PREFER_FAST)
		#if !defined(OPENGB_CODE_PREFER_TIGHT)
			#error Please define OPENGB_CODE_PREFER_FAST or OPENGB_CODE_PREFER_TIGHT for continuing compilation.
		#endif
	#elif defined(OPENGB_CODE_PREFER_TIGHT)
		#error You can only define one between OPENGB_CODE_PREFER_FAST and OPENGB_CODE_PREFER_TIGHT for compilation.
	#endif
	
//#endif