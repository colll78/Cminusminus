#include "CLConstantFieldRefInfo.h"
#include "CLCPInfo.h"
#include "CLConstants.h"

CLConstantFieldRefInfo::CLConstantFieldRefInfo(int class_index, int name_and_type_index) : CLConstantMemberRefInfo(class_index, name_and_type_index, CLConstants::CONSTANT_Fieldref) {

}

CLConstantFieldRefInfo::CLConstantFieldRefInfo(const CLConstantFieldRefInfo& obj) : CLConstantMemberRefInfo(obj.class_index, obj.name_and_type_index, CLConstants::CONSTANT_Fieldref){}

std::unique_ptr<CLCPInfo> CLConstantFieldRefInfo::create_unique(){
	return std::make_unique<CLConstantFieldRefInfo>(*this);
}
