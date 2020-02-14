#pragma once
#include "CLOutputStream.h"
#include <memory>

class CLAttributeInfo {
public:
	int attribute_name_index;
	long long attribute_length;
	CLAttributeInfo(int attribute_name_index, long long attribute_length);
	virtual void write(CLOutputStream& out);
};

class CLConstantValueAttribute : public CLAttributeInfo {
public:
	int constant_value_index;
	CLConstantValueAttribute(int attribute_name_index, long long attribute_length, int constant_value_index);
	void write(CLOutputStream& out);
private:
};

class CLExceptionInfo {
public: 
	int start_pc;
	int end_pc;
	int handler_pc;
	int catch_type;
	CLExceptionInfo(int start_pc, int end_pc, int handler_pc, int catch_type);
	void write(CLOutputStream& out);
};

class CLCodeAttribute : public CLAttributeInfo {
public:
	int max_stack;
	int max_locals;
	long long code_length;
	std::vector<int> code;
	int exception_table_length;
	std::vector<CLExceptionInfo> exception_table;
	int attributes_count;
	std::vector<std::unique_ptr<CLAttributeInfo>> &attributes;
	CLCodeAttribute(int attribute_name_index, long long attribute_length, int max_stack, int max_locals, long long code_length, std::vector<int> code,
		int exception_table_length, std::vector<CLExceptionInfo> exception_table, int attributes_count, std::vector<std::unique_ptr<CLAttributeInfo>> &attributes);
	void write(CLOutputStream& out);
private:
	int int_value(int a, int b, int c, int d);
};

class CLExceptionsAttribute : public CLAttributeInfo {
public:
	int number_of_exceptions;
	std::vector<int> exception_index_table;
	CLExceptionsAttribute(int attribute_name_index, long long attribute_length, int number_of_exceptions, std::vector<int> exception_index_table);
	void write(CLOutputStream &out);
};

class CLInnerClassInfo {
public:
	int inner_class_info_index;
	int outer_class_info_index;
	int inner_name_index;
	int inner_class_access_flags;
	CLInnerClassInfo(int inner_class_info_index, int outer_class_info_index, int inner_name_index, int inner_class__access_flags);
	void write(CLOutputStream& out);
private:
};

class CLInnerClassesAttribute : public CLAttributeInfo {
public:
	int number_of_classes;
	std::vector<CLInnerClassInfo> classes;
	CLInnerClassesAttribute(int attribute_name_index, long long attribute_length, int number_of_classes, std::vector<CLInnerClassInfo> classes);
	void write(CLOutputStream& out);
};

class CLEnclosingMethodAttribute : public CLAttributeInfo {
public:
	int class_index;
	int method_index;
	CLEnclosingMethodAttribute(int attribute_name_index, long long attribute_length, int class_index, int method_index);
	void write(CLOutputStream& out);
};

class CLSyntheticAttribute : public CLAttributeInfo {
public:
	CLSyntheticAttribute(int attribute_name_index, long long attribute_length);
	void write(CLOutputStream& out);
private:
};

class CLSignatureAttribute : public CLAttributeInfo {
public:
	int signature_index;
	CLSignatureAttribute(int attribute_name_index, long long attribute_length, int signature_index);
	void write(CLOutputStream& out);
private:
};

class CLSourceFileAttribute : public CLAttributeInfo {
public:
	int source_file_index;
	CLSourceFileAttribute(int attribute_name_index, long long attribute_length, int source_file_index);
	void write(CLOutputStream& out);
private:
};

class CLSourceDebugExtensionAttribute : public CLAttributeInfo {
public:
	std::vector<std::byte> debug_extension;
	CLSourceDebugExtensionAttribute(int attribute_name_index, long long attribute_length, std::vector<std::byte> debug_extension);
	void write(CLOutputStream& out);
};

class CLLineNumberInfo {
public:
	int start_pc;
	int line_number;
	CLLineNumberInfo(int start_pc, int line_number);
	void write(CLOutputStream& out);
	bool equals(CLLineNumberInfo obj);
private:
};

class CLLineNumberTableAttribute : public CLAttributeInfo {
public:
	int line_number_table_length;
	std::vector<CLLineNumberInfo> line_number_table;
	CLLineNumberTableAttribute(int attribute_name_index, long long attribute_length, int line_number_table_length, std::vector<CLLineNumberInfo> line_number_table);
	void write(CLOutputStream& out);
private:
};

class CLLocalVariableInfo {
public:
	int start_pc;
	int length;
	int name_index;
	int descriptor_index;
	int index;
	CLLocalVariableInfo(int start_pc, int length, int name_index, int descriptor_index, int index);
	void write(CLOutputStream& out);
private:
};

