#ifndef Z80EMU_INSTRUCTIONTABLE_HPP
#define Z80EMU_INSTRUCTIONTABLE_HPP

#include <array>
#include "../z80.hpp"


/* INSTRUCTION struct represents an instruction, it has 2 data members and a constexpr constructor.
 * Data members:
 * const char* opcode: a pointer to a constant character array.
 * void (z80cpu::*instruction)(): z80cpu member function pointer
 * Constexpr Constructor: initialize arrays at compile time
 * Parameters:
 * const char* name: initializes the opcode data member.
 * void (z80cpu::*fp)(): initializes the instruction data member.
 * Member Initializer List:
 * : opcode(name), instruction(fp)
 * this syntax is a member initializer list. it directly initializes opcode with name and instruction with fp.
 */
struct INSTRUCTION {
    const char* opcode;
    void (z80cpu::*instruction)();

    constexpr INSTRUCTION(const char* name, void (z80cpu::*fp)()) : opcode(name), instruction(fp){}
};

/* Extern tells the compiler that the tables are defined elsewhere (InstructionTable.cpp) and will make it
 * available to any file that includes this header.
 * Const ensures the tables cannot be modified after its initialization.
 * Constexpr cant be used in the initialization, only at the definition.
 * make sure to use extern const for future constexpr when dealing with defining variables outside the file.
*/

//Instruction tables
extern const std::array<INSTRUCTION, 256> main_instruction_table;
extern const std::array<INSTRUCTION, 256> bit_instruction_table;        // opcode: CB
extern const std::array<INSTRUCTION, 256> ix_instruction_table;         // opcode: DD
extern const std::array<INSTRUCTION, 256> ix_bit_instruction_table;     // opcode: DD CB
extern const std::array<INSTRUCTION, 256> misc_instruction_table;       // opcode: ED
extern const std::array<INSTRUCTION, 256> iy_instruction_table;         // opcode: FD
extern const std::array<INSTRUCTION, 256> iy_bit_instruction_table;     // opcode: FD CB


#endif //Z80EMU_INSTRUCTIONTABLE_HPP
