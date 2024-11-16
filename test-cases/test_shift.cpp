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


//TEST_F(ShiftTest, SLA_indirect_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x01, 0x80};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x01, 0x0F, 0x00, 0x36, 0xB1, 0xCB, 0x26, 0xCB, 0x26};
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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
//TEST_F(ShiftTest, SLA_indexed_ix_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x01, 0x80};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0xB1,
//            0xDD, 0xCB, 0xFF, 0x26, 0xDD, 0xCB, 0xFF, 0x26
//    };
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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
//TEST_F(ShiftTest, SLA_indexed_iy_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x01, 0x80};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0xB1,
//            0xFD, 0xCB, 0xFF, 0x26, 0xFD, 0xCB, 0xFF, 0x26
//    };
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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
//TEST_F(ShiftTest, SRA_implied_test){
//    // {first, second}
//    // {[LD r, n], [RLC r]}
//    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
//            {{0x3E, 0x2F}, // A
//             {0x06, 0x28}, // B
//             {0x0E, 0x29}, // C
//             {0x16, 0x2A}, // D
//             {0x1E, 0x2B}, // E
//             {0x26, 0x2C}, // H
//             {0x2E, 0x2D}  // L
//            };
//
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x85, 0x80};
//    bool compare_flag_values = false;
//
//    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
//        std::vector<uint8_t> memory = {pair.first, 0x81, 0xCB, pair.second, 0xCB, pair.second};
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
//TEST_F(ShiftTest, SRA_indirect_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85, 0x80};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {0x01, 0x0F, 0x00, 0x36, 0x81, 0xCB, 0x2E, 0xCB, 0x2E};
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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
//TEST_F(ShiftTest, SRA_indexed_ix_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85, 0x80};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x81,
//            0xDD, 0xCB, 0xFF, 0x2E, 0xDD, 0xCB, 0xFF, 0x2E
//    };
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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
//TEST_F(ShiftTest, SRA_indexed_iy_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00, 0x85, 0x80};
//    bool compare_flag_values = false;
//
//    std::vector<uint8_t> memory = {
//            0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x81,
//            0xFD, 0xCB, 0xFF, 0x2E, 0xFD, 0xCB, 0xFF, 0x2E
//    };
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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
//TEST_F(ShiftTest, SRL_implied_test){
//    // {first, second}
//    // {[LD r, n], [SRL r]}
//    std::vector<std::pair<uint8_t, uint8_t>> registers_instructions =
//            {{0x3E, 0x3F}, // A
//             {0x06, 0x38}, // B
//             {0x0E, 0x39}, // C
//             {0x16, 0x3A}, // D
//             {0x1E, 0x3B}, // E
//             {0x26, 0x3C}, // H
//             {0x2E, 0x3D}  // L
//            };
//
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x05};
//    bool compare_flag_values = false;
//
//    for (const std::pair<const uint8_t, uint8_t>& pair : registers_instructions) {
//        std::vector<uint8_t> memory = {pair.first, 0x8F, 0xCB, pair.second};
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
//TEST_F(ShiftTest, SRL_indirect_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00,0x05};
//    bool compare_flag_values = false;
//    std::vector<uint8_t> memory = {0x01, 0x0F, 0x00, 0x36, 0x8F, 0xCB, 0x3E};
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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
//TEST_F(ShiftTest, SRL_indexed_ix_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00,0x05};
//    bool compare_flag_values = false;
//    std::vector<uint8_t> memory = {0xDD, 0x21, 0x00, 0x01, 0xDD, 0x36, 0xFF, 0x8F, 0xDD, 0xCB, 0xFF, 0x3E};
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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
//TEST_F(ShiftTest, SRL_indexed_iy_test){
//    std::vector<uint8_t> expected_flag_values = {0x00, 0x00,0x05};
//    bool compare_flag_values = false;
//    std::vector<uint8_t> memory = {0xFD, 0x21, 0x00, 0x01, 0xFD, 0x36, 0xFF, 0x8F, 0xFD, 0xCB, 0xFF, 0x3E};
//
//    bus.rom_reset();
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    for(uint16_t byte_counter = 0; byte_counter < expected_flag_values.size(); byte_counter++) {
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