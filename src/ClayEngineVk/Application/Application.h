#pragma once

#include "Core/Core.h"
#include "Window/Window.h"
#include "Pipeline/Pipeline.h"
#include "Device/Device.h"
#include "SwapChain/SwapChain.h"
#include "Model/Model.h"

#include <memory>
#include <stdexcept>

namespace ClayEngineVk
{
    class Application
    {
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;

            void Run();

            Application();
            ~Application();

            Application(const Application&) = delete;
            void operator=(const Application&) = delete;

        private:
            void CreatePipelineLayout();
            void CreatePipeline();
            void CreateCommandBuffers();
            void FreeCommandBuffers();
            void DrawFrame();
            void LoadModels();
            void RecreateSwapChain();
            void RecordCommandBuffer(int imageIndex);

            Window window{WIDTH, HEIGHT, "Clay Editor Vulkan"};
            Device device{window};
            std::unique_ptr<SwapChain> swapChain;
            std::unique_ptr<ClayEngineVk::Pipeline> pipeline;
            std::unique_ptr<Model> model;

            VkPipelineLayout pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;

    };
}