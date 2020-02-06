#include "CLConstantStringInfo.h"
#include "CLConstants.h"

CLConstantStringInfo::CLConstantStringInfo(int string_index) : string_index(string_index) {
	tag = CLConstants::CONSTANT_String;
}

CLConstantStringInfo::CLConstantStringInfo(const CLConstantStringInfo& obj) : string_index(obj.string_index){
	tag = CLConstants::CONSTANT_String;
}

void CLConstantStringInfo::write(CLOutputStream out) {
	CLCPInfo::write(out);
	out.write(string_index);
}


bool CLConstantStringInfo::equals(CLConstantStringInfo obj) {
	if (obj.string_index == string_index) {
		return true;
	}
	return false;
}

std::unique_ptr<CLCPInfo> CLConstantStringInfo::create_unique(){
	return std::make_unique<CLConstantStringInfo>(*this);
}
