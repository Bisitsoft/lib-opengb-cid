// Citizen Identification Number
// GB 11643-1999

#if !defined(__ctzidn_h_)
	#define __ctzidn_h_
	#include "opengb_cid_switches.h"
	
	#include "ctzidn_def.h"
	
	#include <cstdlib>
	
	#include "mod11_2.h"
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

namespace opengb{
	namespace ctzidn{
		namespace Sex{
			enum Sex{
				Male=1,
				Female=2,
			};
		}
		
		namespace CIdType{
			enum CIdType{
				Unknown=0,
				_15CId=1,
				_18Cid=2
			};
		}
		
		typedef struct{
			OPENGB_CID_AREA_TYPE area;
			OPENGB_CID_BIRTHDAY_TYPE birthday;
			OPENGB_CID_ORDER_TYPE order;
			OPENGB_CID_CHECKSUM_TYPE checksum;
		}S_CitizenId;
		
		class CitizenId{
		private:
			void Initialize(
				OPENGB_CID_AREA_TYPE area,
				OPENGB_CID_BIRTHDAY_TYPE birthday,
				OPENGB_CID_ORDER_TYPE order,
				OPENGB_CID_CHECKSUM_TYPE checksum,
				bool check_cid = true
			);
		protected:
			S_CitizenId m_cid;
			
			int GetNumberLength(unsigned long int n);
		public:
			OPENGB_CID_AREA_TYPE get_Area();
			OPENGB_CID_BIRTHDAY_TYPE get_Birthday();
			OPENGB_CID_ORDER_TYPE get_Order();
			OPENGB_CID_CHECKSUM_TYPE get_Checksum();
			S_CitizenId get_Cid();
			
			Sex::Sex get_Sex();
			
			bool is_18Cid();
			bool is_15Cid();
			
			//void To18CId(string)
			//void To18CId(_id)
//#warning Commented!
			//bool IsCId(){...; FindAreaCodeVerifyCId}
			//ToCId(string)
			//To18CId(string)
			//To18CId(_id)
			//getAddress()//返回lib-opengb-acd中的AreaNode的链表
			//cid_15to_18Cid(const CitizenId &_15cid)
			//cid_18to15(_18cid)
			
			bool VerifyChecksum(){
				return m_cid.checksum==_OPENGB_MOD11_2_METHOD(*this);
			}
			
			
			
			CitizenId();
			CitizenId(const S_CitizenId &cid);
			CitizenId(
				const OPENGB_CID_AREA_TYPE area,
				const OPENGB_CID_BIRTHDAY_TYPE birthday,
				const OPENGB_CID_ORDER_TYPE order,
				const OPENGB_CID_CHECKSUM_TYPE checksum,
				const bool check_cid = true
			);
		};
		
		
		
		//class CalculatedCitizenId: public CitizenId{
		//	private:
		//		bool _sex;
		//		CIdType _cidType;
		//	//各个属性都是提前计算好的CId类。
		//};
		
	}
}

#endif