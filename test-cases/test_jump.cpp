#include "test_main.hpp"

TEST_F(JumpTest, JP_immediate_test)
{
    const std::vector<uint8_t> expected_register_values = {0x00, 0xFF};

    const std::vector<uint8_t> memory = {0xC3, 0x05, 0x00, 0x3E, 0x28, 0x3E, 0xFF};

    TestRegister(memory, bus.cpu.accumulator, expected_register_values);
}


TEST_F(JumpTest, JP_cc_immediate_test)
{
    const std::vector<uint8_t> expected_register_values_A = {0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04};

    const std::vector<uint8_t> memory_A = {
        0xC2, 0x05, 0x00, 0x3E, 0x28, 0x3E, 0x01, 0xD2,
        0x0C, 0x00, 0x3E, 0x28, 0x3E, 0x02, 0xE2, 0x13,
        0x00, 0x3E, 0x28, 0x3E, 0x03, 0xF2, 0x1A, 0x00,
        0x3E, 0x28, 0x3E, 0x04
    };

    const std::vector<uint8_t> expected_register_values_B = { 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x04 };
    const std::vector<uint8_t> memory_B = {
        0x37, 0xDA, 0x06, 0x00, 0x3E, 0x28, 0x3E, 0x01,
        0x3E, 0x00, 0xB7, 0xCA, 0x10, 0x00, 0x3E, 0x28,
        0x3E, 0x02, 0xEA, 0x17, 0x00, 0x3E, 0x28, 0x3E,
        0x03, 0x3E, 0x00, 0xBF, 0xFA, 0x21, 0x00, 0x3E,
        0x28, 0x3E, 0x04
    };

    TestRegister(memory_A, bus.cpu.accumulator, expected_register_values_A);
    TestRegister(memory_B, bus.cpu.accumulator, expected_register_values_B);
}


TEST_F(JumpTest, JR_relative_test)
{
    const std::vector<uint8_t> expected_register_values = { 0x00, 0x00, 0x01 };
    const std::vector<uint8_t> memory = { 0x3E, 0x00, 0x18, 0x02, 0x3E, 0x28, 0x3E, 0x01 };

    TestRegister(memory, bus.cpu.accumulator, expected_register_values);
}


TEST_F(JumpTest, JR_cc_relative_test)
{
    const std::vector<uint8_t> expected_register_values_A = { 0x00, 0x00, 0x01, 0x01, 0x02 };
    const std::vector<uint8_t> memory_A = {
        0x3E, 0x00, 0x20, 0x02, 0x3E, 0x28, 0x3E, 0x01,
        0x30, 0x02, 0x3E, 0x28, 0x3E, 0x02
    };

    const std::vector<uint8_t> expected_register_values_B = { 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02 };
    const std::vector<uint8_t> memory_B = {
        0x37, 0x38, 0x02, 0x3E, 0x28, 0x3E, 0x01, 0x3E,
        0x00, 0xB7, 0x28, 0x02, 0x3E, 0x28, 0x3E, 0x02
    };

    TestRegister(memory_A, bus.cpu.accumulator, expected_register_values_A);
    TestRegister(memory_B, bus.cpu.accumulator, expected_register_values_B);
}



TEST_F(JumpTest, JP_implict_test)
{
    const std::vector<uint8_t> expected_register_values = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x01 };
    const std::vector<uint8_t> memory = { 0x3F, 0xED, 0x5F, 0x3E, 0x00, 0x21, 0x0B, 0x00, 0xE9, 0x3E, 0x28, 0x3E, 0x01 };

    TestRegister(memory, bus.cpu.accumulator, expected_register_values);
}


TEST_F(JumpTest, DJNZ_immediate_test)
{
    const std::vector<uint8_t> expected_register_values = { 0x00, 0x00, 0x01, 0x01, 0x02 };

    const std::vector<uint8_t> memory = { 0x06, 0x01, 0x10, 0x02, 0x3E, 0x01, 0x10, 0x02, 0x3E, 0x28, 0x3E, 0x02 };

    TestRegister(memory, bus.cpu.accumulator, expected_register_values);
}