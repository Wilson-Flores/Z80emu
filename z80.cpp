#include "z80.hpp"
#include "Bus.hpp"


constexpr uint8_t BIT_MASK_1 = 0x38; // 0011 1000 binary value
constexpr uint8_t BIT_MASK_2 = 0x07; // 0000 0111 binary value

z80cpu::z80cpu() {
	using z = z80cpu;
	instruction_table = {
	{ "00", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "01", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "02", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "03", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "04", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "05", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "06", &z::LD, &z::register_addressing, &z::immediate_addressing, 7 },{ "07", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "08", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "09", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "0A", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "0B", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "0C", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "0D", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "0E", &z::LD, &z::register_addressing, &z::immediate_addressing, 7 },{ "0F", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "10", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "11", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "12", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "13", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "14", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "15", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "16", &z::LD, &z::register_addressing, &z::immediate_addressing, 7 },{ "17", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "18", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "19", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "1A", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "1B", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "1C", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "1D", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "1E", &z::LD, &z::register_addressing, &z::immediate_addressing, 7 },{ "1F", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "20", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "21", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "22", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "23", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "24", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "25", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "26", &z::LD, &z::register_addressing, &z::immediate_addressing, 7 },{ "27", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "28", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "29", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "2A", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "2B", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "2C", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "2D", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "2E", &z::LD, &z::register_addressing, &z::immediate_addressing, 7 },{ "2F", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "30", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "31", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "32", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "33", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "34", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "35", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "36", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "37", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "38", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "39", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "3A", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "3B", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "3C", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "3D", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "3E", &z::LD, &z::register_addressing, &z::immediate_addressing, 7 },{ "3F", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "40", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "41", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "42", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "43", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "44", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "45", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "46", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "47", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "48", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "49", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "4A", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "4B", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "4C", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "4D", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "4E", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "4F", &z::LD, &z::register_addressing, &z::register_addressing, 4 },
	{ "50", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "51", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "52", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "53", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "54", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "55", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "56", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "57", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "58", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "59", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "5A", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "5B", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "5C", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "5D", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "5E", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "5F", &z::LD, &z::register_addressing, &z::register_addressing, 4 },
	{ "60", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "61", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "62", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "63", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "64", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "65", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "66", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "67", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "68", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "69", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "6A", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "6B", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "6C", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "6D", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "6E", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "6F", &z::LD, &z::register_addressing, &z::register_addressing, 4 },
	{ "70", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "71", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "72", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "73", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "74", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "75", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "76", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "77", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "78", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "79", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "7A", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "7B", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "7C", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "7D", &z::LD, &z::register_addressing, &z::register_addressing, 4 },{ "7E", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "7F", &z::LD, &z::register_addressing, &z::register_addressing, 4 },
	{ "80", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "81", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "82", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "83", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "84", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "85", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "86", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "87", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "88", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "89", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "8A", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "8B", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "8C", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "8D", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "8E", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "8F", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "90", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "91", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "92", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "93", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "94", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "95", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "96", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "97", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "98", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "99", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "9A", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "9B", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "9C", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "9D", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "9E", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "9F", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "A0", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A1", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A2", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A3", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A4", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A5", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A6", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A7", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A8", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "A9", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "AA", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "AB", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "AC", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "AD", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "AE", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "AF", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "B0", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B1", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B2", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B3", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B4", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B5", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B6", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B7", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B8", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "B9", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "BA", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "BB", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "BC", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "BD", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "BE", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "BF", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "C0", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C1", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C2", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C3", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C4", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C5", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C6", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C7", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C8", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "C9", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "CA", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "CB", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "CC", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "CD", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "CE", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "CF", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "D0", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D1", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D2", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D3", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D4", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D5", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D6", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D7", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D8", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "D9", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "DA", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "DB", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "DC", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "DD", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "DE", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "DF", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "E0", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E1", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E2", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E3", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E4", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E5", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E6", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E7", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E8", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "E9", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "EA", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "EB", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "EC", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "ED", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "EE", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "EF", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },
	{ "F0", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F1", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F2", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F3", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F4", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F5", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F6", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F7", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F8", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "F9", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "FA", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "FB", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "FC", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "FD", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "FE", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 },{ "FF", &z::LD, &z::register_addressing, &z::immediate_addressing, 0 }};

	register_table = {
		&B_register, // 0b000
		&C_register, // 0b001
		&D_register, // 0b010
		&E_register, // 0b011
		&H_register, // 0b100
		&L_register, // 0b101
		nullptr,     // No register has 0b110 for a bit value
		&accumulator // 0b111
	};

}


uint8_t z80cpu::read(uint16_t address) {
	return bus->read(address);
}

void z80cpu::write(uint16_t address, uint8_t data) {
	bus->write(address, data);
}


void z80cpu::instruction_cycle() {
	// when t cycles reach 0, we are ready to read next instruction
		opcode = read(program_counter);

		// increment program counter
		program_counter++;
		
		// perform operation
		std::cout << "OPCODE: " << this->instruction_table[opcode].name << '\n';
		(this->*instruction_table[opcode].instruction)();
}


// Addressing Mode
uint8_t z80cpu::register_addressing() {
	std::cout << "Register Addressing Mode\n";
	return 0;
}

uint8_t z80cpu::immediate_addressing() {
	std::cout << "Immediate Addressing Mode\n";
	return 0;
}


// Instructions
uint8_t z80cpu::LD() {
	if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::register_addressing) {
		if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::immediate_addressing) {
			// bit mask the opcode to find the register value
			uint8_t destination_register_bit = (opcode & BIT_MASK_1) >> 3;

			*register_table[destination_register_bit] = read(program_counter);

			// Increment program counter again to avoid instruction cycle from mistaking 'n' value for an opcode
			program_counter++;
		}
		else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {
			// bit mask the opcode to find the register destination value and source register value
			uint8_t destination_register_bit = (opcode & BIT_MASK_1) >> 3;
			uint8_t source_register_bit = (opcode & BIT_MASK_2);

			*register_table[destination_register_bit] = *register_table[source_register_bit];
		}
		//else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_indirect_addressing) {

		//}
		//else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::implied_addressing) {

		//}
		//else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::indexed_addressing) {

		//}
		//else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::extended_addressing) {

		//}
	}
	//else if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::register_indirect_addressing) {
	//	if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::immediate_addressing) {

	//	}
	//	else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {

	//	}
	//}
	//else if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::indexed_addressing) {
	//	if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::immediate_addressing) {

	//	}
	//	else if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {

	//	}
	//}
	//else if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::extended_addressing) {
	//	if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {
	//	
	//	}
	//}
	//else if ((this->instruction_table[opcode].addressing_mode1) == &z80cpu::implied_addressing) {
	//	if ((this->instruction_table[opcode].addressing_mode2) == &z80cpu::register_addressing) {

	//	}
	//}

	return 0;
}


