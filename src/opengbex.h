// OpenGB Exception

#ifndef __opengbex_h_
	#define __opengbex_h_
	#include "opengb_cid_switches.h"



typedef unsigned int OPENGB_ERROR_CODE_TYPE;
	// Use `label`(type) as high bits (mask=0xF000) and `ec`(error code) as low bits (mask=0x0FFF) to make a complete error code.
	#define OPENGB_EC_MAKE(label, ec) ((label)|(ec))
	// No error.
	#define OPENGB_NO_ERROR 0UL

// Each error code has its description(_MSG).
//!WIP:	!!!For saving memory, should use a constant string array to instead macro string.

// === OpenGB Base Error Code Begin ==:
	// Label: Base
	#define OPENGB_BASE_EC_LABEL 0x00000000UL
	// Make base error code.
	#define OPENGB_BASE_EC_MAKE(ec) OPENGB_EC_MAKE((OPENGB_BASE_EC_LABEL), (ec))

	#define OPENGB_BASE_EC_NO_ERROR OPENGB_NO_ERROR

	#define OPENGB_BASE_EC_ARGUMENT_NULL OPENGB_BASE_EC_MAKE(0x000001)
	#define OPENGB_BASE_EC_BUFFER_NOT_ENOUGH OPENGB_BASE_EC_MAKE(0x000002)
	#define OPENGB_BASE_EC_OUT_OF_MEMORY OPENGB_BASE_EC_MAKE(0x000003)
	#define OPENGB_BASE_EC_FORMAT_ERROR OPENGB_BASE_EC_MAKE(0x000004)

	#define OPENGB_BASE_EC_SEE_ERRNO OPENGB_BASE_EC_MAKE(0xFFFFFF)
	
	#define OPENGB_BASE_EC_UNKNOWN_ERROR_CODE_MSG		"Unknown error code!"
	#define OPENGB_BASE_EC_NO_ERROR_MSG					"No error."
	#define OPENGB_BASE_EC_ARGUMENT_NULL_MSG			"Argument is NULL!"
	#define OPENGB_BASE_EC_BUFFER_NOT_ENOUGH_MSG		"The buffer you gived isn't enough. Please alloc more space to the buffer!"
	#define OPENGB_BASE_EC_FORMAT_ERROR_MSG				"Format error."
	// When the program out of memory, it shouldn't have any extend values.
	#define OPENGB_BASE_EC_OUT_OF_MEMORY_MSG			"Out of memory!"
	#define OPENGB_BASE_EC_SEE_ERRNO_MSG				"errno has been set by system or other library caused OpenGB actions. Please get errno for more information."
// :==  OpenGB Base Error Code End  ===

// === OpenGB CId Error Code Begin ==:
	// Label: CId
	#define OPENGB_CID_EC_LABEL 0x01000000UL
	// Make CId error code.
	#define OPENGB_CID_EC_MAKE(ec) OPENGB_EC_MAKE((OPENGB_CID_EC_LABEL), (ec))

	#define OPENGB_CID_EC_NOT_18CID OPENGB_CID_EC_MAKE(0x000001)
	#define OPENGB_CID_EC_CID_DATA_ERROR OPENGB_CID_EC_MAKE(0x000002)

	#define OPENGB_CID_EC_NOT_18CID_MSG					"Not a 18-digit CId!"
	#define OPENGB_CID_EC_CID_DATA_ERROR_MSG			"CitizenId data error!"
// :==  OpenGB CId Error Code End  ===

	//The longest message size. Includes terminal '\0'.
	#define OPENGB_EC_MSG_MAX_SIZE 108



OPENGB_ERROR_CODE_TYPE opengb_GetLastOpenGBErrorCode();
void opengb_SetLastOpenGBErrorCode(OPENGB_ERROR_CODE_TYPE errorCode);
void opengb_CleanLastOpenGBErroCode();

	// Throw error code. In fact, it just set last error code.
	#define _OPENGB_THROW(errorCode) opengb_CleanLastOpenGBErrorCode();
	#define _OPENGB_TRY opengb_CleanLastOpenGBErrorCode();
	#define _OPENGB_CATCH(errorCode) if(opengb_GetLastOpenGBErrorCode()==(errorCode)){
	#define _OPENGB_CATCHX(errorCode) }else if(opengb_GetLastOpenGBErrorCode()==(errorCode)){
	#define _OPENGB_CATCH_CLOSE }

	#if defined(OPENGB_EX_ENABLE_ECTOSTR)
		#define _OPENGB_ECTOSTR_BAD_RETURN -1
// Generate the error message corresponding to the error code.
// `_out_msg`: A buffer for saving message.
// `maxSize`: The maxinum size of `_out_msg` (strlen(_out_msg)+1).
// Return -1 means failure. Return any val >0 means success and the value is the length of `_out_msg`.
int opengb_ErrorCodeToString(const OPENGB_ERROR_CODE_TYPE error_code, char* _out_msg, const int maxSize);
	#endif

#endif
