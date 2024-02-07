#include "z80.hpp"
#include "Bus.hpp"


z80cpu::z80cpu() {
	using z = z80cpu;
	main_instruction_table = {
            {"00", nullptr }, {"01", &z::LD_register_immediate_extended_16_bit }, {"02", &z::LD_register_indirect_register }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", &z::LD_register_immediate }, {"07", nullptr }, {"08", nullptr }, {"09", nullptr }, {"0A", &z::LD_register_register_indirect }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", &z::LD_register_immediate }, {"0F", nullptr },
            {"10", nullptr }, {"11", &z::LD_register_immediate_extended_16_bit }, {"12", &z::LD_register_indirect_register }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", &z::LD_register_immediate }, {"17", nullptr }, {"18", nullptr }, {"19", nullptr }, {"1A", &z::LD_register_register_indirect }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", &z::LD_register_immediate }, {"1F", nullptr },
            {"20", nullptr }, {"21", &z::LD_register_immediate_extended_16_bit }, {"22", nullptr }, {"23", nullptr }, {"24", nullptr }, {"25", nullptr }, {"26", &z::LD_register_immediate }, {"27", nullptr }, {"28", nullptr }, {"29", nullptr }, {"2A", &z::LD_register_extended_hl }, {"2B", nullptr }, {"2C", nullptr }, {"2D", nullptr }, {"2E", &z::LD_register_immediate }, {"2F", nullptr },
            {"30", nullptr }, {"31", &z::LD_register_immediate_extended_16_bit }, {"32", &z::LD_extended_register }, {"33", nullptr }, {"34", nullptr }, {"35", nullptr }, {"36", &z::LD_register_indirect_immediate }, {"37", nullptr }, {"38", nullptr }, {"39", nullptr }, {"3A", &z::LD_register_extended }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", &z::LD_register_immediate }, {"3F", nullptr },
            {"40", &z::LD_register_register }, {"41", &z::LD_register_register }, {"42", &z::LD_register_register }, {"43", &z::LD_register_register }, {"44", &z::LD_register_register }, {"45", &z::LD_register_register }, {"46", &z::LD_register_register_indirect }, {"47", &z::LD_register_register }, {"48", &z::LD_register_register }, {"49", &z::LD_register_register }, {"4A", &z::LD_register_register }, {"4B", &z::LD_register_register }, {"4C", &z::LD_register_register }, {"4D", &z::LD_register_register }, {"4E", &z::LD_register_register_indirect }, {"4F", &z::LD_register_register },
            {"50", &z::LD_register_register }, {"51", &z::LD_register_register }, {"52", &z::LD_register_register }, {"53", &z::LD_register_register }, {"54", &z::LD_register_register }, {"55", &z::LD_register_register }, {"56", &z::LD_register_register_indirect }, {"57", &z::LD_register_register }, {"58", &z::LD_register_register }, {"59", &z::LD_register_register }, {"5A", &z::LD_register_register }, {"5B", &z::LD_register_register }, {"5C", &z::LD_register_register }, {"5D", &z::LD_register_register }, {"5E", &z::LD_register_register_indirect }, {"5F", &z::LD_register_register },
            {"60", &z::LD_register_register }, {"61", &z::LD_register_register }, {"62", &z::LD_register_register }, {"63", &z::LD_register_register }, {"64", &z::LD_register_register }, {"65", &z::LD_register_register }, {"66", &z::LD_register_register_indirect }, {"67", &z::LD_register_register }, {"68", &z::LD_register_register }, {"69", &z::LD_register_register }, {"6A", &z::LD_register_register }, {"6B", &z::LD_register_register }, {"6C", &z::LD_register_register }, {"6D", &z::LD_register_register }, {"6E", &z::LD_register_register_indirect }, {"6F", &z::LD_register_register },
            {"70", &z::LD_register_indirect_register }, {"71", &z::LD_register_indirect_register }, {"72", &z::LD_register_indirect_register }, {"73", &z::LD_register_indirect_register }, {"74", &z::LD_register_indirect_register }, {"75", &z::LD_register_indirect_register }, {"76", nullptr }, {"77", &z::LD_register_indirect_register }, {"78", &z::LD_register_register }, {"79", &z::LD_register_register }, {"7A", &z::LD_register_register }, {"7B", &z::LD_register_register }, {"7C", &z::LD_register_register }, {"7D", &z::LD_register_register }, {"7E", &z::LD_register_register_indirect }, {"7F", &z::LD_register_register },
            {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", nullptr }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", nullptr }, {"8F", nullptr },
            {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", nullptr }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", nullptr }, {"9F", nullptr },
            {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", nullptr }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", nullptr }, {"AF", nullptr },
            {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", nullptr }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", nullptr }, {"BF", nullptr },
            {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", nullptr }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
            {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", &z::ix_instructions }, {"DE", nullptr }, {"DF", nullptr },
            {"E0", nullptr }, {"E1", nullptr }, {"E2", nullptr }, {"E3", nullptr }, {"E4", nullptr }, {"E5", nullptr }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", &z::misc_instructions }, {"EE", nullptr }, {"EF", nullptr },
            {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", nullptr }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", &z::iy_instructions }, {"FE", nullptr }, {"FF", nullptr }
	};

	misc_instruction_table = {
		{ "00", nullptr },{ "01", nullptr },{ "02", nullptr },{ "03", nullptr },{ "04", nullptr },{ "05", nullptr },{ "06", nullptr },{ "07", nullptr },{ "08", nullptr },{ "09", nullptr },{ "0A", nullptr },{ "0B", nullptr },{ "0C", nullptr },{ "0D", nullptr },{ "0E", nullptr },{ "0F", nullptr },
		{ "10", nullptr },{ "11", nullptr },{ "12", nullptr },{ "13", nullptr },{ "14", nullptr },{ "15", nullptr },{ "16", nullptr },{ "17", nullptr },{ "18", nullptr },{ "19", nullptr },{ "1A", nullptr },{ "1B", nullptr },{ "1C", nullptr },{ "1D", nullptr },{ "1E", nullptr },{ "1F", nullptr },
		{ "20", nullptr },{ "21", nullptr },{ "22", nullptr },{ "23", nullptr },{ "24", nullptr },{ "25", nullptr },{ "26", nullptr },{ "27", nullptr },{ "28", nullptr },{ "29", nullptr },{ "2A", nullptr },{ "2B", nullptr },{ "2C", nullptr },{ "2D", nullptr },{ "2E", nullptr },{ "2F", nullptr },
		{ "30", nullptr },{ "31", nullptr },{ "32", nullptr },{ "33", nullptr },{ "34", nullptr },{ "35", nullptr },{ "36", nullptr },{ "37", nullptr },{ "38", nullptr },{ "39", nullptr },{ "3A", nullptr },{ "3B", nullptr },{ "3C", nullptr },{ "3D", nullptr },{ "3E", nullptr },{ "3F", nullptr },
		{ "40", nullptr },{ "41", nullptr },{ "42", nullptr },{ "43", nullptr },{ "44", nullptr },{ "45", nullptr },{ "46", nullptr },{ "47", &z::LD_implied_register },{ "48", nullptr },{ "49", nullptr },{ "4A", nullptr },{ "4B", &z::LD_register_extended_16_bit },{ "4C", nullptr },{ "4D", nullptr },{ "4E", nullptr },{ "4F", &z::LD_implied_register },
		{ "50", nullptr },{ "51", nullptr },{ "52", nullptr },{ "53", nullptr },{ "54", nullptr },{ "55", nullptr },{ "56", nullptr },{ "57", &z::LD_register_implied },{ "58", nullptr },{ "59", nullptr },{ "5A", nullptr },{ "5B", &z::LD_register_extended_16_bit },{ "5C", nullptr },{ "5D", nullptr },{ "5E", nullptr },{ "5F", &z::LD_register_implied },
		{ "60", nullptr },{ "61", nullptr },{ "62", nullptr },{ "63", nullptr },{ "64", nullptr },{ "65", nullptr },{ "66", nullptr },{ "67", nullptr },{ "68", nullptr },{ "69", nullptr },{ "6A", nullptr },{ "6B", &z::LD_register_extended_16_bit },{ "6C", nullptr },{ "6D", nullptr },{ "6E", nullptr },{ "6F", nullptr },
		{ "70", nullptr },{ "71", nullptr },{ "72", nullptr },{ "73", nullptr },{ "74", nullptr },{ "75", nullptr },{ "76", nullptr },{ "77", nullptr },{ "78", nullptr },{ "79", nullptr },{ "7A", nullptr },{ "7B", &z::LD_register_extended_16_bit },{ "7C", nullptr },{ "7D", nullptr },{ "7E", nullptr },{ "7F", nullptr },
		{ "80", nullptr },{ "81", nullptr },{ "82", nullptr },{ "83", nullptr },{ "84", nullptr },{ "85", nullptr },{ "86", nullptr },{ "87", nullptr },{ "88", nullptr },{ "89", nullptr },{ "8A", nullptr },{ "8B", nullptr },{ "8C", nullptr },{ "8D", nullptr },{ "8E", nullptr },{ "8F", nullptr },
		{ "90", nullptr },{ "91", nullptr },{ "92", nullptr },{ "93", nullptr },{ "94", nullptr },{ "95", nullptr },{ "96", nullptr },{ "97", nullptr },{ "98", nullptr },{ "99", nullptr },{ "9A", nullptr },{ "9B", nullptr },{ "9C", nullptr },{ "9D", nullptr },{ "9E", nullptr },{ "9F", nullptr },
		{ "A0", nullptr },{ "A1", nullptr },{ "A2", nullptr },{ "A3", nullptr },{ "A4", nullptr },{ "A5", nullptr },{ "A6", nullptr },{ "A7", nullptr },{ "A8", nullptr },{ "A9", nullptr },{ "AA", nullptr },{ "AB", nullptr },{ "AC", nullptr },{ "AD", nullptr },{ "AE", nullptr },{ "AF", nullptr },
		{ "B0", nullptr },{ "B1", nullptr },{ "B2", nullptr },{ "B3", nullptr },{ "B4", nullptr },{ "B5", nullptr },{ "B6", nullptr },{ "B7", nullptr },{ "B8", nullptr },{ "B9", nullptr },{ "BA", nullptr },{ "BB", nullptr },{ "BC", nullptr },{ "BD", nullptr },{ "BE", nullptr },{ "BF", nullptr } 
	};

	ix_instruction_table = {
		{ "00", nullptr },{ "01", nullptr },{ "02", nullptr },{ "03", nullptr },{ "04", nullptr },{ "05", nullptr },{ "06", nullptr },{ "07", nullptr },{ "08", nullptr },{ "09", nullptr },{ "0A", nullptr },{ "0B", nullptr },{ "0C", nullptr },{ "0D", nullptr },{ "0E", nullptr },{ "0F", nullptr },
		{ "10", nullptr },{ "11", nullptr },{ "12", nullptr },{ "13", nullptr },{ "14", nullptr },{ "15", nullptr },{ "16", nullptr },{ "17", nullptr },{ "18", nullptr },{ "19", nullptr },{ "1A", nullptr },{ "1B", nullptr },{ "1C", nullptr },{ "1D", nullptr },{ "1E", nullptr },{ "1F", nullptr },
		{ "20", nullptr },{ "21", &z::LD_register_immediate_extended_ix },{ "22", nullptr },{ "23", nullptr },{ "24", nullptr },{ "25", nullptr },{ "26", nullptr },{ "27", nullptr },{ "28", nullptr },{ "29", nullptr },{ "2A", &z::LD_register_extended_ix },{ "2B", nullptr },{ "2C", nullptr },{ "2D", nullptr },{ "2E", nullptr },{ "2F", nullptr },
		{ "30", nullptr },{ "31", nullptr },{ "32", nullptr },{ "33", nullptr },{ "34", nullptr },{ "35", nullptr },{ "36", &z::LD_indexed_ix_immediate },{ "37", nullptr },{ "38", nullptr },{ "39", nullptr },{ "3A", nullptr },{ "3B", nullptr },{ "3C", nullptr },{ "3D", nullptr },{ "3E", nullptr },{ "3F", nullptr },
		{ "40", nullptr },{ "41", nullptr },{ "42", nullptr },{ "43", nullptr },{ "44", nullptr },{ "45", nullptr },{ "46", &z::LD_register_indexed_ix },{ "47", nullptr },{ "48", nullptr },{ "49", nullptr },{ "4A", nullptr },{ "4B", nullptr },{ "4C", nullptr },{ "4D", nullptr },{ "4E", &z::LD_register_indexed_ix },{ "4F", nullptr },
		{ "50", nullptr },{ "51", nullptr },{ "52", nullptr },{ "53", nullptr },{ "54", nullptr },{ "55", nullptr },{ "56", &z::LD_register_indexed_ix },{ "57", nullptr },{ "58", nullptr },{ "59", nullptr },{ "5A", nullptr },{ "5B", nullptr },{ "5C", nullptr },{ "5D", nullptr },{ "5E", &z::LD_register_indexed_ix },{ "5F", nullptr },
		{ "60", nullptr },{ "61", nullptr },{ "62", nullptr },{ "63", nullptr },{ "64", nullptr },{ "65", nullptr },{ "66", &z::LD_register_indexed_ix },{ "67", nullptr },{ "68", nullptr },{ "69", nullptr },{ "6A", nullptr },{ "6B", nullptr },{ "6C", nullptr },{ "6D", nullptr },{ "6E", &z::LD_register_indexed_ix },{ "6F", nullptr },
		{ "70", &z::LD_indexed_ix_register },{ "71", &z::LD_indexed_ix_register },{ "72", &z::LD_indexed_ix_register },{ "73", &z::LD_indexed_ix_register },{ "74", &z::LD_indexed_ix_register },{ "75", &z::LD_indexed_ix_register},{ "76", nullptr },{ "77", &z::LD_indexed_ix_register },{ "78", nullptr },{ "79", nullptr },{ "7A", nullptr },{ "7B", nullptr },{ "7C", nullptr },{ "7D", nullptr },{ "7E", &z::LD_register_indexed_ix },{ "7F", nullptr },
		{ "80", nullptr },{ "81", nullptr },{ "82", nullptr },{ "83", nullptr },{ "84", nullptr },{ "85", nullptr },{ "86", nullptr },{ "87", nullptr },{ "88", nullptr },{ "89", nullptr },{ "8A", nullptr },{ "8B", nullptr },{ "8C", nullptr },{ "8D", nullptr },{ "8E", nullptr },{ "8F", nullptr },
		{ "90", nullptr },{ "91", nullptr },{ "92", nullptr },{ "93", nullptr },{ "94", nullptr },{ "95", nullptr },{ "96", nullptr },{ "97", nullptr },{ "98", nullptr },{ "99", nullptr },{ "9A", nullptr },{ "9B", nullptr },{ "9C", nullptr },{ "9D", nullptr },{ "9E", nullptr },{ "9F", nullptr },
		{ "A0", nullptr },{ "A1", nullptr },{ "A2", nullptr },{ "A3", nullptr },{ "A4", nullptr },{ "A5", nullptr },{ "A6", nullptr },{ "A7", nullptr },{ "A8", nullptr },{ "A9", nullptr },{ "AA", nullptr },{ "AB", nullptr },{ "AC", nullptr },{ "AD", nullptr },{ "AE", nullptr },{ "AF", nullptr },
		{ "B0", nullptr },{ "B1", nullptr },{ "B2", nullptr },{ "B3", nullptr },{ "B4", nullptr },{ "B5", nullptr },{ "B6", nullptr },{ "B7", nullptr },{ "B8", nullptr },{ "B9", nullptr },{ "BA", nullptr },{ "BB", nullptr },{ "BC", nullptr },{ "BD", nullptr },{ "BE", nullptr },{ "BF", nullptr },
		{ "C0", nullptr },{ "C1", nullptr },{ "C2", nullptr },{ "C3", nullptr },{ "C4", nullptr },{ "C5", nullptr },{ "C6", nullptr },{ "C7", nullptr },{ "C8", nullptr },{ "C9", nullptr },{ "CA", nullptr },{ "CB", nullptr },{ "CC", nullptr },{ "CD", nullptr },{ "CE", nullptr },{ "CF", nullptr },
		{ "D0", nullptr },{ "D1", nullptr },{ "D2", nullptr },{ "D3", nullptr },{ "D4", nullptr },{ "D5", nullptr },{ "D6", nullptr },{ "D7", nullptr },{ "D8", nullptr },{ "D9", nullptr },{ "DA", nullptr },{ "DB", nullptr },{ "DC", nullptr },{ "DD", nullptr },{ "DE", nullptr },{ "DF", nullptr },
		{ "E0", nullptr },{ "E1", nullptr },{ "E2", nullptr },{ "E3", nullptr },{ "E4", nullptr },{ "E5", nullptr },{ "E6", nullptr },{ "E7", nullptr },{ "E8", nullptr },{ "E9", nullptr },{ "EA", nullptr },{ "EB", nullptr },{ "EC", nullptr },{ "ED", nullptr },{ "EE", nullptr },{ "EF", nullptr },
		{ "F0", nullptr },{ "F1", nullptr },{ "F2", nullptr },{ "F3", nullptr },{ "F4", nullptr },{ "F5", nullptr },{ "F6", nullptr },{ "F7", nullptr },{ "F8", nullptr },{ "F9", nullptr },{ "FA", nullptr },{ "FB", nullptr },{ "FC", nullptr },{ "FD", nullptr },{ "FE", nullptr },{ "FF", nullptr }
	};

	iy_instruction_table = {
		{ "00", nullptr },{ "01", nullptr },{ "02", nullptr },{ "03", nullptr },{ "04", nullptr },{ "05", nullptr },{ "06", nullptr },{ "07", nullptr },{ "08", nullptr },{ "09", nullptr },{ "0A", nullptr },{ "0B", nullptr },{ "0C", nullptr },{ "0D", nullptr },{ "0E", nullptr },{ "0F", nullptr },
		{ "10", nullptr },{ "11", nullptr },{ "12", nullptr },{ "13", nullptr },{ "14", nullptr },{ "15", nullptr },{ "16", nullptr },{ "17", nullptr },{ "18", nullptr },{ "19", nullptr },{ "1A", nullptr },{ "1B", nullptr },{ "1C", nullptr },{ "1D", nullptr },{ "1E", nullptr },{ "1F", nullptr },
		{ "20", nullptr },{ "21", &z::LD_register_immediate_extended_iy },{ "22", nullptr },{ "23", nullptr },{ "24", nullptr },{ "25", nullptr },{ "26", nullptr },{ "27", nullptr },{ "28", nullptr },{ "29", nullptr },{ "2A", &z::LD_register_extended_iy },{ "2B", nullptr },{ "2C", nullptr },{ "2D", nullptr },{ "2E", nullptr },{ "2F", nullptr },
		{ "30", nullptr },{ "31", nullptr },{ "32", nullptr },{ "33", nullptr },{ "34", nullptr },{ "35", nullptr },{ "36", &z::LD_indexed_iy_immediate },{ "37", nullptr },{ "38", nullptr },{ "39", nullptr },{ "3A", nullptr },{ "3B", nullptr },{ "3C", nullptr },{ "3D", nullptr },{ "3E", nullptr },{ "3F", nullptr },
		{ "40", nullptr },{ "41", nullptr },{ "42", nullptr },{ "43", nullptr },{ "44", nullptr },{ "45", nullptr },{ "46", &z::LD_register_indexed_iy },{ "47", nullptr },{ "48", nullptr },{ "49", nullptr },{ "4A", nullptr },{ "4B", nullptr },{ "4C", nullptr },{ "4D", nullptr },{ "4E", &z::LD_register_indexed_iy },{ "4F", nullptr },
		{ "50", nullptr },{ "51", nullptr },{ "52", nullptr },{ "53", nullptr },{ "54", nullptr },{ "55", nullptr },{ "56", &z::LD_register_indexed_iy },{ "57", nullptr },{ "58", nullptr },{ "59", nullptr },{ "5A", nullptr },{ "5B", nullptr },{ "5C", nullptr },{ "5D", nullptr },{ "5E", &z::LD_register_indexed_iy },{ "5F", nullptr },
		{ "60", nullptr },{ "61", nullptr },{ "62", nullptr },{ "63", nullptr },{ "64", nullptr },{ "65", nullptr },{ "66", &z::LD_register_indexed_iy },{ "67", nullptr },{ "68", nullptr },{ "69", nullptr },{ "6A", nullptr },{ "6B", nullptr },{ "6C", nullptr },{ "6D", nullptr },{ "6E", &z::LD_register_indexed_iy },{ "6F", nullptr },
		{ "70", &z::LD_indexed_iy_register },{ "71", &z::LD_indexed_iy_register },{ "72", &z::LD_indexed_iy_register },{ "73", &z::LD_indexed_iy_register },{ "74", &z::LD_indexed_iy_register },{ "75", &z::LD_indexed_iy_register },{ "76", nullptr },{ "77", &z::LD_indexed_iy_register },{ "78", nullptr },{ "79", nullptr },{ "7A", nullptr },{ "7B", nullptr },{ "7C", nullptr },{ "7D", nullptr },{ "7E", &z::LD_register_indexed_iy },{ "7F", nullptr },
		{ "80", nullptr },{ "81", nullptr },{ "82", nullptr },{ "83", nullptr },{ "84", nullptr },{ "85", nullptr },{ "86", nullptr },{ "87", nullptr },{ "88", nullptr },{ "89", nullptr },{ "8A", nullptr },{ "8B", nullptr },{ "8C", nullptr },{ "8D", nullptr },{ "8E", nullptr },{ "8F", nullptr },
		{ "90", nullptr },{ "91", nullptr },{ "92", nullptr },{ "93", nullptr },{ "94", nullptr },{ "95", nullptr },{ "96", nullptr },{ "97", nullptr },{ "98", nullptr },{ "99", nullptr },{ "9A", nullptr },{ "9B", nullptr },{ "9C", nullptr },{ "9D", nullptr },{ "9E", nullptr },{ "9F", nullptr },
		{ "A0", nullptr },{ "A1", nullptr },{ "A2", nullptr },{ "A3", nullptr },{ "A4", nullptr },{ "A5", nullptr },{ "A6", nullptr },{ "A7", nullptr },{ "A8", nullptr },{ "A9", nullptr },{ "AA", nullptr },{ "AB", nullptr },{ "AC", nullptr },{ "AD", nullptr },{ "AE", nullptr },{ "AF", nullptr },
		{ "B0", nullptr },{ "B1", nullptr },{ "B2", nullptr },{ "B3", nullptr },{ "B4", nullptr },{ "B5", nullptr },{ "B6", nullptr },{ "B7", nullptr },{ "B8", nullptr },{ "B9", nullptr },{ "BA", nullptr },{ "BB", nullptr },{ "BC", nullptr },{ "BD", nullptr },{ "BE", nullptr },{ "BF", nullptr },
		{ "C0", nullptr },{ "C1", nullptr },{ "C2", nullptr },{ "C3", nullptr },{ "C4", nullptr },{ "C5", nullptr },{ "C6", nullptr },{ "C7", nullptr },{ "C8", nullptr },{ "C9", nullptr },{ "CA", nullptr },{ "CB", nullptr },{ "CC", nullptr },{ "CD", nullptr },{ "CE", nullptr },{ "CF", nullptr },
		{ "D0", nullptr },{ "D1", nullptr },{ "D2", nullptr },{ "D3", nullptr },{ "D4", nullptr },{ "D5", nullptr },{ "D6", nullptr },{ "D7", nullptr },{ "D8", nullptr },{ "D9", nullptr },{ "DA", nullptr },{ "DB", nullptr },{ "DC", nullptr },{ "DD", nullptr },{ "DE", nullptr },{ "DF", nullptr },
		{ "E0", nullptr },{ "E1", nullptr },{ "E2", nullptr },{ "E3", nullptr },{ "E4", nullptr },{ "E5", nullptr },{ "E6", nullptr },{ "E7", nullptr },{ "E8", nullptr },{ "E9", nullptr },{ "EA", nullptr },{ "EB", nullptr },{ "EC", nullptr },{ "ED", nullptr },{ "EE", nullptr },{ "EF", nullptr },
		{ "F0", nullptr },{ "F1", nullptr },{ "F2", nullptr },{ "F3", nullptr },{ "F4", nullptr },{ "F5", nullptr },{ "F6", nullptr },{ "F7", nullptr },{ "F8", nullptr },{ "F9", nullptr },{ "FA", nullptr },{ "FB", nullptr },{ "FC", nullptr },{ "FD", nullptr },{ "FE", nullptr },{ "FF", nullptr }
	};


	register_table = {
		&B_register, // B = 0b000
		&C_register, // C = 0b001
		&D_register, // D = 0b010
		&E_register, // E = 0b011
		&H_register, // H = 0b100
		&L_register, // L = 0b101
		nullptr,     // No register has 0b110 for a bit value
		&accumulator // A = 0b111
	};

    register_pair_table = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {&H_register, &L_register}  // HL = 0b10
    };

}


