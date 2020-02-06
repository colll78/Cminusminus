#include "CLConstantNameAndTypeInfo.h"
#include "CLConstants.h"
CLConstantNameAndTypeInfo::CLConstantNameAndTypeInfo(int name_index, int descriptor_index) : name_index(name_index), descriptor_index(descriptor_index) {
	tag = CLConstants::CONSTANT_NameAndType;
}

CLConstantNameAndTypeInfo::CLConstantNameAndTypeInfo(const CLConstantNameAndTypeInfo& obj) : name_index(obj.name_index), descriptor_index(obj.descriptor_index){
	tag = CLConstants::CONSTANT_NameAndType;
}

void CLConstantNameAndTypeInfo::write(CLOutputStream out) {
	CLCPInfo::write(out);
	out.write_short(name_index);
	out.write_short(descriptor_index);
}

bool CLConstantNameAndTypeInfo::equals(CLConstantNameAndTypeInfo obj) {
	return (obj.name_index == name_index && obj.descriptor_index == descriptor_index);
}

std::unique_ptr<CLCPInfo> CLConstantNameAndTypeInfo::create_unique(){
	return std::make_unique<CLConstantNameAndTypeInfo>(*this);
}
