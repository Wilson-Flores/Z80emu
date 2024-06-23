#include "../z80.hpp"


void z80cpu::SLA_implied() {
    t_state_cycles = 8;

    // copy the data from the register
    data = *register_table[opcode & BIT_MASK_2];

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);

    // shift bits to the left and rewrite data in register
    result = data << 1;
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


void z80cpu::SLA_indirect() {
    t_state_cycles = 15;

    // copy the data from the memory address
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data = ram_read(address_absolute);

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);

    // shift bits to the left
    result = data << 1;

    // overwrite data
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


void z80cpu::SLA_indexed_ix() {
    t_state_cycles = 23;

    // copy the data from the memory address
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    data = ram_read(address_absolute);

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);

    // shift bits to the left
    result = data << 1;

    // overwrite data
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


void z80cpu::SLA_indexed_iy() {
    t_state_cycles = 23;

    // copy the data from the memory address
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    data = ram_read(address_absolute);

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);

    // shift bits to the left
    result = data << 1;

    // overwrite data
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


void z80cpu::SRA_implied() {
    t_state_cycles = 8;

    // copy the data from the register
    data = *register_table[opcode & BIT_MASK_2];

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register |= (data & 0x01);

    // We will be shifting bits to right while keeping the 7 bit the same.
    // EXAMPLE:
    // 7 6 5 4 3 2 1 0 C     7 6 5 4 3 2 1 0 C
    // 1 0 1 1 1 0 0 0 0 ->  1 1 0 1 1 1 0 0 0
    result = (data >> 1) | (data & 0x80);
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


void z80cpu::SRA_indirect() {
    t_state_cycles = 15;

    // copy the data from the memory address
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data = ram_read(address_absolute);

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register |= (data & 0x01);

    // We will be shifting bits to right while keeping the 7 bit the same.
    // EXAMPLE:
    // 7 6 5 4 3 2 1 0 C     7 6 5 4 3 2 1 0 C
    // 1 0 1 1 1 0 0 0 0 ->  1 1 0 1 1 1 0 0 0
    result = (data >> 1) | (data & 0x80);

    // overwrite data
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


void z80cpu::SRA_indexed_ix() {
    t_state_cycles = 23;

    // copy the data from the memory address
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    data = ram_read(address_absolute);

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register |= (data & 0x01);

    // We will be shifting bits to right while keeping the 7 bit the same.
    // EXAMPLE:
    // 7 6 5 4 3 2 1 0 C     7 6 5 4 3 2 1 0 C
    // 1 0 1 1 1 0 0 0 0 ->  1 1 0 1 1 1 0 0 0
    result = (data >> 1) | (data & 0x80);

    // overwrite data
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


void z80cpu::SRA_indexed_iy() {
    t_state_cycles = 23;

    // copy the data from the memory address
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    data = ram_read(address_absolute);

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register |= (data & 0x01);

    // We will be shifting bits to right while keeping the 7 bit the same.
    // EXAMPLE:
    // 7 6 5 4 3 2 1 0 C     7 6 5 4 3 2 1 0 C
    // 1 0 1 1 1 0 0 0 0 ->  1 1 0 1 1 1 0 0 0
    result = (data >> 1) | (data & 0x80);

    // overwrite data
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
