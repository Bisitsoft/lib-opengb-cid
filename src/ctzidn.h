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
	//   Unknown Length.
	#define OPENGB_CID_TYPE_UNKNOWN	0
	//   15 digits.
	#define OPENGB_CID_TYPE_15CID	1
	//   18 digits.
	#define OPENGB_CID_TYPE_18CID	2

	// Each part of 18 digit CId length.
	//   Total length.
	#define OPENGB_CID_18CID_LENGTH				18
	#define OPENGB_CID_18CID_AREA_LENGTH		6
	#define OPENGB_CID_18CID_BIRTHDAY_LENGTH	8
	#define OPENGB_CID_18CID_ORDER_LENGTH		3
	#define OPENGB_CID_18CID_CHECKSUM_LENGTH	1
	
	// Each part of 15 digit CId length.
	//   Total length.
	#define OPENGB_CID_15CID_LENGTH				15
	#define OPENGB_CID_15CID_AREA_LENGTH		6
	#define OPENGB_CID_15CID_BIRTHDAY_LENGTH	6
	#define OPENGB_CID_15CID_ORDER_LENGTH		3
	#define OPENGB_CID_15CID_CHECKSUM_LENGTH	0
	
	// Each part of CId data type.
	#define OPENGB_CID_AREA_TYPE		unsigned long int
	#define OPENGB_CID_BIRTHDAY_TYPE	unsigned long int
	#define OPENGB_CID_ORDER_TYPE		unsigned short int
	#define OPENGB_CID_CHECKSUM_TYPE	unsigned char
	//#define OPENGB_CID_UNIVERSAL_TYPE	unsigned long int



// CId(Unzip) data structure.
typedef struct{
	OPENGB_CID_AREA_TYPE area;
	OPENGB_CID_BIRTHDAY_TYPE birthday;
	OPENGB_CID_ORDER_TYPE order;
	OPENGB_CID_CHECKSUM_TYPE checksum;
}CitizenId;
	// CId(Unzip) null value.
	#define OPENGB_CID_NULL {0,0,0,0}
	// CId-Zip1 data structure: area+birth+order+checksum = 20b+30b+10b+4b = 64bits.
typedef unsigned long long CitizenIdZip1;
	// CId-Zip1 null value.
	#define OPENGB_CID_ZIP1_NULL 0ULL


	// Constant used for Mod 11 verification of CId.
	#define OPENGB_MOD11_2_MOD_CONSTANT_NUMBER 11
	// Data type of result map of Mod 11 verification of CId.
	#define OPENGB_MOD11_2_W_LIST_TYPE unsigned int
	// The return value which means happended of `_OPENGB_MOD11_2_METHOD` method.
	#define _OPENGB_MOD11_2_METHOD_BAD_RETURN 0xFF
	#define _OPENGB_MOD11_2_METHOD(_18cid) (_gb11643_1999_mod11_2(_18cid))
OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2(const CitizenId* const _18cid);

//!WIP:	Return `AreaNode` node list in WIP `lib-opengb-acd`.
//AreaNode* GetAddress(const CitizenId* const cid);
// Return `OPENGB_CID_SEX_MALE` or `OPENGB_CID_SEX_FEMALE`.
int GetSex(const CitizenId* const cid);

// Accroding to cid.birth word's number of digit, detected whether `cid` has 18 digits.
bool Is18CId(const CitizenId* const cid);
// Accroding to cid.birth word's number of digit, detected whether `cid` has 15 digits.
bool Is15CId(const CitizenId* const cid);
bool IsNullCId(const CitizenId* const cid);
bool IsNullCIdZip1(const CitizenIdZip1 cid);

// Copy data in `CitizenId` by `memcpy` method.
CitizenId CloneCId(const CitizenId* cid);
// If `cid` is 18-digit CId, it will return a `cid`'s copy.
CitizenId To18CId(const CitizenId* cid); 
// If `cid` is 15-digit CId, it will return a `cid`'s copy.
CitizenId To15CId(const CitizenId* cid);


// Verify is Cid good.
bool VerifyCId(const CitizenId* const cid);
bool _VerifyCIdArea(const CitizenId* const cid);
bool _VerifyCIdBirthday(const CitizenId* const cid);
bool _VerifyCIdOrder(const CitizenId* const cid);
bool _VerifyCIdChecksum(const CitizenId* const _18cid);

// Generate the error message corresponding to the error code.
// `_out`: A buffer for saving message. Its size should have at least 16 or 19 bytes.
// `maxSize`: The maxinum size of `_out_msg` (strlen(_out_msg)+1).
// Return -1 means failure. Return any val >0 means success and the value is the length of `_out`.
int ToString(const CitizenId* const cid, char* const _out, const int out_buffer_size);

CitizenIdZip1 Zip1(const CitizenId* const cid);
#define _UNZIP1_CID_AREA(cid) (((cid) >> 44) & 0xFFFFF)
#define _UNZIP1_CID_BIRTHDAY(cid) (((cid) >> 14) & 0x3FFFFFFF)
#define _UNZIP1_CID_ORDER(cid) (((cid) >> 4) & 0x3FF)
#define _UNZIP1_CID_CHECKSUM(cid) ((cid) & 0xF)
CitizenId Unzip1(const CitizenIdZip1 cid);



#endif
