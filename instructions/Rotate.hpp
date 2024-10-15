#ifndef Rotate_hpp
#define Rotate_hpp


// 8-bit Instructions
// Rotate Left Circular Instructions
void RLCA_implied();                                                    // [RLCA]
void RLC_implied();                                                     // [RLC r]
void RLC_indirect();                                                    // [RLC (HL)]
void RLC_indexed_ix();                                                  // [RLC (IX+d)
void RLC_indexed_iy();                                                  // [RLC (IY+d)

// Rotate Right Circular Instructions
void RRCA_implied();                                                    // [RRCA]
void RRC_implied();                                                     // [RRC r]
void RRC_indirect();                                                    // [RRC (HL)]
void RRC_indexed_ix();                                                  // [RRC (IX+d)]
void RRC_indexed_iy();                                                  // [RRC (IY+d)]

// Rotate Left Instructions
void RLA_implied();                                                      // [RLA]
void RL_implied();                                                       // [RL r]
void RL_indirect();                                                      // [RL (HL)]
void RL_indexed_ix();                                                    // [RL (IX+d)]
void RL_indexed_iy();                                                    // [RL (IY+d)]

// Rotate Right Instructions
void RRA_implied();                                                      // [RRA]
void RR_implied();                                                       // [RR r]
void RR_indirect();                                                      // [RR (HL)]
void RR_indexed_ix();                                                    // [RR (IX+d)]
void RR_indexed_iy();                                                    // [RR (IY+d)]

// Rotate Digit Left Instruction
void RLD_implied();                                                      // [RLD]

// Rotate Digit Right Instruction
void RRD_implied();                                                      // [RRD]

#endif