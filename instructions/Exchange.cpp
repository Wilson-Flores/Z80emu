#include "../z80.hpp"

void z80cpu::EX_implied_implied_af() {
    t_state_cycles_ = 4;
    // use XOR to swap without needing another temp variable

    accumulator_ ^= alt_accumulator_;
    alt_accumulator_ ^= accumulator_;
    accumulator_ ^= alt_accumulator_;

    flag_register_ ^= alt_flag_register_;
    alt_flag_register_ ^= flag_register_;
    flag_register_ ^= alt_flag_register_;
}


void z80cpu::EXX_implied_implied() {
    t_state_cycles_ = 4;
    // use XOR to swap without needing another temp variable

    for(uint8_t i = 0; i < 6; i++){
        *register_table_[i] ^= *alt_register_table_[i];
        *alt_register_table_[i] ^= *register_table_[i];
        *register_table_[i] ^= *alt_register_table_[i];
    }
}


void z80cpu::EX_implied_implied() {
    t_state_cycles_ = 4;

    D_register_ ^= H_register_;
    H_register_ ^= D_register_;
    D_register_ ^= H_register_;

    E_register_ ^= L_register_;
    L_register_ ^= E_register_;
    E_register_ ^= L_register_;
}


void z80cpu::EX_register_indirect_implied_hl() {
    t_state_cycles_ = 19;

    data_8_ = ram_read(stack_pointer_);  // low byte in HL is swapped with memory at stack pointer address
    // WZ register stores the data from the stack pointer address starting with the low byte from l register
    WZ_register_ = static_cast<uint16_t>(data_8_);
    L_register_ ^= data_8_;
    data_8_ ^= L_register_;
    L_register_ ^= data_8_;
    ram_write(stack_pointer_, data_8_);

    data_8_ = ram_read(stack_pointer_ + 1);     // high byte in HL is swapped with memory at (stack pointer + 1) address
    // WZ register stores the data from the stack pointer address, the high byte is from H register.
    WZ_register_ += static_cast<uint16_t>(data_8_) << 8;
    H_register_ ^= data_8_;
    data_8_ ^= H_register_;
    H_register_ ^= data_8_;
    ram_write(stack_pointer_ + 1, data_8_);
}


void z80cpu::EX_register_indirect_implied_ix() {
    t_state_cycles_ = 19;

    data_16_ = static_cast<uint16_t>(ram_read(stack_pointer_ + 1) << 8) | ram_read(stack_pointer_);
    // data is stored in wz_register
    WZ_register_ = data_16_;
    index_register_x_ ^= data_16_;
    data_16_ ^= index_register_x_;
    index_register_x_ ^= data_16_;

    ram_write(stack_pointer_ + 1, static_cast<uint8_t>(data_16_ >> 8));
    ram_write(stack_pointer_, static_cast<uint8_t>(data_16_));
}


void z80cpu::EX_register_indirect_implied_iy() {
    t_state_cycles_ = 19;

    data_16_ = static_cast<uint16_t>(ram_read(stack_pointer_ + 1) << 8) | ram_read(stack_pointer_);
    // data is stored in wz_register
    WZ_register_ = data_16_;
    index_register_y_ ^= data_16_;
    data_16_ ^= index_register_y_;
    index_register_y_ ^= data_16_;

    ram_write(stack_pointer_ + 1, static_cast<uint8_t>(data_16_ >> 8));
    ram_write(stack_pointer_, static_cast<uint8_t>(data_16_));
}