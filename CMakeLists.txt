cmake_minimum_required (VERSION 3.8)

project("Z80emu")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(z80emu "main.cpp" "z80.cpp" "Bus.cpp" "instructions/Load.cpp"
        instructions/Push.cpp
        instructions/Pop.cpp
        instructions/Exchange.cpp
        instructions/Compare.cpp
        instructions/Add.cpp
)


add_executable(z80emu_test "main.cpp" "z80.cpp" "Bus.cpp" "test-cases/LD_test.cpp" "instructions/Load.cpp"
        instructions/Push.cpp
        instructions/Pop.cpp
        test-cases/push_pop_test.cpp
        instructions/Exchange.cpp
        test-cases/exchange_test.cpp
        instructions/Compare.cpp
        test-cases/compare_test.cpp
        instructions/Add.cpp
)