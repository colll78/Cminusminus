#include <set>
#include "CLInstruction.h"


const std::array<CLInsInfo, 202> CLInstruction::instruction_info = {
	CLInsInfo(CLConstants::NOP, "nop", 0, CLConstants::IRRELEVANT, 0, CLConstants::MISC),
	CLInsInfo(CLConstants::ACONST_NULL, "aconst_null", 0, CLConstants::IRRELEVANT, 1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ICONST_M1,  "iconst_m1",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ICONST_0,  "iconst_0",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ICONST_1,  "iconst_1",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ICONST_2,  "iconst_2",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ICONST_3,  "iconst_3",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ICONST_4,  "iconst_4",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ICONST_5,  "iconst_5",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LCONST_0,  "lconst_0",  0, CLConstants::IRRELEVANT,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LCONST_1,  "lconst_1",  0, CLConstants::IRRELEVANT,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FCONST_0,  "fconst_0",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FCONST_1,  "fconst_1",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FCONST_2,  "fconst_2",  0, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DCONST_0,  "dconst_0",  0, CLConstants::IRRELEVANT,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DCONST_1,  "dconst_1",  0, CLConstants::IRRELEVANT,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::BIPUSH,  "bipush",  1, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE3),
    CLInsInfo(CLConstants::SIPUSH,  "sipush",  2, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE3),
    CLInsInfo(CLConstants::LDC,  "ldc",  1, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE4),
    CLInsInfo(CLConstants::LDC_W,  "ldc_w",  2, CLConstants::IRRELEVANT,  1, CLConstants::LOAD_STORE4),
    CLInsInfo(CLConstants::LDC2_W,  "ldc2_w",  2, CLConstants::IRRELEVANT,  2, CLConstants::LOAD_STORE4),
    CLInsInfo(CLConstants::ILOAD,  "iload",  1, CLConstants::DYNAMIC,  1, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::LLOAD,  "lload",  1, CLConstants::DYNAMIC,  2, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::FLOAD,  "fload",  1, CLConstants::DYNAMIC,  1, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::DLOAD,  "dload",  1, CLConstants::DYNAMIC,  2, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::ALOAD,  "aload",  1, CLConstants::DYNAMIC,  1, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::ILOAD_0,  "iload_0",  0,  0,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ILOAD_1,  "iload_1",  0,  1,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ILOAD_2,  "iload_2",  0,  2,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ILOAD_3,  "iload_3",  0,  3,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LLOAD_0,  "lload_0",  0,  0,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LLOAD_1,  "lload_1",  0,  1,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LLOAD_2,  "lload_2",  0,  2,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LLOAD_3,  "lload_3",  0,  3,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FLOAD_0,  "fload_0",  0,  0,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FLOAD_1,  "fload_1",  0,  1,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FLOAD_2,  "fload_2",  0,  2,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FLOAD_3,  "fload_3",  0,  3,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DLOAD_0,  "dload_0",  0,  0,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DLOAD_1,  "dload_1",  0,  1,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DLOAD_2,  "dload_2",  0,  2,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DLOAD_3,  "dload_3",  0,  3,  2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ALOAD_0,  "aload_0",  0,  0,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ALOAD_1,  "aload_1",  0,  1,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ALOAD_2,  "aload_2",  0,  2,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ALOAD_3,  "aload_3",  0,  3,  1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::IALOAD,  "iaload",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::LALOAD,  "laload",  0, CLConstants::IRRELEVANT,  0, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::FALOAD,  "faload",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::DALOAD,  "daload",  0, CLConstants::IRRELEVANT,  0, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::AALOAD,  "aaload",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::BALOAD,  "baload",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::CALOAD,  "caload",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::SALOAD,  "saload",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::ISTORE,  "istore",  1, CLConstants::DYNAMIC,  -1, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::LSTORE,  "lstore",  1, CLConstants::DYNAMIC,  -2, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::FSTORE,  "fstore",  1, CLConstants::DYNAMIC,  -1, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::DSTORE,  "dstore",  1, CLConstants::DYNAMIC,  -2, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::ASTORE,  "astore",  1, CLConstants::DYNAMIC,  -1, CLConstants::LOAD_STORE2),
    CLInsInfo(CLConstants::ISTORE_0,  "istore_0",  0,  0,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ISTORE_1,  "istore_1",  0,  1,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ISTORE_2,  "istore_2",  0,  2,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ISTORE_3,  "istore_3",  0,  3,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LSTORE_0,  "lstore_0",  0,  0,  -2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LSTORE_1,  "lstore_1",  0,  1,  -2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LSTORE_2,  "lstore_2",  0,  2,  -2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::LSTORE_3,  "lstore_3",  0,  3,  -2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FSTORE_0,  "fstore_0",  0,  0,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FSTORE_1,  "fstore_1",  0,  1,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FSTORE_2,  "fstore_2",  0,  2,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::FSTORE_3,  "fstore_3",  0,  3,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DSTORE_0,  "dstore_0",  0,  0,  -2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DSTORE_1,  "dstore_1",  0,  1,  -2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DSTORE_2,  "dstore_2",  0,  2,  -2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::DSTORE_3,  "dstore_3",  0,  3,  -2, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ASTORE_0,  "astore_0",  0,  0,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ASTORE_1,  "astore_1",  0,  1,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ASTORE_2,  "astore_2",  0,  2,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::ASTORE_3,  "astore_3",  0,  3,  -1, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::IASTORE,  "iastore",  0, CLConstants::IRRELEVANT,  -3, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::LASTORE,  "lastore",  0, CLConstants::IRRELEVANT,  -4, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::FASTORE,  "fastore",  0, CLConstants::IRRELEVANT,  -3, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::DASTORE,  "dastore",  0, CLConstants::IRRELEVANT,  -4, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::AASTORE,  "aastore",  0, CLConstants::IRRELEVANT,  -3, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::BASTORE,  "bastore",  0, CLConstants::IRRELEVANT,  -3, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::CASTORE,  "castore",  0, CLConstants::IRRELEVANT,  -3, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::SASTORE,  "sastore",  0, CLConstants::IRRELEVANT,  -3, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::POP,  "pop",  0, CLConstants::IRRELEVANT,  -1, CLConstants::STACK),
    CLInsInfo(CLConstants::POP2,  "pop2",  0, CLConstants::IRRELEVANT,  -2, CLConstants::STACK),
    CLInsInfo(CLConstants::DUP,  "dup",  0, CLConstants::IRRELEVANT,  1, CLConstants::STACK),
    CLInsInfo(CLConstants::DUP_X1,  "dup_x1",  0, CLConstants::IRRELEVANT,  1, CLConstants::STACK),
    CLInsInfo(CLConstants::DUP_X2,  "dup_x2",  0, CLConstants::IRRELEVANT,  1, CLConstants::STACK),
    CLInsInfo(CLConstants::DUP2,  "dup2",  0, CLConstants::IRRELEVANT,  2, CLConstants::STACK),
    CLInsInfo(CLConstants::DUP2_X1,  "dup2_x1",  0, CLConstants::IRRELEVANT,  2, CLConstants::STACK),
    CLInsInfo(CLConstants::DUP2_X2,  "dup2_x2",  0, CLConstants::IRRELEVANT,  2, CLConstants::STACK),
    CLInsInfo(CLConstants::SWAP,  "swap",  0, CLConstants::IRRELEVANT,  0, CLConstants::STACK),
    CLInsInfo(CLConstants::IADD,  "iadd",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::LADD,  "ladd",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::FADD,  "fadd",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::DADD,  "dadd",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::ISUB,  "isub",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::LSUB,  "lsub",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::FSUB,  "fsub",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::DSUB,  "dsub",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::IMUL,  "imul",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::LMUL,  "lmul",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::FMUL,  "fmul",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::DMUL,  "dmul",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::IDIV,  "idiv",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::LDIV,  "ldiv",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::FDIV,  "fdiv",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::DDIV,  "ddiv",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::IREM,  "irem",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::LREM,  "lrem",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::FREM,  "frem",  0, CLConstants::IRRELEVANT,  -1, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::DREM,  "drem",  0, CLConstants::IRRELEVANT,  -2, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::INEG,  "ineg",  0, CLConstants::IRRELEVANT,  0, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::LNEG,  "lneg",  0, CLConstants::IRRELEVANT,  0, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::FNEG,  "fneg",  0, CLConstants::IRRELEVANT,  0, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::DNEG,  "dneg",  0, CLConstants::IRRELEVANT,  0, CLConstants::ARITHMETIC1),
    CLInsInfo(CLConstants::ISHL,  "ishl",  0, CLConstants::IRRELEVANT,  -1, CLConstants::BIT),
    CLInsInfo(CLConstants::LSHL,  "lshl",  0, CLConstants::IRRELEVANT,  -2, CLConstants::BIT),
    CLInsInfo(CLConstants::ISHR,  "ishr",  0, CLConstants::IRRELEVANT,  -1, CLConstants::BIT),
    CLInsInfo(CLConstants::LSHR,  "lshr",  0, CLConstants::IRRELEVANT,  -2, CLConstants::BIT),
    CLInsInfo(CLConstants::IUSHR,  "iushr",  0, CLConstants::IRRELEVANT,  -1, CLConstants::BIT),
    CLInsInfo(CLConstants::LUSHR,  "lushr",  0, CLConstants::IRRELEVANT,  -2, CLConstants::BIT),
    CLInsInfo(CLConstants::IAND,  "iand",  0, CLConstants::IRRELEVANT,  -1, CLConstants::BIT),
    CLInsInfo(CLConstants::LAND,  "land",  0, CLConstants::IRRELEVANT,  -2, CLConstants::BIT),
    CLInsInfo(CLConstants::IOR,  "ior",  0, CLConstants::IRRELEVANT,  -1, CLConstants::BIT),
    CLInsInfo(CLConstants::LOR,  "lor",  0, CLConstants::IRRELEVANT,  -2, CLConstants::BIT),
    CLInsInfo(CLConstants::IXOR,  "ixor",  0, CLConstants::IRRELEVANT,  -1, CLConstants::BIT),
    CLInsInfo(CLConstants::LXOR,  "lxor",  0, CLConstants::IRRELEVANT,  -2, CLConstants::BIT),
    CLInsInfo(CLConstants::IINC,  "iinc",  2, CLConstants::DYNAMIC,  0, CLConstants::ARITHMETIC2),
    CLInsInfo(CLConstants::I2L,  "i2l",  0, CLConstants::IRRELEVANT,  1, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::I2F,  "i2f",  0, CLConstants::IRRELEVANT,  0, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::I2D,  "i2d",  0, CLConstants::IRRELEVANT,  1, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::L2I,  "l2i",  0, CLConstants::IRRELEVANT,  -1, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::L2F,  "l2f",  0, CLConstants::IRRELEVANT,  -1, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::L2D,  "l2d",  0, CLConstants::IRRELEVANT,  0, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::F2I,  "f2i",  0, CLConstants::IRRELEVANT,  0, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::F2L,  "f2l",  0, CLConstants::IRRELEVANT,  1, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::F2D,  "f2d",  0, CLConstants::IRRELEVANT,  1, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::D2I,  "d2i",  0, CLConstants::IRRELEVANT,  -1, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::D2L,  "d2l",  0, CLConstants::IRRELEVANT,  0, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::D2F,  "d2f",  0, CLConstants::IRRELEVANT,  -1, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::I2B,  "i2b",  0, CLConstants::IRRELEVANT,  0, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::I2C,  "i2c",  0, CLConstants::IRRELEVANT,  0, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::I2S,  "i2s",  0, CLConstants::IRRELEVANT,  0, CLConstants::CONVERSION),
    CLInsInfo(CLConstants::LCMP,  "lcmp",  0, CLConstants::IRRELEVANT,  -3, CLConstants::COMPARISON),
    CLInsInfo(CLConstants::FCMPL,  "fcmpl",  0, CLConstants::IRRELEVANT,  -1, CLConstants::COMPARISON),
    CLInsInfo(CLConstants::FCMPG,  "fcmpg",  0, CLConstants::IRRELEVANT,  -1, CLConstants::COMPARISON),
    CLInsInfo(CLConstants::DCMPL,  "dcmpl",  0, CLConstants::IRRELEVANT,  -3, CLConstants::COMPARISON),
    CLInsInfo(CLConstants::DCMPG,  "dcmpg",  0, CLConstants::IRRELEVANT,  -3, CLConstants::COMPARISON),
    CLInsInfo(CLConstants::IFEQ,  "ifeq",  2, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IFNE,  "ifne",  2, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IFLT,  "iflt",  2, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IFGE,  "ifge",  2, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IFGT,  "ifgt",  2, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IFLE,  "ifle",  2, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IF_ICMPEQ,  "if_icmpeq",  2, CLConstants::IRRELEVANT,  -2, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IF_ICMPNE,  "if_icmpne",  2, CLConstants::IRRELEVANT,  -2, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IF_ICMPLT,  "if_icmplt",  2, CLConstants::IRRELEVANT,  -2, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IF_ICMPGE,  "if_icmpge",  2, CLConstants::IRRELEVANT,  -2, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IF_ICMPGT,  "if_icmpgt",  2, CLConstants::IRRELEVANT,  -2, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IF_ICMPLE,  "if_icmple",  2, CLConstants::IRRELEVANT,  -2, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IF_ACMPEQ,  "if_acmpeq",  2, CLConstants::IRRELEVANT,  -2, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IF_ACMPNE,  "if_acmpne",  2, CLConstants::IRRELEVANT,  -2, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::GOTO,  "goto",  2, CLConstants::IRRELEVANT,  0, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::JSR,  "jsr",  2, CLConstants::IRRELEVANT,  1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::RET,  "ret",  1, CLConstants::IRRELEVANT,  0, CLConstants::FLOW_CONTROL2),
    CLInsInfo(CLConstants::TABLESWITCH,  "tableswitch",  CLConstants::DYNAMIC, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL3),
    CLInsInfo(CLConstants::LOOKUPSWITCH,  "lookupswitch",  CLConstants::DYNAMIC, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL4),
    CLInsInfo(CLConstants::IRETURN,  "ireturn",  0, CLConstants::IRRELEVANT, CLConstants::EMPTY_STACK, CLConstants::METHOD2),
    CLInsInfo(CLConstants::LRETURN,  "lreturn",  0, CLConstants::IRRELEVANT, CLConstants::EMPTY_STACK, CLConstants::METHOD2),
    CLInsInfo(CLConstants::FRETURN,  "freturn",  0, CLConstants::IRRELEVANT, CLConstants::EMPTY_STACK, CLConstants::METHOD2),
    CLInsInfo(CLConstants::DRETURN,  "dreturn",  0, CLConstants::IRRELEVANT, CLConstants::EMPTY_STACK, CLConstants::METHOD2),
    CLInsInfo(CLConstants::ARETURN,  "areturn",  0, CLConstants::IRRELEVANT, CLConstants::EMPTY_STACK, CLConstants::METHOD2),
    CLInsInfo(CLConstants::RETURN,  "return",  0, CLConstants::IRRELEVANT, CLConstants::EMPTY_STACK, CLConstants::METHOD2),
    CLInsInfo(CLConstants::GETSTATIC,  "getstatic",  2, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::FIELD),
    CLInsInfo(CLConstants::PUTSTATIC,  "putstatic",  2, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::FIELD),
    CLInsInfo(CLConstants::GETFIELD,  "getfield",  2, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::FIELD),
    CLInsInfo(CLConstants::PUTFIELD,  "putfield",  2, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::FIELD),
    CLInsInfo(CLConstants::INVOKEVIRTUAL,  "invokevirtual",  2, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::METHOD1),
    CLInsInfo(CLConstants::INVOKESPECIAL,  "invokespecial",  2, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::METHOD1),
    CLInsInfo(CLConstants::INVOKESTATIC,  "invokestatic",  2, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::METHOD1),
    CLInsInfo(CLConstants::INVOKEINTERFACE,  "invokeinterface",  4, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::METHOD1),
    CLInsInfo(CLConstants::INVOKEDYNAMIC,  "invokedynamic",  2, CLConstants::IRRELEVANT, CLConstants::DYNAMIC, CLConstants::METHOD1),
    CLInsInfo(CLConstants::NEW,  "new",  2, CLConstants::IRRELEVANT,  1, CLConstants::OBJECT),
    CLInsInfo(CLConstants::NEWARRAY,  "newarray",  1, CLConstants::IRRELEVANT,  0, CLConstants::ARRAY1),
    CLInsInfo(CLConstants::ANEWARRAY,  "anewarray",  2, CLConstants::IRRELEVANT,  0, CLConstants::ARRAY1),
    CLInsInfo(CLConstants::ARRAYLENGTH,  "arraylength",  0, CLConstants::IRRELEVANT,  0, CLConstants::ARRAY2),
    CLInsInfo(CLConstants::ATHROW,  "athrow",  0, CLConstants::IRRELEVANT, CLConstants::UNIT_SIZE_STACK, CLConstants::MISC),
    CLInsInfo(CLConstants::CHECKCAST,  "checkcast",  2, CLConstants::IRRELEVANT,  0, CLConstants::OBJECT),
    CLInsInfo(CLConstants::INSTANCEOF,  "instanceof",  2, CLConstants::IRRELEVANT,  0, CLConstants::OBJECT),
    CLInsInfo(CLConstants::MONITORENTER,  "monitorenter",  0, CLConstants::IRRELEVANT,  -1, CLConstants::MISC),
    CLInsInfo(CLConstants::MONITOREXIT,  "monitorexit",  0, CLConstants::IRRELEVANT,  -1, CLConstants::MISC),
    CLInsInfo(CLConstants::WIDE,  "wide",  3, CLConstants::IRRELEVANT,  0, CLConstants::LOAD_STORE1),
    CLInsInfo(CLConstants::MULTIANEWARRAY,  "multianewarray",  3, CLConstants::IRRELEVANT,  0, CLConstants::ARRAY3),
    CLInsInfo(CLConstants::IFNULL,  "ifnull",  2, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::IFNONNULL,  "ifnonnull",  2, CLConstants::IRRELEVANT,  -1, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::GOTO_W,  "goto_w",  4, CLConstants::IRRELEVANT,  0, CLConstants::FLOW_CONTROL1),
    CLInsInfo(CLConstants::JSR_W,  "jsr_w",  4, CLConstants::IRRELEVANT,  1, CLConstants::FLOW_CONTROL1)
};

