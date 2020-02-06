#pragma once
#include "CLCPInfo.h"

class CLConstantStringInfo : public CLCPInfo{
public:
	int string_index;
	CLConstantStringInfo(int string_index);
	CLConstantStringInfo(const CLConstantStringInfo& obj);
	virtual void write(CLOutputStream out);
	virtual bool equals(CLConstantStringInfo obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
};