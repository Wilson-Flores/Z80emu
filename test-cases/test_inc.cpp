//#include "test_main.hpp"
//
//
//TEST_F(IncTest, INC_implied_register_test){
//    std::vector<int> expected_flag_values = {
//            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10,
//            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x30,
//            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x30,
//            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x10,
//            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10,
//            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x30,
//            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x30,
//            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x94,
//            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90,
//            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0xB0,
//            0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xB0,
//            0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0x90,
//            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x90,
//            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0xB0,
//            0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xB0,
//            0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0x50
//    };
//    bool compare_flag_values = false;
//
//
//    std::vector<uint8_t> memory = {
//            0x00, 0x00, 0x00, 0x3E, 0x00, 0x31, 0x00, 0x02,
//            0x21, 0x00, 0x00, 0x3C, 0xF5, 0xC1, 0xE5, 0x33,
//            0x33, 0xC3, 0x0B, 0x00
//    };
//
//    for (int i = 0; i < memory.size(); i++) {
//        bus.rom_write(i,memory[i]);
//    }
//
//    uint16_t byte_counter = 0;
//
//    bool accumulator_cycle = false;
//
//    while(!accumulator_cycle){
//        bus.cpu.instruction_cycle();
//
//        // PUSH HL Instruction
//        if(bus.cpu.opcode == 0xE5){
//            if(bus.cpu.get_flag_register_value() != expected_flag_values[byte_counter]){
//                compare_flag_values = true;
//
//                std::cout << "HEX Value: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(byte_counter) << '\t';
//
//                std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.opcode) << '\t';
//
//                std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
//                          << static_cast<int>(bus.cpu.get_flag_register_value()) << '\n';
//            }
//
//            if(bus.cpu.get_registerA_value() == 0x00){
//                accumulator_cycle = true;
//            }
//            byte_counter++;
//        }
//
//        ASSERT_EQ(compare_flag_values, false);
//    }
//}
