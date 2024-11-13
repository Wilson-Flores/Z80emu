#include "Bus.hpp"


Bus::Bus() {
    uint8_t value = 0;
   //TODO: add a real way to load ram, create ram class.
    for(uint8_t& i : ram){
        i = value;
        value++;
    }


    for (uint8_t& i : rom) {
        i = 0x00;
    }

	cpu.connect_bus(this);
}


void Bus::ram_write(uint16_t address, uint8_t data) {
    ram[address] = data;
}


uint8_t Bus::ram_read(uint16_t address) {
    return ram[address];
}


void Bus::rom_write(uint16_t address, uint8_t data) {
    rom[address] = data;
}


uint8_t Bus::rom_read(uint16_t address) {
    return rom[address];
}


void Bus::rom_reset() {
	for (uint8_t& i : rom) {
		i = 0x00;
	}

    cpu.reset();

}