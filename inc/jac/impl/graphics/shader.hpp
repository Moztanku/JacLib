#pragma once

#include <glm/vector_relational.hpp>
#include <glm/matrix.hpp>

#include <cstdint>
#include <optional>
#include <string>

#include "jac/impl/api.hpp"

namespace jac::graphics::impl
{

struct Shader_Base
{
protected:
    // Function to get the location of a uniform in the shader
    virtual std::optional<int> get_uniform_location(const std::string&) = 0;

    // Uniforms
    // Scalars
    virtual void set_uniform(const int, const bool) = 0;
    virtual void set_uniform(const int, const int) = 0;
    virtual void set_uniform(const int, const uint) = 0;
    virtual void set_uniform(const int, const float) = 0;
    virtual void set_uniform(const int, const double) = 0;

    // Vectors
    virtual void set_uniform(const int, const glm::vec<2, bool>&) = 0;
    virtual void set_uniform(const int, const glm::vec<2, int>&) = 0;
    virtual void set_uniform(const int, const glm::vec<2, uint>&) = 0;
    virtual void set_uniform(const int, const glm::vec<2, float>&) = 0;
    virtual void set_uniform(const int, const glm::vec<2, double>&) = 0;

    virtual void set_uniform(const int, const glm::vec<3, bool>&) = 0;
    virtual void set_uniform(const int, const glm::vec<3, int>&) = 0;
    virtual void set_uniform(const int, const glm::vec<3, uint>&) = 0;
    virtual void set_uniform(const int, const glm::vec<3, float>&) = 0;
    virtual void set_uniform(const int, const glm::vec<3, double>&) = 0;

    virtual void set_uniform(const int, const glm::vec<4, bool>&) = 0;
    virtual void set_uniform(const int, const glm::vec<4, int>&) = 0;
    virtual void set_uniform(const int, const glm::vec<4, uint>&) = 0;
    virtual void set_uniform(const int, const glm::vec<4, float>&) = 0;
    virtual void set_uniform(const int, const glm::vec<4, double>&) = 0;

    // Matrices (float)
    virtual void set_uniform(const int, const glm::mat<2, 2, float>&) = 0;
    virtual void set_uniform(const int, const glm::mat<2, 3, float>&) = 0;
    virtual void set_uniform(const int, const glm::mat<2, 4, float>&) = 0;

    virtual void set_uniform(const int, const glm::mat<3, 2, float>&) = 0;
    virtual void set_uniform(const int, const glm::mat<3, 3, float>&) = 0;
    virtual void set_uniform(const int, const glm::mat<3, 4, float>&) = 0;

    virtual void set_uniform(const int, const glm::mat<4, 2, float>&) = 0;
    virtual void set_uniform(const int, const glm::mat<4, 3, float>&) = 0;
    virtual void set_uniform(const int, const glm::mat<4, 4, float>&) = 0;

    // Matrices (double)
    virtual void set_uniform(const int, const glm::mat<2, 2, double>&) = 0;
    virtual void set_uniform(const int, const glm::mat<2, 3, double>&) = 0;
    virtual void set_uniform(const int, const glm::mat<2, 4, double>&) = 0;

    virtual void set_uniform(const int, const glm::mat<3, 2, double>&) = 0;
    virtual void set_uniform(const int, const glm::mat<3, 3, double>&) = 0;
    virtual void set_uniform(const int, const glm::mat<3, 4, double>&) = 0;

    virtual void set_uniform(const int, const glm::mat<4, 2, double>&) = 0;
    virtual void set_uniform(const int, const glm::mat<4, 3, double>&) = 0;
    virtual void set_uniform(const int, const glm::mat<4, 4, double>&) = 0;
};

} // namespace jac::graphics::impl
