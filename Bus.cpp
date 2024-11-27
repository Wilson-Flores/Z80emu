#include "Bus.hpp"


Bus::Bus() {
    for (uint8_t& i : rom_) {
        i = 0x00;
    }

	cpu_.connect_bus(this);
}


void Bus::rom_write(uint16_t address, uint8_t data) {
    rom_[address] = data;
}


uint8_t Bus::rom_read(uint16_t address) const {
    return rom_[address];
}


void Bus::rom_reset() {
	for (uint8_t& i : rom_) {
		i = 0x00;
	}

    cpu_.reset();
}