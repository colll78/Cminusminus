#pragma once
#include "CLCPInfo.h"
#include "array"

class CLConstantUTF8Info : public CLCPInfo {
public:
	std::vector<std::byte> b;
	CLConstantUTF8Info(std::vector<std::byte> b);
	CLConstantUTF8Info(const CLConstantUTF8Info& obj);
	int length();
	void write(CLOutputStream out);
	bool equals(CLConstantUTF8Info obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
};