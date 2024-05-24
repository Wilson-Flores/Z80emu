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

    uint8_t result = ~accumulator + 1;

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
    uint8_t data = accumulator;

    // Check if ADD_SUB_FLAG is 0(ADD) or 1(SUB)
    if(get_flag(ADD_SUB_FLAG) == 0){
        // Check Carry Flag
        if(get_flag(CARRY_FLAG) == 0){
            // Check Half Carry Flag
            if(get_flag(HALF_CARRY_FLAG) == 0){
                // high nibble 0-9, low nibble 0-9
                // changes nothing, adds 0 to accumulator.
                // Carry and Half flag set to false.
                if(((data & 0xF0) < 0xA0) && ((data & 0x0F) < 0x0A)){
                    data += 0x00;
                    set_flag(CARRY_FLAG, false);
                    set_flag(HALF_CARRY_FLAG, false);
                }

                // high nibble 0-8, low nibble A-F
                // add 0x06 to the accumulator.
                // half flag is set to true.
                else if(((data & 0xF0) < 0x90) && ((data & 0x0F) > 0x09)){
                    data += 0x06;
                    set_flag(CARRY_FLAG, false);
                    set_flag(HALF_CARRY_FLAG, true);
                }

                // high nibble A-F, low nibble 0-9
                // add 0x60 to the accumulator,
                // carry flag is set to true.
                // half flag is set to false.
                else if(((data & 0xF0) > 0x90) && ((data & 0x0F) < 0x0A)){
                    data += 0x60;
                    set_flag(CARRY_FLAG, true);
                    set_flag(HALF_CARRY_FLAG, false);
                }

                // high nibble 9-F, low nibble A-F
                // add 0x66 to the accumulator.
                // carry flag and half flag is set to true.
                else if(((data & 0xF0) > 0x80) && ((data & 0x0F) > 0x09)){
                    data += 0x66;
                    set_flag(CARRY_FLAG, true);
                    set_flag(HALF_CARRY_FLAG, true);
                }
            }
            else{
                // high nibble 0-9, low nibble 0-3
                // add 0x06 to accumulator.
                // carry and half flag are set to false.
                if(((data & 0xF0) < 0xA0) && ((data & 0x0F) < 0x04)){
                    data += 0x06;
                    set_flag(CARRY_FLAG, false);
                    set_flag(HALF_CARRY_FLAG, false);
                }

                // high nibble A-F, low nibble 0-3
                // add 0x66 to accumulator.
                // carry flag is set to true.
                // half flag is set to false.
                else if(((data & 0xF0) > 0x90) && ((data & 0x0F) < 0x04)){
                    data += 0x66;
                    set_flag(CARRY_FLAG, true);
                    set_flag(HALF_CARRY_FLAG, false);
                }
            }
        }
        else{
            if(get_flag(HALF_CARRY_FLAG) == 0){
                // high nibble 0-2, low nibble 0-9
                // add 0x60 to accumulator
                // carry flag is set to true.
                // half flag is set to false.
                if(((data & 0xF0) < 0x30) && ((data & 0x0F) < 0x0A)){
                    data += 0x60;
                    set_flag(CARRY_FLAG, true);
                    set_flag(HALF_CARRY_FLAG, false);
                }

                // high nibble 0-2, low nibble A-F
                // add 0x66 to accumulator
                // carry flag is set to true.
                // half flag is set to true.
                else if(((data & 0xF0) < 0x30) && ((data & 0x0F) > 0x09)){
                    data += 0x66;
                    set_flag(CARRY_FLAG, true);
                    set_flag(HALF_CARRY_FLAG, true);
                }
            }
            else{
                // high nibble 0-3, low nibble 0-3
                // add 0x66 to accumulator.
                // carry flag is set to true.
                // half flag is set to false.
                if(((data & 0xF0) < 0x40) && ((data & 0x0F) < 0x04)){
                    data += 0x66;
                    set_flag(CARRY_FLAG, true);
                    set_flag(HALF_CARRY_FLAG, false);
                }
            }
        }
    }
    else {
        // Check Carry Flag
        if(get_flag(CARRY_FLAG) == 0){
            // Check Half Carry Flag
            if(get_flag(HALF_CARRY_FLAG) == 0){
                // high nibble 0-9, low nibble 0-9
                // changes nothing, adds 0 to accumulator.
                // Carry and Half flag set to false.
                if(((data & 0xF0) < 0xA0) && ((data & 0x0F) < 0x0A)){
                    data += 0x00;
                    set_flag(CARRY_FLAG, false);
                    set_flag(HALF_CARRY_FLAG, false);
                }
            }
            else{
                // high nibble 0-8, low nibble 6-F
                // add 0xFA to accumulator.
                // carry and half flag are set to false.
                if(((data & 0xF0) < 0x90) && ((data & 0x0F) > 0x05)){
                    data += 0xFA;
                    set_flag(CARRY_FLAG, false);
                    set_flag(HALF_CARRY_FLAG, false);
                }
            }
        }
        else{
            if(get_flag(HALF_CARRY_FLAG) == 0){
                // high nibble 7-F, low nibble 0-9
                // add 0xA0 to accumulator.
                // carry flag is set to true.
                // half flag is set to false.
                data += 0xA0;
                set_flag(CARRY_FLAG, true);
                set_flag(HALF_CARRY_FLAG, false);
            }
            else{
                // high nibble 6-F, low nibble 6-F
                // add 0x9A to accumulator
                // carry flag is set to true
                // half flag is set to false
                data += 0x9A;
                set_flag(CARRY_FLAG, true);
                set_flag(HALF_CARRY_FLAG, false);

            }
        }
    }

    // S is set if most significant bit of the accumulator is 1 after an operation, else reset
    set_flag(SIGN_FLAG, data & 0x80);
    // Z is set if the accumulator is 0 after an operation, else reset
    set_flag(ZERO_FLAG, data == 0);
    // P/V is set if the accumulator is an even parity after an operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, PARITY_TABLE[data]);
    // N is not affected


    accumulator = data;
}
