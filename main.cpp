#include "Bus.hpp"
#include "test-cases/LD_test.hpp"
#include "test-cases/push_pop_test.hpp"
#include "test-cases/exchange_test.hpp"
#include "test-cases/compare_test.hpp"
#include "test-cases/arithmetic_test.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <fstream> // Added for file handling

void SBC_test() {
    std::ofstream outputFile("output.txt"); // Open the output file

    uint16_t accumulator = 0x0000;
    uint16_t data;
    uint8_t carry_flag = 0x00;

    outputFile << "Initial Carry Flag: " << std::hex << +carry_flag << '\n'; // +carry_flag to print as integer

    while (accumulator < 0x0100) {
        data = 0x0000; // Reset data for each iteration of accumulator
        while (data < 0x0100) {
            uint16_t result = accumulator - data - carry_flag; // Calculate result inside the loop

            outputFile << "Accumulator: " << std::hex << accumulator << "\tData: " << data << "\tResult: " << result << '\n';
            data++;
        }
        accumulator++;
    }

    carry_flag = 0x01;
    outputFile << "Carry Flag: " << std::hex << +carry_flag << '\n'; // +carry_flag to print as integer

    accumulator = 0x0000; // Reset accumulator
    data = 0x0000; // Reset data
    while (accumulator < 0x0100) {
        data = 0x0000; // Reset data for each iteration of accumulator
        while (data < 0x0100) {
            uint16_t result = accumulator - data - carry_flag; // Calculate result inside the loop

            outputFile << "Accumulator: " << std::hex << accumulator << "\tData: " << data << "\tResult: " << result << '\n';
            data++;
        }
        accumulator++;
    }

    outputFile.close(); // Close the output file
}



int main() {
	Bus test;

//    LD_test(test);
//    push_pop_test(test);
//    EX_test(test);
//    compare_test(test);
    arithmetic_test_choice(test);


    return 0;
}



