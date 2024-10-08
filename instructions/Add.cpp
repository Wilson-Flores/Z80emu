#include "../z80.hpp"

void z80cpu::ADD_implied_register() {
    t_state_cycles = 4;

    data_8 = *register_table[opcode & BIT_MASK_2];
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data_8 & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result_16) & ~(accumulator ^ data_8)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADD_implied_register_indirect() {
    t_state_cycles = 7;

    memory_address = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data_8 = ram_read(memory_address);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data_8 & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result_16) & ~(accumulator ^ data_8)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADD_implied_indexed_ix() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    memory_address = index_register_x + static_cast<int16_t>(displacement);
    data_8 = ram_read(memory_address);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data_8 & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result_16) & ~(accumulator ^ data_8)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    // WZ register is updated using memory address
    WZ_register = memory_address;

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADD_implied_indexed_iy() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    memory_address = index_register_y + static_cast<int16_t>(displacement);
    data_8 = ram_read(memory_address);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data_8 & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result_16) & ~(accumulator ^ data_8)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    // WZ register is updated using memory address
    WZ_register = memory_address;

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADD_implied_immediate() {
    t_state_cycles = 7;

    data_8 = rom_read(program_counter);
    program_counter++;
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data_8 & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result_16) & ~(accumulator ^ data_8)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADC_implied_register() {
    t_state_cycles = 4;

    data_8 = *register_table[opcode & BIT_MASK_2];
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8) +
                static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data_8 & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data_8))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADC_implied_register_indirect() {
    t_state_cycles = 7;

    memory_address = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data_8 = ram_read(memory_address);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8) +
                static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data_8 & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data_8))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADC_implied_indexed_ix() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    memory_address = index_register_x + static_cast<int16_t>(displacement);
    data_8 = ram_read(memory_address);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8) +
                static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data_8 & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data_8))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    // WZ register is updated using memory address
    WZ_register = memory_address;

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADC_implied_indexed_iy() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    memory_address = index_register_y + static_cast<int16_t>(displacement);
    data_8 = ram_read(memory_address);
    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8) +
                static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data_8 & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data_8))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    // WZ register is updated using memory address
    WZ_register = memory_address;

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADC_implied_immediate() {
    t_state_cycles = 7;

    data_8 = rom_read(program_counter);
    program_counter++;

    result_16 = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data_8) +
                static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result_16 & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result_16 & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data_8 & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result_16) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data_8))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result_16 > 0x00FF);

    accumulator = result_16;

    //X & Y Flags are copies bit 3 & 5 of the accumulator
    set_flag(X_FLAG, accumulator & 0x08);
    set_flag(Y_FLAG, accumulator & 0x20);
}


void z80cpu::ADD_implied_register_extended() {
    t_state_cycles = 11;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;
    data_16 = (H_register << 8) + L_register;

    // WZ register stores the data from HL pair + 1
    WZ_register = data_16 + 1;

    result_16 = data_16 + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = ((HL_data & 0x0FFF) + (register_pair_data & 0x0FFF));
    set_flag(HALF_CARRY_FLAG, ((data_16 & 0x0FFF) + (register_pair_data & 0x0FFF)) > 0x0FFF);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result_16 < data_16) || (result_16 < register_pair_data));

    H_register = (result_16 & 0xFF00) >> 8;
    L_register = result_16 & 0x00FF;

    //X & Y Flags are copies bit 3 & 5 of the high byte (H register)
    set_flag(X_FLAG, H_register & 0x08);
    set_flag(Y_FLAG, H_register & 0x20);
}


void z80cpu::ADD_implied_register_extended_ix() {
    t_state_cycles = 15;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_pp[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_pp[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;

    // WZ register stores the data from IX pair + 1
    WZ_register =  index_register_x + 1;

    result_16 = index_register_x + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = (index_register_x & 0x0FFF) + (register_pair_data & 0x0FFF)
    set_flag(HALF_CARRY_FLAG, ((index_register_x & 0x0FFF) + (register_pair_data & 0x0FFF)) > 0x0FFF);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result_16 < index_register_x) || (result_16 < register_pair_data));

    index_register_x = result_16;

    //X & Y Flags are copies bit 3 & 5 of the high byte of register x
    set_flag(X_FLAG, index_register_x & 0x0800);
    set_flag(Y_FLAG, index_register_x & 0x2000);
}


void z80cpu::ADD_implied_register_extended_iy() {
    t_state_cycles = 15;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_rr[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_rr[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;

    // WZ register stores the data from IY pair + 1
    WZ_register =  index_register_y + 1;

    result_16 = index_register_y + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = (index_register_y & 0x0FFF) + (register_pair_data & 0x0FFF)
    set_flag(HALF_CARRY_FLAG, ((index_register_y & 0x0FFF) + (register_pair_data & 0x0FFF)) > 0x0FFF);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result_16 < index_register_y) || (result_16 < register_pair_data));

    index_register_y = result_16;

    //X & Y Flags are copies bit 3 & 5 of the high byte of register y
    set_flag(X_FLAG, index_register_y & 0x0800);
    set_flag(Y_FLAG, index_register_y & 0x2000);
}


void z80cpu::ADC_implied_register_extended() {
    t_state_cycles = 15;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = (high_byte << 8) + low_byte;
    data_16 = (H_register << 8) + L_register;

    // WZ register stores the data from HL pair + 1
    WZ_register =  data_16 + 1;

    uint32_t result_32 = static_cast<uint32_t>(data_16) + static_cast<uint32_t>(register_pair_data)
                         + static_cast<uint32_t>(get_flag(CARRY_FLAG));


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, static_cast<uint16_t>(result_32) & 0x8000);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, static_cast<uint16_t>(result_32) == 0x0000);
    // H is set if carry from bit 11, else reset
    // h_result = (HL_data & 0x0FFF) + (register_pair_data & 0x0FFF) + (static_cast<uint16_t>(get_flag(CARRY_FLAG)) & 0x0FFF)
    set_flag(HALF_CARRY_FLAG,((data_16 & 0x0FFF) + (register_pair_data & 0x0FFF) +
                              (static_cast<uint16_t>(get_flag(CARRY_FLAG)) & 0x0FFF)) > 0x0FFF);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG,
             (~(static_cast<uint32_t>(data_16) ^ static_cast<uint32_t>(register_pair_data))
                     & (static_cast<uint32_t>(data_16) ^ result_32)) & 0x00008000);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result_32 > 0xFFFF));

    H_register = (static_cast<uint16_t>(result_32) & 0xFF00) >> 8;
    L_register = static_cast<uint16_t>(result_32) & 0x00FF;

    //X & Y Flags are copies bit 3 & 5 of the high byte (H register)
    set_flag(X_FLAG, H_register & 0x08);
    set_flag(Y_FLAG, H_register & 0x20);
}