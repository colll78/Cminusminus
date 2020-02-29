#pragma once
#include "CLMemberInfo.h"
#include "CLConstantPool.h"

class CLFile {
public:
	CLFile();
	long long magic; // 0xCAFEBABE
	int minor_version;
	int major_version;
	int constant_pool_count;
	CLConstantPool constant_pool;
	int access_flags;
	int this_class;
	int super_class;
	int interfaces_count;
	std::vector<int> interfaces;
	int fields_count;
	std::vector<CLFieldInfo> fields;
	int methods_count;
	std::vector<CLMethodInfo> methods;
	int attributes_count;
	std::vector<std::unique_ptr<CLAttributeInfo>> *attributes;
	void write(CLOutputStream& out);
	std::string class_access_flags_to_string(int access_flags);
	std::string inner_class_access_flags_to_string(int access_flags);
	std::string field_access_flags_to_string(int access_flags);
	std::string method_access_flags_to_string(int access_flags);
	static int access_flag_to_int(std::string access_flags);

};