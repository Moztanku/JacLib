/**
 * @file shader.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains shader interface for the graphics API.
 */
#pragma once

#include "jac/impl/api.hpp"
#include "jac/impl/graphics/shader.hpp"

namespace jac::graphics
{

/**
 * @brief Interface for a shader, to be implemented by the graphics API
 */
JAC_API
struct ShaderI : public impl::Shader_Base
{
    virtual ~ShaderI() = default;

    /**
     * @brief Bind the shader for use
     */
    virtual void bind() const = 0;

    /**
     * @brief Unbind the shader after use
     */
    virtual void unbind() const = 0;

    /**
     * @brief Returns whether the shader is bound
     * 
     * @return true If the shader is bound
     */
    virtual bool isBound() const = 0;

    /**
     * @brief Set a uniform in the shader
     * 
     * @tparam T The type of the uniform, can be any scalar, vector, or matrix type. For vectors and matrices use glm::vec and glm::mat.
     * @param uniform_name The name of the uniform in the shader
     * @param value The value to set the uniform to
     */
    template <typename T>
    void setUniform(const std::string& uniform_name, const T& value);

}; // ShaderI

} // namespace jac::graphics

// If using the library, include the implementation
//  For now OpenGL is the only implementation, later this will be
//  optionally included based on the graphics APIs selected.
#if !defined(JAC_BUILD_LIB) && defined(JAC_GRAPHICS_OPENGL)
    #include "jac/graphics/apis/opengl/shader.hpp"
#endif
