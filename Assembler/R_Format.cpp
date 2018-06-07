#include "R_Format.h"

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "Instruction.h"
#include "Operand.h"

using std::map;
using std::string;
using std::stringstream;


R_Format::R_Format()
{
	// format: Instruction::rd, Instruction::rs, Instruction::rt
	instructions[string("add")] = Instruction(0, 0x20, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("addu")] = Instruction(0, 0x21, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("sub")] = Instruction(0, 0x22, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("subu")] = Instruction(0, 0x23, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("and")] = Instruction(0, 0x24, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("or")] = Instruction(0, 0x25, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("xor")] = Instruction(0, 0x26, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("nor")] = Instruction(0, 0x27, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("slt")] = Instruction(0, 0x2A, Instruction::rd, Instruction::rs, Instruction::rt);
	instructions[string("sltu")] = Instruction(0, 0x2B, Instruction::rd, Instruction::rs, Instruction::rt);

	// format: rd, rt, sa
	instructions[string("sll")] = Instruction(0, 0x0, Instruction::rd, Instruction::rt, Instruction::sa);
	instructions[string("srl")] = Instruction(0, 0x2, Instruction::rd, Instruction::rt, Instruction::sa);
	instructions[string("sra")] = Instruction(0, 0x3, Instruction::rd, Instruction::rt, Instruction::sa);

	// format: rs, rt
	instructions[string("mult")] = Instruction(0, 0x18, Instruction::rs, Instruction::rt, Instruction::none);
	instructions[string("multu")] = Instruction(0, 0x19, Instruction::rs, Instruction::rt, Instruction::none);
	instructions[string("div")] = Instruction(0, 0x1A, Instruction::rs, Instruction::rt, Instruction::none);
	instructions[string("divu")] = Instruction(0, 0x1B, Instruction::rs, Instruction::rt, Instruction::none);

	// jump
	instructions[string("jalr")] = Instruction(0, 0x9, Instruction::rd, Instruction::rs, Instruction::none);
	instructions[string("jr")] = Instruction(0, 0x8, Instruction::rs, Instruction::none, Instruction::none);

	// transfer
	instructions[string("mfhi")] = Instruction(0, 0x10, Instruction::rd, Instruction::none, Instruction::none);
	instructions[string("mflo")] = Instruction(0, 0x12, Instruction::rd, Instruction::none, Instruction::none);
	instructions[string("mthi")] = Instruction(0, 0x11, Instruction::rs, Instruction::none, Instruction::none);
	instructions[string("mtlo")] = Instruction(0, 0x13, Instruction::rs, Instruction::none, Instruction::none);

	// trap
	instructions[string("break")] = Instruction(0, 0xD, Instruction::none, Instruction::none, Instruction::none);
	instructions[string("syscall")] = Instruction(0, 0xC, Instruction::none, Instruction::none, Instruction::none);
}


R_Format::~R_Format()
{
}


uint32_t R_Format::convertToBinary(const string &operation, const vector<Operand> &operands)
{
	const Instruction &inst = instructions[operation];

	uint8_t reg_s = 0, reg_t = 0, reg_d = 0, shamt = 0;

	int operand_size = inst.getOperandSize();
	for (int i = 0; i < operand_size; i++) {
		const Operand &operand = operands[i];
		if (inst.type[i] == Instruction::rs) {
			reg_s = operand.asRegisterToInt();
		} else if (inst.type[i] == Instruction::rt) {
			reg_t = operand.asRegisterToInt();
		} else if (inst.type[i] == Instruction::rd) {
			reg_d = operand.asRegisterToInt();
		} else if (inst.type[i] == Instruction::sa) {
			shamt = operand.asImmediateToInt(5);
		}
	}

	return (inst.opcode << 26) | (reg_s << 21) | (reg_t << 16) | (reg_d << 11) | (shamt << 6) | (inst.funct);
}

