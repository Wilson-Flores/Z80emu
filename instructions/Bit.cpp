#include "../z80.hpp"


void z80cpu::BIT_implied() {
    t_state_cycles_ = 8;

    // register value = *register_table[opcode & BIT_MASK_2]
    // The bit place we want to check: (opcode & BIT_MASK_1) >> 3
    // Shift the data's bit over so the bit we want to look at is in the 0th bit place.
    // clear out the rest of the bits by doing & 0x01.

    // ex. Register B = 0x61
    // We want to look at BIT 4, B
    // 0110 0001 = 0x61
    // temp_data = (0x61 >> 4) = 0000 0110
    // temp_data = (0000 0110) & 0x01 = 0000 0000

    data_8_ = (opcode_ & BIT_MASK_1) >> 3;
    uint8_t register_value = *register_table_[opcode_ & BIT_MASK_2];
    result_8_ = (register_value >> data_8_) & BIT_MASK_5;


    // S is set if b = 7 and tested bit is set
    set_flag(SIGN_FLAG, ((data_8_ == 7) && result_8_ == 1));
    // Z is set if specified is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set identical to ZF.
    // Since tested bit can only have 2 possible values: [0,1] the result becomes identical to ZF.
    set_flag(PARITY_OVERFLOW_FLAG, result_8_ == 0);
    // N is always reset
    set_flag(ADD_SUB_FLAG, false);
    // C is not affected

    // XF is set if bit 3 of the register value is set
    set_flag(X_FLAG, register_value & X_FLAG_MASK);
    // YF is set if bit 5 of the register value is set
    set_flag(Y_FLAG, register_value & Y_FLAG_MASK);
}


void z80cpu::BIT_indirect() {
    t_state_cycles_ = 12;

    // data_8 will store which bit value we will be looking at
    data_8_ = opcode_ & BIT_MASK_1 >> 3;

    // result_8 will store the data at HL address
    memory_address_ = (static_cast<uint16_t>(H_register_) << 8) | L_register_;
    result_8_ = ram_read(memory_address_);

    // we will rewrite result_8 with whatever the bit value is at data_8
    result_8_ = (result_8_ >> data_8_) & BIT_MASK_5;


    // S is set if b = 7 and tested bit is set
    set_flag(SIGN_FLAG, ((data_8_ == 7) && result_8_ == 1));
    // Z is set if specified is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set identical to ZF.
    // Since tested bit can only have 2 possible values: [0,1] the result becomes identical to ZF.
    set_flag(PARITY_OVERFLOW_FLAG, result_8_ == 0);
    // N is always reset
    set_flag(ADD_SUB_FLAG, false);
    // C is not affected

    // X & Y Flags are copies bit 3 & 5 of the high byte of the temporary 16bit register (WZ register)
    set_flag(X_FLAG, WZ_register_ & X_FLAG_MASK_2);
    set_flag(Y_FLAG, WZ_register_ & Y_FLAG_MASK_2);
}


void z80cpu::BIT_indexed_ix() {
    t_state_cycles_ = 20;

    // data_8 will store which bit value we will be looking at
    data_8_ = opcode_ & BIT_MASK_1 >> 3;

    // copy the data from the memory address
    memory_address_ = index_register_x_ + static_cast<int16_t>(displacement_);
    result_8_ = ram_read(memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    // we will rewrite result_8 with whatever the bit value is at data_8
    result_8_ = (result_8_ >> data_8_) & BIT_MASK_5;


    // S is set if b = 7 and tested bit is set
    set_flag(SIGN_FLAG, ((data_8_ == 7) && result_8_ == 1));
    // Z is set if specified is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set identical to ZF.
    // Since tested bit can only have 2 possible values: [0,1] the result becomes identical to ZF.
    set_flag(PARITY_OVERFLOW_FLAG, result_8_ == 0);
    // N is always reset
    set_flag(ADD_SUB_FLAG, false);
    // C is not affected

    // X & Y Flags are copies bit 3 & 5 of the high byte of (IX+d)
    set_flag(X_FLAG, memory_address_ & X_FLAG_MASK_2);
    set_flag(Y_FLAG, memory_address_ & Y_FLAG_MASK_2);
}


void z80cpu::BIT_indexed_iy() {
    t_state_cycles_ = 20;

    // data_8 will store which bit value we will be looking at
    data_8_ = opcode_ & BIT_MASK_1 >> 3;

    // copy the data from the memory address
    memory_address_ = index_register_y_ + static_cast<int16_t>(displacement_);
    result_8_ = ram_read(memory_address_);

    // WZ register is updated using memory address
    WZ_register_ = memory_address_;

    // we will rewrite result_8 with whatever the bit value is at data_8
    result_8_ = (result_8_ >> data_8_) & BIT_MASK_5;


    // S is set if b = 7 and tested bit is set
    set_flag(SIGN_FLAG, ((data_8_ == 7) && result_8_ == 1));
    // Z is set if specified is 0, else reset
    set_flag(ZERO_FLAG, result_8_ == 0);
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is set identical to ZF.
    // Since tested bit can only have 2 possible values: [0,1] the result becomes identical to ZF.
    set_flag(PARITY_OVERFLOW_FLAG, result_8_ == 0);
    // N is always reset
    set_flag(ADD_SUB_FLAG, false);
    // C is not affected

    // X & Y Flags are copies bit 3 & 5 of the high byte of (IX+d)
    set_flag(X_FLAG, memory_address_ & X_FLAG_MASK_2);
    set_flag(Y_FLAG, memory_address_ & Y_FLAG_MASK_2);
}