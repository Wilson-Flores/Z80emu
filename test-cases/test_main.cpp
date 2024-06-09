#include "gtest/gtest.h"
#include "../Bus.hpp"



int main(int argc, char* argv[]){

    // Initializes the Google Test framework with cmd-line arguments
    ::testing::InitGoogleTest(&argc, argv);

    //  Runs all the tests that have been defined.
    //  It returns an integer, which is typically 0 if all tests pass and 1 if any test fails.
    return RUN_ALL_TESTS();

    return 0;
}