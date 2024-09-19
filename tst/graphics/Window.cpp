#include <gtest/gtest.h>
#include <glad/gl.h>

#include <chrono>

#include "jac/print.hpp"
#include "jac/graphics/window.hpp"

namespace
{

auto init_gl() -> bool
{
    if (!gladLoaderLoadGL())
    {
        jac::print_error("Failed to initialize GLAD");
        return false;
    }

    return true;
}

auto draw() -> void
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace

TEST(Graphics, WindowOpenAndClose)
{
    jac::LogLevelCurrent() = jac::LogLevel::Info;

    using namespace jac::graphics;
    using namespace std::chrono;
    using namespace std::chrono_literals;
    using namespace std::this_thread;

    Window window;

    EXPECT_TRUE(init_gl());

    auto duration = 0ms;

    while(window.isAlive())
    {
        time_point start = high_resolution_clock::now();

        draw();

        sleep_for(16ms);

        std::chrono::duration elapsed = high_resolution_clock::now() - start;
        duration += duration_cast<milliseconds>(elapsed);

        if (duration > 10s)
            window.close();

        auto [x, y] = window.getPosition();
        jac::print_info("Window position: ({}, {})", {x, y});

        window.update();
    }
}

TEST(Graphics, MultipleWindows)
{
    using namespace jac::graphics;
    using namespace std::chrono;
    using namespace std::chrono_literals;
    using namespace std::this_thread;

    const Window::params params{
        .width = 400,
        .height = 300
    };

    Window window1(params);
    Window window2(params);

    EXPECT_TRUE(init_gl());

    auto duration = 0ms;

    while(window1.isAlive() && window2.isAlive())
    {
        time_point start = high_resolution_clock::now();

        draw();

        sleep_for(16ms);

        std::chrono::duration elapsed = high_resolution_clock::now() - start;
        duration += duration_cast<milliseconds>(elapsed);

        if (duration > 1s)
        {
            window1.close();
            window2.close();
        }

        window1.update();
        window2.update();
    }
}
