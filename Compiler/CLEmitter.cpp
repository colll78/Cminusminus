#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "CLEmitter.h"
#include <filesystem>
#include <locale>
#include <codecvt>
#include <iostream>
#include "JMMLogger.h"


CLException::CLException(std::string start_label, std::string end_label, std::string handler_label, std::string catch_type)
: start_label(start_label), end_label(end_label), handler_label(handler_label), catch_type(catch_type) {}

bool CLException::resolve_labels(std::unordered_map<std::string, int> label_to_pc){
	bool all_labels_resolved = true;
	if (label_to_pc.count(start_label)) {
		start_pc = label_to_pc[start_label];
	}
	else {
		start_pc = 0;
		all_labels_resolved = false;
	}
	if (label_to_pc.count(end_label)) {
		end_pc = label_to_pc[end_label];
	}
	else {
		end_pc = 0;
		all_labels_resolved = false;
	}
	if (label_to_pc.count(handler_label)) {
		handler_pc = label_to_pc[handler_label];
	}
	else {
		handler_pc = 0;
		all_labels_resolved = false;
	}
	return all_labels_resolved;
}



CLBranchStack::CLBranchStack(){}

void CLBranchStack::push(int target_index, int stack_depth){
	if (visited(target_index)) {
		return;
	}
	branch_targets.push(visit(target_index, stack_depth));
}

std::optional<std::pair<int, int>> CLBranchStack::pop(){
	if (!branch_targets.empty()) {
		std::pair<int , int> bt =  branch_targets.top();
		branch_targets.pop();
		return bt;
	}
	return std::nullopt;
}

std::pair<int, int> CLBranchStack::visit(int target_index, int stack_depth){
	std::pair<int, int> bt = { target_index, stack_depth };
	visited_targets[target_index] = stack_depth;
	return bt;
}

bool CLBranchStack::visited(int target_index){
	return visited_targets.count(target_index) > 0;
}

void CLEmitter::initialize_method_variables(){
	m_access_flags = 0;
	m_name_index = -1;
	m_descriptor_index = -1;
	m_argument_count = 0;
	m_pc = 0;

	m_attributes.clear();
	m_exception_handlers.clear();
	m_code.clear();
	m_code_attributes.clear();
	m_labels.clear();
	
	m_label_count = 1;
	m_instruction_after_label = true;
}

void CLEmitter::end_open_method_if_any(){
	if (is_method_open) {
		is_method_open = false;
		if (!m_instruction_after_label) {
			add_no_arg_instruction(CLConstants::NOP);
		}
		std::vector<CLExceptionInfo> exception_table;
		for (int i = 0; i < m_exception_handlers.size(); i++) {
			CLException e = m_exception_handlers.at(i);
			if (!e.resolve_labels(m_labels)) {
				report_emitter_error(e_current_method, ": unable to resolve exception handler labels");
			}
			int catch_type_index = (e.catch_type == "" ? 0 : constant_pool.constant_class_info(e.catch_type));
			CLExceptionInfo c(e.start_pc, e.end_pc, e.handler_pc, catch_type_index);
			exception_table.push_back(c);
		}
		std::vector<int> byte_code;
		int max_locals = m_argument_count;
		for (int i = 0; i < m_code.size(); i++) {
			CLInstruction* instr = m_code.at(i).get();
			int local_variable_index = instr->get_local_variable_index();
			switch (instr->get_opcode()) {
			case CLConstants::LLOAD:
			case CLConstants::LSTORE:
			case CLConstants::DSTORE:
			case CLConstants::DLOAD:
			case CLConstants::LLOAD_0:
			case CLConstants::LLOAD_1:
			case CLConstants::LLOAD_2:
			case CLConstants::LLOAD_3:
			case CLConstants::LSTORE_0:
			case CLConstants::LSTORE_1:
			case CLConstants::LSTORE_2:
			case CLConstants::LSTORE_3:
			case CLConstants::DLOAD_0:
			case CLConstants::DLOAD_1:
			case CLConstants::DLOAD_2:
			case CLConstants::DLOAD_3:
			case CLConstants::DSTORE_0:
			case CLConstants::DSTORE_1:
			case CLConstants::DSTORE_2:
			case CLConstants::DSTORE_3:
				local_variable_index++;
			}
			max_locals = std::max(max_locals, local_variable_index + 1);

			if (typeid(instr) == typeid(CLFlowControlInstruction)) {
				if (CLFlowControlInstruction* b = dynamic_cast<CLFlowControlInstruction*>(instr)) {
					if (b->resolve_labels(m_labels)) {
						report_emitter_error(e_current_method, ": Unable to resolve jump labels");
					}
				}
			}
			std::vector<int> instr_bytes = instr->to_bytes();
			byte_code.insert(byte_code.end(), instr_bytes.begin(), instr_bytes.end());
		}

		if (!((m_access_flags & CLConstants::ACC_NATIVE) == CLConstants::ACC_NATIVE || (m_access_flags & CLConstants::ACC_ABSTRACT) == CLConstants::ACC_ABSTRACT)) {
			std::unique_ptr<CLAttributeInfo> code_attri = std::make_unique<CLCodeAttribute>(code_attribute(byte_code, exception_table, stack_depth(), max_locals));
			add_method_attribute(std::move(code_attri));
		}

		//CLMethodInfo(mAccessFlags, mNameIndex, mDescriptorIndex, mAttributes.size(), mAttributes))
		CLMethodInfo m_info(m_access_flags, m_name_index, m_descriptor_index, m_attributes.size(), m_attributes);
		methods.push_back(m_info);
	}
	
	if (!inner_classes.empty()) {
		std::unique_ptr<CLAttributeInfo> class_attri = std::make_unique<CLInnerClassesAttribute>(inner_classes_attribute());
		add_class_attribute(std::move(class_attri));
	}
	cl_file.constant_pool_count = constant_pool.size() + 1;
	cl_file.constant_pool = constant_pool;
	cl_file.interfaces_count = interfaces.size();
	cl_file.interfaces = interfaces;
	cl_file.fields_count = fields.size();
	cl_file.fields = fields;
	cl_file.methods_count = methods.size();
	cl_file.methods = methods;
	cl_file.attributes_count = attributes.size();
	cl_file.attributes = &attributes;
	 
}

