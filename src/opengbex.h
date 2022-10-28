// OpenGB Exception

#ifndef __opengbex_h_
	#define __opengbex_h_
	#include "opengb_cid_switches.h"



	#define OPENGB_ERROR_CODE_TYPE unsigned int
	// Use `label`(type) as high bits (mask=0xF000) and `ec`(error code) as low bits (mask=0x0FFF) to make a complete error code.
	#define OPENGB_EC_MAKE(label, ec) ((label)|(ec))
	#define OPENGB_NO_ERROR 0UL //No error.

	#if !defined(OPENGB_EX_ENABLE_EXTEND_VALUES)
		#define OPENGB_BASE_EC_PROCESS_MSG(msg)	(msg) //Directly return message.
	#else
		#define OPENGB_BASE_EC_PROCESS_MSG(msg)	opengb_EXProcessMessageWithExtendValues(msg) //Return processed message.
	#endif

	// Each error code has its description(_MSG).

	// !!!For saving memory, should use a constant string array to instead macro string. //<-----WIP!!!

// === OpenGB Base Error Code Begin ==:
	#define OPENGB_BASE_EC_LABEL 0x00000000UL //Label: Base
	#define OPENGB_BASE_EC_MAKE(ec) OPENGB_EC_MAKE((OPENGB_BASE_EC_LABEL), (ec)) //Make base error code.
	//#define OPENGB_BASE_EC_MAY_HAS_EV 0x800000 //A flag bit: means the error message may have extend values.

	#define OPENGB_BASE_EC_NO_ERROR OPENGB_NO_ERROR
	#define OPENGB_BASE_EC_ARGUMENT_NULL OPENGB_BASE_EC_MAKE(0x000001)
	#define OPENGB_BASE_EC_BUFFER_NOT_ENOUGH OPENGB_BASE_EC_MAKE(0x000002)
	#define OPENGB_BASE_EC_OUT_OF_MEMORY OPENGB_BASE_EC_MAKE(0x000003)
	#define OPENGB_BASE_EC_FORMAT_ERROR OPENGB_BASE_EC_MAKE(0x000004)
	#define OPENGB_BASE_EC_SEE_ERRNO OPENGB_BASE_EC_MAKE(0xFFFFFF)
	
	#define OPENGB_BASE_EC_UNKNOWN_ERROR_CODE_MSG		"Unknown error code!"
	#define OPENGB_BASE_EC_NO_ERROR_MSG					"No error."
	#if !defined(OPENGB_EX_ENABLE_EXTEND_VALUES)
		#define OPENGB_BASE_EC_ARGUMENT_NULL_MSG		"Argument is NULL!"
		#define OPENGB_BASE_EC_BUFFER_NOT_ENOUGH_MSG	"The buffer you gived isn't enough. Please alloc more space to the buffer!"
		#define OPENGB_BASE_EC_FORMAT_ERROR_MSG			"Format error."
	#else
		#define OPENGB_BASE_EC_ARGUMENT_NULL_MSG		"Argument \"{0}\" is NULL!"
		#define OPENGB_BASE_EC_BUFFER_NOT_ENOUGH_MSG	"The buffer you gived isn't enough. Please alloc more space to the buffer! {0} Byte(s) memory is required."
		#define OPENGB_BASE_EC_FORMAT_ERROR_MSG			"\"{0}\" format error."
	#endif
	#define OPENGB_BASE_EC_OUT_OF_MEMORY_MSG			"Out of memory!" //When the program out of memory, it shouldn't have any extend values.
	#define OPENGB_BASE_EC_SEE_ERRNO_MSG				"errno has been set by system or other library caused OpenGB actions . Please get errno for more information."
// :==  OpenGB Base Error Code End  ===



// === OpenGB CId Error Code Begin ==:
	#define OPENGB_CID_EC_LABEL 0x01000000UL //Label: CId
	#define OPENGB_CID_EC_MAKE(ec) OPENGB_EC_MAKE((OPENGB_CID_EC_LABEL), (ec)) //Make CId error code.

	#define OPENGB_CID_EC_NOT_18CID OPENGB_CID_EC_MAKE(0x000001)
	#define OPENGB_CID_EC_CID_DATA_ERROR OPENGB_CID_EC_MAKE(0x000002)

	#define OPENGB_CID_EC_NOT_18CID_MSG					"Not a 18-digit CId!"
	#define OPENGB_CID_EC_CID_DATA_ERROR_MSG			"CitizenId data error!"
// :==  OpenGB CId Error Code End  ===



int opengb_GetLastOpenGBErrorCode(); //Get last error code.
//void opengb_SetLastOpenGBErrorCode(OPENGB_ERROR_CODE_TYPE errorCode);  //Get last error code.
//void opengb_CleanLastOpenGBErrorCode();  //Clean last error code (and extend values). It will not clear extend values.

	#if defined(OPENGB_EX_ENABLE_EXTEND_VALUES)
typedef struct{
	int count;
	char** values;
}OpenGBEXExtendValues;
const OpenGBEXExtendValues* opengb_GetLastOpenGBErrorExtendValues(); //Get parameters of last error message.
//void opengb_SetLastOpenGBErrorExtendValues(const OpenGBEXExtendValues* extendValues); //Set parameters of last error message. It will call `opengb_CleanLastOpenGBErrorCode` before set value.
//void opengb_CleanLastOpenGBErrorCode(); //Clean parameters of last error message. It will use `free` function to release all the parameters.
void opengb_EXProcessMessageWithExtendValues(const char* msg, const char* _out_msg, const int maxSize, const OpenGBEXExtendValues const* ev); //Process error message with ectend values.
const char* _opengb_MakeString(const char** _str); //Return a `_str` copy contained by a new dynamic array.
OpenGBEXExtendValues* opengb_MakeOpenGBErrorExtendValues(const char** args, const int argc); //Box `args` into a new `OpenGBEXExtendValues`.
	#endif

	// Throw error code. In fact, it just set last error code.
	#define _OPENGB_THROW(errorCode) opengb_SetLastOpenGBErrorCode(errorCode);
	// Throw error code with extend values. In fact, it just set last error code with extend values.
	// If you don't define `OPENGB_EX_ENABLE_EXTEND_VALUES`, the extend values will be dropped. 
	#define _OPENGB_THROW_EV(errorCode, extendValues) opengb_SetLastOpenGBErrorCode(errorCode); opengb_SetLastOpenGBErrorExtendValues(extendValues);
	#define _OPENGB_TRY opengb_CleanLastOpenGBErrorCode();
	#define _OPENGB_CATCH(errorCode) if(opengb_GetLastOpenGBErrorCode()==(errorCode)){
	#define _OPENGB_CATCHX(errorCode) }else if(opengb_GetLastOpenGBErrorCode()==(errorCode)){
	#define _OPENGB_CATCH_CLOSE }

	#if defined(OPENGB_EX_ENABLE_ECTOSTR)
// Generate the error message corresponding to the error code.
// Return -1 means failure. Return any val >0 means success and the value is the length of `_out_msg`.
int opengb_ErrorCodeToString(
	const OPENGB_ERROR_CODE_TYPE error_code,
	char * const _out_msg,
	const int maxLen
		#if defined(OPENGB_EX_ENABLE_EXTEND_VALUES)
	, OpenGBEXExtendValues extendValues
		#endif
);
	#endif

#endif