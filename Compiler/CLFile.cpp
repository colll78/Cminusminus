#include "CLFile.h"
#include "CLConstants.h"
#include "jmm_utils.h"

void CLFile::write(CLOutputStream &out) {
	out.write_int(magic);
	out.write_short(minor_version);
	out.write_short(major_version);
	out.write_short(constant_pool_count);
	constant_pool.write(out);
	out.write_short(access_flags);
	out.write_short(this_class);
	out.write_short(super_class);
	out.write_short(interfaces_count);
	for (int i = 0; i < interfaces.size(); i++) {
		out.write_short(interfaces.at(i));
	}
	out.write_short(fields_count);
	for (int i = 0; i < fields.size(); i++) {
		fields.at(i).write(out);
	}
	out.write_short(methods_count);
	for (int i = 0; i < methods.size(); i++) {
		methods.at(i).write(out);
	}
	out.write_short(attributes_count);
	for (int i = 0; i < attributes.size(); i++) {
		attributes.at(i).write(out);
	}
}

std::string CLFile::class_access_flags_to_string(int access_flags){
	std::string b;
	if ((access_flags & CLConstants::ACC_PUBLIC) != 0) {
		b.append("public ");
	}
	if ((access_flags & CLConstants::ACC_FINAL) != 0) {
		b.append("final ");
	}
	if ((access_flags & CLConstants::ACC_SUPER) != 0) {
		b.append("super ");
	}
	if ((access_flags & CLConstants::ACC_INTERFACE) != 0) {
		b.append("interface ");
	}
	if ((access_flags & CLConstants::ACC_ABSTRACT) != 0) {
		b.append("abstract ");
	}
	if ((access_flags & CLConstants::ACC_SYNTHETIC) != 0) {
		b.append("synthetic ");
	}
	if ((access_flags & CLConstants::ACC_ANNOTATION) != 0) {
		b.append("annotation ");
	}
	if ((access_flags & CLConstants::ACC_ENUM) != 0) {
		b.append("enum ");
	}
	trim(b);
	return b;
}

std::string CLFile::inner_class_access_flags_to_string(int access_flags){
	std::string b;
	if ((access_flags & CLConstants::ACC_PUBLIC) != 0) {
		b.append("public ");
	}
	if ((access_flags & CLConstants::ACC_PRIVATE) != 0) {
		b.append("private ");
	}
	if ((access_flags & CLConstants::ACC_PROTECTED) != 0) {
		b.append("protected ");
	}
	if ((access_flags & CLConstants::ACC_STATIC) != 0) {
		b.append("static ");
	}
	if ((access_flags & CLConstants::ACC_FINAL) != 0) {
		b.append("final ");
	}
	if ((access_flags & CLConstants::ACC_INTERFACE) != 0) {
		b.append("interface ");
	}
	if ((access_flags & CLConstants::ACC_ABSTRACT) != 0) {
		b.append("abstract ");
	}
	if ((access_flags & CLConstants::ACC_SYNTHETIC) != 0) {
		b.append("synthetic ");
	}
	if ((access_flags & CLConstants::ACC_ANNOTATION) != 0) {
		b.append("annotation ");
	}
	if ((access_flags & CLConstants::ACC_ENUM) != 0) {
		b.append("enum ");
	}
	trim(b);
	return b;
}

std::string CLFile::field_access_flags_to_string(int access_flags){
	std::string b;
	if ((access_flags & CLConstants::ACC_PUBLIC) != 0) {
		b.append("public ");
	}
	if ((access_flags & CLConstants::ACC_PRIVATE) != 0) {
		b.append("private ");
	}
	if ((access_flags & CLConstants::ACC_PROTECTED) != 0) {
		b.append("protected ");
	}
	if ((access_flags & CLConstants::ACC_STATIC) != 0) {
		b.append("static ");
	}
	if ((access_flags & CLConstants::ACC_FINAL) != 0) {
		b.append("final ");
	}
	if ((access_flags & CLConstants::ACC_VOLATILE) != 0) {
		b.append("volatile ");
	}
	if ((access_flags & CLConstants::ACC_TRANSIENT) != 0) {
		b.append("transient ");
	}
	if ((access_flags & CLConstants::ACC_NATIVE) != 0) {
		b.append("native ");
	}
	if ((access_flags & CLConstants::ACC_SYNTHETIC) != 0) {
		b.append("synthetic ");
	}
	if ((access_flags & CLConstants::ACC_ENUM) != 0) {
		b.append("enum ");
	}
	trim(b);
	return b;
}

