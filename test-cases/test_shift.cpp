#include "test_main.hpp"


TEST_F(ShiftTest, SLA_implied_test)
{
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x21, 0x80};

    // Memory sets for each register
    constexpr std::array<uint8_t, 6> memoryA = {0x3E, 0xB1, 0xCB, 0x27, 0xCB, 0x27};
    constexpr std::array<uint8_t, 6> memoryB = {0x06, 0xB1, 0xCB, 0x20, 0xCB, 0x20};
    constexpr std::array<uint8_t, 6> memoryC = {0x0E, 0xB1, 0xCB, 0x21, 0xCB, 0x21};
    constexpr std::array<uint8_t, 6> memoryD = {0x16, 0xB1, 0xCB, 0x22, 0xCB, 0x22};
    constexpr std::array<uint8_t, 6> memoryE = {0x1E, 0xB1, 0xCB, 0x23, 0xCB, 0x23};
    constexpr std::array<uint8_t, 6> memoryH = {0x26, 0xB1, 0xCB, 0x24, 0xCB, 0x24};
    constexpr std::array<uint8_t, 6> memoryL = {0x2E, 0xB1, 0xCB, 0x25, 0xCB, 0x25};

    // Run tests for each register
    TestFlag(memoryA, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryB, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryC, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryD, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryE, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryH, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryL, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SLA_indirect_test)
{
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x00, 0x21, 0x80};

    constexpr std::array<uint8_t, 9> memory = {0x01, 0x0F, 0x00, 0x36, 0xB1, 0xCB, 0x26, 0xCB, 0x26};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SLA_indexed_ix_test)
{
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x00, 0x21, 0x80};

    constexpr std::array<uint8_t, 16> memory = {
            0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0xB1,
            0xDD, 0xCB, 0xFF, 0x26, 0xDD, 0xCB, 0xFF, 0x26
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SLA_indexed_iy_test)
{
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x00, 0x21, 0x80};

    constexpr std::array<uint8_t, 16> memory = {
            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0xB1,
            0xFD, 0xCB, 0xFF, 0x26, 0xFD, 0xCB, 0xFF, 0x26
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRA_implied_test)
{
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x85, 0xA0};

    // Memory sets for each register
    constexpr std::array<uint8_t, 6> memoryA = {0x3E, 0x81, 0xCB, 0x2F, 0xCB, 0x2F};
    constexpr std::array<uint8_t, 6> memoryB = {0x06, 0x81, 0xCB, 0x28, 0xCB, 0x28};
    constexpr std::array<uint8_t, 6> memoryC = {0x0E, 0x81, 0xCB, 0x29, 0xCB, 0x29};
    constexpr std::array<uint8_t, 6> memoryD = {0x16, 0x81, 0xCB, 0x2A, 0xCB, 0x2A};
    constexpr std::array<uint8_t, 6> memoryE = {0x1E, 0x81, 0xCB, 0x2B, 0xCB, 0x2B};
    constexpr std::array<uint8_t, 6> memoryH = {0x26, 0x81, 0xCB, 0x2C, 0xCB, 0x2C};
    constexpr std::array<uint8_t, 6> memoryL = {0x2E, 0x81, 0xCB, 0x2D, 0xCB, 0x2D};

    // Run tests for each register
    TestFlag(memoryA, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryB, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryC, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryD, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryE, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryH, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryL, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRA_indirect_test)
{
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x00, 0x85, 0xA0};

    constexpr std::array<uint8_t, 9> memory = {0x01, 0x0F, 0x00, 0x36, 0x81, 0xCB, 0x2E, 0xCB, 0x2E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRA_indexed_ix_test)
{
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x00, 0x85, 0xA0};

    constexpr std::array<uint8_t, 16> memory = {
            0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x81,
            0xDD, 0xCB, 0xFF, 0x2E, 0xDD, 0xCB, 0xFF, 0x2E
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRA_indexed_iy_test)
{
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x00, 0x85, 0xA0};

    constexpr std::array<uint8_t, 16> memory = {
            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x81,
            0xFD, 0xCB, 0xFF, 0x2E, 0xFD, 0xCB, 0xFF, 0x2E
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRL_implied_test)
{
    constexpr std::array<uint8_t, 2> expected_flag_values = {0x00, 0x05};

    // Memory sets for each register
    constexpr std::array<uint8_t, 6> memoryA = {0x3E, 0x8F, 0xCB, 0x3F};
    constexpr std::array<uint8_t, 6> memoryB = {0x06, 0x8F, 0xCB, 0x38};
    constexpr std::array<uint8_t, 6> memoryC = {0x0E, 0x8F, 0xCB, 0x39};
    constexpr std::array<uint8_t, 6> memoryD = {0x16, 0x8F, 0xCB, 0x3A};
    constexpr std::array<uint8_t, 6> memoryE = {0x1E, 0x8F, 0xCB, 0x3B};
    constexpr std::array<uint8_t, 6> memoryH = {0x26, 0x8F, 0xCB, 0x3C};
    constexpr std::array<uint8_t, 6> memoryL = {0x2E, 0x8F, 0xCB, 0x3D};

    // Run tests for each register
    TestFlag(memoryA, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryB, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryC, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryD, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryE, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryH, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryL, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRL_indirect_test)
{
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x05};

    constexpr std::array<uint8_t, 7> memory = {0x01, 0x0F, 0x00, 0x36, 0x8F, 0xCB, 0x3E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRL_indexed_ix_test)
{
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x05};

    constexpr std::array<uint8_t, 12> memory = {0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x8F, 0xDD, 0xCB, 0xFF, 0x3E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRL_indexed_iy_test)
{
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x05};

    constexpr std::array<uint8_t, 12> memory = {0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x8F, 0xFD, 0xCB, 0xFF, 0x3E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}