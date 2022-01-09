cmake_minimum_required(VERSION 3.19)

project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

# pliki naglowkowe dla googletest
include_directories(
        include
        src
        googletest-main/googletest/include
        googletest-main/googlemock/include)

set(SOURCE_FILES
        src/storage_types.cpp
        src/package.cpp
        src/nodes.cpp
        )

set(TEST_SOURCES
        test/main_g_test.cpp
        test/test_package.cpp
        )

add_subdirectory(googletest-main)
link_libraries(gmock)

add_executable(NetSim_test ${TEST_SOURCES} ${SOURCE_FILES})

add_executable(NetSim ${SOURCE_FILES})
