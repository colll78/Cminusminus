#include "CLConstantLongInfo.h"
#include "CLConstants.h"

CLConstantLongInfo::CLConstantLongInfo(long long l) : l(l) {
    tag = CLConstants::CONSTANT_Long;
}

CLConstantLongInfo::CLConstantLongInfo(const CLConstantLongInfo& obj) : l(obj.l){
    tag = CLConstants::CONSTANT_Long;
}

std::array<short, 8> CLConstantLongInfo::bytes(){
    std::array<short, 8> s {};
    short mask = 0xFF;
    long long k = l;
    for (int j = 0; j < 8; j++) {
        s[7 - j] = (short)(k & mask);
        k >>= 8;
    }
    return s;
}

std::array<short, 4> CLConstantLongInfo::low_bytes() {
    std::array<short,8> s = bytes();
    std::array<short, 4> l{};
    l[0] = s[4];
    l[1] = s[5];
    l[2] = s[6];
    l[3] = s[7];
    return l;
}

std::array<short, 4> CLConstantLongInfo::high_bytes() {
    std::array<short, 8> s = bytes();
    std::array<short, 4> h{};
    h[0] = s[0];
    h[1] = s[1];
    h[2] = s[2];
    h[3] = s[3];
    return h;
}

void CLConstantLongInfo::write(CLOutputStream out){
    CLCPInfo::write(out);
    out.write_long(l);
}

bool CLConstantLongInfo::equals(CLConstantLongInfo obj) {
    return (obj.l == l);
}

std::unique_ptr<CLCPInfo> CLConstantLongInfo::create_unique(){
	return std::make_unique<CLConstantLongInfo>(*this);
}
