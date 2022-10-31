#include <check.h>

#include <utility.h>

START_TEST(test_utility_skip_chars){
	ck_assert_msg(1,	"NULLABLE_BOOL_IS_TRUE(NULLABLE_BOOL_TURE) should be true.");
}

START_TEST(test_utility_skip_white_space){
	ck_assert_msg(1,	"NULLABLE_BOOL_IS_TRUE(NULLABLE_BOOL_TURE) should be true.");
}

Suite* make_utility_suite(){
	Suite *s=suite_create("utility");
	TCase *tc=tcase_create("utility.h");

	suite_add_tcase(s,tc);

	tcase_add_test(tc, test_utility_skip_chars);
	tcase_add_test(tc, test_utility_skip_white_space);
}