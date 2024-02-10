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

    uint8_t data = read(stack_pointer);  // low byte in HL is swapped with memory at stack pointer address
    L_register ^= data;
    data ^= L_register;
    L_register ^= data;
    write(stack_pointer, data);

    data = read(stack_pointer + 1);     // high byte in HL is swapped with memory at (stack pointer + 1) address
    H_register ^= data;
    data ^= H_register;
    H_register ^= data;
    write(stack_pointer + 1, data);
}


void z80cpu::EX_register_indirect_implied_ix() {
    t_state_cycles = 19;

    uint16_t data = static_cast<uint16_t>(read(stack_pointer) << 8) | read(stack_pointer + 1);
    index_register_x ^= data;
    data ^= index_register_x;
    index_register_x ^= data;

    write(stack_pointer, static_cast<uint8_t>(data >> 8));
    write(stack_pointer + 1, static_cast<uint8_t>(data));

}