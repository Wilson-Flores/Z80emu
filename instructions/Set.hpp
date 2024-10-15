#ifndef Set_hpp
#define Set_hpp


// 8-bit Instructions
void SET_implied();                                                      // [SET b, r]
void SET_indirect();                                                     // [SET b, (HL)]
void SET_indexed_ix();                                                   // [SET b, (IX+d)]
void SET_indexed_iy();                                                   // [SET b, (IY+d)]

#endif