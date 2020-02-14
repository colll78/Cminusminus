#include "CLConstantPool.h"
#include <algorithm>
#include <optional>
#include <typeinfo>
#include "CLConstantIntegerInfo.h"
#include "CLConstantClassInfo.h"
#include "CLConstantFieldRefInfo.h"
#include "CLConstantMethodRefInfo.h"
#include "CLConstantInterfaceMethodRefInfo.h"
#include "CLConstantStringInfo.h"
#include "CLConstantIntegerInfo.h"
#include "CLConstantFloatInfo.h"
#include "CLConstantLongInfo.h"
#include "CLConstantDoubleInfo.h"
#include "CLConstantNameAndTypeInfo.h"
#include "CLConstantUTF8Info.h"
#include "jmm_utils.h"

CLConstantPool::CLConstantPool() : cp_index(1) {}

int CLConstantPool::size(){
	return cp_items.size();
}

int CLConstantPool::find(CLCPInfo &cp_info){
	std::vector<std::unique_ptr<CLCPInfo>>::iterator cp_info_index = std::find_if(
		cp_items.begin(),
		cp_items.end(),
		[&](std::unique_ptr<CLCPInfo> const& obj){
			if (typeid(*obj) == typeid(cp_info)) {
				return obj->equals(cp_info);
			}
			return false;
		}
	);
	if (cp_info_index != cp_items.end()) {
		return std::distance(cp_items.begin(), cp_info_index);
	}
	return -1;
}

int CLConstantPool::find_or_add(CLCPInfo &cp_info){
	int index = find(cp_info);
	if (index == -1) {
		add_cp_item(cp_info);
	}
	return index;
}

CLCPInfo* CLConstantPool::cp_item(int i){
	if (((i - 1) < 0) || ((i - 1) >= cp_items.size())) {
		return nullptr;
	}
	return cp_items.at(i - 1).get();
}

int CLConstantPool::add_cp_item(CLCPInfo &cp_info){
	int i = cp_index++;
	cp_info.cp_index = i;
	cp_items.push_back(cp_info.create_unique());
	const std::type_info &cp_info_type = typeid(cp_info);
	if ( cp_info_type == typeid(CLConstantLongInfo) || cp_info_type == typeid(CLConstantDoubleInfo)) {
		cp_index++;
		cp_items.push_back(nullptr);
	}
	return i;
}

void CLConstantPool::write(CLOutputStream& out){
	for (int i = 0; i < cp_items.size(); i++) {
		CLCPInfo* cp_info = cp_items.at(i).get();
		if (cp_info != nullptr) {
			cp_info->write(out);
		}
	}
}

int CLConstantPool::constant_class_info(std::string s){
	CLConstantClassInfo c(constant_UTF8_info(s));
	return find_or_add(c);
}

int CLConstantPool::constant_field_ref_info(std::string class_name, std::string name, std::string type){
	CLConstantFieldRefInfo c(constant_class_info(class_name), constant_name_and_type_info(name, type));
	return find_or_add(c);
}

int CLConstantPool::constant_method_ref_info(std::string class_name, std::string name, std::string type){
	CLConstantMethodRefInfo c(constant_class_info(class_name), constant_name_and_type_info(name, type));
	return find_or_add(c);
}

int CLConstantPool::constant_interface_method_ref_info(std::string class_name, std::string name, std::string type){
	CLConstantInterfaceMethodRefInfo c(constant_class_info(class_name), constant_name_and_type_info(name, type));
	return find_or_add(c);
}

int CLConstantPool::constant_string_info(std::string s){
	CLConstantStringInfo c(constant_UTF8_info(s));
	return find_or_add(c);
}

int CLConstantPool::constant_integer_info(int i){
	CLConstantIntegerInfo c(i);
	return find_or_add(c);
}

int CLConstantPool::constant_float_info(float f){
	CLConstantFloatInfo c(f);
	return find_or_add(c);
}

int CLConstantPool::constant_long_info(long long l){
	CLConstantLongInfo c(l);
	return find_or_add(c);
}

int CLConstantPool::constant_double_info(double d){
	CLConstantDoubleInfo c(d);
	return find_or_add(c);
}

int CLConstantPool::constant_name_and_type_info(std::string name, std::string type){
	CLConstantNameAndTypeInfo c(constant_UTF8_info(name), constant_UTF8_info(type));
	return find_or_add(c);
}

int CLConstantPool::constant_UTF8_info(std::string s){
	CLConstantUTF8Info c(string_to_bytes(s));
	return find_or_add(c);
}
