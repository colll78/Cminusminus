#pragma once
#include "CLConstantMemberRefInfo.h"

class CLConstantInterfaceMethodRefInfo : public CLConstantMemberRefInfo {
public:
	CLConstantInterfaceMethodRefInfo(int class_index, int name_and_type_index);
	CLConstantInterfaceMethodRefInfo(const CLConstantInterfaceMethodRefInfo& obj);
	std::unique_ptr<CLCPInfo> create_unique();
private: 
};