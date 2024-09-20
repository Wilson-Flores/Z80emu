#include "../z80.hpp"


void z80cpu::SET_implied() {
    t_state_cycles = 8;

    // data_8 will store what bit value we will be setting.
    data_8 = (opcode & BIT_MASK_1) >> 3;

    // we will perform an OR operation with the desired bit value.
    // ex. SET 6, A; where A = 0x80
    //  0b10000000 | 0b01000000 = 0b11000000
    *register_table[opcode & BIT_MASK_2] |= BIT_MASKS[data_8];

    // No flag conditions affected
}


void z80cpu::SET_indirect() {
    t_state_cycles = 15;

    // data_8 will store what bit value we will be setting.
    data_8 = (opcode & BIT_MASK_1) >> 3;

    // get value at (HL) memory address
    memory_address = (static_cast<uint16_t>(H_register) << 8) | L_register;
    result_8 = ram_read(memory_address);

    // we will perform an OR operation with the desired bit value.
    result_8 |= BIT_MASKS[data_8];

    // re-write the value at the memory address
    ram_write(memory_address, result_8);
}


void z80cpu::SET_indexed_ix() {
    t_state_cycles = 23;

    // data_8 will store what bit value we will be setting.
    data_8 = (opcode & BIT_MASK_1) >> 3;

    // copy the data from the memory address
    memory_address = index_register_x + static_cast<int16_t>(displacement);
    result_8 = ram_read(memory_address);

    // WZ register is updated using memory address
    WZ_register = memory_address;

    // we will perform an OR operation with the desired bit value.
    result_8 |= BIT_MASKS[data_8];

    // re-write the value at the memory address
    ram_write(memory_address, result_8);
}


void z80cpu::SET_indexed_iy() {
    t_state_cycles = 23;

    // data_8 will store what bit value we will be setting.
    data_8 = (opcode & BIT_MASK_1) >> 3;

    // copy the data from the memory address
    memory_address = index_register_y + static_cast<int16_t>(displacement);
    result_8 = ram_read(memory_address);

    // WZ register is updated using memory address
    WZ_register = memory_address;

    // we will perform an OR operation with the desired bit value.
    result_8 |= BIT_MASKS[data_8];

    // re-write the value at the memory address
    ram_write(memory_address, result_8);
}