#include "../z80.hpp"


void z80cpu::SET_implied() {
    t_state_cycles_ = 8;

    // data_8 will store what bit value we will be setting.
    temp_data_8_ = (opcode_ & BIT_MASK_1) >> 3;

    // we will perform an OR operation with the desired bit value.
    // ex. SET 6, A; where A = 0x80
    //  0b10000000 | 0b01000000 = 0b11000000
    *register_table_[opcode_ & BIT_MASK_2] |= SET_BIT_MASKS[temp_data_8_];

    // No flag conditions affected
}


void z80cpu::SET_indirect() {
    t_state_cycles_ = 15;

    // data_8 will store what bit value we will be setting.
    temp_data_8_ = (opcode_ & BIT_MASK_1) >> 3;

    // get value at (HL) memory address
    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_result_8_ = ram_read(temp_memory_address_);

    // we will perform an OR operation with the desired bit value.
    temp_result_8_ |= SET_BIT_MASKS[temp_data_8_];

    // re-write the value at the memory address
    ram_write(temp_memory_address_, temp_result_8_);
}


void z80cpu::SET_indexed_ix() {
    t_state_cycles_ = 23;

    // data_8 will store what bit value we will be setting.
    temp_data_8_ = (opcode_ & BIT_MASK_1) >> 3;

    // copy the data from the memory address
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);
    temp_result_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // we will perform an OR operation with the desired bit value.
    temp_result_8_ |= SET_BIT_MASKS[temp_data_8_];

    // re-write the value at the memory address
    ram_write(temp_memory_address_, temp_result_8_);
}


void z80cpu::SET_indexed_iy() {
    t_state_cycles_ = 23;

    // data_8 will store what bit value we will be setting.
    temp_data_8_ = (opcode_ & BIT_MASK_1) >> 3;

    // copy the data from the memory address
    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);
    temp_result_8_ = ram_read(temp_memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    // we will perform an OR operation with the desired bit value.
    temp_result_8_ |= SET_BIT_MASKS[temp_data_8_];

    // re-write the value at the memory address
    ram_write(temp_memory_address_, temp_result_8_);
}