void CLEmitter::add_field_info(std::vector<std::string> access_flags, std::string name, std::string type, bool is_synthetic, int c){
	if (!valid_type_descriptor(type)) {
		report_emitter_error(type, " is not a valid type descriptor for field");
	}
	int flags = 0;
	int name_index = constant_pool.constant_UTF8_info(name);
	int descriptor_index = constant_pool.constant_UTF8_info(type);
	f_attributes.clear();
	if (!access_flags.empty()) {
		for (int i = 0; i < access_flags.size(); i++) {
			flags |= CLFile::access_flag_to_int(access_flags.at(i));
		}
	}
	if (is_synthetic) {
		add_field_attribute(std::make_unique<CLSyntheticAttribute>(synthetic_attribute()));
	}
	if (c != -1) {
		add_field_attribute(std::make_unique<CLConstantValueAttribute>(constant_value_attribute(c)));
	}
	fields.push_back(CLFieldInfo(flags, name_index, descriptor_index, f_attributes.size(), f_attributes));
}

int CLEmitter::type_stack_residue(std::string descriptor){
	int i = 0;
	char c = descriptor.at(0);
	switch (c) {
	case 'B':
	case 'C':
	case 'I':
	case 'F':
	case 'L':
	case 'S':
	case 'Z':
	case '[':
		i = 1;
		break;
	case 'J':
	case 'D':
		i = 2;
		break;
	}
	return i;
}

int CLEmitter::method_stack_residue(std::string descriptor){
	int i = 0;
	std::string::size_type rparen_index = descriptor.find_last_of(")");
	if (rparen_index == std::string::npos) {
		report_emitter_error(descriptor, " is not a valid method descriptor.");
	}
	std::string arg_types = descriptor.substr(1, rparen_index);
	std::string return_type = descriptor.substr(rparen_index + 1);
	for (int j = 0; j < arg_types.size(); j++) {
		char c = arg_types.at(j);
		switch(c){
		case 'B':
		case 'C':
		case 'I':
		case 'F':
		case 'S':
		case 'Z':
			i -= 1;
			break;
		case '[':
			break;
		case 'J':
		case 'D':
			i -= 2;
			break;
		case 'L':
			std::string::size_type k = arg_types.find(';', j);
			j = k;
			i -= 1;
			break;
		}
	}
	i += type_stack_residue(return_type);
	return i;
}

int CLEmitter::argument_count(std::string descriptor){
	int i = 0;
	std::string::size_type rparen_index = descriptor.find_last_of(")");
	if (rparen_index == std::string::npos) {
		report_emitter_error(descriptor, " is not a valid method descriptor.");
	}
	std::string arg_types = descriptor.substr(1, rparen_index - 1);
	for (int j = 0; j < arg_types.size(); j++) {
		char c = arg_types.at(j);
		switch (c) {
		case 'B':
		case 'C':
		case 'I':
		case 'F':
		case 'S':
		case 'Z':
			i += 1;
			break;
		case '[':
			break;
		case 'J':
		case 'D':
			i += 2;
			break;
		case 'L':
			std::string::size_type k = arg_types.find(';', j);
			j = k;
			i++;
			break;
		}
	}
	return i;
}

