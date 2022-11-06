#include <string.h>
#include <stdbool.h>

#include <check.h>

#include <ctzidn.h>

typedef struct {
	CitizenId cid;
	int sex;
	int type;
	CitizenId _18cid;
	CitizenId _15cid;
	CitizenIdZip1 zipped_cid;
	char* str;
}CIdTest;
CIdTest cid_tests[]={
	{{110105, 19491231, 002, 10}, OPENGB_CID_SEX_MALE  , OPENGB_CID_TYPE_18CID, {110105, 19491231, 002, 10}, {110105, 491231, 002, 0 }, 1936987963764752426ULL, "11010519491231002X"}, //11010519491231002X
	{{440524, 18800101, 001, 4 }, OPENGB_CID_SEX_FEMALE, OPENGB_CID_TYPE_18CID, {440524, 18800101, 001, 4 }, {440524, 800101, 001, 0 }, 7749780473051168788ULL, "440524188001010014"}, //440524188001010014
	{{220000, 771001  , 007, 0 }, OPENGB_CID_SEX_FEMALE, OPENGB_CID_TYPE_15CID, {220000, 19771001, 007, 6 }, {220000, 771001, 007, 0 }, 3870280942403600496ULL, "220000771001007"   }, //220000771001007
};
int cid_tests_n=sizeof(cid_tests)/sizeof(CIdTest);

typedef struct {
	CitizenId x;
	CitizenId y;
	int result;
}CompareCIdTest;
CompareCIdTest compare_cid_tests[]={
	{}
};
int compare_cid_tests_n=sizeof(compare_cid_tests)/sizeof(CompareCIdTest);
typedef struct {
	CitizenIdZip1 x;
	CitizenIdZip1 y;
	int result;
}CompareZip1CIdTest;
CompareCIdTest compare_zip1_cid_tests[]={
	{}
};
int compare_zip1_cid_tests_n=sizeof(compare_zip1_cid_tests)/sizeof(CompareZip1CIdTest);

inline bool bool_xand(bool x, bool y){
	return (x&&y)||(!x&&!y);
}

START_TEST(test_ctzidn_cid_to_string){
	int i;
	char buffer[24];

	for(i=0;i<cid_tests_n;i++){
		CId_ToString(&cid_tests[i].cid,&buffer,sizeof(buffer));
		ck_assert_msg(strcmp(buffer, &cid_tests[i].str)==0,
			"CId_ToString()'s result is \"%s\", but it should be \"%s\".", buffer, cid_tests[i].str);
	}
}

START_TEST(test_ctzidn_get_sex){
	int i;

	for(i=0;i<cid_tests_n;i++){
		ck_assert_msg(CId_GetSex(&(cid_tests[i].cid))==cid_tests[i].sex,
			"%s should be a %smale's citien identification number.", cid_tests[i].str, cid_tests[i].sex==OPENGB_CID_SEX_FEMALE?"fa":"");
	}
}

START_TEST(test_ctzidn_is_18cid){
	int i;

	for(i=0;i<cid_tests_n;i++){
		ck_assert_msg(bool_xand(Is18CId(&(cid_tests[i].cid)),cid_tests[i].type==OPENGB_CID_TYPE_18CID),
			"%s should be a 18-digit citien identification number.", cid_tests[i].str);
	}
}

START_TEST(test_ctzidn_is_15cid){
	int i;

	for(i=0;i<cid_tests_n;i++){
		ck_assert_msg(bool_xand(Is15CId(&(cid_tests[i].cid)),cid_tests[i].type==OPENGB_CID_TYPE_15CID),
			"%s should be a 15-digit citien identification number.", cid_tests[i].str);
	}
}

START_TEST(test_ctzidn_cid_to_zip1){
	
}

START_TEST(test_ctzidn_cid_from_zip1){
	
}

START_TEST(test_ctzidn_compare_cid){

}
START_TEST(test_ctzidn_compare_zip1_cid){
	
}

START_TEST(test_ctzidn_is_null_cid){
	int i;
	CitizenId temp=OPENGB_CID_NULL;

	for(i=0;i<cid_tests_n;i++){
		ck_assert_msg(IsNullCId(&(cid_tests[i].cid)), "%s isn't null.", cid_tests[i].str);
	}
	ck_assert_msg(IsNullCId(&temp), "It should be null.");
}

START_TEST(test_ctzidn_is_null_zipped1_cid){
	int i;
	CitizenIdZip1 temp=OPENGB_CID_ZIP1_NULL;

	for(i=0;i<cid_tests_n;i++){
		ck_assert_msg(IsNullZip1CId(cid_tests[i].zipped_cid), "%lld isn't null.", cid_tests[i].zipped_cid);
	}
	ck_assert_msg(IsNullZip1CId(&temp), "It should be null.");
}

START_TEST(test_ctzidn_to_18cid){
	int i;
	CitizenId result;
	char result_str[24], answer_str[24];

	for(i=0;i<cid_tests_n;i++){
		result=To18CId(&(cid_tests[i].cid));

		CId_ToString(&result, result_str, sizeof(result_str));
		CId_ToString(&(cid_tests[i]._18cid), answer_str, sizeof(answer_str));
		ck_assert_msg(CompareCId(&result, &(cid_tests[i]._18cid))==0,
			"To18CId()'s result is \"%s\", but it should be \"%s\".", result_str, answer_str);
	}
}

START_TEST(test_ctzidn_to_15cid){
	int i;
	CitizenId result;
	char result_str[24], answer_str[24];

	for(i=0;i<cid_tests_n;i++){
		result=To15CId(&(cid_tests[i].cid));

		CId_ToString(&result, result_str, sizeof(result_str));
		CId_ToString(&(cid_tests[i]._15cid), answer_str, sizeof(answer_str));
		ck_assert_msg(CompareCId(&result, &(cid_tests[i]._15cid))==0,
			"To15CId()'s result is \"%s\", but it should be \"%s\".", result_str, answer_str);
	}
}

START_TEST(test_ctzidn_verify_cid){
	;
}

START_TEST(test_ctzidn__gb11643_1999_mod11_2){
	;
}

Suite* make_ctzidn_suite(){
	Suite *s=suite_create("ctzidn");
	TCase *tc=tcase_create("ctzidn.h");

	suite_add_tcase(s, tc);

	tcase_add_test(tc, test_ctzidn_cid_to_string);
	tcase_add_test(tc, test_ctzidn_get_sex);
	tcase_add_test(tc, test_ctzidn_is_18cid);
	tcase_add_test(tc, test_ctzidn_is_15cid);
	tcase_add_test(tc, test_ctzidn_cid_to_zip1);
	tcase_add_test(tc, test_ctzidn_cid_from_zip1);
	tcase_add_test(tc, test_ctzidn_compare_cid);
	tcase_add_test(tc, test_ctzidn_compare_zip1_cid);
	tcase_add_test(tc, test_ctzidn_is_null_cid);
	tcase_add_test(tc, test_ctzidn_is_null_zipped1_cid);
	tcase_add_test(tc, test_ctzidn_to_18cid);
	tcase_add_test(tc, test_ctzidn_to_15cid);
	tcase_add_test(tc, test_ctzidn_verify_cid);
	tcase_add_test(tc, test_ctzidn__gb11643_1999_mod11_2);
}