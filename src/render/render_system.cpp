#include "render_system.hpp"

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <stdexcept>

namespace scandium {

	struct SimplePushconstantData{
		glm::mat4 transform{1.0f};
		alignas(16) glm::vec3 color;
	};

	RenderSystem::RenderSystem(EngineDevice &device, VkRenderPass renderPass) : engineDevice{device}{
		createPipelineLayout();
		createPipeline(renderPass);
	}

	RenderSystem::~RenderSystem(){
		vkDestroyPipelineLayout(engineDevice.device(), pipelineLayout, nullptr);
	}

	void RenderSystem::createPipelineLayout(){
		VkPushConstantRange pushConstantRange;
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(SimplePushconstantData);

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
		if (vkCreatePipelineLayout(engineDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS){
			throw std::runtime_error("Failed to create pipeline layout!");
		}
	}

	void RenderSystem::createPipeline(VkRenderPass renderPass){
		assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

		PipelineConfigInfo pipelineConfig{};
		ScandiumPipeline::defaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = renderPass;
		pipelineConfig.pipelineLayout = pipelineLayout;
		scandiumPipeline = std::make_unique<ScandiumPipeline>(engineDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
	}

	void RenderSystem::renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject> &gameObjects, const Camera &camera){
		scandiumPipeline->bind(commandBuffer);
		for (auto &obj: gameObjects){
			obj.Transform2D.rotate(obj.Transform2D.rotation.x + 0.01f, obj.Transform2D.rotation.x + 0.01f, 0.0f);
			SimplePushconstantData push{};
			push.color = obj.color;
			push.transform = camera.getProjection() * obj.Transform2D.transform();

			vkCmdPushConstants(commandBuffer, pipelineLayout, 
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(SimplePushconstantData), &push);
			obj.model->bind(commandBuffer);
			obj.model->draw(commandBuffer);
		}
	}
}