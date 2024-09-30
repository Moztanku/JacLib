/**
 * @file indexbuffer.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains index buffer interface for the graphics API.
 */
#pragma once

#include <span>

#include "jac/types.hpp"
#include "jac/impl/api.hpp"
#include "jac/graphics/common.hpp"

namespace jac::graphics
{

/**
 * @brief Interface for an index buffer, to be implemented by the graphics API
 */
JAC_API
struct IndexBufferI
{
    virtual ~IndexBufferI() = default;

    /**
     * @brief Bind the index buffer for use
     */
    virtual void bind() const = 0;

    /**
     * @brief Unbind the index buffer after use
     */
    virtual void unbind() const = 0;

    /**
     * @brief Returns whether the index buffer is bound
     * 
     * @return true If the index buffer is bound
     */
    virtual bool isBound() const = 0;

    /**
     * @brief Get the number of indices in the buffer
     * 
     * @return uint32 The number of indices
     */
    virtual uint32 getCount() const = 0;

    /**
     * @brief Set the data of the index buffer
     * 
     * @param data The data to set
     * @param count The number of indices in the data
     */
    virtual void setData(const uint32* data, const uint32 count) = 0;

    /**
     * @brief Set the data of the index buffer
     * 
     * @param data The data to set
     */
    virtual void setData(const std::span<uint32> data) = 0;

    /**
     * @brief Release the data of the index buffer, called automatically by the derived class destructor
     */
    virtual void destroy() = 0;

    /**
     * @brief Map the index buffer to memory. The buffer must be unmapped with unlock() after use.
     * 
     * @param access The type of access to the buffer
     * 
     * @return uint32* The pointer to the buffer data
     */
    virtual uint32* lock(const AccessType access = AccessType::ReadWrite) = 0;

    /**
     * @brief Unmap the index buffer from memory
     */
    virtual void unlock() = 0;

}; // IndexBufferI

} // namespace jac::graphics

// If using the library, include the implementation
//  For now OpenGL is the only implementation, later this will be
//  optionally included based on the graphics APIs selected.
#if !defined(JAC_BUILD_LIB) && defined(JAC_GRAPHICS_OPENGL)
    #include "jac/graphics/apis/opengl/indexbuffer.hpp"
#endif
