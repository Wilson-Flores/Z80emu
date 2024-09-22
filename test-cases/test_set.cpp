#include "test_main.hpp"


TEST_F(SetTest, SET_implied_test)
{
    std::vector<uint8_t> expected_register_values = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

    const std::vector<uint8_t> memory_A = {0x3E, 0x00, 0xCB, 0xC7, 0xCB, 0xCF, 0xCB, 0xD7, 0xCB, 0xDF,
                                            0xCB, 0xE7, 0xCB, 0xEF, 0xCB, 0xF7, 0xCB, 0xFF}; // A

    const std::vector<uint8_t> memory_B = {0x06, 0x00, 0xCB, 0xC0, 0xCB, 0xC8, 0xCB, 0xD0, 0xCB, 0xD8,
                                            0xCB, 0xE0, 0xCB, 0xE8, 0xCB, 0xF0, 0xCB, 0xF8}; // B

    const std::vector<uint8_t> memory_C = {0x0E, 0x00, 0xCB, 0xC1, 0xCB, 0xC9, 0xCB, 0xD1, 0xCB, 0xD9,
                                            0xCB, 0xE1, 0xCB, 0xE9, 0xCB, 0xF1, 0xCB, 0xF9}; // C

    const std::vector<uint8_t> memory_D = {0x16, 0x00, 0xCB, 0xC2, 0xCB, 0xCA, 0xCB, 0xD2, 0xCB, 0xDA,
                                            0xCB, 0xE2, 0xCB, 0xEA, 0xCB, 0xF2, 0xCB, 0xFA}; // D

    const std::vector<uint8_t> memory_E = {0x1E, 0x00, 0xCB, 0xC3, 0xCB, 0xCB, 0xCB, 0xD3, 0xCB, 0xDB,
                                            0xCB, 0xE3, 0xCB, 0xEB, 0xCB, 0xF3, 0xCB, 0xFB}; // E

    const std::vector<uint8_t> memory_H = {0x26, 0x00, 0xCB, 0xC4, 0xCB, 0xCC, 0xCB, 0xD4, 0xCB, 0xDC,
                                            0xCB, 0xE4, 0xCB, 0xEC, 0xCB, 0xF4, 0xCB, 0xFC}; // H

    const std::vector<uint8_t> memory_L = {0x2E, 0x00, 0xCB, 0xC5, 0xCB, 0xCD, 0xCB, 0xD5, 0xCB, 0xDD,
                                            0xCB, 0xE5, 0xCB, 0xED, 0xCB, 0xF5, 0xCB, 0xFD}; // L


    // Run tests for each register
    TestRegister(memory_A, bus.cpu.accumulator, expected_register_values);
    TestRegister(memory_B, bus.cpu.B_register, expected_register_values);
    TestRegister(memory_C, bus.cpu.C_register, expected_register_values);
    TestRegister(memory_D, bus.cpu.D_register, expected_register_values);
    TestRegister(memory_E, bus.cpu.E_register, expected_register_values);
    TestRegister(memory_H, bus.cpu.H_register, expected_register_values);
    TestRegister(memory_L, bus.cpu.L_register, expected_register_values);
}


TEST_F(SetTest, SET_indirect_test)
{
    // Set doesnt affect any flags
    std::vector<uint8_t> expected_flag_values(9,0);
    std::vector<uint8_t> expected_register_values = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

    bool compare_flag_values = false;

    std::vector<uint8_t> memory = {
        0x21, 0x50, 0x00, 0x36, 0x00, 0xCB, 0xC6, 0xCB,
        0xCE, 0xCB, 0xD6, 0xCB, 0xDE, 0xCB, 0xE6, 0xCB,
        0xEE, 0xCB, 0xF6, 0xCB, 0xFE
    };

    for (int j = 0; j < memory.size(); j++) {
        bus.rom_write(j,memory[j]);
    }

    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
        bus.cpu.instruction_cycle();

        if(bus.cpu.flag_register != expected_flag_values[byte_counter]){
            compare_flag_values = true;
            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                      << static_cast<int>(bus.cpu.opcode) << '\t';

            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                      << static_cast<int>(bus.cpu.flag_register) << '\n';
        }
        ASSERT_EQ(compare_flag_values, false);
    }
}


TEST_F(SetTest, SET_indexed_ix_test)
{
    // Set doesnt affect any flags
    std::vector<uint8_t> expected_flag_values(9,0);
    std::vector<uint8_t> expected_register_values = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

    bool compare_flag_values = false;

    std::vector<uint8_t> memory = {
        0x21, 0x50, 0x00, 0x36, 0x00, 0xDD, 0x21, 0x50, 0x00, 0xDD,
        0xCB, 0x00, 0xC6, 0xDD, 0xCB, 0x00, 0xCE, 0xDD, 0xCB, 0x00,
        0xD6, 0xDD, 0xCB, 0x00, 0xDE, 0xDD, 0xCB, 0x00, 0xE6, 0xDD,
        0xCB, 0x00, 0xEE, 0xDD, 0xCB, 0x00, 0xF6, 0xDD, 0xCB, 0x00,
        0xFE
    };

    for (int j = 0; j < memory.size(); j++) {
        bus.rom_write(j,memory[j]);
    }

    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
        bus.cpu.instruction_cycle();

        if(bus.cpu.flag_register != expected_flag_values[byte_counter]){
            compare_flag_values = true;
            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                      << static_cast<int>(bus.cpu.opcode) << '\t';

            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                      << static_cast<int>(bus.cpu.flag_register) << '\n';
        }
        ASSERT_EQ(compare_flag_values, false);
    }
}


TEST_F(SetTest, SET_indexed_iy_test)
{
    // Set doesnt affect any flags
    std::vector<uint8_t> expected_flag_values(9,0);
    std::vector<uint8_t> expected_register_values = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

    bool compare_flag_values = false;

    std::vector<uint8_t> memory = {
        0x21, 0x50, 0x00, 0x36, 0x00, 0xFD, 0x21, 0x50, 0x00, 0xFD,
        0xCB, 0x00, 0xC6, 0xFD, 0xCB, 0x00, 0xCE, 0xFD, 0xCB, 0x00,
        0xD6, 0xFD, 0xCB, 0x00, 0xDE, 0xFD, 0xCB, 0x00, 0xE6, 0xFD,
        0xCB, 0x00, 0xEE, 0xFD, 0xCB, 0x00, 0xF6, 0xFD, 0xCB, 0x00,
        0xFE
    };

    for (int j = 0; j < memory.size(); j++) {
        bus.rom_write(j,memory[j]);
    }

    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
        bus.cpu.instruction_cycle();

        if(bus.cpu.flag_register != expected_flag_values[byte_counter]){
            compare_flag_values = true;
            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                      << static_cast<int>(bus.cpu.opcode) << '\t';

            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                      << static_cast<int>(bus.cpu.flag_register) << '\n';
        }
        ASSERT_EQ(compare_flag_values, false);
    }
}