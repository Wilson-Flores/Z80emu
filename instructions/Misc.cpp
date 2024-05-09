#include "../z80.hpp"

void z80cpu::CCF_complement_carry_flag(){
    t_state_cycles = 4;

    // H, previous carry is copied
    set_flag(HALF_CARRY_FLAG, get_flag(CARRY_FLAG));
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if CY was 0 before operation; otherwise, it is reset
    set_flag(CARRY_FLAG, (get_flag(CARRY_FLAG) == 0) ? 1 : 0);
}