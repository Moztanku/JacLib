#include "jac/graphics/shader.hpp"

#include "jac/print.hpp"

namespace jac::graphics
{

template <typename T>
JAC_IMPL
void ShaderI::setUniform(const std::string& uniform_name, const T& value)
{
    std::optional<int> location =
        get_uniform_location(uniform_name);

    if (location)
    {
        set_uniform(*location, value);
    } else
    {
        jac::print_error("Invalid uniform name: {}", uniform_name);
    }
}

#define INSTANTIATE_SCALAR(T) \
    template \
    JAC_IMPL \
    void ShaderI::setUniform<T>( \
        const std::string&, \
        const T&);

INSTANTIATE_SCALAR(bool)
INSTANTIATE_SCALAR(int)
INSTANTIATE_SCALAR(uint)
INSTANTIATE_SCALAR(float)
INSTANTIATE_SCALAR(double)

#undef INSTANTIATE_SCALAR

#define INSTANTIATE_VEC(T, N) \
    template \
    JAC_IMPL \
    void ShaderI::setUniform<glm::vec<N, T>>( \
        const std::string&, \
        const glm::vec<N, T>&);

#define INSTANTIATE_VECTORS(T) \
    INSTANTIATE_VEC(T, 2) \
    INSTANTIATE_VEC(T, 3) \
    INSTANTIATE_VEC(T, 4)

INSTANTIATE_VECTORS(bool)
INSTANTIATE_VECTORS(int)
INSTANTIATE_VECTORS(uint)
INSTANTIATE_VECTORS(float)
INSTANTIATE_VECTORS(double)

#undef INSTANTIATE_VEC
#undef INSTANTIATE_VECTORS

#define INSTANTIATE_MAT(T, N, M) \
    template \
    JAC_IMPL \
    void ShaderI::setUniform<glm::mat<N, M, T>>( \
        const std::string&, \
        const glm::mat<N, M, T>&);

#define INSTANTIATE_MATRICES(T) \
    INSTANTIATE_MAT(T, 2, 2) \
    INSTANTIATE_MAT(T, 2, 3) \
    INSTANTIATE_MAT(T, 2, 4) \
    INSTANTIATE_MAT(T, 3, 2) \
    INSTANTIATE_MAT(T, 3, 3) \
    INSTANTIATE_MAT(T, 3, 4) \
    INSTANTIATE_MAT(T, 4, 2) \
    INSTANTIATE_MAT(T, 4, 3) \
    INSTANTIATE_MAT(T, 4, 4)

INSTANTIATE_MATRICES(float)
INSTANTIATE_MATRICES(double)

#undef INSTANTIATE_MAT
#undef INSTANTIATE_MATRICES

} // namespace jac::graphics
