#include "CLEmitter.h"

CLException::CLException(std::string start_label, std::string end_label, std::string handler_label, std::string catch_type)
: start_label(start_label), end_label(end_label), handler_label(handler_label), catch_type(catch_type) {}

bool CLException::resolve_labels(std::map<std::string, int> label_to_pc){
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

		}
	}
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
	//fields.push_back()
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
	if (descriptor != "") {
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
	if (descriptor.size() > 0) {
		std::string::size_type cparen_pos = descriptor.find_last_of(')');
		if (cparen_pos != std::string::npos && ((cparen_pos + 1) != std::string::npos)) {
			std::string arg_types = descriptor.substr(1, cparen_pos);
			std::string return_type = descriptor.substr(cparen_pos + 1);
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

void CLEmitter::add_class(std::vector<std::string> access_flags, std::string this_class, std::string super_class, std::vector<std::string> super_interfaces, bool is_synthetic){
	error_has_occurred = false;
	cl_file.magic = CLConstants::MAGIC;
	cl_file.major_version = CLConstants::MAJOR_VERSION;
	cl_file.minor_version = CLConstants::MINOR_VERSION;
	if (!valid_internal_form(this_class)) {

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

void CLEmitter::add_method(std::vector<std::string> access_flags, std::string name, std::string descriptor, std::vector<std::string> exceptions, bool is_synthetic){
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
	if (!exceptions.empty()) {
		CLExceptionsAttribute except_attri = exceptions_attribute(exceptions);
		m_attributes.push_back(std::make_unique<CLExceptionsAttribute>(except_attri));
	}
	if (is_synthetic) {
		CLSyntheticAttribute synth_attri = synthetic_attribute();
		m_attributes.push_back(std::make_unique<CLSyntheticAttribute>(synth_attri));
	}
	
}

void CLEmitter::add_exception_handler(std::string start_label, std::string end_label, std::string handler_label, std::string catch_type)
{
}

void CLEmitter::add_no_arg_instruction(int opcode)
{
}

void CLEmitter::add_one_arg_instruction(int opcode, int arg)
{
}

void CLEmitter::add_IINC_instruction(int index, int const_val)
{
}

void CLEmitter::add_member_access_instruction(int opcode, std::string target, std::string name, std::string type)
{
}

void CLEmitter::add_reference_instruction(int opcode, std::string type)
{
}

void CLEmitter::add_array_instruction(int opcode, std::string type)
{
}

void CLEmitter::add_MULTIANEWARRAY_instruction(std::string type, int dim)
{
}

void CLEmitter::add_branch_instruction(int opcode, std::string label)
{
}

void CLEmitter::add_TABLESWITCH_instruction(std::string default_label, int low, int high, std::vector<std::string> labels)
{
}

void CLEmitter::add_LDC_instruction(int i)
{
}

void CLEmitter::add_LDC_instruction(float f)
{
}

void CLEmitter::add_LDC_instruction(long long l)
{
}

void CLEmitter::add_LDC_instruction(double d)
{
}

void CLEmitter::add_LDC_instruction(std::string s)
{
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


