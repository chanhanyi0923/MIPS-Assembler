#include "Text.h"

#include <istream>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/format.hpp>

#include "AssembleException.h"
#include "Label.h"
#include "Statement.h"

using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::stringstream;
using boost::format;


Text::Text()
{
}


Text::~Text()
{
}


void Text::process()
{
	for (auto & statement : statements) {
		try {
			statement.setAddress();
		} catch (AssembleException &e) {
			stringstream message;
			message << "[Error] Line " << statement.getLineNum() << ": ";
			message << e.what();
			throw AssembleException(message.str().c_str());
		}
	}

	for (auto & statement : statements) {
		try {
			uint32_t code = statement.toBinary();
			data.push_back(code);
		} catch (AssembleException &e) {
			stringstream message;
			message << "[Error] Line " << statement.getLineNum() << ": ";
			message << e.what();
			throw AssembleException(message.str().c_str());
		}
	}
}


void Text::setOutputType(Text::OutputType type)
{
	output_type = type;
}


istream & operator >> (istream & input, Text & text)
{
	int addr = 0;
	for (int line_num = 1; !input.eof(); line_num ++) {
		string line;
		getline(input, line);

		// remove comments
		size_t pos = std::min(line.find("#"), line.find("//"));
		if (pos != string::npos) {
			line = line.substr(0, pos);
		}

		// split line into tokens
		vector<string> tokens;
		boost::split(tokens, line, boost::is_any_of(";"), boost::token_compress_on);

		for (auto & token : tokens) {
			token = boost::trim_all_copy(token);
			if (!token.empty()) {
				text.statements.push_back(Statement(token, addr, line_num));
				addr += 4;
			}
		}
	}
	return input;
}


ostream& operator << (ostream & output, const Text& text)
{
	if (text.output_type == Text::coe) {
		text.outputCoe(output);
	} else if (text.output_type == Text::bin) {
		text.outputBin(output);
	}
	return output;
}


void Text::outputCoe(ostream & output) const
{
	output << "memory_initialization_radix=16;" << std::endl;
	output << "memory_initialization_vector=";
	for (auto & code : data) {
		output << boost::format("%08X") % code;
		if (&code == &data.back()) {
			output << ";";
		} else {
			output << ", ";
		}
	}
}


void Text::outputBin(ostream & output) const
{
	for (auto & code : data) {
		for (int i = 0; i < 4; i++) {
			uint8_t byte = (code >> ((3 - i) << 3)) & ((1 << 8) - 1);
			output.write((const char*)&byte, sizeof(uint8_t));
		}
	}
}

