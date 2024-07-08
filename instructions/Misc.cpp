#include "../z80.hpp"

void z80cpu::CCF_implied(){
    // Complement carry flag
    t_state_cycles = 4;

    // H, previous carry is copied
    set_flag(HALF_CARRY_FLAG, get_flag(CARRY_FLAG));
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if CY was 0 before operation; otherwise, it is reset
    set_flag(CARRY_FLAG, (get_flag(CARRY_FLAG) == 0) ? 1 : 0);
}


void z80cpu::NEG_implied() {
    // Negate accumulator
    // contents of the accumulator are subtracted from zero ( two's complement) and stored back into the accumulator.
    // A = 0 - A
    t_state_cycles = 8;

    result = ~accumulator + 1;

    // S is set if result is negative; otherwise it is reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else it is reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if borrow from bit 4, else it is reset
    // 0 - (anything != 0) will always need to borrow, we can use > 0 as well.
    set_flag(HALF_CARRY_FLAG, (accumulator & 0x0F) > 0);
    // P/V is set if Accumulator was 80h before operation, else it is reset
    set_flag(PARITY_OVERFLOW_FLAG, accumulator == 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is set if Accumulator was not 00h before operation, else it is reset
    set_flag(CARRY_FLAG, accumulator != 0);

    accumulator = result;
}


void z80cpu::CPL_implied() {
    // Complement accumulator
    // the contents of the accumulator are inverted (one's complement).
    // A = ~A
    t_state_cycles = 4;

    // S is not affected
    // Z is not affected
    // H is set
    set_flag(HALF_CARRY_FLAG, true);
    // P/V is not affected
    // N is set
    set_flag(ADD_SUB_FLAG, true);
    // C is not affected

    accumulator = ~accumulator;
}


void z80cpu::SCF_implied() {
    // The Carry flag is set
    t_state_cycles = 4;

    // S is not affected
    // Z is not affected
    // H is reset
    set_flag(HALF_CARRY_FLAG, false);
    // P/V is not affected
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set
    set_flag(CARRY_FLAG, true);
}


void z80cpu::DAA_implied() {
    // Adjusts the Accumulator for BCD addition/subtraction operations
    // For Addition: (ADD, ADC, INC); for Subtraction: (SUB, SBC, DEC, NEG)

    t_state_cycles = 4;
    temp_data = accumulator;

    // We check the status of the Add/Sub Flag, Carry Flag, and Half-Carry Flag.
    // operation will vary on the 3 flag combination
    // --------------------------------------------
    // N = 0, C = 0, H = 0
    // high nibble 0-9, low nibble 0-9
    // nothing changes

    // high nibble 0-8, low nibble A-F
    // add 0x06 to the accumulator.
    // half flag is set to true.

    // high nibble A-F, low nibble 0-9
    // add 0x60 to the accumulator,
    // carry flag is set to true.

    // high nibble 9-F, low nibble A-F
    // add 0x66 to the accumulator.
    // carry flag and half flag is set to true.
    // --------------------------------------------
    // N = 0, C = 0, H = 1
    // update: when lower nibble is A-F, half carry is set to true
    // when lower nibble 0-9, half carry is set to false
    // update: every value from (0x00-0x99) get +0x06 added
    // update: every value from (0x9A-0xFF) gets +0x66 added, carry flag is set to true
    // --------------------------------------------
    // N = 0, C = 1, H = 0
    // update: if lower nibble is 0-9, add +0x60
    // update: if lower nibble is A-F, add +0x66, half carry flag is set to true
    // --------------------------------------------
    // N = 0, C = 1, H = 1
    // update: when lower nibble is A-F, half carry is set to true
    // when lower nibble 0-9, half carry is set to false
    // update: every value gets add 0x66
    // --------------------------------------------
    // N = 1, C = 0, H = 0
    // high nibble 0-9, low nibble 0-9
    // nothing changes

    // high nibble 0-8, low nibble A-F, add 0xFA to the accumulator.

    // high nibble A-F, low nibble 0-9
    // add 0xA0 to the accumulator,
    // carry flag is set to true.

    // high nibble 9-F, low nibble A-F
    // add 0x9A to the accumulator.
    // carry flag is set to true.
    // --------------------------------------------
    // N = 1, C = 0, H = 1
    // update: values with lower nibble (0-5), half carry flag is set to true
    // update: every value from (0x00-0x99) get +0xFA added
    // update: every value from (0x9A-0xFF) get +0x9A added, carry flag is set to true
    // --------------------------------------------
    // N = 1, C = 1, H = 0
    // if lower nibble is 0-9, add 0xA0
    // if lower nibble is A-F, add 0x9A
    // --------------------------------------------
    // N = 1, C = 1, H = 1
    // update: all values get +0x9A added
    // update: half carry is set when lower nibble is less than 6.


    if(get_flag(ADD_SUB_FLAG) == 0){
        if(get_flag(CARRY_FLAG) == 0){
            if(get_flag(HALF_CARRY_FLAG) == 0){
                if(((temp_data & 0xF0) < 0x90) && ((temp_data & 0x0F) > 0x09)){
                    temp_data += 0x06;
                    set_flag(HALF_CARRY_FLAG, true);
                }
                else if(((temp_data & 0xF0) > 0x90) && ((temp_data & 0x0F) < 0x0A)){
                    temp_data += 0x60;
                    set_flag(CARRY_FLAG, true);
                }
                else if(((temp_data & 0xF0) > 0x80) && ((temp_data & 0x0F) > 0x09)){
                    temp_data += 0x66;
                    set_flag(CARRY_FLAG, true);
                    set_flag(HALF_CARRY_FLAG, true);
                }
            }
            else{
                set_flag(HALF_CARRY_FLAG, (temp_data & 0x0F) > 0x09);
                if(temp_data < 0x9A){
                    temp_data += 0x06;
                }
                else{
                    temp_data += 0x66;
                    set_flag(CARRY_FLAG, true);
                }
            }
        }
        else{
            if(get_flag(HALF_CARRY_FLAG) == 0){
                if((temp_data & 0x0F) < 0x0A){
                    temp_data += 0x60;
                }
                else{
                    temp_data += 0x66;
                    set_flag(HALF_CARRY_FLAG, true);
                }
            }
            else{
                set_flag(HALF_CARRY_FLAG, (temp_data & 0x0F) > 0x09);
                temp_data += 0x66;
            }
        }
    }
    else {
        if(get_flag(CARRY_FLAG) == 0){
            if(get_flag(HALF_CARRY_FLAG) == 0){
                if(((temp_data & 0xF0) < 0x90) && ((temp_data & 0x0F) > 0x09)){
                    temp_data += 0xFA;
                }
                else if(((temp_data & 0xF0) > 0x90) && ((temp_data & 0x0F) < 0x0A)){
                    temp_data += 0xA0;
                    set_flag(CARRY_FLAG, true);
                }
                else if(((temp_data & 0xF0) > 0x80) && ((temp_data & 0x0F) > 0x09)) {
                    temp_data += 0x9A;
                    set_flag(CARRY_FLAG, true);
                }
            }
            else{
                set_flag(HALF_CARRY_FLAG, (temp_data & 0x0F) < 0x06);
                if(temp_data < 0x9A){
                    temp_data += 0xFA;
                }
                else{
                    temp_data += 0x9A;
                    set_flag(CARRY_FLAG, true);
                }
            }
        }
        else{
            if(get_flag(HALF_CARRY_FLAG) == 0){
                if((temp_data & 0x0F) < 0x0A){
                    temp_data += 0xA0;
                }
                else{
                    temp_data += 0x9A;
                }
            }
            else{
                set_flag(HALF_CARRY_FLAG, (temp_data & 0x0F) < 0x06);
                temp_data += 0x9A;
            }
        }
    }

    // S is set if most significant bit of the accumulator is 1 after an operation, else reset
    set_flag(SIGN_FLAG, temp_data & 0x80);
    // Z is set if the accumulator is 0 after an operation, else reset
    set_flag(ZERO_FLAG, temp_data == 0);
    // P/V is set if the accumulator is an even parity after an operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[temp_data]);
    // N is not affected

    accumulator = temp_data;
}


void z80cpu::NOP_implied() {
    t_state_cycles = 4;

    // do nothing
}