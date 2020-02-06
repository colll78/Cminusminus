#include "CLConstantUTF8Info.h"
#include "CLConstants.h"

CLConstantUTF8Info::CLConstantUTF8Info(std::vector<std::byte> b) : b(b){
	tag = CLConstants::CONSTANT_Utf8;
}

CLConstantUTF8Info::CLConstantUTF8Info(const CLConstantUTF8Info& obj) : b(obj.b){
	tag = CLConstants::CONSTANT_Utf8;
}

int CLConstantUTF8Info::length() {
	return b.size();
}

void CLConstantUTF8Info::write(CLOutputStream out) {
	CLCPInfo::write(out);
	std::string str;
	str.reserve(b.size());
	std::transform(b.begin(), b.end(), std::back_inserter(str),
		[](std::byte value) {
			return char(value);
		}
	);
	out.write_UTF(str);
}

bool CLConstantUTF8Info::equals(CLConstantUTF8Info obj) {
	std::string obj_str;
	obj_str.reserve(obj.b.size());
	std::transform(obj.b.begin(), obj.b.end(), std::back_inserter(obj_str), 
		[](std::byte value){
			return char(value);
		}
	);
	/*
	for (int i = 0; i < obj.b.size(); i++) {
		obj_str.push_back(char(b[i]));
	}
	*/
	std::string str;
	str.reserve(b.size());
	std::transform(b.begin(), b.end(), std::back_inserter(str),
		[](std::byte value) {
			return char(value);
		}
	);
	return(obj_str == str);
}

std::unique_ptr<CLCPInfo> CLConstantUTF8Info::create_unique(){
	return std::make_unique<CLConstantUTF8Info>(*this);
}
