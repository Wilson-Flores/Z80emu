#include "../z80.hpp"


void z80cpu::ADD_helper() {
    temp_result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(temp_data_8_);

    set_flag(SIGN_FLAG, temp_result_16_ & SIGN_MASK);
    set_flag(ZERO_FLAG, (temp_result_16_ & LOW_BYTE_MASK) == 0);
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) + (temp_data_8_ & BIT_MASK_8) > BIT_MASK_8);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator_ ^ temp_result_16_) & ~(accumulator_ ^ temp_data_8_)) & BIT_MASK_9);
    set_flag(ADD_SUB_FLAG, false);
    set_flag(CARRY_FLAG, temp_result_16_ > LOW_BYTE_MASK);

    accumulator_ = temp_result_16_;

    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::ADC_helper() {
    temp_result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(temp_data_8_) +
                      static_cast<uint16_t>(get_flag(CARRY_FLAG));

    set_flag(SIGN_FLAG, temp_result_16_ & SIGN_MASK);
    set_flag(ZERO_FLAG, (temp_result_16_ & LOW_BYTE_MASK) == 0);
    set_flag(HALF_CARRY_FLAG,
             ((accumulator_ & BIT_MASK_8) + (temp_data_8_ & BIT_MASK_8) + get_flag(CARRY_FLAG)) > BIT_MASK_8);
    set_flag(PARITY_OVERFLOW_FLAG,
             ((static_cast<uint16_t>(accumulator_) ^ temp_result_16_) &
              ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(temp_data_8_))) & SIGN_MASK);
    set_flag(ADD_SUB_FLAG, false);
    set_flag(CARRY_FLAG, temp_result_16_ > LOW_BYTE_MASK);

    accumulator_ = temp_result_16_;

    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::ADD_implied_register() {
    t_state_cycles_ = 4;

    temp_data_8_ = *register_table_[opcode_ & BIT_MASK_2];
    ADD_helper();
}


void z80cpu::ADD_implied_register_indirect() {
    t_state_cycles_ = 7;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);
    ADD_helper();
}


void z80cpu::ADD_implied_indexed_ix() {
    t_state_cycles_ = 19;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);
    WZ_register_ = temp_memory_address_;
    temp_data_8_ = ram_read(temp_memory_address_);
    ADD_helper();
}


void z80cpu::ADD_implied_indexed_iy() {
    t_state_cycles_ = 19;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);
    WZ_register_ = temp_memory_address_;
    temp_data_8_ = ram_read(temp_memory_address_);
    ADD_helper();
}


void z80cpu::ADD_implied_immediate() {
    t_state_cycles_ = 7;

    temp_data_8_ = rom_read(program_counter_);
    program_counter_++;
    ADD_helper();
}


void z80cpu::ADC_implied_register() {
    t_state_cycles_ = 4;

    temp_data_8_ = *register_table_[opcode_ & BIT_MASK_2];
    ADC_helper();
}


void z80cpu::ADC_implied_register_indirect() {
    t_state_cycles_ = 7;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);
    ADC_helper();
}


void z80cpu::ADC_implied_indexed_ix() {
    t_state_cycles_ = 19;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);
    temp_data_8_ = ram_read(temp_memory_address_);
    WZ_register_ = temp_memory_address_;
    ADC_helper();
}


void z80cpu::ADC_implied_indexed_iy() {
    t_state_cycles_ = 19;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);
    temp_data_8_ = ram_read(temp_memory_address_);
    WZ_register_ = temp_memory_address_;
    ADC_helper();
}


void z80cpu::ADC_implied_immediate() {
    t_state_cycles_ = 7;

    temp_data_8_ = rom_read(program_counter_);
    program_counter_++;
    ADC_helper();
}


void z80cpu::ADD_implied_register_extended() {
    t_state_cycles_ = 11;

    temp_data_8_ = (opcode_ & BIT_MASK_3) >> 4;
    temp_high_byte_ = *register_pair_table_ss_[temp_data_8_].high_byte_register;
    temp_low_byte_ = *register_pair_table_ss_[temp_data_8_].low_byte_register;
    temp_reg_pair_data_ = ( temp_high_byte_ << 8) + temp_low_byte_;

    temp_data_16_ = (static_cast<uint16_t>(H_register_) << 8) + L_register_;
    WZ_register_ = temp_data_16_ + 1;
    temp_result_16_ = temp_data_16_ + temp_reg_pair_data_;

    set_flag(HALF_CARRY_FLAG, ((temp_data_16_ & CARRY_MASK) + (temp_reg_pair_data_ & CARRY_MASK)) > CARRY_MASK);
    set_flag(ADD_SUB_FLAG, false);
    set_flag(CARRY_FLAG, (temp_result_16_ < temp_data_16_) || (temp_result_16_ < temp_reg_pair_data_));

    H_register_ = (temp_result_16_ & HIGH_BYTE_MASK) >> 8;
    L_register_ = temp_result_16_ & LOW_BYTE_MASK;

    set_flag(X_FLAG, H_register_ & X_FLAG_MASK);
    set_flag(Y_FLAG, H_register_ & Y_FLAG_MASK);
}


