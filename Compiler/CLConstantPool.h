#pragma once
#include "CLCPInfo.h"
#include <optional>
#include <memory>
class CLConstantPool {
public:
	CLConstantPool();
	int size();
	int find(CLCPInfo& cp_info);
	CLCPInfo* cp_item(int i);
	int add_cp_item(CLCPInfo &cp_info);
	void write(CLOutputStream& out);
	int constant_class_info(std::string s);
	int constant_field_ref_info(std::string class_name, std::string name, std::string type);
	int constant_method_ref_info(std::string class_name, std::string name, std::string type);
	int constant_interface_method_ref_info(std::string class_name, std::string name, std::string type);
	int constant_string_info(std::string s);
	int constant_integer_info(int i);
	int constant_float_info(float f);
	int constant_long_info(long long l);
	int constant_double_info(double d);
	int constant_name_and_type_info(std::string name, std::string type);
	int constant_UTF8_info(std::string s);
private:
	/* Index of the next item into the constant pool */
	int cp_index;
	std::vector<std::unique_ptr<CLCPInfo>> cp_items;
	int find_or_add(CLCPInfo &cp_info);
};