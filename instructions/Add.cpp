#include "../z80.hpp"


void z80cpu::ADD_compute_arithmetic_and_flag() {
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(data_8_);

    set_flag(SIGN_FLAG, result_16_ & SIGN_MASK);
    set_flag(ZERO_FLAG, (result_16_ & LOW_BYTE_MASK) == 0);
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) + (data_8_ & BIT_MASK_8) > BIT_MASK_8);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator_ ^ result_16_) & ~(accumulator_ ^ data_8_)) & BIT_MASK_9);
    set_flag(ADD_SUB_FLAG, false);
    set_flag(CARRY_FLAG, result_16_ > LOW_BYTE_MASK);
    accumulator_ = result_16_;
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::ADD_implied_register() {
    t_state_cycles_ = 4;

    data_8_ = *register_table_[opcode_ & BIT_MASK_2];
    ADD_compute_arithmetic_and_flag();
}


void z80cpu::ADD_implied_register_indirect() {
    t_state_cycles_ = 7;

    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);
    ADD_compute_arithmetic_and_flag();
}


void z80cpu::ADD_implied_indexed_ix() {
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);
    WZ_register_ = memory_address_;
    data_8_ = ram_read(memory_address_);
    ADD_compute_arithmetic_and_flag();
}


void z80cpu::ADD_implied_indexed_iy() {
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);
    WZ_register_ = memory_address_;
    data_8_ = ram_read(memory_address_);
    ADD_compute_arithmetic_and_flag();
}


void z80cpu::ADD_implied_immediate() {
    t_state_cycles_ = 7;

    data_8_ = rom_read(program_counter_);
    program_counter_++;
    ADD_compute_arithmetic_and_flag();
}


void z80cpu::ADC_implied_register() {
    t_state_cycles_ = 4;

    data_8_ = *register_table_[opcode_ & BIT_MASK_2];
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(data_8_) +
                 static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & SIGN_MASK);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & LOW_BYTE_MASK) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator_ & BIT_MASK_8) + (data_8_ & BIT_MASK_8) + get_flag(CARRY_FLAG)) > BIT_MASK_8);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_) &
                                    ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(data_8_))) & SIGN_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > LOW_BYTE_MASK);

    accumulator_ = result_16_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::ADC_implied_register_indirect() {
    t_state_cycles_ = 7;

    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(data_8_) +
                 static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & SIGN_MASK);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & LOW_BYTE_MASK) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator_ & BIT_MASK_8) + (data_8_ & BIT_MASK_8) + get_flag(CARRY_FLAG)) > BIT_MASK_8);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_) &
                                    ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(data_8_))) & SIGN_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > LOW_BYTE_MASK);

    accumulator_ = result_16_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::ADC_implied_indexed_ix() {
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(data_8_) +
                 static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & SIGN_MASK);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & LOW_BYTE_MASK) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator_ & BIT_MASK_8) + (data_8_ & BIT_MASK_8) + get_flag(CARRY_FLAG)) > BIT_MASK_8);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_) &
                                    ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(data_8_))) & SIGN_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > LOW_BYTE_MASK);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    accumulator_ = result_16_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::ADC_implied_indexed_iy() {
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(data_8_) +
                 static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & SIGN_MASK);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & LOW_BYTE_MASK) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator_ & BIT_MASK_8) + (data_8_ & BIT_MASK_8) + get_flag(CARRY_FLAG)) > BIT_MASK_8);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_) &
                                    ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(data_8_))) & SIGN_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > LOW_BYTE_MASK);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    accumulator_ = result_16_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::ADC_implied_immediate() {
    t_state_cycles_ = 7;

    data_8_ = rom_read(program_counter_);
    program_counter_++;

    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(data_8_) +
                 static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & SIGN_MASK);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & LOW_BYTE_MASK) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator_ & BIT_MASK_8) + (data_8_ & BIT_MASK_8) + get_flag(CARRY_FLAG)) > BIT_MASK_8);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_) &
                                    ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(data_8_))) & SIGN_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > LOW_BYTE_MASK);

    accumulator_ = result_16_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & X_FLAG_MASK);
    set_flag(Y_FLAG, accumulator_ & Y_FLAG_MASK);
}


