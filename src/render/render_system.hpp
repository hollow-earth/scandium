#pragma once

#include "camera.hpp"
#include "engine_device.hpp"
#include "pipeline.hpp"
#include "../game/gameObject.hpp"

#include <memory>
#include <vector>

namespace scandium{
	
	class RenderSystem{

		public:
			RenderSystem(EngineDevice &device, VkRenderPass renderPass);
			~RenderSystem();

			RenderSystem(const RenderSystem &) = delete;
			RenderSystem &operator=(const RenderSystem &) = delete;
			
			void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject> &gameObjects, const Camera &camera);
		
		private:
			void createPipelineLayout();
			void createPipeline(VkRenderPass renderPass);

			EngineDevice &engineDevice;
			std::unique_ptr<ScandiumPipeline> scandiumPipeline;
			VkPipelineLayout pipelineLayout;
	};
}