#include "Label.h"

#include <string>
#include <map>

#include "AssembleException.h"

using std::string;
using std::map;

Label::Label()
{
}


Label::~Label()
{
}

void Label::insert(string str, int address)
{
	map<string, int>::iterator it = address_table.find(str);
	if (it != address_table.end()) {
		throw AssembleException("Cannot redeclare label.");
	}
	address_table[str] = address;
}

int Label::getAddress(string str)
{
	map<string, int>::iterator it = address_table.find(str);
	if (it == address_table.end()) {
		throw AssembleException("Label dose not exist.");
	}
	return it->second;
}

