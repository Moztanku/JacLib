#include "jac/graphics/apis/opengl/vertexbuffer.hpp"

#include <glad/gl.h>

namespace jac::graphics::opengl
{

template <BufferType Type>
JAC_API
VertexBuffer<Type>::~VertexBuffer()
{
    destroy();
}

template <BufferType Type>
JAC_API
VertexBuffer<Type>::VertexBuffer(VertexBuffer&& other)
    : m_id{other.m_id}, m_size{other.m_size}
{
    other.m_id = 0u;
    other.m_size = 0u;
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::operator=(VertexBuffer&& other) -> VertexBuffer&
{
    if (this != &other)
    {
        glDeleteBuffers(1, &m_id);

        m_id = other.m_id;
        m_size = other.m_size;

        other.m_id = 0u;
        other.m_size = 0u;
    }

    return *this;
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::bind() const -> void
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::unbind() const -> void
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::isBound() const -> bool
{
    if (m_id == 0u)
        return false;

    int current_id;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &current_id);

    return static_cast<uint>(current_id) == m_id;
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::getCount() const -> uint32
{
    return m_size / m_layout.getStride();
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::setData(const void* data, const uint32 size) -> void
{
    destroy();

    glGenBuffers(1, &m_id);

    m_size = size;

    bind();

    constexpr auto USAGE =
        Type == BufferType::Static  ? GL_STATIC_DRAW  :
        Type == BufferType::Dynamic ? GL_DYNAMIC_DRAW :
              /*BufferType::Stream*/  GL_STREAM_DRAW  ;

    glBufferData(
        GL_ARRAY_BUFFER,
        m_size,
        data,
        USAGE
    );
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::setData(const std::span<std::byte> data) -> void
{
    setData(
        static_cast<void*>(data.data()),
        static_cast<uint32>(data.size())
    );
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::setLayout(const VertexBufferLayout& layout) -> void
{
    m_layout = layout;
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::getLayout() const -> const VertexBufferLayout&
{
    return m_layout;
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::destroy() -> void
{
    if (m_id != 0u)
    {
        glDeleteBuffers(1, &m_id);
        m_id = 0u;
        m_size = 0u;
    }
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::lock(const AccessType access) -> void*
{
    bind();

    const auto ACCESS =
        access == AccessType::Read      ? GL_READ_ONLY  :
        access == AccessType::Write     ? GL_WRITE_ONLY :
                /*AccessType::ReadWrite*/ GL_READ_WRITE ;
    
    void* ptr = glMapBuffer(GL_ARRAY_BUFFER, ACCESS);

    return ptr;
}

template <BufferType Type>
JAC_API
auto VertexBuffer<Type>::unlock() -> void
{
    bind();

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

template class
JAC_API
VertexBuffer<BufferType::Static>;

template class
JAC_API
VertexBuffer<BufferType::Dynamic>;

template class
JAC_API
VertexBuffer<BufferType::Stream>;

} // namespace jac::graphics::opengl