bool CLEmitter::valid_internal_form(std::string name) {
	if ((name == "") || (name[0] == '/') || (name[name.size() - 1] == '\\')) {
		return false;
	}
	std::vector<std::string> tokens;
	jmm_string_utils::split(tokens, name, jmm_string_utils::is_any_of<std::string>("/"));
	for (std::string& s : tokens) {
		if (!jmm_java_utils::is_java_identifier_start(s[0])) {
			return false;
		}
		for (int i = 1; i < s.size(); i++) {
			if (!jmm_java_utils::is_java_identifier_part(s[i])) {
				return false;
			}
		}
	}
	return true;
}

bool CLEmitter::valid_type_descriptor(std::string descriptor){
	if (!descriptor.empty()) {
		switch (descriptor[0]) {
		case 'B':
		case 'C':
		case 'I':
		case 'F':
		case 'S':
		case 'Z':
		case 'J':
		case 'D':
			return (descriptor.size() == 1);
		case 'L':
			if (descriptor.back() == ';') {
				return valid_internal_form(descriptor.substr(1, descriptor.size() - 2));
			}
			return false;
		case '[':
			if (descriptor.size() > 1) {  
				return valid_type_descriptor(descriptor.substr(1));
			}
			return false;
		}
	}
	return false;
}

bool CLEmitter::valid_method_descriptor(std::string descriptor){
	if (!descriptor.empty()) {
		std::string::size_type cparen_pos = descriptor.find_last_of(')');
		if (cparen_pos != std::string::npos && ((cparen_pos + 1) != std::string::npos)) {
			std::string arg_types = descriptor.substr(1, cparen_pos - 1);
			std::string return_type = descriptor.substr(cparen_pos + 1);
			//logger::log<LOG_DEBUG>("Arg Types: %s\nReturn Type: %s\n", arg_types.c_str(), return_type.c_str());
			for (int i = 0; i < arg_types.size(); i++) {
				char c = arg_types[i];
				switch (c) {
				case 'B':
				case 'C':
				case 'I':
				case 'F':
				case 'S':
				case 'Z':
				case 'J':
				case 'D':
				case '[':
					break;
				case 'L':
				{
					std::string::size_type semi_pos = descriptor.find(';', i);
					if (semi_pos != std::string::npos) {
						std::string s = arg_types.substr(i, semi_pos + 1);
						i = semi_pos;
						if (!valid_type_descriptor(s)) {
							return false;
						}
					}
					break;
				}
				default:
					return false;
				}
			}
			return (return_type == "V" || valid_type_descriptor(return_type));

		}
	}
	return false;
}

CLInstruction* CLEmitter::instruction(int pc){
	for (int j = 0; j < m_code.size(); j++) {
		CLInstruction* i = m_code.at(j).get();
		if (i->get_pc() == pc) {
			return i;
		}
	}
	return nullptr;
}

CLInstruction* CLEmitter::instruction(int pc, int& index){
	int j;
	for (j = 0; j < m_code.size(); j++) {
		CLInstruction* i = m_code.at(j).get();
		if (i->get_pc() == pc) {
			index = j;
			return i;
		}
	}
	index = j;
	return nullptr;
}

int CLEmitter::instruction_index(int pc){
	int j = 0;
	for (; j < m_code.size(); j++) {
		CLInstruction* i = m_code.at(j).get();
		if (i->get_pc() == pc) {
			return j;
		}
	}
	return j;
}

