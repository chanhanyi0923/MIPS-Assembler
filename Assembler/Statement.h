#pragma once

#include <string>
#include <vector>

#include "Operand.h"
#include "R_Format.h"
#include "I_Format.h"
#include "J_Format.h"

using std::string;
using std::vector;

class Statement
{
	static R_Format R;
	static I_Format I;
	static J_Format J;
	string operation, label;
	vector<Operand> operands;
	int address, line_num;
public:
	Statement();
	~Statement();
	Statement(const string & statement, int address, int line_num);
	uint32_t toBinary();
	void setAddress();
	int getLineNum();
};

