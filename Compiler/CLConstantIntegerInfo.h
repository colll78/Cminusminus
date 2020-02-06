#pragma once
#include "CLCPInfo.h"
#include "array"
class CLConstantIntegerInfo : public CLCPInfo {
public:
	/* int number */
	int i;
	CLConstantIntegerInfo(int i);
	CLConstantIntegerInfo(const CLConstantIntegerInfo& obj);
	std::array<short, 4> bytes();
	void write(CLOutputStream out);
	bool equals(CLConstantIntegerInfo obj);
	std::unique_ptr<CLCPInfo> create_unique();
private:
	
};