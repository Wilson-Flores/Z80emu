#include "../z80.hpp"


void z80cpu::DEC_implied_register() {
    t_state_cycles = 4;

    // Decrement value in register
    uint8_t register_bit = (opcode & BIT_MASK_4) >> 3;
    uint8_t data = *register_table[register_bit];
    uint8_t result = data - 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if carry from bit 3;
    // only time half carry occurs: (0b0000 - 0b0001)
    set_flag(HALF_CARRY_FLAG, ((data & 0x0F) == 0));
    // P/V is set if r was 80h before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, data == 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    *register_table[register_bit] = result;
}


void z80cpu::DEC_implied_register_indirect() {
    t_state_cycles = 11;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);
    uint8_t result = data - 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if carry from bit 3;
    // only time half carry occurs: (0b0000 - 0b0001)
    set_flag(HALF_CARRY_FLAG, ((data & 0x0F) == 0));
    // P/V is set if r was 80h before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, data == 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    ram_write(address_absolute, result);
}


void z80cpu::DEC_implied_indexed_ix() {
    t_state_cycles = 23;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint8_t result = data - 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if carry from bit 3;
    // only time half carry occurs: (0b0000 - 0b0001)
    set_flag(HALF_CARRY_FLAG, ((data & 0x0F) == 0));
    // P/V is set if r was 80h before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, data == 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    ram_write(address_absolute, result);
}


void z80cpu::DEC_implied_indexed_iy() {
    t_state_cycles = 23;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    uint8_t data = ram_read(address_absolute);
    uint8_t result = data - 1;

    // S is set if result is negative, else reset
    set_flag(SIGN_FLAG, result & 0x80);
    // Z is set if result is 0, else reset
    set_flag(ZERO_FLAG, result == 0);
    // H is set if carry from bit 3;
    // only time half carry occurs: (0b0000 - 0b0001)
    set_flag(HALF_CARRY_FLAG, ((data & 0x0F) == 0));
    // P/V is set if r was 80h before operation, else reset
    set_flag(PARITY_OVERFLOW_FLAG, data == 0x80);
    // N is set
    set_flag(ADD_SUB_FLAG, true);

    ram_write(address_absolute, result);
}