int CLEmitter::stack_depth(){
	CLBranchStack branch_targets;
	int h_index = 0;
	for (int i = 0; i < m_exception_handlers.size(); i++) {
		CLException e = m_exception_handlers.at(i);
		CLInstruction* h = instruction(e.handler_pc, h_index);
		if (h != nullptr) {
			branch_targets.push(h_index, 1);
		}
	}
	int stack_depth_i = 0, max_stack_depth = 0, c = 0;
	CLInstruction* instr = m_code.empty() ? nullptr : m_code.at(c).get();
	while (instr != nullptr) {
		int opcode = instr->get_opcode();
		int stack_units = instr->get_stack_units();
		int instr_index = -1;
		if (stack_units == CLConstants::EMPTY_STACK) {
			stack_depth_i = 0;
		}
		else if (stack_units == CLConstants::UNIT_SIZE_STACK) {
			stack_depth_i = 1;
		}
		else {
			stack_depth_i += stack_units;
		}
		if (stack_depth_i >= max_stack_depth) {
			max_stack_depth = stack_depth_i;
		}
		if (CLFlowControlInstruction* b = dynamic_cast<CLFlowControlInstruction*>(instr)) {
			int jump_to_index = b->get_opcode() + b->get_jump_offset();
			CLInstruction* instr_at = nullptr;
			switch (opcode) {
			case CLConstants::JSR:
			case CLConstants::JSR_W:
			case CLConstants::RET:
				instr = nullptr;
				break;
			case CLConstants::GOTO:
			case CLConstants::GOTO_W:
				instr = nullptr;
			default:
				instr_at = instruction(jump_to_index, instr_index);
				if (instr_at != nullptr) {
					branch_targets.push(instr_index, stack_depth_i);
				}
			} 
		}
		else {
			if ((opcode == CLConstants::ATHROW) || (opcode >= CLConstants::IRETURN) || (opcode <= CLConstants::RETURN)){
				instr = nullptr;
			}
		}
		if (instr != nullptr) {
			instr = (++c >= m_code.size()) ? nullptr : m_code.at(c).get();
		}
		if (instr == nullptr){
			std::optional<std::pair<int, int>> bt = branch_targets.pop();
			if (bt != std::nullopt) {
				instr = m_code.at(bt->first).get();
				stack_depth_i = bt->second;
				c = bt->first;
			}

		}
	}
	return max_stack_depth;
}

void CLEmitter::ldc_instruction(int index){
	std::unique_ptr<CLLoadStoreInstruction> instr;
	if (index < 255) {
		instr = std::make_unique<CLLoadStoreInstruction>(CLConstants::LDC, m_pc++, index);
	} else {
		instr = std::make_unique<CLLoadStoreInstruction>(CLConstants::LDC_W, m_pc++, index);
	}
	m_pc += instr->get_operand_count();
	m_code.push_back(std::move(instr));
	m_instruction_after_label = true;
}

void CLEmitter::ldc2w_instruction(int index){
	std::unique_ptr<CLLoadStoreInstruction> instr;
	instr = std::make_unique<CLLoadStoreInstruction>(CLConstants::LDC2_W, m_pc++, index);
	m_pc += instr->get_operand_count();
	m_code.push_back(std::move(instr));
	m_instruction_after_label = true;
}

CLConstantValueAttribute CLEmitter::constant_value_attribute(int c){
	int attribute_name_index = constant_pool.constant_UTF8_info(CLConstants::ATT_CONSTANT_VALUE);
	return CLConstantValueAttribute(attribute_name_index, 2, c);
}

CLCodeAttribute CLEmitter::code_attribute(std::vector<int> byte_code, std::vector<CLExceptionInfo> exception_table, int stack_depth_i, int max_locals){
	int code_length = byte_code.size();
	int attribute_name_index = constant_pool.constant_UTF8_info(CLConstants::ATT_CODE);
	int attribute_length = code_length + 8 * exception_table.size() + 12;
	for (int i = 0; i < m_code_attributes.size(); i++) {
		attribute_length += 6 + m_code_attributes[i]->attribute_length;
	}
	return CLCodeAttribute(attribute_name_index, attribute_length, stack_depth_i, max_locals, (long long) code_length, byte_code, 
		exception_table.size(), exception_table, m_code_attributes.size(), m_code_attributes);
}

CLExceptionsAttribute CLEmitter::exceptions_attribute(std::vector<std::string> exceptions){
	int attribute_name_index = constant_pool.constant_UTF8_info(CLConstants::ATT_EXCEPTIONS);
	std::vector<int> exception_index_table;
	for (int i = 0; i < exceptions.size(); i++) {
		std::string e = exceptions.at(i);
		exception_index_table.push_back(constant_pool.constant_class_info(e));
	}
	return CLExceptionsAttribute(attribute_name_index, exception_index_table.size() * 2 + 2, exception_index_table.size(), exception_index_table);
}

CLInnerClassesAttribute CLEmitter::inner_classes_attribute(){
	int attribute_name_index = constant_pool.constant_UTF8_info(CLConstants::ATT_INNER_CLASSES);
	long long attribute_length = inner_classes.size() * 8 + 2;
	return CLInnerClassesAttribute(attribute_name_index, attribute_length, inner_classes.size(), inner_classes);

}

CLSyntheticAttribute CLEmitter::synthetic_attribute(){
	int attribute_name_index = constant_pool.constant_UTF8_info(CLConstants::ATT_SYNTHETIC);
	return CLSyntheticAttribute(attribute_name_index, 0);
}

