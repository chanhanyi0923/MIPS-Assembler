#pragma once

#include <string>
#include <utility>

using std::string;
using std::pair;

class Operand
{
	string data;
public:
	Operand();
	Operand(string s);
	~Operand();

	static uint32_t setBit(uint32_t value, uint8_t bits);
	uint8_t asRegisterToInt() const;
	uint32_t asImmediateToInt(int bits) const;
	int asLabelToInt(int bits) const;
	pair<uint32_t, uint32_t> asImmediateAndRegisterToPair(int imm_bit) const;
};

