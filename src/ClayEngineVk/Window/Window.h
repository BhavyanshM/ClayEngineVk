#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <string>
namespace ClayEngineVk
{
    class Window
    {
    public:
        Window(int width, int height, std::string name);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        bool ShouldClose();

        void PollEvents();

        void InitWindow();

        void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

        VkExtent2D GetExtent() { return {static_cast<uint32_t>(_width), static_cast<uint32_t>(_height)}; }

        bool FrameBufferResized() { return _frameBufferResize; }

        void ResetFrameBufferResizedFlag() { _frameBufferResize = false; }

        // bool ShouldClose() { return glfwWindowShouldClose(_window); }

        // void PollEvents() { glfwPollEvents(); }

        // void SwapBuffers() { glfwSwapBuffers(_window); }

    private:

        static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);

        int _width;
        int _height;
        std::string _name;
        bool _frameBufferResize = false;

        GLFWwindow* _window;
    };
}