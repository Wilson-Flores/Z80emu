#ifndef  test_main_hpp
#define test_main_hpp

#include "gtest/gtest.h"
#include "../Bus.hpp"



// Define a test fixture class
// Define a generic test fixture class for all tests
class BusTest : public ::testing::Test {
protected:
    Bus bus;

    // when dealing with templates and undefined references, have the definition in the header.
    template<size_t N, size_t M>
    void TestRegister(const std::array<uint8_t, N>& memory, const uint8_t& reg,
                               const std::array<uint8_t, M>& expected_register_values) {
        bool compare_reg_values = false;
        // Write memory to the bus
        bus.rom_reset();
        for (int j = 0; j < memory.size(); j++) {
            bus.rom_write(j, memory[j]);
        }

        // Test register values
        for (const uint8_t reg_value : expected_register_values) {
            bus.cpu_.instruction_cycle();
            if (reg != reg_value) {
                compare_reg_values = true;
                std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                          << static_cast<int>(bus.cpu_.get_opcode_address()) << '\t';
                std::cout << "REG VALUE: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                          << static_cast<int>(reg) << '\n';
                std::cout << "EXPECTED REG VALUE: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                          << static_cast<int>(reg_value) << '\n';
            }
            ASSERT_EQ(compare_reg_values, false);
        }
    }

    template<size_t N, size_t M>
    void TestFlag(const std::array<uint8_t, N>& memory, const uint8_t& flag,
                           const std::array<uint8_t, M>& expected_flag_values) {
        bool compare_flag_values = false;
        bus.rom_reset();
        for (int j = 0; j < memory.size(); j++) {
            bus.rom_write(j, memory[j]);
        }

        for (const uint8_t flag_value : expected_flag_values) {
            bus.cpu_.instruction_cycle();
            if (flag != flag_value) {
                compare_flag_values = true;
                std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                          << static_cast<int>(bus.cpu_.get_opcode_address()) << '\t';
                std::cout << "FLAG VALUE: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                          << static_cast<int>(flag) << '\n';
                std::cout << "EXPECTED FLAG VALUE: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                          << static_cast<int>(flag_value) << '\n';
            }
            ASSERT_EQ(compare_flag_values, false);
        }
    }

};

// Use BusTest as the base class for all specific test cases
using IncTest = BusTest;
using RotateTest = BusTest;
using ShiftTest = BusTest;
using BitTest = BusTest;
using SetTest = BusTest;
using ResetTest = BusTest;
using JumpTest = BusTest;
using LoadTest = BusTest;

#endif