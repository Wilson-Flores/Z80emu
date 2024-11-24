#include "../z80.hpp"


void z80cpu::JP_immediate() {
    t_state_cycles_ = 10;

    temp_data_8_ = rom_read(program_counter_);
    program_counter_++;

    temp_data_16_ = (static_cast<uint16_t>(rom_read(program_counter_)) << 8) + temp_data_8_;
    program_counter_++;

    program_counter_ = temp_data_16_;

    // WZ_registers stores the program counter value
    WZ_register_ = program_counter_;
}


void z80cpu::JP_cc_immediate() {
    t_state_cycles_ = 10;

    temp_result_8_ = (opcode_ & BIT_MASK_1) >> 3;

    temp_data_8_ = rom_read(program_counter_);
    program_counter_++;

    temp_data_16_ = static_cast<uint16_t>(rom_read(program_counter_)) << 8;
    program_counter_++;

    temp_data_16_ += temp_data_8_;

    switch (temp_result_8_) {
        case 0:
            if(get_flag(ZERO_FLAG) == 0){
                program_counter_ = temp_data_16_;
            }
            break;
        case 1:
            if(get_flag(ZERO_FLAG) == 1){
                program_counter_ = temp_data_16_;
            }
            break;
        case 2:
            if(get_flag(CARRY_FLAG) == 0){
                program_counter_ = temp_data_16_;
            }
            break;
        case 3:
            if(get_flag(CARRY_FLAG) == 1){
                program_counter_ = temp_data_16_;
            }
            break;
        case 4:
            if(get_flag(PARITY_OVERFLOW_FLAG) == 0){
                program_counter_ = temp_data_16_;
            }
            break;
        case 5:
            if(get_flag(PARITY_OVERFLOW_FLAG) == 1){
                program_counter_ = temp_data_16_;
            }
            break;
        case 6:
            if(get_flag(ADD_SUB_FLAG) == 0){
                program_counter_ = temp_data_16_;
            }
            break;
        case 7:
            if(get_flag(ADD_SUB_FLAG) == 1){
                program_counter_ = temp_data_16_;
            }
            break;
        default: break;
    }

    // WZ_registers stores the program counter value
    WZ_register_ = program_counter_;
}


void z80cpu::JR_relative() {
    t_state_cycles_ = 12;

    // How this originally works
    // PC = (PC + 2) + displacement
    // (PC + 2): PC is the program counter value before the instruction cycle starts.

    // Instruction cycle increments PC by 1.
    // We increment again after reading the displacement value

    // we just preform a regular PC += displacement
    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    program_counter_ += static_cast<int16_t>(temp_displacement_);
    WZ_register_ = program_counter_;
}


void z80cpu::JR_cc_relative() {
// T cycles will be decided if conditions are met or not

    temp_result_8_ = (opcode_ & BIT_MASK_4) >> 3;
    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    switch (temp_result_8_)
    {
    case 0:
        if(get_flag(ZERO_FLAG) == 0){
            t_state_cycles_ = 12;
            program_counter_ += static_cast<int16_t>(temp_displacement_);
            WZ_register_ = program_counter_;
        }
        else
        {
            t_state_cycles_ = 7;
        }
        break;
    case 1:
        if(get_flag(ZERO_FLAG) == 1){
            t_state_cycles_ = 12;
            program_counter_ += static_cast<int16_t>(temp_displacement_);
            WZ_register_ = program_counter_;
        }
        else
        {
            t_state_cycles_ = 7;
        }
        break;
    case 2:
        if(get_flag(CARRY_FLAG) == 0){
            t_state_cycles_ = 12;
            program_counter_ += static_cast<int16_t>(temp_displacement_);
            WZ_register_ = program_counter_;
        }
        else
        {
            t_state_cycles_ = 7;
        }
        break;
    case 3:
        if(get_flag(CARRY_FLAG) == 1){
            t_state_cycles_ = 12;
            program_counter_ += static_cast<int16_t>(temp_displacement_);
            WZ_register_ = program_counter_;
        }
        else
        {
            t_state_cycles_ = 7;
        }
        break;
    default: break;
    }
}


void z80cpu::JP_implicit() {
    t_state_cycles_ = 4;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    program_counter_ = temp_memory_address_;
}


void z80cpu::JP_implicit_ix() {
    t_state_cycles_ = 8;

    program_counter_ = index_register_x_;
}


void z80cpu::JP_implicit_iy() {
    t_state_cycles_ = 8;

    program_counter_ = index_register_y_;
}


void z80cpu::DJNZ_immediate() {
    // the amount of cycles will be determined after finding out the value of register B

    // first we decrement the b register.
    B_register_--;

    // we have to retrieve the offset value before we do anything to push the program counter forward.
    // How this originally works
    // PC = (PC + 2) + displacement
    // (PC + 2): PC is the program counter value before the instruction cycle starts.

    // Instruction cycle increments PC by 1.
    // We increment again after reading the displacement value
    // we just preform a regular PC += displacement
    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    if(B_register_ != 0)
    {
        t_state_cycles_ = 13;
        program_counter_ += static_cast<int16_t>(temp_displacement_);
        WZ_register_ = program_counter_;
    }
    else
    {
        // when B == 0, we do nothing.
        t_state_cycles_ = 8;
    }
}