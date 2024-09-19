#pragma once

#include <gtest/gtest.h>

#include "jac/graphics/window.hpp"

/**
 * @brief Fixture for the graphics tests.
 */
class Graphics : public testing::Test
{
    protected:
        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
}; // class Graphics
