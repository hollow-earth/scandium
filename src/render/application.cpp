#include "application.hpp"

#include <stdexcept>
#include <array>

namespace scandium {

	Application::Application(){
		loadModels();
		createPipelineLayout();
		recreateSwapChain();
		createCommandBuffers();
	}

	Application::~Application(){
		vkDestroyPipelineLayout(engineDevice.device(), pipelineLayout, nullptr);
	}

	void Application::run(){
		while(!renderWindow.shouldClose()){
			glfwPollEvents();
			drawFrame();
		}
		vkDeviceWaitIdle(engineDevice.device());
	}

	void Application::loadModels(){
		std::vector<ScandiumModel::Vertex> vertices {
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}}, 
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}, 
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};
		scandiumModel = std::make_unique<ScandiumModel>(engineDevice, vertices);
	}

	void Application::createPipelineLayout(){
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(engineDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS){
			throw std::runtime_error("Failed to create pipeline layout!");
		}
	}

	void Application::createPipeline(){
		assert(scandiumSwapchain != nullptr && "Cannot create pipeline before swapchain");
		assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

		PipelineConfigInfo pipelineConfig{};
		ScandiumPipeline::defaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = scandiumSwapchain->getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		scandiumPipeline = std::make_unique<ScandiumPipeline>(engineDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
	}

	void Application::recreateSwapChain(){
		auto extent = renderWindow.getExtent();
		while (extent.width == 0 || extent.height == 0){
			extent = renderWindow.getExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(engineDevice.device());
		if (scandiumSwapchain == nullptr){
			scandiumSwapchain = nullptr;
			scandiumSwapchain = std::make_unique<ScandiumSwapchain>(engineDevice, extent);
		}
		else{
			scandiumSwapchain = std::make_unique<ScandiumSwapchain>(engineDevice, extent, std::move(scandiumSwapchain));
			if (scandiumSwapchain->imageCount() != commandBuffers.size()){
				freeCommandBuffers();
				createCommandBuffers();
			}
		}
		
		//TODO: optimization: if render passes are compatible do nothing
		createPipeline();
	}


	void Application::createCommandBuffers() {
		commandBuffers.resize(scandiumSwapchain->imageCount());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = engineDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(engineDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS){
			throw std::runtime_error("Failed to allocate command buffers!");
		}

	}

	void Application::freeCommandBuffers(){
		vkFreeCommandBuffers(engineDevice.device(), engineDevice.getCommandPool(), 
			static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void Application::recordCommandBuffer(int imageIndex){
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS){
			throw std::runtime_error("Failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = scandiumSwapchain->getRenderPass();
		renderPassInfo.framebuffer = scandiumSwapchain->getFrameBuffer(imageIndex);

		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = scandiumSwapchain->getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
		clearValues[1].depthStencil = {1.0f, 0};
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(scandiumSwapchain->getSwapChainExtent().width);
		viewport.height = static_cast<float>(scandiumSwapchain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{{0, 0}, scandiumSwapchain->getSwapChainExtent()};
		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

		scandiumPipeline->bind(commandBuffers[imageIndex]);
		scandiumModel->bind(commandBuffers[imageIndex]);
		scandiumModel->draw(commandBuffers[imageIndex]);

		vkCmdEndRenderPass(commandBuffers[imageIndex]);
		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS){
			throw std::runtime_error("Failed to record a command buffer!");
		}
	}

	void Application::drawFrame() {
		uint32_t imageIndex;
		auto result = scandiumSwapchain->acquireNextImage(&imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR){
			recreateSwapChain();
			return;
		}
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
			throw std::runtime_error("Failed to acquire swapchain image!");
		}
		recordCommandBuffer(imageIndex);
		result = scandiumSwapchain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR  || result == VK_SUBOPTIMAL_KHR || renderWindow.wasWindowResized()){
			renderWindow.resetWindowResizedFlag();
			recreateSwapChain();
			return;
		}
		if (result != VK_SUCCESS){
			throw std::runtime_error("Failed to present swapchain image!");
		}
	}

}