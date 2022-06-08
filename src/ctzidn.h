// Citizen Identification Number
// GB 11643-1999

#if !defined(__ctzidn_h_)
	#define __ctzidn_h_
	#include "opengb_cid_switches.h"

	#include <stdbool.h>
	#include <stdlib.h>
	
	#include "opengbex.h"

/*
可以选择的存储方式：
	半字节存储法：1~X存储在4个比特中，两个数为一个字节，共用9个字节。
	整数存储法：将整个身份证号存储在int64中。
		正负表示法：用负数表示最后一位为X，其它为0~9.
		加数位表示法：最后一个数字占两个10进制数字位，如3即为03，X即为10。
	字符串表示法：存储在字符串中； <-可扩展性最高
		也可以是定长18位字符数组。
	结构体表示法：将区号、生日、顺序码、校验码分别存储。
		整数表示法：分别存储于int32、int32、int16、byte中。 <-可扩展性较高
		位表示法：20b、24b、10b、4b共58b，需7字节。 <- 不易维护与使用
		紧凑位表示法：行政区共34个，次级区编号最多有X（需统计）个，5+14=19位表示区号。 <- 不易维护与使用
*/

	#define OPENGB_CID_SEX_MALE		1
	#define OPENGB_CID_SEX_FEMALE	2

	#define OPENGB_CID_TYPE_UNKNOWN	0
	#define OPENGB_CID_TYPE_15CID	1
	#define OPENGB_CID_TYPE_18CID	2

	#define OPENGB_CID_18CID_LENGTH				18
	#define OPENGB_CID_18CID_AREA_LENGTH		6
	#define OPENGB_CID_18CID_BIRTHDAY_LENGTH	8
	#define OPENGB_CID_18CID_ORDER_LENGTH		3
	#define OPENGB_CID_18CID_CHECKSUM_LENGTH	1
	
	#define OPENGB_CID_15CID_LENGTH				15
	#define OPENGB_CID_15CID_AREA_LENGTH		6
	#define OPENGB_CID_15CID_BIRTHDAY_LENGTH	6
	#define OPENGB_CID_15CID_ORDER_LENGTH		3
	#define OPENGB_CID_15CID_CHECKSUM_LENGTH	0
	
	#define OPENGB_CID_AREA_TYPE		unsigned long int
	#define OPENGB_CID_BIRTHDAY_TYPE	unsigned long int
	#define OPENGB_CID_ORDER_TYPE		unsigned short int
	#define OPENGB_CID_CHECKSUM_TYPE	unsigned char
	

	
	#define OPENGB_MOD11_2_MOD_CONSTANT_NUMBER 11
	
	#if defined(OPENGB_CODE_PREFER_FAST)
		#define OPENGB_MOD11_2_W_LIST_TYPE unsigned int
	#elif defined(OPENGB_CODE_PREFER_TIGHT)
		#define OPENGB_MOD11_2_W_LIST_TYPE unsigned char
	#endif

	
	typedef struct{
		OPENGB_CID_AREA_TYPE area;
		OPENGB_CID_BIRTHDAY_TYPE birthday;
		OPENGB_CID_ORDER_TYPE order;
		OPENGB_CID_CHECKSUM_TYPE checksum;
	}CitizenId;

	#if defined(OPENGB_CODE_PREFER_FAST)
		#define _OPENGB_MOD11_2_METHOD(_18cid) (_gb11643_1999_mod11_2_fst(_18cid))
OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_fst(const CitizenId *_18cid);
	#elif defined(OPENGB_CODE_PREFER_TIGHT)
		#define _OPENGB_MOD11_2_METHOD(_18cid) (_gb11643_1999_mod11_2_tt(_18cid))
OPENGB_CID_CHECKSUM_TYPE _gb11643_1999_mod11_2_tt(const CitizenId *_18cid);
	#endif

	int GetSex(const CitizenId *cid);

	bool Is18CId(const CitizenId *cid);
	bool Is15CId(const CitizenId *cid);

			
			
//#warning Commented!
//void To18CId(string)
//void To18CId(_id)
//bool IsCId(){...; FindAreaCodeVerifyCId}
//ToCId(string)
//To18CId(string)
//To18CId(_id)
//getAddress()//返回lib-opengb-acd中的AreaNode的链表
//cid_15to_18Cid(const CitizenId &_15cid)
//cid_18to15(_18cid)
			
bool VerifyCIdChecksum(const CitizenId *_18cid);



#endif
