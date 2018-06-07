#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

class Label
{
	static map<string, int> address_table;
public:
	Label();
	~Label();
	static void insert(string str, int address);
	static int getAddress(string str);
};

