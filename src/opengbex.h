// OpenGB Exception

#if !defined(__opengbex_h_)
	#define __opengbex_h_
	#include "opengb_cid_switches.h"



	#define OPENGB_ERROR_CODE_TYPE unsigned int
	#define OPENGB_EC_MAKE(label, ec) (label|ec)
	#define OPENGB_NO_ERROR 0UL



// === OpenGB Base Error Code Begin ==:
	#define OPENGB_BASE_EC_LABEL 0x00000000UL
	#define OPENGB_BASE_EC_MAKE(ec) OPENGB_EC_MAKE(OPENGB_BASE_EC_LABEL, ec)

	#define OPENGB_BASE_EC_NO_ERROR OPENGB_NO_ERROR
	#define OPENGB_BASE_EC_ARGUMENT_NULL OPENGB_BASE_EC_MAKE(0x000001)
	
	#define OPENGB_BASE_EC_UNKNOWN_ERROR_CODE_MSG "Unknown error code!"
	#define OPENGB_BASE_EC_NO_ERROR_MSG "No error."
	#define OPENGB_BASE_EC_ARGUMENT_NULL_MSG "Argument is NULL."
// :==  OpenGB Base Error Code End  ===



// === OpenGB CId Error Code Begin ==:
	#define OPENGB_CID_EC_LABEL 0x01000000UL
	#define OPENGB_CID_EC_MAKE(ec) OPENGB_EC_MAKE(OPENGB_CID_EC_LABEL, ec)

	#define OPENGB_CID_EC_NOT_18CID OPENGB_CID_EC_MAKE(0x000001)
	#define OPENGB_CID_EC_CID_DATA_ERROR OPENGB_CID_EC_MAKE(0x000002)

	#define OPENGB_CID_EC_NOT_18CID_MSG "Not a 18-digit CId!"
	#define OPENGB_CID_EC_CID_DATA_ERROR_MSG "CitizenId data error!"
// :==  OpenGB CId Error Code End  ===



int opengb_GetLastOpenGBErrorCode();
void opengb_SetLastOpenGBErrorCode(OPENGB_ERROR_CODE_TYPE errorCode);

	#define _OPENGB_THROW(errorCode) opengb_SetLastOpenGBErrorCode(errorCode);
	#define _OPENGB_TRY opengb_SetLastOpenGBErrorCode(OPENGB_NO_ERROR);
	#define _OPENGB_CATCH(errorCode) if(opengb_GetLastOpenGBErrorCode()==errorCode){
	#define _OPENGB_CATCHX(errorCode) }else if(opengb_GetLastOpenGBErrorCode()==errorCode){
	#define _OPENGB_CATCH_CLOSE }

	#ifdef OPENGB_EX_COMPILE_ECTOSTR
int opengb_ErrorCodeToString(const OPENGB_ERROR_CODE_TYPE error_code, char * const _out_msg, const int maxLen); //return -1 for failure, >0 for success and length.
	#endif

#endif