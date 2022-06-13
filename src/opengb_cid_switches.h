#if !defined(__opengb_cid_switches_h_)
	#define __opengb_cid_switches_h_

// === Editable Zone 1/2 Begin ==:
	
	#define _OPENGB_CID_SWITCHES_FIRST_EDIT
	
// :==  Editable Zone 1/2 End  ===
	#if defined(_OPENGB_CID_SWITCHES_FIRST_EDIT)
		#error When you first use this library, you will see this error message. \
It is telling you here is header file with many macros of switch compilation. \
If you has known this, you can comment out the line "#define _OPENGB_CID_SWITCHES_FIRST_EDIT" shown above, \
and keep going your work. \
Have fun! :)
	#endif
	
// === Editable Zone 2/2 Begin ==:
	
	//#define OPENGB_CODE_PREFER_FAST
	#define OPENGB_CODE_PREFER_TIGHT

	#define OPENGB_EX_COMPILE_ECTOSTR
	
// :==  Editable Zone 2/2 End  ===

	#if !defined(OPENGB_CODE_PREFER_FAST) && !defined(OPENGB_CODE_PREFER_TIGHT)
		#define OPENGB_CODE_PREFER_FAST
	#endif
	
	#include "ckdef_code_prefer.h"
	
#endif
