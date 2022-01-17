cmake_minimum_required(VERSION 3.19)

project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Werror=switch)

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
        #src/reports.cpp
        )

set(TEST_SOURCES
        test/main_g_test.cpp
        test/test_package.cpp
        test/test_storage_types.cpp
        #test/test_nodes.cpp
        test/test_Factory.cpp
        test/test_factory_io.cpp
        #test/test_reports.cpp
        )

add_subdirectory(googletest-main)
link_libraries(gmock)

add_executable(NetSim_test ${TEST_SOURCES} ${SOURCE_FILES})
target_compile_definitions(NetSim_test PUBLIC EXERCISE_ID=FACTORY)