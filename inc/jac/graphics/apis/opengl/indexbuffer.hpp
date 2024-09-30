/**
 * @file opengl/indexbuffer.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains the OpenGL implementation of the IndexBuffer interface.
 */
#pragma once

#include "jac/graphics/indexbuffer.hpp"

namespace jac::graphics::opengl
{

/**
 * @brief OpenGL implementation of the IndexBuffer interface
 */
template <BufferType Type = BufferType::Static>
class IndexBuffer : public jac::graphics::IndexBufferI
{
public:
    /**
     * @brief Construct a new empty IndexBuffer object, fill it with data using setData().
     */
    IndexBuffer();

    /**
     * @brief Construct a new IndexBuffer object and fill it with data.
     * 
     * @param data The data to fill the buffer with
     * @param count The number of indices in the data
     */
    IndexBuffer(const uint32* data, const uint32 count);

    /**
     * @brief Construct a new IndexBuffer object and fill it with data.
     * 
     * @param data The data to fill the buffer with
     */
    IndexBuffer(const std::span<uint32> data);

    /**
     * @brief Destroy the IndexBuffer object and free the buffer.
     */
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    IndexBuffer(IndexBuffer&&);
    IndexBuffer& operator=(IndexBuffer&&);

    void bind() const override;
    void unbind() const override;

    bool isBound() const override;
    uint32 getCount() const override;

    void setData(const uint32* data, const uint32 count) override;
    void setData(const std::span<uint32> data) override;

    void destroy() override;

    uint32* lock(const AccessType access = AccessType::ReadWrite) override;
    void unlock() override;

private:
    uint m_id{0u};
    uint32 m_count{0u};
}; // IndexBuffer

} // namespace jac::graphics::opengl
