#include "CLConstantIntegerInfo.h"
#include "CLConstants.h"
CLConstantIntegerInfo::CLConstantIntegerInfo(int i) : i(i) {
	tag = CLConstants::CONSTANT_Integer;
}

CLConstantIntegerInfo::CLConstantIntegerInfo(const CLConstantIntegerInfo& obj) : i(obj.i){
    tag = CLConstants::CONSTANT_Integer;
}

std::array<short, 4> CLConstantIntegerInfo::bytes() {
    std::array<short, 4> s = {};
    short mask = 0xFF;
    int k = i;
    for (int j = 0; j < 4; j++) {
        s[3 - j] = (short)(k & mask);
        k >>= 8;
    }
    return s;
}

void CLConstantIntegerInfo::write(CLOutputStream out) {
    CLCPInfo::write(out);
    out.write_int(i);
}

bool CLConstantIntegerInfo::equals(CLConstantIntegerInfo obj) {
    return (obj.i == i);
}

std::unique_ptr<CLCPInfo> CLConstantIntegerInfo::create_unique(){
	return std::make_unique<CLConstantIntegerInfo>(*this);
}
