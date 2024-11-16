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
        const std::vector<uint8_t>& expected_register_values);


    void TestFlag(const std::vector<uint8_t>& memory, const uint8_t& flag,
                      const std::vector<uint8_t>& expected_flag_values);

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