// OpenGB Exception

#include "opengbex.h"

#include <stdlib.h>
#include <ctype.h>

#include "moretype.h"
#include "utility.h"

// `size_t` is unnecessary here (`i` in each function), `int` is appropriate and enough.

OPENGB_ERROR_CODE_TYPE _lastErrorCode = OPENGB_NO_ERROR;

OPENGB_ERROR_CODE_TYPE opengb_GetLastOpenGBErrorCode() {
    return _lastErrorCode;
}

void opengb_SetLastOpenGBErrorCode(OPENGB_ERROR_CODE_TYPE errorCode){
	_lastErrorCode = errorCode;
}

void opengb_CleanLastOpenGBErroCode(){
	_lastErrorCode=OPENGB_BASE_EC_NO_ERROR;
}

#if defined(OPENGB_EX_ENABLE_ECTOSTR)
	#include <string.h>

int opengb_ErrorCodeToString(const OPENGB_ERROR_CODE_TYPE error_code, char* _out_msg, const int maxSize){
	int msgLen;
	char *msg = NULL;

	// `x` must be a macro word name.
	#define _OPENGB_SET_MSG(x) case x: msg = x##_MSG; break;
	//!WIP:	Need a dictionary (search by dichotomy) for large set of error messages instead switch-cases!
	switch (error_code){
		_OPENGB_SET_MSG(OPENGB_BASE_EC_NO_ERROR)

		_OPENGB_SET_MSG(OPENGB_BASE_EC_ARGUMENT_NULL)
		_OPENGB_SET_MSG(OPENGB_BASE_EC_BUFFER_NOT_ENOUGH)
		_OPENGB_SET_MSG(OPENGB_BASE_EC_OUT_OF_MEMORY)
		_OPENGB_SET_MSG(OPENGB_BASE_EC_FORMAT_ERROR)

		_OPENGB_SET_MSG(OPENGB_BASE_EC_SEE_ERRNO)
		
		_OPENGB_SET_MSG(OPENGB_CID_EC_NOT_18CID)
		_OPENGB_SET_MSG(OPENGB_CID_EC_CID_DATA_ERROR)
		
		default:
			msg = OPENGB_BASE_EC_UNKNOWN_ERROR_CODE_MSG; break;
	}
	#undef _OPENGB_SET_MSG

	msgLen = strlen(msg);
	if(msgLen>=maxSize){
		// In order to protect error code, we shouldn't use opengbex in itself.
		// But user may have saved error code before calling this function.
		// So we can use OpenGB exception here.
		_OPENGB_THROW(OPENGB_BASE_EC_BUFFER_NOT_ENOUGH);
		return _OPENGB_ECTOSTR_BAD_RETURN;
	}else{
		strcpy(_out_msg, msg);
		return msgLen;
	}
}
#endif
