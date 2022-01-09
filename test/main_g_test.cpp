//
// Created by Daniel on 12/15/2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}