bool CLInstruction::is_valid(int opcode){
	return CLConstants::NOP;
}

int CLInstruction::get_opcode(){
	return opcode;
}

std::string CLInstruction::get_mnemonic(){
	return mnemonic;
}

int CLInstruction::get_operand_count(){
	return operand_count;
}

int CLInstruction::get_pc(){
	return pc;
}

int CLInstruction::get_stack_units(){
	return stack_units;
}

int CLInstruction::get_local_variable_index(){
	return local_variable_index;
}

std::vector<int> CLInstruction::to_bytes(){
    return std::vector<int>();
}

int CLInstruction::byte_at(int i, int byte_num){
	int j = 0;
	switch (byte_num) {
	case 1:
		j = i & 0xFF;
		break;
	case 2:
		j = (i >> 8) & 0xFF;
		break;
	case 3:
		j = (i >> 16) & 0xFF;
		break;
	case 4:
		j = (i >> 24) & 0xFF;
		break;
	}
	return j;
}

CLObjectInstruction::CLObjectInstruction(int opcode, int pc, int index) : index(index) {
	CLInstruction::opcode = opcode;
	CLInstruction::pc = pc;
	CLInstruction::mnemonic = instruction_info[opcode].mnemonic;
}

std::vector<int> CLObjectInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    bytes.push_back(byte_at(index, 2));
    bytes.push_back(byte_at(index, 1));
    return bytes;
}

