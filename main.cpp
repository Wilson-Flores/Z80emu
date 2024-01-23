#include <iostream>
#include "z80.hpp"
#include "Bus.hpp"
#include <iomanip>


void LD_test() {
	Bus test;

	// LD r,n: loading the 19h into each register A,B,C,D,E,H,L
	std::vector<uint8_t> LD_r_n_test{ 0x3E, 0x19,0x06,
0x19,0x0E,0x19,0x16,0x19,0x1E,0x19,0x26,0x19,0x2E,0x19 };

	// load LD r,n test instructions into ram
	for (uint8_t i = 0; i < LD_r_n_test.size(); i++) {
		test.ram[i] = LD_r_n_test[i];
		std::cout << "ram[" << static_cast<int>(i) << "] : " << std::hex << std::uppercase <<
			std::setw(2) << std::setfill('0') << static_cast<int>(test.ram[i]) << '\n';
	}


}


int main() {
	LD_test();

	return 0;
}



