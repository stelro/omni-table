#include <gtest/gtest.h>

#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "table.h"

using namespace gctable;

namespace {

class TableTest : public ::testing::Test { 
protected:
    Table table;
};

TEST_F(TableTest, TableHasZeroSizeAndZeroCapacity) {
    EXPECT_EQ(0, table.size());
    EXPECT_EQ(0, table.capacity());
}

TEST_F(TableTest, CapacityCanGrowToOne) {
    table[0][0] = 1;
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(1, table.capacity());
}

TEST_F(TableTest, IncreasesCapacity) {
    for (size_t i = 0; i < 10; ++i) {
        table[i][0] = i;
    }
    EXPECT_EQ(10, table.size());
    EXPECT_GE(table.capacity(), 10);
    EXPECT_TRUE((table.capacity() & (table.capacity() - 1)) == 0);  // Check if capacity is power of 2
}

TEST_F(TableTest, CapacityDoubling) {
    table[0][0] = 1;   // Should set capacity to 1
    EXPECT_EQ(1, table.capacity());

    table[1][0] = 1;  // Should double capacity to 2
    EXPECT_EQ(2, table.capacity());

    table[2][0] = 1;  // Capacity should double from 2 to 4
    EXPECT_EQ(4, table.capacity());
}

TEST_F(TableTest, ShrinkToFitWorks) {
    for (size_t i = 0; i < 5; ++i) {
        table[i][0] = i;
    }
    EXPECT_EQ(5, table.size());
    table.shrink_to_fit();
    EXPECT_EQ(5, table.capacity());
}

TEST_F(TableTest, ShrinkToActualSize) {
    for (size_t i = 0; i < 16; ++i) {
        table[i][0] = i;
    }
    table.shrink_to_fit();
    EXPECT_EQ(16, table.size());
    EXPECT_EQ(16, table.capacity());
}

TEST_F(TableTest, NoChangeWhenShrinkToFitCalledWithoutExcessCapacity) {
    table[1][0] = 1;
    table.shrink_to_fit();
    EXPECT_EQ(1, table.capacity());
}


}
    