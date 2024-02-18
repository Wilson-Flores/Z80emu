#include "../z80.hpp"

void z80cpu::ADD_register_register() {
    t_state_cycles = 4;

    uint8_t data = *register_table[opcode & BIT_MASK_2];

    // H is set if carry from bit 3 in lower nibble
    set_flag(HALF_CARRY_FLAG, ((accumulator + data) & 0x0F) < (data & 0x0F));
    // P/V flag considers all values as signed.
    set_flag(PARITY_OVERFLOW_FLAG, (accumulator ^ (accumulator + data)) & ~(accumulator ^ data));

    // A = A + r
    accumulator += data;

    // S is set if result is negative, else its reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else its reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);
}


void z80cpu::ADD_register_register_indirect() {
    t_state_cycles = 7;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);

    // H is set if carry from bit 3 in lower nibble
    set_flag(HALF_CARRY_FLAG, ((accumulator + data) & 0x0F) < (data & 0x0F));
    // Overflow flag considers all values as signed.
    set_flag(PARITY_OVERFLOW_FLAG, (accumulator ^ (accumulator + data)) & ~(accumulator ^ data));

    // A = A + (HL)
    accumulator += data;

    // S is set if result is negative, else its reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else its reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);
}


void z80cpu::ADD_register_indexed_ix() {
    t_state_cycles = 19;

    int8_t displacement;
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);

    // H is set if carry from bit 3 in lower nibble
    set_flag(HALF_CARRY_FLAG, ((accumulator + data) & 0x0F) < (data & 0x0F));
    // Overflow flag considers all values as signed.
    set_flag(PARITY_OVERFLOW_FLAG, (accumulator ^ (accumulator + data)) & ~(accumulator ^ data));

    // A = A + (HL)
    accumulator += data;

    // S is set if result is negative, else its reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else its reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);
}


void z80cpu::ADD_register_indexed_iy() {
    t_state_cycles = 19;

    int8_t displacement;
    displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);

    // H is set if carry from bit 3 in lower nibble
    set_flag(HALF_CARRY_FLAG, ((accumulator + data) & 0x0F) < (data & 0x0F));
    // Overflow flag considers all values as signed.
    set_flag(PARITY_OVERFLOW_FLAG, (accumulator ^ (accumulator + data)) & ~(accumulator ^ data));

    accumulator += data;

    // S is set if result is negative, else its reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else its reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);
}


void z80cpu::ADD_register_immediate() {
    t_state_cycles = 7;

    uint8_t data = rom_read(program_counter);
    program_counter++;

    // H is set if carry from bit 3 in lower nibble
    set_flag(HALF_CARRY_FLAG, ((accumulator + data) & 0x0F) < (data & 0x0F));
    // Overflow flag considers all values as signed.
    set_flag(PARITY_OVERFLOW_FLAG, (accumulator ^ (accumulator + data)) & ~(accumulator ^ data));

    accumulator += data;

    // S is set if result is negative, else its reset
    set_flag(SIGN_FLAG, accumulator & 0x80);
    // Z is set if result is 0, else its reset
    set_flag(ZERO_FLAG, accumulator == 0);
    // N is reset
    set_flag(ADD_SUB_FLAG, false);
    // C is set if carry from bit 7, else reset
    set_flag(CARRY_FLAG, accumulator < data);
}


void z80cpu::ADC_register_register() {
    t_state_cycles = 4;

    uint8_t source_register_bit = (opcode & BIT_MASK_2);


}