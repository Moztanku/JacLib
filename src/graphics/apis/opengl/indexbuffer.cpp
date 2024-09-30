#include "jac/graphics/apis/opengl/indexbuffer.hpp"

#include <glad/gl.h>

namespace jac::graphics::opengl
{

template <BufferType Type>
JAC_API
IndexBuffer<Type>::~IndexBuffer()
{
    destroy();
}

template <BufferType Type>
JAC_API
IndexBuffer<Type>::IndexBuffer(IndexBuffer&& other)
    : m_id{other.m_id}, m_count{other.m_count}
{
    other.m_id = 0u;
    other.m_count = 0u;
}

template <BufferType Type>
JAC_API
auto IndexBuffer<Type>::operator=(IndexBuffer&& other) -> IndexBuffer&
{
    if (this != &other)
    {
        glDeleteBuffers(1, &m_id);

        m_id = other.m_id;
        m_count = other.m_count;

        other.m_id = 0u;
        other.m_count = 0u;
    }

    return *this;
}

template <BufferType Type>
JAC_API
void IndexBuffer<Type>::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

template <BufferType Type>
JAC_API
void IndexBuffer<Type>::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

template <BufferType Type>
JAC_API
bool IndexBuffer<Type>::isBound() const
{
    if (m_id == 0u)
        return false;

    int current_id;
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &current_id);

    return static_cast<uint>(current_id) == m_id;
}

template <BufferType Type>
JAC_API
uint32 IndexBuffer<Type>::getCount() const
{
    return m_count;
}

template <BufferType Type>
JAC_API
void IndexBuffer<Type>::setData(const uint32* data, const uint32 count)
{
    destroy();

    glGenBuffers(1, &m_id);

    m_count = count;

    bind();

    constexpr auto USAGE =
        Type == BufferType::Static  ? GL_STATIC_DRAW  :
        Type == BufferType::Dynamic ? GL_DYNAMIC_DRAW :
              /*BufferType::Stream*/  GL_STREAM_DRAW  ;

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        count * sizeof(uint32),
        data,
        USAGE
    );
}

template <BufferType Type>
JAC_API
void IndexBuffer<Type>::setData(const std::span<uint32> data)
{
    setData(data.data(), static_cast<uint32>(data.size()));
}

template <BufferType Type>
JAC_API
void IndexBuffer<Type>::destroy()
{
    if (m_id != 0u)
    {
        glDeleteBuffers(1, &m_id);
        m_id = 0u;
        m_count = 0u;
    }
}

template <BufferType Type>
JAC_API
uint32* IndexBuffer<Type>::lock(const AccessType access)
{
    bind();

    const auto ACCESS =
        access == AccessType::Read      ? GL_READ_ONLY  :
        access == AccessType::Write     ? GL_WRITE_ONLY :
                /*AccessType::ReadWrite*/ GL_READ_WRITE ;

    void* ptr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, ACCESS);

    return static_cast<uint32*>(ptr);
}

template <BufferType Type>
JAC_API
void IndexBuffer<Type>::unlock()
{
    bind();

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

template class
JAC_API
IndexBuffer<BufferType::Static>;

template class
JAC_API
IndexBuffer<BufferType::Dynamic>;

template class
JAC_API
IndexBuffer<BufferType::Stream>;

} // namespace jac::graphics::opengl
