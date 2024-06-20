#include "../z80.hpp"


void z80cpu::SLA_implied() {
    t_state_cycles = 8;

    // copy the data from the register
    data = *register_table[opcode & BIT_MASK_2];

    // clear the carry flag bit
    flag_register &= 0xFE;
    // copy data 7th bit into carry flag bit
    flag_register |= (data >> 7);

    // shift bits to the left and rewrite data in register
    result = data << 1;
    *register_table[opcode & BIT_MASK_2] = result;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is set if parity even, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[result]);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of source register
}


void z80cpu::SLA_indirect() {

}


void z80cpu::SLA_indexed_ix() {

}


void z80cpu::SLA_indexed_iy() {

}
