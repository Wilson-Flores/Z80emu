#ifndef Load_hpp
#define Load_hpp


// 8-bit Instructions
void LD_register_immediate();                                           // [LD r, n]
void LD_register_register();                                            // [LD r, r']
void LD_register_register_indirect();                                   // [LD r, (HL)]
void LD_register_register_indirect_BC();                                // [LD A, (BC)]
void LD_register_register_indirect_DE();                                // [LD A, (DE)]
void LD_register_implied_I();                                           // [LD A, I]
void LD_register_implied_R();                                           // [LD A, R]
void LD_register_indexed_ix();                                          // [LD r, (IX+d)]
void LD_register_indexed_iy();                                          // [LD r, (IY+d)]
void LD_register_extended();                                            // [LD A, (nn)]
void LD_register_indirect_immediate();                                  // [LD (HL), n]
void LD_register_indirect_register();                                   // [LD (HL), r]
void LD_register_indirect_register_BC();                                // [LD (BC), A]
void LD_register_indirect_register_DE();                                // [LD (DE), A]
void LD_indexed_ix_immediate();                                         // [LD (IX+d), n]
void LD_indexed_iy_immediate();                                         // [LD (IY+d), n]
void LD_indexed_ix_register();                                          // [LD (IX+d), r]
void LD_indexed_iy_register();                                          // [LD (IY+d), r]
void LD_extended_register();                                            // [LD (nn), A]
void LD_implied_register_I();                                           // [LD I, A]
void LD_implied_register_R();                                           // [LD R, A]

// Block Transfer Instructions
void LDI_register_indirect_register_indirect();                         // [LDI]
void LDIR_register_indirect_register_indirect();                        // [LDIR]
void LDD_register_indirect_register_indirect();                         // [LDD]
void LDDR_register_indirect_register_indirect();                        // [LDDR]


// 16-bit Instructions
void LD_register_immediate_extended_16_bit();                            // [LD ss, nn]
void LD_register_immediate_extended_ix();                                // [LD IX, nn]
void LD_register_immediate_extended_iy();                                // [LD IY, nn]
void LD_register_extended_16_bit();                                      // [LD ss, (nn)]
void LD_register_extended_hl();                                          // [LD HL, (nn)]
void LD_register_extended_ix();                                          // [LD IX, (nn)]
void LD_register_extended_iy();                                          // [LD IY, (nn)]
void LD_register_register_hl();                                          // [LD SP, HL]
void LD_register_register_ix();                                          // [LD SP, IX]
void LD_register_register_iy();                                          // [LD SP, IY]
void LD_extended_register_16_bit();                                      // [LD (nn), ss]
void LD_extended_register_hl();                                          // [LD (nn), HL]
void LD_extended_register_ix();                                          // [LD (nn), IX]
void LD_extended_register_iy();                                          // [LD (nn), IY]

#endif