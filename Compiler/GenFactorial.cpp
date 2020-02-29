#include "CLEmitter.h"
#include <iostream>
#include <vector>
#include "JMMLogger.h"

int main() {
	logger::threshold_level() = LOG_DEBUG;
	//logger::log<LOG_DEBUG>("%s %s", "this is ", "a test.");
	CLEmitter e(true);
	std::vector<std::string> access_flags;
	access_flags.push_back("public");
	e.add_class(access_flags, "Factorial", "java/lang/Object", std::nullopt, true);

	access_flags.clear();
	access_flags.push_back("public");
	e.add_method(access_flags, "<init>", "()V", std::nullopt, true);
	e.add_no_arg_instruction(CLConstants::ALOAD_0);
	e.add_member_access_instruction(CLConstants::INVOKESPECIAL, "java/lang/Object", "<init>", "()V");
	e.add_no_arg_instruction(CLConstants::RETURN);
	access_flags.clear();
	access_flags.push_back("public");
	e.add_method(access_flags, "compute", "(I)I", std::nullopt, true);
	e.add_no_arg_instruction(CLConstants::ILOAD_1);
	e.add_no_arg_instruction(CLConstants::ICONST_1);
	e.add_branch_instruction(CLConstants::IF_ICMPGT, "false_label");
	e.add_no_arg_instruction(CLConstants::ILOAD_1);
	e.add_no_arg_instruction(CLConstants::IRETURN);
	e.add_label("false_label");
	e.add_no_arg_instruction(CLConstants::ILOAD_1);
	e.add_no_arg_instruction(CLConstants::ALOAD_0);
	e.add_no_arg_instruction(CLConstants::ILOAD_1);
	e.add_no_arg_instruction(CLConstants::ICONST_1);
	e.add_no_arg_instruction(CLConstants::ISUB);
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "Factorial", "compute", "(I)I");
	e.add_no_arg_instruction(CLConstants::IMUL);
	e.add_no_arg_instruction(CLConstants::IRETURN);

	access_flags.clear();
	access_flags.push_back("public");
	access_flags.push_back("static");
	e.add_method(access_flags, "main", "([Ljava/lang/String;)V", std::nullopt, true);
	e.add_exception_handler("try_start", "try_end", "catch", "java/lang/NumberFormatException");
	e.add_label("try_start");
	e.add_reference_instruction(CLConstants::NEW, "Factorial");
	e.add_no_arg_instruction(CLConstants::DUP);
	e.add_member_access_instruction(CLConstants::INVOKESPECIAL, "Factorial", "<init>", "()V");
	e.add_no_arg_instruction(CLConstants::ASTORE_1);
	e.add_no_arg_instruction(CLConstants::ALOAD_0);
	e.add_no_arg_instruction(CLConstants::ICONST_0);
	e.add_no_arg_instruction(CLConstants::AALOAD);
	e.add_member_access_instruction(CLConstants::INVOKESTATIC, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I");
	e.add_no_arg_instruction(CLConstants::ISTORE_2);
	e.add_member_access_instruction(CLConstants::GETSTATIC, "java/lang/System", "out", "Ljava/io/PrintStream;");
	e.add_reference_instruction(CLConstants::NEW, "java/lang/StringBuffer");
	e.add_no_arg_instruction(CLConstants::DUP);
	e.add_member_access_instruction(CLConstants::INVOKESPECIAL, "java/lang/StringBuffer", "<init>", "()V");
	e.add_LDC_instruction("Factorial(");
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/lang/StringBuffer", "append", "(Ljava/lang/String;)Ljava/lang/StringBuffer;");
	e.add_no_arg_instruction(CLConstants::ILOAD_2);
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/lang/StringBuffer", "append", "(I)Ljava/lang/StringBuffer;");
	e.add_LDC_instruction(") = ");
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/lang/StringBuffer", "append", "(Ljava/lang/String;)Ljava/lang/StringBuffer;");
	e.add_no_arg_instruction(CLConstants::ALOAD_1);
	e.add_no_arg_instruction(CLConstants::ALOAD_2);
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "Factorial", "compute", "(I)I");
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/lang/StringBuffer", "append", "(I)Ljava/lang/StringBuffer;");
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/lang/StringBuffer", "toString", "()Ljava/lang/String;");
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/io/PrintStream", "println", "(Ljava/lang/String;)V");
	e.add_label("try_end");
	e.add_branch_instruction(CLConstants::GOTO, "done");
	e.add_label("catch");
	e.add_no_arg_instruction(CLConstants::ASTORE_1);
	e.add_member_access_instruction(CLConstants::GETSTATIC, "java/lang/System", "err", "Ljava/io/PrintStream;");
	e.add_reference_instruction(CLConstants::NEW, "java/lang/StringBuffer");
	e.add_no_arg_instruction(CLConstants::DUP);
	e.add_member_access_instruction(CLConstants::INVOKESPECIAL, "java/lang/StringBuffer", "<init>", "()V");
	e.add_LDC_instruction("Invalid number ");
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/lang/StringBuffer", "append", "(Ljava/lang/String;)Ljava/lang/StringBuffer;");
	e.add_no_arg_instruction(CLConstants::ALOAD_0);
	e.add_no_arg_instruction(CLConstants::ICONST_0);
	e.add_no_arg_instruction(CLConstants::AALOAD);
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/lang/StringBuffer", "append", "(Ljava/lang/String;)Ljava/lang/StringBuffer;");
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/lang/StringBuffer", "toString", "()Ljava/lang/String;");
	e.add_member_access_instruction(CLConstants::INVOKEVIRTUAL, "java/io/PrintStream", "println", "(Ljava/lang/String;)V");
	e.add_label("done");
	e.add_no_arg_instruction(CLConstants::RETURN);
	e.write();
}