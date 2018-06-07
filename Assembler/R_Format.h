#pragma once

#include <map>
#include <string>
#include <vector>

#include "Operand.h"
#include "Format.h"
#include "Instruction.h"

using std::map;
using std::string;
using std::vector;

class R_Format: public Format
{
public:
	R_Format();
	~R_Format();
	uint32_t convertToBinary(const string &operation, const vector<Operand> &operands);
};

