#ifndef Shift_hpp
#define Shift_hpp

#include "../z80.hpp"


// 8-bit Instructions
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

#endif