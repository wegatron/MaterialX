#include "glfw_window.h"
#include <iostream>

namespace x_engine
{    
    namespace samples
    {
        void windowSizeCallback(GLFWwindow * window, int width, int height)
        {
            //window->
            auto glfw_window = reinterpret_cast<GlfwWindow *>(glfwGetWindowUserPointer(window));
            glfw_window->callWindowSizeCallback(width, height);
        }
        
        GlfwWindow::GlfwWindow(const Window::Properties &properties)    
            : Window(properties)
        {
            glfwInit();
            glfwWindowHint(GLFW_RESIZABLE, properties.resizable ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

            // Specify GL version and profile.
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);            

            handle_ = glfwCreateWindow(properties.extent.width, properties.extent.height,
                                       properties.title.c_str(), nullptr, nullptr);
            glfwSetWindowUserPointer(handle_, this);
            glfwSetWindowSizeCallback(handle_, windowSizeCallback);
            glfwMakeContextCurrent(handle_);         
        }

        GlfwWindow::~GlfwWindow()
        {	    
            glfwDestroyWindow(handle_);
        }

        bool GlfwWindow::should_close()
        {
            return glfwWindowShouldClose(handle_);
        }

        void GlfwWindow::process_events()
        {
            glfwPollEvents();
        }

        void GlfwWindow::close()
        {
            glfwSetWindowShouldClose(handle_, GLFW_TRUE);
        }

        float GlfwWindow::get_dpi_factor() const
        {
            int width, height;
            glfwGetFramebufferSize(handle_, &width, &height);

            int width_window, height_window;
            glfwGetWindowSize(handle_, &width_window, &height_window);

            return static_cast<float>(width) / static_cast<float>(width_window);
        }

        float GlfwWindow::get_content_scale_factor() const
        {
            float x_scale, y_scale;
            glfwGetWindowContentScale(handle_, &x_scale, &y_scale);

            return x_scale;
        }
    }
}
