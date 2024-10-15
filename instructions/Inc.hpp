#ifndef Inc_hpp
#define Inc_hpp


// 8-bit Instructions
void INC_implied_register();                                            // [INC r]
void INC_implied_register_indirect();                                   // [INC (HL)]
void INC_implied_indexed_ix();                                          // [INC (IX+d)]
void INC_implied_indexed_iy();                                          // [INC (IY+d)]

// 16-bit Instructions
void INC_implied_register_extended();                                    // [INC ss]
void INC_implied_register_extended_ix();                                 // [INC IX]
void INC_implied_register_extended_iy();                                 // [INC IY]

#endif