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
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }


    for(uint16_t byte_counter = 0; byte_counter < 4; byte_counter++){
        test.cpu.instruction_cycle();
    }
}
