cmake_minimum_required (VERSION 3.11 FATAL_ERROR)

project("Z80emu" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


# List of source files
set(SOURCES
        z80.cpp
        Bus.cpp
        instructions/Load.cpp
        instructions/Push.cpp
        instructions/Pop.cpp
        instructions/Exchange.cpp
        instructions/Compare.cpp
        instructions/Add.cpp
        instructions/Sub.cpp
        instructions/And.cpp
        instructions/Or.cpp
        instructions/Xor.cpp
        instructions/Inc.cpp
        instructions/Dec.cpp
        instructions/Misc.cpp
        instructions/Rotate.cpp
)

add_executable(z80emu
        main.cpp
        ${SOURCES}
)



# check for ENABLE_UNIT_TESTS, by default it is on
option(ENABLE_UNIT_TESTS "Enable unit test" ON)

if(ENABLE_UNIT_TESTS)
    # include FetchContent module, declare a new content to fetch, query its properties
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.14.0
    )


    FetchContent_GetProperties(googletest)

    # if content hasn't populated (fetched) yet, we fetch and configure it
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)

        # Prevent GoogleTest from overriding our compiler/linker options when building with Visual Studio
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


        # add the targets: gtest, gtest_main, gmock, gmock_main
        add_subdirectory(
                ${googletest_SOURCE_DIR}
                ${googletest_SOURCE_DIR}
        )

        # Silence std::tr1 warning on MSVC
        if(MSVC)
            foreach(_tgt gtest gtest_main gmock gmock_main)
                target_compile_definitions(${_tgt}
                        PRIVATE
                        "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING")
            endforeach()
        endif()

        # My Clion fix on Windows
        if(MINGW)
            # Prevent GoogleTest from using PThreads (linux threading)
            set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
            endif()

    endif()


    add_executable(z80emu_test "")

    target_sources(z80emu_test PRIVATE
            test-cases/test_main.cpp
            test-cases/test_rotate.cpp
#            test-cases/test_load.cpp
            ${SOURCES})

    target_link_libraries(z80emu_test
            PRIVATE
            gtest_main)

    #enable testing
    enable_testing()
    add_test(NAME z80emu_test COMMAND $<TARGET_FILE:z80emu_test>)
endif()
