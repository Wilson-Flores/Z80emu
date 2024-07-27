#ifndef z80_hpp
#define z80_hpp

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

constexpr uint8_t BIT_MASK_1 = 0x38;      // 0011 1000 binary value
constexpr uint8_t BIT_MASK_2 = 0x07;      // 0000 0111 binary value
constexpr uint8_t BIT_MASK_3 = 0x30;      // 0011 0000 binary value
constexpr uint8_t LOW_BYTE_MASK = 0xFF;   // 1111 1111 binary value

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

    // TODO: figure out what instructions actually utilize WZ_register and which will need to have a separate temp value
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

	// 8-bit Instructions
	// LD Instructions
	void LD_register_immediate();                                           // [LD r, n]
	void LD_register_register();                                            // [LD r, r']
	void LD_register_register_indirect();                                   // [LD r, (HL)]
    void LD_register_register_indirect_BC();                                // [LD A, (BC)]
    void LD_register_register_indirect_DE();                                // [LD A, (DE)]
	void LD_register_implied();                                             // [LD A, I], [LD A, R]
	void LD_register_indexed_ix();                                          // [LD r, (IX+d)]
	void LD_register_indexed_iy();                                          // [LD r, (IY+d)]
	void LD_register_extended();                                            // [LD A, (nn)]
	void LD_register_indirect_immediate();                                  // [LD (HL), n]
    void LD_register_indirect_register();                                   // [LD (HL), r], [LD (BC), A], [LD (DE), A]
    void LD_indexed_ix_immediate();                                         // [LD (IX+d), n]
    void LD_indexed_iy_immediate();                                         // [LD (IY+d), n]
    void LD_indexed_ix_register();                                          // [LD (IX+d), r]
    void LD_indexed_iy_register();                                          // [LD (IY+d), r]
    void LD_extended_register();                                            // [LD (nn), A]
    void LD_implied_register();                                             // [LD I, A], [LD R, A]

    // Block Transfer Instructions
    void LDI_register_indirect_register_indirect();                         // [LDI]
    void LDIR_register_indirect_register_indirect();                        // [LDIR]
    void LDD_register_indirect_register_indirect();                         // [LDD]
    void LDDR_register_indirect_register_indirect();                        // [LDDR]

    // Block Search Instructions
    void CPI_register_indirect();                                           // [CPI]
    void CPIR_register_indirect();                                          // [CPIR]
    void CPD_register_indirect();                                           // [CPD]
    void CPDR_register_indirect();                                          // [CPDR]

    // Arithmetic Instructions
    // ADD Instructions
    void ADD_implied_register();                                            // [ADD A, r]
    void ADD_implied_register_indirect();                                   // [ADD A, (HL)]
    void ADD_implied_indexed_ix();                                          // [ADD A, (IX+d)]
    void ADD_implied_indexed_iy();                                          // [ADD A, (IY+d)]
    void ADD_implied_immediate();                                           // [ADD A, n]

    // ADC Instructions
    void ADC_implied_register();                                            // [ADC A, r]
    void ADC_implied_register_indirect();                                   // [ADC A, (HL)]
    void ADC_implied_indexed_ix();                                          // [ADC A, (IX+d)]
    void ADC_implied_indexed_iy();                                          // [ADC A, (IY+d)]
    void ADC_implied_immediate();                                           // [ADC A, n]

    // SUB Instructions
    void SUB_implied_register();                                            // [SUB r]
    void SUB_implied_register_indirect();                                   // [SUB (HL)]
    void SUB_implied_indexed_ix();                                          // [SUB (IX+d)]
    void SUB_implied_indexed_iy();                                          // [SUB (IY+d)]
    void SUB_implied_immediate();                                           // [SUB n]

    // SBC Instructions
    void SBC_implied_register();                                            // [SBC A, r]
    void SBC_implied_register_indirect();                                   // [SBC A, (HL)]
    void SBC_implied_indexed_ix();                                          // [SBC A, (IX+d)]
    void SBC_implied_indexed_iy();                                          // [SBC A, (IY+d)]
    void SBC_implied_immediate();                                           // [SBC A, n]

    // AND Instructions
    void AND_implied_register();                                            // [ADD r]
    void AND_implied_register_indirect();                                   // [ADD (HL)]
    void AND_implied_indexed_ix();                                          // [ADD (IX+d)]
    void AND_implied_indexed_iy();                                          // [ADD (IY+d)]
    void AND_implied_immediate();                                           // [ADD n]

    // OR Instructions
    void OR_implied_register();                                             // [OR r]
    void OR_implied_register_indirect();                                    // [OR (HL)]
    void OR_implied_indexed_ix();                                           // [OR (IX+d)]
    void OR_implied_indexed_iy();                                           // [OR (IY+d)]
    void OR_implied_immediate();                                            // [OR n]

    // XOR Instructions
    void XOR_implied_register();                                            // [XOR r]
    void XOR_implied_register_indirect();                                   // [XOR (HL)]
    void XOR_implied_indexed_ix();                                          // [XOR (IX+d)]
    void XOR_implied_indexed_iy();                                          // [XOR (IY+d)]
    void XOR_implied_immediate();                                           // [XOR n]

    // OR Instructions
    void CP_implied_register();                                             // [CP r]
    void CP_implied_register_indirect();                                    // [CP (HL)]
    void CP_implied_indexed_ix();                                           // [CP (IX+d)]
    void CP_implied_indexed_iy();                                           // [CP (IY+d)]
    void CP_implied_immediate();                                            // [CP n]

    // INC Instructions
    void INC_implied_register();                                            // [INC r]
    void INC_implied_register_indirect();                                   // [INC (HL)]
    void INC_implied_indexed_ix();                                          // [INC (IX+d)]
    void INC_implied_indexed_iy();                                          // [INC (IY+d)]

    // DEC Instructions
    void DEC_implied_register();                                            // [DEC r]
    void DEC_implied_register_indirect();                                   // [DEC (HL)]
    void DEC_implied_indexed_ix();                                          // [DEC (IX+d)]
    void DEC_implied_indexed_iy();                                          // [DEC (IY+d)]

    // General-Purpose AF Operation Instructions
    // DAA Instruction
    void DAA_implied();                                                     // [DAA]

    // CPL Instruction
    void CPL_implied();                                                     // [CPL]

    // NEG Instruction
    void NEG_implied();                                                     // [NEG]

    // CCF Instruction
    void CCF_implied();                                                     // [CCF]

    // SCF Instruction
    void SCF_implied();                                                     // [SCF]

    // Rotate Instructions
    // Rotate Left Circular Instructions
    void RLCA_implied();                                                    // [RLCA]
    void RLC_implied();                                                     // [RLC r]
    void RLC_indirect();                                                    // [RLC (HL)]
    void RLC_indexed_ix();                                                  // [RLC (IX+d)
    void RLC_indexed_iy();                                                  // [RLC (IY+d)

    // Rotate Right Circular Instructions
    void RRCA_implied();                                                    // [RRCA]
    void RRC_implied();                                                     // [RRC r]
    void RRC_indirect();                                                    // [RRC (HL)]
    void RRC_indexed_ix();                                                  // [RRC (IX+d)]
    void RRC_indexed_iy();                                                  // [RRC (IY+d)]

    // Rotate Left Instructions
    void RLA_implied();                                                      // [RLA]
    void RL_implied();                                                       // [RL r]
    void RL_indirect();                                                      // [RL (HL)]
    void RL_indexed_ix();                                                    // [RL (IX+d)]
    void RL_indexed_iy();                                                    // [RL (IY+d)]

    // Rotate Right Instructions
    void RRA_implied();                                                      // [RRA]
    void RR_implied();                                                       // [RR r]
    void RR_indirect();                                                      // [RR (HL)]
    void RR_indexed_ix();                                                    // [RR (IX+d)]
    void RR_indexed_iy();                                                    // [RR (IY+d)]

    // Rotate Digit Left Instruction
    void RLD_implied();                                                      // [RLD]

    // Rotate Digit Right Instruction
    void RRD_implied();                                                      // [RRD]

    // Shift Instructions
    // Shift Left Arithmetic Instructions
    void SLA_implied();                                                      // [SLA r]
    void SLA_indirect();                                                     // [SLA (HL)]
    void SLA_indexed_ix();                                                   // [SLA (IX+d)]
    void SLA_indexed_iy();                                                   // [SLA (IY+d)]

    // Shift Right Arithmetic Instructions
    void SRA_implied();                                                      // [SRA r]
    void SRA_indirect();                                                     // [SRA (HL)]
    void SRA_indexed_ix();                                                   // [SRA (IX+d)]
    void SRA_indexed_iy();                                                   // [SRA (IY+d)]

    // Shift Right Logical Instructions
    void SRL_implied();                                                      // [SRL r]
    void SRL_indirect();                                                     // [SRL (HL)]
    void SRL_indexed_ix();                                                   // [SRL (IX+d)]
    void SRL_indexed_iy();                                                   // [SRL (IY+d)]

    // BIT Instructions
    void BIT_implied();                                                      // [BIT b, r]
    void BIT_indirect();                                                     // [BIT b, (HL)]
    void BIT_indexed_ix();                                                   // [BIT b, (IX+d)]
    void BIT_indexed_iy();                                                   // [BIT b, (IY+d)]

    // Jump Instructions
    void JP_immediate();                                                     // [JP nn]
    void JP_cc_immediate();                                                  // [JP cc, nn]

    // NOP Instruction
    void NOP_implied();                                                      // [NOP]

    // 16-bit Instructions
	// LD Instructions
    void LD_register_immediate_extended_16_bit();                            // [LD ss, nn]
	void LD_register_immediate_extended_ix();                                // [LD IX, nn]
	void LD_register_immediate_extended_iy();                                // [LD IY, nn]
    void LD_register_extended_16_bit();                                      // [LD ss, (nn)]
    void LD_register_extended_hl();                                          // [LD HL, (nn)]
    void LD_register_extended_ix();                                          // [LD IX, (nn)]
    void LD_register_extended_iy();                                          // [LD IY, (nn)]
    void LD_register_register_hl();                                          // [LD SP, HL]
    void LD_register_register_ix();                                          // [LD SP, IX]
    void LD_register_register_iy();                                          // [LD SP, IY]
    void LD_extended_register_16_bit();                                      // [LD (nn), ss]
    void LD_extended_register_hl();                                          // [LD (nn), HL]
    void LD_extended_register_ix();                                          // [LD (nn), IX]
    void LD_extended_register_iy();                                          // [LD (nn), IY]

    // PUSH Instructions
    void PUSH_register_indirect_register();                                  // [PUSH qq]
    void PUSH_register_indirect_register_ix();                               // [PUSH IX]
    void PUSH_register_indirect_register_iy();                               // [PUSH IY]

    // POP Instructions
    void POP_register_indirect_register();                                   // [POP qq]
    void POP_register_indirect_register_ix();                                // [POP IX]
    void POP_register_indirect_register_iy();                                // [POP IY]

    // EX Instructions
    void EX_implied_implied_af();                                            // [EX AF, AF']
    void EXX_implied_implied();                                              // [EXX]
    void EX_implied_implied();                                               // [EX DE, HL]
    void EX_register_indirect_implied_hl();                                  // [EX (SP), HL]
    void EX_register_indirect_implied_ix();                                  // [EX (SP), IX]
    void EX_register_indirect_implied_iy();                                  // [EX (SP), IY]

    // Arithmetic Instructions
    // ADD Instructions
    void ADD_implied_register_extended();                                    // [ADD HL, ss]
    void ADD_implied_register_extended_ix();                                 // [ADD IX, pp]
    void ADD_implied_register_extended_iy();                                 // [ADD IY, rr]

    // ADC Instruction
    void ADC_implied_register_extended();                                    // [ADC HL, ss]

    // SBC Instruction
    void SBC_implied_register_extended();                                    // [SBC HL, ss]

    // INC Instructions
    void INC_implied_register_extended();                                    // [INC ss]
    void INC_implied_register_extended_ix();                                 // [INC IX]
    void INC_implied_register_extended_iy();                                 // [INC IY]

    // DEC Instructions
    void DEC_implied_register_extended();                                    // [DEC ss]
    void DEC_implied_register_extended_ix();                                 // [DEC IX]
    void DEC_implied_register_extended_iy();                                 // [DEC IY]



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



private:
	Bus* bus = nullptr;


	uint8_t rom_read(uint16_t address);

    uint8_t ram_read(uint16_t address);
    void ram_write(uint16_t address, uint8_t data);


	uint8_t get_flag(FLAGSZ80 flag) const;
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
