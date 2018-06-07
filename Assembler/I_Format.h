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

class I_Format: public Format
{
public:
	I_Format();
	~I_Format();
	uint32_t convertToBinary(const string &operation, const vector<Operand> &operands, int address);
};

