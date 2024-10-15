#ifndef Reset_hpp
#define Reset_hpp


// 8-bit Instructions
void RES_implied();                                                      // [RES b, r]
void RES_indirect();                                                     // [RES b, (HL)]
void RES_indexed_ix();                                                   // [RES b, (IX+d)]
void RES_indexed_iy();                                                   // [RES b, (IY+d)]

#endif