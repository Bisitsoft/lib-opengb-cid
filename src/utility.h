// Utility

#ifndef __utility_h_
	#define __utility_h_
	#include "opengb_cid_switches.h"

	#include <string.h>

// Skip each character of `str` which in `chars` from `now_i`. For safety, the length of `chars`, `chars_n` must be correctly given.
// The function will set the index of the first char which isn't included in `chars` to `now_i`.
inline void SkipChars(const char * chars, const int chars_n, int * const now_i, const char * str);

// Skip each character of `str` which is whitespace from `now_i`.
// Whitespace included ' ' and '\t'.
// The function will set the index of the first char which isn't whitespace to `now_i`.
inline void SkipWhiteSpace(int * const now_i, const char * str);

#endif // __utility_h_