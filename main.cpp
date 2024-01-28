#include "z80.hpp"
#include "Bus.hpp"
#include "Test.hpp"



int main() {
	Bus test;

	//LD_register_immediate_test(test);
	//LD_register_register_test(test);
	//LD_register_register_indirect_test(test);
	LD_register_implied_test(test);

	return 0;
}