/*
CLCodeAttribute CLEmitter::code_attribute(std::vector<int> byte_code, std::vector<CLExceptionInfo> exception_table, int stack_depth_i, int max_locals){
	int code_length = byte_code.size();
	int attribute_name_index = constant_pool.constant_UTF8_info(CLConstants::ATT_CODE);
	int attribute_length = code_length + 8 * exception_table.size() + 12;
	for (size_t i = 0; i < m_code_attributes.size(); i++){
		attribute_length += 6 + m_code_attributes.at(i)->attribute_length;
	}
	// to do 
}*/

void CLEmitter::report_opcode_error(int opcode){
	if (CLInstruction::is_valid(opcode)) {
		report_emitter_error(e_current_method, ": Invalid opcode '", opcode, "'");
	}
	else {
		report_emitter_error(e_current_method, ": Incorrect method used to add instruction '", CLInstruction::instruction_info[opcode].mnemonic, "'");
	}
}

CLEmitter::CLEmitter(bool to_file) : to_file(to_file){
	dest_dir = L".";
}

void CLEmitter::destination_dir(std::string dest_dir){
	CLEmitter::dest_dir = std::wstring(dest_dir.begin(), dest_dir.end());
}

bool CLEmitter::has_error_occurred(){
	return error_has_occurred;
}

void CLEmitter::add_class(std::vector<std::string> access_flags, std::string this_class, std::string super_class, std::optional<std::vector<std::string>> super_interfaces, bool is_synthetic){
	cl_file = CLFile();
	constant_pool = CLConstantPool();
	interfaces.clear();
	fields.clear();
	methods.clear();
	attributes.clear();
	inner_classes.clear();

	error_has_occurred = false;
	cl_file.magic = CLConstants::MAGIC;
	cl_file.major_version = CLConstants::MAJOR_VERSION;
	cl_file.minor_version = CLConstants::MINOR_VERSION;
	if (!valid_internal_form(this_class)) {
		report_emitter_error(this_class, " is not in internal form");
	}
	if (!valid_internal_form(super_class)) {
		report_emitter_error(super_class, " is not in internal form");
	}
	for (int i = 0; i < access_flags.size(); i++) {
		cl_file.access_flags |= CLFile::access_flag_to_int(access_flags.at(i));
	}
	name = this_class;
	cl_file.this_class = constant_pool.constant_class_info(this_class);
	cl_file.this_class = constant_pool.constant_class_info(super_class);
	for (int i = 0; super_interfaces && i < (*super_interfaces).size(); i++) {
		if (!valid_internal_form((*super_interfaces).at(i))) {
			report_emitter_error((*super_interfaces).at(i), " is not in internal form.");
		}
		interfaces.push_back(constant_pool.constant_class_info((*super_interfaces).at(i)));
	}
	if (is_synthetic){
		add_class_attribute(std::make_unique<CLSyntheticAttribute>(synthetic_attribute()));
	}
}

void CLEmitter::add_inner_class(std::vector<std::string> access_flags, std::string inner_class, std::string outer_class, std::string inner_name){
	int flags = 0;
	for (int j = 0; j < access_flags.size(); j++) {
		flags |= CLFile::access_flag_to_int(access_flags.at(j));
	}
	CLInnerClassInfo inner_class_info(constant_pool.constant_class_info(inner_class), constant_pool.constant_class_info(outer_class), constant_pool.constant_UTF8_info(inner_name), flags);
	inner_classes.push_back(inner_class_info);
}

void CLEmitter::add_field(std::vector<std::string> access_flags, std::string name, std::string type, bool is_synthetic){
	add_field_info(access_flags, name, type, is_synthetic, -1);
}

void CLEmitter::add_field(std::vector<std::string> access_flags, std::string name, std::string type, bool is_synthetic, int i){
	add_field_info(access_flags, name, type, is_synthetic, constant_pool.constant_integer_info(i));
}

void CLEmitter::add_field(std::vector<std::string> access_flags, std::string name, bool is_synthetic, float f){
	add_field_info(access_flags, name, "F", is_synthetic, constant_pool.constant_float_info(f));
}

void CLEmitter::add_field(std::vector<std::string> access_flags, std::string name, bool is_synthetic, long long l){
	add_field_info(access_flags, name, "J", is_synthetic, constant_pool.constant_long_info(l));
}

void CLEmitter::add_field(std::vector<std::string> access_flags, std::string name, bool is_synthetic, double d){
	add_field_info(access_flags, name, "D", is_synthetic, constant_pool.constant_double_info(d));
}

void CLEmitter::add_field(std::vector<std::string> access_flags, std::string name, bool is_synthetic, std::string s){
	add_field_info(access_flags, name, "Ljava/lang/String;", is_synthetic, constant_pool.constant_string_info(s));
}

