#include "test_main.hpp"


TEST_F(LoadTest, LD_register_immediate_test){
    constexpr std::array<uint8_t, 1> expected_reg_value = {0x28};

    constexpr std::array<uint8_t, 2> memoryA = {0x3E, 0x28};
    constexpr std::array<uint8_t, 2> memoryB = {0x06, 0x28};
    constexpr std::array<uint8_t, 2> memoryC = {0x0E, 0x28};
    constexpr std::array<uint8_t, 2> memoryD = {0x16, 0x28};
    constexpr std::array<uint8_t, 2> memoryE = {0x1E, 0x28};
    constexpr std::array<uint8_t, 2> memoryH = {0x26, 0x28};
    constexpr std::array<uint8_t, 2> memoryL = {0x2E, 0x28};

    TestRegister(memoryA, bus.cpu_.get_accumulator_address(), expected_reg_value);
    TestRegister(memoryB, bus.cpu_.get_registerB_address(), expected_reg_value);
    TestRegister(memoryC, bus.cpu_.get_registerC_address(), expected_reg_value);
    TestRegister(memoryD, bus.cpu_.get_registerD_address(), expected_reg_value);
    TestRegister(memoryE, bus.cpu_.get_registerE_address(), expected_reg_value);
    TestRegister(memoryH, bus.cpu_.get_registerH_address(), expected_reg_value);
    TestRegister(memoryL, bus.cpu_.get_registerL_address(), expected_reg_value);
}
