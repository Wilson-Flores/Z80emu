#include "../z80.hpp"



// 8-bit LD Instructions
void z80cpu::LD_register_immediate() {
    t_state_cycles_ = 7;

    // bit mask the opcode to find the register value
    // destination_register_bit = (opcode & BIT_MASK_1) >> 3;
    *register_table_[(opcode_ & BIT_MASK_1) >> 3] = rom_read(program_counter_);

    // Increment program counter again to avoid instruction cycle from mistaking 'n' value for an opcode
    program_counter_++;
}


void z80cpu::LD_register_register() {
    t_state_cycles_ = 4;

    // bit mask the opcode to find the register destination value and source register value
    // destination_register_bit = (opcode & BIT_MASK_1) >> 3;
    // source_register_bit = (opcode & BIT_MASK_2);

    *register_table_[(opcode_ & BIT_MASK_1) >> 3] = *register_table_[(opcode_ & BIT_MASK_2)];
}


void z80cpu::LD_register_register_indirect() {
    t_state_cycles_ = 7;

    // bit mask the opcode to find the register value
    // destination_register_bit = (opcode & BIT_MASK_1) >> 3;
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    *register_table_[(opcode_ & BIT_MASK_1) >> 3] = ram_read(memory_address_);
}


void z80cpu::LD_register_register_indirect_BC() {
    t_state_cycles_ = 7;

    memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;
    // WZ register is BC address plus 1
    WZ_register_ = memory_address_ + 1;
    accumulator_ = ram_read(memory_address_);
}


void z80cpu::LD_register_register_indirect_DE() {
    t_state_cycles_ = 7;

    memory_address_ = (static_cast<uint16_t>(D_register_) << 8) | E_register_;
    // WZ register is DE address plus 1
    WZ_register_ = memory_address_ + 1;
    accumulator_ = ram_read(memory_address_);
}


void z80cpu::LD_register_implied_R() {
    t_state_cycles_ = 9;

    // Half Carry flag is reset.
    set_flag(HALF_CARRY_FLAG, false);
    // Add/Subtract flag is reset.
    set_flag(ADD_SUB_FLAG, false);
    // P/V contains contents of IFF2
    set_flag(PARITY_OVERFLOW_FLAG, interrupt_enable_flip_flop_2_);
    // Sign Flag is set if I is negative, else it is reset.
    set_flag(SIGN_FLAG, (memory_refresh_register_ >> 7) == 0x01);
    // Zero Flag is set if I equals 0, else it is reset.
    set_flag(SIGN_FLAG, memory_refresh_register_ == 0x00);

    accumulator_ = memory_refresh_register_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::LD_register_implied_I() {
    t_state_cycles_ = 9;

    // Half Carry flag is reset.
    set_flag(HALF_CARRY_FLAG, false);
    // Add/Subtract flag is reset.
    set_flag(ADD_SUB_FLAG, false);
    // P/V contains contents of IFF2
    set_flag(PARITY_OVERFLOW_FLAG, interrupt_enable_flip_flop_2_);
    // Sign Flag is set if I is negative, else it is reset.
    set_flag(SIGN_FLAG, (interrupt_vector_register_ >> 7) == 0x01);
    // Zero Flag is set if I equals 0, else it is reset.
    set_flag(ZERO_FLAG, interrupt_vector_register_ == 0x00);

    accumulator_ = interrupt_vector_register_;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator_ & 0x08);
    set_flag(Y_FLAG, accumulator_ & 0x20);
}


void z80cpu::LD_register_indexed_ix() {
    t_state_cycles_ = 19;

    // one-byte signed integer (-128 to +127)
    displacement_ = static_cast<int8_t>(rom_read(program_counter_));

    // add the value in index register x with the twos-complement signed value
    WZ_register_ = index_register_x_ + static_cast<int16_t>(displacement_);
    // register_bit = (opcode & BIT_MASK_1) >> 3;
    *register_table_[(opcode_ & BIT_MASK_1) >> 3] = ram_read(WZ_register_);

    program_counter_++;
}


void z80cpu::LD_register_indexed_iy() {
    t_state_cycles_ = 19;

    // one-byte signed integer (-128 to +127)
    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    // add the value in ind
    // ex register x with the twos-complement signed value
    WZ_register_ = index_register_y_ + static_cast<int16_t>(displacement_);
    // register_bit = (opcode & BIT_MASK_1) >> 3;
    *register_table_[(opcode_ & BIT_MASK_1) >> 3] = ram_read(WZ_register_);
}


