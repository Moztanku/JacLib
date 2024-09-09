#include <gtest/gtest.h>

#include "jac/types.hpp"

TEST(Types, Integers)
{
    ASSERT_EQ(sizeof(int8), 1);
    ASSERT_EQ(sizeof(int16), 2);
    ASSERT_EQ(sizeof(int32), 4);
    ASSERT_EQ(sizeof(int64), 8);

    ASSERT_EQ(sizeof(uint8), 1);
    ASSERT_EQ(sizeof(uint16), 2);
    ASSERT_EQ(sizeof(uint32), 4);
    ASSERT_EQ(sizeof(uint64), 8);
}

TEST(Types, Floats)
{
    ASSERT_EQ(sizeof(float32), 4);
    ASSERT_EQ(sizeof(float64), 8);
}
