#include "../z80.hpp"


void z80cpu::SLA_implied() {
    t_state_cycles_ = 8;

    // copy the data from the register
    data_8_ = *register_table_[opcode_ & BIT_MASK_2];

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 7th bit into carry flag bit
    flag_register_ |= (data_8_ >> 7);

    // shift bits to the left and rewrite data in register
    result_8_ = data_8_ << 1;
    *register_table_[opcode_ & BIT_MASK_2] = result_8_;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SLA_indirect() {
    t_state_cycles_ = 15;

    // copy the data from the memory address
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 7th bit into carry flag bit
    flag_register_ |= (data_8_ >> 7);

    // shift bits to the left
    result_8_ = data_8_ << 1;

    // overwrite data
    ram_write(memory_address_, result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SLA_indexed_ix() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 7th bit into carry flag bit
    flag_register_ |= (data_8_ >> 7);

    // shift bits to the left
    result_8_ = data_8_ << 1;

    // overwrite data
    ram_write(memory_address_, result_8_);

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & BIT_MASK_8);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SLA_indexed_iy() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 7th bit into carry flag bit
    flag_register_ |= (data_8_ >> 7);

    // shift bits to the left
    result_8_ = data_8_ << 1;

    // overwrite data
    ram_write(memory_address_, result_8_);

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SRA_implied() {
    t_state_cycles_ = 8;

    // copy the data from the register
    data_8_ = *register_table_[opcode_ & BIT_MASK_2];

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (data_8_ & BIT_MASK_5);

    // We will be shifting bits to right while keeping the 7 bit the same.
    // EXAMPLE:
    // 7 6 5 4 3 2 1 0 C     7 6 5 4 3 2 1 0 C
    // 1 0 1 1 1 0 0 0 0 ->  1 1 0 1 1 1 0 0 0
    result_8_ = (data_8_ >> 1) | (data_8_ & BIT_MASK_9);
    *register_table_[opcode_ & BIT_MASK_2] = result_8_;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 0 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SRA_indirect() {
    t_state_cycles_ = 15;

    // copy the data from the memory address
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);

    // clear the carry flag bit
    flag_register_ &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (data_8_ & BIT_MASK_5);

    // We will be shifting bits to right while keeping the 7 bit the same.
    // EXAMPLE:
    // 7 6 5 4 3 2 1 0 C     7 6 5 4 3 2 1 0 C
    // 1 0 1 1 1 0 0 0 0 ->  1 1 0 1 1 1 0 0 0
    result_8_ = (data_8_ >> 1) | (data_8_ & BIT_MASK_9);

    // overwrite data
    ram_write(memory_address_, result_8_);


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 0 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SRA_indexed_ix() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (data_8_ & BIT_MASK_5);

    // We will be shifting bits to right while keeping the 7 bit the same.
    // EXAMPLE:
    // 7 6 5 4 3 2 1 0 C     7 6 5 4 3 2 1 0 C
    // 1 0 1 1 1 0 0 0 0 ->  1 1 0 1 1 1 0 0 0
    result_8_ = (data_8_ >> 1) | (data_8_ & BIT_MASK_9);

    // overwrite data
    ram_write(memory_address_, result_8_);

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 0 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SRA_indexed_iy() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (data_8_ & BIT_MASK_5);

    // We will be shifting bits to right while keeping the 7 bit the same.
    // EXAMPLE:
    // 7 6 5 4 3 2 1 0 C     7 6 5 4 3 2 1 0 C
    // 1 0 1 1 1 0 0 0 0 ->  1 1 0 1 1 1 0 0 0
    result_8_ = (data_8_ >> 1) | (data_8_ & BIT_MASK_9);

    // overwrite data
    ram_write(memory_address_, result_8_);

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 0 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SRL_implied() {
    t_state_cycles_ = 8;

    // copy the data from the register
    data_8_ = *register_table_[opcode_ & BIT_MASK_2];

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (data_8_ & BIT_MASK_5);

    // We will be shifting bits to right
    result_8_ = data_8_ >> 1;
    *register_table_[opcode_ & BIT_MASK_2] = result_8_;

    // S is reset
    set_flag(SIGN_FLAG, false);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 0 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SRL_indirect() {
    t_state_cycles_ = 15;

    // copy the data from the memory address
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);

    // clear the carry flag bit
    flag_register_ &= 0xFE;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (data_8_ & BIT_MASK_5);

    // We will be shifting bits to right
    result_8_ = data_8_ >> 1;

    // overwrite data
    ram_write(memory_address_, result_8_);


    // S is reset
    set_flag(SIGN_FLAG, false);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SRL_indexed_ix() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (data_8_ & BIT_MASK_5);

    // We will be shifting bits to right
    result_8_ = data_8_ >> 1;

    // overwrite data
    ram_write(memory_address_, result_8_);

    // S is reset
    set_flag(SIGN_FLAG, false);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}


void z80cpu::SRL_indexed_iy() {
    t_state_cycles_ = 23;

    // copy the data from the memory address
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    // clear the carry flag bit
    flag_register_ &= BIT_MASK_6;
    // copy data 0th bit into carry flag bit
    flag_register_ |= (data_8_ & BIT_MASK_5);

    // We will be shifting bits to right
    result_8_ = data_8_ >> 1;

    // overwrite data
    ram_write(memory_address_, result_8_);

    // S is reset
    set_flag(SIGN_FLAG, false);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result_8_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, result_8_ & Y_FLAG_MASK);
}
