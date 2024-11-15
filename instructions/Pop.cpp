#include "../z80.hpp"

void z80cpu::POP_register_indirect_register() {
    t_state_cycles_ = 10;

    data_8_ = (opcode_ & BIT_MASK_3) >> 4;

    *register_pair_table_qq_[data_8_].low_byte_register = ram_read(stack_pointer_);
    stack_pointer_++;

    *register_pair_table_qq_[data_8_].high_byte_register = ram_read(stack_pointer_);
    stack_pointer_++;
}


void z80cpu::POP_register_indirect_register_ix() {
    t_state_cycles_ = 14;

    uint8_t ix_low_byte = ram_read(stack_pointer_);
    stack_pointer_++;

    uint8_t ix_high_byte = ram_read(stack_pointer_);
    stack_pointer_++;

    index_register_x_ = static_cast<uint16_t>(ix_high_byte << 8) | ix_low_byte;
}


void z80cpu::POP_register_indirect_register_iy() {
    t_state_cycles_ = 14;

    uint8_t iy_low_byte = ram_read(stack_pointer_);
    stack_pointer_++;

    uint8_t iy_high_byte = ram_read(stack_pointer_);
    stack_pointer_++;

    index_register_y_ = static_cast<uint16_t>(iy_high_byte << 8) | iy_low_byte;
}