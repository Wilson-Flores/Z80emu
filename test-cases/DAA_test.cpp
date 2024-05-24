#include "DAA_test.hpp"


void daa_test_choice(Bus& test){
    int test_choice;
    std::cout << "Enter a number: ";
    std::cin >> test_choice;

    switch (test_choice) {
        case 1:
            daa_test_1(test);
            break;
        case 2:
            daa_test_2(test);
            break;
        case 3:
            daa_test_3(test);
            break;
        case 4:
            daa_test_4(test);
            break;
        case 5:
            daa_test_5(test);
            break;
        case 6:
            daa_test_6(test);
            break;
        case 7:
            daa_test_7(test);
            break;
        case 8:
            daa_test_8(test);
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}


void daa_test_1(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x99, 0x27, 0x3E, 0x8F, 0x27, 0xED, 0x5F,
            0x3E, 0xF9, 0x27, 0x3F, 0xED, 0x5F, 0x3E, 0xFF,
            0x27
    };

    for (int i = 0; i < memory.size(); i++) {
        test.rom_write(i,memory[i]);
        std::cout << "rom[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.rom[i]) << '\n';
    }

    for(uint16_t byte_counter = 0; byte_counter < 11; byte_counter++){
        test.cpu.instruction_cycle();
    }
}


void daa_test_2(Bus& test){}


void daa_test_3(Bus& test){}


void daa_test_4(Bus& test){}


void daa_test_5(Bus& test){}


void daa_test_6(Bus& test){}


void daa_test_7(Bus& test){}


void daa_test_8(Bus& test){}
