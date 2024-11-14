#include "z80.hpp"
#include "Bus.hpp"
#include "instructions/InstructionTable.hpp"


z80cpu::z80cpu() {
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

    alt_register_table = {
        &alt_B_register,
        &alt_C_register,
        &alt_D_register,
        &alt_E_register,
        &alt_H_register,
        &alt_L_register,
        nullptr,
        &alt_accumulator
    };

    register_pair_table_qq = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {&H_register, &L_register}, // HL = 0b10
            {&accumulator, &flag_register} // AF = 0b11
    };

    register_pair_table_ss = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {&H_register, &L_register}, // HL = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer) + 1,
             reinterpret_cast<uint8_t*>(&stack_pointer)} // SP = 0b11
    };

    register_pair_table_pp = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {reinterpret_cast<uint8_t*>(&index_register_x) + 1,
                    reinterpret_cast<uint8_t*>(&index_register_x)}, // IX = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer) + 1,
                          reinterpret_cast<uint8_t*>(&stack_pointer)} // SP = 0b11
    };

    register_pair_table_rr = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {reinterpret_cast<uint8_t*>(&index_register_y) + 1,
                          reinterpret_cast<uint8_t*>(&index_register_y)}, // IY = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer) + 1,
                          reinterpret_cast<uint8_t*>(&stack_pointer)} // SP = 0b11
    };
}


uint8_t z80cpu::rom_read(uint16_t address) {
	return bus->rom_read(address);
}


uint8_t z80cpu::ram_read(uint16_t address) {
    return bus->ram_read(address);
}


void z80cpu::ram_write(uint16_t address, uint8_t data) {
    bus->ram_write(address, data);
}


void z80cpu::set_flag(FLAGSZ80 flag, bool set_flag) {
	if (set_flag) {
		flag_register |= flag;
	}
	else {
		flag_register &= ~flag;
	}
}

uint8_t z80cpu::get_flag(FLAGSZ80 flag) const {
    return ((flag_register & flag) > 0) ? 1 : 0;
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
	opcode = rom_read(program_counter);

    // increment program counter
    program_counter++;

	//memory refresh register increments after pulling an opcode
	memory_refresh_counter();

	// begin going through the main instruction table
    (this->*main_instruction_table[opcode].instruction)();
}


// Function Tables
void z80cpu::misc_instructions() {
	opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

	(this->*misc_instruction_table[opcode].instruction)();
}


void z80cpu::ix_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*ix_instruction_table[opcode].instruction)();
}


void z80cpu::iy_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*iy_instruction_table[opcode].instruction)();
}

void z80cpu::bit_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*bit_instruction_table[opcode].instruction)();
}


void z80cpu::ix_bit_instructions() {
    // DDCB opcodes have a displacement value placed before the final opcode
    // ex DD CB d 06
    displacement = rom_read(program_counter);
    program_counter++;

    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*ix_bit_instruction_table[opcode].instruction)();
}


void z80cpu::iy_bit_instructions() {
    displacement = rom_read(program_counter);
    program_counter++;

    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*iy_bit_instruction_table[opcode].instruction)();
}

void z80cpu::reset() {
    // General Purpose Registers
    accumulator = 0x00;
    B_register = 0x00;
    C_register = 0x00;
    D_register = 0x00;
    E_register = 0x00;
    H_register = 0x00;
    L_register = 0x00;
    flag_register = 0x00;

    // Alternate Registers
    alt_accumulator = 0x00;
    alt_B_register = 0x00;
    alt_C_register = 0x00;
    alt_D_register = 0x00;
    alt_E_register = 0x00;
    alt_H_register = 0x00;
    alt_L_register = 0x00;
    alt_flag_register = 0x00;

    // Index Registers
    index_register_x = 0x0000;
    index_register_y = 0x0000;

    // Other Registers
    interrupt_vector_register = 0x00;
    memory_refresh_register = 0x00;
    stack_pointer = 0x0000;
    program_counter = 0x0000;
    WZ_register = 0x0000;
    opcode = 0x00;
    t_state_cycles = 0x00;

    // Temporary Values
    displacement = 0x00;
    data_8 = 0;
    result_8 = 0;
    data_16 = 0;
    result_16 = 0;

    // Interrupts
    interrupt_enable_flip_flop_1 = false;
    interrupt_enable_flip_flop_2 = false;
}

const uint8_t& z80cpu::get_flag_register_address() const { return flag_register; }
const uint8_t& z80cpu::get_accumulator_address() const { return accumulator; }
const uint8_t& z80cpu::get_registerB_address() const { return B_register; }
const uint8_t& z80cpu::get_registerC_address() const { return C_register; }
const uint8_t& z80cpu::get_registerD_address() const { return D_register; }
const uint8_t& z80cpu::get_registerE_address() const { return E_register; }
const uint8_t& z80cpu::get_registerH_address() const { return H_register; }
const uint8_t& z80cpu::get_registerL_address() const { return L_register; }


const uint8_t& z80cpu::get_opcode_address() const { return opcode; }