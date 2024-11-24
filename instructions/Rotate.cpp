#include "../z80.hpp"


void z80cpu::RLCA_implied() {
    t_state_cycles_ = 4;

    // isolate leading bit in accumulator, then overwrite the carry bit in the flag register.
    // first we clear out the carry bit in the flag register,
    // then we do an or operation to copy the accumulator bit into the carry bit
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= (accumulator_ >> 7);

    // rotate accumulator bits 1 to the left, then add 7th bit
    accumulator_ = (accumulator_ << 1) + (accumulator_ >> 7);

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of Accumulator

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::RLC_implied() {
    t_state_cycles_ = 8;

    // copy the data from the register
    temp_data_8_ = *register_table_[opcode_ & BIT_MASK_2];

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 7th bit into carry flag bit
    flag_register_ |= (temp_data_8_ >> 7);
    // rotate data bits and save back into register
    temp_result_8_ = (temp_data_8_ << 1) + (temp_data_8_ >> 7);
    *register_table_[opcode_ & BIT_MASK_2] = temp_result_8_;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RLC_indirect() {
    t_state_cycles_ = 15;

    // copy the data from the memory address
    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);


    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 7th bit into carry flag bit
    flag_register_ |= (temp_data_8_ >> 7);
    // rotate data bits and save back into register
    temp_result_8_ = (temp_data_8_ << 1) + (temp_data_8_ >> 7);
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RLC_indexed_ix() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);
    temp_data_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 7th bit into carry flag bit
    flag_register_ |= (temp_data_8_ >> 7);
    // rotate data bits and save back into register
    temp_result_8_ = (temp_data_8_ << 1) + (temp_data_8_ >> 7);
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RLC_indexed_iy() {
    t_state_cycles_ = 23;

    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);
    temp_data_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 7th bit into carry flag bit
    flag_register_ |= (temp_data_8_ >> 7);
    // rotate data bits and save back into register
    temp_result_8_ = (temp_data_8_ << 1) + (temp_data_8_ >> 7);
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RRCA_implied() {
    t_state_cycles_ = 4;

    // isolate last bit in accumulator, then overwrite the carry bit in the flag register.
    // first we clear out the carry bit in the flag register,
    // then we do an or operation to copy the accumulator bit into the carry bit
    flag_register_ &= BIT_MASK_6;

    flag_register_ |= (accumulator_ & BIT_MASK_5);

    // rotate accumulator bits 1 to the right, then add 7th bit
    accumulator_ = (accumulator_ >> 1) + ((accumulator_ & BIT_MASK_5) << 7);

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 0 of Accumulator

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::RRC_implied() {
    t_state_cycles_ = 8;

    // copy the data from the register
    temp_data_8_ = *register_table_[opcode_ & BIT_MASK_2];

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (temp_data_8_ & BIT_MASK_5);
    // rotate data bits and save back into register
    temp_result_8_ = (temp_data_8_ >> 1) + ((temp_data_8_ & BIT_MASK_5) << 7);
    *register_table_[opcode_ & BIT_MASK_2] = temp_result_8_;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RRC_indirect() {
    t_state_cycles_ = 15;

    // copy the data from the memory address
    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);


    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (temp_data_8_ & BIT_MASK_5);
    // rotate data bits and save back into register
    temp_result_8_ = (temp_data_8_ >> 1) + ((temp_data_8_ & BIT_MASK_5) << 7);
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RRC_indexed_ix() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);
    temp_data_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (temp_data_8_ & BIT_MASK_5);
    // rotate data bits and save back into register
    temp_result_8_ = (temp_data_8_ >> 1) + ((temp_data_8_ & BIT_MASK_5) << 7);
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}



void z80cpu::RRC_indexed_iy() {
    t_state_cycles_ = 23;

    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);
    temp_data_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (temp_data_8_ & BIT_MASK_5);
    // rotate data bits and save back into register
    temp_result_8_ = (temp_data_8_ >> 1) + ((temp_data_8_ & BIT_MASK_5) << 7);
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RLA_implied() {
    t_state_cycles_ = 4;

    // temp store 7th bit value of accumulator
    temp_data_8_ = (accumulator_ >> 7);

    // bit shift left and add carry bit
    accumulator_ = (flag_register_ & BIT_MASK_5) | (accumulator_ << 1);

    // clear carry bit and then add 7th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of Accumulator

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::RL_implied() {
    t_state_cycles_ = 8;

    // copy the data from the register
    temp_result_8_ = *register_table_[opcode_ & BIT_MASK_2];

    // temp store 7th bit value of register
    temp_data_8_ = (temp_result_8_ >> 7);

    // bit shift left and add carry bit
    temp_result_8_ = (flag_register_ & BIT_MASK_5) | (temp_result_8_ << 1);

    // clear carry bit and then add 7th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // overwrite the register data
    *register_table_[opcode_ & BIT_MASK_2] = temp_result_8_;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RL_indirect() {
    t_state_cycles_ = 15;

    // copy the data from the memory address
    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_result_8_ = ram_read(temp_memory_address_);

    // temp store 7th bit value of register
    temp_data_8_ = (temp_result_8_ >> 7);

    // bit shift left and add carry bit
    temp_result_8_ = (flag_register_ & BIT_MASK_5) | (temp_result_8_ << 1);

    // clear carry bit and then add 7th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // overwrite data
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RL_indexed_ix() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);
    temp_result_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // temp store 7th bit value of register
    temp_data_8_ = (temp_result_8_ >> 7);

    // bit shift left and add carry bit
    temp_result_8_ = (flag_register_ & BIT_MASK_5) | (temp_result_8_ << 1);

    // clear carry bit and then add 7th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // overwrite data
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RL_indexed_iy() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);
    temp_result_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // temp store 7th bit value of register
    temp_data_8_ = (temp_result_8_ >> 7);

    // bit shift left and add carry bit
    temp_result_8_ = (flag_register_ & BIT_MASK_5) | (temp_result_8_ << 1);

    // clear carry bit and then add 7th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // overwrite data
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RRA_implied() {
    t_state_cycles_ = 4;

    // temp store 0th bit value of accumulator
    temp_data_8_ = (accumulator_ & 0x01);

    // bit shift right and add carry bit
    accumulator_ = ((flag_register_ & BIT_MASK_5) << 7) | (accumulator_ >> 1);

    // clear carry bit and then add 0th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of Accumulator

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}

void z80cpu::RR_implied() {
    t_state_cycles_ = 8;

    // copy the data from the register
    temp_result_8_ = *register_table_[opcode_ & BIT_MASK_2];

    // temp store 0th bit value of register
    temp_data_8_ = (temp_result_8_ & BIT_MASK_5);

    // bit shift right and add carry bit
    temp_result_8_ = ((flag_register_ & BIT_MASK_5) << 7) | (temp_result_8_ >> 1);

    // clear carry bit and then add 0th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // overwrite the register data
    *register_table_[opcode_ & BIT_MASK_2] = temp_result_8_;


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RR_indirect() {
    t_state_cycles_ = 15;

    // copy the data from the memory address
    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_result_8_ = ram_read(temp_memory_address_);

    // temp store 0th bit value of register
    temp_data_8_ = (temp_result_8_ & BIT_MASK_5);

    // bit shift right and add carry bit
    temp_result_8_ = ((flag_register_ & BIT_MASK_5) << 7) | (temp_result_8_ >> 1);

    // clear carry bit and then add 0th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // overwrite data
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RR_indexed_ix() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);
    temp_result_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // temp store 0th bit value of register
    temp_data_8_ = (temp_result_8_ & BIT_MASK_5);

    // bit shift right and add carry bit
    temp_result_8_ = ((flag_register_ & BIT_MASK_5) << 7) | (temp_result_8_ >> 1);

    // clear carry bit and then add 0th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // overwrite data
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RR_indexed_iy() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);
    temp_result_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // temp store 0th bit value of register
    temp_data_8_ = (temp_result_8_ & BIT_MASK_5);

    // bit shift right and add carry bit
    temp_result_8_ = ((flag_register_ & BIT_MASK_5) << 7) | (temp_result_8_ >> 1);

    // clear carry bit and then add 0th bit value
    flag_register_ &= BIT_MASK_6;
    flag_register_ |= temp_data_8_;

    // overwrite data
    ram_write(temp_memory_address_, temp_result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::RLD_implied() {
    t_state_cycles_ = 18;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;

    // WZ registers stores the mem address + 1
    WZ_register_ = temp_memory_address_ + 1;

    temp_data_8_ = ram_read(temp_memory_address_);

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

    temp_result_8_ = (temp_data_8_ << 4) | (accumulator_ & BIT_MASK_8);
    accumulator_ &= BIT_MASK_7;
    accumulator_ |= (temp_data_8_ >> 4);

    ram_write(temp_memory_address_, temp_result_8_);

    // S is set if accumulator is negative after an operation, else reset
    set_flag(SIGN_FLAG, accumulator_ & BIT_MASK_9);
    // Z is set if the accumulator is 0 after an operation, else reset
    set_flag(ZERO_FLAG, accumulator_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if the parity of the accumulator is even after an operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is not affected

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::RRD_implied() {
    t_state_cycles_ = 18;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;

    // WZ registers stores the mem address + 1
    WZ_register_ = temp_memory_address_ + 1;

    temp_data_8_ = ram_read(temp_memory_address_);

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

    temp_result_8_ = (temp_data_8_ >> 4) | (accumulator_ << 4);

    // clear the low-order bits
    accumulator_ &= BIT_MASK_7;
    // 'OR' operation with data's low-order bits
    accumulator_ |= (temp_data_8_ & BIT_MASK_8);

    ram_write(temp_memory_address_, temp_result_8_);

    // S is set if accumulator is negative after an operation, else reset
    set_flag(SIGN_FLAG, accumulator_ & BIT_MASK_9);
    // Z is set if the accumulator is 0 after an operation, else reset
    set_flag(ZERO_FLAG, accumulator_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if the parity of the accumulator is even after an operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is not affected

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}