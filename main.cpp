// #include "jac/print.hpp"
#include "jac/graphics/window.hpp"
#include "jac/graphics/shader.hpp"
#include "jac/graphics/indexbuffer.hpp"
#include "jac/graphics/vertexbuffer.hpp"

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

    unique_ptr<ShaderI> shader =
        make_unique<opengl::Shader>("test.glsl");

    shader->setUniform("u_Color", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

    // unique_ptr<VertexBufferI> vbo{new opengl::VertexBuffer<>()};
    // unique_ptr<IndexBufferI> ibo =
    //     make_unique<opengl::IndexBuffer<>>();

    // unique_ptr<VertexBufferI> vbo =
    //     make_unique<opengl::VertexBuffer<>>();

    return 0;
}
