#include "utility.h"

inline void SkipChars(const char * chars, const int chars_n, int * const now_i, const char * str){
	int j;
	for(;str[*now_i]!='\0';++(*now_i)){
		for(j=0;j<chars_n;++j){
			if(chars[j]==str[*now_i]){
				break;
			}
		}
		if(j>=chars_n){
			return;
		}
	}
}

inline void SkipWhiteSpace(int * const now_i, const char * str){
	const char *p=str+*now_i;

	for(;*p!='\0' && (*p==' ' || *p=='\t');++p) ; //Skip whitespaces.

	(*now_i)=p-str;
}