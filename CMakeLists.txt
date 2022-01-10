cmake_minimum_required(VERSION 3.19)

project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)


include_directories(
        include
        src
        mocks
        googletest-main/googletest/include
        googletest-main/googlemock/include)

set(SOURCE_FILES
        src/storage_types.cpp
        src/package.cpp
        src/nodes.cpp
        src/helpers.cpp
        src/factory.cpp
        )

set(TEST_SOURCES
        test/main_g_test.cpp
        test/test_package.cpp
        test/test_storage_types.cpp
        test/test_nodes.cpp
        )

add_subdirectory(googletest-main)
link_libraries(gmock)

add_executable(NetSim_test ${TEST_SOURCES} ${SOURCE_FILES})
target_compile_definitions(NetSim_test PUBLIC EXERCISE_ID=EXERCISE_ID_FACTORY)

add_executable(NetSim ${SOURCE_FILES})
