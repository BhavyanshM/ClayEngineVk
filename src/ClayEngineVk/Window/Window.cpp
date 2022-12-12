#include "Window/Window.h"

namespace ClayEngineVk
{
    Window::Window(int width, int height, std::string name)
        : _width(width), _height(height), _name(name)
    {
        InitWindow();
    }

    Window::~Window()
    {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(_window);
    }

    void Window::InitWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
    }
}