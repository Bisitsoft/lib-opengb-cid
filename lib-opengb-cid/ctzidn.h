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
����ѡ��Ĵ洢��ʽ��
	���ֽڴ洢����1~X�洢��4�������У�������Ϊһ���ֽڣ�����9���ֽڡ�
	�����洢�������������֤�Ŵ洢��int64�С�
		������ʾ�����ø�����ʾ���һλΪX������Ϊ0~9.
		����λ��ʾ�������һ������ռ����10��������λ����3��Ϊ03��X��Ϊ10��
	�ַ�����ʾ�����洢���ַ����У� <-����չ�����
		Ҳ�����Ƕ���18λ�ַ����顣
	�ṹ���ʾ���������š����ա�˳���롢У����ֱ�洢��
		������ʾ�����ֱ�洢��int32��int32��int16��byte�С� <-����չ�Խϸ�
		λ��ʾ����20b��24b��10b��4b��58b����7�ֽڡ� <- ����ά����ʹ��
		����λ��ʾ������������34�����μ�����������X����ͳ�ƣ�����5+14=19λ��ʾ���š� <- ����ά����ʹ��
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
			//getAddress()//����lib-opengb-acd�е�AreaNode������
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
		//	//�������Զ�����ǰ����õ�CId�ࡣ
		//};
		
	}
}

#endif