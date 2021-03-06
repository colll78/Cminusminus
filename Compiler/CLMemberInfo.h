#pragma once
#include "CLAttributeInfo.h"

class CLMemberInfo {
public:
	int access_flags;
	int name_index;
	int descriptor_index;
	int attributes_count;
	std::vector<std::unique_ptr<CLAttributeInfo>> &attributes;
	CLMemberInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<std::unique_ptr<CLAttributeInfo>> &attributes);
	void write(CLOutputStream &out);
};

class CLFieldInfo : public CLMemberInfo {
public:
	CLFieldInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<std::unique_ptr<CLAttributeInfo>> &attributes);
};


class CLMethodInfo : public CLMemberInfo {
public:
	CLMethodInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<std::unique_ptr<CLAttributeInfo>> &attributes);
};