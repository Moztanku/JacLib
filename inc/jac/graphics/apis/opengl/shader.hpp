/**
 * @file opengl/shader.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains the OpenGL implementation of the Shader interface.
 */
#pragma once

#include "jac/graphics/shader.hpp"

#include <string_view>
#include <unordered_map>

namespace jac::graphics::opengl
{

/**
 * @brief OpenGL implementation of the Shader interface
 */
JAC_API
class Shader : public jac::graphics::ShaderI
{
public:
    /**
     * @brief Construct a new Shader object from vertex and fragment shader sources
     * 
     * @param vertex_shader The source of the vertex shader
     * @param fragment_shader The source of the fragment shader
     */
    Shader(
        const std::string_view vertex_shader,
        const std::string_view fragment_shader
    );

    /**
     * @brief Construct a new Shader object from a combined shader source
     *  The combined shader source should contain both the vertex and fragment shaders
     *  in the same source marked by the tags: "#vertex" and "#fragment"
     * 
     * @param combined_shader The source of the combined shader
     */
    Shader(
        const std::string_view combined_shader
    );

    /**
     * @brief Destroy the Shader object and free the shader program
     */
    ~Shader();

    void bind() const override;
    void unbind() const override;

    bool isBound() const override;

private:
    uint m_id;
    std::unordered_map<std::string, int> m_uniforms{};

    std::optional<int> get_uniform_location(const std::string&) override;

    void set_uniform(const int, const bool)   override;
    void set_uniform(const int, const int)    override;
    void set_uniform(const int, const uint)   override;
    void set_uniform(const int, const float)  override;
    void set_uniform(const int, const double) override;

    void set_uniform(const int, const glm::vec<2, bool>&)   override;
    void set_uniform(const int, const glm::vec<2, int>&)    override;
    void set_uniform(const int, const glm::vec<2, uint>&)   override;
    void set_uniform(const int, const glm::vec<2, float>&)  override;
    void set_uniform(const int, const glm::vec<2, double>&) override;

    void set_uniform(const int, const glm::vec<3, bool>&)   override;
    void set_uniform(const int, const glm::vec<3, int>&)    override;
    void set_uniform(const int, const glm::vec<3, uint>&)   override;
    void set_uniform(const int, const glm::vec<3, float>&)  override;
    void set_uniform(const int, const glm::vec<3, double>&) override;

    void set_uniform(const int, const glm::vec<4, bool>&)   override;
    void set_uniform(const int, const glm::vec<4, int>&)    override;
    void set_uniform(const int, const glm::vec<4, uint>&)   override;
    void set_uniform(const int, const glm::vec<4, float>&)  override;
    void set_uniform(const int, const glm::vec<4, double>&) override;

    void set_uniform(const int, const glm::mat<2, 2, float>&) override;
    void set_uniform(const int, const glm::mat<2, 3, float>&) override;
    void set_uniform(const int, const glm::mat<2, 4, float>&) override;
    
    void set_uniform(const int, const glm::mat<3, 2, float>&) override;
    void set_uniform(const int, const glm::mat<3, 3, float>&) override;
    void set_uniform(const int, const glm::mat<3, 4, float>&) override;

    void set_uniform(const int, const glm::mat<4, 2, float>&) override;
    void set_uniform(const int, const glm::mat<4, 3, float>&) override;
    void set_uniform(const int, const glm::mat<4, 4, float>&) override;

    void set_uniform(const int, const glm::mat<2, 2, double>&) override;
    void set_uniform(const int, const glm::mat<2, 3, double>&) override;
    void set_uniform(const int, const glm::mat<2, 4, double>&) override;
    
    void set_uniform(const int, const glm::mat<3, 2, double>&) override;
    void set_uniform(const int, const glm::mat<3, 3, double>&) override;
    void set_uniform(const int, const glm::mat<3, 4, double>&) override;

    void set_uniform(const int, const glm::mat<4, 2, double>&) override;
    void set_uniform(const int, const glm::mat<4, 3, double>&) override;
    void set_uniform(const int, const glm::mat<4, 4, double>&) override;
}; // class Shader

} // namespace jac::graphics::opengl
