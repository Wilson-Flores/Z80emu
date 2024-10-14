#ifndef Sub_hpp
#define Sub_hpp

#include "../z80.hpp"


// 8-bit Instructions
// Arithmetic Instructions
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


// 16-bit Instruction
// SBC Instruction
void SBC_implied_register_extended();                                    // [SBC HL, ss]

#endif