#pragma once
#include "CLCPInfo.h"

class CLConstantNameAndTypeInfo : public CLCPInfo {
public:
	int name_index;
	int descriptor_index;
	CLConstantNameAndTypeInfo(int name_index, int descriptor_index);
	CLConstantNameAndTypeInfo(const CLConstantNameAndTypeInfo& obj);
	void write(CLOutputStream out);
	bool equals(CLConstantNameAndTypeInfo obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
};