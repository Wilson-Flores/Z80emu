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

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::RLC_implied() {
    t_state_cycles = 8;

    // copy the data from the register
    data_8 = *register_table[opcode & BIT_MASK_2];

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data_8 >> 7);
    // rotate data bits and save back into register
    result_8 = (data_8 << 1) + (data_8 >> 7);
    *register_table[opcode & BIT_MASK_2] = result_8;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RLC_indirect() {
    t_state_cycles = 15;

    // copy the data from the memory address
    WZ_register = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data_8 = ram_read(WZ_register);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data_8 >> 7);
    // rotate data bits and save back into register
    result_8 = (data_8 << 1) + (data_8 >> 7);
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RLC_indexed_ix() {
    t_state_cycles = 23;

    // copy the data from the memory address
    WZ_register = index_register_x + static_cast<int16_t>(displacement);
    data_8 = ram_read(WZ_register);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data_8 >> 7);
    // rotate data bits and save back into register
    result_8 = (data_8 << 1) + (data_8 >> 7);
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RLC_indexed_iy() {
    t_state_cycles = 23;

    WZ_register = index_register_y + static_cast<int16_t>(displacement);
    data_8 = ram_read(WZ_register);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data_8 >> 7);
    // rotate data bits and save back into register
    result_8 = (data_8 << 1) + (data_8 >> 7);
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RRCA_implied() {
    t_state_cycles = 4;

    // isolate last bit in accumulator, then overwrite the carry bit in the flag register.
    // first we clear out the carry bit in the flag register,
    // then we do an or operation to copy the accumulator bit into the carry bit
    flag_register &= 0xFE;

    flag_register |= (accumulator & 0x01);

    // rotate accumulator bits 1 to the right, then add 7th bit
    accumulator = (accumulator >> 1) + ((accumulator & 0x01) << 7);

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 0 of Accumulator

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::RRC_implied() {
    t_state_cycles = 8;

    // copy the data from the register
    data_8 = *register_table[opcode & BIT_MASK_2];

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register |= (data_8 & 0x01);
    // rotate data bits and save back into register
    result_8 = (data_8 >> 1) + ((data_8 & 0x01) << 7);
    *register_table[opcode & BIT_MASK_2] = result_8;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RRC_indirect() {
    t_state_cycles = 15;

    // copy the data from the memory address
    WZ_register = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data_8 = ram_read(WZ_register);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register |= (data_8 & 0x01);
    // rotate data bits and save back into register
    result_8 = (data_8 >> 1) + ((data_8 & 0x01) << 7);
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RRC_indexed_ix() {
    t_state_cycles = 23;

    // copy the data from the memory address
    WZ_register = index_register_x + static_cast<int16_t>(displacement);
    data_8 = ram_read(WZ_register);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register |= (data_8 & 0x01);
    // rotate data bits and save back into register
    result_8 = (data_8 >> 1) + ((data_8 & 0x01) << 7);
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}



void z80cpu::RRC_indexed_iy() {
    t_state_cycles = 23;

    WZ_register = index_register_y + static_cast<int16_t>(displacement);
    data_8 = ram_read(WZ_register);


    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register |= (data_8 & 0x01);
    // rotate data bits and save back into register
    result_8 = (data_8 >> 1) + ((data_8 & 0x01) << 7);
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RLA_implied() {
    t_state_cycles = 4;

    // temp store 7th bit value of accumulator
    data_8 = (accumulator >> 7);

    // bit shift left and add carry bit
    accumulator = (flag_register & 0x01) | (accumulator << 1);

    // clear carry bit and then add 7th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of Accumulator

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::RL_implied() {
    t_state_cycles = 8;

    // copy the data from the register
    result_8 = *register_table[opcode & BIT_MASK_2];

    // temp store 7th bit value of register
    data_8 = (result_8 >> 7);

    // bit shift left and add carry bit
    result_8 = (flag_register & 0x01) | (result_8 << 1);

    // clear carry bit and then add 7th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // overwrite the register data
    *register_table[opcode & BIT_MASK_2] = result_8;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RL_indirect() {
    t_state_cycles = 15;

    // copy the data from the memory address
    WZ_register = (static_cast<uint16_t>(H_register) << 8) | L_register;
    result_8 = ram_read(WZ_register);

    // temp store 7th bit value of register
    data_8 = (result_8 >> 7);

    // bit shift left and add carry bit
    result_8 = (flag_register & 0x01) | (result_8 << 1);

    // clear carry bit and then add 7th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // overwrite data
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RL_indexed_ix() {
    t_state_cycles = 23;

    // copy the data from the memory address
    WZ_register = index_register_x + static_cast<int16_t>(displacement);
    result_8 = ram_read(WZ_register);

    // temp store 7th bit value of register
    data_8 = (result_8 >> 7);

    // bit shift left and add carry bit
    result_8 = (flag_register & 0x01) | (result_8 << 1);

    // clear carry bit and then add 7th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // overwrite data
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RL_indexed_iy() {
    t_state_cycles = 23;

    // copy the data from the memory address
    WZ_register = index_register_y + static_cast<int16_t>(displacement);
    result_8 = ram_read(WZ_register);

    // temp store 7th bit value of register
    data_8 = (result_8 >> 7);

    // bit shift left and add carry bit
    result_8 = (flag_register & 0x01) | (result_8 << 1);

    // clear carry bit and then add 7th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // overwrite data
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RRA_implied() {
    t_state_cycles = 4;

    // temp store 0th bit value of accumulator
    data_8 = (accumulator & 0x01);

    // bit shift right and add carry bit
    accumulator = ((flag_register & 0x01) << 7) | (accumulator >> 1);

    // clear carry bit and then add 0th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of Accumulator

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}

void z80cpu::RR_implied() {
    t_state_cycles = 8;

    // copy the data from the register
    result_8 = *register_table[opcode & BIT_MASK_2];

    // temp store 0th bit value of register
    data_8 = (result_8 & 0x01);

    // bit shift right and add carry bit
    result_8 = ((flag_register & 0x01) << 7) | (result_8 >> 1);

    // clear carry bit and then add 0th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // overwrite the register data
    *register_table[opcode & BIT_MASK_2] = result_8;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RR_indirect() {
    t_state_cycles = 15;

    // copy the data from the memory address
    WZ_register = (static_cast<uint16_t>(H_register) << 8) | L_register;
    result_8 = ram_read(WZ_register);

    // temp store 0th bit value of register
    data_8 = (result_8 & 0x01);

    // bit shift right and add carry bit
    result_8 = ((flag_register & 0x01) << 7) | (result_8 >> 1);

    // clear carry bit and then add 0th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // overwrite data
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RR_indexed_ix() {
    t_state_cycles = 23;

    // copy the data from the memory address
    WZ_register = index_register_x + static_cast<int16_t>(displacement);
    result_8 = ram_read(WZ_register);

    // temp store 0th bit value of register
    data_8 = (result_8 & 0x01);

    // bit shift right and add carry bit
    result_8 = ((flag_register & 0x01) << 7) | (result_8 >> 1);

    // clear carry bit and then add 0th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // overwrite data
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RR_indexed_iy() {
    t_state_cycles = 23;

    // copy the data from the memory address
    WZ_register = index_register_y + static_cast<int16_t>(displacement);
    result_8 = ram_read(WZ_register);

    // temp store 0th bit value of register
    data_8 = (result_8 & 0x01);

    // bit shift right and add carry bit
    result_8 = ((flag_register & 0x01) << 7) | (result_8 >> 1);

    // clear carry bit and then add 0th bit value
    flag_register &= 0xFE;
    flag_register |= data_8;

    // overwrite data
    ram_write(WZ_register, result_8);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8 & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8 == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8 & 0x08);
    set_flag(Y_FLAG, result_8 & 0x20);
}


void z80cpu::RLD_implied() {
    t_state_cycles = 18;

    WZ_register = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data_8 = ram_read(WZ_register);

    /* The contents of the low-order four bits (3,2,1,0) of data in memory location (HL)
     * are copied to the high-order four bits (7,6,5,4) of data in memory location (HL).
     *
     * The previous contents of those high-order four bits are copied to the low-order four bits of the accumulator.
     *
     * The previous contents of the low-order four bits of the accumulator are copied to the low-order four bits of
     * data in memory location (HL)
     * */

    /* Step 1: Left Shift data bits. [ 0 0 0 0 1 1 1 1 ] -> [ 1 1 1 1 0 0 0 0 ]
     * Step 2: Perform 'AND' operation on accumulator. We will only be working with the low-order bits.
     * [ 1111 1111 & 0000 1111 = 0000 1111 ]
     * Step 3: Perform an 'OR' operation and store the data into result variable.
     * Step 4: Perform and 'OR' operation with the Right Shift data bits and accumulator.
     * Step 5: Overwrite accumulator value.
     * */

    result_8 = (data_8 << 4) | (accumulator & 0x0F);
    accumulator &= 0xF0;
    accumulator |= (data_8 >> 4);

    ram_write(WZ_register, result_8);

    // S is set if accumulator is negative after an operation, else reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if the accumulator is 0 after an operation, else reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if the parity of the accumulator is even after an operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is not affected

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::RRD_implied() {
    t_state_cycles = 18;

    WZ_register = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data_8 = ram_read(WZ_register);

    /* The contents of the low-order four bits (3,2,1,0) of data in memory location (HL)
     * are copied to the low-order bits of the accumulator.
     *
     * The previous contents of the low-order four bits of the accumulator are copied to the high-order four bits of
     * data in memory location (HL).
     *
     * The previous contents of the high-order four bits of (HL) are copied to the low-order four bits of (HL).
     * */

    /* Step 1: Right Shift data bits. [ 1111 0000 ] -> [ 0000 1111 ]
     * Step 2: Left Shift accumulator bits. [ 0000 1111 ] -> [ 1111 0000 ]
     * Step 3: Perform an 'OR' operation and store the data into result variable.
     * Step 4: Perform and 'OR' operation with the  data's low-order bits and accumulator.
     * Step 5: Overwrite accumulator value.
     * */

    result_8 = (data_8 >> 4) | (accumulator << 4);

    // clear the low-order bits
    accumulator &= 0xF0;
    // 'OR' operation with data's low-order bits
    accumulator |= (data_8 & 0x0F);

    ram_write(WZ_register, result_8);

    // S is set if accumulator is negative after an operation, else reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if the accumulator is 0 after an operation, else reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if the parity of the accumulator is even after an operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is not affected

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}