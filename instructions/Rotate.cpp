#include "../z80.hpp"


void z80cpu::RLCA_implied() {
    t_state_cycles = 4;

    // isolate leading bit in accumulator, then overwrite the carry bit in the flag register
    // first we clear out the carry bit
    flag_register &= 0xFE;
    flag_register |= (accumulator >> 7);

    // rotate accumulator bits 1 to the left, then add 7th bit
    accumulator = (accumulator << 1) + (accumulator >> 7);

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is data from bit 7 of Accumulator
}


void z80cpu::RLC_implied() {

}