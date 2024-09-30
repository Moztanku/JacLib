#include "jac/graphics/common.hpp"

#if defined(JAC_GRAPHICS_OPENGL)
    #include "jac/graphics/apis/opengl/init.hpp"
#endif

#if defined(JAC_GRAPHICS_VULKAN)
    #include "jac/graphics/apis/vulkan/init.hpp"
#endif

#include "jac/print.hpp"

namespace
{

constexpr jac::graphics::API default_api =
#if defined(JAC_GRAPHICS_OPENGL)
    jac::graphics::API::OpenGL;
#elif defined(JAC_GRAPHICS_VULKAN)
    jac::graphics::API::Vulkan;
#else
    jac::graphics::API::Unknown;
#endif

auto init_invalid() -> bool
{
    jac::print_error("Unavailable graphics API selected");

    return false;
}

auto terminate_invalid() -> void
{
    jac::print_error("Unavailable graphics API selected");

    return;
}

} // namespace

namespace jac::graphics
{

JAC_API
auto CurrentAPI() -> API&
{
    static API api = default_api;

    return api;
}

JAC_API
auto InitAPI() -> bool
{
    switch (CurrentAPI())
    {
        #if defined(JAC_GRAPHICS_OPENGL)
        case API::OpenGL:
            return opengl::init_gl();
        #endif

        #if defined(JAC_GRAPHICS_VULKAN)
        case API::Vulkan:
            return vulkan::init_vk();
        #endif

        default:
            return init_invalid();
    }
}

JAC_API
auto TerminateAPI() -> void
{
    switch (CurrentAPI())
    {
        #if defined(JAC_GRAPHICS_OPENGL)
        case API::OpenGL:
            return opengl::terminate_gl();
        #endif

        #if defined(JAC_GRAPHICS_VULKAN)
        case API::Vulkan:
            return vulkan::terminate_vk();
        #endif

        default:
            return terminate_invalid();
    }
}

} // namespace jac::graphics
