#include "Bus.hpp"
#include "test-cases/LD_test.hpp"
#include "test-cases/push_pop_test.hpp"






int main() {
	Bus test;

//    LD_test(test);

    push_pop_test(test);

    return 0;
}