std::string CLFile::method_access_flags_to_string(int access_flags){
	std::string b;
	if ((access_flags & CLConstants::ACC_PUBLIC) != 0) {
		b.append("public ");
	}
	if ((access_flags & CLConstants::ACC_PRIVATE) != 0) {
		b.append("private ");
	}
	if ((access_flags & CLConstants::ACC_PROTECTED) != 0) {
		b.append("protected ");
	}
	if ((access_flags & CLConstants::ACC_STATIC) != 0) {
		b.append("static ");
	}
	if ((access_flags & CLConstants::ACC_FINAL) != 0) {
		b.append("final ");
	}
	if ((access_flags & CLConstants::ACC_SYNCHRONIZED) != 0) {
		b.append("synchronized ");
	}
	if ((access_flags & CLConstants::ACC_BRIDGE) != 0) {
		b.append("bridge ");
	}
	if ((access_flags & CLConstants::ACC_VARARGS) != 0) {
		b.append("varargs ");
	}
	if ((access_flags & CLConstants::ACC_NATIVE) != 0) {
		b.append("native ");
	}
	if ((access_flags & CLConstants::ACC_ABSTRACT) != 0) {
		b.append("abstract ");
	}
	if ((access_flags & CLConstants::ACC_STRICT) != 0) {
		b.append("strict ");
	}
	if ((access_flags & CLConstants::ACC_SYNTHETIC) != 0) {
		b.append("synthetic ");
	}
	trim(b);
	return b;
}

int CLFile::access_flag_to_int(std::string access_flags){
	int flag = 0;
	if (access_flags == "public") {
		flag = CLConstants::ACC_PUBLIC;
	}
	if (access_flags == "private") {
		flag = CLConstants::ACC_PRIVATE;
	}
	if (access_flags == "protected") {
		flag = CLConstants::ACC_PROTECTED;
	}
	if (access_flags == "static") {
		flag = CLConstants::ACC_STATIC;
	}
	if (access_flags == "final") {
		flag = CLConstants::ACC_FINAL;
	}
	if (access_flags == "super") {
		flag = CLConstants::ACC_SUPER;
	}
	if (access_flags == "synchronized") {
		flag = CLConstants::ACC_SYNCHRONIZED;
	}
	if (access_flags == "volatile") {
		flag = CLConstants::ACC_VOLATILE;
	}
	if (access_flags == "bridge") {
		flag = CLConstants::ACC_BRIDGE;
	}
	if (access_flags == "transient") {
		flag = CLConstants::ACC_TRANSIENT;
	}
	if (access_flags == "varargs") {
		flag = CLConstants::ACC_VARARGS;
	}
	if (access_flags == "native") {
		flag = CLConstants::ACC_NATIVE;
	}
	if (access_flags == "interface") {
		flag = CLConstants::ACC_INTERFACE;
	}
	if (access_flags == "abstract") {
		flag = CLConstants::ACC_ABSTRACT;
	}
	if (access_flags == "strict") {
		flag = CLConstants::ACC_STRICT;
	}
	if (access_flags == "synthetic") {
		flag = CLConstants::ACC_SYNTHETIC;
	}
	if (access_flags == "annotation") {
		flag = CLConstants::ACC_ANNOTATION;
	}
	if (access_flags == "enum") {
		flag = CLConstants::ACC_ENUM;
	}
	return flag;
}
