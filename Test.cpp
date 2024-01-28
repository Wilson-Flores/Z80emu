#include "Test.hpp"


void LD_register_immediate_test(Bus& test) {
	// LD r,n: loading the 19h into each register A,B,C,D,E,H,L
	std::vector<uint8_t> memory = {
		0x3E, 0x19, 0x06, 0x1A, 0x0E, 0x1B, 0x16,
		0x1C, 0x1E, 0x1D, 0x26, 0x1E, 0x2E, 0x1F };

	// clear RAM
	test.reset();

	// load LD r,n test instructions into ram
	for (uint16_t i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}


	for (int i = 0; i < 7; i++) {
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

	for (uint16_t i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < 56; i++) {
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


	for (uint16_t i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < 20; i++) {
		test.cpu.instruction_cycle();
	}
}



void LD_register_implied_test(Bus& test) {
	std::vector<uint8_t> memory = { 0x3E, 0x19, 0xED, 0x57, 0x3E, 0x19, 0xED, 0x5F };

	// clear RAM
	test.reset();


	for (uint16_t i = 0; i < memory.size(); i++) {
		test.ram[i] = memory[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < 4; i++) {
		test.cpu.instruction_cycle();
	}
}


