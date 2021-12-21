# wersja cmake
cmake_minimum_required(VERSION 3.19)

# nazwa projektu
project(NetSim)

# standard C++
set(CMAKE_CXX_STANDARD 17)

# flagi kompilacji
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

# dodatkowe pliki cmake dla poszczegolnych czesci projektu
add_subdirectory(polprodukty)
add_subdirectory(wezly)
add_subdirectory(fabryka)
add_subdirectory(IO)
add_subdirectory(raporty)
add_subdirectory(symulacja)


### TESTY ###
# pliki naglowkowe dla googletest
include_directories(
        polprodukty/include
        polprodukty/src
        googletest-main/googletest/include
        googletest-main/googlemock/include)

# wspoldzielone pliki cpp dla testów
set(TEST_SOURCES
        # testy - polprodukty
        polprodukty/test/storage_types_test.cpp
        polprodukty/test/package_test.cpp

        # testy - wezly


        # testy - fabryka


        # testy - I/O


        # testy - raporty


        # testy - symulacja


        # test - glowny pilk
        test/main_g_test.cpp
        )

# dodanie biblioteki googletest
add_subdirectory(googletest-main)
link_libraries(gmock)

# konfiguracja do testow
add_executable(NetSim_test ${TEST_SOURCES})
