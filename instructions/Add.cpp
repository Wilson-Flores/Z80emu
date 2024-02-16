#include "../z80.hpp"

void z80cpu::ADD_register_register() {
    t_state_cycles = 4;

    uint8_t source_register_bit = (opcode & BIT_MASK_2);

    // H is set if carry from bit 3 in lower nibble
    if((accumulator & 0x0F) + (*register_table[source_register_bit] & 0x0F) > 15) {
        set_flag(HALF_CARRY_FLAG, true);
    }
    else {
        set_flag(HALF_CARRY_FLAG, false);
    }

    int8_t value1;
    value1 = static_cast<int8_t>(accumulator);
    int8_t value2;
    value2 = static_cast<int8_t>(*register_table[source_register_bit]);

    // Overflow flag considers all values as signed.
    if((value1 > 0 && value2 > 0 && value1 > (127 - value2)) ||
    (value1 < 0 && value2 < 0 && value1 < (-128 - value2))) {
        set_flag(PARITY_OVERFLOW_FLAG, true);
    }
    else{
        set_flag(PARITY_OVERFLOW_FLAG, false);
    }

    // A = A + r
    accumulator += *register_table[source_register_bit];

    // S is set if result is negative, else its reset
    if(accumulator > 0x7F){
        set_flag(SIGN_FLAG, true);
    }
    else{
        set_flag(SIGN_FLAG, false);
    }

    // Z is set if result is 0, else its reset
    if(accumulator == 0){
        set_flag(ZERO_FLAG, true);
    }
    else{
        set_flag(ZERO_FLAG, false);
    }

    // N is reset
    set_flag(ADD_SUB_FLAG, false);

    // C is set if carry from bit 7, else reset
    if(accumulator < *register_table[source_register_bit]) {
        set_flag(CARRY_FLAG, true);
    }
    else{
        set_flag(CARRY_FLAG, false);
    }
}
