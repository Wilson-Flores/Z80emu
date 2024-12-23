#include "test_main.hpp"

TEST_F(AddTest,ADD_implied_register_test){
    constexpr std::array<uint8_t, 14> expected_flag_values = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
            0xA8, 0x51, 0x28, 0xA8, 0x51, 0x00
    };

    constexpr std::array<uint8_t, 14> expected_reg_values = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0x00, 0x28, 0xA8, 0x00, 0x01
    };

    constexpr std::array<uint8_t, 21> memory = {
            0x3E, 0x00, 0x06, 0xFF, 0x0E, 0x01, 0x16, 0x28,
            0x1E, 0x80, 0x26, 0x58, 0x2E, 0x01, 0x87, 0x80,
            0x81, 0x82, 0x83, 0x84, 0x85
    };

    TestRegister(memory, bus.cpu_.get_accumulator_address(), expected_reg_values);
    TestFlag(memory,bus.cpu_.get_flag_register_address(), expected_flag_values);
}