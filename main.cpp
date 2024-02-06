#include "Bus.hpp"
#include "Test.hpp"


void LD_test(Bus& test){
    int test_choice;
    std::cout << "Enter a number: ";
    std::cin >> test_choice;

    switch (test_choice) {
        case 1:
            LD_register_immediate_test(test);
            break;
        case 2:
            LD_register_register_test(test);
            break;
        case 3:
            LD_register_register_indirect_test(test);
            break;
        case 4:
            LD_register_implied_test(test);
            break;
        case 5:
            LD_register_indexed_test(test);
            break;
        case 6:
            LD_register_extended_test(test);
            break;
        case 7:
            LD_register_indirect_immediate(test);
            break;
        case 8:
            LD_register_indirect_register(test);
            break;
        case 9:
            LD_indexed_immediate_test(test);
            break;
        case 10:
            LD_indexed_register_test(test);
            break;
        case 11:
            LD_extended_register_test(test);
            break;
        case 12:
            LD_implied_register_test(test);
            break;
        default:
            std::cout << "Invalid choice.\n";
    }
}



int main() {
	Bus test;

    LD_test(test);

    return 0;
}



