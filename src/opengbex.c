#include "opengbex.h"

int lastErrorCode = OPENGB_NO_ERROR;

int opengb_GetLastOpenGBErrorCode() {
    return lastErrorCode;
}

void opengb_SetLastOpenGBErrorCode(int errorCode) {
    lastErrorCode = errorCode;
}

#ifdef OPENGB_EX_COMPILE_ECTOSTR
	#include <string.h>

int opengb_ErrorCodeToString(const OPENGB_ERROR_CODE_TYPE error_code, char * const _out_msg, const int maxSize){
	int msgLen;
	char *msg = NULL;

	switch (error_code){
		case OPENGB_BASE_EC_NO_ERROR:
			msg = OPENGB_BASE_EC_NO_ERROR_MSG;
			break;
		case OPENGB_BASE_EC_ARGUMENT_NULL:
			msg = OPENGB_BASE_EC_ARGUMENT_NULL_MSG;
			break;

		case OPENGB_CID_EC_NOT_18CID:
			msg = OPENGB_CID_EC_NOT_18CID_MSG;
			break;
		case OPENGB_CID_EC_CID_DATA_ERROR:
			msg = OPENGB_CID_EC_CID_DATA_ERROR_MSG;
			break;
		
		default:
			msg = OPENGB_BASE_EC_UNKNOWN_ERROR_CODE_MSG;
			break;
	}

	msgLen = strlen(msg);
	if(msgLen>=maxSize){
		return -1;
	}else{
		strcpy(_out_msg, msg);
		return strlen(msg);
	}
}
#endif