#include "add_test.hpp"


void add_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16, 0x1C,
            0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F, 0x87, 0x80,
            0x81, 0x82, 0x83, 0x84, 0x85, 0x21, 0x00, 0x00,
            0x32, 0x00, 0x00, 0x88, 0xDD, 0x21, 0x22, 0x00,
            0xFD, 0x21, 0x24, 0x00, 0xDD, 0x86, 0xDE, 0xFD,
            0x86, 0xDC, 0xC6, 0x8C
    };

    test.rom_reset();

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }

    // test full byte range 64KB
    for(uint16_t byte_counter = 0; byte_counter < 22; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void adc_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16, 0x1C,
            0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F, 0x8F, 0x88,
            0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x21, 0x00, 0x00,
            0x32, 0x00, 0x00, 0x8E, 0xDD, 0x21, 0x22, 0x00,
            0xFD, 0x21, 0x24, 0x00, 0xDD, 0x8E, 0xDE, 0xFD,
            0x8E, 0xDC, 0xCE, 0x89
    };

    test.rom_reset();

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }

    // test full byte range 64KB
    for(uint16_t byte_counter = 0; byte_counter < 22; byte_counter++){
        test.cpu.instruction_cycle();
    }

}