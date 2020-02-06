#pragma once
#include <memory>
#include "CLOutputStream.h"

class CLCPInfo {
public:
	int cp_index;	/* Index of this object into the constant pool */
	short int tag;	/* cp_info.tag item */
	virtual void write(CLOutputStream out);
	virtual bool equals(CLCPInfo obj);
	virtual std::unique_ptr<CLCPInfo> create_unique();
private:
};
