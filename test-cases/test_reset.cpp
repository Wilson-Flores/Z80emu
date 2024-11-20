#include "test_main.hpp"


TEST_F(ResetTest, RES_implied_test)
{
    constexpr std::array<uint8_t, 9> expected_register_values = {0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00};

    // Memory sets for each register
    constexpr std::array<uint8_t, 18> memoryA = {0x3E, 0xFF, 0xCB, 0x87, 0xCB, 0x8F, 0xCB, 0x97, 0xCB, 0x9F,
                                           0xCB, 0xA7, 0xCB, 0xAF, 0xCB, 0xB7, 0xCB, 0xBF};

    constexpr std::array<uint8_t, 18> memoryB = {0x06, 0xFF, 0xCB, 0x80, 0xCB, 0x88, 0xCB, 0x90, 0xCB, 0x98,
                                           0xCB, 0xA0, 0xCB, 0xA8, 0xCB, 0xB0, 0xCB, 0xB8};

    constexpr std::array<uint8_t, 18> memoryC = {0x0E, 0xFF, 0xCB, 0x81, 0xCB, 0x89, 0xCB, 0x91, 0xCB, 0x99,
                                           0xCB, 0xA1, 0xCB, 0xA9, 0xCB, 0xB1, 0xCB, 0xB9};

    constexpr std::array<uint8_t, 18> memoryD = {0x16, 0xFF, 0xCB, 0x82, 0xCB, 0x8A, 0xCB, 0x92, 0xCB, 0x9A,
                                           0xCB, 0xA2, 0xCB, 0xAA, 0xCB, 0xB2, 0xCB, 0xBA};

    constexpr std::array<uint8_t, 18> memoryE = {0x1E, 0xFF, 0xCB, 0x83, 0xCB, 0x8B, 0xCB, 0x93, 0xCB, 0x9B,
                                           0xCB, 0xA3, 0xCB, 0xAB, 0xCB, 0xB3, 0xCB, 0xBB};

    constexpr std::array<uint8_t, 18> memoryH = {0x26, 0xFF, 0xCB, 0x84, 0xCB, 0x8C, 0xCB, 0x94, 0xCB, 0x9C,
                                           0xCB, 0xA4, 0xCB, 0xAC, 0xCB, 0xB4, 0xCB, 0xBC};

    constexpr std::array<uint8_t, 18> memoryL = {0x2E, 0xFF, 0xCB, 0x85, 0xCB, 0x8D, 0xCB, 0x95, 0xCB, 0x9D,
                                           0xCB, 0xA5, 0xCB, 0xAD, 0xCB, 0xB5, 0xCB, 0xBD};

    // Run tests for each register
    TestRegister(memoryA, bus.cpu_.get_accumulator_address(), expected_register_values);
    TestRegister(memoryB, bus.cpu_.get_registerB_address(), expected_register_values);
    TestRegister(memoryC, bus.cpu_.get_registerC_address(), expected_register_values);
    TestRegister(memoryD, bus.cpu_.get_registerD_address(), expected_register_values);
    TestRegister(memoryE, bus.cpu_.get_registerE_address(), expected_register_values);
    TestRegister(memoryH, bus.cpu_.get_registerH_address(), expected_register_values);
    TestRegister(memoryL, bus.cpu_.get_registerL_address(), expected_register_values);
}


TEST_F(ResetTest, RES_indirect_test)
{
    // Set doesnt affect any flags
    constexpr std::array<uint8_t, 18> expected_register_values = {
        0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xF8,
        0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80, 0x00
    };

    constexpr std::array<uint8_t, 29> memory = {
        0x21, 0x50, 0x00, 0x36, 0xFF, 0xCB, 0x86, 0x7E, 0xCB, 0x8E, 0x7E, 0xCB, 0x96, 0x7E,
        0xCB, 0x9E, 0x7E, 0xCB, 0xA6, 0x7E, 0xCB, 0xAE, 0x7E, 0xCB, 0xB6, 0x7E, 0xCB, 0xBE, 0x7E
    };

    TestRegister(memory, bus.cpu_.get_accumulator_address(), expected_register_values);
}


TEST_F(ResetTest, RES_indexed_ix_test)
{
    // Set doesnt affect any flags
    constexpr std::array<uint8_t, 19> expected_register_values = {
        0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8,
        0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80, 0x00
    };

    constexpr std::array<uint8_t, 49> memory = {
        0x21, 0x50, 0x00, 0x36, 0xFF, 0xDD, 0x21, 0x50,
        0x00, 0xDD, 0xCB, 0x00, 0x86, 0x7E, 0xDD, 0xCB,
        0x00, 0x8E, 0x7E, 0xDD, 0xCB, 0x00, 0x96, 0x7E,
        0xDD, 0xCB, 0x00, 0x9E, 0x7E, 0xDD, 0xCB, 0x00,
        0xA6, 0x7E, 0xDD, 0xCB, 0x00, 0xAE, 0x7E, 0xDD,
        0xCB, 0x00, 0xB6, 0x7E, 0xDD, 0xCB, 0x00, 0xBE,
        0x7E
    };

    TestRegister(memory, bus.cpu_.get_accumulator_address(), expected_register_values);
}


TEST_F(ResetTest, RES_indexed_iy_test)
{
    // Set doesnt affect any flags
    constexpr std::array<uint8_t, 19> expected_register_values = {
        0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8,
        0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80, 0x00
    };

    constexpr std::array<uint8_t, 49> memory = {
        0x21, 0x50, 0x00, 0x36, 0xFF, 0xFD, 0x21, 0x50,
        0x00, 0xFD, 0xCB, 0x00, 0x86, 0x7E, 0xFD, 0xCB,
        0x00, 0x8E, 0x7E, 0xFD, 0xCB, 0x00, 0x96, 0x7E,
        0xFD, 0xCB, 0x00, 0x9E, 0x7E, 0xFD, 0xCB, 0x00,
        0xA6, 0x7E, 0xFD, 0xCB, 0x00, 0xAE, 0x7E, 0xFD,
        0xCB, 0x00, 0xB6, 0x7E, 0xFD, 0xCB, 0x00, 0xBE,
        0x7E
    };

    TestRegister(memory, bus.cpu_.get_accumulator_address(), expected_register_values);
}