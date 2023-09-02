#pragma once

#include <string>
#include <vector>
#include <Device/Device.h>

namespace ClayEngineVk
{

    struct PipelineConfigInfo
    {
    };

    class Pipeline
    {
        public:
            Pipeline(Device &device, 
                     const std::string &vertFilepath, 
                     const std::string &fragFilepath, 
                     const PipelineConfigInfo &configInfo);

            ~Pipeline() {}

            Pipeline(const Pipeline &) = delete;
            void operator=(const Pipeline &) = delete;

            static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);


        private:
            static std::vector<char> ReadFile(const std::string &filepath);

            void CreateGraphicsPipeline(const std::string &vertFilepath, 
                                        const std::string &fragFilepath, 
                                        const PipelineConfigInfo &configInfo);

            void CreateShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

            Device& _device;
            VkPipeline graphicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;            
    };
}