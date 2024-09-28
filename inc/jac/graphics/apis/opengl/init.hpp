#pragma once

#include <glad/gl.h>

#include "jac/print.hpp"

namespace jac::graphics::opengl
{

void init_gl() noexcept
{
    static bool initialized{false};

    if (initialized)
        return;

    if (!gladLoaderLoadGL())
    {
        jac::print_error("Failed to load OpenGL functions");
        return;
    }

    initialized = true;
}

} // namespace jac::graphics::opengl
