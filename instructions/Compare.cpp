#include "../z80.hpp"

void z80cpu::CPI_register_indirect() {
    t_state_cycles = 16;

    // Read data at HL address, then decrement HL
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    temp_data = ram_read(address_absolute);
    L_register++;
    if(L_register == 0x00){
        H_register++;
    }

    // decrementing BC register pair
    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // A - (HL)
    // S is set if result is negative else reset
    result = accumulator - temp_data;
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if A == (HL), else reset
    set_flag(ZERO_FLAG, accumulator == temp_data);
    // H is set if borrow in lower nibble, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // P/V is set if BC-1 != 0, else reset
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
    set_flag(PARITY_OVERFLOW_FLAG, address_absolute != 0);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
}


void z80cpu::CPIR_register_indirect() {
    t_state_cycles = 16;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    temp_data = ram_read(address_absolute);
    L_register++;
    if(L_register == 0x00){
        H_register++;
    }

    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // S is set if result is negative else reset
    result = accumulator - temp_data;
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if A == (HL), else reset
    set_flag(ZERO_FLAG, accumulator == temp_data);
    // H is set if borrow in lower nibble, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    // P/V is set if BC-1 != 0, else reset
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;

    if((address_absolute != 0) && (accumulator != temp_data)){
        set_flag(PARITY_OVERFLOW_FLAG, true);
        t_state_cycles += 5;
        program_counter -= 2;
        return;
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }
}


void z80cpu::CPD_register_indirect() {
    t_state_cycles = 16;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    temp_data = ram_read(address_absolute);
    L_register--;
    if(L_register == 0xFF){
        H_register--;
    }

    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // S is set if result is negative else reset
    result = accumulator - temp_data;
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if A == (HL), else reset
    set_flag(ZERO_FLAG, accumulator == temp_data);
    // H is set if borrow in lower nibble, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // P/V is set if BC-1 != 0, else reset
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
    set_flag(PARITY_OVERFLOW_FLAG, address_absolute != 0);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
}


void z80cpu::CPDR_register_indirect() {
    t_state_cycles = 16;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    temp_data = ram_read(address_absolute);
    L_register--;
    if(L_register == 0xFF){
        H_register--;
    }

    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // S is set if result is negative else reset
    result = accumulator - temp_data;
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if A == (HL), else reset
    set_flag(ZERO_FLAG, accumulator == temp_data);
    // H is set if borrow in lower nibble, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    // P/V is set if BC-1 != 0, else reset
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;

    if((address_absolute != 0) && (accumulator != temp_data)){
        set_flag(PARITY_OVERFLOW_FLAG, true);
        t_state_cycles += 5;
        program_counter -= 2;
        return;
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }
}


void z80cpu::CP_implied_register() {
    t_state_cycles = 4;

    temp_data = *register_table[opcode & BIT_MASK_2];
    result = accumulator - temp_data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~temp_data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~temp_data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < temp_data);
}


void z80cpu::CP_implied_register_indirect() {
    t_state_cycles = 7;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    temp_data = ram_read(address_absolute);
    result = accumulator - temp_data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~temp_data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~temp_data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < temp_data);
}


void z80cpu::CP_implied_indexed_ix() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    temp_data = ram_read(address_absolute);
    result = accumulator - temp_data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~temp_data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~temp_data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < temp_data);
}


void z80cpu::CP_implied_indexed_iy() {
    t_state_cycles = 19;

    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    temp_data = ram_read(address_absolute);
    result = accumulator - temp_data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~temp_data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~temp_data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < temp_data);
}


void z80cpu::CP_implied_immediate() {
    t_state_cycles = 7;

    temp_data = rom_read(program_counter);
    program_counter++;
    result = accumulator - temp_data;

    // S is set if result if negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else reset
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) < (temp_data & 0x0F));
    // P/V is set if overflow, else reset
    // perform 2s complement on data, reuse ADD's logic for overflow flag
    uint8_t overflow_result = accumulator + (~temp_data + 0x01);
    set_flag(PARITY_OVERFLOW_FLAG, ((accumulator ^ overflow_result) & ~(accumulator ^ (~temp_data + 0x01))) & 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if borrow to bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < temp_data);
}