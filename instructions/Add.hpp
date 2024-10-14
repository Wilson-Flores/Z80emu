#ifndef Add_hpp
#define Add_hpp

#include "../z80.hpp"


// 8-bit Instructions
// Arithmetic Instructions
// ADD Instructions
void ADD_implied_register();                                            // [ADD A, r]
void ADD_implied_register_indirect();                                   // [ADD A, (HL)]
void ADD_implied_indexed_ix();                                          // [ADD A, (IX+d)]
void ADD_implied_indexed_iy();                                          // [ADD A, (IY+d)]
void ADD_implied_immediate();                                           // [ADD A, n]

// ADC Instructions
void ADC_implied_register();                                            // [ADC A, r]
void ADC_implied_register_indirect();                                   // [ADC A, (HL)]
void ADC_implied_indexed_ix();                                          // [ADC A, (IX+d)]
void ADC_implied_indexed_iy();                                          // [ADC A, (IY+d)]
void ADC_implied_immediate();                                           // [ADC A, n]


// 16-bit Instructions
// ADD Instructions
void ADD_implied_register_extended();                                    // [ADD HL, ss]
void ADD_implied_register_extended_ix();                                 // [ADD IX, pp]
void ADD_implied_register_extended_iy();                                 // [ADD IY, rr]

// ADC Instruction
void ADC_implied_register_extended();                                    // [ADC HL, ss]

#endif