#pragma once
#include "CLCPInfo.h"

class CLConstantClassInfo : public CLCPInfo{
public:
	int name_index;
	CLConstantClassInfo(int name_index);
	CLConstantClassInfo(const CLConstantClassInfo& obj);
	void write(CLOutputStream out);
	bool equals(CLConstantClassInfo obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
};