void CLEmitter::add_method(std::vector<std::string> access_flags, std::string name, std::string descriptor, std::optional<std::vector<std::string>> exceptions, bool is_synthetic){
	if (!valid_method_descriptor(descriptor)) {
		report_emitter_error(descriptor, " is not a valid type descriptor for method");
	}
	end_open_method_if_any();
	is_method_open = true;
	initialize_method_variables();
	e_current_method = name + descriptor;
	if (!access_flags.empty()) {
		for (int i = 0; i < access_flags.size(); i++) {
			m_access_flags |= CLFile::access_flag_to_int(access_flags.at(i));
		}
	}
	m_argument_count = argument_count(descriptor) + (std::find(access_flags.begin(), access_flags.end(), "static") != access_flags.end()) ? 0 : 1;
	m_name_index = constant_pool.constant_UTF8_info(name);
	m_descriptor_index = constant_pool.constant_UTF8_info(descriptor);
	if (exceptions) {
		CLExceptionsAttribute except_attri = exceptions_attribute(*exceptions);
		m_attributes.push_back(std::make_unique<CLExceptionsAttribute>(except_attri));
	}
	if (is_synthetic) {
		CLSyntheticAttribute synth_attri = synthetic_attribute();
		m_attributes.push_back(std::make_unique<CLSyntheticAttribute>(synth_attri));
	}
	
}

void CLEmitter::add_exception_handler(std::string start_label, std::string end_label, std::string handler_label, std::string catch_type){
	if (!catch_type.empty() && !valid_internal_form(catch_type)) {
		report_emitter_error(catch_type, " is not in internal form");
	}
	CLException e(start_label, end_label, handler_label, catch_type);
	m_exception_handlers.push_back(e);
}

void CLEmitter::add_no_arg_instruction(int opcode){
	std::unique_ptr<CLInstruction> instr; 
	switch (CLInstruction::instruction_info[opcode].category) {
	case CLConstants::ARITHMETIC1:
		instr = std::make_unique<CLArithmeticInstruction>(opcode, m_pc++); 
		break;
	case CLConstants::ARRAY2:
		instr = std::make_unique<CLArrayInstruction>(opcode, m_pc++);
		break;
	case CLConstants::BIT:
		instr = std::make_unique<CLBitInstruction>(opcode, m_pc++);
		break;
	case CLConstants::COMPARISON:
		instr = std::make_unique<CLComparisonInstruction>(opcode, m_pc++);
		break;
	case CLConstants::CONVERSION:
		instr = std::make_unique<CLConversionInstruction>(opcode, m_pc++);
		break;
	case CLConstants::LOAD_STORE1:
		instr = std::make_unique<CLLoadStoreInstruction>(opcode, m_pc++);
		break;
	case CLConstants::METHOD2:
		instr = std::make_unique<CLMethodInstruction>(opcode, m_pc++);
		break;
	case CLConstants::MISC:
		instr = std::make_unique<CLMiscInstruction>(opcode, m_pc++);
		break;
	case CLConstants::STACK:
		instr = std::make_unique<CLStackInstruction>(opcode, m_pc++);
		break;
	default:
		report_opcode_error(opcode);
		return;
	}
	m_pc += instr.get()->get_operand_count();
	m_code.push_back(std::move(instr));
	m_instruction_after_label = true;
}

void CLEmitter::add_one_arg_instruction(int opcode, int arg){
	std::unique_ptr<CLInstruction> instr = nullptr;
	bool is_widened = false;
	switch (CLInstruction::instruction_info[opcode].category) {
	case CLConstants::LOAD_STORE2:
		is_widened = arg > 255;
		if (is_widened) {
			m_code.push_back(std::make_unique<CLLoadStoreInstruction>(CLConstants::WIDE, m_pc++));
		}
		instr = std::make_unique<CLLoadStoreInstruction>(opcode, m_pc++, arg, is_widened);
		break;
	case CLConstants::LOAD_STORE3:
		instr = std::make_unique<CLLoadStoreInstruction>(opcode, m_pc++, arg);
		break;
	case CLConstants::FLOW_CONTROL2:
		is_widened = arg > 255;
		if (is_widened) {
			m_code.push_back(std::make_unique<CLLoadStoreInstruction>(CLConstants::WIDE, m_pc++));
		}
		instr = std::make_unique<CLFlowControlInstruction>(m_pc++, arg, is_widened);
		break;
	default:
		report_opcode_error(opcode);
	}
	if (instr != nullptr) {
		m_pc += instr.get()->get_opcode();
		m_code.push_back(std::move(instr));
		m_instruction_after_label = true;
	}
}

