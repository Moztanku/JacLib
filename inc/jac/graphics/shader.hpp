#pragma once

namespace jac::graphics
{

/**
 * @brief Interface for a shader, to be implemented by the graphics API
 * 
 * 
 */
struct ShaderI
{
    virtual ~ShaderI() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};

} // namespace jac::graphics