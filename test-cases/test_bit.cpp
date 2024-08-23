#include "../Bus.hpp"
#include "gtest/gtest.h"


//Define a test fixture class
class BitTest : public ::testing::Test {
protected:
    Bus bus;
};

TEST_F(BitTest, BIT_b_r_test){
    std::vector<uint8_t> expected_flag_values_00 = {0x00, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54};
    std::vector<uint8_t> expected_flag_values_FF = {0x00, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xB8};

    std::vector<uint8_t> load_value = {0x00, 0xFF};

    bool compare_flag_values = false;

    for (int i = 0; i < load_value.size(); i++){
        std::vector<uint8_t> memory_A = {
                0x3E, load_value[i], 0xCB, 0x47, 0xCB, 0x4F, 0xCB, 0x57,
                0xCB, 0x5F, 0xCB, 0x67, 0xCB, 0x6F, 0xCB, 0x77,
                0xCB, 0x7F
        };

        bus.rom_reset();

        for (int j = 0; j < memory_A.size(); j++) {
            bus.rom_write(j,memory_A[j]);
        }

        if(load_value[i] == 0x00){
            for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_00.size(); byte_counter++){
                bus.cpu.instruction_cycle();

                if(bus.cpu.flag_register != expected_flag_values_00[byte_counter]){
                    compare_flag_values = true;
                    std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                              << static_cast<int>(load_value[i]) << '\t';

                    std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                              << static_cast<int>(bus.cpu.opcode) << '\t';

                    std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                              << static_cast<int>(bus.cpu.flag_register) << '\n';
                }
                ASSERT_EQ(compare_flag_values, false);
            }
        }
        else if(load_value[i] == 0xFF){
            for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_FF.size(); byte_counter++){
                bus.cpu.instruction_cycle();

                if(bus.cpu.flag_register != expected_flag_values_FF[byte_counter]){
                    compare_flag_values = true;
                    std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                              << static_cast<int>(load_value[i]) << '\t';
                    std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                              << static_cast<int>(bus.cpu.opcode) << '\t';

                    std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                              << static_cast<int>(bus.cpu.flag_register) << '\n';
                }
                ASSERT_EQ(compare_flag_values, false);
            }
        }
    }
}