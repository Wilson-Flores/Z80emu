#include "z80.hpp"

void z80cpu::POP_register_indirect_register() {
    t_state_cycles = 10;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3);

    *register_pair_table[register_pair_bit].low_byte_register = read(stack_pointer);

    if(stack_pointer == 0xFFFF){
        stack_pointer = 0x0000;
    }
    else{
        stack_pointer++;
    }

    *register_pair_table[register_pair_bit].high_byte_register = read(stack_pointer);

    if(stack_pointer == 0xFFFF){
        stack_pointer = 0x0000;
    }
    else{
        stack_pointer++;
    }
}


void z80cpu::POP_register_indirect_register_ix() {
    t_state_cycles = 14;

    uint8_t ix_low_byte = read(stack_pointer);

    if(stack_pointer == 0xFFFF){
        stack_pointer = 0x0000;
    }
    else{
        stack_pointer++;
    }

    uint8_t ix_high_byte = read(stack_pointer);

    if(stack_pointer == 0xFFFF){
        stack_pointer = 0x0000;
    }
    else{
        stack_pointer++;
    }

    index_register_x = static_cast<uint16_t>(ix_high_byte << 8) | ix_low_byte;
}


void z80cpu::POP_register_indirect_register_iy() {
    t_state_cycles = 14;

    uint8_t iy_low_byte = read(stack_pointer);

    if(stack_pointer == 0xFFFF){
        stack_pointer = 0x0000;
    }
    else{
        stack_pointer++;
    }

    uint8_t iy_high_byte = read(stack_pointer);

    if(stack_pointer == 0xFFFF){
        stack_pointer = 0x0000;
    }
    else{
        stack_pointer++;
    }

    index_register_y = static_cast<uint16_t>(iy_high_byte << 8) | iy_low_byte;
}