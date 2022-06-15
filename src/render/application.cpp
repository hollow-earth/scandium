#include "application.hpp"
#include "render_system.hpp"

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <stdexcept>

namespace scandium {

	Application::Application(){
		loadGameObjects();
	}

	Application::~Application(){}

	void Application::run(){
		RenderSystem renderSystem{engineDevice, renderer.getSwapChainRenderPass()};

		while(!renderWindow.shouldClose()){
			glfwPollEvents();

			if (auto commandBuffer = renderer.beginFrame()){
				renderer.beginSwapChainRenderPass(commandBuffer);
				renderSystem.renderGameObjects(commandBuffer, gameObjects);
				renderer.endSwapChainRenderPass(commandBuffer);
				renderer.endFrame();
			}
		}
		vkDeviceWaitIdle(engineDevice.device());
	}

	void Application::loadGameObjects(){
		std::vector<ScandiumModel::Vertex> vertices {
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}}, 
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}, 
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};
		auto scandiumModel = std::make_shared<ScandiumModel>(engineDevice, vertices);
		auto triangle = GameObject::createGameObject();
		triangle.model = scandiumModel;
		triangle.color = {0.1f, 0.8f, 0.1f};
		triangle.Transform2D.translate(0.0f, 0.0f);
		triangle.Transform2D.scale(1.0f, 0.5f);
		triangle.Transform2D.rotate(0.0f, 0.0f, 0.0f);
		triangle.Transform2D.flip_x();
		gameObjects.push_back(std::move(triangle));
	}
}