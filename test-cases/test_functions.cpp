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
    for (const uint8_t expected_reg_value : expected_register_values) {
        bus.cpu_.instruction_cycle();
        if (reg != expected_reg_value) {
            compare_reg_values = true;
            std::cout << "OPCODE: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
            << static_cast<int>(bus.cpu_.get_opcode_address()) << '\t';
            std::cout << "REG VALUE: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
            << static_cast<int>(reg) << '\n';
            std::cout << "EXPECTED REG VALUE: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
            << static_cast<int>(expected_reg_value) << '\n';
        }
        ASSERT_EQ(compare_reg_values, false);
    }
}