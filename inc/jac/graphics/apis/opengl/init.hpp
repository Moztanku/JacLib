#pragma once

#include <glad/gl.h>

#include "jac/print.hpp"

namespace jac::graphics::opengl
{

inline bool init_gl() noexcept
{
    static bool initialized{false};

    if (initialized)
        return true;

    if (!gladLoaderLoadGL())
    {
        jac::print_error("Failed to load OpenGL functions");
        return false;
    }

    initialized = true;

    return true;
}

inline void terminate_gl() noexcept
{
    gladLoaderUnloadGL();

    return;
}

} // namespace jac::graphics::opengl
