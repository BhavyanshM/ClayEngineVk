#pragma once

#include <string>
#include <vector>
#include <Device/Device.h>

namespace ClayEngineVk
{

    struct PipelineConfigInfo
    {
        VkViewport viewport;
        VkRect2D scissors;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class Pipeline
    {
        public:
            Pipeline(Device &device, 
                     const std::string &vertFilepath, 
                     const std::string &fragFilepath, 
                     const PipelineConfigInfo &configInfo);

            ~Pipeline();

            Pipeline(const Pipeline &) = delete;
            Pipeline& operator=(const Pipeline &) = delete;

            void Bind(VkCommandBuffer commandBuffer);

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