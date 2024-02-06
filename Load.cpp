#include "z80.hpp"

constexpr uint8_t BIT_MASK_1 = 0x38; // 0011 1000 binary value
constexpr uint8_t BIT_MASK_2 = 0x07; // 0000 0111 binary value


void z80cpu::ix_instructions() {
    opcode = read(program_counter);
    memory_refresh_counter();
    program_counter++;

    std::cout << "OPCODE: " << this->ix_instruction_table[opcode].opcode << '\n';
    (this->*iy_instruction_table[opcode].instruction)();
}


void z80cpu::iy_instructions() {
    opcode = read(program_counter);
    memory_refresh_counter();
    program_counter++;

    std::cout << "OPCODE: " << this->iy_instruction_table[opcode].opcode << '\n';
    (this->*iy_instruction_table[opcode].instruction)();
}


// 8-bit LD Instructions
void z80cpu::LD_register_immediate() {
    t_state_cycles = 7;

    // bit mask the opcode to find the register value
    uint8_t destination_register_bit = (opcode & BIT_MASK_1) >> 3;

    *register_table[destination_register_bit] = read(program_counter);

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
            accumulator = read(address_absolute);

        }
        else {
            // LD A, (DE)
            address_absolute = (static_cast<uint16_t>(D_register) << 8) | E_register;
            accumulator = read(address_absolute);
        }
    }
    else {
        // LD r, (HL)
        address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
        *register_table[register_bit] = read(address_absolute);
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
        if ((interrupt_vector_register >> 7) == 0x01) {
            set_flag(SIGN_FLAG, true);
        }
        else {
            set_flag(SIGN_FLAG, false);
        }

        // Zero Flag is set if I equals 0, else it is reset.
        if (interrupt_vector_register == 0x00) {
            set_flag(ZERO_FLAG, true);
        }
        else {
            set_flag(ZERO_FLAG, false);
        }

        accumulator = interrupt_vector_register;
    }
    else { // LD A, R

        // Sign Flag is set if I is negative, else it is reset.
        if ((memory_refresh_register >> 7) == 0x01) {
            set_flag(SIGN_FLAG, true);
        }
        else {
            set_flag(SIGN_FLAG, false);
        }

        // Zero Flag is set if I equals 0, else it is reset.
        if (memory_refresh_register == 0x00) {
            set_flag(ZERO_FLAG, true);
        }
        else {
            set_flag(ZERO_FLAG, false);
        }

        accumulator = memory_refresh_register;
    }
}


void z80cpu::LD_register_indexed_ix() {
    t_state_cycles = 19;
    uint8_t register_bit = (opcode & BIT_MASK_1) >> 3;

    // one-byte signed integer (-128 to +127)
    int8_t displacement;
    displacement = static_cast<int8_t>(read(program_counter));

    // add the value in index register x with the twos-complement signed value
    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    *register_table[register_bit] = read(address_absolute);

    program_counter++;
}


void z80cpu::LD_register_indexed_iy() {
    t_state_cycles = 19;
    uint8_t register_bit = (opcode & BIT_MASK_1) >> 3;

    // one-byte signed integer (-128 to +127)
    int8_t displacement;
    displacement = static_cast<int8_t>(read(program_counter));
    program_counter++;

    // add the value in index register x with the twos-complement signed value
    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    *register_table[register_bit] = read(address_absolute);
}


void z80cpu::LD_register_extended() {
    t_state_cycles = 4;

    uint8_t high_byte = read(program_counter);
    program_counter++;
    uint8_t low_byte = read(program_counter);
    program_counter++;

    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    accumulator = read(address_absolute);
}


void z80cpu::LD_register_indirect_immediate() {
    t_state_cycles = 3;

    address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;
    uint8_t value = read(program_counter);
    program_counter++;

    write(address_absolute, value);
}


void z80cpu::LD_register_indirect_register() {
    t_state_cycles = 7;

    // [LD (BC), A]
    if (opcode == 0x02){
        address_absolute = (static_cast<uint16_t>(B_register) << 8) | C_register;
        write(address_absolute,accumulator);
    }
    // [LD (DE), A]
    else if(opcode == 0x12){
        address_absolute = (static_cast<uint16_t>(D_register) << 8) | E_register;
        write(address_absolute,accumulator);
    }
    // [LD (HL), r]
    else{
        uint8_t register_bit = (opcode & BIT_MASK_2);

        address_absolute = (static_cast<uint16_t>(H_register) << 8) | L_register;

        // the data from the register will be written to the address location
        write(address_absolute, *register_table[register_bit]);
    }

}


void z80cpu::LD_indexed_ix_immediate(){
    t_state_cycles = 19;

    int8_t displacement;
    displacement = static_cast<int8_t>(read(program_counter));
    program_counter++;

    uint8_t value = read(program_counter);
    program_counter++;

    address_absolute = index_register_x + static_cast<int16_t>(displacement);

    write(address_absolute, value);
}


void z80cpu::LD_indexed_iy_immediate() {
    t_state_cycles = 19;

    int8_t displacement;
    displacement = static_cast<int8_t>(read(program_counter));
    program_counter++;

    uint8_t value = read(program_counter);
    program_counter++;

    address_absolute = index_register_y + static_cast<int16_t>(displacement);

    write(address_absolute, value);
}


void z80cpu::LD_indexed_ix_register(){
    t_state_cycles = 19;

    uint8_t register_bit = (opcode & BIT_MASK_2);

    int8_t displacement;
    displacement = static_cast<int8_t>(read(program_counter));
    program_counter++;

    address_absolute = index_register_x + static_cast<int16_t>(displacement);
    write(address_absolute, *register_table[register_bit]);
}


void z80cpu::LD_indexed_iy_register(){
    t_state_cycles = 19;

    uint8_t register_bit = (opcode & BIT_MASK_2);

    int8_t displacement;
    displacement = static_cast<int8_t>(read(program_counter));
    program_counter++;

    address_absolute = index_register_y + static_cast<int16_t>(displacement);
    write(address_absolute, *register_table[register_bit]);
}


void z80cpu::LD_extended_register() {
    t_state_cycles = 13;

    uint8_t high_byte = read(program_counter);
    program_counter++;
    uint8_t low_byte = read(program_counter);
    program_counter++;

    address_absolute = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    write(address_absolute, accumulator);
}


// 16-bit LD Instructions
void z80cpu::LD_register_immediate_extended_ix() {
    t_state_cycles = 14;

    uint8_t high_byte = read(program_counter);
    program_counter++;
    uint8_t low_byte = read(program_counter);
    program_counter++;

    uint16_t value = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    index_register_x = value;
}


void z80cpu::LD_register_immediate_extended_iy() {
    t_state_cycles = 14;

    uint8_t high_byte = read(program_counter);
    program_counter++;
    uint8_t low_byte = read(program_counter);
    program_counter++;

    uint16_t value = (static_cast<uint16_t>(high_byte) << 8) | low_byte;
    index_register_y = value;
}



