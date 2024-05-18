#include "../z80.hpp"

void z80cpu::CCF_implied(){
    // Complement carry flag
    t_state_cycles = 4;

    // H, previous carry is copied
    set_flag(HALF_CARRY_FLAG, get_flag(CARRY_FLAG));
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if CY was 0 before operation; otherwise, it is reset
    set_flag(CARRY_FLAG, (get_flag(CARRY_FLAG) == 0) ? 1 : 0);
}


void z80cpu::NEG_implied() {
    // Negate accumulator
    // contents of the accumulator are subtracted from zero ( two's complement) and stored back into the accumulator.
    // A = 0 - A
    t_state_cycles = 8;

    uint8_t result = ~accumulator + 1;

    // S is set if result is negative; otherwise it is reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else it is reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else it is reset
    // 0 - (anything != 0) will always need to borrow, we can use > 0 as well.
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) > 0);
    // P/V is set if Accumulator was 80h before operation, else it is reset
    set_flag(PARITY_OVERFLOW_FLAG, accumulator == 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if Accumulator was not 00h before operation, else it is reset
    set_flag(CARRY_FLAG, accumulator != 0);

    accumulator = result;
}


void z80cpu::CPL_implied() {
    // Complement accumulator
    // the contents of the accumulator are inverted (one's complement).
    // A = ~A
    t_state_cycles = 4;

    // S is not affected
    // Z is not affected
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is not affected
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is not affected

    accumulator = ~accumulator;
}


void z80cpu::SCF_implied() {
    // The Carry flag is set
    t_state_cycles = 4;

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set
    set_flag(CARRY_FLAG, true);
}


