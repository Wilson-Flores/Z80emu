#include "test_main.hpp"


void BusTest::TestRegister(const std::vector<uint8_t>& memory, const uint8_t& reg,
                  const std::vector<uint8_t>& expected_register_values) {
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


void BusTest::TestFlag(const std::vector<uint8_t> &memory, const uint8_t &flag,
                       const std::vector<uint8_t> &expected_flag_values) {
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