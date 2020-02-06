#pragma once
#include "CLConstantMemberRefInfo.h"

class CLConstantMethodRefInfo : public CLConstantMemberRefInfo {
public:
	CLConstantMethodRefInfo(int class_index, int name_and_type_index);
	CLConstantMethodRefInfo(const CLConstantMethodRefInfo& obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
};