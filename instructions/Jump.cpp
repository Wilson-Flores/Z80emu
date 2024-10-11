#include "../z80.hpp"


void z80cpu::JP_immediate() {
    t_state_cycles = 10;

    data_8 = rom_read(program_counter);
    program_counter++;

    data_16 = (static_cast<uint16_t>(rom_read(program_counter)) << 8) + data_8;
    program_counter++;

    program_counter = data_16;

    // WZ_registers stores the program counter value
    WZ_register = program_counter;
}


void z80cpu::JP_cc_immediate() {
    t_state_cycles = 10;
    
    result_8 = (opcode & BIT_MASK_1) >> 3;

    data_8 = rom_read(program_counter);
    program_counter++;

    data_16 = static_cast<uint16_t>(rom_read(program_counter)) << 8;
    program_counter++;

    data_16 += data_8;

    switch (result_8) {
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
        default: break;
    }

    // WZ_registers stores the program counter value
    WZ_register = program_counter;
}


void z80cpu::JR_relative() {
    t_state_cycles = 12;

    // How this originally works
    // PC = (PC + 2) + displacement
    // (PC + 2): PC is the program counter value before the instruction cycle starts.

    // Instruction cycle increments PC by 1.
    // We increment again after reading the displacement value

    // we just preform a regular PC += displacement
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;

    program_counter += static_cast<int16_t>(displacement);
    WZ_register = program_counter;
}


void z80cpu::JR_cc_relative() {
// T cycles will be decided if conditions are met or not

    result_8 = (opcode & BIT_MASK_4) >> 3;
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;

    switch (result_8)
    {
    case 0:
        if(get_flag(ZERO_FLAG) == 0){
            t_state_cycles = 12;
            program_counter += static_cast<int16_t>(displacement);
            WZ_register = program_counter;
        }
        else
        {
            t_state_cycles = 7;
        }
        break;
    case 1:
        if(get_flag(ZERO_FLAG) == 1){
            t_state_cycles = 12;
            program_counter += static_cast<int16_t>(displacement);
            WZ_register = program_counter;
        }
        else
        {
            t_state_cycles = 7;
        }
        break;
    case 2:
        if(get_flag(CARRY_FLAG) == 0){
            t_state_cycles = 12;
            program_counter += static_cast<int16_t>(displacement);
            WZ_register = program_counter;
        }
        else
        {
            t_state_cycles = 7;
        }
        break;
    case 3:
        if(get_flag(CARRY_FLAG) == 1){
            t_state_cycles = 12;
            program_counter += static_cast<int16_t>(displacement);
            WZ_register = program_counter;
        }
        else
        {
            t_state_cycles = 7;
        }
        break;
    default: break;
    }
}


void z80cpu::JP_implict() {
    t_state_cycles = 4;

    memory_address = (static_cast<uint16_t>(H_register) << 8) | L_register;
    program_counter = memory_address;
}


void z80cpu::JP_implict_ix() {
    t_state_cycles = 8;

    program_counter = index_register_x;
}


void z80cpu::JP_implict_iy() {
    t_state_cycles = 8;

    program_counter = index_register_y;
}


void z80cpu::DJNZ_immediate() {
    // the amount of cycles will be determined after finding out the value of register B

    // first we decrement the b register.
    B_register--;

    // we have to retrieve the offset value before we do anything to push the program counter forward.
    // How this originally works
    // PC = (PC + 2) + displacement
    // (PC + 2): PC is the program counter value before the instruction cycle starts.

    // Instruction cycle increments PC by 1.
    // We increment again after reading the displacement value
    // we just preform a regular PC += displacement
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;

    if(B_register != 0)
    {
        t_state_cycles = 13;
        program_counter += static_cast<int16_t>(displacement);
        WZ_register = program_counter;
    }
    else
    {
        // when B == 0, we do nothing.
        t_state_cycles = 8;
    }
}