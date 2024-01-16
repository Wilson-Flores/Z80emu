#ifndef z80_hpp
#define z80_hpp

#include <cstdint>


class z80cpu {
public:
	z80cpu();
	~z80cpu();


	// Status Register
	enum FLAGSZ80 {
		CARRY_FLAG = (1 << 0),
		ADD_SUB_FLAG = (1 << 1),
		PARITY_OVERFLOW_FLAG = (1 << 2),
		UNUSED1 = (1 << 3),
		HALF_CARRY_FLAG = (1 << 4),
		UNUSED2 = (1 << 5),
		ZERO_FLAG = (1 << 6),
		SIGN_FLAG = (1 << 7)
	};


	// Main Registers
	uint8_t accumulator = 0x00;
	uint8_t B_register = 0x00;
	uint8_t C_register = 0x00;
	uint8_t D_register = 0x00;
	uint8_t E_register = 0x00;
	uint8_t H_register = 0x00;
	uint8_t L_register = 0x00;
	uint8_t flag_register = 0x00;

	// Alternate Registers
	uint8_t alt_accumulator = 0x00;
	uint8_t alt_B_register = 0x00;
	uint8_t alt_C_register = 0x00;
	uint8_t alt_D_register = 0x00;
	uint8_t alt_E_register = 0x00;
	uint8_t alt_H_register = 0x00;
	uint8_t alt_L_register = 0x00;
	uint8_t alt_flag_register = 0x00;

	// Index Registers
	uint16_t index_register_x = 0x0000;
	uint16_t index_register_y = 0x0000;

	uint16_t stack_pointer = 0x0000;
	uint16_t program_counter = 0x0000;


	// Other Registers
	uint8_t interrupt_vector = 0x00;
	uint8_t refresh_counter = 0x00;


	// Addressing Modes
	uint8_t immediate_addressing();
	uint8_t immediate_extended_addressing();
	uint8_t modified_page_zero_addressing();
	uint8_t relative_addressing();
	uint8_t extended_addressing();
	uint8_t indexed_addressing();
	uint8_t register_addressing();
	uint8_t implied_addressing();
	uint8_t register_indirect_addressing();
	uint8_t bit_addressing();



};

#endif // !z80_hpp
