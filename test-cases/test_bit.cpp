//#include "test_main.hpp"
//
//
//TEST_F(BitTest, BIT_implied_test){
//    std::vector<uint8_t> expected_flag_values_00 = {0x00, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54};
//    std::vector<uint8_t> expected_flag_values_FF = {0x00, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xB8};
//
//    std::vector<uint8_t> load_value = {0x00, 0xFF};
//
//    bool compare_flag_values = false;
//
//    std::vector<std::pair<uint8_t, std::vector<uint8_t>>> register_instructions = {
//            { 0x3E, {0x47, 0x4F, 0x57, 0x5F, 0x67, 0x6F, 0x77, 0x7F} }, // A
//            { 0x06, {0x40, 0x48, 0x50, 0x58, 0x60, 0x68, 0x70, 0x78} }, // B
//            { 0x0E, {0x41, 0x49, 0x51, 0x59, 0x61, 0x69, 0x71, 0x79} }, // C
//            { 0x16, {0x42, 0x4A, 0x52, 0x5A, 0x62, 0x6A, 0x72, 0x7A} }, // D
//            { 0x1E, {0x43, 0x4B, 0x53, 0x5B, 0x63, 0x6B, 0x73, 0x7B} }, // E
//            { 0x26, {0x44, 0x4C, 0x54, 0x5C, 0x64, 0x6C, 0x74, 0x7C} }, // H
//            { 0x2E, {0x45, 0x4D, 0x55, 0x5D, 0x65, 0x6D, 0x75, 0x7D} }  // L
//    };
//
//
//    for (int i = 0; i < load_value.size(); i++){
//        for(const std::pair<uint8_t, std::vector<uint8_t>>& pair : register_instructions){
//            std::vector<uint8_t> memory = {pair.first, load_value[i], 0xCB, pair.second[0], 0xCB, pair.second[1],
//                                           0xCB, pair.second[2], 0xCB, pair.second[3], 0xCB, pair.second[4],
//                                           0xCB, pair.second[5], 0xCB, pair.second[6], 0xCB, pair.second[7]};
//
//            bus.rom_reset();
//
//            for (int j = 0; j < memory.size(); j++) {
//                bus.rom_write(j,memory[j]);
//            }
//
//            if(load_value[i] == 0x00){
//                for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_00.size(); byte_counter++){
//                    bus.cpu.instruction_cycle();
//
//                    if(bus.cpu.flag_register != expected_flag_values_00[byte_counter]){
//                        compare_flag_values = true;
//                        std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                                  << static_cast<int>(load_value[i]) << '\t';
//
//                        std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                                  << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                        std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                                  << static_cast<int>(bus.cpu.flag_register) << '\n';
//                    }
//                    ASSERT_EQ(compare_flag_values, false);
//                }
//            }
//            else if(load_value[i] == 0xFF){
//                for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_FF.size(); byte_counter++){
//                    bus.cpu.instruction_cycle();
//
//                    if(bus.cpu.flag_register != expected_flag_values_FF[byte_counter]){
//                        compare_flag_values = true;
//                        std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                                  << static_cast<int>(load_value[i]) << '\t';
//                        std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                                  << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                        std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                                  << static_cast<int>(bus.cpu.flag_register) << '\n';
//                    }
//                    ASSERT_EQ(compare_flag_values, false);
//                }
//            }
//        }
//    }
//}
//
//
//TEST_F(BitTest, BIT_indirect_test){
//    std::vector<uint8_t> expected_flag_values_00 = {0x00, 0x00, 0x00, 0x00,
//                                                    0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C};
//    std::vector<uint8_t> expected_flag_values_FF = {0x00, 0x00, 0x00, 0x00,
//                                                    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38};
//
//    std::vector<uint8_t> load_value = {0x00, 0xFF};
//    bool compare_flag_values = false;
//
//    for (int i = 0; i < load_value.size(); i++){
//        std::vector<uint8_t> memory = {
//                0x21, 0x50, 0x00, 0xDD, 0x21, 0x00, 0x28, 0xDD,
//                0x36, 0x00, 0x00, 0x36, load_value[i], 0xCB, 0x46, 0xCB,
//                0x4E, 0xCB, 0x56, 0xCB, 0x5E, 0xCB, 0x66, 0xCB,
//                0x6E, 0xCB, 0x76, 0xCB, 0x7E
//        };
//
//        bus.rom_reset();
//
//        for (int j = 0; j < memory.size(); j++) {
//            bus.rom_write(j,memory[j]);
//        }
//
//        if(load_value[i] == 0x00){
//            for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_00.size(); byte_counter++){
//                bus.cpu.instruction_cycle();
//
//                if(bus.cpu.flag_register != expected_flag_values_00[byte_counter]){
//                    compare_flag_values = true;
//                    std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(load_value[i]) << '\t';
//
//                    std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                    std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.flag_register) << '\n';
//                }
//                ASSERT_EQ(compare_flag_values, false);
//            }
//        }
//        else if(load_value[i] == 0xFF){
//            for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_FF.size(); byte_counter++){
//                bus.cpu.instruction_cycle();
//
//                if(bus.cpu.flag_register != expected_flag_values_FF[byte_counter]){
//                    compare_flag_values = true;
//                    std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(load_value[i]) << '\t';
//                    std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                    std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.flag_register) << '\n';
//                }
//                ASSERT_EQ(compare_flag_values, false);
//            }
//        }
//    }
//}
//
//
//TEST_F(BitTest, BIT_indexed_ix_test){
//    std::vector<uint8_t> expected_flag_values_00 = {0x00, 0x00, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C};
//    std::vector<uint8_t> expected_flag_values_FF = {0x00, 0x00, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38};
//
//    std::vector<uint8_t> load_value = {0x00, 0xFF};
//    bool compare_flag_values = false;
//
//    for (int i = 0; i < load_value.size(); i++){
//        std::vector<uint8_t> memory = {
//            0xDD, 0x21, 0x00, 0x28, 0xDD, 0x36, 0x00, load_value[i],
//            0xDD, 0xCB, 0x00, 0x46, 0xDD, 0xCB, 0x00, 0x4E,
//            0xDD, 0xCB, 0x00, 0x56, 0xDD, 0xCB, 0x00, 0x5E,
//            0xDD, 0xCB, 0x00, 0x66, 0xDD, 0xCB, 0x00, 0x6E,
//            0xDD, 0xCB, 0x00, 0x76, 0xDD, 0xCB, 0x00, 0x7E
//        };
//
//        bus.rom_reset();
//
//        for (int j = 0; j < memory.size(); j++) {
//            bus.rom_write(j,memory[j]);
//        }
//
//        if(load_value[i] == 0x00){
//            for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_00.size(); byte_counter++){
//                bus.cpu.instruction_cycle();
//
//                if(bus.cpu.flag_register != expected_flag_values_00[byte_counter]){
//                    compare_flag_values = true;
//                    std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(load_value[i]) << '\t';
//
//                    std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                    std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.flag_register) << '\n';
//                }
//                ASSERT_EQ(compare_flag_values, false);
//            }
//        }
//        else if(load_value[i] == 0xFF){
//            for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_FF.size(); byte_counter++){
//                bus.cpu.instruction_cycle();
//
//                if(bus.cpu.flag_register != expected_flag_values_FF[byte_counter]){
//                    compare_flag_values = true;
//                    std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(load_value[i]) << '\t';
//                    std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                    std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.flag_register) << '\n';
//                }
//                ASSERT_EQ(compare_flag_values, false);
//            }
//        }
//    }
//}
//
//
//TEST_F(BitTest, BIT_indexed_iy_test){
//    std::vector<uint8_t> expected_flag_values_00 = {0x00, 0x00, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C};
//    std::vector<uint8_t> expected_flag_values_FF = {0x00, 0x00, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38};
//
//    std::vector<uint8_t> load_value = {0x00, 0xFF};
//    bool compare_flag_values = false;
//
//    for (int i = 0; i < load_value.size(); i++){
//        std::vector<uint8_t> memory = {
//            0xFD, 0x21, 0x00, 0x28, 0xFD, 0x36, 0x00, load_value[i],
//            0xFD, 0xCB, 0x00, 0x46, 0xFD, 0xCB, 0x00, 0x4E,
//            0xFD, 0xCB, 0x00, 0x56, 0xFD, 0xCB, 0x00, 0x5E,
//            0xFD, 0xCB, 0x00, 0x66, 0xFD, 0xCB, 0x00, 0x6E,
//            0xFD, 0xCB, 0x00, 0x76, 0xFD, 0xCB, 0x00, 0x7E
//        };
//
//        bus.rom_reset();
//
//        for (int j = 0; j < memory.size(); j++) {
//            bus.rom_write(j,memory[j]);
//        }
//
//        if(load_value[i] == 0x00){
//            for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_00.size(); byte_counter++){
//                bus.cpu.instruction_cycle();
//
//                if(bus.cpu.flag_register != expected_flag_values_00[byte_counter]){
//                    compare_flag_values = true;
//                    std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(load_value[i]) << '\t';
//
//                    std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                    std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.flag_register) << '\n';
//                }
//                ASSERT_EQ(compare_flag_values, false);
//            }
//        }
//        else if(load_value[i] == 0xFF){
//            for(uint16_t byte_counter = 0; byte_counter < expected_flag_values_FF.size(); byte_counter++){
//                bus.cpu.instruction_cycle();
//
//                if(bus.cpu.flag_register != expected_flag_values_FF[byte_counter]){
//                    compare_flag_values = true;
//                    std::cout << "VALUE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(load_value[i]) << '\t';
//                    std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                    std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                              << static_cast<int>(bus.cpu.flag_register) << '\n';
//                }
//                ASSERT_EQ(compare_flag_values, false);
//            }
//        }
//    }
//}