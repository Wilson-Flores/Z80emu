#include "../z80.hpp"

void z80cpu::ADD_implied_register() {
    t_state_cycles = 4;

    uint8_t data = *register_table[opcode & BIT_MASK_2];
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADD_implied_register_indirect() {
    t_state_cycles = 7;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADD_implied_indexed_ix() {
    t_state_cycles = 19;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADD_implied_indexed_iy() {
    t_state_cycles = 19;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADD_implied_immediate() {
    t_state_cycles = 7;

    uint8_t data = rom_read(program_counter);
    program_counter++;
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data);

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F)
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) + (data & 0x0F) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ result) & ~(accumulator ^ data)) & 0x80);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADC_implied_register() {
    t_state_cycles = 4;

    uint8_t data = *register_table[opcode & BIT_MASK_2];
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data) +
            static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADC_implied_register_indirect() {
    t_state_cycles = 7;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data) +
            static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADC_implied_indexed_ix() {
    t_state_cycles = 19;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data) +
            static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADC_implied_indexed_iy() {
    t_state_cycles = 19;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data) +
                      static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADC_implied_immediate() {
    t_state_cycles = 7;

    uint8_t data = rom_read(program_counter);
    program_counter++;

    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(data) +
                      static_cast<uint16_t>(get_flag(CARRY_FLAG));

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x0080);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, (result & 0x00FF) == 0);
    // H is set if carry from bit 3, else reset
    // h_result = (accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)
    set_flag(HALF_CARRY_FLAG, ((accumulator & 0x0F) + (data & 0x0F) + get_flag(CARRY_FLAG)) > 0x0F);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG, ((static_cast<uint16_t>(accumulator) ^ result) &
    ~(static_cast<uint16_t>(accumulator) ^ static_cast<uint16_t>(data))) & 0x0080);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, result > 0x00FF);

    accumulator = result;
}


void z80cpu::ADD_implied_register_extended() {
    t_state_cycles = 11;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;
    uint16_t HL_data = (H_register << 8) + L_register;
    uint16_t result = HL_data + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = ((HL_data & 0x0FFF) + (register_pair_data & 0x0FFF));
    set_flag(HALF_CARRY_FLAG, ((HL_data & 0x0FFF) + (register_pair_data & 0x0FFF)) > 0x0FFF);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result < HL_data) || (result < register_pair_data));

    H_register = (result & 0xFF00) >> 8;
    L_register = result & 0x00FF;
}


void z80cpu::ADD_implied_register_extended_ix() {
    t_state_cycles = 15;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_pp[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_pp[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;
    uint16_t result = index_register_x + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = (index_register_x & 0x0FFF) + (register_pair_data & 0x0FFF)
    set_flag(HALF_CARRY_FLAG, ((index_register_x & 0x0FFF) + (register_pair_data & 0x0FFF)) > 0x0FFF);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result < index_register_x) || (result < register_pair_data));

    index_register_x = result;
}


void z80cpu::ADD_implied_register_extended_iy() {
    t_state_cycles = 15;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_rr[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_rr[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = ( high_byte << 8) + low_byte;
    uint16_t result = index_register_y + register_pair_data;

    // H is set if carry from bit 11; else reset
    // h_result = (index_register_y & 0x0FFF) + (register_pair_data & 0x0FFF)
    set_flag(HALF_CARRY_FLAG, ((index_register_y & 0x0FFF) + (register_pair_data & 0x0FFF)) > 0x0FFF);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result < index_register_y) || (result < register_pair_data));

    index_register_y = result;
}


void z80cpu::ADC_implied_register_extended() {
    t_state_cycles = 15;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;
    uint8_t high_byte = *register_pair_table_ss[register_pair_bit].high_byte_register;
    uint8_t low_byte = *register_pair_table_ss[register_pair_bit].low_byte_register;
    uint16_t register_pair_data = (high_byte << 8) + low_byte;
    uint16_t HL_data = (H_register << 8) + L_register;
    uint32_t result = static_cast<uint32_t>(HL_data) + static_cast<uint32_t>(register_pair_data)
                      + static_cast<uint32_t>(get_flag(CARRY_FLAG));


    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, static_cast<uint16_t>(result) & 0x8000);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, static_cast<uint16_t>(result) == 0x0000);
    // H is set if carry from bit 11, else reset
    // h_result = (HL_data & 0x0FFF) + (register_pair_data & 0x0FFF) + (static_cast<uint16_t>(get_flag(CARRY_FLAG)) & 0x0FFF)
    set_flag(HALF_CARRY_FLAG,((HL_data & 0x0FFF) + (register_pair_data & 0x0FFF) +
             (static_cast<uint16_t>(get_flag(CARRY_FLAG)) & 0x0FFF)) > 0x0FFF);
    // P/V is set if overflow, else reset
    set_flag(PARITY_OVERFLOW_FLAG,
             (~(static_cast<uint32_t>(HL_data) ^ static_cast<uint32_t>(register_pair_data))
                     & (static_cast<uint32_t>(HL_data) ^ result)) & 0x00008000);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 15, else reset
    set_flag(CARRY_FLAG, (result > 0xFFFF));

    H_register = (result & 0xFF00) >> 8;
    L_register = result & 0x00FF;
}