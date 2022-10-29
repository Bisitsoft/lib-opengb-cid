// lib-opengb-cid Switches

#if !defined(__opengb_cid_switches_h_)
	#define __opengb_cid_switches_h_

// To lib-opengb-cid Maintainers:
//   Please do not add or remove any macro in this zone.
//   You could only uncomment or use `//` to comment `#define _OPENGB_CID_SWITCHES_FIRST_EDIT`.
//   And here is the only place for define this macro only one time.
//   However, if anyone changed this zone, please remember to change `Pre-commit Mode` and `Development Mode` scripts in `opengb-cid-switched.sh`, too.
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
	
	//#define OPENGB_CODE_PREFER_FAST // Make code faster, but use more memories. It is mutually exclusive with OPENGB_CODE_PREFER_TIGHT.
	#define OPENGB_CODE_PREFER_TIGHT // Make code save memories, but running slowly. It is mutually exclusive with OPENGB_CODE_PREFER_FAST.

	#define OPENGB_EX_ENABLE_ECTOSTR // Enable error code converte to string functions.
	
// :==  Editable Zone 2/2 End  ===

	// The default value of OpenGB Code Preferance
	#if !defined(OPENGB_CODE_PREFER_FAST) && !defined(OPENGB_CODE_PREFER_TIGHT)
		#define OPENGB_CODE_PREFER_FAST
	#endif
	
	// Check Defination of Code Preference
	#include "ckdef_code_prefer.h"
	
#endif
