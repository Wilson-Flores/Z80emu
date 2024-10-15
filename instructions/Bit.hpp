#ifndef Bit_hpp
#define Bit_hpp


// 8-bit Instructions
void BIT_implied();                                                      // [BIT b, r]
void BIT_indirect();                                                     // [BIT b, (HL)]
void BIT_indexed_ix();                                                   // [BIT b, (IX+d)]
void BIT_indexed_iy();                                                   // [BIT b, (IY+d)]

#endif