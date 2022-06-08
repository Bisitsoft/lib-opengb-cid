#include "ctzidn.h"

using opengb;
using opengb::ctzidn;

void CitizenId::Initialize(
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
	
	//if(check_cid){
	//	if(!IsCid){
	//		throw ;
	//	}
	//}
}



int CitizenId::GetNumberLength(unsigned long int n){
	int count=0;
	while(n>0){
		n/=10;
		count++;
	}
	return count;
}



OPENGB_CID_AREA_TYPE CitizenId::get_Area() { return m_cid.area; }
OPENGB_CID_BIRTHDAY_TYPE CitizenId::get_Birthday() { return m_cid.birthday; }
OPENGB_CID_ORDER_TYPE CitizenId::get_Order() { return m_cid.order; }
OPENGB_CID_CHECKSUM_TYPE CitizenId::get_Checksum() { return m_cid.checksum; }
S_CitizenId CitizenId::get_Cid() { return m_cid; }
			
Sex CitizenId::get_Sex(){
	return m_cid.order%2 == 0 ? Sex::Female : Sex::Male;
}



bool CitizenId::is_18Cid(){
	return GetNumberLength(m_cid.birthday)==8;
}
bool CitizenId::is_15Cid(){
	return GetNumberLength(m_cid.birthday)==6; //理论上应该不存在190X年的生日。
		//&& m_cid.birthday == 0;
}



bool CitizenId::VerifyChecksum(){
	return m_cid.checksum==_OPENGB_MOD11_2_METHOD(*this);
}



CitizenId::CitizenId(){
	memset(&m_cid,0,sizeof(S_CitizenId));
}

CitizenId::CitizenId(const S_CitizenId &cid){
	Initialize(cid.area,cid.birthday,cid.order,cid.checksum,check_cid);
}

CitizenId::CitizenId(
	const OPENGB_CID_AREA_TYPE area,
	const OPENGB_CID_BIRTHDAY_TYPE birthday,
	const OPENGB_CID_ORDER_TYPE order,
	const OPENGB_CID_CHECKSUM_TYPE checksum,
	const bool check_cid = true
){
	Initialize(area,birthday,order,checksum,check_cid);
}