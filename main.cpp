// #include "jac/print.hpp"
#include "jac/graphics/window.hpp"
#include "jac/graphics/shader.hpp"
#include "jac/graphics/indexbuffer.hpp"

#include "jac/graphics/apis/opengl/init.hpp"

#include <glad/gl.h>

#include <iostream>

int main()
{
    using namespace jac::graphics;
    // jac::LogLevelCurrent() = jac::LogLevel::Debug;

    // const jac::graphics::Window::params params{
    //     .width = 400,
    //     .height = 300
    // };

    Window window;

    // jac::graphics::Window window(params);
    // jac::graphics::Shader shader("vertex", "fragment");

    // while(window.isAlive())
    // {
    //     window.bind();

    //     window.update();
    // }

    InitAPI();

    unique_ptr<ShaderI> shader = make_unique<opengl::Shader>("test.glsl");

    return 0;
}
