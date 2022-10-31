#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "test.h"

int main(){
	SRunner* sr=NULL;

	sr=srunner_create(make_moretype_suite());
	srunner_add_suite(sr, make_utility_suite());

	srunner_run_all(sr, CK_VERBOSE);
	int fn=srunner_ntests_failed(sr);
	srunner_free(sr);

	return fn==0?EXIT_SUCCESS:EXIT_FAILURE;
}