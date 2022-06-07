#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "engine_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

namespace scandium{
	class ScandiumModel{
		public:
			struct Vertex{
				glm::vec2 position;
				glm::vec3 color;
				
				static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
				static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
			};

			ScandiumModel(EngineDevice &device, const std::vector<Vertex> &vertices);
			~ScandiumModel();

			ScandiumModel(const ScandiumModel &) = delete;
			ScandiumModel &operator=(const ScandiumModel &) = delete;

			void bind(VkCommandBuffer commandBuffer);
			void draw(VkCommandBuffer commandBuffer);

		private: 
			void createVertexBuffers(const std::vector<Vertex> &vertices);

			EngineDevice& engineDevice;
			VkBuffer vertexBuffer;
			VkDeviceMemory vertexBufferMemory;
			uint32_t vertexCount;
	};
}