class CLLocalVariableTableAttribute : public CLAttributeInfo {
public:
	int local_variable_table_length;
	std::vector<CLLocalVariableInfo> local_variable_table;
	CLLocalVariableTableAttribute(int attribute_name_index, long long attribute_length, int local_variable_table_length, std::vector<CLLocalVariableInfo> local_variable_table);
	void write(CLOutputStream& out);
private:
};

class CLLocalVariableTypeInfo {
public:
	int start_pc;
	int length;
	int name_index;
	int signature_index;
	int index;
	CLLocalVariableTypeInfo(int start_pc, int length, int name_index, int signature_index, int index);
	void write(CLOutputStream& out);
private:
};

class CLLocalVariableTypeTableAttribute : public CLAttributeInfo {
public:
	int local_variable_type_table_length;
	std::vector<CLLocalVariableTypeInfo> local_variable_type_table;
	CLLocalVariableTypeTableAttribute(int attribute_name_index, long long attribute_length, int local_variable_type_table_length, std::vector<CLLocalVariableTypeInfo> local_variable_type_table);
	void write(CLOutputStream& out);
private:
};

class CLDeprecatedAttribute : public CLAttributeInfo {
public:
	CLDeprecatedAttribute(int attribute_name_index, long long attribute_length);
	void write(CLOutputStream& out);
private:
};

class CLElementValuePair;

class CLAnnotation {
public:
	int type_index;
	int num_element_value_pairs;
	std::vector<CLElementValuePair> element_value_pairs; 
	CLAnnotation();
	CLAnnotation(int type_index, int num_element_value_pairs, std::vector<CLElementValuePair> element_value_pairs);
	void write(CLOutputStream& out);
private:
};

class CLElementValue {
public:
	short tag;
	int const_value_index;
	int type_name_index;
	int const_name_index;
	int class_info_index;
	CLAnnotation annotation_value;
	int num_values;
	std::vector<CLElementValue> values;
	CLElementValue(short tag, int const_value_index);
	CLElementValue(int type_name_index, int const_name_index);
	CLElementValue(int class_info_index);
	CLElementValue(CLAnnotation annotation_value);
	CLElementValue(int num_values, std::vector<CLElementValue> values);
	void write(CLOutputStream& out);
private:
};

class CLElementValuePair {
public:
	int element_name_index;
	CLElementValue value;
	CLElementValuePair(int element_name_index, CLElementValue value);
	void write(CLOutputStream& out);
};


class CLRuntimeVisibleAnnotationsAttribute : public CLAttributeInfo {
public:
	int num_annotations;
	std::vector<CLAnnotation> annotations;
	CLRuntimeVisibleAnnotationsAttribute(int attribute_name_index, long long attribute_length, int num_annotations, std::vector<CLAnnotation> annotations);
	void write(CLOutputStream& out);
};

class CLRuntimeInvisibleAnnotationsAttribute : public CLAttributeInfo {
public:
	int num_annotations;
	std::vector<CLAnnotation> annotations;
	CLRuntimeInvisibleAnnotationsAttribute(int attribute_name_index, long long attribute_length, int num_annotations, std::vector<CLAnnotation> annotations);
	void write(CLOutputStream& out);
};

class CLParameterAnnotationInfo {
public:
	int num_annotations;
	std::vector<CLAnnotation> annotations;
	CLParameterAnnotationInfo(int num_annotations, std::vector<CLAnnotation> annotations);
	void write(CLOutputStream& out);
};

class CLRuntimeVisibleParameterAnnotationsAttribute : public CLAttributeInfo {
	short num_parameters;
	std::vector<CLParameterAnnotationInfo> parameter_annotations;
	CLRuntimeVisibleParameterAnnotationsAttribute(int attribute_name_index, long long attribute_length, short num_parameters, std::vector<CLParameterAnnotationInfo> parameter_annotations);
	void write(CLOutputStream& out);
};

class CLRuntimeInvisibleParameterAnnotationsAttribute : public CLAttributeInfo {
	short num_parameters;
	std::vector<CLParameterAnnotationInfo> parameter_annotations;
	CLRuntimeInvisibleParameterAnnotationsAttribute(int attribute_name_index, long long attribute_length, short num_parameters, std::vector<CLParameterAnnotationInfo> parameter_annotations);
	void write(CLOutputStream& out);
};

class CLAnnotationDefaultAttribute : public CLAttributeInfo {
public:
	CLElementValue default_value;
	CLAnnotationDefaultAttribute(int attribute_name_index, long long attribute_length, CLElementValue default_value);
	void write(CLOutputStream& out);
};