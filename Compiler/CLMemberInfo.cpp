#include "CLMemberInfo.h"

CLMemberInfo::CLMemberInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<CLAttributeInfo> attributes)
	: access_flags(access_flags), name_index(name_index), descriptor_index(descriptor_index), attributes_count(attributes_count), attributes(attributes)
{
}

void CLMemberInfo::write(CLOutputStream& out){
	out.write_short(access_flags);
	out.write_short(name_index);
	out.write_short(descriptor_index);
	out.write_short(attributes_count);
	for (int i = 0; i < attributes.size(); i++) {
		attributes.at(i).write(out);
	}
}

CLFieldInfo::CLFieldInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<CLAttributeInfo> attributes)
: CLMemberInfo(access_flags, name_index, descriptor_index, attributes_count, attributes){}

CLMethodInfo::CLMethodInfo(int access_flags, int name_index, int descriptor_index, int attributes_count, std::vector<CLAttributeInfo> attributes)
	: CLMemberInfo(access_flags, name_index, descriptor_index, attributes_count, attributes) {}
