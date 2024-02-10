#include "../z80.hpp"

void z80cpu::EX_implied_implied_af() {
    t_state_cycles = 4;
    // use XOR to swap without needing another temp variable

    accumulator ^= alt_accumulator;
    alt_accumulator ^= accumulator;
    accumulator ^= alt_accumulator;

    flag_register ^= alt_flag_register;
    alt_flag_register ^= flag_register;
    flag_register ^= alt_flag_register;
}


void z80cpu::EXX_implied_implied() {
    t_state_cycles = 4;
    // use XOR to swap without needing another temp variable

    for(uint8_t i = 0; i < 6; i++){
        *register_table[i] ^= *alt_register_table[i];
        *alt_register_table[i] ^= *register_table[i];
        *register_table[i] ^= *alt_register_table[i];
    }
}

void z80cpu::EX_implied_implied() {
    t_state_cycles = 4;

    D_register ^= H_register;
    H_register ^= D_register;
    D_register ^= H_register;

    E_register ^= L_register;
    L_register ^= E_register;
    E_register ^= L_register;
}


void z80cpu::EX_register_indirect_implied_hl() {

    t_state_cycles = 19;

    uint8_t low_byte_data = read(stack_pointer);
    L_register ^= low_byte_data;
    low_byte_data ^= L_register;
    L_register ^= low_byte_data;

    uint8_t high_byte_data = read(stack_pointer + 1);


}