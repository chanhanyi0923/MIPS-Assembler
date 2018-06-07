#pragma once

#include "Operand.h"
#include "Format.h"

class J_Format: public Format
{
public:
	J_Format();
	~J_Format();
	uint32_t convertToBinary(const string &operation, const vector<Operand> &operands);
};

