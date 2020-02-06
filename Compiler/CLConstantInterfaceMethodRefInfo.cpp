#include "CLConstantInterfaceMethodRefInfo.h"
#include "CLConstants.h"

CLConstantInterfaceMethodRefInfo::CLConstantInterfaceMethodRefInfo(int class_index, int name_and_type_index) : CLConstantMemberRefInfo(class_index, name_and_type_index, CLConstants::CONSTANT_InterfaceMethodref){}

CLConstantInterfaceMethodRefInfo::CLConstantInterfaceMethodRefInfo(const CLConstantInterfaceMethodRefInfo& obj) : CLConstantMemberRefInfo(obj.class_index, obj.name_and_type_index, CLConstants::CONSTANT_InterfaceMethodref){}

std::unique_ptr<CLCPInfo> CLConstantInterfaceMethodRefInfo::create_unique(){
	return std::make_unique<CLConstantInterfaceMethodRefInfo>(*this);
}
