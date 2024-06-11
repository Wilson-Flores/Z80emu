#include "../z80.hpp"


void z80cpu::RLCA_implied() {
    t_state_cycles = 4;

    // isolate leading bit in accumulator, then overwrite the carry bit in the flag register.
    // first we clear out the carry bit in the flag register,
    // then we do an or operation to copy the accumulator bit into the carry bit
    flag_register &= 0xFE;
    flag_register |= (accumulator >> 7);

    // rotate accumulator bits 1 to the left, then add 7th bit
    accumulator = (accumulator << 1) + (accumulator >> 7);

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of Accumulator
}


void z80cpu::RLC_implied() {
    t_state_cycles = 8;

    // copy the data from the register
    data = *register_table[opcode & BIT_MASK_2];

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);
    // rotate data bits and save back into register
    result = (data << 1) + (data >> 7);
    *register_table[opcode & BIT_MASK_2] = result;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register
}


void z80cpu::RLC_indirect() {
    t_state_cycles = 15;

    // copy the data from the memory address
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data = ram_read(address_absolute);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);
    // rotate data bits and save back into register
    result = (data << 1) + (data >> 7);
    ram_write(address_absolute, result);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register
}


void z80cpu::RLC_indexed_ix() {
    t_state_cycles = 23;

    // copy the data from the memory address
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    data = ram_read(address_absolute);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);
    // rotate data bits and save back into register
    result = (data << 1) + (data >> 7);
    ram_write(address_absolute, result);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register
}


void z80cpu::RLC_indexed_iy() {
    t_state_cycles = 23;

    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    data = ram_read(address_absolute);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);
    // rotate data bits and save back into register
    result = (data << 1) + (data >> 7);
    ram_write(address_absolute, result);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register
}