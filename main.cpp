#include "Bus.hpp"
#include "Test.hpp"



int main() {
	Bus test;

	//LD_register_immediate_test(test);
	//LD_register_register_test(test);
	//LD_register_register_indirect_test(test);
	//LD_register_implied_test(test);
	//LD_register_indexed_test(test);
	LD_register_extended_test(test);
	LD_register_indirect_immediate(test);

	return 0;
}



