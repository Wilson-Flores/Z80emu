#include "../z80.hpp"

void z80cpu::CPI_register_indirect() {
    t_state_cycles_ = 16;

    // Read data at HL address, then decrement HL
    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);
    L_register_++;
    if(L_register_ == MIN_BYTE){
        H_register_++;
    }

    // WZ_register increments after HL increments
    WZ_register_++;

    // decrementing BC register pair
    C_register_--;
    if(C_register_ == MAX_BYTE){
        B_register_--;
    }

    // A - (HL)
    // S is set if result is negative else reset
    temp_result_8_ = accumulator_ - temp_data_8_;
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if A == (HL), else reset
    set_flag(ZERO_FLAG, accumulator_ == temp_data_8_);
    // H is set if borrow in lower nibble, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // P/V is set if BC-1 != 0, else reset
    temp_memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;
    set_flag(PARITY_OVERFLOW_FLAG, temp_memory_address_ != 0);
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    temp_result_8_ -= get_flag(HALF_CARRY_FLAG);
    set_flag(X_FLAG, temp_data_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_data_8_ & Y_FLAG_MASK_2);
}


void z80cpu::CPIR_register_indirect() {
    t_state_cycles_ = 16;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);
    L_register_++;
    if(L_register_ == MIN_BYTE){
        H_register_++;
    }

    // WZ_register increments after HL increments
    WZ_register_++;

    C_register_--;
    if(C_register_ == MAX_BYTE){
        B_register_--;
    }

    // S is set if result is negative else reset
    temp_result_8_ = accumulator_ - temp_data_8_;
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if A == (HL), else reset
    set_flag(ZERO_FLAG, accumulator_ == temp_data_8_);
    // H is set if borrow in lower nibble, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    // P/V is set if BC-1 != 0, else reset
    temp_memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;

    if((temp_memory_address_ != 0) && (accumulator_ != temp_data_8_)){
        set_flag(PARITY_OVERFLOW_FLAG, true);
        t_state_cycles_ += 5;
        program_counter_ -= 2;
        return;
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }

    temp_result_8_ -= get_flag(HALF_CARRY_FLAG);
    set_flag(X_FLAG, temp_data_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_data_8_ & Y_FLAG_MASK);
}


void z80cpu::CPD_register_indirect() {
    t_state_cycles_ = 16;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);
    L_register_--;
    if(L_register_ == MAX_BYTE){
        H_register_--;
    }

    // WZ_register decrements after HL decrements
    WZ_register_--;

    C_register_--;
    if(C_register_ == MAX_BYTE){
        B_register_--;
    }

    // S is set if result is negative else reset
    temp_result_8_ = accumulator_ - temp_data_8_;
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if A == (HL), else reset
    set_flag(ZERO_FLAG, accumulator_ == temp_data_8_);
    // H is set if borrow in lower nibble, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // P/V is set if BC-1 != 0, else reset
    temp_memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;
    set_flag(PARITY_OVERFLOW_FLAG, temp_memory_address_ != 0);
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    temp_result_8_ -= get_flag(HALF_CARRY_FLAG);
    set_flag(X_FLAG, temp_data_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_data_8_ & Y_FLAG_MASK);
}


void z80cpu::CPDR_register_indirect() {
    t_state_cycles_ = 16;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);
    L_register_--;
    if(L_register_ == MAX_BYTE){
        H_register_--;
    }

    // WZ_register decrements after HL decrements
    WZ_register_--;

    C_register_--;
    if(C_register_ == MAX_BYTE){
        B_register_--;
    }

    // S is set if result is negative else reset
    temp_result_8_ = accumulator_ - temp_data_8_;
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if A == (HL), else reset
    set_flag(ZERO_FLAG, accumulator_ == temp_data_8_);
    // H is set if borrow in lower nibble, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    // P/V is set if BC-1 != 0, else reset
    temp_memory_address_ = (static_cast<uint16_t>(B_register_) << 8) | C_register_;

    if((temp_memory_address_ != 0) && (accumulator_ != temp_data_8_)){
        set_flag(PARITY_OVERFLOW_FLAG, true);
        t_state_cycles_ += 5;
        program_counter_ -= 2;
        return;
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }

    temp_result_8_ -= get_flag(HALF_CARRY_FLAG);
    set_flag(X_FLAG, temp_data_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_data_8_ & Y_FLAG_MASK);
}


void z80cpu::CP_implied_register() {
    t_state_cycles_ = 4;

    temp_data_8_ = *register_table_[opcode_ & BIT_MASK_2];
    temp_result_8_ = accumulator_ - temp_data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator_ + (~temp_data_8_ + 1);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator_ ^ overflow_result) & ~(accumulator_ ^ (~temp_data_8_ + 1))) & BIT_MASK_9);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < temp_data_8_);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::CP_implied_register_indirect() {
    t_state_cycles_ = 7;

    temp_memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    temp_data_8_ = ram_read(temp_memory_address_);
    temp_result_8_ = accumulator_ - temp_data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator_ + (~temp_data_8_ + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator_ ^ overflow_result) & ~(accumulator_ ^ (~temp_data_8_ + 1))) & BIT_MASK_9);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < temp_data_8_);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::CP_implied_indexed_ix() {
    t_state_cycles_ = 19;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_x_ + static_cast<int16_t>(temp_displacement_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    temp_data_8_ = ram_read(temp_memory_address_);
    temp_result_8_ = accumulator_ - temp_data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator_ + (~temp_data_8_ + 1);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator_ ^ overflow_result) & ~(accumulator_ ^ (~temp_data_8_ + 1))) & BIT_MASK_9);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < temp_data_8_);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::CP_implied_indexed_iy() {
    t_state_cycles_ = 19;

    temp_displacement_ = static_cast<int8_t>(rom_read(program_counter_));
    program_counter_++;
    temp_memory_address_ = index_register_y_ + static_cast<int16_t>(temp_displacement_);

    // WZ register is updated using memory address
    WZ_register_ = temp_memory_address_;

    temp_data_8_ = ram_read(temp_memory_address_);
    temp_result_8_ = accumulator_ - temp_data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator_ + (~temp_data_8_ + 1);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator_ ^ overflow_result) & ~(accumulator_ ^ (~temp_data_8_ + 1))) & BIT_MASK_9);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < temp_data_8_);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}


void z80cpu::CP_implied_immediate() {
    t_state_cycles_ = 7;

    temp_data_8_ = rom_read(program_counter_);
    program_counter_++;
    temp_result_8_ = accumulator_ - temp_data_8_;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, temp_result_8_ & BIT_MASK_9);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, temp_result_8_ == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator_ & BIT_MASK_8) < (temp_data_8_ & BIT_MASK_8));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator_ + (~temp_data_8_ + 1);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator_ ^ overflow_result) & ~(accumulator_ ^ (~temp_data_8_ + 1))) & BIT_MASK_9);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator_ < temp_data_8_);

    //X & Y Flags are copies bit 3 & 5 of the register
    set_flag(X_FLAG, temp_result_8_ & X_FLAG_MASK);
    set_flag(Y_FLAG, temp_result_8_ & Y_FLAG_MASK);
}