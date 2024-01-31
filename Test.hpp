#ifndef Test_hpp
#define Test_hpp

#include "Bus.hpp"
#include <iomanip>
#include <iostream>

void LD_register_immediate_test(Bus& test);

void LD_register_register_test(Bus& test);

void LD_register_register_indirect_test(Bus& test);

void LD_register_implied_test(Bus& test);

void LD_register_indexed_test(Bus& test);

void LD_register_extended_test(Bus& test);

void LD_register_indirect_immediate(Bus& test);

#endif // !Test_hpp
