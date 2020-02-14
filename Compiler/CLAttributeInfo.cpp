#include "CLAttributeInfo.h"
#include "CLConstants.h"

CLAttributeInfo::CLAttributeInfo(int attribute_name_index, long long attribute_length) : attribute_name_index(attribute_name_index), attribute_length(attribute_length){
}

void CLAttributeInfo::write(CLOutputStream& out){
	out.write_short(attribute_name_index);
	out.write_int((long long)attribute_length);
}

CLConstantValueAttribute::CLConstantValueAttribute(int attribute_name_index, long long attribute_length, int constant_value_index) : CLAttributeInfo(attribute_name_index, attribute_length), constant_value_index(constant_value_index) {
}

void CLConstantValueAttribute::write(CLOutputStream& out) {
	CLAttributeInfo::write(out);
	out.write_short(constant_value_index);
}

CLExceptionInfo::CLExceptionInfo(int start_pc, int end_pc, int handler_pc, int catch_type) : start_pc(start_pc), end_pc(end_pc), handler_pc(handler_pc), catch_type(catch_type){
}

void CLExceptionInfo::write(CLOutputStream& out){
	out.write_short(start_pc);
	out.write_short(end_pc);
	out.write_short(handler_pc);
	out.write_short(catch_type);
}

int CLCodeAttribute::int_value(int a, int b, int c, int d) {
	return (a << 24) | (b << 16) | (c << 8) | (d << 0);
}

CLCodeAttribute::CLCodeAttribute(int attribute_name_index, long long attribute_length, int max_stack, int max_locals, 
	long long code_length, std::vector<int> code, int exception_table_length, std::vector<CLExceptionInfo> exception_table,
	int attributes_count, std::vector<std::unique_ptr<CLAttributeInfo>> &attributes) :
	CLAttributeInfo(attribute_name_index, attribute_length), max_stack(max_stack), max_locals(max_locals), code_length(code_length), code(), exception_table_length(exception_table_length),
	exception_table(exception_table), attributes_count(attributes_count), attributes(attributes)
{
}

void CLCodeAttribute::write(CLOutputStream& out){
	CLCodeAttribute::write(out);
	out.write_short(max_stack);
	out.write_short(max_locals);
	out.write_int(code_length);
	for (int i = 0; i < code.size(); i++) {
		out.write_byte(code.at(i));
	}
	out.write_short(exception_table_length);
	for (int i = 0; i < exception_table.size(); i++) {
		exception_table.at(i).write(out);
	}
	out.write_short(attributes_count);
	for (int i = 0; i < attributes.size(); i++) {
		attributes.at(i).get()->write(out);
	}
}

CLExceptionsAttribute::CLExceptionsAttribute(int attribute_name_index, long long attribute_length, int number_of_exceptions, std::vector<int> exception_index_table)
	: CLAttributeInfo(attribute_name_index, attribute_length), number_of_exceptions(number_of_exceptions), exception_index_table(exception_index_table)
{
}

void CLExceptionsAttribute::write(CLOutputStream& out) {
	CLAttributeInfo::write(out);
	out.write_short(number_of_exceptions);
	for (int i = 0; i < exception_index_table.size(); i++) {
		out.write_short(exception_index_table.at(i));
	}
}

CLInnerClassInfo::CLInnerClassInfo(int inner_class_info_index, int outer_class_info_index, int inner_name_index, int inner_class_access_flags)
	: inner_class_info_index(inner_class_info_index), outer_class_info_index(outer_class_info_index), inner_name_index(inner_name_index), inner_class_access_flags(inner_class_access_flags)
{
}

void CLInnerClassInfo::write(CLOutputStream& out){
	out.write_short(inner_class_info_index);
	out.write_short(outer_class_info_index);
	out.write_short(inner_name_index);
	out.write_short(inner_class_access_flags);
}

CLInnerClassesAttribute::CLInnerClassesAttribute(int attribute_name_index, long long attribute_length, int number_of_classes, std::vector<CLInnerClassInfo> classes)
	: CLAttributeInfo(attribute_name_index, attribute_length), number_of_classes(number_of_classes), classes(classes)
{
}

void CLInnerClassesAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_short(number_of_classes);
	for (int i = 0; i < classes.size(); i++) {
		classes.at(i).write(out);
	}
}

CLEnclosingMethodAttribute::CLEnclosingMethodAttribute(int attribute_name_index, long long attribute_length, int class_index, int method_index)
	: CLAttributeInfo(attribute_name_index, attribute_length), class_index(class_index), method_index(method_index)
{
}

void CLEnclosingMethodAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_short(class_index);
	out.write_short(method_index);
}

CLSyntheticAttribute::CLSyntheticAttribute(int attribute_name_index, long long attribute_length) : CLAttributeInfo(attribute_name_index, attribute_length)
{
}

void CLSyntheticAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
}

CLSignatureAttribute::CLSignatureAttribute(int attribute_name_index, long long attribute_length, int signature_index)
: CLAttributeInfo(attribute_name_index, attribute_length), signature_index(signature_index) {
}

void CLSignatureAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_short(signature_index);
}

CLSourceFileAttribute::CLSourceFileAttribute(int attribute_name_index, long long attribute_length, int source_file_index)
	: CLAttributeInfo(attribute_name_index, attribute_length), source_file_index(source_file_index)
{
}

void CLSourceFileAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_short(source_file_index);
}

CLSourceDebugExtensionAttribute::CLSourceDebugExtensionAttribute(int attribute_name_index, long long attribute_length, std::vector<std::byte> debug_extension)
	: CLAttributeInfo(attribute_name_index, attribute_length), debug_extension(debug_extension)
{
}

void CLSourceDebugExtensionAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	for (int i = 0; i < debug_extension.size(); i++) {
		out.write_byte((int)debug_extension.at(i));
	}
}

CLLineNumberInfo::CLLineNumberInfo(int start_pc, int line_number) : start_pc(start_pc), line_number(line_number)
{
}

void CLLineNumberInfo::write(CLOutputStream& out){
	out.write_short(start_pc);
	out.write_short(line_number);
}

bool CLLineNumberInfo::equals(CLLineNumberInfo obj){
	return (obj.line_number == line_number);
}

CLLineNumberTableAttribute::CLLineNumberTableAttribute(int attribute_name_index, long long attribute_length, int line_number_table_length, std::vector<CLLineNumberInfo> line_number_table)
	: CLAttributeInfo(attribute_name_index, attribute_length), line_number_table_length(line_number_table_length), line_number_table(line_number_table)
{
}

void CLLineNumberTableAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_short(line_number_table_length);
	for (int i = 0; i < line_number_table.size(); i++) {
		line_number_table.at(i).write(out);
	}
}

CLLocalVariableInfo::CLLocalVariableInfo(int start_pc, int length, int name_index, int descriptor_index, int index)
	: start_pc(start_pc), length(length), name_index(name_index), descriptor_index(descriptor_index), index(index)
{
}

void CLLocalVariableInfo::write(CLOutputStream& out){
	out.write_short(start_pc);
	out.write_short(length);
	out.write_short(name_index);
	out.write_short(descriptor_index);
	out.write_short(index);
}

CLLocalVariableTableAttribute::CLLocalVariableTableAttribute(int attribute_name_index, long long attribute_length, int local_variable_table_length, std::vector<CLLocalVariableInfo> local_variable_table)
	: CLAttributeInfo(attribute_name_index, attribute_length), local_variable_table_length(local_variable_table_length), local_variable_table(local_variable_table)
{
}

void CLLocalVariableTableAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_short(local_variable_table_length);
	for (int i = 0; i < local_variable_table.size(); i++) {
		local_variable_table.at(i).write(out);
	}
}

CLLocalVariableTypeInfo::CLLocalVariableTypeInfo(int start_pc, int length, int name_index, int signature_index, int index)
	: start_pc(start_pc), length(length), name_index(name_index), signature_index(signature_index), index(index)
{
}

void CLLocalVariableTypeInfo::write(CLOutputStream& out){
	out.write_short(start_pc);
	out.write_short(length);
	out.write_short(name_index);
	out.write_short(signature_index);
	out.write_short(index);
}

CLLocalVariableTypeTableAttribute::CLLocalVariableTypeTableAttribute(int attribute_name_index, long long attribute_length, int local_variable_type_table_length, std::vector<CLLocalVariableTypeInfo> local_variable_type_table)
	: CLAttributeInfo(attribute_name_index, attribute_length), local_variable_type_table_length(local_variable_type_table_length), local_variable_type_table(local_variable_type_table)
{
}

void CLLocalVariableTypeTableAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_short(local_variable_type_table_length);
	for (int i = 0; i < local_variable_type_table.size(); i++) {
		local_variable_type_table.at(i).write(out);
	}
}

CLDeprecatedAttribute::CLDeprecatedAttribute(int attribute_name_index, long long attribute_length)
	: CLAttributeInfo(attribute_name_index, attribute_length)
{
}

void CLDeprecatedAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
}

CLAnnotation::CLAnnotation() {

}

CLAnnotation::CLAnnotation(int type_index, int num_element_value_pairs, std::vector<CLElementValuePair> element_value_pairs) 
: type_index(type_index), num_element_value_pairs(num_element_value_pairs), element_value_pairs(element_value_pairs) {

}

void CLAnnotation::write(CLOutputStream& out) {
	out.write_short(type_index);
	out.write_short(num_element_value_pairs);
	for (int i = 0; i < element_value_pairs.size(); i++) {
		element_value_pairs.at(i).write(out);
	}
}

CLElementValue::CLElementValue(short tag, int const_value_index) : tag(tag), const_value_index(const_value_index){}

CLElementValue::CLElementValue(int type_name_index, int const_name_index) : type_name_index(type_name_index), const_name_index(const_name_index){
	tag = CLConstants::ELT_e;
}