void CLEmitter::add_IINC_instruction(int index, int const_val){
	bool is_widened = index > 255 || const_val < -128 || const_val > 128;
	if (is_widened) {
		m_code.push_back(std::make_unique<CLLoadStoreInstruction>(CLConstants::WIDE, m_pc++));
	}
	std::unique_ptr<CLInstruction> instr = std::make_unique<CLArithmeticInstruction>(CLConstants::IINC, m_pc++, index, const_val, is_widened);
	m_pc += instr.get()->get_operand_count();
	m_code.push_back(std::move(instr));
	m_instruction_after_label = true;

}

void CLEmitter::add_member_access_instruction(int opcode, std::string target, std::string name, std::string type){
	if (!valid_internal_form(target)) {
		report_emitter_error(e_current_method, ": ", target, " is not in internal form");
	}
	std::unique_ptr<CLInstruction> instr = nullptr;
	int index, stack_units;
	switch (CLInstruction::instruction_info[opcode].category) {
	case CLConstants::FIELD:
		if (!valid_type_descriptor(type)) {
			report_emitter_error(e_current_method, ": ", type, " is not a valid type descriptor for field.");
		}
		index = constant_pool.constant_field_ref_info(target, name, type);
		stack_units = type_stack_residue(type);
		if ((opcode == CLConstants::GETFIELD) || (opcode == CLConstants::PUTFIELD)) {
			stack_units--;
		}
		instr = std::make_unique<CLFieldInstruction>(opcode, m_pc++, index, stack_units);
		break;
	case CLConstants::METHOD1:
		if (!valid_method_descriptor(type)) {
			report_emitter_error(e_current_method, ": ", type, " is not a valid type descriptor for method");
		}
		if (opcode == CLConstants::INVOKEINTERFACE) {
			index = constant_pool.constant_interface_method_ref_info(target, name, type);
		}
		else {
			index = constant_pool.constant_method_ref_info(target, name, type);
		}
		stack_units = method_stack_residue(type);
		if (opcode != CLConstants::INVOKESTATIC) {
			stack_units--;
		}
		instr = std::make_unique<CLMethodInstruction>(opcode, m_pc++, index, stack_units);

		if (opcode == CLConstants::INVOKEINTERFACE) {
			CLMethodInstruction* b = dynamic_cast<CLMethodInstruction*>(instr.get());
			b->set_argument_count(argument_count(type) + 1);
		}
		break;
	default:
		report_opcode_error(opcode);
	}
	if (instr == nullptr) {
		m_pc += instr.get()->get_operand_count();
		m_code.push_back(std::move(instr));
	}
}

void CLEmitter::add_reference_instruction(int opcode, std::string type){
	if (!valid_type_descriptor(type) && !valid_internal_form(type)) {
		report_emitter_error(e_current_method, ": ", type, " is neither a type descriptor nor in internal form");
	}
	std::unique_ptr<CLInstruction> instr = nullptr;
	switch (CLInstruction::instruction_info[opcode].category) {
	case CLConstants::OBJECT:
	{
		int index = constant_pool.constant_class_info(type);
		instr = std::make_unique<CLObjectInstruction>(opcode, m_pc++, index);
		break;
	} 
	default:
		report_opcode_error(opcode);
	}
	if (instr != nullptr) {
		m_pc += instr.get()->get_operand_count();
		m_code.push_back(std::move(instr));
	}
}

void CLEmitter::add_array_instruction(int opcode, std::string type){
	std::unique_ptr<CLInstruction> instr = nullptr;
	switch (CLInstruction::instruction_info[opcode].category) {
	case CLConstants::ARRAY1:
		int index = 0;
		if (opcode == CLConstants::NEWARRAY) {
			if (jmm_string_utils::iequals(type, "Z")) {
				index = 4;
			}
			else if (jmm_string_utils::iequals(type, "C")) {
				index = 5;
			}
			else if (jmm_string_utils::iequals(type, "F")) {
				index = 6;
			}
			else if (jmm_string_utils::iequals(type, "D")) {
				index = 7;
			}
			else if (jmm_string_utils::iequals(type, "B")) {
				index = 8;
			}
			else if (jmm_string_utils::iequals(type, "S")) {
				index = 9;
			}
			else if (jmm_string_utils::iequals(type, "I")) {
				index = 10;
			}
			else if (jmm_string_utils::iequals(type, "J")) {
				index = 11;
			}
			else {
				report_emitter_error(e_current_method, ": ", type, " is not a valid primitive type.");
			}
		}
		else {
			if (!valid_type_descriptor(type) && !valid_internal_form(type)) {
				report_emitter_error(e_current_method, ": ", type, " is not a valid type descriptor for an array.");
			}
			index = constant_pool.constant_class_info(type);
		}
		if (instr != nullptr) {
			m_pc += instr.get()->get_operand_count();
			m_code.push_back(std::move(instr));
		}
	}
}

