#include <gtest/gtest.h>

#include <cstring>
#include <cstdlib>
#include <cstdio>

namespace {
    TEST(SimpleTest, SimpleTestCase) {
        int a = 1;
        EXPECT_EQ(a, 1);
    }
}
