// More Type

#ifndef __moretype_h_
	#define __moretype_h_

	// Define NULL
	#ifndef NULL
		#ifdef __cplusplus
			#define NULL 0
		#else
			#define NULL ((void *)0)
		#endif
	#endif

	// Nullable Boolean
	#define NULLABLE_BOOL_TYPE char
	#define NULLABLE_BOOL_TURE 1
	#define NULLABLE_BOOL_FALSE 0
	#define NULLABLE_BOOL_NULL -1
	#define NULLABLE_BOOL_IS_TRUE(value) (value==NULLABLE_BOOL_TURE)
	#define NULLABLE_BOOL_IS_FALSE(value) (value==NULLABLE_BOOL_FALSE)
	#define NULLABLE_BOOL_IS_NULL(value) (value==NULLABLE_BOOL_IS_NULL)

#endif