uint8_t z80cpu::read(uint16_t address) {
	return bus->read(address);
}


void z80cpu::write(uint16_t address, uint8_t data) {
	bus->write(address, data);
}


void z80cpu::set_flag(FLAGSZ80 flag, bool set_flag) {
	if (set_flag) {
		flag_register |= flag;
	}
	else {
		flag_register &= ~flag;
	}
}


void z80cpu::memory_refresh_counter() {
	if (((memory_refresh_register + 1) & 0x7F) < 0x7F) {
		memory_refresh_register++;
	}
	else {
		memory_refresh_register &= 0x80;
	}
}


void z80cpu::instruction_cycle() {
	// when t cycles reach 0, we are ready to read next instruction
	opcode = read(program_counter);

	//memory refresh register increments after pulling an opcode
	memory_refresh_counter();

	// increment program counter
	program_counter++;

	// begin going through the main instruction table
	std::cout << "OPCODE: " << this->main_instruction_table[opcode].opcode << '\n';
	(this->*main_instruction_table[opcode].instruction)();
}


// Function Tables
void z80cpu::misc_instructions() {
	opcode = read(program_counter);
	memory_refresh_counter();
	program_counter++;

	std::cout << "OPCODE: " << this->misc_instruction_table[opcode].opcode << '\n';
	(this->*misc_instruction_table[opcode].instruction)();
}


void z80cpu::ix_instructions() {
    opcode = read(program_counter);
    memory_refresh_counter();
    program_counter++;

    std::cout << "OPCODE: " << this->ix_instruction_table[opcode].opcode << '\n';
    (this->*iy_instruction_table[opcode].instruction)();
}


void z80cpu::iy_instructions() {
    opcode = read(program_counter);
    memory_refresh_counter();
    program_counter++;

    std::cout << "OPCODE: " << this->iy_instruction_table[opcode].opcode << '\n';
    (this->*iy_instruction_table[opcode].instruction)();
}