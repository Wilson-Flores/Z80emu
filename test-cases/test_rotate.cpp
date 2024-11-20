#include "test_main.hpp"


TEST_F(RotateTest, RLCA_implied_test){
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x01, 0x01, 0x00};

    constexpr std::array<uint8_t, 6> memory = {0x3E, 0x88, 0x07, 0x3E, 0x6B, 0x07};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLC_implied_test){
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x05, 0x05, 0x80};

    constexpr std::array<uint8_t, 8> memoryA = {0x3E, 0x88, 0xCB, 0x07, 0x3E, 0x6B, 0xCB, 0x07};
    constexpr std::array<uint8_t, 8> memoryB = {0x06, 0x88, 0xCB, 0x00, 0x06, 0x6B, 0xCB, 0x00};
    constexpr std::array<uint8_t, 8> memoryC = {0x0E, 0x88, 0xCB, 0x01, 0x0E, 0x6B, 0xCB, 0x01};
    constexpr std::array<uint8_t, 8> memoryD = {0x16, 0x88, 0xCB, 0x02, 0x16, 0x6B, 0xCB, 0x02};
    constexpr std::array<uint8_t, 8> memoryE = {0x1E, 0x88, 0xCB, 0x03, 0x1E, 0x6B, 0xCB, 0x03};
    constexpr std::array<uint8_t, 8> memoryH = {0x26, 0x88, 0xCB, 0x04, 0x26, 0x6B, 0xCB, 0x04};
    constexpr std::array<uint8_t, 8> memoryL = {0x2E, 0x88, 0xCB, 0x05, 0x2E, 0x6B, 0xCB, 0x05};


    TestFlag(memoryA, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryB, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryC, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryD, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryE, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryH, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryL, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLC_indirect_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x05};

    constexpr std::array<uint8_t, 7> memory = {0x01, 0x0A, 0x00, 0x36, 0x88, 0xCB, 0x06};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLC_indexed_ix_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x05};

    constexpr std::array<uint8_t, 12> memory = {0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x88, 0xDD, 0xCB, 0xFF, 0x06};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLC_indexed_iy_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x05};

    constexpr std::array<uint8_t, 12> memory = {0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x88, 0xFD, 0xCB, 0xFF, 0x06};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRCA_implied_test){
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x09, 0x09, 0x28};

    constexpr std::array<uint8_t, 6> memory = {0x3E, 0x11, 0x0F, 0x3E, 0xD6, 0x0F};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRC_implied_test){
    constexpr std::array<uint8_t, 8> memoryA = {0x3E, 0x11, 0xCB, 0x0F, 0x3E, 0xD6, 0xCB, 0x0F};
    constexpr std::array<uint8_t, 8> memoryB = {0x06, 0x11, 0xCB, 0x08, 0x06, 0xD6, 0xCB, 0x08};
    constexpr std::array<uint8_t, 8> memoryC = {0x0E, 0x11, 0xCB, 0x09, 0x0E, 0xD6, 0xCB, 0x09};
    constexpr std::array<uint8_t, 8> memoryD = {0x16, 0x11, 0xCB, 0x0A, 0x16, 0xD6, 0xCB, 0x0A};
    constexpr std::array<uint8_t, 8> memoryE = {0x1E, 0x11, 0xCB, 0x0B, 0x1E, 0xD6, 0xCB, 0x0B};
    constexpr std::array<uint8_t, 8> memoryH = {0x26, 0x11, 0xCB, 0x0C, 0x26, 0xD6, 0xCB, 0x0C};
    constexpr std::array<uint8_t, 8> memoryL = {0x2E, 0x11, 0xCB, 0x0D, 0x2E, 0xD6, 0xCB, 0x0D};

    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x8D, 0x8D, 0x28};

    TestFlag(memoryA, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryB, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryC, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryD, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryE, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryH, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryL, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRC_indirect_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x8D};

    constexpr std::array<uint8_t, 7> memory = {0x01, 0x0A, 0x00, 0x36, 0x11, 0xCB, 0x0E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRC_indexed_ix_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x8D};

    constexpr std::array<uint8_t, 12> memory = {
            0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x11, 0xDD, 0xCB, 0xFF, 0x0E
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRC_indexed_iy_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x8D};

    constexpr std::array<uint8_t, 12> memory = {
            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x11, 0xFD, 0xCB, 0xFF, 0x0E
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLA_implied_test){
    constexpr std::array<uint8_t, 5> expected_flag_values = {0x00, 0x21, 0x28, 0x28, 0x09};

    constexpr std::array<uint8_t, 7> memory = {0x3E, 0x76, 0x3F, 0x17, 0x3E, 0x8F, 0x17};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RL_implied_test){
    // the flag value after CCF instruction changes based on accumulator's value
    constexpr std::array<uint8_t, 5> expected_flag_valueA = { 0x00, 0x21, 0xAC, 0xAC, 0x0D};
    constexpr std::array<uint8_t, 5> expected_flag_values = { 0x00, 0x01, 0xAC, 0xAC, 0x0D};

    constexpr std::array<uint8_t, 9> memoryA = {0x3E, 0x76, 0x3F, 0xCB, 0x17, 0x3E, 0x8F, 0xCB, 0x17};
    constexpr std::array<uint8_t, 9> memoryB = {0x06, 0x76, 0x3F, 0xCB, 0x10, 0x06, 0x8F, 0xCB, 0x10};
    constexpr std::array<uint8_t, 9> memoryC = {0x0E, 0x76, 0x3F, 0xCB, 0x11, 0x0E, 0x8F, 0xCB, 0x11};
    constexpr std::array<uint8_t, 9> memoryD = {0x16, 0x76, 0x3F, 0xCB, 0x12, 0x16, 0x8F, 0xCB, 0x12};
    constexpr std::array<uint8_t, 9> memoryE = {0x1E, 0x76, 0x3F, 0xCB, 0x13, 0x1E, 0x8F, 0xCB, 0x13};
    constexpr std::array<uint8_t, 9> memoryH = {0x26, 0x76, 0x3F, 0xCB, 0x14, 0x26, 0x8F, 0xCB, 0x14};
    constexpr std::array<uint8_t, 9> memoryL = {0x2E, 0x76, 0x3F, 0xCB, 0x15, 0x2E, 0x8F, 0xCB, 0x15};

    TestFlag(memoryA, bus.cpu_.get_flag_register_address(), expected_flag_valueA);
    TestFlag(memoryB, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryC, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryD, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryE, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryH, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryL, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RL_indirect_test){
    constexpr std::array<uint8_t, 6> expected_flag_values = {0x00, 0x00, 0x01, 0xAC, 0xAC, 0x0D};

    constexpr std::array<uint8_t, 12> memory = {0x01 ,0x0F, 0x00, 0x36, 0x76, 0x3F, 0xCB, 0x16, 0x36, 0x8F, 0xCB, 0x16};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RL_indexed_ix_test){
    constexpr std::array<uint8_t, 7> expected_flag_values = {0x00, 0x00, 0x01, 0xAC, 0xAC, 0xAC, 0x0D};

    constexpr std::array<uint8_t, 22> memory = {
            0xDD, 0x21, 0x00, 0x01, 0xDD,
            0x36, 0xFF, 0x76, 0x3F, 0xDD, 0xCB, 0xFF, 0x16,
            0x00, 0xDD, 0x36, 0xFF, 0x8F, 0xDD, 0xCB, 0xFF, 0x16
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RL_indexed_iy_test){
    constexpr std::array<uint8_t, 7> expected_flag_values = {0x00, 0x00, 0x01, 0xAC, 0xAC, 0xAC, 0x0D};

    constexpr std::array<uint8_t, 22> memory = {
            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x76,
            0x3F, 0xFD, 0xCB, 0xFF, 0x16, 0x00, 0xFD, 0x36,
            0xFF, 0x8F, 0xFD, 0xCB, 0xFF, 0x16
    };

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRA_implied_test){
    constexpr std::array<uint8_t, 2> expected_flag_values = {0x00, 0x21};

    constexpr std::array<uint8_t, 3> memory = {0x3E, 0xE1, 0x1F};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RR_implied_test){
    constexpr std::array<uint8_t, 2> expected_flag_values = {0x00, 0x21};

    constexpr std::array<uint8_t, 4> memoryA = {0x3E, 0xE1, 0xCB, 0x1F};
    constexpr std::array<uint8_t, 4> memoryB = {0x06, 0xE1, 0xCB, 0x18};
    constexpr std::array<uint8_t, 4> memoryC = {0x0E, 0xE1, 0xCB, 0x19};
    constexpr std::array<uint8_t, 4> memoryD = {0x16, 0xE1, 0xCB, 0x1A};
    constexpr std::array<uint8_t, 4> memoryE = {0x1E, 0xE1, 0xCB, 0x1B};
    constexpr std::array<uint8_t, 4> memoryH = {0x26, 0xE1, 0xCB, 0x1C};
    constexpr std::array<uint8_t, 4> memoryL = {0x2E, 0xE1, 0xCB, 0x1D};

    TestFlag(memoryA, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryB, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryC, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryD, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryE, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryH, bus.cpu_.get_flag_register_address(), expected_flag_values);
    TestFlag(memoryL, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RR_indirect_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x21};

    constexpr std::array<uint8_t, 7> memory = { 0x01, 0x0F, 0x00, 0x36, 0xE1, 0xCB, 0x1E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RR_indexed_ix_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x21};

    constexpr std::array<uint8_t, 12> memory = {0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0xE1, 0xDD, 0xCB, 0xFF, 0x1E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RR_indexed_iy_test){
    constexpr std::array<uint8_t, 3> expected_flag_values = {0x00, 0x00, 0x21};

    constexpr std::array<uint8_t, 12> memory = {0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0xE1, 0xFD, 0xCB, 0xFF, 0x1E};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RLD_implied_test){
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x00, 0x00, 0x84};

    constexpr std::array<uint8_t, 9> memory = {0x01, 0x00, 0x50, 0x36, 0x31, 0x3E, 0x9A, 0xED, 0x6F};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}


TEST_F(RotateTest, RRD_implied_test){
    constexpr std::array<uint8_t, 4> expected_flag_values = {0x00, 0x00, 0x00, 0x80};

    constexpr std::array<uint8_t, 9> memory = {0x01, 0x00, 0x50, 0x36, 0x20, 0x3E, 0x84, 0xED, 0x67};

    TestFlag(memory, bus.cpu_.get_flag_register_address(), expected_flag_values);
}