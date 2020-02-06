#pragma once
#include "CLCPInfo.h"
class CLConstantMemberRefInfo : public CLCPInfo {
public:
	int class_index;
	int name_and_type_index;
	CLConstantMemberRefInfo(int class_index, int name_and_type_index, short tag);
	CLConstantMemberRefInfo(const CLConstantMemberRefInfo& obj);
	void write(CLOutputStream out);
	bool equals(CLConstantMemberRefInfo obj);
	virtual std::unique_ptr<CLCPInfo> create_unique();
private:
};
