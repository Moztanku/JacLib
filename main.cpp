#include <glad/gl.h>

#include <vector>
#include <thread>
#include <algorithm>

#include "jac/print.hpp"
#include "jac/graphics/window.hpp"

void init_gl()
{
    if (!gladLoaderLoadGL())
    {
        jac::print_error("Failed to initialize GLAD");
    }
}

void draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw2()
{
    glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    using namespace jac;
    using namespace jac::graphics;

    LogLevelCurrent() = LogLevel::Debug;

    const Window::params params{
        .width = 400,
        .height = 300
    };

    std::vector<std::thread> threads(2);
    std::mutex mutex;

    for (auto &t : threads)
    {
        t = std::thread([params, &mutex](){

            mutex.lock();
            Window window(params);

            init_gl();
            mutex.unlock();

            double frame_time_ms = 1000.0 / 60.0;

            while(window.isAlive())
            {
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(static_cast<int>(frame_time_ms))
                );
                
                std::lock_guard lock(mutex);
                window.bind();

                draw();

                window.update();
                window.unbind();
            }
        });
    }

    for (auto &t : threads)
        t.join();

    // std::vector<Window*> windows(10, nullptr);

    // for (auto &window : windows)
    //     window = new Window(params);

    // init_gl();

    // while(std::all_of(windows.begin(), windows.end(), [](const auto& window){
    //     return window->isAlive();
    // }))
    // {
    //     for (size_t i = 0; i < windows.size(); i++)
    //     {
    //         windows[i]->bind();

    //         if (i % 2 == 0)
    //             draw();
    //         else
    //             draw2();

    //         windows[i]->update();
    //     }
    // }

    // for (auto &window : windows)
    //     delete window;

    return 0;
}
