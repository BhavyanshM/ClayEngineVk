#include "Core/Core.h"
#include "Window/Window.h"
#include "Pipeline/Pipeline.h"

#include <cstdlib>
#include <iostream>

namespace ClayEngineVk
{
    class ClayEditorVk
    {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void Run()
        {

            while (!window.ShouldClose())
            {
                window.PollEvents();
            }
        }

    private:
        Window window{WIDTH, HEIGHT, "Clay Editor Vulkan"};
        Device device{window};
        Pipeline pipeline{
            device,
            "/home/quantum/Workspace/Code/ClayEngineVk/src/ClayEngineVk/Shaders/simple_shader.vert.spv",
            "/home/quantum/Workspace/Code/ClayEngineVk/src/ClayEngineVk/Shaders/simple_shader.frag.spv",
            Pipeline::DefaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
}

int main()
{
    help();
    ClayEngineVk::ClayEditorVk editor;

    try
    {
        editor.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}