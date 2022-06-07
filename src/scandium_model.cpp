#include "scandium_model.hpp"

#include <cassert>

namespace scandium{
	ScandiumModel::ScandiumModel(EngineDevice &device, const std::vector<Vertex> &vertices) : engineDevice{device}{
		createVertexBuffers(vertices);
	}

	ScandiumModel::~ScandiumModel(){
		vkDestroyBuffer(engineDevice.device(), vertexBuffer, nullptr);
		vkFreeMemory(engineDevice.device(), vertexBufferMemory, nullptr);
	}

	void ScandiumModel::createVertexBuffers(const std::vector<Vertex> &vertices){
		vertexCount = static_cast<uint32_t>(vertices.size());
		assert(vertexCount >= 3 && "Vertex count must be at least 3");
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
		engineDevice.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory);
		void *data;
		vkMapMemory(engineDevice.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(engineDevice.device(), vertexBufferMemory);
	}
}