CLInsInfo::CLInsInfo(int opcode, std::string mnemonic, int operand_count, int local_variable_index, int stack_units, CLConstants::Category category)
    : opcode(opcode), mnemonic(mnemonic), operand_count(operand_count), local_variable_index(local_variable_index), stack_units(stack_units), category(category) {}

CLFieldInstruction::CLFieldInstruction(int opcode, int pc, int index, int stack_units){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    CLInstruction::stack_units = stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
    CLFieldInstruction::index = index;
}

std::vector<int> CLFieldInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    bytes.push_back(byte_at(index, 2));
    bytes.push_back(byte_at(index, 1));
    return bytes;
}

CLMethodInstruction::CLMethodInstruction(int opcode, int pc, int index, int stack_units) : index(index) {
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    CLInstruction::stack_units = stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

CLMethodInstruction::CLMethodInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

void CLMethodInstruction::set_argument_count(int n_args){
    CLMethodInstruction::n_args = n_args;
}

std::vector<int> CLMethodInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    if (instruction_info[opcode].category == CLConstants::METHOD1) {
        bytes.push_back(byte_at(index, 2));
        bytes.push_back(byte_at(index, 1));
        if (opcode == CLConstants::INVOKEINTERFACE) {
            bytes.push_back(byte_at(n_args, 1));
            bytes.push_back(0);
        }
    }
    return bytes;
}

