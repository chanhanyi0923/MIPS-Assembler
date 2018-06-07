#pragma once

#include <map>
#include <string>
#include <vector>

#include "Instruction.h"

using std::map;
using std::string;
using std::vector;


class Format
{
protected:
	map<string, Instruction> instructions;
public:
	Format();
	~Format();
	bool operationIn(const string &operation);
};

