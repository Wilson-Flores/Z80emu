#include "../Bus.hpp"
#include "gtest/gtest.h"


// Define a test fixture class
//class RotateTest : public ::testing::Test {
//protected:
//    Bus bus;
//};
//
//TEST_F(RotateTest, RLC_implied_test){
//    std::vector<std::pair<uint8_t, uint8_t>> registers =
//            {{0x3E, 0x07}, // A
//             {0x06, 0x00}, // B
//             {0x0E, 0x01}, // C
//             {0x16, 0x02}, // D
//             {0x1E, 0x03}, // E
//             {0x26, 0x04}, // H
//             {0x2E, 0x05}  // L
//            };
//
//    for (const std::pair<const uint8_t, uint8_t>& pair : registers) {
//        std::vector<uint8_t> memory = {pair.first, 0x88, 0xCB, pair.second, pair.first, 0x6B, 0xCB, pair.second};
//
//        bus.rom_reset();
//
//        for (int i = 0; i < memory.size(); i++) {
//            bus.rom_write(i,memory[i]);
//        }
//
//        for(uint16_t byte_counter = 0; byte_counter < 4; byte_counter++){
//            bus.cpu.instruction_cycle();
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.flag_register) << '\n';
//        }
//    }
//}