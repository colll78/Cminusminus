#include "CLConstantFloatInfo.h"
#include "CLConstants.h"
#include "jmm_utils.h"
CLConstantFloatInfo::CLConstantFloatInfo(float f) : f(f){
	tag = CLConstants::CONSTANT_Float;
}

CLConstantFloatInfo::CLConstantFloatInfo(const CLConstantFloatInfo& obj) : f(obj.f){
    tag = CLConstants::CONSTANT_Float;
}

std::array<short, 4> CLConstantFloatInfo::bytes() {
    std::array<short, 4> s{};
    short mask = 0xFF;
    int i = float_to_int_bits(f);
    for (int j = 0; j < 4; j++) {
        s[3 - j] = (short)(i & mask);
        i >>= 8;
    }
    return s;
}

void CLConstantFloatInfo::write(CLOutputStream out){
    CLCPInfo::write(out);
    out.write_float(f);
}

bool CLConstantFloatInfo::equals(CLConstantFloatInfo obj) {
    return (obj.f == f);
}

std::unique_ptr<CLCPInfo> CLConstantFloatInfo::create_unique(){
    return std::make_unique<CLConstantFloatInfo>(*this);
}
