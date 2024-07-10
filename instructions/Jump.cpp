#include "../z80.hpp"


void z80cpu::JP_immediate() {
    t_state_cycles = 10;

    data_8 = rom_read(program_counter);
    program_counter++;

    data_16 = static_cast<uint16_t>(rom_read(program_counter)) << 8;
    program_counter++;

    data_16 += data_8;
    program_counter = data_16;
}


void z80cpu::JP_cc_immediate() {
    t_state_cycles = 10;
    
    uint8_t cc_bit = (opcode & BIT_MASK_1) >> 3;

    data_8 = rom_read(program_counter);
    program_counter++;

    data_16 = static_cast<uint16_t>(rom_read(program_counter)) << 8;
    program_counter++;

    data_16 += data_8;

    switch (cc_bit) {
        case 0:
            if(get_flag(ZERO_FLAG) == 0){
                program_counter = data_16;
            }
            break;
        case 1:
            if(get_flag(ZERO_FLAG) == 1){
                program_counter = data_16;
            }
            break;
        case 2:
            if(get_flag(CARRY_FLAG) == 0){
                program_counter = data_16;
            }
            break;
        case 3:
            if(get_flag(CARRY_FLAG) == 1){
                program_counter = data_16;
            }
            break;
        case 4:
            if(get_flag(PARITY_OVERFLOW_FLAG) == 0){
                program_counter = data_16;
            }
            break;
        case 5:
            if(get_flag(PARITY_OVERFLOW_FLAG) == 1){
                program_counter = data_16;
            }
            break;
        case 6:
            if(get_flag(ADD_SUB_FLAG) == 0){
                program_counter = data_16;
            }
            break;
        case 7:
            if(get_flag(ADD_SUB_FLAG) == 1){
                program_counter = data_16;
            }
            break;
    }
}