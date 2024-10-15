#ifndef z80_hpp
#define z80_hpp

#include <cstdint>
#include <string>
#include <vector>
#include <iomanip>

constexpr uint8_t BIT_MASK_1 = 0x38;      // 0011 1000 binary value
constexpr uint8_t BIT_MASK_2 = 0x07;      // 0000 0111 binary value
constexpr uint8_t BIT_MASK_3 = 0x30;      // 0011 0000 binary value
constexpr uint8_t BIT_MASK_4 = 0x18;      // 0001 1000 binary value
constexpr uint8_t LOW_BYTE_MASK = 0xFF;   // 1111 1111 binary value

//For Set instructions, we use these bit masks with OR operation to set the desired bit in the value
constexpr uint8_t SET_BIT_MASKS[8] = {
	0x01,    //0b00000001
	0x02,    //0b00000010
	0x04,    //0b00000100
	0x08,    //0b00001000
	0x10,    //0b00010000
	0x20,    //0b00100000
	0x40,    //0b01000000
	0x80     //0b10000000
	};

//For Reset instructions, we use these bit masks with AND operation to set the desired bit in the value
constexpr uint8_t RES_BIT_MASKS[8] = {
	0xFE,    //0b11111110
	0xFD,    //0b11111101
	0xFB,    //0b11111011
	0xF7,    //0b11110111
	0xEF,    //0b11101111
	0xDF,    //0b11011111
	0xBF,    //0b10111111
	0x7F     //0b01111111
	};

// lookup table for the parity of any value from 0-255. Used for P/V flag
// 0: Odd, 1: Even
constexpr uint8_t PARITY_TABLE[256] = {
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
    1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1
};


class Bus;


class z80cpu {
public:
	z80cpu();


	// connect to Bus
	void connect_bus(Bus* n) { bus = n; }

	// Status Register
	enum FLAGSZ80 {
		CARRY_FLAG = (1 << 0),                    // C
		ADD_SUB_FLAG = (1 << 1),                  // N
		PARITY_OVERFLOW_FLAG = (1 << 2),          // P/V
		X_FLAG = (1 << 3),                        // X
		HALF_CARRY_FLAG = (1 << 4),               // H
		Y_FLAG = (1 << 5),                        // Y
		ZERO_FLAG = (1 << 6),                     // Z
		SIGN_FLAG = (1 << 7)                      // S
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
    uint16_t WZ_register = 0x0000;

	void memory_refresh_counter();

	uint16_t stack_pointer = 0x0000;
	uint16_t program_counter = 0x0000;

	// Interrupts
	bool interrupt_enable_flip_flop_1 = false;
	bool interrupt_enable_flip_flop_2 = false;
	void software_maskable_interrupt(); // INT
	void non_maskable_interrupt(); // NMI


	void instruction_cycle();

	uint8_t opcode = 0x00;
	uint8_t t_state_cycles = 0;

    // variables that temporarily store values while executing certain instructions
    int8_t displacement = 0x00;

    // 8-bit temp values
    uint8_t data_8 = 0;
    uint8_t result_8 = 0;

    // 16-bit temp values
    uint16_t data_16 = 0;
    uint16_t result_16 = 0;

    // temp memory address value
    uint16_t memory_address = 0x0000;

    // LDIR/LDDR WZ register Flag
    // This flag will indicate that the instruction loop has started.
    // we need to grab BC's value to determine what value will be stored at WZ register.
    // This only occurs at the start of the instruction, so we cant have it overwriting while it loops.
    bool WZ_register_flag = false;


private:
	Bus* bus = nullptr;


	uint8_t rom_read(uint16_t address);

    uint8_t ram_read(uint16_t address);
    void ram_write(uint16_t address, uint8_t data);


	uint8_t get_flag(FLAGSZ80 flag) const;
	void set_flag(FLAGSZ80 flag, bool setFlag);


	//Function tables
	void bit_instructions();
	void ix_instructions();
	void ix_bit_instructions();
	void misc_instructions();
	void iy_instructions();
	void iy_bit_instructions();

	//Insturction tables
	struct INSTRUCTION {
		std::string opcode;
		void(*instruction)() = nullptr;
	};

	std::vector<INSTRUCTION> main_instruction_table;
	std::vector<INSTRUCTION> bit_instruction_table;			// opcode: CB
	std::vector<INSTRUCTION> ix_instruction_table;			// opcode: DD
	std::vector<INSTRUCTION> ix_bit_instruction_table;		// opcode: DD CB
	std::vector<INSTRUCTION> misc_instruction_table;		// opcode: ED
	std::vector<INSTRUCTION> iy_instruction_table;			// opcode: FD
	std::vector<INSTRUCTION> iy_bit_instruction_table;		// opcode: FD CB


	// each register has a correlating bit value that is used to determine what register to use in the instruction.
    std::vector<uint8_t*> register_table;
    std::vector<uint8_t*> alt_register_table;


    // each register pair has a correlating bit value
    struct REGISTER_PAIR{
        uint8_t* high_byte_register;
        uint8_t* low_byte_register;
    };

	std::vector<REGISTER_PAIR> register_pair_table_qq;
    std::vector<REGISTER_PAIR> register_pair_table_ss;
    std::vector<REGISTER_PAIR> register_pair_table_pp;
    std::vector<REGISTER_PAIR> register_pair_table_rr;

};

#endif // !z80_hpp
