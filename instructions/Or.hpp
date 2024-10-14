#ifndef Or_hpp
#define Or_hpp

#include "../z80.hpp"


// 8-bit Instructions
// Arithmetic Instructions
void OR_implied_register();                                             // [OR r]
void OR_implied_register_indirect();                                    // [OR (HL)]
void OR_implied_indexed_ix();                                           // [OR (IX+d)]
void OR_implied_indexed_iy();                                           // [OR (IY+d)]
void OR_implied_immediate();                                            // [OR n]

#endif