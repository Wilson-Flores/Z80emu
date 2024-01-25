#include "z80.hpp"
#include "Bus.hpp"
#include "Test.hpp"



int main() {
	Bus test;

	LD_r_n_test(test);
	LD_r_r_test(test);


	return 0;
}