void z80cpu::LD_register_extended() {
    t_state_cycles_ = 4;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;

    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    // WZ register is (nn) address plus 1
    WZ_register_ = memory_address_ + 1;
    accumulator_ = ram_read(memory_address_);
}


void z80cpu::LD_register_indirect_immediate() {
    t_state_cycles_ = 3;

    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = rom_read(program_counter_);
    program_counter_++;

    ram_write(memory_address_, data_8_);
}


void z80cpu::LD_register_indirect_register() {
    t_state_cycles_ = 7;

    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    // the data from the register will be written to the address location
    // register_bit = (opcode & BIT_MASK_2);
    ram_write(memory_address_, *register_table_[(opcode_ & BIT_MASK_2)]);
}


void z80cpu::LD_register_indirect_register_BC() {
    t_state_cycles_ = 7;

    // WZ register high byte is the accumulator value, low byte is C register value + 1
    WZ_register_ = (static_cast<uint16_t>(accumulator_) << 8) | static_cast<uint16_t>(C_register_ + 1);
    memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;
    ram_write(memory_address_, accumulator_);
}


void z80cpu::LD_register_indirect_register_DE() {
    t_state_cycles_ = 7;

    // WZ register high byte is the accumulator value, low byte is E register value + 1
    WZ_register_ = (static_cast<uint16_t>(accumulator_) << 8) | static_cast<uint16_t>(E_register_ + 1);
    memory_address_ = (static_cast<uint16_t>(D_register_) << 8) | E_register_;
    ram_write(memory_address_, accumulator_);

}


void z80cpu::LD_indexed_ix_immediate(){
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    data_8_ = rom_read(program_counter_);
    program_counter_++;

    WZ_register_ = index_register_x_ + static_cast<int16_t>(displacement_);

    ram_write(WZ_register_, data_8_);
}


void z80cpu::LD_indexed_iy_immediate() {
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    data_8_ = rom_read(program_counter_);
    program_counter_++;

    WZ_register_ = index_register_y_ + static_cast<int16_t>(displacement_);

    ram_write(WZ_register_, data_8_);
}


void z80cpu::LD_indexed_ix_register(){
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    WZ_register_ = index_register_x_ + static_cast<int16_t>(displacement_);
    // register_bit = (opcode & BIT_MASK_2);
    ram_write(WZ_register_, *register_table_[opcode_ & BIT_MASK_2]);
}


void z80cpu::LD_indexed_iy_register(){
    t_state_cycles_ = 19;

    displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;

    WZ_register_ = index_register_y_ + static_cast<int16_t>(displacement_);
    // register_bit = (opcode & BIT_MASK_2);
    ram_write(WZ_register_, *register_table_[opcode_ & BIT_MASK_2]);
}


void z80cpu::LD_extended_register() {
    t_state_cycles_ = 13;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;

    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    // WZ register high byte is the accumulator value, low byte is (nn)'s low byte value + 1
    WZ_register_ = (static_cast<uint16_t>(accumulator_) << 8) | static_cast<uint16_t>(low_byte + 1);
    ram_write(memory_address_, accumulator_);
}


void z80cpu::LD_implied_register_I() {
    t_state_cycles_ = 9;

    interrupt_vector_register_ = accumulator_;
}


void z80cpu::LD_implied_register_R() {
    t_state_cycles_ = 9;

    memory_refresh_register_ = accumulator_;
}


// 16-bit LD Instructions
void z80cpu::LD_register_immediate_extended_16_bit() {
    t_state_cycles_ = 10;

    data_8_ = (opcode_ & BIT_MASK_3) >> 4;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;

    *register_pair_table_ss_[data_8_].high_byte_register = high_byte;
    *register_pair_table_ss_[data_8_].low_byte_register = low_byte;
}


void z80cpu::LD_register_immediate_extended_ix() {
    t_state_cycles_ = 14;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;

    data_16_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    index_register_x_ = data_16_;
}


void z80cpu::LD_register_immediate_extended_iy() {
    t_state_cycles_ = 14;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;

    data_16_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    index_register_y_ = data_16_;
}


void z80cpu::LD_register_extended_16_bit() {
    t_state_cycles_ = 20;

    data_8_ = (opcode_ & BIT_MASK_3) >> 4;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;
    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    // wz register is the memory address + 1
    WZ_register_ = memory_address_ + 1;

    *register_pair_table_ss_[data_8_].high_byte_register = ram_read(memory_address_ + 1);
    *register_pair_table_ss_[data_8_].low_byte_register = ram_read(memory_address_);
}


void z80cpu::LD_register_extended_hl() {
    t_state_cycles_ = 16;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;
    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    // wz register is the memory address + 1
    WZ_register_ = memory_address_ + 1;

    H_register_ = ram_read(memory_address_ + 1);
    L_register_ = ram_read(memory_address_);
}


