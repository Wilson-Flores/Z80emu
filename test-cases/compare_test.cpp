#include "compare_test.hpp"


void compare_test(Bus& test) {
    std::vector<uint8_t> memory = {
            0x01, 0x0A, 0x00, 0x21, 0x00, 0x00, 0x3E, 0x00,
            0xED, 0xA1, 0xED, 0xB1, 0x01, 0x0A, 0x00, 0xED, 0xA9, 0xED, 0xB9
    };

    test.rom_reset();

    for (int i = 0; i < memory.size(); i++) {
        test.rom[i] = memory[i];
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }

    // test full byte range 64KB
    for(uint16_t byte_counter = 0; byte_counter < 0xFFFF; byte_counter++){
        test.cpu.instruction_cycle();
    }

}

