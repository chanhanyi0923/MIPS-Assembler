#include "J_Format.h"

#include "Operand.h"
#include "Label.h"

J_Format::J_Format()
{
	instructions[string("j")] = Instruction(0x2, 0, Instruction::label, Instruction::none, Instruction::none);
	instructions[string("jal")] = Instruction(0x3, 0, Instruction::label, Instruction::none, Instruction::none);
}


J_Format::~J_Format()
{
}


uint32_t J_Format::convertToBinary(const string &operation, const vector<Operand> &operands)
{
	Instruction inst = instructions[operation];

	uint32_t immediate;

	int operand_size = inst.getOperandSize();
	for (int i = 0; i < operand_size; i++) {
		const Operand &operand = operands[i];
		if (inst.type[i] == Instruction::label) {
			int label_address = operand.asLabelToInt(28);
			immediate = label_address >> 2;
		}
	}

	return (inst.opcode << 26) | immediate;
}