void z80cpu::LD_register_extended_ix() {
    t_state_cycles_ = 20;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;
    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    // wz register is the memory address + 1
    WZ_register_ = memory_address_ + 1;

    index_register_x_ = (static_cast<uint16_t>(ram_read(memory_address_ + 1))) << 8 | ram_read(memory_address_);
}


void z80cpu::LD_register_extended_iy() {
    t_state_cycles_ = 20;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;
    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    // wz register is the memory address + 1
    WZ_register_ = memory_address_ + 1;

    index_register_y_ = (static_cast<uint16_t>(ram_read(memory_address_ + 1))) << 8 | ram_read(memory_address_);
}


void z80cpu::LD_register_register_hl() {
    t_state_cycles_ = 6;

    stack_pointer_ = (static_cast<uint16_t>(H_register_)) << 8 | L_register_;
}


void z80cpu::LD_register_register_ix() {
    t_state_cycles_ = 10;

    stack_pointer_ = index_register_x_;
}


void z80cpu::LD_register_register_iy() {
    t_state_cycles_ = 10;

    stack_pointer_ = index_register_y_;
}


void z80cpu::LD_extended_register_16_bit() {
    t_state_cycles_ = 20;

    data_8_ = (opcode_ & BIT_MASK_3) >> 4;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;
    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    // wz register is the memory address + 1
    WZ_register_ = memory_address_ + 1;

    // register_high_byte = *register_pair_table_ss[data_8].high_byte_register;
    // register_low_byte = *register_pair_table_ss[data_8].low_byte_register;
    ram_write(memory_address_, *register_pair_table_ss_[data_8_].low_byte_register);
    ram_write(memory_address_ + 1, *register_pair_table_ss_[data_8_].high_byte_register);
}


void z80cpu::LD_extended_register_hl() {
    t_state_cycles_ = 16;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;
    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    // wz register is the memory address + 1
    WZ_register_ = memory_address_ + 1;

    ram_write(memory_address_, L_register_);
    ram_write(memory_address_ + 1, H_register_);
}


void z80cpu::LD_extended_register_ix() {
    t_state_cycles_ = 20;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;
    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    // wz register is the memory address + 1
    WZ_register_ = memory_address_ + 1;

    // ix low byte
    data_8_ = static_cast<uint8_t>(index_register_x_ & LOW_BYTE_MASK);
    ram_write(memory_address_, data_8_);
    // ix high byte
    data_8_ = static_cast<uint8_t>(index_register_x_ >> 8);
    ram_write(memory_address_ + 1, data_8_);
}


void z80cpu::LD_extended_register_iy() {
    t_state_cycles_ = 20;

    uint8_t low_byte = rom_read(program_counter_);
    program_counter_++;
    uint8_t high_byte = rom_read(program_counter_);
    program_counter_++;
    memory_address_ = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    // wz register is the memory address + 1
    WZ_register_ = memory_address_ + 1;

    // iy low byte
    data_8_ = static_cast<uint8_t>(index_register_y_ & LOW_BYTE_MASK);
    ram_write(memory_address_, data_8_);
    // iy high byte
    data_8_ = static_cast<uint8_t>(index_register_y_ >> 8);
    ram_write(memory_address_ + 1, data_8_);
}


// Block Transfer Instructions - The concept is the same as an LD instruction.
void z80cpu::LDI_register_indirect_register_indirect() {
    t_state_cycles_ = 16;

    // We get the data from the address location of HL register pair
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);

    // we are taking HL register and incrementing by 1
    L_register_++;
    if(L_register_ == 0x00){
        H_register_++;
    }

    // Next we write that data into the address location of DE register pair
    memory_address_ = (static_cast<uint16_t>(D_register_) << 8) | E_register_;
    ram_write(memory_address_, data_8_);

    // we are taking DE register and incrementing by 1
    E_register_++;
    if(E_register_ == 0x00){
        D_register_++;
    }

    // The byte counter (BC register) is decremented
    C_register_--;
    if(C_register_ == 0xFF){
        B_register_--;
    }

    // H is reset.
    set_flag(HALF_CARRY_FLAG, false);
    // N is reset.
    set_flag(ADD_SUB_FLAG, false);
    // P/V is set if BC-1 != 0, else it is reset.
    memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;
    set_flag(PARITY_OVERFLOW_FLAG, memory_address_ != 0);

    // re-use data_8 as a temp
    data_8_ += accumulator_;
    set_flag(Y_FLAG, data_8_ & 0x02);
    set_flag(X_FLAG, data_8_ & 0x08);
}


