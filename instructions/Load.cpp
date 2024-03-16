#include "../z80.hpp"

// 8-bit LD Instructions
void z80cpu::LD_register_immediate() {
    t_state_cycles = 7;

    // bit mask the opcode to find the register value
    uint8_t destination_register_bit = (opcode & BIT_MASK_1) >> 3;

    *register_table[destination_register_bit] = rom_read(program_counter);

    // Increment program counter again to avoid instruction cycle from mistaking 'n' value for an opcode
    program_counter++;
}


void z80cpu::LD_register_register() {
    t_state_cycles = 4;

    // bit mask the opcode to find the register destination value and source register value
    uint8_t destination_register_bit = (opcode & BIT_MASK_1) >> 3;
    uint8_t source_register_bit = (opcode & BIT_MASK_2);

    *register_table[destination_register_bit] = *register_table[source_register_bit];
}


void z80cpu::LD_register_register_indirect() {
    t_state_cycles = 7;

    // LD r, (HL) opcode ends with 0b110, while LD A, (BC) and LD A, (DE) end with 0b010
    uint8_t opcode_bit = (opcode & BIT_MASK_2);
    uint8_t register_bit = (opcode & BIT_MASK_1) >> 3;

    if (opcode_bit == 0x02) {
        if (register_bit == 0x01) {
            // LD A, (BC)
            address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
            accumulator = ram_read(address_absolute);

        }
        else {
            // LD A, (DE)
            address_absolute = (static_cast<uint16_t>(D_register) << 8) | E_register;
            accumulator = ram_read(address_absolute);
        }
    }
    else {
        // LD r, (HL)
        address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
        *register_table[register_bit] = ram_read(address_absolute);
    }
}


void z80cpu::LD_register_implied() {
    t_state_cycles = 9;

    // Half Carry flag is reset.
    set_flag(HALF_CARRY_FLAG, false);
    // Add/Subtract flag is reset.
    set_flag(ADD_SUB_FLAG, false);
    // P/V contains contents of IFF2
    set_flag(PARITY_OVERFLOW_FLAG, interrupt_enable_flip_flop_2);


    if (opcode == 0x57) { // LD A, I

        // Sign Flag is set if I is negative, else it is reset.
        set_flag(SIGN_FLAG, (interrupt_vector_register >> 7) == 0x01);

        // Zero Flag is set if I equals 0, else it is reset.
        set_flag(ZERO_FLAG, interrupt_vector_register == 0x00);

        accumulator = interrupt_vector_register;
    }
    else { // LD A, R

        // Sign Flag is set if I is negative, else it is reset.
        set_flag(SIGN_FLAG, (memory_refresh_register >> 7) == 0x01);

        // Zero Flag is set if I equals 0, else it is reset.
        set_flag(SIGN_FLAG, memory_refresh_register == 0x00);

        accumulator = memory_refresh_register;
    }
}


void z80cpu::LD_register_indexed_ix() {
    t_state_cycles = 19;
    uint8_t register_bit = (opcode & BIT_MASK_1) >> 3;

    // one-byte signed integer (-128 to +127)
    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));

    // add the value in index register x with the twos-complement signed value
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    *register_table[register_bit] = ram_read(address_absolute);

    program_counter++;
}


void z80cpu::LD_register_indexed_iy() {
    t_state_cycles = 19;
    uint8_t register_bit = (opcode & BIT_MASK_1) >> 3;

    // one-byte signed integer (-128 to +127)
    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;

    // add the value in ind
    // ex register x with the twos-complement signed value
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    *register_table[register_bit] = ram_read(address_absolute);
}


void z80cpu::LD_register_extended() {
    t_state_cycles = 4;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;

    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    accumulator = ram_read(address_absolute);
}


void z80cpu::LD_register_indirect_immediate() {
    t_state_cycles = 3;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t value = rom_read(program_counter);
    program_counter++;

    ram_write(address_absolute, value);
}


void z80cpu::LD_register_indirect_register() {
    t_state_cycles = 7;

    // [LD (BC), A]
    if (opcode == 0x02){
        address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
        ram_write(address_absolute, accumulator);
    }
    // [LD (DE), A]
    else if(opcode == 0x12){
        address_absolute = (static_cast<uint16_t>(D_register) << 8) | E_register;
        ram_write(address_absolute, accumulator);
    }
    // [LD (HL), r]
    else{
        uint8_t register_bit = (opcode & BIT_MASK_2);

        address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;

        // the data from the register will be written to the address location
        ram_write(address_absolute, *register_table[register_bit]);
    }

}


