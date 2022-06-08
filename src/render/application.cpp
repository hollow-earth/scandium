#include "application.hpp"

#include <stdexcept>
#include <array>

namespace scandium {

	Application::Application(){
		loadModels();
		createPipelineLayout();
		createPipeline();
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
		auto pipelineConfig = ScandiumPipeline::defaultPipelineConfigInfo(scandiumSwapchain.width(), scandiumSwapchain.height());
		pipelineConfig.renderPass = scandiumSwapchain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		scandiumPipeline = std::make_unique<ScandiumPipeline>(engineDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
	}

	void Application::createCommandBuffers() {
		commandBuffers.resize(scandiumSwapchain.imageCount());
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = engineDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(engineDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS){
			throw std::runtime_error("Failed to allocate command buffers!");
		}

		for (int i = 0; i < commandBuffers.size(); i++){
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS){
				throw std::runtime_error("Failed to begin recording command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = scandiumSwapchain.getRenderPass();
			renderPassInfo.framebuffer = scandiumSwapchain.getFrameBuffer(i);

			renderPassInfo.renderArea.offset = {0, 0};
			renderPassInfo.renderArea.extent = scandiumSwapchain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
			clearValues[1].depthStencil = {1.0f, 0};
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			scandiumPipeline->bind(commandBuffers[i]);
			scandiumModel->bind(commandBuffers[i]);
			scandiumModel->draw(commandBuffers[i]);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS){
				throw std::runtime_error("Failed to record a command buffer!");
			}
		}
	}

	void Application::drawFrame() {
		uint32_t imageIndex;
		auto result = scandiumSwapchain.acquireNextImage(&imageIndex);
		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
			throw std::runtime_error("Failed to acquire swapchain image!");
		}
		result = scandiumSwapchain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS){
			throw std::runtime_error("Failed to present swapchain image!");
		}
	}

}