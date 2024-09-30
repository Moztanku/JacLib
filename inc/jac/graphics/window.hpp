/**
 * @file window.hpp
 * @author Moztanku (mostankpl@gmail.com)
 * @brief This file contains the Window class for creating windows (contexts) for rendering.
 */
#pragma once

#include <memory>
#include <string>
#include <thread>
#include <atomic>

#include "jac/impl/api.hpp"

#include <iostream>

/**
 * @brief Forward declaration of GLFWwindow.
 */
class GLFWwindow;

namespace jac::graphics
{

/**
 * @brief Class for creating windows (contexts) for rendering.
 * 
 * This class is used to create windows for rendering. It uses GLFW to create and manage windows.
 * 
 * Typically it should look like this:
 * @code {.cpp}
 *  #include <jac/graphics/window.hpp>
 * 
 *  int main()
 *  {
 *      jac::graphics::Window window;
 * 
 *      while(window.isAlive())
 *      {
 *          // Rendering code here
 * 
 *          if (some condition)
 *              window.close();
 * 
 *          window.update();
 *      }
 *  }
 * @endcode
 */
JAC_API
class Window
{
    public:
        /** @brief Parameters for creating a window. */
        struct params
        {
            /** @brief The title of the window. Default is "JAC Window". */
            std::string title{"JAC Window"};

            /** @brief The width of the window. Default is 1280. */
            uint32_t width{1280};
            /** @brief The height of the window. Default is 720. */
            uint32_t height{720};

            /** @brief Whether the window is resizable. Default is false. */
            bool resizable{false};

            /** @brief Whether the window is fullscreen. Default is false. */
            bool fullscreen{false};
            /** @brief The monitor to use for fullscreen. Default is 0 (primary monitor). */
            size_t monitor{0};
        };

        /** @brief Create a window with default parameters. */
        Window() noexcept;
        /** @brief Create a window with custom parameters.
         * 
         * @param params The parameters for creating the window.
         */
        Window(const params& params) noexcept;

        ~Window() noexcept;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        
        Window(Window&&) noexcept;
        Window& operator=(Window&&) noexcept;

        /**
         * @brief Bind the current window for rendering.
         * 
         * This function is necessary when using multiple windows. It binds the current window to be used
         * as a context for rendering. New windows are automatically bound when created.
         */
        void bind() const noexcept;

        /**
         * @brief Unbind the current window.
         * 
         * This function is necessary when rendering from multiple threads. It unbinds the current window so that
         * window in another thread can be bound. This should be called after rendering is done and is not thread-safe.
         * 
         * Requires additional synchronization if used in a multithreaded environment.
         * 
         * Example:
         * @code {.cpp}
         * 
         *  std::vector<std::thread> threads(2);
         *  std::mutex mutex;
         * 
         *  for (auto &t : threads)
         *      t = std::thread([params, &mutex](){
         *          // Each thread has its own window
         *          mutex.lock();
         *          Window window;
         * 
         *          init_gl();
         *          mutex.unlock();
         * 
         *          while(window.isAlive())
         *          {
         *              // Do other stuff, prepare for rendering
         * 
         *              std::lock_guard lock(mutex);
         * 
         *              // Bind so current thread can render to the window
         *              window.bind();
         * 
         *              Render_stuff();
         * 
         *              window.update();
         * 
         *              // Unbind so other threads can render to their windows
         *              window.unbind();
         *          }
         */
        void unbind() const noexcept;

        /**
         * @brief Update the window.
         * 
         * This function should be called every frame to update the window.
         * It will poll events and swap buffers.
         */
        void update() noexcept;

        /**
         * @brief Close the window. Needs update to take effect.
         */
        void close() noexcept;

        /**
         * @brief Check if the window is alive.
         * 
         * @return True if the window is alive, false otherwise.
         */
        bool isAlive() const noexcept;

        std::pair<uint32_t, uint32_t> getPosition() const noexcept;
    private:
        /** @brief The GLFW window handle. */
        GLFWwindow* m_window;

        /**
         * @brief The number of windows currently open.
         * 
         * This is used to init GLFW when the first window is created and terminate GLFW when the last window is destroyed.
         */
        inline static std::atomic_uint32_t s_window_count{0};
};

} // namespace jac::graphics