void z80cpu::LD_indexed_ix_immediate(){
    t_state_cycles = 19;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;

    uint8_t value = rom_read(program_counter);
    program_counter++;

    address_absolute = index_register_x + static_cast<int16_t>(displacement);

    ram_write(address_absolute, value);
}


void z80cpu::LD_indexed_iy_immediate() {
    t_state_cycles = 19;

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;

    uint8_t value = rom_read(program_counter);
    program_counter++;

    address_absolute = index_register_y + static_cast<int16_t>(displacement);

    ram_write(address_absolute, value);
}


void z80cpu::LD_indexed_ix_register(){
    t_state_cycles = 19;

    uint8_t register_bit = (opcode & BIT_MASK_2);

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;

    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    ram_write(address_absolute, *register_table[register_bit]);
}


void z80cpu::LD_indexed_iy_register(){
    t_state_cycles = 19;

    uint8_t register_bit = (opcode & BIT_MASK_2);

    int8_t displacement = static_cast<int8_t>(rom_read(program_counter));
    program_counter++;

    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    ram_write(address_absolute, *register_table[register_bit]);
}


void z80cpu::LD_extended_register() {
    t_state_cycles = 13;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;

    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    ram_write(address_absolute, accumulator);
}


void z80cpu::LD_implied_register() {
    t_state_cycles = 9;

    if (opcode == 0x47) { // LD I, A
        interrupt_vector_register = accumulator;
    }
    else { // LD R, A
        memory_refresh_register = accumulator;
    }
}


// 16-bit LD Instructions
void z80cpu::LD_register_immediate_extended_16_bit() {
    t_state_cycles = 10;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;

    *register_pair_table_ss[register_pair_bit].high_byte_register = high_byte;
    *register_pair_table_ss[register_pair_bit].low_byte_register = low_byte;

}


void z80cpu::LD_register_immediate_extended_ix() {
    t_state_cycles = 14;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;

    uint16_t value = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    index_register_x = value;
}


void z80cpu::LD_register_immediate_extended_iy() {
    t_state_cycles = 14;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;

    uint16_t value = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    index_register_y = value;
}


void z80cpu::LD_register_extended_16_bit() {
    t_state_cycles = 20;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;
    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    *register_pair_table_ss[register_pair_bit].high_byte_register = ram_read(address_absolute + 1);
    *register_pair_table_ss[register_pair_bit].low_byte_register = ram_read(address_absolute);
}


void z80cpu::LD_register_extended_hl() {
    t_state_cycles = 16;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;
    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    H_register = ram_read(address_absolute + 1);
    L_register = ram_read(address_absolute);
}


void z80cpu::LD_register_extended_ix() {
    t_state_cycles = 20;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;
    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    index_register_x = (static_cast<uint16_t>(ram_read(address_absolute + 1))) << 8 | ram_read(address_absolute);
}


void z80cpu::LD_register_extended_iy() {
    t_state_cycles = 20;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;
    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    index_register_y = (static_cast<uint16_t>(ram_read(address_absolute + 1))) << 8 | ram_read(address_absolute);
}


void z80cpu::LD_register_register_hl() {
    t_state_cycles = 6;

    stack_pointer = (static_cast<uint16_t>(H_register)) << 8 | L_register;
}


void z80cpu::LD_register_register_ix() {
    t_state_cycles = 10;

    stack_pointer = index_register_x;
}


void z80cpu::LD_register_register_iy() {
    t_state_cycles = 10;

    stack_pointer = index_register_y;
}


void z80cpu::LD_extended_register_16_bit() {
    t_state_cycles = 20;

    uint8_t register_pair_bit = (opcode & BIT_MASK_3) >> 4;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;
    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    uint8_t register_high_byte = *register_pair_table_ss[register_pair_bit].high_byte_register;
    uint8_t register_low_byte = *register_pair_table_ss[register_pair_bit].low_byte_register;


    ram_write(address_absolute, register_low_byte);
    ram_write(address_absolute + 1, register_high_byte);
}


void z80cpu::LD_extended_register_hl() {
    t_state_cycles = 16;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;
    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    ram_write(address_absolute, L_register);
    ram_write(address_absolute + 1, H_register);
}


void z80cpu::LD_extended_register_ix() {
    t_state_cycles = 20;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;
    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    uint8_t ix_high_byte;
    ix_high_byte = static_cast<uint8_t>(index_register_x >> 8);
    uint8_t ix_low_byte;
    ix_low_byte = static_cast<uint8_t>(index_register_x & LOW_BYTE_MASK);


    ram_write(address_absolute, ix_low_byte);
    ram_write(address_absolute + 1, ix_high_byte);
}


