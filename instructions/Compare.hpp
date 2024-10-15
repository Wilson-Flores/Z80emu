#ifndef Compare_hpp
#define Compare_hpp


// 8-bit Instructions
// Block Search Instructions
void CPI_register_indirect();                                           // [CPI]
void CPIR_register_indirect();                                          // [CPIR]
void CPD_register_indirect();                                           // [CPD]
void CPDR_register_indirect();                                          // [CPDR]

// Arithmetic Instructions
void CP_implied_register();                                             // [CP r]
void CP_implied_register_indirect();                                    // [CP (HL)]
void CP_implied_indexed_ix();                                           // [CP (IX+d)]
void CP_implied_indexed_iy();                                           // [CP (IY+d)]
void CP_implied_immediate();                                            // [CP n]

#endif