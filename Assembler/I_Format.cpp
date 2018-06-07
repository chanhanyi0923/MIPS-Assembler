#include "I_Format.h"

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

#include "Instruction.h"
#include "Operand.h"
#include "Label.h"

using std::map;
using std::string;
using std::stringstream;
using std::pair;


I_Format::I_Format()
{
	// format: rt, imm(rs)
	instructions[string("lw")] = Instruction(0x23, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("lb")] = Instruction(0x20, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("lbu")] = Instruction(0x24, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("lh")] = Instruction(0x21, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("lhu")] = Instruction(0x25, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("sw")] = Instruction(0x2B, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("sb")] = Instruction(0x28, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);
	instructions[string("sh")] = Instruction(0x29, 0, Instruction::rt, Instruction::imm_rs, Instruction::none);

	// format: rt, rs, imm
	instructions[string("addi")] = Instruction(0x8, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("addiu")] = Instruction(0x9, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("andi")] = Instruction(0xC, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("ori")] = Instruction(0xD, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("xori")] = Instruction(0xE, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("slti")] = Instruction(0xA, 0, Instruction::rt, Instruction::rs, Instruction::imm);
	instructions[string("sltiu")] = Instruction(0xB, 0, Instruction::rt, Instruction::rs, Instruction::imm);

	// format: rt, imm
	instructions[string("lui")] = Instruction(0xF, 0, Instruction::rt, Instruction::imm, Instruction::none);

	// format: rs, rt, label
	instructions[string("beq")] = Instruction(0x4, 0, Instruction::rs, Instruction::rt, Instruction::label);
	instructions[string("bne")] = Instruction(0x5, 0, Instruction::rs, Instruction::rt, Instruction::label);

	// format: rs, label
	instructions[string("blez")] = Instruction(0x6, 0, Instruction::rs, Instruction::label, Instruction::none);
	instructions[string("bgtz")] = Instruction(0x7, 0, Instruction::rs, Instruction::label, Instruction::none);
	instructions[string("bltz")] = Instruction(0x1, 0, Instruction::rs, Instruction::label, Instruction::none);
	instructions[string("bgez")] = Instruction(0x1, 0, Instruction::rs, Instruction::label, Instruction::none);
}


I_Format::~I_Format()
{
}


uint32_t I_Format::convertToBinary(const string &operation, const vector<Operand> &operands, int address)
{
	const Instruction &inst = instructions[operation];

	uint8_t reg_s = 0, reg_t = 0;
	uint16_t immediate = 0;

	if (operation == string("bgez")) {
		reg_t = 1;
	} else if (operation == string("bltz")) {
		reg_t = 0;
	}

	int operand_size = inst.getOperandSize();
	for (int i = 0; i < operand_size; i++) {
		const Operand &operand = operands[i];
		if (inst.type[i] == Instruction::rs) {
			reg_s = operand.asRegisterToInt();
		} else if (inst.type[i] == Instruction::rt) {
			reg_t = operand.asRegisterToInt();
		} else if (inst.type[i] == Instruction::imm_rs) {
			pair<uint32_t, uint32_t> pii = operand.asImmediateAndRegisterToPair(16);
			immediate = pii.first;
			reg_s = pii.second;
		} else if (inst.type[i] == Instruction::label) {
			int label_address = operand.asLabelToInt(32);
			immediate = ((label_address - address) >> 2) - 1;
		} else if (inst.type[i] == Instruction::imm) {
			immediate = operand.asImmediateToInt(16);
		}
	}

	return (inst.opcode << 26) | (reg_s << 21) | (reg_t << 16) | (immediate);
}

