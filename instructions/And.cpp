#include "../z80.hpp"


void z80cpu::AND_implied_register() {
    t_state_cycles = 4;

    data = *register_table[opcode & BIT_MASK_2];
    accumulator &= data;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);
}


void z80cpu::AND_implied_register_indirect() {
    t_state_cycles = 7;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data = ram_read(address_absolute);
    accumulator &= data;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);
}

void z80cpu::AND_implied_indexed_ix() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    data = ram_read(address_absolute);
    accumulator &= data;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);
}


void z80cpu::AND_implied_indexed_iy() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    data = ram_read(address_absolute);
    accumulator &= data;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);
}

void z80cpu::AND_implied_immediate() {
    t_state_cycles = 7;

    data = rom_read(program_counter);
    program_counter++;
    accumulator &= data;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);
}