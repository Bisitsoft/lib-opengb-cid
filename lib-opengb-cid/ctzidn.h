// Citizen Identification Number
// GB 11643-1999

#if !defined(__cizidn_h_)
	#define __cizidn_h_
	
	#include <cstdlib>
	
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

	#define OPENGB_CID_18CID_LENGTH 18
//	#define OPENGB_CID_18CID_LENGTH_1 17
	#define OPENGB_CID_18CID_AREA_LENGTH 6
	#define OPENGB_CID_18CID_BIRTHDAY_LENGTH 8
	#define OPENGB_CID_18CID_ORDER_LENGTH 3
	#define OPENGB_CID_18CID_CHECKSUM_LENGTH 1
	
	#define OPENGB_CID_15CID_LENGTH 15
//	#define OPENGB_CID_15CID_LENGTH_1 14
	#define OPENGB_CID_15CID_AREA_LENGTH 6
	#define OPENGB_CID_15CID_BIRTHDAY_LENGTH 6
	#define OPENGB_CID_15CID_ORDER_LENGTH 3
	#define OPENGB_CID_15CID_CHECKSUM_LENGTH 0
		
typedef unsigned long int	OPENGB_CID_AREA_TYPE;
typedef unsigned long int	OPENGB_CID_BIRTHDAY_TYPE;
typedef unsigned short int	OPENGB_CID_ORDER_TYPE;
typedef unsigned char		OPENGB_CID_CHECKSUM_TYPE;

namespace opengb{
	namespace cizidn{
		
		typedef struct{
			OPENGB_CID_AREA_TYPE area;
			OPENGB_CID_BIRTHDAY_TYPE birthday;
			OPENGB_CID_ORDER_TYPE order;
			OPENGB_CID_CHECKSUM_TYPE checksum;
		}S_CitizenId;
		
		class CitizenId{
		private:
		public:
			S_CitizenId m_cid;
			
//#warning Commented!
			//bool IsCId(){...; FindAreaCodeVerifyCId}
			//ToCId(string)
			//To18CId(string)
			//To18CId(_id)
			//cid_15to18(_15cid)
			//cid_18to15(_18cid)
			//bool VerifyCId(_18cid)
			
			CitizenId(){memset(&m_cid,0,sizeof(S_CitizenId));}
			CitizenId(
				OPENGB_CID_AREA_TYPE area,
				OPENGB_CID_BIRTHDAY_TYPE birthday,
				OPENGB_CID_ORDER_TYPE order,
				OPENGB_CID_CHECKSUM_TYPE checksum,
				bool check_cid = true
			){
				m_cid.area=area;
				m_cid.birthday=birthday;
				m_cid.order=order;
				m_cid.checksum=checksum;
				
//#warning Commented!
				if(check_cid){
					//if(!IsCid){
					//	throw ;
					//}
				}
			}
		};
		
	}
}

#endif