void z80cpu::LD_extended_register_iy() {
    t_state_cycles = 20;

    uint8_t low_byte = rom_read(program_counter);
    program_counter++;
    uint8_t high_byte = rom_read(program_counter);
    program_counter++;
    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;

    uint8_t iy_high_byte;
    iy_high_byte = static_cast<uint8_t>(index_register_y >> 8);
    uint8_t iy_low_byte;
    iy_low_byte = static_cast<uint8_t>(index_register_y & LOW_BYTE_MASK);

    ram_write(address_absolute, iy_low_byte);
    ram_write(address_absolute + 1, iy_high_byte);
}


// Block Transfer Instructions - The concept is the same as an LD instruction.
void z80cpu::LDI_register_indirect_register_indirect() {
    t_state_cycles = 16;

    // We get the data from the address location of HL register pair
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);

    // we are taking HL register and incrementing by 1
    L_register++;
    if(L_register == 0x00){
        H_register++;
    }

    // Next we write that data into the address location of DE register pair
    address_absolute = (static_cast<uint16_t>(D_register) << 8) | E_register;
    ram_write(address_absolute, data);

    // we are taking DE register and incrementing by 1
    E_register++;
    if(E_register == 0x00){
        D_register++;
    }

    // The byte counter (BC register) is decremented
    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // H is reset.
    set_flag(HALF_CARRY_FLAG, false);
    // N is reset.
    set_flag(ADD_SUB_FLAG, false);
    // P/V is set if BC-1 != 0, else it is reset.
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
    set_flag(PARITY_OVERFLOW_FLAG,address_absolute != 0);
}


void z80cpu::LDIR_register_indirect_register_indirect() {
    t_state_cycles = 16;

    // we are reading the data from address at HL register pair
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);
    L_register++;
    if(L_register == 0x00){
        H_register++;
    }

    // we are writing the data to address at DE register pair
    address_absolute = (static_cast<uint16_t>(D_register) << 8) | E_register;
    ram_write(address_absolute, data);
    E_register++;
    if(E_register == 0x00){
        D_register++;
    }

    // decrementing BC register pair
    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // checking if byte counter has reached 0 or not
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;

    set_flag(HALF_CARRY_FLAG, false);
    set_flag(ADD_SUB_FLAG, false);

    if(address_absolute != 0) {
        // P/V us set uf BC - 1 != 0
        set_flag(PARITY_OVERFLOW_FLAG, true);

        // 5 extra clock cycles are added at the end when the program_counter decrements by 2
        t_state_cycles += 5;

        // we set the program_counter back 2 opcodes and start this instruction over again until byte_counter = 0
        program_counter -= 2;
        return;
    }

    set_flag(PARITY_OVERFLOW_FLAG, false);
}


void z80cpu::LDD_register_indirect_register_indirect() {
    t_state_cycles = 16;

    // we are reading the data from address at HL register pair
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);
    L_register--;
    if(L_register == 0xFF){
        H_register--;
    }

    // we are writing the data to address at DE register pair
    address_absolute = (static_cast<uint16_t>(D_register) << 8) | E_register;
    ram_write(address_absolute, data);
    E_register--;
    if(E_register == 0xFF){
        D_register--;
    }

    // decrementing BC register pair
    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // H is reset.
    set_flag(HALF_CARRY_FLAG, false);
    // N is reset.
    set_flag(ADD_SUB_FLAG, false);
    // P/V is set if BC != 0, else it is reset.
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
    set_flag(PARITY_OVERFLOW_FLAG, address_absolute != 0);
}


void z80cpu::LDDR_register_indirect_register_indirect() {
    t_state_cycles = 16;

    // we are reading the data from address at HL register pair
    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t data = ram_read(address_absolute);
    L_register--;
    if(L_register == 0xFF){
        H_register--;
    }

    // we are writing the data to address at DE register pair
    address_absolute = (static_cast<uint16_t>(D_register) << 8) | E_register;
    ram_write(address_absolute, data);
    E_register--;
    if(E_register == 0xFF){
        D_register--;
    }

    // decrementing BC register pair
    C_register--;
    if(C_register == 0xFF){
        B_register--;
    }

    // H, N is reset
    set_flag(HALF_CARRY_FLAG, false);
    set_flag(ADD_SUB_FLAG, false);


    // checking if byte counter has reached 0 or not
    address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;

    if(address_absolute != 0) {
        set_flag(PARITY_OVERFLOW_FLAG, true);
        t_state_cycles += 5; // 5 extra clock cycles are added at the end when the program_counter decrements by 2

        // we set the program_counter back 2 opcodes and start this instruction over again until byte_counter = 0
        program_counter -= 2;
        return;
    }

    set_flag(PARITY_OVERFLOW_FLAG, false);
}