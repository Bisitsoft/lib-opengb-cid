// OpenGB Exception

#include "opengbex.h"

#include <stdlib.h>
#include <string.h>
//#include <stdarg.h>
#include <ctype.h>

#include "moretype.h"
#include "utility.h"

// `size_t` is unnecessary here (`i` in each function), `int` is appropriate and enough.

int lastErrorCode = OPENGB_NO_ERROR;

int num_length(int num);

int opengb_GetLastOpenGBErrorCode() {
    return lastErrorCode;
}

void opengb_SetLastOpenGBErrorCode(int errorCode) {
	//opengb_CleanLastOpenGBErrorCode();
    lastErrorCode = errorCode;
}

void opengb_CleanLastOpenGBErrorCode(){
	lastErrorCode=OPENGB_BASE_EC_NO_ERROR;
//#if defined(OPENGB_EX_ENABLE_EXTEND_VALUES)
//	opengb_CleanLastOpenGBErrorExtendValues(); //<delete>Duplicate (`opengb_SetLastOpenGBErrorExtendValues` will call it, too) but necessary?</delete>Has been removed.
//#endif
}

#if defined(OPENGB_EX_ENABLE_EXTEND_VALUES)
OpenGBEXExtendValues *lastExtendValues=NULL;

const OpenGBEXExtendValues* opengb_GetLastOpenGBErrorExtendValues() { return lastExtendValues; }

void opengb_CleanLastOpenGBErrorExtendValues(){
	int i;

	if(lastExtendValues!=NULL){
		for(i=0;i<lastExtendValues->count;++i){
			free(lastExtendValues->values[i]);
		}
		free(lastExtendValues->values);
		free(lastExtendValues);
		lastExtendValues=NULL;
	}
}

const char* _opengb_MakeString(const char** _str){
	char *r = (char*)malloc(sizeof(char)*(strlen(_str)+1));
	strcpy(r,_str);
	return r;
}

OpenGBEXExtendValues* opengb_MakeOpenGBErrorExtendValues(const char** args, const int argc){
	int i;
	OpenGBEXExtendValues *r=(OpenGBEXExtendValues*)malloc(sizeof(OpenGBEXExtendValues));

	r->count=argc;
	r->values=(const char**)malloc(sizeof(const char*)*argc);
	for (i = 0; i < argc; ++i) {
		r->values[i]=args[i];
	}
	
	return r;
}

void opengb_SetLastOpenGBErrorExtendValues(const OpenGBEXExtendValues* extendValues) {
	opengb_CleanLastOpenGBErrorExtendValues();
	lastExtendValues = extendValues;
}

	//右边这段代码干嘛的？ //#define OPENGB_BASE_EC_PROCESS_MSG(msg)	opengb_EXProcessMessageWithExtendValues(msg)
void opengb_EXProcessMessageWithExtendValues(const char* msg, const char* _out_msg, const int maxSize, const OpenGBEXExtendValues const* ev){
	int i, j, temp_idx, len = strlen(msg), arg_n;
	int *arg_pos=NULL;

	// Fast find parameter amount.
	for(i=0,arg_n=0;i<len;++i){
		if(msg[i]=='{'){
			if(i+1<len && msg[i]!='{'){
				++arg_n; //Found single '{'.
			}else{
				++i; //Found continuous double '{'.
			}
		}
	}

	if(arg_n==0){ //No parameter blank.
		_out_msg = _opengb_MakeString(msg); //Directly return a `msg` copy.
		return;
	}
	arg_pos=(int*)malloc(sizeof(int)*arg_n*2);

	// Mark all parameter blank.
	for(i=0,arg_n=0;i<len;++i){
		if(msg[i]=='{'){
			if(i+1<len && msg[i]!='{'){
				++arg_n; //Found single '{'.
			}else{
				++i; //Found continuous double '{'.
			}
		}
	}
	

	
}
int num_length(int num){
	int r=1;
	while(num>9){
		num/=10;
		++r;
	}
	return r;
}
#else
void opengb_SetLastOpenGBErrorExtendValues(OpenGBEXExtendValues extendValues) { ; }
#endif

#if defined(OPENGB_EX_ENABLE_ECTOSTR)
	#include <string.h>

//#warning Need a dictionary for large set of error messages instead switch-cases!

	#define _OPENGB_SET_MSG(x) case x: msg = x##_MSG; break; //x must be a macro word name.

int opengb_ErrorCodeToString(
	const OPENGB_ERROR_CODE_TYPE error_code,
	char * const _out_msg,
	const int maxLen
#if defined(OPENGB_EX_ENABLE_EXTEND_VALUES)
	, OpenGBEXExtendValues extendValues
#endif
){
	int msgLen;
	char *msg = NULL;

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
			msg = OPENGB_BASE_EC_UNKNOWN_ERROR_CODE_MSG;
			break;
	}

	#if defined(OPENGB_EX_ENABLE_EXTEND_VALUES)
	HERE
	#endif

	msgLen = strlen(msg);
	if(msgLen>=maxSize){
		_OPENGB_THROW(OPENGB_BASE_EC_BUFFER_NOT_ENOUGH); //opengbex中应当不用自己的异常机制，以免冲刷异常码，但是用户应当已经保存此处的代码，所以可以使用。
		return -1;
	}else{
		strcpy(_out_msg, msg);
		return strlen(msg);
	}
}
#endif