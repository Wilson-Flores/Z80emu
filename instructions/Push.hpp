#ifndef Push_hpp
#define Push_hpp

#include "../z80.hpp"


// 16-bit Instructions
void PUSH_register_indirect_register();                                  // [PUSH qq]
void PUSH_register_indirect_register_ix();                               // [PUSH IX]
void PUSH_register_indirect_register_iy();                               // [PUSH IY]

#endif