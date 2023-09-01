#include "Pipeline/Pipeline.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace ClayEngineVk
{

    Pipeline::Pipeline(const std::string& vertFilepath, const std::string& fragFilepath)
    {
        CreateGraphicsPipeline(vertFilepath, fragFilepath);
    }

    std::vector<char> Pipeline::ReadFile(const std::string& filepath)
    {
        std::ifstream file(filepath, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filepath);
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;        
    }

    void Pipeline::CreateGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath)
    {
        auto vertCode = ReadFile(vertFilepath);
        auto fragCode = ReadFile(fragFilepath);

        std::cout << "Vertex Shader Code Size: " << vertCode.size() << std::endl;
        std::cout << "Fragment Shader Code Size: " << fragCode.size() << std::endl;
    }
}