CLElementValue::CLElementValue(int class_info_index) : class_info_index(class_info_index) {
	tag = CLConstants::ELT_c;
}

CLElementValue::CLElementValue(CLAnnotation annotation_value) : annotation_value(annotation_value) {
	tag = CLConstants::ELT_ANNOTATION;
}

CLElementValue:: CLElementValue(int num_values, std::vector<CLElementValue> values) : num_values(num_values), values(values){
	tag = CLConstants::ELT_ARRAY;
}

void CLElementValue::write(CLOutputStream& out){
	out.write_byte(tag);
	switch (tag) {
	case CLConstants::ELT_B:
	case CLConstants::ELT_C:
	case CLConstants::ELT_D:
	case CLConstants::ELT_F:
	case CLConstants::ELT_I:
	case CLConstants::ELT_J:
	case CLConstants::ELT_S:
	case CLConstants::ELT_Z:
	case CLConstants::ELT_s:
		out.write_int(const_value_index);
		break;
	case CLConstants::ELT_e:
		out.write_int(type_name_index);
		out.write_int(const_name_index);
		break;
	case CLConstants::ELT_c:
		out.write_int(class_info_index);
		break;
	case CLConstants::ELT_ANNOTATION:
		annotation_value.write(out);
		break;
	case CLConstants::ELT_ARRAY:
		out.write_int(num_values);
		for (int i = 0; i < num_values; i++) {	
			values.at(i).write(out);
		}
	}
}

CLElementValuePair::CLElementValuePair(int element_name_index, CLElementValue value) : element_name_index(element_name_index), value(value) {}

void CLElementValuePair::write(CLOutputStream& out){
	out.write_short(element_name_index);
	value.write(out);
}

CLRuntimeVisibleAnnotationsAttribute::CLRuntimeVisibleAnnotationsAttribute(int attribute_name_index, long long attribute_length, int num_annotations, std::vector<CLAnnotation> annotations)
 : CLAttributeInfo(attribute_name_index, attribute_length), num_annotations(num_annotations), annotations(annotations){}

void CLRuntimeVisibleAnnotationsAttribute::write(CLOutputStream& out) {
	CLAttributeInfo::write(out);
	out.write_short(num_annotations);
	for (int i = 0; i < annotations.size(); i++) {
		annotations.at(i).write(out);
	}
}

CLRuntimeInvisibleAnnotationsAttribute::CLRuntimeInvisibleAnnotationsAttribute(int attribute_name_index, long long attribute_length, int num_annotations, std::vector<CLAnnotation> annotations)
	: CLAttributeInfo(attribute_name_index, attribute_length), num_annotations(num_annotations), annotations(annotations) {}

void CLRuntimeInvisibleAnnotationsAttribute::write(CLOutputStream& out) {
	CLAttributeInfo::write(out);
	out.write_short(num_annotations);
	for (int i = 0; i < annotations.size(); i++) {
		annotations.at(i).write(out);
	}
}

CLParameterAnnotationInfo::CLParameterAnnotationInfo(int num_annotations, std::vector<CLAnnotation> annotations)
: num_annotations(num_annotations), annotations(annotations) {}

void CLParameterAnnotationInfo::write(CLOutputStream& out){
	out.write_short(num_annotations);
	for (int i = 0; i < annotations.size(); i++) {
		annotations.at(i).write(out);
	}
}

CLRuntimeVisibleParameterAnnotationsAttribute::CLRuntimeVisibleParameterAnnotationsAttribute(int attribute_name_index, long long attribute_length, short num_parameters, std::vector<CLParameterAnnotationInfo> parameter_annotations)
	: CLAttributeInfo(attribute_name_index, attribute_length) {}

void CLRuntimeVisibleParameterAnnotationsAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_byte(num_parameters);
	for (int i = 0; i < parameter_annotations.size(); i++) {
		parameter_annotations.at(i).write(out);
	}
}

CLRuntimeInvisibleParameterAnnotationsAttribute::CLRuntimeInvisibleParameterAnnotationsAttribute(int attribute_name_index, long long attribute_length, short num_parameters, std::vector<CLParameterAnnotationInfo> parameter_annotations)
	: CLAttributeInfo(attribute_name_index, attribute_length), num_parameters(num_parameters), parameter_annotations(parameter_annotations)
{}

void CLRuntimeInvisibleParameterAnnotationsAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	out.write_byte(num_parameters);
	for (int i = 0; i < parameter_annotations.size(); i++) {
		parameter_annotations.at(i).write(out);
	}
}

CLAnnotationDefaultAttribute::CLAnnotationDefaultAttribute(int attribute_name_index, long long attribute_length, CLElementValue default_value)
	: CLAttributeInfo(attribute_name_index, attribute_length), default_value(default_value) {}

void CLAnnotationDefaultAttribute::write(CLOutputStream& out){
	CLAttributeInfo::write(out);
	default_value.write(out);
}
