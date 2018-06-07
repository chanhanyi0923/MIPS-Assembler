#include "Operand.h"

#include <utility>
#include <string>
#include <regex>
#include <boost/lexical_cast.hpp>

#include "AssembleException.h"
#include "RegisterList.h"
#include "Label.h"

Operand::Operand()
{
}


Operand::Operand(string s): data(s)
{
}



Operand::~Operand()
{
}


uint32_t Operand::setBit(uint32_t value, uint8_t bits)
{
	return value & ((1llu << bits) - 1);
}


uint32_t Operand::asImmediateToInt(int bits) const
{
	int value;

	try {
		value = boost::lexical_cast<int>(data);
	} catch (boost::bad_lexical_cast const&) {
		throw AssembleException("Invalid immediate operand.");
	}

	return setBit(value, bits);
}


pair<uint32_t, uint32_t> Operand::asImmediateAndRegisterToPair(int imm_bit) const
{
	std::smatch m;
	uint32_t imm, reg;
	if (regex_search(data, m, std::regex("^(.*)\\((.*?)\\)$"))) {
		Operand o1(m[1]), o2(m[2]);
		imm = o1.asImmediateToInt(imm_bit);
		reg = o2.asRegisterToInt();
	} else {
		throw AssembleException("Invalid immediate(register).");
	}
	return pair<int, int>(imm, reg);
}


uint8_t Operand::asRegisterToInt() const
{
	uint8_t value;
	const string * ptr;

	ptr = std::find(RegisterList::list_1, RegisterList::list_1 + 32, data);
	if (ptr != RegisterList::list_1 + 32) {
		value = (int)(ptr - RegisterList::list_1);
		return value;
	}

	ptr = std::find(RegisterList::list_2, RegisterList::list_2 + 32, data);
	if (ptr != RegisterList::list_2 + 32) {
		value = (int)(ptr - RegisterList::list_2);
		return value;
	}

	throw AssembleException("Invalid register");
}


int Operand::asLabelToInt(int bits) const
{
	int address = Label::getAddress(data);
	return setBit(address, bits);
}

