#ifndef And_hpp
#define And_hpp


// 8-bit Instructions
// Arithmetic Instructions
void AND_implied_register();                                            // [ADD r]
void AND_implied_register_indirect();                                   // [ADD (HL)]
void AND_implied_indexed_ix();                                          // [ADD (IX+d)]
void AND_implied_indexed_iy();                                          // [ADD (IY+d)]
void AND_implied_immediate();                                           // [ADD n]

#endif