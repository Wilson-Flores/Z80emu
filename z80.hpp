#ifndef z80_hpp
#define z80_hpp

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>


class Bus;


class z80cpu {
public:
	z80cpu();


	// connect to Bus
	void connect_bus(Bus* n) { bus = n; }

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

	// Other Registers
	uint8_t interrupt_vector_register = 0x00;
	uint8_t memory_refresh_register = 0x00;
	void memory_refresh_counter();

	uint16_t stack_pointer = 0x0000;
	uint16_t program_counter = 0x0000;

	// Interrupts
	bool interrupt_enable_flip_flop_1 = false;
	bool interrupt_enable_flip_flop_2 = false;
	void software_maskable_interrupt(); // INT
	void non_maskable_interrupt(); // NMI



	// 8-bit Instructions
	// LD Instructions
	void LD_register_immediate();                 // [LD r, n]
	void LD_register_register();                  // [LD r, r']
	void LD_register_register_indirect();         // [LD r, (HL)], [LD A, (BC)], [LD A, (DE)]
	void LD_register_implied();                   // [LD A, R], [LD A, I]
	void LD_register_indexed_ix();                // [LD r, (IX+d)]
	void LD_register_indexed_iy();                // [LD r, (IY+d)]
	void LD_register_extended();				  // [LD A, (nn)]
	void LD_register_indirect_immediate();		  // [LD (HL), n]

	
	// 16-bit Instructions
	// LD Instructions
	void LD_register_immediate_extended_ix();     // [LD IX, nn]
	void LD_register_immediate_extended_iy();     // [LD IY, nn]


	void instruction_cycle();

	uint16_t address_absolute = 0x0000;
	uint16_t address_relative = 0x0000;
	uint8_t opcode = 0x00;
	uint8_t t_state_cycles = 0;

private:
	Bus* bus = nullptr;


	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t data);

	uint8_t get_flag(FLAGSZ80 flag);
	void set_flag(FLAGSZ80 flag, bool setFlag);

	struct INSTRUCTION {
		std::string opcode;
		void(z80cpu::* instruction)() = nullptr;
	};


	//Function tables
	void bit_instructions();
	void ix_instructions();
	void ix_bit_instructions();
	void misc_instructions();
	void iy_instructions();
	void iy_bit_instructions();


	std::vector<INSTRUCTION> main_instruction_table;
	std::vector<INSTRUCTION> bit_instruction_table;			// opcode: CB
	std::vector<INSTRUCTION> ix_instruction_table;			// opcode: DD
	std::vector<INSTRUCTION> ix_bit_instruction_table;		// opcode: DD CB
	std::vector<INSTRUCTION> misc_instruction_table;		// opcode: ED
	std::vector<INSTRUCTION> iy_instruction_table;			// opcode: FD
	std::vector<INSTRUCTION> iy_bit_instruction_table;		// opcode: FD CB


	// each register has a correlating bit value that is used to determine what register to use in the instruction.
	std::vector<uint8_t*> register_table;
};

#endif // !z80_hpp
