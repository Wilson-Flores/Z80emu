#include "arithmetic_test.hpp"


void arithmetic_test_choice(Bus& test) {
    int test_choice;
    std::cout << "Enter a number: ";
    std::cin >> test_choice;

    switch (test_choice) {
        case 1:
            add_test(test);
            break;
        case 2:
            adc_test(test);
            break;
        case 3:
            sub_test(test);
            break;
        case 4:
            sbc_test(test);
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}

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


void sub_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16, 0x1C,
            0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F, 0x97, 0x90,
            0x91, 0x92, 0x93, 0x94, 0x95, 0x21, 0x00, 0x00,
            0x32, 0x00, 0x00, 0x96, 0xDD, 0x21, 0x22, 0x00,
            0xFD, 0x21, 0x24, 0x00, 0xDD, 0x96, 0xDE, 0xFD,
            0x96, 0xDC, 0xD6, 0x56
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


void sbc_test(Bus& test) {
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16, 0x1C,
            0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F, 0x9F, 0x98,
            0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x21, 0x00, 0x00,
            0x32, 0x00, 0x00, 0x9E, 0xDD, 0x21, 0x22, 0x00,
            0xFD, 0x21, 0x24, 0x00, 0xDD, 0x9E, 0xDE, 0xFD,
            0x9E, 0xDC, 0xDE, 0x57
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