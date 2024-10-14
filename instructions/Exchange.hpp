#ifndef Exchange_hpp
#define Exchange_hpp

#include "../z80.hpp"


// 16-bit Instructions
void EX_implied_implied_af();                                            // [EX AF, AF']
void EXX_implied_implied();                                              // [EXX]
void EX_implied_implied();                                               // [EX DE, HL]
void EX_register_indirect_implied_hl();                                  // [EX (SP), HL]
void EX_register_indirect_implied_ix();                                  // [EX (SP), IX]
void EX_register_indirect_implied_iy();                                  // [EX (SP), IY]

#endif