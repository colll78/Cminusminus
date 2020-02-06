#pragma once
#include "CLCPInfo.h"
#include "array"
class CLConstantLongInfo : public CLCPInfo {
public:
	long long l;
	CLConstantLongInfo(long long l);
	CLConstantLongInfo(const CLConstantLongInfo& obj);
	std::array<short, 4> low_bytes();
	std::array<short, 4> high_bytes();
	void write(CLOutputStream out);
	bool equals(CLConstantLongInfo obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
	std::array<short, 8> bytes();
};