CLArrayInstruction::CLArrayInstruction(int opcode, int pc, int type) : type(type) {
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

CLArrayInstruction::CLArrayInstruction(int opcode, int pc, int type, int dim) : type(type), dim(dim) {
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

CLArrayInstruction::CLArrayInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

std::vector<int> CLArrayInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    switch (opcode) {
    case CLConstants::NEWARRAY:
        bytes.push_back(byte_at(type, 1));
        break;
    case CLConstants::ANEWARRAY:
        bytes.push_back(byte_at(type, 2));
        bytes.push_back(byte_at(type, 1));
        break;
    case CLConstants::MULTIANEWARRAY:
        bytes.push_back(byte_at(type, 2));
        bytes.push_back(byte_at(type, 1));
        bytes.push_back(byte_at(dim, 1));
        break;
    }
    return bytes;
}

CLArithmeticInstruction::CLArithmeticInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

CLArithmeticInstruction::CLArithmeticInstruction(int opcode, int pc, int local_variable_index, int const_val, bool is_widened){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    CLInstruction::local_variable_index = local_variable_index;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    CLArithmeticInstruction::const_val = const_val;
    CLArithmeticInstruction::is_widened = is_widened;
}

std::vector<int> CLArithmeticInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    if (opcode == CLConstants::IINC) {
        if (is_widened) {
            bytes.push_back(byte_at(local_variable_index, 2));
            bytes.push_back(byte_at(local_variable_index, 1));
            bytes.push_back(byte_at(const_val, 2));
            bytes.push_back(byte_at(const_val, 1));
        }
        else {
            bytes.push_back(byte_at(local_variable_index, 1));
            bytes.push_back(byte_at(const_val, 1));
        }
    }
    return bytes;
}

