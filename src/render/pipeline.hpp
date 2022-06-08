#pragma once

#include <string>
#include <vector>

#include "engine_device.hpp"

namespace scandium {																																
	struct PipelineConfigInfo{
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class ScandiumPipeline{
 		public:
  			ScandiumPipeline(EngineDevice& device, const std::string& vertFilepath, 
			  const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
			~ScandiumPipeline();

			ScandiumPipeline(const ScandiumPipeline&) = delete;
			void operator = (const ScandiumPipeline&) = delete;

			static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
			void bind(VkCommandBuffer commandBuffer);

 		private:
  			static std::vector<char> readFile(const std::string& filepath);
  			void createGraphicsPipeline(const std::string& vertFilepath,
			  const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
			void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

			EngineDevice& engineDevice;
			VkPipeline graphicsPipeline;
			VkShaderModule vertShaderModule;
			VkShaderModule fragShaderModule;
	};
}