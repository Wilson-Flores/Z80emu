#include "../z80.hpp"

void z80cpu::CPI_register_indirect() {
    t_state_cycles = 16;

    // Read data at HL address, then decrement HL
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data = ram_read(address_absolute);
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
    if(accumulator < data){
        set_flag(SIGN_FLAG, true);
    }
    else{
        set_flag(SIGN_FLAG, false);
    }
    // Z is set if A == (HL), else reset
    if(accumulator == data){
        set_flag(ZERO_FLAG, true);
    }
    else{
        set_flag(ZERO_FLAG, false);
    }
    // H is set if borrow in lower nibble, else reset
    if(((accumulator & 0x0F) - (data & 0x0F)) < (data & 0x0F) ){
        set_flag(HALF_CARRY_FLAG, true);
    }
    else{
        set_flag(HALF_CARRY_FLAG, false);
    }
    // P/V is set if BC-1 != 0, else reset
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
    if(address_absolute != 0){
        set_flag(PARITY_OVERFLOW_FLAG, true);
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }
    // N is set
    set_flag(ADD_SUB_FLAG, true);
}


void z80cpu::CPIR_register_indirect() {
    t_state_cycles = 16;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data = ram_read(address_absolute);
    L_register++;
    if(L_register == 0x00){
        H_register++;
    }

    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // S is set if result is negative else reset
    if(accumulator < data){
        set_flag(SIGN_FLAG, true);
    }
    else{
        set_flag(SIGN_FLAG, false);
    }
    // Z is set if A == (HL), else reset
    if(accumulator == data){
        set_flag(ZERO_FLAG, true);
    }
    else{
        set_flag(ZERO_FLAG, false);
    }
    // H is set if borrow in lower nibble, else reset
    if(((accumulator & 0x0F) - (data & 0x0F)) < (data & 0x0F) ){
        set_flag(HALF_CARRY_FLAG, true);
    }
    else{
        set_flag(HALF_CARRY_FLAG, false);
    }
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    // P/V is set if BC-1 != 0, else reset
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;

    if((address_absolute != 0) && (accumulator != data)){
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
    data = ram_read(address_absolute);
    L_register--;
    if(L_register == 0xFF){
        H_register--;
    }

    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // S is set if result is negative else reset
    if(accumulator < data){
        set_flag(SIGN_FLAG, true);
    }
    else{
        set_flag(SIGN_FLAG, false);
    }
    // Z is set if A == (HL), else reset
    if(accumulator == data){
        set_flag(ZERO_FLAG, true);
    }
    else{
        set_flag(ZERO_FLAG, false);
    }
    // H is set if borrow in lower nibble, else reset
    if(((accumulator & 0x0F) - (data & 0x0F)) < (data & 0x0F) ){
        set_flag(HALF_CARRY_FLAG, true);
    }
    else{
        set_flag(HALF_CARRY_FLAG, false);
    }
    // P/V is set if BC-1 != 0, else reset
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
    if(address_absolute != 0){
        set_flag(PARITY_OVERFLOW_FLAG, true);
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }
    // N is set
    set_flag(ADD_SUB_FLAG, true);
}


void z80cpu::CPDR_register_indirect() {
    t_state_cycles = 16;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    data = ram_read(address_absolute);
    L_register--;
    if(L_register == 0xFF){
        H_register--;
    }

    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // S is set if result is negative else reset
    if(accumulator < data){
        set_flag(SIGN_FLAG, true);
    }
    else{
        set_flag(SIGN_FLAG, false);
    }
    // Z is set if A == (HL), else reset
    if(accumulator == data){
        set_flag(ZERO_FLAG, true);
    }
    else{
        set_flag(ZERO_FLAG, false);
    }
    // H is set if borrow in lower nibble, else reset
    if(((accumulator & 0x0F) - (data & 0x0F)) < (data & 0x0F) ){
        set_flag(HALF_CARRY_FLAG, true);
    }
    else{
        set_flag(HALF_CARRY_FLAG, false);
    }
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    // P/V is set if BC-1 != 0, else reset
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;

    if((address_absolute != 0) && (accumulator != data)){
        set_flag(PARITY_OVERFLOW_FLAG, true);
        t_state_cycles += 5;
        program_counter -= 2;
        return;
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }
}