CLBitInstruction::CLBitInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

std::vector<int> CLBitInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    return bytes;
}

CLComparisonInstruction::CLComparisonInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

std::vector<int> CLComparisonInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    return bytes;
}

CLConversionInstruction::CLConversionInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

std::vector<int> CLConversionInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    return bytes;
}

CLFlowControlInstruction::CLFlowControlInstruction(int opcode, int pc, std::string jump_to_label) : jump_to_label(jump_to_label) {
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

CLFlowControlInstruction::CLFlowControlInstruction(int pc, int index, bool is_widened)
    : index(index), is_widened(is_widened){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

CLFlowControlInstruction::CLFlowControlInstruction(int opcode, int pc, std::string default_label, int low, int high, std::vector<std::string> labels){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
    default_label = default_label;
    low = low;
    high = high;
    labels = labels;
    pad = 4 - ((pc + 1) % 4);
    if (pad == 4) {
        pad == 0;
    }
    operand_count = pad + 12 + 4 * labels.size();
}

CLFlowControlInstruction::CLFlowControlInstruction(int opcode, int pc, std::string default_label, int num_pairs, std::map<int, std::string> match_label_pairs){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
    default_label = default_label;
    num_pairs = num_pairs;
    match_label_pairs = match_label_pairs;
    pad = 4 - ((pc + 1) % 4);
    if (pad == 4) {
        pad = 0;
    }
    operand_count = pad + 8 + 8 * num_pairs;
}

bool CLFlowControlInstruction::resolve_labels(std::map<std::string, int> label_to_pc){
    bool all_labels_resolved = true;
    if (instruction_info[opcode].category == CLConstants::FLOW_CONTROL1) {
        if (label_to_pc.count(jump_to_label)) {
            jump_to_offset = label_to_pc.at(jump_to_label);
        }
        else {
            jump_to_offset = operand_count;
            all_labels_resolved = false;
        }
    }
    else if (opcode == CLConstants::LOOKUPSWITCH) {
        if (label_to_pc.count(default_label)) {
            default_offset = label_to_pc.at(default_label) - pc;
        }
        else {
            default_offset = operand_count;
            all_labels_resolved = false;
        }
        std::map<int, std::string>::iterator iter = match_label_pairs.begin();
        for (; iter != match_label_pairs.end(); iter++) {
            const std::pair<int, std::string>& entry = *iter;
            int match = entry.first;
            const std::string &label = entry.second;
            if (label_to_pc.count(label)) {
                match_offset_pairs.insert(std::pair<int, int>(match, label_to_pc.at(label) - pc));
            }
            else {
                match_offset_pairs.insert(std::pair<int, int>(match, operand_count));
                all_labels_resolved = false;
            }
        }
    }
    else if (opcode == CLConstants::TABLESWITCH) {
        if (label_to_pc.count(default_label)) {
            default_offset = label_to_pc.at(default_label) - pc;
        }
        else {
            default_offset = operand_count;
            all_labels_resolved = false;
        }
        for (int i = 0; i < labels.size(); i++) {
            if (label_to_pc.count(labels[i])) {
                offsets.push_back(label_to_pc.at(labels[i]) - pc);
            }
            else {
                offsets.push_back(operand_count);
                all_labels_resolved = false;
            }
        }
    }
    return all_labels_resolved;
}

int CLFlowControlInstruction::get_jump_offset(){
    return jump_to_offset;
}

std::vector<int> CLFlowControlInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    switch (opcode) {
    case CLConstants::RET:
        if (is_widened) {
            bytes.push_back(byte_at(index, 2));
            bytes.push_back(byte_at(index, 1));
        }
        else {
            bytes.push_back(byte_at(index, 1));
        }
        break;
    case CLConstants::TABLESWITCH:
        for (int i = 0; i < pad; i++) {
            bytes.push_back(0);
        }
        bytes.push_back(byte_at(default_offset, 4));
        bytes.push_back(byte_at(default_offset, 3));
        bytes.push_back(byte_at(default_offset, 2));
        bytes.push_back(byte_at(default_offset, 1));
        bytes.push_back(byte_at(low, 4));
        bytes.push_back(byte_at(low, 3));
        bytes.push_back(byte_at(low, 2));
        bytes.push_back(byte_at(low, 1));
        bytes.push_back(byte_at(high, 4));
        bytes.push_back(byte_at(high, 3));
        bytes.push_back(byte_at(high, 2));
        bytes.push_back(byte_at(high, 1));
        for (int i = 0; i < offsets.size(); i++) {
            int jump_offset = offsets[i];
            bytes.push_back(byte_at(jump_offset, 4));
            bytes.push_back(byte_at(jump_offset, 3));
            bytes.push_back(byte_at(jump_offset, 2));
            bytes.push_back(byte_at(jump_offset, 1));
        }
        break;
    case CLConstants::LOOKUPSWITCH:
    {
        for (int i = 0; i < pad; i++) {
            bytes.push_back(0);
        }
        bytes.push_back(byte_at(default_offset, 4));
        bytes.push_back(byte_at(default_offset, 3));
        bytes.push_back(byte_at(default_offset, 2));
        bytes.push_back(byte_at(default_offset, 1));
        bytes.push_back(byte_at(num_pairs, 4));
        bytes.push_back(byte_at(num_pairs, 3));
        bytes.push_back(byte_at(num_pairs, 2));
        bytes.push_back(byte_at(num_pairs, 1));
        std::map<int, int>::iterator iter = match_offset_pairs.begin();
        for (; iter != match_offset_pairs.end(); iter++) {
            const std::pair<int, int>& entry = *iter;
            int match = entry.first;
            int offset = entry.second;
            bytes.push_back(byte_at(match, 4));
            bytes.push_back(byte_at(match, 3));
            bytes.push_back(byte_at(match, 2));
            bytes.push_back(byte_at(match, 1));
            bytes.push_back(byte_at(offset, 4));
            bytes.push_back(byte_at(offset, 3));
            bytes.push_back(byte_at(offset, 2));
            bytes.push_back(byte_at(offset, 1));
        }
        break;
    }
    case CLConstants::GOTO_W:
    case CLConstants::JSR_W:
        bytes.push_back(byte_at(jump_to_offset, 4));
        bytes.push_back(byte_at(jump_to_offset, 3));
        bytes.push_back(byte_at(jump_to_offset, 2));
        bytes.push_back(byte_at(jump_to_offset, 1));
        break;
    default:
        bytes.push_back(byte_at(jump_to_offset, 2));
        bytes.push_back(byte_at(jump_to_offset, 1));
    }
    return bytes;
}

CLLoadStoreInstruction::CLLoadStoreInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

CLLoadStoreInstruction::CLLoadStoreInstruction(int opcode, int pc, int local_variable_index, bool is_widened){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    CLInstruction::local_variable_index = local_variable_index;
    is_widened = is_widened;
}

CLLoadStoreInstruction::CLLoadStoreInstruction(int opcode, int pc, int const_val) : const_val(const_val){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

std::vector<int> CLLoadStoreInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    if (instruction_info[opcode].operand_count > 0) {
        if (local_variable_index != CLConstants::IRRELEVANT) {
            if (is_widened) {
                bytes.push_back(byte_at(local_variable_index, 2));
            }
            bytes.push_back(byte_at(local_variable_index, 1));
        }
        else {
            switch (opcode) {
            case CLConstants::BIPUSH:
            case CLConstants::LDC:
                bytes.push_back(byte_at(const_val, 1));
                break;
            case CLConstants::SIPUSH:
            case CLConstants::LDC_W:
            case CLConstants::LDC2_W:
                bytes.push_back(byte_at(const_val, 2));
                bytes.push_back(byte_at(const_val, 1));
            }
        }
    }
    return bytes;
}

CLStackInstruction::CLStackInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

std::vector<int> CLStackInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    return bytes;
}

CLMiscInstruction::CLMiscInstruction(int opcode, int pc){
    CLInstruction::opcode = opcode;
    CLInstruction::pc = pc;
    mnemonic = instruction_info[opcode].mnemonic;
    operand_count = instruction_info[opcode].operand_count;
    stack_units = instruction_info[opcode].stack_units;
    local_variable_index = instruction_info[opcode].local_variable_index;
}

std::vector<int> CLMiscInstruction::to_bytes(){
    std::vector<int> bytes;
    bytes.push_back(opcode);
    return bytes;
}

