#ifndef  test_main_hpp
#define test_main_hpp

#include "gtest/gtest.h"
#include "../Bus.hpp"


// Define a test fixture class
// Define a generic test fixture class for all tests
class BusTest : public ::testing::Test {
protected:
    Bus bus;

    void TestRegister(const std::vector<uint8_t>& memory, const uint8_t& reg,
        const std::vector<uint8_t>& expected_register_values) {

        bool compare_reg_values = false;

        // Write memory to the bus
        bus.rom_reset();
        for (int j = 0; j < memory.size(); j++) {
            bus.rom_write(j, memory[j]);
        }

        // Test register values
        for (const uint8_t expected_reg_value : expected_register_values) {
            bus.cpu.instruction_cycle();
            if (reg != expected_reg_value) {
                compare_reg_values = true;
                std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                          << static_cast<int>(bus.cpu.opcode) << '\t';
                std::cout << "REG VALUE: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
                          << static_cast<int>(reg) << '\n';
                std::cout << "EXPECTED REG VALUE: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
          << static_cast<int>(expected_reg_value) << '\n';
            }
            ASSERT_EQ(compare_reg_values, false);
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

#endif