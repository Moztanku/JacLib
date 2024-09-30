/**
 * @file vertexbuffer.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains vertex buffer interface for the graphics API.
 */
#pragma once

#include <glm/vector_relational.hpp>

#include <span>
#include <vector>

#include "jac/types.hpp"
#include "jac/impl/api.hpp"
#include "jac/graphics/common.hpp"

namespace jac::graphics
{

/**
 * @brief Element of a vertex buffer
 */
JAC_API
struct VertexBufferElement
{
    /**
     * @brief Type of the element
     */
    enum class Type
    {
        Float,
        Vec2,
        Vec3,
        Vec4,
        Int
        // ... more types
    };

    /**
     * @brief Get the type of the element from the template type
     * 
     * @tparam T The type of the element
     */
    template <typename T>
    constexpr Type getType()
    {
        if (std::is_same_v<T, float>)
            return Type::Float;
        else if (std::is_same_v<T, glm::vec<2, float>>)
            return Type::Vec2;
        else if (std::is_same_v<T, glm::vec<3, float>>)
            return Type::Vec3;
        else if (std::is_same_v<T, glm::vec<4, float>>)
            return Type::Vec4;
        else if (std::is_same_v<T, int>)
            return Type::Int;
        // ... more types

        return Type::Float;
    }

    /**
     * @brief Construct a new Vertex Buffer Element object
     * 
     * @tparam T The type of the element
     */
    template <typename T>
    VertexBufferElement(const T&)
    : type{getType<T>()}, size{sizeof(T)}
    {}

    size_t size;
    Type type;
};

/**
 * @brief Layout of a vertex buffer
 */
JAC_API
class VertexBufferLayout
{
public:
    /**
     * @brief Create a vertex buffer layout
     * 
     * @tparam Args The types of the elements in the layout
     * @return VertexBufferLayout The created layout
     */
    template <typename ...Args>
    static VertexBufferLayout Create()
    {
        VertexBufferLayout layout;

        layout.m_elements.reserve(sizeof...(Args));

        (layout.m_elements.push_back(Args{}), ...);

        for (const auto& element : layout.m_elements)
        {
            layout.m_stride += element.size;
        }

        return layout;
    }

    /**
     * @brief Get the stride size of the layout
     */
    size_t getStride() const { return m_stride; }

    /**
     * @brief Get the elements of the layout
     */
    const std::vector<VertexBufferElement>& getElements() const { return m_elements; }

private:
    VertexBufferLayout() = default;

    std::vector<VertexBufferElement> m_elements{};
    uint32 m_stride{};
}; // struct VertexBufferLayout

/**
 * @brief Interface for a vertex buffer, to be implemented by the graphics API
 */
JAC_API
struct VertexBufferI
{
    virtual ~VertexBufferI() = default;

    /**
     * @brief Bind the vertex buffer for use
     */
    virtual void bind() const = 0;

    /**
     * @brief Unbind the vertex buffer after use
     */
    virtual void unbind() const = 0;

    /**
     * @brief Returns whether the vertex buffer is bound
     * 
     * @return true If the vertex buffer is bound
     */
    virtual bool isBound() const = 0;

    /**
     * @brief Get the number of vertices in the buffer 
     */
    virtual uint32 getCount() const = 0;

    /**
     * @brief Set the data of the vertex buffer
     * 
     * @param data The data to set
     * @param count The number of vertices in the data
     */
    virtual void setData(const void* data, const uint32 count) = 0;

    /**
     * @brief Set the data of the vertex buffer
     * 
     * @param data The data to set
     */
    virtual void setData(const std::span<std::byte> data) = 0;

    /**
     * @brief Set the layout of the vertex buffer
     * 
     * @param layout The layout to set
     */
    virtual void setLayout(const VertexBufferLayout& layout) = 0;

    /**
     * @brief Get the layout of the vertex buffer
     * 
     * @return VertexBufferLayout The layout of the vertex buffer
     */
    virtual const VertexBufferLayout& getLayout() const = 0;

    /**
     * @brief Release the data of the vertex buffer, called automatically by the derived class destructor
     */
    virtual void destroy() = 0;

    /**
     * @brief Map the vertex buffer to memory. The buffer must be unmapped with unlock() after use.
     *  Use together with getLayout() to calculate the offset of the data and know data types
     * 
     * @param access The type of access to the buffer
     * 
     * @return void* The pointer to the buffer data
     */
    virtual void* lock(const AccessType access = AccessType::ReadWrite) = 0;

    /**
     * @brief Unmap the vertex buffer from memory
     */
    virtual void unlock() = 0;

}; // struct VertexBufferI

} // namespace jac::graphics

// If using the library, include the implementation
//  For now OpenGL is the only implementation, later this will be
//  optionally included based on the graphics APIs selected.
#if !defined(JAC_BUILD_LIB) && defined(JAC_GRAPHICS_OPENGL)
    #include "jac/graphics/apis/opengl/vertexbuffer.hpp"
#endif
