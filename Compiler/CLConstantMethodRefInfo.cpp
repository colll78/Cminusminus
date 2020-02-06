#include "CLConstantMethodRefInfo.h"
#include "CLConstants.h"

CLConstantMethodRefInfo::CLConstantMethodRefInfo(int class_index, int name_and_type_index) : CLConstantMemberRefInfo(class_index, name_and_type_index, CLConstants::CONSTANT_Methodref){}

CLConstantMethodRefInfo::CLConstantMethodRefInfo(const CLConstantMethodRefInfo& obj) : CLConstantMemberRefInfo(obj.class_index, obj.name_and_type_index, CLConstants::CONSTANT_Methodref){}

std::unique_ptr<CLCPInfo> CLConstantMethodRefInfo::create_unique(){
	return std::make_unique<CLConstantMethodRefInfo>(*this);
}
