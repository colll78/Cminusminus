#pragma once
#include "CLConstantMemberRefInfo.h"

class CLConstantFieldRefInfo : public CLConstantMemberRefInfo {
public:
	CLConstantFieldRefInfo(int class_index, int name_and_type_index);
	CLConstantFieldRefInfo(const CLConstantFieldRefInfo& obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
};
