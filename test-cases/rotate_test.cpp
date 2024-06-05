#include <unordered_map>
#include "rotate_test.hpp"


void rotate_test_choice(Bus& test){
    int test_choice;
    std::cout << "Enter a number: ";
    std::cin >> test_choice;

    switch (test_choice) {
        case 1:
            RLCA_test(test);
            break;
        case 2:
            RLC_test(test);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}


void RLCA_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x88, 0x07, 0x3E, 0x6B, 0x07
    };

    test.rom_reset();

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
    }


    for(uint16_t byte_counter = 0; byte_counter < 4; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void RLC_test(Bus& test){
    std::vector<std::pair<uint8_t, uint8_t>> registers =
            {{0x3E, 0x07}, // A
             {0x06, 0x00}, // B
             {0x0E, 0x01}, // C
             {0x16, 0x02}, // D
             {0x1E, 0x03}, // E
             {0x26, 0x04}, // H
             {0x2E, 0x05}  // L
             };

    for (const std::pair<const uint8_t, uint8_t>& pair : registers) {
        std::vector<uint8_t> memory = {pair.first, 0x88, 0xCB, pair.second, pair.first, 0x6B, 0xCB, pair.second};

        test.rom_reset();

        for (int i = 0; i < memory.size(); i++) {
            test.rom_write(i,memory[i]);
        }

        for(uint16_t byte_counter = 0; byte_counter < 4; byte_counter++){
            test.cpu.instruction_cycle();
            std::cout << "Flag: 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase
            << static_cast<int>(test.cpu.flag_register) << '\n';
        }
    }
}
