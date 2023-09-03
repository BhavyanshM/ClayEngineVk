
#include <Application/Application.h>

#include <cstdlib>
#include <iostream>
#include <vector>

int main()
{
    ClayEngineVk::Application editor;

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