void z80cpu::ADD_implied_register_extended_ix() {
    t_state_cycles_ = 15;

    temp_data_8_ = (opcode_ & BIT_MASK_3) >> 4;
    temp_high_byte_ = *register_pair_table_pp_[temp_data_8_].high_byte_register;
    temp_low_byte_ = *register_pair_table_pp_[temp_data_8_].low_byte_register;
    temp_reg_pair_data_ = ( temp_high_byte_ << 8) + temp_low_byte_;
    WZ_register_ = index_register_x_ + 1;

    temp_result_16_ = index_register_x_ + temp_reg_pair_data_;

    set_flag(HALF_CARRY_FLAG, ((index_register_x_ & CARRY_MASK) + (temp_reg_pair_data_ & CARRY_MASK)) > CARRY_MASK);
    set_flag(ADD_SUB_FLAG, false);
    set_flag(CARRY_FLAG, (temp_result_16_ < index_register_x_) || (temp_result_16_ < temp_reg_pair_data_));

    index_register_x_ = temp_result_16_;

    set_flag(X_FLAG, index_register_x_ & X_FLAG_MASK_2);
    set_flag(Y_FLAG, index_register_x_ & Y_FLAG_MASK_2);
}


void z80cpu::ADD_implied_register_extended_iy() {
    t_state_cycles_ = 15;

    temp_data_8_ = (opcode_ & BIT_MASK_3) >> 4;
    temp_high_byte_ = *register_pair_table_rr_[temp_data_8_].high_byte_register;
    temp_low_byte_ = *register_pair_table_rr_[temp_data_8_].low_byte_register;
    temp_reg_pair_data_ = ( temp_high_byte_ << 8) + temp_low_byte_;
    WZ_register_ = index_register_y_ + 1;

    temp_result_16_ = index_register_y_ + temp_reg_pair_data_;

    set_flag(HALF_CARRY_FLAG, ((index_register_y_ & CARRY_MASK) + (temp_reg_pair_data_ & CARRY_MASK)) > CARRY_MASK);
    set_flag(ADD_SUB_FLAG, false);
    set_flag(CARRY_FLAG, (temp_result_16_ < index_register_y_) || (temp_result_16_ < temp_reg_pair_data_));

    index_register_y_ = temp_result_16_;

    set_flag(X_FLAG, index_register_y_ & X_FLAG_MASK_2);
    set_flag(Y_FLAG, index_register_y_ & Y_FLAG_MASK_2);
}


void z80cpu::ADC_implied_register_extended() {
    t_state_cycles_ = 15;

    temp_data_8_ = (opcode_ & BIT_MASK_3) >> 4;
    temp_high_byte_ = *register_pair_table_ss_[temp_data_8_].high_byte_register;
    temp_low_byte_ = *register_pair_table_ss_[temp_data_8_].low_byte_register;
    temp_reg_pair_data_ = (temp_high_byte_ << 8) + temp_low_byte_;
    temp_data_16_ = (H_register_ << 8) + L_register_;
    WZ_register_ = temp_data_16_ + 1;

    uint32_t result_32 = static_cast<uint32_t>(temp_data_16_) + static_cast<uint32_t>(temp_reg_pair_data_)
                         + static_cast<uint32_t>(get_flag(CARRY_FLAG));


    set_flag(SIGN_FLAG, static_cast<uint16_t>(result_32) & SIGN_MASK_2);
    set_flag(ZERO_FLAG, static_cast<uint16_t>(result_32) == 0);
    set_flag(HALF_CARRY_FLAG,((temp_data_16_ & CARRY_MASK) + (temp_reg_pair_data_ & CARRY_MASK) +
                              (static_cast<uint16_t>(get_flag(CARRY_FLAG)) & CARRY_MASK)) > CARRY_MASK);
    set_flag(PARITY_OVERFLOW_FLAG,
             (~(static_cast<uint32_t>(temp_data_16_) ^ static_cast<uint32_t>(temp_reg_pair_data_))
                     & (static_cast<uint32_t>(temp_data_16_) ^ result_32)) & PARITY_OVERFLOW_MASK);
    set_flag(ADD_SUB_FLAG, false);
    set_flag(CARRY_FLAG, (result_32 > CARRY_MASK_2));

    H_register_ = (static_cast<uint16_t>(result_32) & HIGH_BYTE_MASK) >> 8;
    L_register_ = static_cast<uint16_t>(result_32) & LOW_BYTE_MASK;

    set_flag(X_FLAG, H_register_ & X_FLAG_MASK);
    set_flag(Y_FLAG, H_register_ & Y_FLAG_MASK);
}