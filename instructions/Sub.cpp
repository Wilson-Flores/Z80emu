#include "../z80.hpp"

void z80cpu::SUB_register_register() {
    t_state_cycles = 4;

    // convert data using 2s complement then reuse ADD procedure.
    uint8_t data = ~(*register_table[opcode & BIT_MASK_2]) + 0x01;
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    uint8_t h_result = (accumulator & 0x0F) + (data & 0x0F);
    set_flag(HALF_CARRY_FLAG, h_result > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::SUB_register_register_indirect() {
    t_state_cycles = 7;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ~(ram_read(address_absolute)) + 0x01;
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    uint8_t h_result = (accumulator & 0x0F) + (data & 0x0F);
    set_flag(HALF_CARRY_FLAG, h_result > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::SUB_register_indexed_ix() {
    t_state_cycles = 19;

    int8_t displacement;
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    uint8_t data = ~(ram_read(address_absolute)) + 0x01;
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    uint8_t h_result = (accumulator & 0x0F) + (data & 0x0F);
    set_flag(HALF_CARRY_FLAG, h_result > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::SUB_register_indexed_iy() {
    t_state_cycles = 19;

    int8_t displacement;
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    uint8_t data = ~(ram_read(address_absolute)) + 0x01;
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    uint8_t h_result = (accumulator & 0x0F) + (data & 0x0F);
    set_flag(HALF_CARRY_FLAG, h_result > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::SUB_register_immediate() {
    t_state_cycles = 7;

    uint8_t data = ~(rom_read(program_counter)) + 0x01;
    program_counter++;
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    uint8_t h_result = (accumulator & 0x0F) + (data & 0x0F);
    set_flag(HALF_CARRY_FLAG, h_result > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}