#include "../z80.hpp"

//TODO: Fix SUB functions so it does the same as ADD but with 2s complement of data
void z80cpu::SUB_implied_register() {
    t_state_cycles = 4;

    uint8_t data = *register_table[opcode & BIT_MASK_2];
    uint8_t result = accumulator - data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);

    accumulator = result;
}


void z80cpu::SUB_implied_register_indirect() {
    t_state_cycles = 7;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);
    uint8_t result = accumulator - data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);

    accumulator = result;
}


void z80cpu::SUB_implied_indexed_ix() {
    t_state_cycles = 19;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint8_t result = accumulator - data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);

    accumulator = result;
}


void z80cpu::SUB_implied_indexed_iy() {
    t_state_cycles = 19;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint8_t result = accumulator - data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);

    accumulator = result;
}


void z80cpu::SUB_implied_immediate() {
    t_state_cycles = 7;

    uint8_t data = rom_read(program_counter);
    program_counter++;
    uint8_t result = accumulator - data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);

    accumulator = result;
}


void z80cpu::SBC_implied_register() {
    t_state_cycles = 4;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    uint8_t data = *register_table[opcode & BIT_MASK_2];
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG,((static_cast<uint16_t>(accumulator) ^ result)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::SBC_implied_register_indirect() {
    t_state_cycles = 7;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG,((static_cast<uint16_t>(accumulator) ^ result)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::SBC_implied_indexed_ix() {
    t_state_cycles = 19;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG,((static_cast<uint16_t>(accumulator) ^ result)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::SBC_implied_indexed_iy() {
    t_state_cycles = 19;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG,((static_cast<uint16_t>(accumulator) ^ result)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}

void z80cpu::SBC_implied_immediate() {
    t_state_cycles = 7;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    uint8_t data = rom_read(program_counter);
    program_counter++;
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG,((static_cast<uint16_t>(accumulator) ^ result)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}