#include "jac/graphics/window.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "jac/types.hpp"
#include "jac/print.hpp"

namespace
{

auto init_glfw() -> bool
{
    if (!glfwInit())
    {
        int error_code = glfwGetError(nullptr);

        jac::print("Failed to initialize GLFW: ", error_code);

        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

auto create_window(const jac::graphics::Window::params& params) -> owner<GLFWwindow>
{
    int monitor_count;
    GLFWmonitor* monitor = nullptr;

    if (params.fullscreen)
    {
        GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);

        if (params.monitor >= monitor_count)
        {
            jac::print_error(
                "Monitor index out of range: {} >= {}",
                {params.monitor, monitor_count});
            return nullptr;
        }

        monitor = monitors[params.monitor];
    }

    return glfwCreateWindow(
        params.width,
        params.height,
        params.title.c_str(),
        monitor,
        nullptr
    );
}

} // namespace

namespace jac::graphics
{

JAC_IMPL
Window::Window() noexcept : Window(params{})
{}

JAC_IMPL
Window::Window(const params& params) noexcept
{
    // If s_window_count is 0 then it's the first window, so we need to initialize GLFW
    if (s_window_count == 0 && !init_glfw())
        return;

    m_window = create_window(params);

    if (m_window)
        s_window_count++;
    else
    {
        jac::print_error("Failed to create window");

        if (s_window_count == 0)
            glfwTerminate();

        return;
    }

    glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x, int y){
        
    });

    bind();
}

JAC_IMPL
Window::~Window() noexcept
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        s_window_count--;
    }

    if (s_window_count == 0)
        glfwTerminate();
}

JAC_IMPL
Window::Window(Window&& other) noexcept
    : m_window{other.m_window}
{
    other.m_window = nullptr;
}

JAC_IMPL
Window& Window::operator=(Window&& other) noexcept
{
    if (this != &other)
    {
        m_window = other.m_window;
        other.m_window = nullptr;
    }

    return *this;
}

JAC_IMPL
void Window::bind() const noexcept
{
    glfwMakeContextCurrent(m_window);
}

JAC_IMPL
void Window::unbind() const noexcept
{
    glfwMakeContextCurrent(nullptr);
}

JAC_IMPL
void Window::update() noexcept
{
    bind();
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

JAC_IMPL
void Window::close() noexcept
{
    bind();
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

JAC_IMPL
bool Window::isAlive() const noexcept
{
    return glfwWindowShouldClose(m_window) == 0;
}

JAC_IMPL
std::pair<uint32_t, uint32_t> Window::getPosition() const noexcept
{
    int x, y;
    glfwGetWindowPos(m_window, &x, &y);

    return {
        static_cast<uint32_t>(x),
        static_cast<uint32_t>(y)
    };
}

} // namespace jac::graphics
