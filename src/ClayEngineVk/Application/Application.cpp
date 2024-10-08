#include <Application/Application.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace ClayEngineVk
{

    struct SimplePushConstantData
    {
        glm::vec2 offset;
        alignas(16) glm::vec3 color;
    };

    void Application::Run()
    {
        while (!window.ShouldClose())
        {
            window.PollEvents();
            DrawFrame();
        }

        vkDeviceWaitIdle(device.device());
    }

    Application::Application()
    {
        LoadModels();
        CreatePipelineLayout();
        RecreateSwapChain();
        CreateCommandBuffers();
    }

    Application::~Application()
    {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void Application::LoadModels()
    {
        std::vector<Model::Vertex> vertices{
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.3f}, {0.0f, 0.0f, 1.0f}}};

        model = std::make_unique<Model>(device, vertices);
    }

    void Application::CreatePipelineLayout()
    {
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(SimplePushConstantData);
        


        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

        if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create pipeline layout!");
        }
    }

    void Application::CreatePipeline()
    {
        assert(swapChain != nullptr && "Cannot create pipeline before swap chain");
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        PipelineConfigInfo pipelineConfig{};
        Pipeline::DefaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = swapChain->GetRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<Pipeline>(
            device, 
            "/home/quantum/Workspace/Code/ClayEngineVk/src/ClayEngineVk/Shaders/simple_shader.vert.spv", 
            "/home/quantum/Workspace/Code/ClayEngineVk/src/ClayEngineVk/Shaders/simple_shader.frag.spv", 
            pipelineConfig);

    }

    void Application::RecreateSwapChain()
    {
        auto extent = window.GetExtent();
        while (extent.width == 0 || extent.height == 0)
        {
            extent = window.GetExtent();
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(device.device());

        if (swapChain == nullptr)
        {
            swapChain = std::make_unique<SwapChain>(device, extent);
        }
        else
        {
            swapChain = std::make_unique<SwapChain>(device, extent, std::move(swapChain));
            if (swapChain->ImageCount() != commandBuffers.size())
            {
                FreeCommandBuffers();
                CreateCommandBuffers();
            }
        }

        swapChain = std::make_unique<SwapChain>(device, extent);
        CreatePipeline();
    }

    void Application::CreateCommandBuffers()
    {
        commandBuffers.resize(swapChain->ImageCount());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = device.GetCommandPool();
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate command buffers!");
        }        
    }

    void Application::FreeCommandBuffers()
    {
        vkFreeCommandBuffers(device.device(), device.GetCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
        commandBuffers.clear();
    }

    void Application::RecordCommandBuffer(int imageIndex)
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = swapChain->GetRenderPass();
        renderPassInfo.framebuffer = swapChain->GetFrameBuffer(imageIndex);

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChain->GetSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
        clearValues[1].depthStencil = {1.0f, 0};
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(swapChain->GetSwapChainExtent().width);
        viewport.height = static_cast<float>(swapChain->GetSwapChainExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        VkRect2D scissor{{0, 0}, swapChain->GetSwapChainExtent()};
        vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
        vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

        pipeline->Bind(commandBuffers[imageIndex]);
        model->Bind(commandBuffers[imageIndex]);


        for (int j = 0; j < 4; j++)
        {
            SimplePushConstantData push{};
            push.offset = {0.4f, -0.4f + j * 0.25f};
            push.color = {0.0f, 0.0f, 0.2f + 0.2f * j};
            vkCmdPushConstants(
                commandBuffers[imageIndex],
                pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0,
                sizeof(SimplePushConstantData),
                &push);

            model->Draw(commandBuffers[imageIndex]);
        }

        vkCmdEndRenderPass(commandBuffers[imageIndex]);

        if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to record command buffer!");
        }
    }

    void Application::DrawFrame()
    {
        uint32_t imageIndex;
        auto result = swapChain->AcquireNextImage(&imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR)
        {
            RecreateSwapChain();
            return;
        }

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("Failed to acquire swap chain image!");
        }

        RecordCommandBuffer(imageIndex);
        result = swapChain->SubmitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window.FrameBufferResized())
        {
            window.ResetFrameBufferResizedFlag();
            RecreateSwapChain();
            return;
        }

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to present swap chain image!");
        }

    }
}