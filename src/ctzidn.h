// Citizen Identification Number
// GB 11643-1999

#if !defined(__ctzidn_h_)
	#define __ctzidn_h_
	#include "opengb_cid_switches.h"

	#include <stdbool.h>
	#include <stdio.h>
	
	#include "opengbex.h"

/*
讨论：可以选择的存储方式：
	半字节存储法：1~X存储在4个比特中，两个数为一个字节，共用9个字节。
	整数存储法：将整个身份证号存储在int64中。
		正负表示法：用负数表示最后一位为X，其它为0~9.
		加数位表示法：最后一个数字占两个10进制数字位，如3即为03，X即为10。
	字符串表示法：存储在字符串中； <-可扩展性最高
		也可以是定长18位字符数组。
	结构体表示法：将区号、生日、顺序码、校验码分别存储。
		整数表示法：分别存储于int32、int32、int16、byte中。 <-可扩展性较高 <<<目前用法
		位表示法（即本库中的Zip1）：20b、27b、10b、4b共61b，需8字节。 <- 不易维护与使用 <<<20+30+10+4=64b
		紧凑位表示法：行政区共34个，次级区编号最多有X（需统计）个，5+14=19位表示区号。 <- 不易维护与使用
*/

	// Sex Code.
	#define OPENGB_CID_SEX_MALE		1
	#define OPENGB_CID_SEX_FEMALE	2

	// CId Type (Length) Code.
	#define OPENGB_CID_TYPE_UNKNOWN	0	// Unknown Length.
	#define OPENGB_CID_TYPE_15CID	1	// 15 digits.
	#define OPENGB_CID_TYPE_18CID	2	// 18 digits.

	// Each part of 18 digit CId length.
	#define OPENGB_CID_18CID_LENGTH				18	//Total length.
	#define OPENGB_CID_18CID_AREA_LENGTH		6
	#define OPENGB_CID_18CID_BIRTHDAY_LENGTH	8
	#define OPENGB_CID_18CID_ORDER_LENGTH		3
	#define OPENGB_CID_18CID_CHECKSUM_LENGTH	1
	
	// Each part of 15 digit CId length.
	#define OPENGB_CID_15CID_LENGTH				15	//Total length.
	#define OPENGB_CID_15CID_AREA_LENGTH		6
	#define OPENGB_CID_15CID_BIRTHDAY_LENGTH	6
	#define OPENGB_CID_15CID_ORDER_LENGTH		3
	#define OPENGB_CID_15CID_CHECKSUM_LENGTH	0
	
	// Each part of CId data type.
	#define OPENGB_CID_AREA_TYPE		unsigned long int
	#define OPENGB_CID_BIRTHDAY_TYPE	unsigned long int
	#define OPENGB_CID_ORDER_TYPE		unsigned short int
	#define OPENGB_CID_CHECKSUM_TYPE	unsigned char
	

	
	// Constant used for Mod 11 verification of CId.
	#define OPENGB_MOD11_2_MOD_CONSTANT_NUMBER 11
	
	// Data type of result map of Mod 11 verification of CId.
	#if defined(OPENGB_CODE_PREFER_FAST)
		#define OPENGB_MOD11_2_W_LIST_TYPE unsigned int
	#elif defined(OPENGB_CODE_PREFER_TIGHT)
		#define OPENGB_MOD11_2_W_LIST_TYPE unsigned char
	#endif

// CId(Unzip) data structure.
typedef struct{
	OPENGB_CID_AREA_TYPE area;
	OPENGB_CID_BIRTHDAY_TYPE birthday;
	OPENGB_CID_ORDER_TYPE order;
	OPENGB_CID_CHECKSUM_TYPE checksum;
}CitizenId;
	#define OPENGB_CID_NULL {0,0,0,0} // CId(Unzip) null value.
// CId-Zip1 data structure: area+birth+order+checksum = 20b+30b+10b+4b = 64bits.
typedef unsigned long long CitizenIdZip1;
	#define OPENGB_CID_ZIP1_NULL 0ULL //CId-Zip1 null value.

	#define _OPENGB_MOD11_2_METHOD_BAD_RETURN 0xFF //The return value which means happended of `_OPENGB_MOD11_2_METHOD` method.

	#if defined(OPENGB_CODE_PREFER_FAST)
		#define _OPENGB_MOD11_2_METHOD(_18cid) (_gb11643_1999_mod11_2_fst(_18cid))
OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(const CitizenId * const _18cid);
	#elif defined(OPENGB_CODE_PREFER_TIGHT)
		#define _OPENGB_MOD11_2_METHOD(_18cid) (_gb11643_1999_mod11_2_tt(_18cid))
OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_tt(const CitizenId * const _18cid);
	#endif

//getAddress() //返回lib-opengb-acd中的AreaNode的链表 //<-----WIP!!!
int GetSex(const CitizenId * const cid);

bool Is18CId(const CitizenId * const cid);
bool Is15CId(const CitizenId * const cid);
bool IsNullCId(const CitizenId * const cid);

CitizenId CloneCId(const CitizenId * const cid); // Copy data in `CitizenId` by `memcpy` method.
CitizenId To18CId(const CitizenId * const cid); 
CitizenId To15CId(const CitizenId * const cid);

//bool IsCId(){...; FindAreaCodeVerifyCId}
bool VerifyCId(const CitizenId * const cid);
//bool VerifyCIdArea(const CitizenId * const cid);
bool VerifyCIdBirthday(const CitizenId * const cid);
bool VerifyCIdOrder(const CitizenId * const cid);
bool VerifyCIdChecksum(const CitizenId * const _18cid);

bool ToCId(const char const * text, const int text_Length, CitizenId * const _out);
bool ToString(const CitizenId * const cid, char* const _out, const int out_buffer_size); //_out应当至少有19或16字节。//return -1 for failure, >0 for success and length.

CitizenIdZip1 Zip1(const CitizenId * const cid);
#define _UNZIP1_CID_AREA(cid) ((cid >> 44) & 0xFFFFF)
#define _UNZIP1_CID_BIRTHDAY(cid) ((cid >> 14) & 0x3FFFFFFF)
#define _UNZIP1_CID_ORDER(cid) ((cid >> 4) & 0x3FF)
#define _UNZIP1_CID_CHECKSUM(cid) (cid & 0xF)
CitizenId Unzip1(const CitizenIdZip1 cid);



#endif
