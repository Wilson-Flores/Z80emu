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
    // We will loop through ( 0x00 - 0xFF) checking the DAA results for each value.

    std::cout << "Hex Values:\tDAA Values:\tCF:\tHF:\tAdded Value:\n";

    for(uint16_t value = 0x00; value <= 0xFF; value++){
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(value) << '\t';
        std::vector<uint8_t> memory = { 0x3E, static_cast<uint8_t>(value), 0x27 };

        // write memory vector to rom
        for (int i = 0; i < memory.size(); i++) {
            test.rom_write(i,memory[i]);
        }

        for(uint8_t byte_counter = 0; byte_counter < 2; byte_counter++){
            test.cpu.instruction_cycle();
        }

        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.flag_register & 0x01)  << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>((test.cpu.flag_register & 0x10) >> 4) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator - value) << '\n';
        test.cpu.program_counter = 0x00;
        test.cpu.flag_register = 0x00;
        test.cpu.accumulator = 0x00;
    }
}


void daa_test_2(Bus& test){
    // We will loop through ( 0x00 - 0xFF) checking the DAA results for each value.

    std::cout << "Hex Values:\tDAA Values:\tCF:\tHF:\tAdded Value:\n";

    for(uint16_t value = 0x00; value <= 0xFF; value++){
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(value) << '\t';
        std::vector<uint8_t> memory = { 0x3E, 0x0F, 0xC6, 0x01, 0x3E, static_cast<uint8_t>(value), 0x27 };

        // write memory vector to rom
        for (int i = 0; i < memory.size(); i++) {
            test.rom_write(i,memory[i]);
        }

        for(uint8_t byte_counter = 0; byte_counter < 4; byte_counter++){
            test.cpu.instruction_cycle();
        }

        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.flag_register & 0x01)  << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>((test.cpu.flag_register & 0x10) >> 4) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator - value) << '\n';
        test.cpu.program_counter = 0x00;
        test.cpu.flag_register = 0x00;
        test.cpu.accumulator = 0x00;
    }
}


void daa_test_3(Bus& test){
    // We will loop through ( 0x00 - 0xFF) checking the DAA results for each value.

    std::cout << "Hex Values:\tDAA Values:\tCF:\tHF:\tAdded Value:\n";

    for(uint16_t value = 0x00; value <= 0xFF; value++){
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(value) << '\t';
        std::vector<uint8_t> memory = { 0x3E, 0xF0, 0xC6, 0x10, 0x3E, static_cast<uint8_t>(value), 0x27 };

        // write memory vector to rom
        for (int i = 0; i < memory.size(); i++) {
            test.rom_write(i,memory[i]);
        }

        for(uint8_t byte_counter = 0; byte_counter < 4; byte_counter++){
            test.cpu.instruction_cycle();
        }

        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.flag_register & 0x01)  << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>((test.cpu.flag_register & 0x10) >> 4) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator - value) << '\n';
        test.cpu.program_counter = 0x00;
        test.cpu.flag_register = 0x00;
        test.cpu.accumulator = 0x00;
    }
}


void daa_test_4(Bus& test){
    // We will loop through ( 0x00 - 0xFF) checking the DAA results for each value.

    std::cout << "Hex Values:\tDAA Values:\tCF:\tHF:\tAdded Value:\n";

    for(uint16_t value = 0x00; value <= 0xFF; value++){
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(value) << '\t';
        std::vector<uint8_t> memory = { 0x3E, 0xFF, 0xC6, 0x01, 0x3E, static_cast<uint8_t>(value), 0x27 };

        // write memory vector to rom
        for (int i = 0; i < memory.size(); i++) {
            test.rom_write(i,memory[i]);
        }

        for(uint8_t byte_counter = 0; byte_counter < 4; byte_counter++){
            test.cpu.instruction_cycle();
        }

        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.flag_register & 0x01)  << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>((test.cpu.flag_register & 0x10) >> 4) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator - value) << '\n';
        test.cpu.program_counter = 0x00;
        test.cpu.flag_register = 0x00;
        test.cpu.accumulator = 0x00;
    }
}


void daa_test_5(Bus& test){
    // We will loop through ( 0x00 - 0xFF) checking the DAA results for each value.

    std::cout << "Hex Values:\tDAA Values:\tCF:\tHF:\tAdded Value:\n";

    for(uint16_t value = 0x00; value <= 0xFF; value++){
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(value) << '\t';
        std::vector<uint8_t> memory = { 0x3E, 0x02, 0xD6, 0x01, 0x3E, static_cast<uint8_t>(value), 0x27 };

        // write memory vector to rom
        for (int i = 0; i < memory.size(); i++) {
            test.rom_write(i,memory[i]);
        }

        for(uint8_t byte_counter = 0; byte_counter < 4; byte_counter++){
            test.cpu.instruction_cycle();
        }

        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.flag_register & 0x01)  << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>((test.cpu.flag_register & 0x10) >> 4) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator - value) << '\n';
        test.cpu.program_counter = 0x00;
        test.cpu.flag_register = 0x00;
        test.cpu.accumulator = 0x00;
    }
}


void daa_test_6(Bus& test){
    // We will loop through ( 0x00 - 0xFF) checking the DAA results for each value.

    std::cout << "Hex Values:\tDAA Values:\tCF:\tHF:\tAdded Value:\n";

    for(uint16_t value = 0x00; value <= 0xFF; value++){
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(value) << '\t';
        std::vector<uint8_t> memory = { 0x3E, 0x10, 0xD6, 0x01, 0x3E, static_cast<uint8_t>(value), 0x27 };

        // write memory vector to rom
        for (int i = 0; i < memory.size(); i++) {
            test.rom_write(i,memory[i]);
        }

        for(uint8_t byte_counter = 0; byte_counter < 4; byte_counter++){
            test.cpu.instruction_cycle();
        }

        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.flag_register & 0x01)  << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>((test.cpu.flag_register & 0x10) >> 4) << '\t';
        std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(test.cpu.accumulator - value) << '\n';
        test.cpu.program_counter = 0x00;
        test.cpu.flag_register = 0x00;
        test.cpu.accumulator = 0x00;
    }
}


void daa_test_7(Bus& test){}


void daa_test_8(Bus& test){}
