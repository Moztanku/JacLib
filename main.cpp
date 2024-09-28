#include "jac/print.hpp"
#include "jac/graphics/window.hpp"
#include "jac/graphics/shader.hpp"

int main()
{
    jac::LogLevelCurrent() = jac::LogLevel::Debug;

    const jac::graphics::Window::params params{
        .width = 400,
        .height = 300
    };

    jac::graphics::Window window(params);
    jac::graphics::Shader shader("vertex", "fragment");

    while(window.isAlive())
    {
        window.bind();

        window.update();
    }

    return 0;
}
