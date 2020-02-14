#pragma once
#include "CLFile.h"
#include "CLInstruction.h"
#include "jmm_utils.h"
#include <stack>
#include <unordered_map>
#include <iostream>

class CLException;

class CLEmitter {
public:
	CLEmitter(bool to_file);
	void destination_dir(std::string dest_dir);
	bool has_error_occurred();
	void add_class(std::vector<std::string> access_flags, std::string this_class, std::string super_class, std::optional<std::vector<std::string>> super_interfaces, bool is_synthetic);
	void add_inner_class(std::vector<std::string> access_flags, std::string inner_class, std:: string outer_class, std::string inner_name);
	void add_field(std::vector<std::string> access_flags, std::string name, std::string type, bool is_synthetic);
	void add_field(std::vector<std::string> access_flags, std::string name, std::string type, bool is_synthetic, int i);
	void add_field(std::vector<std::string> access_flags, std::string name, bool is_synthetic, float f);
	void add_field(std::vector<std::string> access_flags, std::string name, bool is_synthetic, long long l);
	void add_field(std::vector<std::string> access_flags, std::string name, bool is_synthetic, double d);
	void add_field(std::vector<std::string> access_flags, std::string name, bool is_synthetic, std::string s);
	void add_method(std::vector<std::string> access_flags, std::string name, std::string descriptor, std::optional<std::vector<std::string>> exceptions, bool is_synthetic);
	void add_exception_handler(std::string start_label, std::string end_label, std::string handler_label, std::string catch_type);
	void add_no_arg_instruction(int opcode);
	void add_one_arg_instruction(int opcode, int arg);
	void add_IINC_instruction(int index, int const_val);
	void add_member_access_instruction(int opcode, std::string target, std::string name, std::string type);
	void add_reference_instruction(int opcode, std::string type);
	void add_array_instruction(int opcode, std::string type);
	void add_MULTIANEWARRAY_instruction(std::string type, int dim);
	void add_branch_instruction(int opcode, std::string label);
	void add_TABLESWITCH_instruction(std::string default_label, int low, int high, std::vector<std::string> labels);
	void add_LOOKUPSWITCH_instruction(std::string default_label, int num_pairs, std::map<int, std::string> match_label_pairs);
	void add_LDC_instruction(int i);
	void add_LDC_instruction(float f);
	void add_LDC_instruction(long long l);
	void add_LDC_instruction(double d);
	void add_LDC_instruction(std::string s);
	void add_class_attribute(std::unique_ptr<CLAttributeInfo> &&attribute); 
	void add_method_attribute(std::unique_ptr<CLAttributeInfo> &&attribute);
	void add_field_attribute(std::unique_ptr<CLAttributeInfo> &&attribute);
	void add_code_attribute(std::unique_ptr<CLAttributeInfo> &&attribute);
	void add_label(std::string label);
	std::string create_label();
	int get_pc();
	CLConstantPool& get_constant_pool();
	static void initialize_byte_class_loader();
	CLFile& get_cl_file();
	void write();


private:
	std::string name;
	bool to_file;
	std::wstring dest_dir;
	CLFile cl_file;
	CLConstantPool constant_pool;
	std::vector<int> interfaces;
	std::vector<CLFieldInfo> fields;
	std::vector<std::unique_ptr<CLAttributeInfo>> f_attributes;
	std::vector<CLMethodInfo> methods;
	std::vector<std::unique_ptr<CLAttributeInfo>> m_attributes;
	std::vector<std::unique_ptr<CLAttributeInfo>> attributes;
	std::vector<CLInnerClassInfo> inner_classes;
	std::vector<std::unique_ptr<CLInstruction>> m_code;
	std::vector<CLException> m_exception_handlers;
	int m_access_flags;
	int m_name_index;
	int m_descriptor_index;
	int m_argument_count;
	std::vector<std::unique_ptr<CLAttributeInfo>> m_code_attributes;
	bool is_method_open;
	std::unordered_map<std::string, int> m_labels;
	int m_label_count;
	bool m_instruction_after_label;
	int m_pc;
	std::string e_current_method;
	bool error_has_occurred;
	
	void initialize_method_variables();
	void end_open_method_if_any();
	void add_field_info(std::vector<std::string> access_flags, std::string name, std::string type, bool is_synthetic, int c);
	int type_stack_residue(std::string descriptor);
	int method_stack_residue(std::string descriptor);
	int argument_count(std::string descriptor);
	bool valid_internal_form(std::string name);
	bool valid_type_descriptor(std::string descriptor);
	bool valid_method_descriptor(std::string descriptor);
	CLInstruction* instruction(int pc);
	CLInstruction* instruction(int pc, int& index);
	int instruction_index(int pc);
	int stack_depth();
	void ldc_instruction(int index);
	void ldc2w_instruction(int index);
	CLConstantValueAttribute constant_value_attribute(int c);
	CLCodeAttribute code_attribute(std::vector<int> byte_code, std::vector<CLExceptionInfo> exception_table, int stack_depth_i, int max_locals);
	CLExceptionsAttribute exceptions_attribute(std::vector<std::string> exceptions);
	CLInnerClassesAttribute inner_classes_attribute();
	CLSyntheticAttribute synthetic_attribute();
	void report_opcode_error(int opcode);
	template<class... Args>
	void report_emitter_error(Args... args) {
		(std::cerr << ... << args) << "\n";
		error_has_occurred = true;
	}
};

class CLException {
public:
	std::string start_label;
	std::string end_label;
	std::string handler_label;
	std::string catch_type;
	int start_pc;
	int end_pc;
	int handler_pc;
	CLException(std::string start_label, std::string end_label, std::string handler_label, std::string catch_type);
	bool resolve_labels(std::map<std::string, int> label_to_pc);
private:
};

class CLBranchStack {
public:
	CLBranchStack();
	void push(int target_index, int stack_depth);
	std::optional<std::pair<int, int>> pop();
private:
	std::stack<std::pair<int, int>> branch_targets;
	std::map<int, int> visited_targets;
	std::pair<int, int>	 visit(int target_index, int stack_depth);
	bool visited(int target_index);
};

 