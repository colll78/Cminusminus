#pragma once
#include "CLAttributeInfo.h"

class CLMemberInfo {
public:
	int access_flags;
	int name_index;
	int descriptor_index;
	int attributes_count;
	std::vector<CLAttributeInfo> attributes;
	CLMemberInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<CLAttributeInfo> attributes);
	void write(CLOutputStream out);
};

class CLFieldInfo : public CLMemberInfo {
	CLFieldInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<CLAttributeInfo> attributes);
};


class CLMethodInfo : public CLMemberInfo {
	CLMethodInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<CLAttributeInfo> attributes);
};