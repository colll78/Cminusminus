#pragma once
#include "CLCPInfo.h"
#include "array"
class CLConstantFloatInfo : public CLCPInfo {
public:
	float f;
	CLConstantFloatInfo(float f);
	CLConstantFloatInfo(const CLConstantFloatInfo& obj);
	std::array<short, 4> bytes();
	void write(CLOutputStream out);
	bool equals(CLConstantFloatInfo obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
};