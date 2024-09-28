#include "jac/graphics/apis/opengl/shader.hpp"
#include "jac/graphics/apis/opengl/init.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace
{

} // namespace

namespace jac::graphics::opengl
{

JAC_API
Shader::Shader(
    const std::string_view vertex_shader,
    const std::string_view fragment_shader
)
{
    init_gl();
    
    m_id = glCreateProgram();
}

JAC_API
Shader::~Shader()
{
    glDeleteProgram(m_id);
}

JAC_API
void Shader::bind() const
{
    glUseProgram(m_id);
}

JAC_API
void Shader::unbind() const
{
    glUseProgram(0);
}

JAC_API
std::optional<int> Shader::get_uniform_location(const std::string& location)
{
    auto it = m_uniforms.find(location);

    if (it == m_uniforms.end())
    {
        const int loc = glGetUniformLocation(m_id, location.c_str());

        if (loc == -1)
            return std::nullopt;

        m_uniforms[location] = loc;

        return loc;
    }

    return it->second;
}

JAC_API void Shader::set_uniform(const int loc, const bool   v) { glUniform1i (loc, v); }
JAC_API void Shader::set_uniform(const int loc, const int    v) { glUniform1i (loc, v); }
JAC_API void Shader::set_uniform(const int loc, const uint   v) { glUniform1ui(loc, v); }
JAC_API void Shader::set_uniform(const int loc, const float  v) { glUniform1f (loc, v); }
JAC_API void Shader::set_uniform(const int loc, const double v) { glUniform1d (loc, v); }

JAC_API void Shader::set_uniform(const int loc, const glm::vec<2, bool>&   v) { glUniform2i (loc, v.x, v.y); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<2, int>&    v) { glUniform2i (loc, v.x, v.y); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<2, uint>&   v) { glUniform2ui(loc, v.x, v.y); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<2, float>&  v) { glUniform2f (loc, v.x, v.y); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<2, double>& v) { glUniform2d (loc, v.x, v.y); }

JAC_API void Shader::set_uniform(const int loc, const glm::vec<3, bool>&   v) { glUniform3i (loc, v.x, v.y, v.z); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<3, int>&    v) { glUniform3i (loc, v.x, v.y, v.z); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<3, uint>&   v) { glUniform3ui(loc, v.x, v.y, v.z); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<3, float>&  v) { glUniform3f (loc, v.x, v.y, v.z); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<3, double>& v) { glUniform3d (loc, v.x, v.y, v.z); }

JAC_API void Shader::set_uniform(const int loc, const glm::vec<4, bool>&   v) { glUniform4i (loc, v.x, v.y, v.z, v.w); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<4, int>&    v) { glUniform4i (loc, v.x, v.y, v.z, v.w); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<4, uint>&   v) { glUniform4ui(loc, v.x, v.y, v.z, v.w); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<4, float>&  v) { glUniform4f (loc, v.x, v.y, v.z, v.w); }
JAC_API void Shader::set_uniform(const int loc, const glm::vec<4, double>& v) { glUniform4d (loc, v.x, v.y, v.z, v.w); }

JAC_API void Shader::set_uniform(const int loc, const glm::mat<2, 2, float>& v) { glUniformMatrix2fv  (loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<2, 3, float>& v) { glUniformMatrix2x3fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<2, 4, float>& v) { glUniformMatrix2x4fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
    
JAC_API void Shader::set_uniform(const int loc, const glm::mat<3, 2, float>& v) { glUniformMatrix3x2fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<3, 3, float>& v) { glUniformMatrix3fv  (loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<3, 4, float>& v) { glUniformMatrix3x4fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }

JAC_API void Shader::set_uniform(const int loc, const glm::mat<4, 2, float>& v) { glUniformMatrix4x2fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<4, 3, float>& v) { glUniformMatrix4x3fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<4, 4, float>& v) { glUniformMatrix4fv  (loc, 1, GL_FALSE, glm::value_ptr(v)); }

JAC_API void Shader::set_uniform(const int loc, const glm::mat<2, 2, double>& v) { glUniformMatrix2dv  (loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<2, 3, double>& v) { glUniformMatrix2x3dv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<2, 4, double>& v) { glUniformMatrix2x4dv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
    
JAC_API void Shader::set_uniform(const int loc, const glm::mat<3, 2, double>& v) { glUniformMatrix3x2dv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<3, 3, double>& v) { glUniformMatrix3dv  (loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<3, 4, double>& v) { glUniformMatrix3x4dv(loc, 1, GL_FALSE, glm::value_ptr(v)); }

JAC_API void Shader::set_uniform(const int loc, const glm::mat<4, 2, double>& v) { glUniformMatrix4x2dv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<4, 3, double>& v) { glUniformMatrix4x3dv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
JAC_API void Shader::set_uniform(const int loc, const glm::mat<4, 4, double>& v) { glUniformMatrix4dv  (loc, 1, GL_FALSE, glm::value_ptr(v)); }

} // namespace jac::graphics::opengl
