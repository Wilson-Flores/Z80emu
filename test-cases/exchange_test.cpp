#include "exchange_test.hpp"


void EX_test(Bus& test) {
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0x08, 0x11, 0x1C, 0x1B, 0x21, 0x1E,
            0x1D, 0xEB, 0x01, 0x1A, 0x19, 0xD9, 0x21, 0x1E,
            0x1D, 0x31, 0x21, 0x00, 0xE3, 0xDD, 0x21, 0x22,
            0x21, 0xFD, 0x21, 0x24, 0x23, 0xDD, 0xE3, 0xFD,
            0xE3, 0x00, 0x00
    };

    test.rom_reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < 14; i++) {
        test.cpu.instruction_cycle();
    }
}