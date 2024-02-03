cmake_minimum_required (VERSION 3.8)

project("Z80emu")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(z80emu "main.cpp" "z80.cpp" "Bus.cpp" "Test.cpp"
        Load.cpp
)
