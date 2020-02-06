#include "CLConstantMemberRefInfo.h"
#include "CLCPInfo.h"
#include "CLConstants.cpp"

CLConstantMemberRefInfo::CLConstantMemberRefInfo(int class_index, int name_and_type_index, short tag) : class_index(class_index), name_and_type_index(name_and_type_index){
	tag = tag;
}

CLConstantMemberRefInfo::CLConstantMemberRefInfo(const CLConstantMemberRefInfo& obj) : class_index(obj.class_index), name_and_type_index(obj.name_and_type_index){
	tag = tag;
}

void CLConstantMemberRefInfo::write(CLOutputStream out) {
	CLCPInfo::write(out);
	out.write(class_index);
	out.write(name_and_type_index);
}

bool CLConstantMemberRefInfo::equals(CLConstantMemberRefInfo obj) {
	if (obj.tag == tag && obj.class_index == class_index) {
		return true;
	}
	return false;
}

std::unique_ptr<CLCPInfo> CLConstantMemberRefInfo::create_unique(){
	return std::make_unique<CLConstantMemberRefInfo>(*this);
}
