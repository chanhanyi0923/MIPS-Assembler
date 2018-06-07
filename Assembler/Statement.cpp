#include "Statement.h"

#include <sstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include "AssembleException.h"
#include "Operand.h"
#include "Label.h"

using std::stringstream;
using std::string;
using std::vector;


Statement::Statement()
{
}


Statement::~Statement()
{
}


Statement::Statement(const string & statement, int addr, int line_num)
{
	this->address = addr;
	this->line_num = line_num;

	string str;
	stringstream buffer(statement);
	buffer >> str;
	if (str.back() == ':') {
		str.pop_back();
		this->label = str;
		buffer >> str;
	}
	this->operation = str;

	getline(buffer, str);

	// split operands
	vector<string> tokens;
	boost::split(tokens, str, boost::is_any_of(","), boost::token_compress_on);
	for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
		string &token = *it;
		token = boost::trim_all_copy(token);
		if (!token.empty()) {
			this->operands.push_back(Operand(token));
		}
	}
}


uint32_t Statement::toBinary()
{
	uint32_t code;
	if (R.operationIn(operation)) {
		code = R.convertToBinary(operation, operands);
	} else if (I.operationIn(operation)) {
		code = I.convertToBinary(operation, operands, address);
	} else if (J.operationIn(operation)) {
		code = J.convertToBinary(operation, operands);
	} else {
		throw AssembleException("Unknown operation.");
	}
	return code;
}


void Statement::setAddress()
{
	if (!label.empty()) {
		Label::insert(label, address);
	}
}


int Statement::getLineNum()
{
	return line_num;
}

