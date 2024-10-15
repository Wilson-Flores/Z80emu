#ifndef Jump_hpp
#define Jump_hpp


// 8-bit Instructions
void JP_immediate();                                                     // [JP nn]
void JP_cc_immediate();                                                  // [JP cc, nn]
void JR_relative();                                                      // [JR e]
void JR_cc_relative();                                                   // [JR cc, e]
void JP_implict();                                                       // [JP (HL)]
void JP_implict_ix();                                                    // [JP (IX)]
void JP_implict_iy();                                                    // [JP (IY)]
void DJNZ_immediate();                                                   // [DJNZ e]

#endif