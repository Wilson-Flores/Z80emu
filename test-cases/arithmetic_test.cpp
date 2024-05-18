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
        case 5:
            and_test(test);
            break;
        case 6:
            xor_test(test);
            break;
        case 7:
            or_test(test);
            break;
        case 8:
            cp_test(test);
            break;
        case 9:
            inc_test(test);
            break;
        case 10:
            dec_test(test);
            break;
        case 11:
            add_16_test(test);
            break;
        case 12:
            ccf_test(test);
            break;
        case 13:
            adc_16_test(test);
            break;
        case 14:
            sbc_16_test(test);
            break;
        case 15:
            inc_dec_16_test(test);
            break;
        case 16:
            neg_test(test);
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


    for(uint16_t byte_counter = 0; byte_counter < 22; byte_counter++){
        test.cpu.instruction_cycle();
    }
}

void and_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0xFF, 0x06, 0x7F, 0x0E, 0x3F, 0x16, 0x1F,
            0x1E, 0x0F, 0x26, 0x07, 0x2E, 0x03, 0xA7, 0xA0,
            0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0x21, 0x00, 0x00,
            0x3E, 0xFF, 0x32, 0x00, 0x00, 0xA6, 0xDD, 0x21,
            0x22, 0x00, 0xFD, 0x21, 0x24, 0x00, 0xDD, 0xA6,
            0xDE, 0xFD, 0xA6, 0xDC, 0xE6, 0x00
    };

    test.rom_reset();

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 23; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void xor_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0xAF, 0x3E, 0x19, 0x06, 0x8A, 0xA8,
            0x3E, 0x19, 0x0E, 0x18, 0xA9, 0x3E, 0x19, 0x16,
            0x1C, 0xAA, 0x3E, 0x19, 0x1E, 0x1D, 0xAB, 0x3E,
            0x19, 0x26, 0x1E, 0xAC, 0x3E, 0x19, 0x2E, 0x1F,
            0xAD, 0x3E, 0x19, 0x21, 0x19, 0x00, 0xAE, 0x3E,
            0x19, 0xDD, 0x21, 0xAA, 0x00, 0xDD, 0xAE, 0xEF,
            0x3E, 0x19, 0xFD, 0x21, 0xAA, 0x00, 0xFD, 0xAE,
            0xEF, 0x3E, 0x19, 0xEE, 0x19
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 31; byte_counter++){
        test.cpu.instruction_cycle();
    }
}

void or_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0xB7, 0x3E, 0x19, 0x06, 0x8A, 0xB0,
            0x3E, 0x19, 0x0E, 0x18, 0xB1, 0x3E, 0x19, 0x16,
            0x1C, 0xB2, 0x3E, 0x19, 0x1E, 0x1D, 0xB3, 0x3E,
            0x19, 0x26, 0x1E, 0xB4, 0x3E, 0x19, 0x2E, 0x1F,
            0xB5, 0x3E, 0x19, 0x21, 0x19, 0x00, 0xB6, 0x3E,
            0x19, 0xDD, 0x21, 0xAA, 0x00, 0xDD, 0xB6, 0xEF,
            0x3E, 0x19, 0xFD, 0x21, 0xAA, 0x00, 0xFD, 0xB6,
            0xEF, 0x3E, 0x00, 0xF6, 0x00
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 31; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void cp_test(Bus& test) {
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0xBF, 0x3E, 0x19, 0x06, 0x8A, 0xB8,
            0x3E, 0x19, 0x0E, 0x18, 0xB9, 0x3E, 0x19, 0x16,
            0x1C, 0xBA, 0x3E, 0x19, 0x1E, 0x1D, 0xBB, 0x3E,
            0x19, 0x26, 0x1E, 0xBC, 0x3E, 0x19, 0x2E, 0x1F,
            0xBD, 0x3E, 0x19, 0x21, 0x19, 0x00, 0xBE, 0x3E,
            0x19, 0xDD, 0x21, 0xAA, 0x00, 0xDD, 0xBE, 0xEF,
            0x3E, 0x19, 0xFD, 0x21, 0xAA, 0x00, 0xFD, 0xBE,
            0xEF, 0x3E, 0x00, 0xFE, 0x00
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 31; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void inc_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0xFF, 0x06, 0x7F, 0x0E, 0x18, 0x16, 0x1C,
            0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F, 0x3C, 0x04,
            0x0C, 0x14, 0x1C, 0x24, 0x2C, 0x21, 0x19, 0x00,
            0xDD, 0x21, 0xAA, 0x00, 0xFD, 0x21, 0xAA, 0x00,
            0x34, 0xDD, 0x34, 0xEF, 0xFD, 0x34, 0xEF
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 20; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void dec_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x00, 0x06, 0x80, 0x0E, 0x18, 0x16, 0x1C,
            0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x20, 0x3D, 0x05,
            0x0D, 0x15, 0x1D, 0x25, 0x2D, 0x21, 0x19, 0x00,
            0xDD, 0x21, 0xAA, 0x00, 0xFD, 0x21, 0xAA, 0x00,
            0x35, 0xDD, 0x35, 0xEF, 0xFD, 0x35, 0xEF
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 20; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void add_16_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x01, 0x01, 0x00, 0x11, 0xFF,
            0xFF, 0x21, 0xFF, 0xFF, 0x31, 0x20, 0x1F, 0x09,
            0x19, 0x29, 0x39, 0xDD, 0x21, 0x01, 0x00, 0xFD,
            0x21, 0x01, 0x00, 0xDD, 0x09, 0xDD, 0x19, 0xDD,
            0x39, 0xDD, 0x29, 0xFD, 0x09, 0xFD, 0x19, 0xFD,
            0x39, 0xFD, 0x29
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 18; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void ccf_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3F, 0x3F, 0x3F, 0x3E, 0xFF, 0x87, 0x3F
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 6; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void adc_16_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x01, 0x00, 0x80, 0xED, 0x4A, 0x11, 0xFF, 0xFF,
            0xED, 0x5A, 0xED, 0x6A, 0x31, 0x01, 0x00, 0xED,
            0x7A
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 7; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void sbc_16_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x01, 0x00, 0x80, 0xED, 0x42, 0x21, 0x00, 0x00,
            0x11, 0x00, 0x80, 0xED, 0x52, 0x21, 0x00, 0x00,
            0x31, 0xFF, 0xFF, 0xED, 0x72
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 8; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void inc_dec_16_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x21, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x11, 0xFF,
            0xFF, 0x31, 0xFF, 0xFF, 0xDD, 0x21, 0xFF, 0xFF,
            0xFD, 0x21, 0xFF, 0xFF, 0x03, 0x13, 0x23, 0x33,
            0xDD, 0x23, 0xFD, 0x23, 0x0B, 0x1B, 0x2B, 0x3B,
            0xDD, 0x2B, 0xFD, 0x2B
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }

    for(uint16_t byte_counter = 0; byte_counter < 18; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void neg_test(Bus& test){
    std::vector<uint8_t> memory = {
            0xED, 0x44, 0x3E, 0xFF, 0xED, 0x44, 0x3E, 0x80, 0xED, 0x44
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }

    for(uint16_t byte_counter = 0; byte_counter < 5; byte_counter++){
        test.cpu.instruction_cycle();
    }
}

