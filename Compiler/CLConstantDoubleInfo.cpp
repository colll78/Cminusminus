#include "CLConstantDoubleInfo.h"
#include "CLConstants.h"

CLConstantDoubleInfo::CLConstantDoubleInfo(double d) : d(d) {
    tag = CLConstants::CONSTANT_Double;
}

CLConstantDoubleInfo::CLConstantDoubleInfo(const CLConstantDoubleInfo& obj) : d(obj.d){
    tag = CLConstants::CONSTANT_Double;
}

std::array<short, 8> CLConstantDoubleInfo::bytes() {
    std::array<short, 8> s{};
    short mask = 0xFF;
    long long k = d;
    for (int j = 0; j < 8; j++) {
        s[7 - j] = (short)(k & mask);
        k >>= 8;
    }
    return s;
}

std::array<short, 4> CLConstantDoubleInfo::low_bytes() {
    std::array<short, 8> s = bytes();
    std::array<short, 4> l{};
    l[0] = s[4];
    l[1] = s[5];
    l[2] = s[6];
    l[3] = s[7];
    return l;
}

std::array<short, 4> CLConstantDoubleInfo::high_bytes() {
    std::array<short, 8> s = bytes();
    std::array<short, 4> h{};
    h[0] = s[0];
    h[1] = s[1];
    h[2] = s[2];
    h[3] = s[3];
    return h;
}

void CLConstantDoubleInfo::write(CLOutputStream out) {
    CLCPInfo::write(out);
    out.write_double(d);
}

bool CLConstantDoubleInfo::equals(CLConstantDoubleInfo obj) {
    return (obj.d == d);
}

std::unique_ptr<CLCPInfo> CLConstantDoubleInfo::create_unique(){
	return std::make_unique<CLConstantDoubleInfo>(*this);
}
