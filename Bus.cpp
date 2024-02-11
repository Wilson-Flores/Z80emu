#include "Bus.hpp"


Bus::Bus() {
	for (uint8_t& i : ram) {
		i = 0x00;
	}

    for (uint8_t& i : rom) {
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


void Bus::rom_reset() {
	for (uint8_t& i : rom) {
		i = 0x00;
	}
	std::cout << "Memory Cleared!\n";
	cpu.accumulator = 0x00;
	cpu.B_register = 0x00;
	cpu.C_register = 0x00;
	cpu.D_register = 0x00;
	cpu.E_register = 0x00;
	cpu.H_register = 0x00;
	cpu.L_register = 0x00;
	cpu.flag_register = 0x00;


	// Alternate Registers
	cpu.alt_accumulator = 0x00;
	cpu.alt_B_register = 0x00;
	cpu.alt_C_register = 0x00;
	cpu.alt_D_register = 0x00;
	cpu.alt_E_register = 0x00;
	cpu.alt_H_register = 0x00;
	cpu.alt_L_register = 0x00;
	cpu.alt_flag_register = 0x00;

	// Index Registers
	cpu.index_register_x = 0x0000;
	cpu.index_register_y = 0x0000;

	// Other Registers
	cpu.interrupt_vector_register = 0x00;
	cpu.memory_refresh_register = 0x00;
	cpu.stack_pointer = 0x0000;
	cpu.program_counter = 0x0000;

	// Interrupts
	cpu.interrupt_enable_flip_flop_1 = false;
	cpu.interrupt_enable_flip_flop_2 = false;
}