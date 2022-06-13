#pragma once

#include "engine_device.hpp"
#include "window.hpp"
#include "scandium_swapchain.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace scandium{
	
	class Renderer{

		public:
			Renderer(Window &window, EngineDevice &device);
			~Renderer();

			Renderer(const Renderer &) = delete;
			Renderer &operator=(const Renderer &) = delete;

			VkRenderPass getSwapChainRenderPass() const { return scandiumSwapchain->getRenderPass(); }
			bool isFrameInProgress() const { return isFrameStarted; }
			
			VkCommandBuffer getCurrentCommandBuffer() const{
				assert(isFrameStarted && "Cannot get command buffer when frame not in progress)");
				return commandBuffers[currentFrameIndex];
			}

			int getFrameIndex() const{
				assert(isFrameStarted && "Cannot get frame index when frame not in progress");
				return currentFrameIndex;
			}

			VkCommandBuffer beginFrame();
			void endFrame();
			void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
			void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

		private:
			void createCommandBuffers();
			void freeCommandBuffers();
			void recreateSwapChain();

			Window& renderWindow;
			EngineDevice& engineDevice;
			std::unique_ptr<ScandiumSwapchain> scandiumSwapchain;
			std::vector<VkCommandBuffer> commandBuffers;

			uint32_t currentImageIndex;
			int currentFrameIndex{0};
			bool isFrameStarted;
	};
}