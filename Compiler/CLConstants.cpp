//#include <string>
//
//class CLConstants {
//public:
//    static const long MAGIC = 3405691582L;
//
//    static const int MAJOR_VERSION = 49;
//    static const int MINOR_VERSION = 0;
//
//    // Access flags
//    inline static const int ACC_PUBLIC = 0x0001;
//    inline static const int ACC_PRIVATE = 0x0002;
//    inline static const int ACC_PROTECTED = 0x0004;
//    inline static const int ACC_STATIC = 0x0008;
//    inline static const int ACC_FINAL = 0x0010;
//    inline static const int ACC_SUPER = 0x0020;
//    inline static const int ACC_SYNCHRONIZED = 0x0020;
//    inline static const int ACC_VOLATILE = 0x0040;
//    inline static const int ACC_BRIDGE = 0x0040;
//    inline static const int ACC_TRANSIENT = 0x0080;
//
//    inline static const int ACC_VARARGS = 0x0080;
//
//    /** native access flag. */
//    inline static const int ACC_NATIVE = 0x0100;
//
//    /** interface access flag. */
//    inline static const int ACC_INTERFACE = 0x0200;
//
//    /** abstract access flag. */
//    inline static const int ACC_ABSTRACT = 0x0400;
//
//    /** strict access flag. */
//    inline static const int ACC_STRICT = 0x0800;
//
//    /** synthetic access flag. */
//    inline static const int ACC_SYNTHETIC = 0x1000;
//
//    /** annotation access flag. */
//    inline static const int ACC_ANNOTATION = 0x2000;
//
//    /** enum access flag. */
//    inline static const int ACC_ENUM = 0x4000;
//
//    /** Identifies CONSTANT_Utf8_info constant pool structure. */
//    inline static const short CONSTANT_Utf8 = 1;
//
//    /** Identifies CONSTANT_Integer_info constant pool structure. */
//    inline static const short CONSTANT_Integer = 3;
//
//    /** Identifies CONSTANT_Float_info constant pool structure. */
//    inline static const short CONSTANT_Float = 4;
//
//    /** Identifies CONSTANT_Long_info constant pool structure. */
//    inline static const short CONSTANT_Long = 5;
//
//    /** Identifies CONSTANT_Double_info constant pool structure. */
//    inline static const short CONSTANT_Double = 6;
//
//    /** Identifies CONSTANT_Class_info constant pool structure. */
//    inline static const short CONSTANT_Class = 7;
//
//    /** Identifies CONSTANT_String_info constant pool structure. */
//    inline static const short CONSTANT_String = 8;
//
//    /** Identifies CONSTANT_Fieldref_info constant pool structure. */
//    inline static const short CONSTANT_Fieldref = 9;
//
//    /**
//     * Identifies CONSTANT_Methodref_info constant pool structure.
//     */
//    inline static const short CONSTANT_Methodref = 10;
//
//    /**
//     * Identifies CONSTANT_InterfaceMethodref_info constant pool structure.
//     */
//    inline static const short CONSTANT_InterfaceMethodref = 11;
//
//    /**
//     * Identifies CONSTANT_NameAndType_info constant pool structure.
//     */
//    inline static const short CONSTANT_NameAndType = 12;
//
//    /** Identifies ConstantValue attribute. */
//    inline static const std::string ATT_CONSTANT_VALUE = "ConstantValue";
//
//    /** Identifies Code attribute. */
//    inline static const std::string ATT_CODE = "Code";
//
//    /** Identifies Exceptions attribute. */
//    inline static const std::string ATT_EXCEPTIONS = "Exceptions";
//
//    /** Identifies InnerClasses attribute. */
//    inline static const std::string ATT_INNER_CLASSES = "InnerClasses";
//
//    /** Identifies EnclosingMethod attribute. */
//    inline static const std::string ATT_ENCLOSING_METHOD = "EnclosingMethod";
//
//    /** Identifies Synthetic attribute. */
//    inline static const std::string ATT_SYNTHETIC = "Synthetic";
//
//    /** Identifies Signature attribute. */
//    inline static const std::string ATT_SIGNATURE = "Signature";
//
//    /** Identifies SourceFile attribute. */
//    inline static const std::string ATT_SOURCE_FILE = "SourceFile";
//
//    /** Identifies SourceDebugExtension attribute. */
//    inline static const std::string ATT_SOURCE_DEBUG_EXTENSION = "SourceDebugExtension";
//
//    /** Identifies LineNumberTable attribute. */
//    inline static const std::string ATT_LINE_NUMBER_TABLE = "LineNumberTable";
//
//    /** Identifies LocalVariableTable attribute. */
//    inline static const std::string ATT_LOCAL_VARIABLE_TABLE = "LocalVariableTable";
//
//    /** Identifies LocalVariableTypeTable attribute. */
//    inline static const std::string ATT_LOCAL_VARIABLE_TYPE_TABLE = "LocalVariableTypeTable";
//
//    /** Identifies Deprecated attribute. */
//    inline static const std::string ATT_DEPRECATED = "Deprecated";
//
//    /** Identifies RuntimeVisibleAnnotations attribute. */
//    inline static const std::string ATT_RUNTIME_VISIBLE_ANNOTATIONS = "RuntimeVisibleAnnotations";
//
//    /** Identifies RuntimeInvisibleAnnotations attribute. */
//    inline static const std::string ATT_RUNTIME_INVISIBLE_ANNOTATIONS = "RuntimeInvisibleAnnotations";
//
//    /** Identifies RuntimeVisibleParameterAnnotations attribute. */
//    inline static const std::string ATT_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS = "RuntimeVisibleParameterAnnotations";
//
//    /** Identifies RuntimeInvisibleParameterAnnotations attribute. */
//    inline static const std::string ATT_RUNTIME_INVISIBLE_PARAMETER_ANNOTATIONS = "RuntimeInvisibleParameterAnnotations";
//
//    /** Identifies AnnotationDefault attribute. */
//    inline static const std::string ATT_ANNOTATION_DEFAULT = "AnnotationDefault";
//
//    /** Identifies boolean type of annotation element value. */
//    inline static const short ELT_B = 'B';
//
//    /** Identifies char type of annotation element value. */
//    inline static const short ELT_C = 'C';
//
//    /** Identifies double type of annotation element value. */
//    inline static const short ELT_D = 'D';
//
//    /** Identifies float type of annotation element value. */
//    inline static const short ELT_F = 'F';
//
//    /** Identifies int type of annotation element value. */
//    inline static const short ELT_I = 'I';
//
//    /** Identifies long type of annotation element value. */
//    inline static const short ELT_J = 'J';
//
//    /** Identifies short type of annotation element value. */
//    inline static const short ELT_S = 'S';
//
//    /** Identifies boolean type of annotation element value. */
//    inline static const short ELT_Z = 'Z';
//
//    /** Identifies String type of annotation element value. */
//    inline static const short ELT_s = 's';
//
//    /** Identifies class type of annotation element value. */
//    inline static const short ELT_c = 'c';
//
//    /** Identifies annotation type of annotation element value. */
//    inline static const short ELT_ANNOTATION = '@';
//
//    /** Identifies array type of annotation element value. */
//    inline static const short ELT_ARRAY = '[';
//
//    /** Identifies enum type of annotation element value. */
//    inline static const short ELT_e = 'e';
//
//    // JVM instructions begin here
//
//    /** NOP instruction. */
//    inline static const int NOP = 0;
//
//    /** ACONST_NULL instruction. */
//    inline static const int ACONST_NULL = 1;
//
//    /** ICONST_M1 instruction. */
//    inline static const int ICONST_M1 = 2;
//
//    /** ICONST_0 instruction. */
//    inline static const int ICONST_0 = 3;
//
//    /** ICONST_1 instruction. */
//    inline static const int ICONST_1 = 4;
//
//    /** ICONST_2 instruction. */
//    inline static const int ICONST_2 = 5;
//
//    /** ICONST_3 instruction. */
//    inline static const int ICONST_3 = 6;
//
//    /** ICONST_4 instruction. */
//    inline static const int ICONST_4 = 7;
//
//    /** ICONST_5 instruction. */
//    inline static const int ICONST_5 = 8;
//
//    /** LCONST_0 instruction. */
//    inline static const int LCONST_0 = 9;
//
//    /** LCONST_1 instruction. */
//    inline static const int LCONST_1 = 10;
//
//    /** FCONST_0 instruction. */
//    inline static const int FCONST_0 = 11;
//
//    /** FCONST_1 instruction. */
//    inline static const int FCONST_1 = 12;
//
//    /** FCONST_2 instruction. */
//    inline static const int FCONST_2 = 13;
//
//    /** DCONST_0 instruction. */
//    inline static const int DCONST_0 = 14;
//
//    /** DCONST_1 instruction. */
//    inline static const int DCONST_1 = 15;
//
//    /** BIPUSH instruction. */
//    inline static const int BIPUSH = 16;
//
//    /** SIPUSH instruction. */
//    inline static const int SIPUSH = 17;
//
//    /** LDC instruction. */
//    inline static const int LDC = 18;
//
//    /** LDC_W instruction. */
//    inline static const int LDC_W = 19;
//
//    /** LDC2_W instruction. */
//    inline static const int LDC2_W = 20;
//
//    /** ILOAD instruction. */
//    inline static const int ILOAD = 21;
//
//    /** LLOAD instruction. */
//    inline static const int LLOAD = 22;
//
//    /** FLOAD instruction. */
//    inline static const int FLOAD = 23;
//
//    /** DLOAD instruction. */
//    inline static const int DLOAD = 24;
//
//    /** ALOAD instruction. */
//    inline static const int ALOAD = 25;
//
//    /** ILOAD_0 instruction. */
//    inline static const int ILOAD_0 = 26;
//
//    /** ILOAD_1 instruction. */
//    inline static const int ILOAD_1 = 27;
//
//    /** ILOAD_2 instruction. */
//    inline static const int ILOAD_2 = 28;
//
//    /** ILOAD_3 instruction. */
//    inline static const int ILOAD_3 = 29;
//
//    /** LLOAD_0 instruction. */
//    inline static const int LLOAD_0 = 30;
//
//    /** LLOAD_1 instruction. */
//    inline static const int LLOAD_1 = 31;
//
//    /** LLOAD_2 instruction. */
//    inline static const int LLOAD_2 = 32;
//
//    /** LLOAD_3 instruction. */
//    inline static const int LLOAD_3 = 33;
//
//    /** FLOAD_0 instruction. */
//    inline static const int FLOAD_0 = 34;
//
//    /** FLOAD_1 instruction. */
//    inline static const int FLOAD_1 = 35;
//
//    /** FLOAD_2 instruction. */
//    inline static const int FLOAD_2 = 36;
//
//    /** FLOAD_3 instruction. */
//    inline static const int FLOAD_3 = 37;
//
//    /** DLOAD_0 instruction. */
//    inline static const int DLOAD_0 = 38;
//
//    /** DLOAD_1 instruction. */
//    inline static const int DLOAD_1 = 39;
//
//    /** DLOAD_2 instruction. */
//    inline static const int DLOAD_2 = 40;
//
//    /** DLOAD_3 instruction. */
//    inline static const int DLOAD_3 = 41;
//
//    /** ALOAD_0 instruction. */
//    inline static const int ALOAD_0 = 42;
//
//    /** ALOAD_1 instruction. */
//    inline static const int ALOAD_1 = 43;
//
//    /** ALOAD_2 instruction. */
//    inline static const int ALOAD_2 = 44;
//
//    /** ALOAD_3 instruction. */
//    inline static const int ALOAD_3 = 45;
//
//    /** IALOAD instruction. */
//    inline static const int IALOAD = 46;
//
//    /** LALOAD instruction. */
//    inline static const int LALOAD = 47;
//
//    /** FALOAD instruction. */
//    inline static const int FALOAD = 48;
//
//    /** DALOAD instruction. */
//    inline static const int DALOAD = 49;
//
//    /** AALOAD instruction. */
//    inline static const int AALOAD = 50;
//
//    /** BALOAD instruction. */
//    inline static const int BALOAD = 51;
//
//    /** CALOAD instruction. */
//    inline static const int CALOAD = 52;
//
//    /** SALOAD instruction. */
//    inline static const int SALOAD = 53;
//
//    /** ISTORE instruction. */
//    inline static const int ISTORE = 54;
//
//    /** LSTORE instruction. */
//    inline static const int LSTORE = 55;
//
//    /** FSTORE instruction. */
//    inline static const int FSTORE = 56;
//
//    /** DSTORE instruction. */
//    inline static const int DSTORE = 57;
//
//    /** ASTORE instruction. */
//    inline static const int ASTORE = 58;
//
//    /** ISTORE_0 instruction. */
//    inline static const int ISTORE_0 = 59;
//
//    /** ISTORE_1 instruction. */
//    inline static const int ISTORE_1 = 60;
//
//    /** ISTORE_2 instruction. */
//    inline static const int ISTORE_2 = 61;
//
//    /** ISTORE_3 instruction. */
//    inline static const int ISTORE_3 = 62;
//
//    /** LSTORE_0 instruction. */
//    inline static const int LSTORE_0 = 63;
//
//    /** LSTORE_1 instruction. */
//    inline static const int LSTORE_1 = 64;
//
//    /** LSTORE_2 instruction. */
//    inline static const int LSTORE_2 = 65;
//
//    /** LSTORE_3 instruction. */
//    inline static const int LSTORE_3 = 66;
//
//    /** FSTORE_0 instruction. */
//    inline static const int FSTORE_0 = 67;
//
//    /** FSTORE_1 instruction. */
//    inline static const int FSTORE_1 = 68;
//
//    /** FSTORE_2 instruction. */
//    inline static const int FSTORE_2 = 69;
//
//    /** FSTORE_3 instruction. */
//    inline static const int FSTORE_3 = 70;
//
//    /** DSTORE_0 instruction. */
//    inline static const int DSTORE_0 = 71;
//
//    /** DSTORE_1 instruction. */
//    inline static const int DSTORE_1 = 72;
//
//    /** DSTORE_2 instruction. */
//    inline static const int DSTORE_2 = 73;
//
//    /** DSTORE_3 instruction. */
//    inline static const int DSTORE_3 = 74;
//
//    /** ASTORE_0 instruction. */
//    inline static const int ASTORE_0 = 75;
//
//    /** ASTORE_1 instruction. */
//    inline static const int ASTORE_1 = 76;
//
//    /** ASTORE_2 instruction. */
//    inline static const int ASTORE_2 = 77;
//
//    /** ASTORE_3 instruction. */
//    inline static const int ASTORE_3 = 78;
//
//    /** IASTORE instruction. */
//    inline static const int IASTORE = 79;
//
//    /** LASTORE instruction. */
//    inline static const int LASTORE = 80;
//
//    /** FASTORE instruction. */
//    inline static const int FASTORE = 81;
//
//    /** DASTORE instruction. */
//    inline static const int DASTORE = 82;
//
//    /** AASTORE instruction. */
//    inline static const int AASTORE = 83;
//
//    /** BASTORE instruction. */
//    inline static const int BASTORE = 84;
//
//    /** CASTORE instruction. */
//    inline static const int CASTORE = 85;
//
//    /** SASTORE instruction. */
//    inline static const int SASTORE = 86;
//
//    /** POP instruction. */
//    inline static const int POP = 87;
//
//    /** POP2 instruction. */
//    inline static const int POP2 = 88;
//
//    /** DUP instruction. */
//    inline static const int DUP = 89;
//
//    /** DUP_X1 instruction. */
//    inline static const int DUP_X1 = 90;
//
//    /** DUP_X2 instruction. */
//    inline static const int DUP_X2 = 91;
//
//    /** DUP2 instruction. */
//    inline static const int DUP2 = 92;
//
//    /** DUP2_X1 instruction. */
//    inline static const int DUP2_X1 = 93;
//
//    /** DUP2_X2 instruction. */
//    inline static const int DUP2_X2 = 94;
//
//    /** SWAP instruction. */
//    inline static const int SWAP = 95;
//
//    /** IADD instruction. */
//    inline static const int IADD = 96;
//
//    /** LADD instruction. */
//    inline static const int LADD = 97;
//
//    /** FADD instruction. */
//    inline static const int FADD = 98;
//
//    /** DADD instruction. */
//    inline static const int DADD = 99;
//
//    /** ISUB instruction. */
//    inline static const int ISUB = 100;
//
//    /** LSUB instruction. */
//    inline static const int LSUB = 101;
//
//    /** FSUB instruction. */
//    inline static const int FSUB = 102;
//
//    /** DSUB instruction. */
//    inline static const int DSUB = 103;
//
//    /** IMUL instruction. */
//    inline static const int IMUL = 104;
//
//    /** LMUL instruction. */
//    inline static const int LMUL = 105;
//
//    /** FMUL instruction. */
//    inline static const int FMUL = 106;
//
//    /** DMUL instruction. */
//    inline static const int DMUL = 107;
//
//    /** IDIV instruction. */
//    inline static const int IDIV = 108;
//
//    /** LDIV instruction. */
//    inline static const int LDIV = 109;
//
//    /** FDIV instruction. */
//    inline static const int FDIV = 110;
//
//    /** DDIV instruction. */
//    inline static const int DDIV = 111;
//
//    /** IREM instruction. */
//    inline static const int IREM = 112;
//
//    /** LREM instruction. */
//    inline static const int LREM = 113;
//
//    /** FREM instruction. */
//    inline static const int FREM = 114;
//
//    /** DREM instruction. */
//    inline static const int DREM = 115;
//
//    /** INEG instruction. */
//    inline static const int INEG = 116;
//
//    /** LNEG instruction. */
//    inline static const int LNEG = 117;
//
//    /** FNEG instruction. */
//    inline static const int FNEG = 118;
//
//    /** DNEG instruction. */
//    inline static const int DNEG = 119;
//
//    /** ISHL instruction. */
//    inline static const int ISHL = 120;
//
//    /** LSHL instruction. */
//    inline static const int LSHL = 121;
//
//    /** ISHR instruction. */
//    inline static const int ISHR = 122;
//
//    /** LSHR instruction. */
//    inline static const int LSHR = 123;
//
//    /** IUSHR instruction. */
//    inline static const int IUSHR = 124;
//
//    /** LUSHR instruction. */
//    inline static const int LUSHR = 125;
//
//    /** IAND instruction. */
//    inline static const int IAND = 126;
//
//    /** LAND instruction. */
//    inline static const int LAND = 127;
//
//    /** IOR instruction. */
//    inline static const int IOR = 128;
//
//    /** LOR instruction. */
//    inline static const int LOR = 129;
//
//    /** IXOR instruction. */
//    inline static const int IXOR = 130;
//
//    /** LXOR instruction. */
//    inline static const int LXOR = 131;
//
//    /** IINC instruction. */
//    inline static const int IINC = 132;
//
//    /** I2L instruction. */
//    inline static const int I2L = 133;
//
//    /** I2F instruction. */
//    inline static const int I2F = 134;
//
//    /** I2D instruction. */
//    inline static const int I2D = 135;
//
//    /** L2I instruction. */
//    inline static const int L2I = 136;
//
//    /** L2F instruction. */
//    inline static const int L2F = 137;
//
//    /** L2D instruction. */
//    inline static const int L2D = 138;
//
//    /** F2I instruction. */
//    inline static const int F2I = 139;
//
//    /** F2L instruction. */
//    inline static const int F2L = 140;
//
//    /** F2D instruction. */
//    inline static const int F2D = 141;
//
//    /** D2I instruction. */
//    inline static const int D2I = 142;
//
//    /** D2L instruction. */
//    inline static const int D2L = 143;
//
//    /** D2F instruction. */
//    inline static const int D2F = 144;
//
//    /** I2B instruction. */
//    inline static const int I2B = 145;
//
//    /** I2C instruction. */
//    inline static const int I2C = 146;
//
//    /** I2S instruction. */
//    inline static const int I2S = 147;
//
//    /** LCMP instruction. */
//    inline static const int LCMP = 148;
//
//    /** FCMPL instruction. */
//    inline static const int FCMPL = 149;
//
//    /** FCMPG instruction. */
//    inline static const int FCMPG = 150;
//
//    /** DCMPL instruction. */
//    inline static const int DCMPL = 151;
//
//    /** DCMPG instruction. */
//    inline static const int DCMPG = 152;
//
//    /** IFEQ instruction. */
//    inline static const int IFEQ = 153;
//
//    /** IFNE instruction. */
//    inline static const int IFNE = 154;
//
//    /** IFLT instruction. */
//    inline static const int IFLT = 155;
//
//    /** IFGE instruction. */
//    inline static const int IFGE = 156;
//
//    /** IFGT instruction. */
//    inline static const int IFGT = 157;
//
//    /** IFLE instruction. */
//    inline static const int IFLE = 158;
//
//    /** IF_ICMPEQ instruction. */
//    inline static const int IF_ICMPEQ = 159;
//
//    /** IF_ICMPNE instruction. */
//    inline static const int IF_ICMPNE = 160;
//
//    /** IF_ICMPLT instruction. */
//    inline static const int IF_ICMPLT = 161;
//
//    /** IF_ICMPGE instruction. */
//    inline static const int IF_ICMPGE = 162;
//
//    /** IF_ICMPGT instruction. */
//    inline static const int IF_ICMPGT = 163;
//
//    /** IF_ICMPLE instruction. */
//    inline static const int IF_ICMPLE = 164;
//
//    /** IF_ACMPEQ instruction. */
//    inline static const int IF_ACMPEQ = 165;
//
//    /** IF_ACMPNE instruction. */
//    inline static const int IF_ACMPNE = 166;
//
//    /** GOTO instruction. */
//    inline static const int GOTO = 167;
//
//    /** JSR instruction. */
//    inline static const int JSR = 168;
//
//    /** RET instruction. */
//    inline static const int RET = 169;
//
//    /** TABLESWITCH instruction. */
//    inline static const int TABLESWITCH = 170;
//
//    /** LOOKUPSWITCH instruction. */
//    inline static const int LOOKUPSWITCH = 171;
//
//    /** IRETURN instruction. */
//    inline static const int IRETURN = 172;
//
//    /** LRETURN instruction. */
//    inline static const int LRETURN = 173;
//
//    /** FRETURN instruction. */
//    inline static const int FRETURN = 174;
//
//    /** DRETURN instruction. */
//    inline static const int DRETURN = 175;
//
//    /** ARETURN instruction. */
//    inline static const int ARETURN = 176;
//
//    /** RETURN instruction. */
//    inline static const int RETURN = 177;
//
//    /** GETSTATIC instruction. */
//    inline static const int GETSTATIC = 178;
//
//    /** PUTSTATIC instruction. */
//    inline static const int PUTSTATIC = 179;
//
//    /** GETFIELD instruction. */
//    inline static const int GETFIELD = 180;
//
//    /** PUTFIELD instruction. */
//    inline static const int PUTFIELD = 181;
//
//    /** INVOKEVIRTUAL instruction. */
//    inline static const int INVOKEVIRTUAL = 182;
//
//    /** INVOKESPECIAL instruction. */
//    inline static const int INVOKESPECIAL = 183;
//
//    /** INVOKESTATIC instruction. */
//    inline static const int INVOKESTATIC = 184;
//
//    /** INVOKEINTERFACE instruction. */
//    inline static const int INVOKEINTERFACE = 185;
//
//    /** INVOKEDYNAMIC instruction. */
//    inline static const int INVOKEDYNAMIC = 186;
//
//    /** NEW instruction. */
//    inline static const int NEW = 187;
//
//    /** NEWARRAY instruction. */
//    inline static const int NEWARRAY = 188;
//
//    /** ANEWARRAY instruction. */
//    inline static const int ANEWARRAY = 189;
//
//    /** ARRAYLENGTH instruction. */
//    inline static const int ARRAYLENGTH = 190;
//
//    /** ATHROW instruction. */
//    inline static const int ATHROW = 191;
//
//    /** CHECKCAST instruction. */
//    inline static const int CHECKCAST = 192;
//
//    /** INSTANCEOF instruction. */
//    inline static const int INSTANCEOF = 193;
//
//    /** MONITORENTER instruction. */
//    inline static const int MONITORENTER = 194;
//
//    /** MONITOREXIT instruction. */
//    inline static const int MONITOREXIT = 195;
//
//    /** WIDE instruction. */
//    inline static const int WIDE = 196;
//
//    /** MULTIANEWARRAY instruction. */
//    inline static const int MULTIANEWARRAY = 197;
//
//    /** IFNULL instruction. */
//    inline static const int IFNULL = 198;
//
//    /** IFNONNULL instruction. */
//    inline static const int IFNONNULL = 199;
//
//    /** GOTO_W instruction. */
//    inline static const int GOTO_W = 200;
//
//    /** JSR_W instruction. */
//    inline static const int JSR_W = 201;
//
//    enum Category { 
//        OBJECT, FIELD, METHOD1, METHOD2, 
//        ARRAY1, ARRAY2, ARRAY3, ARITHMETIC1,
//        ARITHMETIC2, BIT, COMPARISON, CONVERSION,
//        FLOW_CONTROL1, FLOW_CONTROL2, FLOW_CONTROL3, 
//        FLOW_CONTROL4, LOAD_STORE1, LOAD_STORE2,
//        LOAD_STORE3, LOAD_STORE4, STACK, MISC 
//    };
//
//    inline static const int IRRELEVANT = -1;
//    
//    inline static const int DYNAMIC = 300;
//
//    inline static const int EMPTY_STACK = 301;
//
//    inline static const int UNIT_SIZE_STACK = 302;
//};