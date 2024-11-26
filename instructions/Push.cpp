#include "../z80.hpp"

void z80cpu::PUSH_register_indirect_register() {
    t_state_cycles_ = 11;

    temp_data_8_ = (opcode_ & BIT_MASK_3) >> 4;

    stack_pointer_--;
    rom_write(stack_pointer_, *register_pair_table_qq_[temp_data_8_].high_byte_register);
    stack_pointer_--;
    rom_write(stack_pointer_, *register_pair_table_qq_[temp_data_8_].low_byte_register);
}


void z80cpu::PUSH_register_indirect_register_ix() {
    t_state_cycles_ = 15;

    uint8_t ix_high_byte = static_cast<uint8_t>(index_register_x_ >> 8);
    uint8_t ix_low_byte = static_cast<uint8_t>(index_register_x_);

    stack_pointer_--;
    rom_write(stack_pointer_, ix_high_byte);

    stack_pointer_--;
    rom_write(stack_pointer_, ix_low_byte);
}


void z80cpu::PUSH_register_indirect_register_iy() {
    t_state_cycles_ = 15;

    uint8_t iy_high_byte = static_cast<uint8_t>(index_register_y_ >> 8);
    uint8_t iy_low_byte = static_cast<uint8_t>(index_register_y_);

    stack_pointer_--;
    rom_write(stack_pointer_, iy_high_byte);

    stack_pointer_--;
    rom_write(stack_pointer_, iy_low_byte);
}