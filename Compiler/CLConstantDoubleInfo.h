#pragma once
#include "CLCPInfo.h"
#include "array"
class CLConstantDoubleInfo : public CLCPInfo {
public:
	double d;
	CLConstantDoubleInfo(double d);
	CLConstantDoubleInfo(const CLConstantDoubleInfo& obj);
	std::array<short, 4> low_bytes();
	std::array<short, 4> high_bytes();
	void write(CLOutputStream out);
	bool equals(CLConstantDoubleInfo obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
	std::array<short, 8> bytes();
};