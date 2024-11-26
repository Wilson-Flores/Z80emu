#include "z80.hpp"
#include "Bus.hpp"
#include "instructions/InstructionTable.hpp"


z80cpu::z80cpu() {
    register_table_ = {
		&B_register_, // B = 0b000
		&C_register_, // C = 0b001
		&D_register_, // D = 0b010
		&E_register_, // E = 0b011
		&H_register_, // H = 0b100
		&L_register_, // L = 0b101
		nullptr,     // No register has 0b110 for a bit value
		&accumulator_ // A = 0b111
	};

    alt_register_table_ = {
        &alt_B_register_,
        &alt_C_register_,
        &alt_D_register_,
        &alt_E_register_,
        &alt_H_register_,
        &alt_L_register_,
        nullptr,
        &alt_accumulator_
    };

    register_pair_table_qq_ = {
            {&B_register_,  &C_register_},                                   // BC = 0b00
            {&D_register_,  &E_register_},                                   // DE = 0b01
            {&H_register_,  &L_register_},                                   // HL = 0b10
            {&accumulator_, &flag_register_}                                // AF = 0b11
    };

    register_pair_table_ss_ = {
            {&B_register_, &C_register_},                                   // BC = 0b00
            {&D_register_, &E_register_},                                   // DE = 0b01
            {&H_register_, &L_register_},                                   // HL = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer_) + 1,
                           reinterpret_cast<uint8_t*>(&stack_pointer_)}                  // SP = 0b11
    };

    register_pair_table_pp_ = {
            {&B_register_, &C_register_},                                   // BC = 0b00
            {&D_register_, &E_register_},                                   // DE = 0b01
            {reinterpret_cast<uint8_t*>(&index_register_x_) + 1,
                           reinterpret_cast<uint8_t*>(&index_register_x_)},       // IX = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer_) + 1,
                           reinterpret_cast<uint8_t*>(&stack_pointer_)}     // SP = 0b11
    };

    register_pair_table_rr_ = {
            {&B_register_, &C_register_},                                   // BC = 0b00
            {&D_register_, &E_register_},                                   // DE = 0b01
            {reinterpret_cast<uint8_t*>(&index_register_y_) + 1,
                           reinterpret_cast<uint8_t*>(&index_register_y_)}, // IY = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer_) + 1,
                           reinterpret_cast<uint8_t*>(&stack_pointer_)}     // SP = 0b11
    };
}


uint8_t z80cpu::rom_read(uint16_t address) {
	return bus_->rom_read(address);
}


void z80cpu::rom_write(uint16_t address, uint8_t data) {
    bus_->rom_write(address, data);
}


void z80cpu::set_flag(FLAGSZ80 flag, bool set_flag) {
	if (set_flag) {
        flag_register_ |= flag;
	}
	else {
        flag_register_ &= ~flag;
	}
}


uint8_t z80cpu::get_flag(FLAGSZ80 flag) const {
    return ((flag_register_ & flag) > 0) ? 1 : 0;
}


void z80cpu::memory_refresh_counter() {
	if (((memory_refresh_register_ + 1) & PARITY_REG_VALUE) < PARITY_REG_VALUE) {
		memory_refresh_register_++;
	}
	else {
        memory_refresh_register_ &= BIT_MASK_9;
	}
}


void z80cpu::fetch_opcode() {
    opcode_ = rom_read(program_counter_);
    program_counter_++;
    memory_refresh_counter();
}


void z80cpu::instruction_cycle() {
    fetch_opcode();
    (this->*main_instruction_table[opcode_].instruction)();
}


// Function Tables
void z80cpu::misc_instructions() {
    fetch_opcode();
	(this->*misc_instruction_table[opcode_].instruction)();
}


void z80cpu::ix_instructions() {
    fetch_opcode();
    (this->*ix_instruction_table[opcode_].instruction)();
}


void z80cpu::iy_instructions() {
    fetch_opcode();
    (this->*iy_instruction_table[opcode_].instruction)();
}


void z80cpu::bit_instructions() {
    fetch_opcode();
    (this->*bit_instruction_table[opcode_].instruction)();
}


void z80cpu::ix_bit_instructions() {
    // DDCB opcodes have a displacement value placed before the final opcode
    // ex DD CB d 06
    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    fetch_opcode();
    (this->*ix_bit_instruction_table[opcode_].instruction)();
}


void z80cpu::iy_bit_instructions() {
    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    fetch_opcode();
    (this->*iy_bit_instruction_table[opcode_].instruction)();
}


void z80cpu::reset() {
    // General Purpose Registers
    accumulator_ = 0x00;
    B_register_ = 0x00;
    C_register_ = 0x00;
    D_register_ = 0x00;
    E_register_ = 0x00;
    H_register_ = 0x00;
    L_register_ = 0x00;
    flag_register_ = 0x00;

    // Alternate Registers
    alt_accumulator_ = 0x00;
    alt_B_register_ = 0x00;
    alt_C_register_ = 0x00;
    alt_D_register_ = 0x00;
    alt_E_register_ = 0x00;
    alt_H_register_ = 0x00;
    alt_L_register_ = 0x00;
    alt_flag_register_ = 0x00;

    // Index Registers
    index_register_x_ = 0x0000;
    index_register_y_ = 0x0000;

    // Other Registers
    interrupt_vector_register_ = 0x00;
    memory_refresh_register_ = 0x00;
    stack_pointer_ = 0x0000;
    program_counter_ = 0x0000;
    WZ_register_ = 0x0000;
    opcode_ = 0x00;
    t_state_cycles_ = 0x00;

    // Temporary Values
    temp_displacement_ = 0x00;
    temp_data_8_ = 0;
    temp_result_8_ = 0;
    temp_data_16_ = 0;
    temp_result_16_ = 0;

    // Interrupts
    interrupt_enable_flip_flop_1_ = false;
    interrupt_enable_flip_flop_2_ = false;
}


const uint8_t& z80cpu::get_flag_register_address() const { return flag_register_; }
const uint8_t& z80cpu::get_accumulator_address() const { return accumulator_; }
const uint8_t& z80cpu::get_registerB_address() const { return B_register_; }
const uint8_t& z80cpu::get_registerC_address() const { return C_register_; }
const uint8_t& z80cpu::get_registerD_address() const { return D_register_; }
const uint8_t& z80cpu::get_registerE_address() const { return E_register_; }
const uint8_t& z80cpu::get_registerH_address() const { return H_register_; }
const uint8_t& z80cpu::get_registerL_address() const { return L_register_; }
const uint8_t& z80cpu::get_interrupt_vector_address() const { return interrupt_vector_register_; }
const uint8_t& z80cpu::get_memory_refresh_address() const { return memory_refresh_register_; }
const uint16_t& z80cpu::get_regIX_address() const {return index_register_x_; }
const uint16_t& z80cpu::get_regIY_address() const {return index_register_y_; }


const uint8_t& z80cpu::get_opcode_address() const { return opcode_; }