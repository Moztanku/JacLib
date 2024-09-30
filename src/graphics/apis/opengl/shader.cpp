#include "jac/graphics/apis/opengl/shader.hpp"

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <filesystem>

#include "jac/print.hpp"

namespace
{

auto read_file(const std::string_view path) -> std::string
{
    std::ifstream file(path.data(), std::ios::in);

    if (!file.is_open())
        return "";

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

struct ShaderSource
{
    std::string vertex;
    std::string fragment;
};

auto split_combined_shader(const std::string_view combined_shader) -> ShaderSource
{
    constexpr std::string_view vertex_tag = "#vertex";
    constexpr std::string_view fragment_tag = "#fragment";

    std::string vertex_shader;
    std::string fragment_shader;

    const size_t vertex_pos = combined_shader.find(vertex_tag);
    const size_t fragment_pos = combined_shader.find(fragment_tag);

    if (vertex_pos == std::string::npos || fragment_pos == std::string::npos)
        return { "", "" };

    if (vertex_pos < fragment_pos)
    {
        vertex_shader = combined_shader.substr(
            vertex_pos + vertex_tag.size(),
            fragment_pos - (vertex_pos + vertex_tag.size())    
        );

        fragment_shader = combined_shader.substr(
            fragment_pos + fragment_tag.size()
        );
    }
    else
    {
        vertex_shader = combined_shader.substr(
            vertex_pos + vertex_tag.size()
        );

        fragment_shader = combined_shader.substr(
            fragment_pos + fragment_tag.size(),
            vertex_pos - (fragment_pos + fragment_tag.size())
        );
    }

    return ShaderSource{
        .vertex = std::move(vertex_shader),
        .fragment = std::move(fragment_shader)
    };
}

template <uint Type>
auto compile_shader(const std::string_view source) -> uint
{
    constexpr std::string_view type_name = 
        Type == GL_VERTEX_SHADER ? "vertex" : "fragment";

    if constexpr(Type != GL_VERTEX_SHADER && Type != GL_FRAGMENT_SHADER)
    {
        jac::print_error("Invalid shader type");

        return 0;
    }

    if (source.empty())
    {
        jac::print_error("Empty {} shader source", type_name);

        return 0;
    }

    const uint id = glCreateShader(Type);

    const char* src = source.data();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        std::string message(length, '\0');
        glGetShaderInfoLog(id, length, &length, message.data());

        jac::print_error(
            "Failed to compile {} shader:\n{}",
            {type_name, message}
        );

        return 0;
    }

    return id;
}

auto compile_shader_program(const ShaderSource& source) -> uint
{
    const uint program = glCreateProgram();

    const uint vertex   = compile_shader<GL_VERTEX_SHADER>(source.vertex);
    const uint fragment = compile_shader<GL_FRAGMENT_SHADER>(source.fragment);

    if (vertex == 0 || fragment == 0)
    {
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return 0;
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

} // namespace

namespace jac::graphics::opengl
{

JAC_API
Shader::Shader(
    const std::string_view vertex_shader,
    const std::string_view fragment_shader
)
{
    const ShaderSource source = 
    {
        .vertex = read_file(vertex_shader),
        .fragment = read_file(fragment_shader)
    };

    m_id = compile_shader_program(source);
}

JAC_API
Shader::Shader(
    const std::string_view combined_shader
)
{
    const ShaderSource source = split_combined_shader(
        read_file(combined_shader)
    );

    m_id = compile_shader_program(source);
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
bool Shader::isBound() const
{
    int current_id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current_id);

    return static_cast<uint>(current_id) == m_id;
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
