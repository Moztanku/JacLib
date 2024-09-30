/**
 * @file opengl/vertexbuffer.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains the OpenGL implementation of the vertex buffer.
 */
#pragma once

#include "jac/graphics/vertexbuffer.hpp"

namespace jac::graphics::opengl
{

/**
 * @brief OpenGL implementation of the vertex buffer
 * 
 * @tparam Type The type of the buffer, static, dynamic or stream, @see jac::graphics::BufferType
 */
template <BufferType Type = BufferType::Static>
JAC_API
class VertexBuffer : public VertexBufferI
{
public:
    /**
     * @brief Construct a new VertexBuffer object, needs to be initialized with setData()
     *  and setLayout() before use.
     */
    VertexBuffer() = default;

    /**
     * @brief Destroy the VertexBuffer object and free the buffer.
     */
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other);
    VertexBuffer& operator=(VertexBuffer&& other);

    void bind() const override;
    void unbind() const override;

    bool isBound() const override;
    uint32 getCount() const override;

    void setData(const void* data, const uint32 size) override;
    void setData(const std::span<std::byte> data) override;

    void setLayout(const VertexBufferLayout& layout) override;
    const VertexBufferLayout& getLayout() const override;

    void destroy() override;

    void* lock(const AccessType access = AccessType::ReadWrite) override;
    void unlock() override;

private:
    uint32 m_id{0u};
    uint32 m_size{0u};
    VertexBufferLayout m_layout{VertexBufferLayout::Create<>()};
}; // class VertexBuffer

} // namespace jac::graphics::opengl
