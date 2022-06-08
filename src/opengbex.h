// OpenGB Exception

#if !defined(__opengbex_h_)
	#define __opengbex_h_

// === OpenGB Base Error Code Begin ==:
#define OPENGB_NO_ERROR 0
// :==  OpenGB Base Error Code End  ===



// === OpenGB CId Error Code Begin ==:

// :==  OpenGB CId Error Code End  ===



int opengb_GetLastErrorCode();
void opengb_SetLastErrorCode(int code);

#endif