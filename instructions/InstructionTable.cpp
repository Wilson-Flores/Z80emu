#include "InstructionTable.hpp"


// Function Tables
void misc_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*misc_instruction_table[opcode].instruction)();
}


void ix_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*ix_instruction_table[opcode].instruction)();
}


void iy_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*iy_instruction_table[opcode].instruction)();
}

void bit_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*bit_instruction_table[opcode].instruction)();
}


void ix_bit_instructions() {
    // DDCB opcodes have a displacement value placed before the final opcode
    // ex DD CB d 06
    displacement = rom_read(program_counter);
    program_counter++;

    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*ix_bit_instruction_table[opcode].instruction)();
}


void iy_bit_instructions() {
    displacement = rom_read(program_counter);
    program_counter++;

    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*iy_bit_instruction_table[opcode].instruction)();
}

