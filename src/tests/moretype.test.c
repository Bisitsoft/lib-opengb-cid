#include <check.h>

#include <moretype.h>

START_TEST(test_moretype_nullable_bool_is_ture){
	ck_assert_msg(NULLABLE_BOOL_IS_TRUE(NULLABLE_BOOL_TURE),	"NULLABLE_BOOL_IS_TRUE(NULLABLE_BOOL_TURE) should be true.");
	ck_assert_msg(!NULLABLE_BOOL_IS_TRUE(NULLABLE_BOOL_FALSE),	"NULLABLE_BOOL_IS_TRUE(NULLABLE_BOOL_FALSE) should be false.");
	ck_assert_msg(!NULLABLE_BOOL_IS_TRUE(NULLABLE_BOOL_NULL),	"NULLABLE_BOOL_IS_TRUE(NULLABLE_BOOL_NULL) should be false.");
}

START_TEST(test_moretype_nullable_bool_is_false){
	ck_assert_msg(!NULLABLE_BOOL_IS_FALSE(NULLABLE_BOOL_TURE),	"NULLABLE_BOOL_IS_FALSE(NULLABLE_BOOL_TURE) should be false.");
	ck_assert_msg(NULLABLE_BOOL_IS_FALSE(NULLABLE_BOOL_FALSE),	"NULLABLE_BOOL_IS_FALSE(NULLABLE_BOOL_FALSE) should be true.");
	ck_assert_msg(!NULLABLE_BOOL_IS_FALSE(NULLABLE_BOOL_NULL),	"NULLABLE_BOOL_IS_FALSE(NULLABLE_BOOL_NULL) should be false.");
}

START_TEST(test_moretype_nullable_bool_is_null){
	ck_assert_msg(!NULLABLE_BOOL_IS_NULL(NULLABLE_BOOL_TURE),	"NULLABLE_BOOL_IS_NULL(NULLABLE_BOOL_TURE) should be false.");
	ck_assert_msg(!NULLABLE_BOOL_IS_NULL(NULLABLE_BOOL_FALSE),	"NULLABLE_BOOL_IS_NULL(NULLABLE_BOOL_FALSE) should be false.");
	ck_assert_msg(NULLABLE_BOOL_IS_NULL(NULLABLE_BOOL_NULL),	"NULLABLE_BOOL_IS_NULL(NULLABLE_BOOL_NULL) should be true.");
}

Suite* make_moretype_suite(){
	Suite *s=suite_create("moretype");
	TCase *tc=tcase_create("moretype.h");

	suite_add_tcase(s, tc);

	tcase_add_test(tc, test_moretype_nullable_bool_is_ture);
	tcase_add_test(tc, test_moretype_nullable_bool_is_false);
	tcase_add_test(tc, test_moretype_nullable_bool_is_null);
}
