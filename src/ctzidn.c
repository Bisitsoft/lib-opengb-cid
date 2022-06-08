#include "ctzidn.h"

int GetNumberLength(unsigned long int n);



int GetNumberLength(unsigned long int n){
	int count=0;
	while(n>0){
		n/=10;
		count++;
	}
	return count;
}


			
int GetSex(const CitizenId *cid){
	return cid->order%2 == 0 ? OPENGB_CID_SEX_FEMALE : OPENGB_CID_SEX_MALE;
}



bool Is18CId(const CitizenId *cid){
	return GetNumberLength(cid->birthday)==8;
}
bool Is15CId(const CitizenId *cid){
	return GetNumberLength(cid->birthday)==6; //理论上应该不存在190X年的生日。
		//&& m_cid.birthday == 0;
}



bool VerifyCIdChecksum(const CitizenId *_18cid){
	return _18cid->checksum==_OPENGB_MOD11_2_METHOD(_18cid);
}
