#include "z80.hpp"


z80cpu::~z80cpu() {
	using z = z80cpu;
	instruction_table = {};

}



uint8_t z80cpu::LD() {
	if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::register_addressing) {
		if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::immediate_addressing) {

		}
		else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {

		}
		else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_indirect_addressing) {

		}
		else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::implied_addressing) {

		}
		else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::indexed_addressing) {

		}
		else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::extended_addressing) {

		}
	}
	else if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::register_indirect_addressing) {
		if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::immediate_addressing) {

		}
		else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {

		}
	}
	else if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::indexed_addressing) {
		if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::immediate_addressing) {

		}
		else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {

		}
	}
	else if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::extended_addressing) {
		if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {
		
		}
	}
	else if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::implied_addressing) {
		if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {

		}
	}

	return 0;
}


