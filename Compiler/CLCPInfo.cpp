#include "CLCPInfo.h"
#include "CLConstantClassInfo.h"


void CLCPInfo::write(CLOutputStream out){
	out.write(tag);
}

bool CLCPInfo::equals(CLCPInfo obj){
	return &obj == this;
}

std::unique_ptr<CLCPInfo> CLCPInfo::create_unique(){
	return std::make_unique<CLCPInfo>(*this);
}
