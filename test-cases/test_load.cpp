#include "../Bus.hpp"
#include "gtest/gtest.h"

//TODO: implement loop instructions first,
// then come back so we can loop through 0x00-0xFF and load them to registers.


// Define a test fixture class
class LoadTest : public ::testing::Test {
protected:
    Bus bus;
};

TEST_F(LoadTest, LD_register_immediate_test){
    std::vector<uint8_t> registers =
            {0x3E,  // A
             0x06,  // B
             0x0E,  // C
             0x16,  // D
             0x1E,  // E
             0x26,  // H
             0x2E,  // L
            };

    uint8_t flag_value = 0x00;
    bool compare_flag_values = false;


    for (const uint8_t& reg : registers) {
        std::vector<uint8_t> memory = {reg, 0xFF};

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
