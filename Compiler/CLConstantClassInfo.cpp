#include "CLConstantClassInfo.h"
#include "CLCPInfo.h"
#include "CLConstants.h"

CLConstantClassInfo::CLConstantClassInfo(int name_index) : name_index(name_index) {
	tag = CLConstants::CONSTANT_Class;
}

CLConstantClassInfo::CLConstantClassInfo(const CLConstantClassInfo& obj) : name_index(obj.name_index){
	tag = CLConstants::CONSTANT_Class;
}

void CLConstantClassInfo::write(CLOutputStream out) {
	CLCPInfo::write(out);
	out.write_short(name_index);
}

bool CLConstantClassInfo::equals(CLConstantClassInfo obj) {
	if (obj.name_index == name_index) {
		return true;
	}
	return false;
}

std::unique_ptr<CLCPInfo> CLConstantClassInfo::create_unique(){
	return std::make_unique<CLConstantClassInfo>(*this);
}