void CLEmitter::add_MULTIANEWARRAY_instruction(std::string type, int dim){
	std::unique_ptr<CLInstruction> instr = nullptr;
	if (!valid_type_descriptor(type)) {
		report_emitter_error(e_current_method, ": ", type, " is not a valid type descriptor for an array.");
	}
	int index = constant_pool.constant_class_info(type);
	instr = std::make_unique<CLArrayInstruction>(CLConstants::MULTIANEWARRAY, m_pc++, index, dim);
	if (instr != nullptr) {
		m_pc += instr.get()->get_operand_count();
		m_code.push_back(std::move(instr));
	}
}

void CLEmitter::add_branch_instruction(int opcode, std::string label){
	std::unique_ptr<CLInstruction> instr = nullptr;
	switch (CLInstruction::instruction_info[opcode].category) {
	case CLConstants::FLOW_CONTROL1:
		instr = std::make_unique<CLFlowControlInstruction>(opcode, m_pc++, label);
		break;
	default:
		report_opcode_error(opcode);
	}
	if (instr != nullptr) {
		m_pc += instr.get()->get_operand_count();
		m_code.push_back(std::move(instr));
		m_instruction_after_label = true;
	}
}

void CLEmitter::add_TABLESWITCH_instruction(std::string default_label, int low, int high, std::vector<std::string> labels){
	std::unique_ptr<CLInstruction> instr = std::make_unique<CLFlowControlInstruction>(CLConstants::TABLESWITCH, m_pc++, default_label, low, high, labels);
	m_pc += instr.get()->get_operand_count();
	m_code.push_back(std::move(instr));
	m_instruction_after_label = true;
}

void CLEmitter::add_LOOKUPSWITCH_instruction(std::string default_label, int num_pairs, std::map<int, std::string> match_label_pairs){
	std::unique_ptr<CLInstruction> instr = std::make_unique<CLFlowControlInstruction>(CLConstants::LOOKUPSWITCH, m_pc++, default_label, num_pairs, match_label_pairs);
	m_pc += instr.get()->get_operand_count();
	m_code.push_back(std::move(instr));
	m_instruction_after_label = true;
}

void CLEmitter::add_LDC_instruction(int i){
	ldc_instruction(constant_pool.constant_integer_info(i));
}

void CLEmitter::add_LDC_instruction(float f){
	ldc_instruction(constant_pool.constant_float_info(f));
}

void CLEmitter::add_LDC_instruction(long long l){
	ldc_instruction(constant_pool.constant_long_info(l));
}

void CLEmitter::add_LDC_instruction(double d){
	ldc_instruction(constant_pool.constant_double_info(d));
}

void CLEmitter::add_LDC_instruction(std::string s){
	ldc_instruction(constant_pool.constant_string_info(s));
}

void CLEmitter::add_class_attribute(std::unique_ptr<CLAttributeInfo> &&attribute){
	attributes.push_back(std::move(attribute));
}

void CLEmitter::add_method_attribute(std::unique_ptr<CLAttributeInfo> &&attribute){
	m_attributes.push_back(std::move(attribute));
}

void CLEmitter::add_field_attribute(std::unique_ptr<CLAttributeInfo> &&attribute){
	f_attributes.push_back(std::move(attribute));
}

void CLEmitter::add_code_attribute(std::unique_ptr<CLAttributeInfo> &&attribute){
	m_code_attributes.push_back(std::move(attribute));
}

void CLEmitter::add_label(std::string label){
	m_labels[label] = m_pc;
	m_instruction_after_label = false;
}

std::string CLEmitter::create_label(){
	return "Label" + m_label_count++;
}

int CLEmitter::get_pc(){
	return m_pc;
}

CLConstantPool& CLEmitter::get_constant_pool(){
	return constant_pool;
}

CLFile& CLEmitter::get_cl_file(){
	return cl_file;
}

void CLEmitter::write(){
	end_open_method_if_any();
	if (!to_file) {
		logger::log<LOG_DEBUG>("Not to file.");
		return;
	}
	logger::log<LOG_DEBUG>("Output file name: %s", name.c_str());
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide_name = converter.from_bytes(name);
	dest_dir = L"";
	std::wstring outfile = dest_dir + std::filesystem::path::preferred_separator + wide_name + L".class";
	std::wcout << outfile << L"\n";
	CLOutputStream out(outfile);
	
	cl_file.write(out);
	out.flush_buffer();
	out.close();
}





