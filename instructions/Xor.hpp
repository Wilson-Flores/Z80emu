#ifndef Xor_hpp
#define Xor_hpp

#include "../z80.hpp"


// 8-bit Instructions
// Arithmetic Instructions
void XOR_implied_register();                                            // [XOR r]
void XOR_implied_register_indirect();                                   // [XOR (HL)]
void XOR_implied_indexed_ix();                                          // [XOR (IX+d)]
void XOR_implied_indexed_iy();                                          // [XOR (IY+d)]
void XOR_implied_immediate();                                           // [XOR n]

#endif
