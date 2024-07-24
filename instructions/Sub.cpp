#include "../z80.hpp"

void z80cpu::SUB_implied_register() {
    t_state_cycles = 4;

    data_8 = *register_table[opcode & BIT_MASK_2];
    result_8 = accumulator - data_8;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data_8 & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator ^ (accumulator + (~data_8 + 0x01))) & ~(accumulator ^ (~data_8 + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data_8);

    accumulator = result_8;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SUB_implied_register_indirect() {
    t_state_cycles = 7;

    WZ_register = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data_8 = ram_read(WZ_register);
    result_8 = accumulator - data_8;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data_8 & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator ^ (accumulator + (~data_8 + 0x01))) & ~(accumulator ^ (~data_8 + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data_8);

    accumulator = result_8;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SUB_implied_indexed_ix() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    WZ_register = index_register_x + static_cast<int16_t>(displacement);
    data_8 = ram_read(WZ_register);
    result_8 = accumulator - data_8;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data_8 & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator ^ (accumulator + (~data_8 + 0x01))) & ~(accumulator ^ (~data_8 + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data_8);

    accumulator = result_8;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SUB_implied_indexed_iy() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    WZ_register = index_register_y + static_cast<int16_t>(displacement);
    data_8 = ram_read(WZ_register);
    result_8 = accumulator - data_8;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data_8 & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator ^ (accumulator + (~data_8 + 0x01))) & ~(accumulator ^ (~data_8 + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data_8);

    accumulator = result_8;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SUB_implied_immediate() {
    t_state_cycles = 7;

    data_8 = rom_read(program_counter);
    program_counter++;
    result_8 = accumulator - data_8;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (data_8 & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator ^ (accumulator + (~data_8 + 0x01))) & ~(accumulator ^ (~data_8 + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data_8);

    accumulator = result_8;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SBC_implied_register() {
    t_state_cycles = 4;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    data_8 = *register_table[opcode & BIT_MASK_2];
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data_8) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    // this flag works differently compared to ADC, borrow will always occur when the data is bigger than the accumulator.
    // this time we include the carry flag. using A - D - C -> A - (D + C) -> A < (D + C)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data_8 & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data_8))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = static_cast<uint8_t>(result_16);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SBC_implied_register_indirect() {
    t_state_cycles = 7;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    WZ_register = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data_8 = ram_read(WZ_register);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data_8) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data_8 & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data_8))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = static_cast<uint8_t>(result_16);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SBC_implied_indexed_ix() {
    t_state_cycles = 19;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    WZ_register = index_register_x + static_cast<int16_t>(displacement);
    data_8 = ram_read(WZ_register);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data_8) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data_8 & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data_8))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = static_cast<uint8_t>(result_16);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SBC_implied_indexed_iy() {
    t_state_cycles = 19;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    WZ_register = index_register_y + static_cast<int16_t>(displacement);
    data_8 = ram_read(WZ_register);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data_8) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data_8 & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data_8))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = static_cast<uint8_t>(result_16);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}

void z80cpu::SBC_implied_immediate() {
    t_state_cycles = 7;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    data_8 = rom_read(program_counter);
    program_counter++;
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(~data_8) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < ((data_8 & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16)
    & ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(~data_8))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = static_cast<uint8_t>(result_16);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::SBC_implied_register_extended() {
    t_state_cycles = 15;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = (high_byte << 8) + low_byte;
    data_16 = (H_register << 8) + L_register;

    uint32_t result_32 = static_cast<uint32_t>(data_16) + static_cast<uint32_t>(~register_pair_data) +
                         static_cast<uint32_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, static_cast<uint16_t>(result_32) & 0x8000);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, static_cast<uint16_t>(result_32) == 0x0000);
    // H is set if borrow from bit 12, else reset
    set_flag(HALF_CARRY_FLAG, (data_16 & 0x0FFF) < ((register_pair_data & 0x0FFF) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint32_t>(data_16) ^ result_32)
    & ~(static_cast<uint32_t>(data_16) ^ static_cast<uint32_t>(~register_pair_data))) & 0x00008000);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow, else reset
    set_flag(CARRY_FLAG, result_32 > 0xFFFF);

    H_register = (static_cast<uint16_t>(result_32) & 0xFF00) >> 8;
    L_register = static_cast<uint16_t>(result_32) & 0x00FF;

    //X & Y Flags are copies bit 3 & 5 of the high byte (H register)
    set_flag(X_FLAG, H_register & 0x08);
    set_flag(Y_FLAG, H_register & 0x20);
}