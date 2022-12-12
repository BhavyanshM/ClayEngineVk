
#include "Core/Core.h"
#include "Window/Window.h"

#include <stdexcept>
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
    };
}

int main()
{
    help();
    ClayEngineVk::ClayEditorVk editor;
    
    int i = 0;

    try
    {
        printf("Running: %d\n", i++);
        editor.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}