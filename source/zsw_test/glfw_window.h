#pragma once

#include <GLFW/glfw3.h>
#include "window.h"
#include <functional>

namespace x_engine
{
    namespace samples{
        class GlfwWindow : public Window
        {
        public:
            GlfwWindow(const Window::Properties &properties);

            ~GlfwWindow();

            bool should_close() override;

            void process_events() override;

            void close() override;

            float get_dpi_factor() const override;

            float get_content_scale_factor() const override;

            void * get_handle() override { return handle_; }

            void setWindowSizeCallback(std::function<void(int, int)> &&cb)
            {
                window_size_cb_ = std::move(cb);
            }

            void callWindowSizeCallback(int width, int height)
            {
                window_size_cb_(width, height);
            }

        private:
            GLFWwindow *handle_{nullptr};
            std::function<void(int, int)> window_size_cb_;
        };
    }
}