void z80cpu::LDIR_register_indirect_register_indirect() {
    t_state_cycles_ = 16;

    // we are reading the data from address at HL register pair
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);
    L_register_++;
    if(L_register_ == 0x00){
        H_register_++;
    }

    // we are writing the data to address at DE register pair
    memory_address_ = (static_cast<uint16_t>(D_register_) << 8) | E_register_;
    ram_write(memory_address_, data_8_);
    E_register_++;
    if(E_register_ == 0x00){
        D_register_++;
    }

    // decrementing BC register pair
    C_register_--;
    if(C_register_ == 0xFF){
        B_register_--;
    }

    // checking if byte counter has reached 0 or not
    memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;

    // Checks if wz_register_flag is false
    if(!WZ_register_flag_){
        if((memory_address_ + 1) != 1){
            WZ_register_ = program_counter_ + 1;
        }
        WZ_register_flag_ = true;
    }

    set_flag(HALF_CARRY_FLAG, false);
    set_flag(ADD_SUB_FLAG, false);


    if(memory_address_ != 0) {
        // P/V us set uf BC - 1 != 0
        set_flag(PARITY_OVERFLOW_FLAG, true);

        // 5 extra clock cycles are added at the end when the program_counter decrements by 2
        t_state_cycles_ += 5;

        // we set the program_counter back 2 opcodes and start this instruction over again until byte_counter = 0
        program_counter_ -= 2;
        return;
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }

    // re-use data_8 as a temp
    data_8_ += accumulator_;
    set_flag(Y_FLAG, data_8_ & 0x02);
    set_flag(X_FLAG, data_8_ & 0x08);

    // reset WZ_register_flag
    WZ_register_flag_ = false;
}


void z80cpu::LDD_register_indirect_register_indirect() {
    t_state_cycles_ = 16;

    // we are reading the data from address at HL register pair
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);
    L_register_--;
    if(L_register_ == 0xFF){
        H_register_--;
    }

    // we are writing the data to address at DE register pair
    memory_address_ = (static_cast<uint16_t>(D_register_) << 8) | E_register_;
    ram_write(memory_address_, data_8_);
    E_register_--;
    if(E_register_ == 0xFF){
        D_register_--;
    }

    // decrementing BC register pair
    C_register_--;
    if(C_register_ == 0xFF){
        B_register_--;
    }

    // H is reset.
    set_flag(HALF_CARRY_FLAG, false);
    // N is reset.
    set_flag(ADD_SUB_FLAG, false);
    // P/V is set if BC != 0, else it is reset.
    memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;
    set_flag(PARITY_OVERFLOW_FLAG, memory_address_ != 0);

    // re-use data_8 as a temp
    data_8_ += accumulator_;
    set_flag(Y_FLAG, data_8_ & 0x02);
    set_flag(X_FLAG, data_8_ & 0x08);
}


void z80cpu::LDDR_register_indirect_register_indirect() {
    t_state_cycles_ = 16;

    // we are reading the data from address at HL register pair
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    data_8_ = ram_read(memory_address_);
    L_register_--;
    if(L_register_ == 0xFF){
        H_register_--;
    }

    // we are writing the data to address at DE register pair
    memory_address_ = (static_cast<uint16_t>(D_register_) << 8) | E_register_;
    ram_write(memory_address_, data_8_);
    E_register_--;
    if(E_register_ == 0xFF){
        D_register_--;
    }

    // decrementing BC register pair
    C_register_--;
    if(C_register_ == 0xFF){
        B_register_--;
    }

    // H, N is reset
    set_flag(HALF_CARRY_FLAG, false);
    set_flag(ADD_SUB_FLAG, false);


    // checking if byte counter has reached 0 or not
    memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;

    // Checks if wz_register_flag is false
    if(!WZ_register_flag_){
        if((memory_address_ + 1) != 1){
            WZ_register_ = program_counter_ + 1;
        }
        WZ_register_flag_ = true;
    }
    if(memory_address_ != 0) {
        set_flag(PARITY_OVERFLOW_FLAG, true);
        t_state_cycles_ += 5; // 5 extra clock cycles are added at the end when the program_counter decrements by 2

        // we set the program_counter back 2 opcodes and start this instruction over again until byte_counter = 0
        program_counter_ -= 2;
        return;
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }

    // re-use data_8 as a temp
    data_8_ += accumulator_;
    set_flag(Y_FLAG, data_8_ & 0x02);
    set_flag(X_FLAG, data_8_ & 0x08);

    // reset WZ_register_flag
    WZ_register_flag_ = false;
}