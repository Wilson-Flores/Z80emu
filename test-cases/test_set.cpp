#include "../Bus.hpp"
#include "gtest/gtest.h"


//Define a test fixture class
class SetTest : public ::testing::Test {
protected:
    Bus bus;
};


TEST_F(SetTest, SET_implied_test)
{
    // Set doesnt affect any flags
    std::vector<uint8_t> expected_flag_values(9,0);
    std::vector<uint8_t> expected_register_values = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

    bool compare_flag_values = false;

    std::vector<std::pair<uint8_t, std::vector<uint8_t>>> register_instructions = {
        { 0x3E, {0xC7, 0xCF, 0xD7, 0xDF, 0xE7, 0xEF, 0xF7, 0xFF} }, // A
        { 0x06, {0xC0, 0xC8, 0xD0, 0xD8, 0xE0, 0xE8, 0xF0, 0xF8} }, // B
        { 0x0E, {0xC1, 0xC9, 0xD1, 0xD9, 0xE1, 0xE9, 0xF1, 0xF9} }, // C
        { 0x16, {0xC2, 0xCA, 0xD2, 0xDA, 0xE2, 0xEA, 0xF2, 0xFA} }, // D
        { 0x1E, {0xC3, 0xCB, 0xD3, 0xDB, 0xE3, 0xEB, 0xF3, 0xFB} }, // E
        { 0x26, {0xC4, 0xCC, 0xD4, 0xDC, 0xE4, 0xEC, 0xF4, 0xFC} }, // H
        { 0x2E, {0xC5, 0xCD, 0xD5, 0xDD, 0xE5, 0xED, 0xF5, 0xFD} }  // L
    };

    for (const std::pair<uint8_t, std::vector<uint8_t>>& pair : register_instructions) {
        std::vector<uint8_t> memory = {pair.first, 0x00, 0xCB, pair.second[0], 0xCB, pair.second[1],
                                       0xCB, pair.second[2], 0xCB, pair.second[3], 0xCB, pair.second[4],
                                       0xCB, pair.second[5], 0xCB, pair.second[6], 0xCB, pair.second[7]};

        bus.rom_reset();

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