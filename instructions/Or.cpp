#include "../z80.hpp"


void z80cpu::OR_implied_register() {
    t_state_cycles_ = 4;

    temp_data_8_ = *register_table_[opcode_ & BIT_MASK_2];
    accumulator_ |= temp_data_8_;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::OR_implied_register_indirect() {
    t_state_cycles_ = 7;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = rom_read(temp_memory_address_);
    accumulator_ |= temp_data_8_;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}

void z80cpu::OR_implied_indexed_ix() {
    t_state_cycles_ = 19;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    temp_data_8_ = rom_read(temp_memory_address_);
    accumulator_ |= temp_data_8_;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::OR_implied_indexed_iy() {
    t_state_cycles_ = 19;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    temp_data_8_ = rom_read(temp_memory_address_);
    accumulator_ |= temp_data_8_;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}

void z80cpu::OR_implied_immediate() {
    t_state_cycles_ = 7;

    temp_data_8_ = rom_read(program_counter_);
    program_counter_++;
    accumulator_ |= temp_data_8_;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, accumulator_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, accumulator_ == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity is even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[accumulator_]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is reset
    set_flag(CARRY_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}