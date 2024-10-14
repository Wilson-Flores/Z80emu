#ifndef Dec_hpp
#define Dec_hpp

#include "../z80.hpp"


// 8-bit Instructions
// Arithmetic Instructions
void DEC_implied_register();                                            // [DEC r]
void DEC_implied_register_indirect();                                   // [DEC (HL)]
void DEC_implied_indexed_ix();                                          // [DEC (IX+d)]
void DEC_implied_indexed_iy();                                          // [DEC (IY+d)]

// 16-bit Instructions
void DEC_implied_register_extended();                                    // [DEC ss]
void DEC_implied_register_extended_ix();                                 // [DEC IX]
void DEC_implied_register_extended_iy();                                 // [DEC IY]

#endif