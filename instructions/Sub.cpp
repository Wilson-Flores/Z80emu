#include "../z80.hpp"

void z80cpu::SUB_implied_register() {
    t_state_cycles_ = 4;

    data_8_ = *register_table_[opcode_ & BIT_MASK_2];
    result_8_ = accumulator_ - data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < (data_8_ & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator_ ^ (accumulator_ + (~data_8_ + 0x01))) & ~(accumulator_ ^ (~data_8_ + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < data_8_);

    accumulator_ = result_8_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SUB_implied_register_indirect() {
    t_state_cycles_ = 7;

    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);
    result_8_ = accumulator_ - data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < (data_8_ & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator_ ^ (accumulator_ + (~data_8_ + 0x01))) & ~(accumulator_ ^ (~data_8_ + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < data_8_);

    accumulator_ = result_8_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SUB_implied_indexed_ix() {
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);
    result_8_ = accumulator_ - data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < (data_8_ & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator_ ^ (accumulator_ + (~data_8_ + 0x01))) & ~(accumulator_ ^ (~data_8_ + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < data_8_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    accumulator_ = result_8_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SUB_implied_indexed_iy() {
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);
    result_8_ = accumulator_ - data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < (data_8_ & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator_ ^ (accumulator_ + (~data_8_ + 0x01))) & ~(accumulator_ ^ (~data_8_ + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < data_8_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    accumulator_ = result_8_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SUB_implied_immediate() {
    t_state_cycles_ = 7;

    data_8_ = rom_read(program_counter_);
    program_counter_++;
    result_8_ = accumulator_ - data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < (data_8_ & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s compliment on data, reuse ADD's logic for overflow flag
    // overflow_result = accumulator + (~data + 0x01)
    set_flag(PARITY_OVERFLOW_FLAG,
             ((accumulator_ ^ (accumulator_ + (~data_8_ + 0x01))) & ~(accumulator_ ^ (~data_8_ + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < data_8_);

    accumulator_ = result_8_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SBC_implied_register() {
    t_state_cycles_ = 4;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    data_8_ = *register_table_[opcode_ & BIT_MASK_2];
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(~data_8_) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    // this flag works differently compared to ADC, borrow will always occur when the data is bigger than the accumulator.
    // this time we include the carry flag. using A - D - C -> A - (D + C) -> A < (D + C)
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < ((data_8_ & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_)
    & ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(~data_8_))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > 0x00FF);

    accumulator_ = static_cast<uint8_t>(result_16_);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SBC_implied_register_indirect() {
    t_state_cycles_ = 7;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(~data_8_) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < ((data_8_ & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_)
    & ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(~data_8_))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > 0x00FF);

    accumulator_ = static_cast<uint8_t>(result_16_);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SBC_implied_indexed_ix() {
    t_state_cycles_ = 19;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(~data_8_) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < ((data_8_ & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_)
    & ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(~data_8_))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > 0x00FF);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    accumulator_ = static_cast<uint8_t>(result_16_);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SBC_implied_indexed_iy() {
    t_state_cycles_ = 19;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);
    data_8_ = ram_read(memory_address_);
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(~data_8_) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < ((data_8_ & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_)
    & ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(~data_8_))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > 0x00FF);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;
    accumulator_ = static_cast<uint8_t>(result_16_);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}

void z80cpu::SBC_implied_immediate() {
    t_state_cycles_ = 7;

    // A = A - D - C
    // we can modify the equation so the instruction will perform addition instead.
    // take the 2s complement of D: -D = (~D + 1)
    // A = A + (~D + 1) - C -> A = A + ~D + (1 - C)
    // take it a step further by taking the 2s complement of C: A = A + ~D + 1 + (~C + 1) -> A = A + ~D + ~C + 2
    data_8_ = rom_read(program_counter_);
    program_counter_++;
    result_16_ = static_cast<uint16_t>(accumulator_) + static_cast<uint16_t>(~data_8_) + static_cast<uint16_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16_ & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16_ & 0x00FF) == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & 0x0F) < ((data_8_ & 0x0F) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator_) ^ result_16_)
    & ~(static_cast<uint16_t>(accumulator_) ^ static_cast<uint16_t>(~data_8_))) & 0x0080);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, result_16_ > 0x00FF);

    accumulator_ = static_cast<uint8_t>(result_16_);

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::SBC_implied_register_extended() {
    t_state_cycles_ = 15;

    uint8_t register_pair_bit = (opcode_ & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss_[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss_[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = (high_byte << 8) + low_byte;
    data_16_ = (H_register_ << 8) + L_register_;

    // WZ register stores the data from HL pair + 1
    WZ_register_ = data_16_ + 1;

    uint32_t result_32 = static_cast<uint32_t>(data_16_) + static_cast<uint32_t>(~register_pair_data) +
                         static_cast<uint32_t>(~get_flag(CARRY_FLAG)) + 2;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, static_cast<uint16_t>(result_32) & 0x8000);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, static_cast<uint16_t>(result_32) == 0x0000);
    // H is set if borrow from bit 12, else reset
    set_flag(HALF_CARRY_FLAG, (data_16_ & 0x0FFF) < ((register_pair_data & 0x0FFF) + get_flag(CARRY_FLAG)));
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint32_t>(data_16_) ^ result_32)
    & ~(static_cast<uint32_t>(data_16_) ^ static_cast<uint32_t>(~register_pair_data))) & 0x00008000);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow, else reset
    set_flag(CARRY_FLAG, result_32 > 0xFFFF);

    H_register_ = (static_cast<uint16_t>(result_32) & 0xFF00) >> 8;
    L_register_ = static_cast<uint16_t>(result_32) & 0x00FF;

    //X & Y Flags are copies bit 3 & 5 of the high byte (H register)
    set_flag(X_FLAG, H_register_ & 0x08);
    set_flag(Y_FLAG, H_register_ & 0x20);
}