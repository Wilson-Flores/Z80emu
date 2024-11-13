//#include "test_main.hpp"
//
//
//
//TEST_F(RotateTest, RLCA_implied_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x01, 0x01, 0x00};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x3E, 0x88, 0x07, 0x3E, 0x6B, 0x07};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < 4; byte_counter++) {
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RLC_implied_test){
//
//    // {first, second}
//    // {[LD r, n], [RLC r]}
//    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
//            {{0x3E, 0x07}, // A
//             {0x06, 0x00}, // B
//             {0x0E, 0x01}, // C
//             {0x16, 0x02}, // D
//             {0x1E, 0x03}, // E
//             {0x26, 0x04}, // H
//             {0x2E, 0x05}  // L
//            };
//
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x05, 0x05, 0x80};
//    bool compare_flag_values = false;
//
//    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
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
//
//            if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//                compare_flag_values = true;
//                std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//            }
//            ASSERT_EQ(compare_flag_values, false);
//        }
//    }
//}
//
//
//TEST_F(RotateTest, RLC_indirect_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x05};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x01, 0x0A, 0x00, 0x36, 0x88, 0xCB, 0x06};
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < 3; byte_counter++) {
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RLC_indexed_ix_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x05};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xDD, 0x21, 0x00, 0x01, 0xDD,
//            0x36, 0xFF, 0x88, 0xDD, 0xCB, 0xFF, 0x06
//    };
//
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < 3; byte_counter++) {
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RLC_indexed_iy_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x05};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xFD, 0x21, 0x00, 0x01, 0xFD,
//            0x36, 0xFF, 0x88, 0xFD, 0xCB, 0xFF, 0x06
//    };
//
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < 3; byte_counter++) {
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RRCA_implied_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x01, 0x01, 0x00};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x3E, 0x11, 0x0F, 0x3E, 0xD6, 0x0F};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < 4; byte_counter++) {
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RRC_implied_test){
//
//    // {first, second}
//    // {[LD r, n], [RLC r]}
//    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
//            {{0x3E, 0x0F}, // A
//             {0x06, 0x08}, // B
//             {0x0E, 0x09}, // C
//             {0x16, 0x0A}, // D
//             {0x1E, 0x0B}, // E
//             {0x26, 0x0C}, // H
//             {0x2E, 0x0D}  // L
//            };
//
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x85, 0x85, 0x00};
//    bool compare_flag_values = false;
//
//    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
//        std::vector<uint8_t> memory = {pair.first, 0x11, 0xCB, pair.second, pair.first, 0xD6, 0xCB, pair.second};
//
//        bus.rom_reset();
//
//        for (int i = 0; i < memory.size(); i++) {
//            bus.rom_write(i,memory[i]);
//        }
//
//        for(uint16_t byte_counter = 0; byte_counter < 4; byte_counter++){
//            bus.cpu.instruction_cycle();
//
//            if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//                compare_flag_values = true;
//                std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//            }
//            ASSERT_EQ(compare_flag_values, false);
//        }
//    }
//}
//
//
//TEST_F(RotateTest, RRC_indirect_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x01, 0x0A, 0x00, 0x36, 0x11, 0xCB, 0x0E};
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < 3; byte_counter++) {
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RRC_indexed_ix_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xDD, 0x21, 0x00, 0x01, 0xDD,
//            0x36, 0xFF, 0x11, 0xDD, 0xCB, 0xFF, 0x0E
//    };
//
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < 3; byte_counter++) {
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RRC_indexed_iy_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xFD, 0x21, 0x00, 0x01, 0xFD,
//            0x36, 0xFF, 0x11, 0xFD, 0xCB, 0xFF, 0x0E
//    };
//
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < 3; byte_counter++) {
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RLA_implied_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x01, 0x00, 0x00, 0x01};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x3E, 0x76, 0x3F, 0x17, 0x3E, 0x8F, 0x17};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//
//}
//
//
//TEST_F(RotateTest, RL_implied_test){
//    // {first, second}
//    // {[LD r, n], [RL r]}
//    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
//            {{0x3E, 0x17}, // A
//             {0x06, 0x10}, // B
//             {0x0E, 0x11}, // C
//             {0x16, 0x12}, // D
//             {0x1E, 0x13}, // E
//             {0x26, 0x14}, // H
//             {0x2E, 0x15}  // L
//            };
//
//    std::vector<uint8_t> expected_flag_values = { 0x00, 0x01, 0x84, 0x84, 0x05};
//    bool compare_flag_values = false;
//
//    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
//        std::vector<uint8_t> memory = {pair.first, 0x76, 0x3F, 0xCB, pair.second, pair.first, 0x8F, 0xCB, pair.second};
//
//        bus.rom_reset();
//
//        for (int i = 0; i < memory.size(); i++) {
//            bus.rom_write(i,memory[i]);
//        }
//
//        for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//            bus.cpu.instruction_cycle();
//
//            if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//                compare_flag_values = true;
//                std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//            }
//            ASSERT_EQ(compare_flag_values, false);
//        }
//    }
//}
//
//
//TEST_F(RotateTest, RL_indirect_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x01, 0x84, 0x84, 0x05};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x01 ,0x0F, 0x00, 0x36, 0x76, 0x3F, 0xCB, 0x16, 0x36, 0x8F, 0xCB, 0x16};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//
//}
//
//
//TEST_F(RotateTest, RL_indexed_ix_test){
//    std::vector<int> expected_flag_values = {0x00, 0x00, 0x01, 0x84, 0x84, 0x84, 0x05};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xDD, 0x21, 0x00, 0x01, 0xDD,
//            0x36, 0xFF, 0x76, 0x3F, 0xDD, 0xCB, 0xFF, 0x16,
//            0x00, 0xDD, 0x36, 0xFF, 0x8F, 0xDD, 0xCB, 0xFF, 0x16
//    };
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RL_indexed_iy_test){
//    std::vector<int> expected_flag_values = {0x00, 0x00, 0x01, 0x84, 0x84, 0x84, 0x05};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x76,
//            0x3F, 0xFD, 0xCB, 0xFF, 0x16, 0x00, 0xFD, 0x36,
//            0xFF, 0x8F, 0xFD, 0xCB, 0xFF, 0x16
//    };
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RRA_implied_test){
//    std::vector<int> expected_flag_values = {0x00, 0x01};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x3E, 0xE1, 0x1F};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RR_implied_test){
//    // {first, second}
//    // {[LD r, n], [RR r]}
//    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
//            {{0x3E, 0x1F}, // A
//             {0x06, 0x18}, // B
//             {0x0E, 0x19}, // C
//             {0x16, 0x1A}, // D
//             {0x1E, 0x1B}, // E
//             {0x26, 0x1C}, // H
//             {0x2E, 0x1D}  // L
//            };
//    std::vector<int> expected_flag_values = {0x00, 0x01};
//    bool compare_flag_values = false;
//
//    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
//        std::vector<uint8_t> memory = {pair.first, 0xE1, 0xCB, pair.second};
//
//        bus.rom_reset();
//
//        for (int i = 0; i < memory.size(); i++) {
//            bus.rom_write(i,memory[i]);
//        }
//
//        for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//            bus.cpu.instruction_cycle();
//
//            if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//                compare_flag_values = true;
//                std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//            }
//            ASSERT_EQ(compare_flag_values, false);
//        }
//    }
//}
//
//
//TEST_F(RotateTest, RR_indirect_test){
//    std::vector<int> expected_flag_values = {0x00, 0x00, 0x01};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = { 0x01, 0x0F, 0x00, 0x36, 0xE1, 0xCB, 0x1E};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RR_indexed_ix_test){
//    std::vector<int> expected_flag_values = {0x00, 0x00, 0x01};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0xE1, 0xDD, 0xCB, 0xFF, 0x1E};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RR_indexed_iy_test){
//    std::vector<int> expected_flag_values = {0x00, 0x00, 0x01};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0xE1, 0xFD, 0xCB, 0xFF, 0x1E};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RLD_implied_test){
//    std::vector<int> expected_flag_values = {0x00, 0x00, 0x00, 0x84};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x01, 0x00, 0x50, 0x36, 0x31, 0x3E, 0x9A, 0xED, 0x6F};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
//
//
//TEST_F(RotateTest, RRD_implied_test){
//    std::vector<int> expected_flag_values = {0x00, 0x00, 0x00, 0x80};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x01, 0x00, 0x50, 0x36, 0x20, 0x3E, 0x84, 0xED, 0x67};
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++){
//        bus.cpu.instruction_cycle();
//
//        if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//            compare_flag_values = true;
//            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.opcode) << '\t';
//
//            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                      << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//        }
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}