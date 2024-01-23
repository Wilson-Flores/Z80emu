#ifndef z80_hpp
#define z80_hpp

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

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
	uint8_t interrupt_vector = 0x00;
	uint8_t refresh_counter = 0x00;
	uint16_t stack_pointer = 0x0000;
	uint16_t program_counter = 0x0000;


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


	// 8-bit Instructions
	uint8_t ADC();  uint8_t ADD();  uint8_t AND();

	uint8_t BIT();

	uint8_t CALL(); uint8_t CCF();  uint8_t CP();   uint8_t CPD();
	uint8_t CPDR(); uint8_t CPI();  uint8_t CPIR(); uint8_t CPL();
	
	uint8_t DAA();  uint8_t DEC();  uint8_t DI();   uint8_t DJNZ();

	uint8_t EI();   uint8_t EX();   uint8_t EXX();

	uint8_t HALT();

	uint8_t IM0();  uint8_t IM1();  uint8_t IM2();  uint8_t IN();
	uint8_t INC();  uint8_t INI();  uint8_t INIR();

	uint8_t JP();   uint8_t JR();

	uint8_t LD();   uint8_t LDD();  uint8_t LDDR(); uint8_t LDI();  uint8_t LDIR();

	uint8_t NEG();  uint8_t NOP();

	uint8_t OR();   uint8_t OTDR(); uint8_t OUT();  uint8_t OUTD(); uint8_t OUTI();

	uint8_t POP();  uint8_t PUSH();

	uint8_t RES();  uint8_t RET();  uint8_t RETI(); uint8_t RETN(); uint8_t RL();
	uint8_t RLA();  uint8_t RLC();  uint8_t RLCA(); uint8_t RLD();  uint8_t RR();
	uint8_t RRA();  uint8_t RRC();  uint8_t RRCA(); uint8_t RRD();  uint8_t RST();

	uint8_t SBC();  uint8_t SCF();  uint8_t SET();  uint8_t SLA();
	uint8_t SRA();  uint8_t SRL();  uint8_t SUB();

	uint8_t XOR();


	// Catch any "illegal opcodes
	uint8_t XXX();


	void instruction_cycle();

	uint16_t address_absolute = 0x0000;
	uint16_t address_relative = 0x0000;
	uint8_t opcode = 0x00;
	uint8_t t_state_cycles = 0;

private:
	Bus* bus = nullptr;


	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t data);

	uint8_t GetFlag(FLAGSZ80 flag);
	void SetFlag(FLAGSZ80 flag, bool setFlag);

	struct INSTRUCTION {
		std::string name;
		uint8_t(z80cpu::* instruction)(void) = nullptr;
		uint8_t(z80cpu::* addressing_mode1)(void) = nullptr;
		uint8_t(z80cpu::* addressing_mode2)(void) = nullptr;
		uint8_t t_state_cycles = 0;
	};


	std::vector<INSTRUCTION> instruction_table;
};

#endif // !z80_hpp
