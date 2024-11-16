#include "test_main.hpp"


TEST_F(ShiftTest, SLA_implied_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x21, 0x80};

    // Memory sets for each register
    std::vector<uint8_t> memory_A = {0x3E, 0xB1, 0xCB, 0x27, 0xCB, 0x27};
    std::vector<uint8_t> memory_B = {0x06, 0xB1, 0xCB, 0x20, 0xCB, 0x20};
    std::vector<uint8_t> memory_C = {0x0E, 0xB1, 0xCB, 0x21, 0xCB, 0x21};
    std::vector<uint8_t> memory_D = {0x16, 0xB1, 0xCB, 0x22, 0xCB, 0x22};
    std::vector<uint8_t> memory_E = {0x1E, 0xB1, 0xCB, 0x23, 0xCB, 0x23};
    std::vector<uint8_t> memory_H = {0x26, 0xB1, 0xCB, 0x24, 0xCB, 0x24};
    std::vector<uint8_t> memory_L = {0x2E, 0xB1, 0xCB, 0x25, 0xCB, 0x25};

    // Run tests for each register
    TestFlag(memory_A, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_B, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_C, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_D, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_E, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_H, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_L, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SLA_indirect_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x21, 0x80};

    std::vector<uint8_t> memory = {0x01, 0x0F, 0x00, 0x36, 0xB1, 0xCB, 0x26, 0xCB, 0x26};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SLA_indexed_ix_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x21, 0x80};

    std::vector<uint8_t> memory = {
            0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0xB1,
            0xDD, 0xCB, 0xFF, 0x26, 0xDD, 0xCB, 0xFF, 0x26
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SLA_indexed_iy_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x21, 0x80};

    std::vector<uint8_t> memory = {
            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0xB1,
            0xFD, 0xCB, 0xFF, 0x26, 0xFD, 0xCB, 0xFF, 0x26
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRA_implied_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x85, 0xA0};

    // Memory sets for each register
    std::vector<uint8_t> memory_A = {0x3E, 0x81, 0xCB, 0x2F, 0xCB, 0x2F};
    std::vector<uint8_t> memory_B = {0x06, 0x81, 0xCB, 0x28, 0xCB, 0x28};
    std::vector<uint8_t> memory_C = {0x0E, 0x81, 0xCB, 0x29, 0xCB, 0x29};
    std::vector<uint8_t> memory_D = {0x16, 0x81, 0xCB, 0x2A, 0xCB, 0x2A};
    std::vector<uint8_t> memory_E = {0x1E, 0x81, 0xCB, 0x2B, 0xCB, 0x2B};
    std::vector<uint8_t> memory_H = {0x26, 0x81, 0xCB, 0x2C, 0xCB, 0x2C};
    std::vector<uint8_t> memory_L = {0x2E, 0x81, 0xCB, 0x2D, 0xCB, 0x2D};

    // Run tests for each register
    TestFlag(memory_A, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_B, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_C, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_D, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_E, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_H, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_L, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRA_indirect_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85, 0xA0};

    std::vector<uint8_t> memory = {0x01, 0x0F, 0x00, 0x36, 0x81, 0xCB, 0x2E, 0xCB, 0x2E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRA_indexed_ix_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85, 0xA0};

    std::vector<uint8_t> memory = {
            0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x81,
            0xDD, 0xCB, 0xFF, 0x2E, 0xDD, 0xCB, 0xFF, 0x2E
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRA_indexed_iy_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85, 0xA0};

    std::vector<uint8_t> memory = {
            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x81,
            0xFD, 0xCB, 0xFF, 0x2E, 0xFD, 0xCB, 0xFF, 0x2E
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRL_implied_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x05};

    // Memory sets for each register
    std::vector<uint8_t> memory_A = {0x3E, 0x8F, 0xCB, 0x3F};
    std::vector<uint8_t> memory_B = {0x06, 0x8F, 0xCB, 0x38};
    std::vector<uint8_t> memory_C = {0x0E, 0x8F, 0xCB, 0x39};
    std::vector<uint8_t> memory_D = {0x16, 0x8F, 0xCB, 0x3A};
    std::vector<uint8_t> memory_E = {0x1E, 0x8F, 0xCB, 0x3B};
    std::vector<uint8_t> memory_H = {0x26, 0x8F, 0xCB, 0x3C};
    std::vector<uint8_t> memory_L = {0x2E, 0x8F, 0xCB, 0x3D};

    // Run tests for each register
    TestFlag(memory_A, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_B, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_C, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_D, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_E, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_H, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memory_L, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRL_indirect_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x05};

    std::vector<uint8_t> memory = {0x01, 0x0F, 0x00, 0x36, 0x8F, 0xCB, 0x3E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRL_indexed_ix_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00,0x05};

    std::vector<uint8_t> memory = {0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x8F, 0xDD, 0xCB, 0xFF, 0x3E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(ShiftTest, SRL_indexed_iy_test)
{
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00,0x05};

    std::vector<uint8_t> memory = {0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x8F, 0xFD, 0xCB, 0xFF, 0x3E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}