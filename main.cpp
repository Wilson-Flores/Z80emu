#include <iostream>
#include "z80.hpp"
#include "Bus.hpp"
#include <iomanip>


void LD_r_n_test(Bus& test) {
	// LD r,n: loading the 19h into each register A,B,C,D,E,H,L
	std::vector<uint8_t> LD_r_n_test = { 0x3E, 0x19,0x06,
0x1A,0x0E,0x1B,0x16,0x1C,0x1E,0x1D,0x26,0x1E,0x2E,0x1F };

	// load LD r,n test instructions into ram
	for (uint16_t i = 0; i < LD_r_n_test.size(); i++) {
		test.ram[i] = LD_r_n_test[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}

	for (int i = 0; i < 7; i++) {
		test.cpu.instruction_cycle();
	}

}


void LD_r_r_test(Bus& test) {
	std::vector<uint8_t> LD_r_r_test = {
	0x7F, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D,
	0x47, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45,
	0x4F, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D,
	0x57, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
	0x5F, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D,
	0x67, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65,
	0x6F, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D };

	for (uint16_t i = 0; i < LD_r_r_test.size(); i++) {
		test.ram[i + 14] = LD_r_r_test[i];
		std::cout << "ram[" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i + 14 << "] : " <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}


}


int main() {
	Bus test;

	LD_r_n_test(test);
	LD_r_r_test(test);


	return 0;
}