void z80cpu::ADD_implied_register_extended() {
    t_state_cycles_ = 11;

    uint8_t register_pair_bit = (opcode_ & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss_[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss_[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;
    data_16_ = (H_register_ << 8) + L_register_;

    // WZ register stores the data from HL pair + 1
    WZ_register_ = data_16_ + 1;

    result_16_ = data_16_ + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = ((HL_data & 0x0FFF) + (register_pair_data & 0x0FFF));
    set_flag(HALF_CARRY_FLAG, ((data_16_ & HALF_CARRY_MASK) + (register_pair_data & HALF_CARRY_MASK)) > HALF_CARRY_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result_16_ < data_16_) || (result_16_ < register_pair_data));

    H_register_ = (result_16_ & HIGH_BYTE_MASK) >> 8;
    L_register_ = result_16_ & LOW_BYTE_MASK;

    //X & Y Flags are copies bit 3 & 5 of the high byte (H register)
    set_flag(X_FLAG, H_register_ & X_FLAG_MASK);
    set_flag(Y_FLAG, H_register_ & Y_FLAG_MASK);
}


void z80cpu::ADD_implied_register_extended_ix() {
    t_state_cycles_ = 15;

    uint8_t register_pair_bit = (opcode_ & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_pp_[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_pp_[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;

    // WZ register stores the data from IX pair + 1
    WZ_register_ = index_register_x_ + 1;

    result_16_ = index_register_x_ + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = (index_register_x & 0x0FFF) + (register_pair_data & 0x0FFF)
    set_flag(HALF_CARRY_FLAG, ((index_register_x_ & HALF_CARRY_MASK) + (register_pair_data & HALF_CARRY_MASK)) > HALF_CARRY_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result_16_ < index_register_x_) || (result_16_ < register_pair_data));

    index_register_x_ = result_16_;

    //X & Y Flags are copies bit 3 & 5 of the high byte of register x
    set_flag(X_FLAG, index_register_x_ & X_FLAG_MASK_2);
    set_flag(Y_FLAG, index_register_x_ & Y_FLAG_MASK_2);
}


void z80cpu::ADD_implied_register_extended_iy() {
    t_state_cycles_ = 15;

    uint8_t register_pair_bit = (opcode_ & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_rr_[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_rr_[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;

    // WZ register stores the data from IY pair + 1
    WZ_register_ = index_register_y_ + 1;

    result_16_ = index_register_y_ + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = (index_register_y & 0x0FFF) + (register_pair_data & 0x0FFF)
    set_flag(HALF_CARRY_FLAG, ((index_register_y_ & HALF_CARRY_MASK) + (register_pair_data & HALF_CARRY_MASK)) > HALF_CARRY_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result_16_ < index_register_y_) || (result_16_ < register_pair_data));

    index_register_y_ = result_16_;

    //X & Y Flags are copies bit 3 & 5 of the high byte of register y
    set_flag(X_FLAG, index_register_y_ & X_FLAG_MASK_2);
    set_flag(Y_FLAG, index_register_y_ & Y_FLAG_MASK_2);
}


void z80cpu::ADC_implied_register_extended() {
    t_state_cycles_ = 15;

    uint8_t register_pair_bit = (opcode_ & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss_[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss_[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = (high_byte << 8) + low_byte;
    data_16_ = (H_register_ << 8) + L_register_;

    // WZ register stores the data from HL pair + 1
    WZ_register_ = data_16_ + 1;

    uint32_t result_32 = static_cast<uint32_t>(data_16_) + static_cast<uint32_t>(register_pair_data)
                         + static_cast<uint32_t>(get_flag(CARRY_FLAG));


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, static_cast<uint16_t>(result_32) & SIGN_MASK);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, static_cast<uint16_t>(result_32) == 0);
    // H is set if carry from bit 11, else reset
    // h_result = (HL_data & 0x0FFF) + (register_pair_data & 0x0FFF) + (static_cast<uint16_t>(get_flag(CARRY_FLAG)) & 0x0FFF)
    set_flag(HALF_CARRY_FLAG, ((data_16_ & HALF_CARRY_MASK) + (register_pair_data & HALF_CARRY_MASK) +
                               (static_cast<uint16_t>(get_flag(CARRY_FLAG)) & HALF_CARRY_MASK)) > HALF_CARRY_MASK);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG,
             (~(static_cast<uint32_t>(data_16_) ^ static_cast<uint32_t>(register_pair_data))
                     & (static_cast<uint32_t>(data_16_) ^ result_32)) & PARITY_OVERFLOW_MASK);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result_32 > CARRY_MASK));

    H_register_ = (static_cast<uint16_t>(result_32) & HIGH_BYTE_MASK) >> 8;
    L_register_ = static_cast<uint16_t>(result_32) & LOW_BYTE_MASK;

    //X & Y Flags are copies bit 3 & 5 of the high byte (H register)
    set_flag(X_FLAG, H_register_ & X_FLAG_MASK);
    set_flag(Y_FLAG, H_register_ & Y_FLAG_MASK);
}