#include <stdlib.h>
#include <string.h>

#include <check.h>

#include <utility.h>

typedef struct{
	char *test;
	char *result;
	char *skip_chars;
}s_skip_chars_test; //string key value pair.

typedef struct{
	char *test;
	char *result;
}s_skip_white_space_test; //string key value pair.

s_skip_chars_test skip_chars_tests[]={
	{"abc", "", "cab"},
	{" a \t \tb\t\t\tc  ", "abc", " \t"},
	{"a \t \tb\t\t\tc", "abc", " \t"},
};

s_skip_white_space_test skip_white_space_tests[]={
	{"abc", "abc"},
	{" a \t \tb\t\t\tc  ", "abc"},
	{"a \t \tb\t\t\tc", "abc"},
};

START_TEST(test_utility_skip_chars){
	int i, j, k, tests_n, str_n, skip_chars_n;
	char result[1024];
	int result_max_n=sizeof(result)/sizeof(char);
	int error_flag;

	tests_n=sizeof(skip_chars_tests)/sizeof(s_skip_chars_test);
	for(i=0;i<tests_n;i++){
		error_flag=0;
		str_n=strlen(skip_chars_tests[i].test);
		skip_chars_n=strlen(skip_chars_tests[i].skip_chars);
		if(str_n>=result_max_n){
			ck_assert_msg(0,"Test string is longer than %d bytes.", result_max_n-1);
			continue;
		}
		for(j=0,k=0;j<str_n;j++){
			SkipChars(skip_chars_tests[i].skip_chars, skip_chars_n, &j, skip_chars_tests[i].test);
			if(j>str_n){
				ck_assert_msg(0, "`SkipWhiteSpace` make index out of range.", result_max_n-1);
				error_flag=1;
				break;
			}
			if(k>=result_max_n){
				ck_assert_msg(0, "Result index out of range.", result_max_n-1);
				error_flag=1;
				break;
			}
			result[k++]=skip_chars_tests[i].test[j];
		}
		if(error_flag){
			continue;
		}
		result[k]='\0';
		ck_assert_msg(
			strcmp(result, skip_chars_tests[i].result)==0,
			"Result is \"%s\", it should be \"%s\".", result, skip_chars_tests[i].result
		);
	}
}

START_TEST(test_utility_skip_white_space){
	int i, j, k, tests_n, str_n;
	char result[1024];
	int result_max_n=sizeof(result)/sizeof(char);
	int error_flag;

	tests_n=sizeof(skip_white_space_tests)/sizeof(s_skip_white_space_test);
	for(i=0;i<tests_n;i++){
		error_flag=0;
		str_n=strlen(skip_white_space_tests[i].test);
		if(str_n>=result_max_n){
			ck_assert_msg(0,"Test string is longer than %d bytes.", result_max_n-1);
			continue;
		}
		for(j=0,k=0;j<str_n;j++){
			SkipWhiteSpace(&j, skip_white_space_tests[i].test);
			if(j>str_n){
				ck_assert_msg(0, "`SkipWhiteSpace` make index out of range.", result_max_n-1);
				error_flag=1;
				break;
			}
			if(k>=result_max_n){
				ck_assert_msg(0, "Result index out of range.", result_max_n-1);
				error_flag=1;
				break;
			}
			result[k++]=skip_white_space_tests[i].test[j];
		}
		if(error_flag){
			continue;
		}
		result[k]='\0';
		ck_assert_msg(
			strcmp(result, skip_white_space_tests[i].result)==0,
			"Result is \"%s\", it should be \"%s\".", result, skip_white_space_tests[i].result
		);
	}
}

Suite* make_utility_suite(){
	Suite *s=suite_create("utility");
	TCase *tc=tcase_create("utility.h");

	suite_add_tcase(s, tc);

	tcase_add_test(tc, test_utility_skip_chars);
	tcase_add_test(tc, test_utility_skip_white_space);
}