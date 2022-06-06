// Citizen Identification Number
// GB 11643-1999

#if !defined(__cizidn_h_)
	#define __cizidn_h_
	
	#include <cstdlib>
	
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