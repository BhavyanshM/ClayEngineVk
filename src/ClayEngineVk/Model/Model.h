#pragma once

#include "Device/Device.h"


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace ClayEngineVk
{
    class Model
    {
        public:

            struct Vertex 
            {
                glm::vec2 position;
                glm::vec3 color;

                static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
                static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
            };

            Model(Device& device, const std::vector<Vertex> &vertices);
            ~Model();

            Model(const Model&) = delete;
            Model& operator=(const Model&) = delete;

            void Bind(VkCommandBuffer commandBuffer);
            void Draw(VkCommandBuffer commandBuffer);

        private:
            void CreateVertexBuffers(const std::vector<Vertex> &vertices);

            Device& device;
            VkBuffer vertexBuffer;
            VkDeviceMemory vertexBufferMemory;
            uint32_t vertexCount;

    };

}