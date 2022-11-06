#include <check.h>

//#include "opengb_cid_switches.h"
#include <opengbex.h>

OPENGB_ERROR_CODE_TYPE all_error_codes[]={
	OPENGB_BASE_EC_NO_ERROR,
	OPENGB_BASE_EC_ARGUMENT_NULL,
	OPENGB_BASE_EC_BUFFER_NOT_ENOUGH,
	OPENGB_BASE_EC_OUT_OF_MEMORY,
	OPENGB_BASE_EC_FORMAT_ERROR,
	OPENGB_BASE_EC_SEE_ERRNO,
	OPENGB_CID_EC_NOT_18CID,
	OPENGB_CID_EC_CID_DATA_ERROR
};

START_TEST(test_opegnex_last_error_code_init_value){
	ck_assert_msg(opengb_GetLastOpenGBErrorCode()==OPENGB_NO_ERROR, "OpenGB error code isn't OPENGB_NO_ERROR at first.");
}

START_TEST(test_opegnex_error_code_functions){
	opengb_SetLastOpenGBErrorCode(OPENGB_CID_EC_NOT_18CID);
	if(opengb_GetLastOpenGBErrorCode()!=OPENGB_CID_EC_NOT_18CID){
		ck_abort_msg("Last error code set or get error.");
		return;
	}
	
	opengb_CleanLastOpenGBErrorCode();
	ck_assert_msg(opengb_GetLastOpenGBErrorCode()==OPENGB_NO_ERROR, "OpenGB error code isn't OPENGB_NO_ERROR after cleaning.");
}

void throw_opengb_error_code(OPENGB_ERROR_CODE_TYPE ec){
	_OPENGB_THROW(ec)
}

START_TEST(test_opegnex_exception_machanism){
	int catched;

	opengb_CleanLastOpenGBErrorCode();
	_OPENGB_THROW(OPENGB_CID_EC_NOT_18CID)
	ck_assert_msg(opengb_GetLastOpenGBErrorCode()==OPENGB_CID_EC_NOT_18CID, "Throw error failed.");

	_OPENGB_TRY
		catched=0;
		ck_assert_msg(opengb_GetLastOpenGBErrorCode()==OPENGB_NO_ERROR, "OpenGB error code isn't OPENGB_NO_ERROR at beginning if _OPENGB_TRY.");
		throw_opengb_error_code(OPENGB_CID_EC_NOT_18CID);
	_OPENGB_CATCH(OPENGB_CID_EC_NOT_18CID)
		catched=1;
	_OPENGB_CATCH_CLOSE
	ck_assert_msg(catched, "Didn't catch error code.");

	_OPENGB_TRY
		catched=0;
		ck_assert_msg(opengb_GetLastOpenGBErrorCode()==OPENGB_NO_ERROR, "OpenGB error code isn't OPENGB_NO_ERROR at beginning if _OPENGB_TRY.");
		throw_opengb_error_code(OPENGB_CID_EC_CID_DATA_ERROR);
	_OPENGB_CATCH(OPENGB_CID_EC_NOT_18CID)
		ck_assert_msg(0, "Caught wrong error code.");
		catched=-1;
	_OPENGB_CATCHX(OPENGB_CID_EC_CID_DATA_ERROR)
		catched=1;
	_OPENGB_CATCH_CLOSE
	if(catched!=-1){
		ck_assert_msg(catched, "Didn't catch error code.");
	}
}

START_TEST(test_opegnex_msg_max_size){
	int i, len;
	int all_error_codes_n=sizeof(all_error_codes)/sizeof(OPENGB_ERROR_CODE_TYPE);
	char buffer[OPENGB_EC_MSG_MAX_SIZE];

	#if !defined(OPENGB_EX_ENABLE_ECTOSTR)
		ck_abort_msg("OPENGB_EX_ENABLE_ECTOSTR undefined.");
	#endif

	for(i=0;i<all_error_codes_n;i++){
		_OPENGB_TRY
			opengb_ErrorCodeToString(all_error_codes[i], buffer, OPENGB_EC_MSG_MAX_SIZE);
		_OPENGB_CATCH(OPENGB_BASE_EC_BUFFER_NOT_ENOUGH_MSG)
			ck_assert_msg(0, "OPENGB_EC_MSG_MAX_SIZE isn't right.");
			return;
		_OPENGB_CATCH_CLOSE
	}
	ck_assert(1);
}

Suite* make_opengbex_suite(){
	Suite *s=suite_create("opengbex");
	TCase *tc=tcase_create("opengbex.h");

	suite_add_tcase(s, tc);

	tcase_add_test(tc, test_opegnex_last_error_code_init_value);
	tcase_add_test(tc, test_opegnex_error_code_functions);
	tcase_add_test(tc, test_opegnex_exception_machanism);
	tcase_add_test(tc, test_opegnex_msg_max_size);
}