#include "Bus.hpp"
#include "Test.hpp"



int main() {
	Bus test;

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
        default:
            std::cout << "Invalid choice.\n";
    }
	return 0;
}



