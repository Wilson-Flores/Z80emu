#include "../Bus.hpp"
#include "gtest/gtest.h"


// Define a test fixture class
class LoadTest : public ::testing::Test {
protected:
    Bus bus;
};

TEST_F(LoadTest, LD_register_immediate_test){
    std::vector<std::pair<uint8_t, uint8_t>> registers =
            {{0x3E, 0xFF}, // A
             {0x06, 0xFF}, // B
             {0x0E, 0xFF}, // C
             {0x16, 0xFF}, // D
             {0x1E, 0xFF}, // E
             {0x26, 0xFF}, // H
             {0x2E, 0xFF}  // L
            };


    bool compare_flag_values = false;

    for (const std::pair<const uint8_t, uint8_t>& pair : registers) {
        std::vector<uint8_t> memory = {pair.first, pair.second};

        uint8_t flag_value = 0x00;

        bus.rom_reset();

        for (int i = 0; i < memory.size(); i++) {
            bus.rom_write(i,memory[i]);
        }

        bus.cpu.instruction_cycle();

        if(bus.cpu.flag_register != flag_value){
            compare_flag_values = true;
        }
        ASSERT_EQ(compare_flag_values, false);
    }
}