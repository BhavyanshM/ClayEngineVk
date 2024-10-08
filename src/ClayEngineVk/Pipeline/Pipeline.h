#pragma once

#include <string>
#include <vector>
#include <Device/Device.h>

namespace ClayEngineVk
{

    struct PipelineConfigInfo
    {
        PipelineConfigInfo(const PipelineConfigInfo &) = delete;
        PipelineConfigInfo& operator=(const PipelineConfigInfo &) = delete;

        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicState;
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

            static void DefaultPipelineConfigInfo(PipelineConfigInfo &configInfo);


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