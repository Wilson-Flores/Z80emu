#include "Bus.hpp"
#include "test-cases/LD_test.hpp"
#include "test-cases/push_pop_test.hpp"
#include "test-cases/exchange_test.hpp"
#include "test-cases/compare_test.hpp"
#include "test-cases/add_test.hpp"



int main() {
	Bus test;

//    LD_test(test);
//    push_pop_test(test);
//    EX_test(test);
//    compare_test(test);
//    add_test(test);
    adc_test(test);

    return 0;
}



