#include "Bus.hpp"


Bus::Bus() {
	for (uint8_t& i : ram) {
		i = 0x00;
	}

	cpu.connect_bus(this);
}

void Bus::write(uint16_t address, uint8_t data) {
	if (address >= 0x0000 && address <= 0xFFFF) {
		ram[address] = data;
	}
}

uint8_t Bus::read(uint16_t address) {
	if (address >= 0x0000 && address <= 0xFFFF) {
		return ram[address];
	}

	return 0x00;
}