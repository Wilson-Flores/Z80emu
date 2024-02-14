#include "Bus.hpp"
#include "test-cases/LD_test.hpp"
#include "test-cases/push_pop_test.hpp"
#include "test-cases/exchange_test.hpp"


void subtraction(uint8_t accumulator, uint8_t data){
    int8_t result = static_cast<int8_t>(accumulator) - static_cast<int8_t>(data);

    // Print intermediate steps
    std::cout << "Accumulator: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(accumulator) << std::endl;
    std::cout << "Data: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data) << std::endl;
    std::cout << "After conversion to int8_t: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<int8_t>(accumulator)) << std::endl;
    std::cout << "After conversion to int8_t: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<int8_t>(data)) << std::endl;
    std::cout << "Result: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(result) << std::endl;

}





int main() {
	Bus test;

//    LD_test(test);
//    push_pop_test(test);
//    EX_test(test);
    uint8_t accumulator = 0x00;
    uint8_t data = 0x19;

    subtraction(accumulator,data);

    return 0;
}



