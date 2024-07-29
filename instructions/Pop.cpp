#include "../z80.hpp"

void z80cpu::POP_register_indirect_register() {
    t_state_cycles = 10;

    data_8 = (opcode & BIT_MASK_3) >> 4;

    *register_pair_table_qq[data_8].low_byte_register = ram_read(stack_pointer);
    stack_pointer++;

    *register_pair_table_qq[data_8].high_byte_register = ram_read(stack_pointer);
    stack_pointer++;
}


void z80cpu::POP_register_indirect_register_ix() {
    t_state_cycles = 14;

    uint8_t ix_low_byte = ram_read(stack_pointer);
    stack_pointer++;

    uint8_t ix_high_byte = ram_read(stack_pointer);
    stack_pointer++;

    index_register_x = static_cast<uint16_t>(ix_high_byte << 8) | ix_low_byte;
}


void z80cpu::POP_register_indirect_register_iy() {
    t_state_cycles = 14;

    uint8_t iy_low_byte = ram_read(stack_pointer);
    stack_pointer++;

    uint8_t iy_high_byte = ram_read(stack_pointer);
    stack_pointer++;

    index_register_y = static_cast<uint16_t>(iy_high_byte << 8) | iy_low_byte;
}