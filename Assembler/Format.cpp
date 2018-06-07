#include "Format.h"

#include <map>
#include <string>

#include "Instruction.h"

using std::string;
using std::map;


Format::Format()
{
}


Format::~Format()
{
}


bool Format::operationIn(const string &operation)
{
	map<string, Instruction>::iterator it = instructions.find(operation);
	return it != instructions.end();
}

