#include "Test.hpp"



constexpr int number_of_instructions[] = {7, 56, 20, 4, 50, 3, 23, 2, 6};

void LD_register_immediate_test(Bus& test) {
	// LD r,n: loading the 19h into each register A,B,C,D,E,H,L
	std::vector<uint8_t> memory = {
		0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16,
		0x1C, 0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F };

	// clear RAM
	test.reset();

	// load LD r,n test instructions into ram
	for (int i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}


	for (int i = 0; i < number_of_instructions[0]; i++) {
		test.cpu.instruction_cycle();
	}

}


void LD_register_register_test(Bus& test) {
	std::vector<uint8_t> memory = {
	0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16,
	0x1C, 0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F,
	0x7F, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D,
	0x47, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45,
	0x4F, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D,
	0x57, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
	0x5F, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D,
	0x67, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65,
	0x6F, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D };

	// clear RAM
	test.reset();

	for (int i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < number_of_instructions[1]; i++) {
 		test.cpu.instruction_cycle();
	}
}


void LD_register_register_indirect_test(Bus& test) {
	std::vector<uint8_t> memory = {
		0x3E, 0x19, 0x3E, 0x00, 0x26, 0x00, 0x2E, 0x01,
		0x7E, 0x46, 0x4E, 0x56, 0x5E, 0x66, 0x26, 0x00,
		0x6E, 0x06, 0x00, 0x0E, 0x01, 0x16, 0x00, 0x1E,
		0x01, 0x3E, 0x00, 0x0A, 0x3E, 0x00, 0x1A
	};

	// clear RAM
	test.reset();


	for (int i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < number_of_instructions[2]; i++) {
		test.cpu.instruction_cycle();
	}
}



void LD_register_implied_test(Bus& test) {
	std::vector<uint8_t> memory = { 0x3E, 0x19, 0xED, 0x57, 0x3E, 0x19, 0xED, 0x5F };

	// clear RAM
	test.reset();


	for (int i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < number_of_instructions[3]; i++) {
		test.cpu.instruction_cycle();
	}
}


void LD_register_indexed_test(Bus& test) {
	std::vector<uint8_t> memory = {
	0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16, 0x1C, 0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F, 0x3E, 0x00,
	0x06, 0x00, 0x0E, 0x00, 0x16, 0x00, 0x1E, 0x00, 0x26, 0x00, 0x2E, 0x00, 0xDD, 0x7E, 0x01, 0xDD,
	0x46, 0x03, 0xDD, 0x4E, 0x05, 0xDD, 0x56, 0x07, 0xDD, 0x5E, 0x09, 0xDD, 0x66, 0x0B, 0xDD, 0x6E,
	0x0D, 0x3E, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x16, 0x00, 0x1E, 0x00, 0x26, 0x00, 0x2E, 0x00, 0xFD,
	0x7E, 0x01, 0xFD, 0x46, 0x03, 0xFD, 0x4E, 0x05, 0xFD, 0x56, 0x07, 0xFD, 0x5E, 0x09, 0xFD, 0x66,
	0x0B, 0xFD, 0x6E, 0x0D, 0x3E, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x16, 0x00, 0x1E, 0x00, 0x26, 0x00,
	0x2E, 0x00, 0xDD, 0x21, 0x00, 0x0E, 0xDD, 0x7E, 0xFF, 0xDD, 0x46, 0xFD, 0xDD, 0x4E, 0xFB, 0xDD,
	0x56, 0xF9, 0xDD, 0x5E, 0xF7, 0xDD, 0x66, 0xF5, 0xDD, 0x6E, 0xF3
	};

	test.reset();

	for (int i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < number_of_instructions[4]; i++) {
		test.cpu.instruction_cycle();
	}
}


