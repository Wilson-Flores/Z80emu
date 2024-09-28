#include "test_main.hpp"

TEST_F(JumpTest, JP_immediate_test)
{
    const std::vector<uint8_t> expected_register_values = {0x00, 0xFF};

    const std::vector<uint8_t> memory = {0xC3, 0x05, 0x00, 0x3E, 0x28, 0x3E, 0xFF};

    TestRegister(memory, bus.cpu.accumulator, expected_register_values);
}