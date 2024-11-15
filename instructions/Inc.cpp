#include "../z80.hpp"


void z80cpu::INC_implied_register() {
    t_state_cycles_ = 4;

    // increment value in register
    uint8_t register_bit = (opcode_ & BIT_MASK_1) >> 3;
    data_8_ = *register_table_[register_bit];
    result_8_ = data_8_ + 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if carry from bit 3;
    // only time half carry occurs: (0b1111 + 0b0001)
    set_flag(HALF_CARRY_FLAG, ((data_8_ & 0x0F) == 0x0F));
    // P/V is set if r was 7Fh before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, data_8_ == 0x7F);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & 0x08);
    set_flag(Y_FLAG, result_8_ & 0x20);


    *register_table_[register_bit] = result_8_;
}


void z80cpu::INC_implied_register_indirect() {
    t_state_cycles_ = 11;

    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);
    result_8_ = data_8_ + 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if carry from bit 3;
    set_flag(HALF_CARRY_FLAG, ((data_8_ & 0x0F) == 0x0F));
    // P/V is set if r was 7Fh before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, data_8_ == 0x7F);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & 0x08);
    set_flag(Y_FLAG, result_8_ & 0x20);

    ram_write(memory_address_, result_8_);
}


void z80cpu::INC_implied_indexed_ix() {
    t_state_cycles_ = 23;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    data_8_ = ram_read(memory_address_);
    result_8_ = data_8_ + 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if carry from bit 3;
    set_flag(HALF_CARRY_FLAG, ((data_8_ & 0x0F) == 0x0F));
    // P/V is set if r was 7Fh before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, data_8_ == 0x7F);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & 0x08);
    set_flag(Y_FLAG, result_8_ & 0x20);

    ram_write(memory_address_, result_8_);
}


void z80cpu::INC_implied_indexed_iy() {
    t_state_cycles_ = 23;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    data_8_ = ram_read(memory_address_);
    result_8_ = data_8_ + 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result_8_ & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set if carry from bit 3;
    set_flag(HALF_CARRY_FLAG, ((data_8_ & 0x0F) == 0x0F));
    // P/V is set if r was 7Fh before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, data_8_ == 0x7F);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, result_8_ & 0x08);
    set_flag(Y_FLAG, result_8_ & 0x20);

    ram_write(memory_address_, result_8_);
}


void z80cpu::INC_implied_register_extended(){
    t_state_cycles_ = 6;

    uint8_t register_pair_bit = (opcode_ & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss_[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss_[register_pair_bit].low_byte_register;

    data_16_ = (high_byte << 8) + low_byte;
    data_8_++;

    *register_pair_table_ss_[register_pair_bit].high_byte_register = static_cast<uint8_t>((data_8_ & 0xFF00) >> 8);
    *register_pair_table_ss_[register_pair_bit].low_byte_register = static_cast<uint8_t>(data_8_ & 0x00FF);
}


void z80cpu::INC_implied_register_extended_ix(){
    t_state_cycles_ = 10;

    index_register_x_++;
}


void z80cpu::INC_implied_register_extended_iy(){
    t_state_cycles_ = 10;

    index_register_y_++;
}

