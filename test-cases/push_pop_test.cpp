#include "push_pop_test.hpp"


void push_pop_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x01, 0x19, 0x1A, 0x11, 0x1B, 0x1C, 0x21, 0x1D,
            0x1E, 0x31, 0x00, 0x30, 0xDD, 0x21, 0x21, 0x22,
            0xFD, 0x21, 0x23, 0x24, 0xC5, 0xD5, 0xE5, 0xF5,
            0xDD, 0xE5, 0xFD, 0xE5, 0xC1, 0xD1, 0xE1, 0xF1,
            0xDD, 0xE1, 0xFD, 0xE1
    };

    test.rom_reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < 18; i++) {
        test.cpu.instruction_cycle();
    }
}
