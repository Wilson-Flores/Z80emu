#include "../z80.hpp"

void z80cpu::PUSH_register_indirect_register() {
    t_state_cycles = 11;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;

    // allow the stack point to wrap around once it reaches 0
    if(stack_pointer == 0x0000){
        stack_pointer = 0xFFFF;
    }
    else{
        stack_pointer--;
    }

    write(stack_pointer, *register_pair_table[register_pair_bit].high_byte_register);

    if(stack_pointer == 0x0000){
        stack_pointer = 0xFFFF;
    }
    else{
        stack_pointer--;
    }

    write(stack_pointer, *register_pair_table[register_pair_bit].low_byte_register);
}


void z80cpu::PUSH_register_indirect_register_ix() {
    t_state_cycles = 15;

    uint8_t ix_high_byte;
    ix_high_byte = static_cast<uint8_t>(index_register_x >> 8);
    uint8_t ix_low_byte;
    ix_low_byte = static_cast<uint8_t>(index_register_x);

    if(stack_pointer == 0x0000){
        stack_pointer = 0xFFFF;
    }
    else{
        stack_pointer--;
    }

    write(stack_pointer, ix_high_byte);

    if(stack_pointer == 0x0000){
        stack_pointer = 0xFFFF;
    }
    else{
        stack_pointer--;
    }

    write(stack_pointer, ix_low_byte);
}


void z80cpu::PUSH_register_indirect_register_iy() {
    t_state_cycles = 15;

    uint8_t iy_high_byte;
    iy_high_byte = static_cast<uint8_t>(index_register_y >> 8);
    uint8_t iy_low_byte;
    iy_low_byte = static_cast<uint8_t>(index_register_y);

    if(stack_pointer == 0x0000){
        stack_pointer = 0xFFFF;
    }
    else{
        stack_pointer--;
    }

    write(stack_pointer, iy_high_byte);

    if(stack_pointer == 0x0000){
        stack_pointer = 0xFFFF;
    }
    else{
        stack_pointer--;
    }

    write(stack_pointer, iy_low_byte);
}