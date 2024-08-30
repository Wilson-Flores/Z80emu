#include "../z80.hpp"


void z80cpu::SET_implied() {
    t_state_cycles = 8;

    // data_8 will store what bit value we will be setting.
    // register value will store the value at the register we want to work with.
    data_8 = (opcode & BIT_MASK_1) >> 3;

    // we will perform an OR operation with the desired bit value.
    // ex. SET 6, A; where A = 0x80
    //  0b10000000 | 0b01000000 = 0b11000000
    *register_table[opcode & BIT_MASK_2] |= bit_masks[data_8];

    // No flag conditions affected
}
