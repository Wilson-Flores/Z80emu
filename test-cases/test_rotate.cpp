#include "test_main.hpp"


TEST_F(RotateTest, RLCA_implied_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x01, 0x01, 0x00};

    std::vector<uint8_t> memory = {0x3E, 0x88, 0x07, 0x3E, 0x6B, 0x07};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLC_implied_test){
    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
            {{0x3E, 0x07}, // A
             {0x06, 0x00}, // B
             {0x0E, 0x01}, // C
             {0x16, 0x02}, // D
             {0x1E, 0x03}, // E
             {0x26, 0x04}, // H
             {0x2E, 0x05}  // L
            };

    std::vector<uint8_t> expected_flag_values = {0x00, 0x05, 0x05, 0x80};

    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
        std::vector<uint8_t> memory = {pair.first, 0x88, 0xCB, pair.second, pair.first, 0x6B, 0xCB, pair.second};

        TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
    }
}


TEST_F(RotateTest, RLC_indirect_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x05};

    std::vector<uint8_t> memory = {0x01, 0x0A, 0x00, 0x36, 0x88, 0xCB, 0x06};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLC_indexed_ix_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x05};

    std::vector<uint8_t> memory = {0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x88, 0xDD, 0xCB, 0xFF, 0x06};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLC_indexed_iy_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x05};

    std::vector<uint8_t> memory = {0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x88, 0xFD, 0xCB, 0xFF, 0x06};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRCA_implied_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x09, 0x09, 0x28};

    std::vector<uint8_t> memory = {0x3E, 0x11, 0x0F, 0x3E, 0xD6, 0x0F};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRC_implied_test){
    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
            {{0x3E, 0x0F}, // A
             {0x06, 0x08}, // B
             {0x0E, 0x09}, // C
             {0x16, 0x0A}, // D
             {0x1E, 0x0B}, // E
             {0x26, 0x0C}, // H
             {0x2E, 0x0D}  // L
            };

    std::vector<uint8_t> expected_flag_values = {0x00, 0x8D, 0x8D, 0x28};

    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
        std::vector<uint8_t> memory = {pair.first, 0x11, 0xCB, pair.second, pair.first, 0xD6, 0xCB, pair.second};

        TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
    }
}


TEST_F(RotateTest, RRC_indirect_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x8D};

    std::vector<uint8_t> memory = {0x01, 0x0A, 0x00, 0x36, 0x11, 0xCB, 0x0E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRC_indexed_ix_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x8D};

    std::vector<uint8_t> memory = {
            0xDD, 0x21, 0x00, 0x01, 0xDD,
            0x36, 0xFF, 0x11, 0xDD, 0xCB, 0xFF, 0x0E
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRC_indexed_iy_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x8D};

    std::vector<uint8_t> memory = {
            0xFD, 0x21, 0x00, 0x01, 0xFD,
            0x36, 0xFF, 0x11, 0xFD, 0xCB, 0xFF, 0x0E
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLA_implied_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x21, 0x28, 0x28, 0x09};

    std::vector<uint8_t> memory = {0x3E, 0x76, 0x3F, 0x17, 0x3E, 0x8F, 0x17};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RL_implied_test){
    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
            {{0x3E, 0x17}, // A
             {0x06, 0x10}, // B
             {0x0E, 0x11}, // C
             {0x16, 0x12}, // D
             {0x1E, 0x13}, // E
             {0x26, 0x14}, // H
             {0x2E, 0x15}  // L
            };

    // the flag value after CCF instruction changes based on accumulator's value
    std::vector<uint8_t> expected_flag_valueA = { 0x00, 0x21, 0xAC, 0xAC, 0x0D};
    std::vector<uint8_t> expected_flag_values = { 0x00, 0x01, 0xAC, 0xAC, 0x0D};

    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
        std::vector<uint8_t> memory = {pair.first, 0x76, 0x3F, 0xCB, pair.second, pair.first, 0x8F, 0xCB, pair.second};

        if(pair.first == 0x3E) {
            TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_valueA);
        }
        else {
            TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
        }

    }
}


TEST_F(RotateTest, RL_indirect_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x01, 0xAC, 0xAC, 0x0D};

    std::vector<uint8_t> memory = {0x01 ,0x0F, 0x00, 0x36, 0x76, 0x3F, 0xCB, 0x16, 0x36, 0x8F, 0xCB, 0x16};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RL_indexed_ix_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x01, 0xAC, 0xAC, 0xAC, 0x0D};

    std::vector<uint8_t> memory = {
            0xDD, 0x21, 0x00, 0x01, 0xDD,
            0x36, 0xFF, 0x76, 0x3F, 0xDD, 0xCB, 0xFF, 0x16,
            0x00, 0xDD, 0x36, 0xFF, 0x8F, 0xDD, 0xCB, 0xFF, 0x16
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RL_indexed_iy_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x01, 0xAC, 0xAC, 0xAC, 0x0D};

    std::vector<uint8_t> memory = {
            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x76,
            0x3F, 0xFD, 0xCB, 0xFF, 0x16, 0x00, 0xFD, 0x36,
            0xFF, 0x8F, 0xFD, 0xCB, 0xFF, 0x16
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRA_implied_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x21};

    std::vector<uint8_t> memory = {0x3E, 0xE1, 0x1F};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RR_implied_test){
    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
            {{0x3E, 0x1F}, // A
             {0x06, 0x18}, // B
             {0x0E, 0x19}, // C
             {0x16, 0x1A}, // D
             {0x1E, 0x1B}, // E
             {0x26, 0x1C}, // H
             {0x2E, 0x1D}  // L
            };
    std::vector<uint8_t> expected_flag_values = {0x00, 0x21};

    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
        std::vector<uint8_t> memory = {pair.first, 0xE1, 0xCB, pair.second};

        TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
    }
}


TEST_F(RotateTest, RR_indirect_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x21};

    std::vector<uint8_t> memory = { 0x01, 0x0F, 0x00, 0x36, 0xE1, 0xCB, 0x1E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RR_indexed_ix_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x21};

    std::vector<uint8_t> memory = {0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0xE1, 0xDD, 0xCB, 0xFF, 0x1E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RR_indexed_iy_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x21};

    std::vector<uint8_t> memory = {0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0xE1, 0xFD, 0xCB, 0xFF, 0x1E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLD_implied_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x00, 0x84};

    std::vector<uint8_t> memory = {0x01, 0x00, 0x50, 0x36, 0x31, 0x3E, 0x9A, 0xED, 0x6F};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRD_implied_test){
    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x00, 0x80};

    std::vector<uint8_t> memory = {0x01, 0x00, 0x50, 0x36, 0x20, 0x3E, 0x84, 0xED, 0x67};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}