#include "../z80.hpp"


void z80cpu::INC_implied_register() {
    t_state_cycles_ = 4;

    // increment value in register
    uint8_t register_bit = (opcode_ & BIT_MASK_1) >> 3;
    temp_data_8_ = *register_table_[register_bit];
    temp_result_8_ = temp_data_8_ + 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if carry from bit 3;
    // only time half carry occurs: (0b1111 + 0b0001)
    set_flag(HALF_CARRY_FLAG, ((temp_data_8_ & BIT_MASK_8) == BIT_MASK_8));
    // P/V is set if r was 7Fh before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, temp_data_8_ == PARITY_REG_VALUE);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);


    *register_table_[register_bit] = temp_result_8_;
}


void z80cpu::INC_implied_register_indirect() {
    t_state_cycles_ = 11;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);
    temp_result_8_ = temp_data_8_ + 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if carry from bit 3;
    set_flag(HALF_CARRY_FLAG, ((temp_data_8_ & BIT_MASK_8) == BIT_MASK_8));
    // P/V is set if r was 7Fh before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, temp_data_8_ == PARITY_REG_VALUE);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);

    ram_write(temp_memory_address_, temp_result_8_);
}


void z80cpu::INC_implied_indexed_ix() {
    t_state_cycles_ = 23;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    temp_data_8_ = ram_read(temp_memory_address_);
    temp_result_8_ = temp_data_8_ + 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if carry from bit 3;
    set_flag(HALF_CARRY_FLAG, ((temp_data_8_ & BIT_MASK_8) == BIT_MASK_8));
    // P/V is set if r was 7Fh before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, temp_data_8_ == PARITY_REG_VALUE);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);

    ram_write(temp_memory_address_, temp_result_8_);
}


void z80cpu::INC_implied_indexed_iy() {
    t_state_cycles_ = 23;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    temp_data_8_ = ram_read(temp_memory_address_);
    temp_result_8_ = temp_data_8_ + 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if carry from bit 3;
    set_flag(HALF_CARRY_FLAG, ((temp_data_8_ & BIT_MASK_8) == BIT_MASK_8));
    // P/V is set if r was 7Fh before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, temp_data_8_ == PARITY_REG_VALUE);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);

    ram_write(temp_memory_address_, temp_result_8_);
}


void z80cpu::INC_implied_register_extended(){
    t_state_cycles_ = 6;

    uint8_t register_pair_bit = (opcode_ & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss_[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss_[register_pair_bit].low_byte_register;

    temp_data_16_ = (high_byte << 8) + low_byte;
    temp_data_8_++;

    *register_pair_table_ss_[register_pair_bit].high_byte_register = static_cast<uint8_t>((temp_data_8_ & HIGH_BYTE_MASK) >> 8);
    *register_pair_table_ss_[register_pair_bit].low_byte_register = static_cast<uint8_t>(temp_data_8_ & LOW_BYTE_MASK);
}


void z80cpu::INC_implied_register_extended_ix(){
    t_state_cycles_ = 10;

    index_register_x_++;
}


void z80cpu::INC_implied_register_extended_iy(){
    t_state_cycles_ = 10;

    index_register_y_++;
}

