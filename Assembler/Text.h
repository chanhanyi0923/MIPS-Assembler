#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "Statement.h"

using std::istream;
using std::ostream;
using std::string;

class Text
{
public:
	enum OutputType { coe, bin };
private:
	OutputType output_type;
	vector<Statement> statements;
	vector<uint32_t> data;
public:
	Text();
	~Text();

	void process();
	void setOutputType(OutputType type);

	friend istream& operator >> (istream & input, Text& text);
	friend ostream& operator << (ostream & output, const Text& text);
	void outputCoe(ostream & output) const;
	void outputBin(ostream & output) const;
};

