#pragma once

#include "engine_device.hpp"
#include "pipeline.hpp"
#include "renderer.hpp"
#include "scandium_swapchain.hpp"
#include "scandium_model.hpp"

#include <memory>
#include <vector>

namespace scandium{
	
	class Application{

		public:
			static const int WIDTH = 800;
			static const int HEIGHT = 600;
			
			Application();
			~Application();

			Application(const Application &) = delete;
			Application &operator=(const Application &) = delete;

			void run();
			
		private:
			void loadModels();
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void drawFrame();

			rendererWindow renderWindow{WIDTH, HEIGHT, "Bruh"};
			EngineDevice engineDevice{renderWindow};
			ScandiumSwapchain scandiumSwapchain{engineDevice, renderWindow.getExtent()};
			std::unique_ptr<ScandiumPipeline> scandiumPipeline;
			VkPipelineLayout pipelineLayout;
			std::vector<VkCommandBuffer> commandBuffers;
			std::unique_ptr<ScandiumModel> scandiumModel;
	};
}