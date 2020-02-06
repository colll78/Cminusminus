#pragma once
#include "CLConstants.h"
#include <string>
#include <array>
#include <vector>
#include <map>

class CLInsInfo;

class CLInstruction {
public:
	static const std::array<CLInsInfo, 202> instruction_info;
	static bool is_valid(int opcode);
	int get_opcode();
	std::string get_mnemonic();
	int get_operand_count();
	int get_pc();
	int get_stack_units();
	int get_local_variable_index();
	/* Returns the bytecode for this instruction */
	virtual std::vector<int> to_bytes();
private:

protected:
	int opcode;
	std::string mnemonic;
	int operand_count;
	int pc;
	int stack_units;
	int local_variable_index;
	int byte_at(int i, int byte_num);
};

class CLObjectInstruction : public CLInstruction {
public:
	CLObjectInstruction(int opcode, int pc, int index);
	std::vector<int> to_bytes();
private:
	int index;
};

class CLFieldInstruction : public CLInstruction {
public:
	CLFieldInstruction(int opcode, int pc, int index, int stack_units);
	std::vector<int> to_bytes();
private:
	int index;
};

class CLMethodInstruction : public CLInstruction {
public:
	CLMethodInstruction(int opcode, int pc, int index, int stack_units);
	CLMethodInstruction(int opcode, int pc);
	void set_argument_count(int n_args);
	std::vector<int> to_bytes();
private:
	int index;
	int n_args;
};

class CLArrayInstruction : public CLInstruction {
public:
	CLArrayInstruction(int opcode, int pc, int type);
	CLArrayInstruction(int opcode, int pc, int type, int dim);
	CLArrayInstruction(int opcode, int pc);
	std::vector<int> to_bytes();
private:
	int type;
	int dim;
};

class CLArithmeticInstruction : public CLInstruction {
public:
	CLArithmeticInstruction(int opcode, int pc);
	CLArithmeticInstruction(int opcode, int pc, int local_variable_index, int const_val, bool is_widened);
	std::vector<int> to_bytes();
private:
	bool is_widened;
	int const_val;
};

class CLBitInstruction : public CLInstruction {
public:
	CLBitInstruction(int opcode, int pc);
	std::vector<int> to_bytes();
private:
};

class CLComparisonInstruction : public CLInstruction {
public:
	CLComparisonInstruction(int opcode, int pc);
	std::vector<int> to_bytes();
private:
};

class CLConversionInstruction : public CLInstruction {
public:
	CLConversionInstruction(int opcode, int pc);
	std::vector<int> to_bytes();
private:
};

class CLFlowControlInstruction : public CLInstruction {
public:
	CLFlowControlInstruction(int opcode, int pc, std::string jump_to_label);
	CLFlowControlInstruction(int pc, int index, bool is_widened);
	CLFlowControlInstruction(int opcode, int pc, std::string default_label, int low, int high, std::vector<std::string> labels);
	CLFlowControlInstruction(int opcode, int pc, std::string default_label, int num_pairs, std::map<int, std::string> match_label_pairs);
	/**
	 * Resolves the jump labels to the corresponding offset values using the
	 * given label to pc mapping. If unable to resolve a label, the offset is
	 * set such that the next instruction will be executed.
	 */
	bool resolve_labels(std::map<std::string, int> label_to_pc);
	/**
	* Returns the pc of instruction to jump to.
	* @return pc to jump to.
	*/
	int get_jump_offset();

	std::vector<int> to_bytes();
private:
	std::string jump_to_label;
	int jump_to_offset;
	int index;
	bool is_widened;
	int pad;
	std::string default_label;
	int default_offset;
	int num_pairs;
	/* Key and label pairs for LOOKUPSWITCH instruction */
	std::map<int, std::string> match_label_pairs;
	/* Key and offset table for LOOKUPSWITCH instruction */
	std::map<int, int> match_offset_pairs;
	/* Smallest value of index for TABLESWITCH instruction */
	int low;
	/* Highest value of index for TABLESWITCH instruction */
	int high;
	/* 
	* List of jump labels for TABLESWITCH instruction for each value 
	* from low to high, end values included.
	*/
	std::vector<std::string> labels;
	/* List of offsets for TABLESWITCH instruction */
	std::vector<int> offsets;
};

class CLLoadStoreInstruction : public CLInstruction {
public:
	CLLoadStoreInstruction(int opcode, int pc);
	CLLoadStoreInstruction(int opcode, int pc, int local_variable_index, bool is_widened);
	CLLoadStoreInstruction(int opcode, int pc, int const_val);
	std::vector<int> to_bytes();
private:
	bool is_widened;
	int const_val;
};

class CLStackInstruction : public CLInstruction {
public:
	CLStackInstruction(int opcode, int pc);
	std::vector<int> to_bytes();
};

class CLMiscInstruction : public CLInstruction {
public:
	CLMiscInstruction(int opcode, int pc);
	std::vector<int> to_bytes();
private:
};

class CLInsInfo {
public:
	int opcode;
	std::string mnemonic;
	int operand_count;
	int stack_units;
	int local_variable_index;
	CLConstants::Category category;
	CLInsInfo(int opcode, std::string mnemonic, int operand_count, int local_variable_index, int stack_units, CLConstants::Category category);
private:
};