void LD_register_extended_test(Bus& test) {
	std::vector<uint8_t> memory = {
		0x3E, 0x19, 0x3E, 0x00, 0x3A, 0x00, 0x01 
	};

	test.reset();

	for (int i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < number_of_instructions[5]; i++) {
		test.cpu.instruction_cycle();
	}
}


void LD_register_indirect_immediate(Bus& test) {
	std::vector<uint8_t> memory = {
	0x26, 0x00, 0x2E, 0x06, 0x36, 0x19
	};

	test.reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

	for (int i = 0; i < number_of_instructions[5]; i++) {
		test.cpu.instruction_cycle();
	}
}


void LD_register_indirect_register(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16, 0x1C, 0x1E, 0x1D, 0x26, 0x00, 0x2E, 0x1F, 0x77, 0x70,
            0x71, 0x72, 0x73, 0x74, 0x75, 0x06, 0x00, 0x0E, 0x20, 0x16, 0x00, 0x1E, 0x21, 0x02, 0x12
    };

    test.reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < number_of_instructions[2]; i++) {
        test.cpu.instruction_cycle();
    }
}


void LD_indexed_immediate_test(Bus& test){
    std::vector<uint8_t> memory = {
            0xDD, 0x36, 0x0C, 0x19, 0xFD, 0x21, 0x00, 0x21, 0xFD, 0x36, 0xEC, 0x1A
    };

    test.reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < number_of_instructions[5]; i++) {
        test.cpu.instruction_cycle();
    }

}

void LD_indexed_register_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16, 0x1C, 0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F,
            0xDD, 0x77, 0x40, 0xDD, 0x70, 0x40, 0xDD, 0x71, 0x40, 0xDD, 0x72, 0x40, 0xDD, 0x73, 0x40,
            0xDD, 0x74, 0x40, 0xDD, 0x75, 0x40, 0xFD, 0x21, 0x00, 0x21, 0xFD, 0x21, 0x00, 0x46, 0xFD,
            0x77, 0xFA, 0xFD, 0x70, 0xFA, 0xFD, 0x71, 0xFA, 0xFD, 0x72, 0xFA, 0xFD, 0x73, 0xFA, 0xFD,
            0x74, 0xFA, 0xFD, 0x75, 0xFA
    };

    test.reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < number_of_instructions[6]; i++) {
        test.cpu.instruction_cycle();
    }
}


void LD_extended_register_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0x32, 0x00, 0x05
    };

    test.reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < number_of_instructions[7]; i++) {
        test.cpu.instruction_cycle();
    }
}


void LD_implied_register_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x3E, 0x19, 0xED, 0x47, 0xED, 0x4F
    };

    test.reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < number_of_instructions[5]; i++) {
        test.cpu.instruction_cycle();
    }
}


void LD_register_immediate_extended_test(Bus& test){
    std::vector<uint8_t> memory = {
            0x01, 0x19, 0x1A, 0x11, 0x1B, 0x1C, 0x21, 0x1D, 0x1E, 0x31, 0x1F, 0x20,
            0xDD, 0x21, 0x21, 0x22, 0xFD, 0x21, 0x23, 0x24
    };

    test.reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < number_of_instructions[8]; i++) {
        test.cpu.instruction_cycle();
    }
}


void LD_register_extended_16_bit_test(Bus& test){
    std::vector<uint8_t> memory = {
            0xED, 0x4B, 0x00, 0x1B, 0xED, 0x5B, 0x00, 0x1D,
            0xED, 0x6B, 0x00, 0x1F, 0xED, 0x7B, 0x00, 0x21,
            0xDD, 0x2A, 0x00, 0x23, 0xFD, 0x2A, 0x00, 0x25,
            0x2A, 0x00, 0x27, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
            0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
            0x26
    };

    test.reset();

    for (int i = 0; i < memory.size(); i++) {
        test.ram[i] = memory[i];
        std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
                  std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
    }

    for (int i = 0; i < number_of_instructions[0]; i++) {
        test.cpu.instruction_cycle();
    }
}
