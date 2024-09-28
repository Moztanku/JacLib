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
    Shader(
        const std::string_view vertex_shader,
        const std::string_view fragment_shader
    );
    ~Shader();

    void bind() const override;
    void unbind() const override;

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
